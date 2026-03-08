#!/bin/bash
# Zwingt das Terminal, im Ordner des Skripts zu arbeiten
cd "$(dirname "$0")" || exit

# Farb-Codes fuer Mac/Linux Terminals
CYAN='\033[0;36m'
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
NC='\033[0m' # Kein Farbe

clear
echo -e "${CYAN}"
echo "   ██ ███   ██  ██████  █████  ███   ██ ███████ "
echo "   ██ ████  ██ ██      ██   ██ ████  ██ ██      "
echo "   ██ ██ ██ ██  █████  ███████ ██ ██ ██ █████   ━━━━"
echo "   ██ ██  ████      ██ ██   ██ ██  ████ ██      "
echo "   ██ ██   ███ ██████  ██   ██ ██   ███ ███████"
echo ""
echo "       ISS  BLUETOOTH V5 AUTO-FLASHER TOOL"
echo "======================================================="
echo -e "${NC}"

# --- SCHRITT 0: FIRMWARE SUCHEN ODER VON GITHUB LADEN ---

FIRMWARE_FILE=$(ls *.merged.bin 2>/dev/null | head -n 1)

if [ -z "$FIRMWARE_FILE" ]; then
    echo -e "${CYAN}[INFO] Keine lokale Firmware-Datei gefunden.${NC}\n"
    read -p "Die Firmware wird benoetigt. Moechtest du sie jetzt von GitHub herunterladen? [J/N]: " choice
    case "$choice" in 
        j|J )
            echo -e "\n${CYAN}[INFO] Suche auf GitHub nach Updates...${NC}"
            
            # API-Abfrage mit curl (grep extrahiert die URL der *.merged.bin)
            DOWNLOAD_URL=$(curl -s -H "User-Agent: Mozilla/5.0" "https://api.github.com/repos/babeinlovexd/insane-sound-system/contents/Firmware?ref=V5-dev" | grep -o '"download_url": *"[^"]*merged\.bin"' | head -n 1 | cut -d '"' -f 4)

            if [ -z "$DOWNLOAD_URL" ]; then
                echo -e "${RED}[FEHLER] Konnte keine Firmware auf GitHub finden!${NC}"
                exit 1
            fi

            FIRMWARE_FILE=$(basename "$DOWNLOAD_URL")
            curl -L -H "User-Agent: Mozilla/5.0" -o "$FIRMWARE_FILE" "$DOWNLOAD_URL"
            
            if [ $? -ne 0 ]; then
                echo -e "${RED}[FEHLER] Download fehlgeschlagen! Bitte Internetverbindung pruefen.${NC}"
                exit 1
            fi
            echo -e "${GREEN}[OK] Firmware erfolgreich geladen!${NC}\n"
            ;;
        * )
            echo -e "\n${RED}[ABBRUCH] Ohne Firmware kann der Flash-Vorgang nicht gestartet werden.${NC}"
            exit 1
            ;;
    esac
fi

echo -e "${CYAN}[INFO] Firmware-Datei gefunden: $FIRMWARE_FILE${NC}\n"

# --- SCHRITT 0.1: ESPTOOL PRUEFEN & INSTALLIEREN ---

# Pruefe ob esptool.py oder esptool installiert ist
if ! command -v esptool.py &> /dev/null && ! command -v esptool &> /dev/null; then
    echo -e "${CYAN}[INFO] Flasher-Engine 'esptool' nicht gefunden.${NC}\n"
    read -p "Das Flasher-Tool wird benoetigt. Moechtest du es jetzt via Python installieren? [J/N]: " choice
    case "$choice" in 
        j|J )
            echo -e "\n${CYAN}[INFO] Installiere esptool ueber pip...${NC}"
            pip3 install esptool || pip install esptool
            if [ $? -ne 0 ]; then
                echo -e "${RED}[FEHLER] Installation fehlgeschlagen! Bitte stelle sicher, dass Python3 installiert ist.${NC}"
                exit 1
            fi
            echo -e "${GREEN}[OK] esptool erfolgreich installiert!${NC}\n"
            ;;
        * )
            echo -e "\n${RED}[ABBRUCH] Ohne Flasher-Engine kann nicht geflasht werden.${NC}"
            exit 1
            ;;
    esac
fi

# Setze den korrekten Befehlsnamen fuer Mac/Linux
ESP_CMD="esptool.py"
if ! command -v esptool.py &> /dev/null; then
    ESP_CMD="esptool"
fi

# --- SCHRITT 1: VORBEREITUNG ---

echo "SCHRITT 1: VORBEREITUNG"
echo "1. Gehe in dein Home Assistant."
echo "2. Oeffne das Dashboard fuer dein Insane Sound System."
echo "3. Druecke dort den Button \"WROOM in Flash-Modus setzen\"."
echo ""
read -p "Druecke Enter, wenn du bereit bist..."

# --- SCHRITT 2: VERBINDUNG & PING-LOOP ---

echo -e "\nSCHRITT 2: VERBINDUNG"
read -p "Gib die IP-Adresse deines Insane Sound Systems ein (z.B. 192.168.178.50): " IP_ADDR
echo ""

MAX_TRIES=3
TRY_COUNT=0
SUCCESS=0

while [ $TRY_COUNT -lt $MAX_TRIES ]; do
    ((TRY_COUNT++))
    echo -e "${CYAN}[INFO] Pruefe Verbindung zu $IP_ADDR (Versuch $TRY_COUNT/$MAX_TRIES)...${NC}"
    
    # Ping-Befehl kombiniert fuer Mac (-t) und Linux (-W)
    if ping -c 1 -W 2 "$IP_ADDR" &> /dev/null || ping -c 1 -t 2 "$IP_ADDR" &> /dev/null; then
        SUCCESS=1
        break
    fi
    
    if [ $TRY_COUNT -lt $MAX_TRIES ]; then
        echo -e "${YELLOW}[WARNUNG] Keine Antwort vom Board. Neuer Versuch in 2 Sekunden...${NC}"
        sleep 2
    fi
done

if [ $SUCCESS -eq 0 ]; then
    echo -e "\n${RED}[FEHLER] Das Board unter $IP_ADDR antwortet nach $MAX_TRIES Versuchen nicht!${NC}"
    echo "Ist das Insane Sound System eingeschaltet und im selben WLAN?"
    exit 1
fi

echo -e "${GREEN}[OK] Verbindung erfolgreich hergestellt!${NC}\n"

# --- SCHRITT 3: FLASH-VORGANG ---

echo "======================================================="
echo "VERBINDE MIT $IP_ADDR UND FLASHE BLUETOOTH-MODUL..."
echo "/!\ BITTE DAS SYSTEM JETZT NICHT VOM STROM TRENNEN /!\\"
echo "======================================================="
echo ""

$ESP_CMD --port socket://$IP_ADDR:8888 write_flash 0x0 "$FIRMWARE_FILE"

if [ $? -ne 0 ]; then
    echo -e "\n${RED}======================================================="
    echo "[FEHLER] Der Flash-Vorgang ist fehlgeschlagen!"
    echo "Hast du den Button \"WROOM in Flash-Modus setzen\" gedrueckt?"
    echo "=======================================================${NC}"
    exit 1
fi

# --- ABSCHLUSS ---

echo -e "\n${GREEN}======================================================="
echo "                     BÄÄÄM! FERTIG! "
echo "======================================================="
echo "Dein Insane Sound System hat jetzt die Faehigkeit Bluetooth :)"
echo ""
echo "Bitte trenne die Box jetzt fuer 5 Sekunden vom Strom"
echo "und stecke sie danach wieder ein."
echo -e "=======================================================${NC}"