# 🚀 Insane Sound System (V4)

Willkommen beim **Insane Sound System V4**! Dies ist eine kompromisslose, WLAN- und Bluetooth-fähige Audio-Matrix auf Basis des ESP32-S3 und eines ESP32 D1 Mini. Es kombiniert High-Fidelity I2S-Audio, automatische Quellenumschaltung per Hardware-Multiplexer, einen Class-D Verstärker und 4-Zonen WS2811-LED-Steuerung auf einem einzigen, optimierten Custom-PCB.

## 📦 Verzeichnis-Inhalt
* `/Gerber/` - Die Produktionsdaten für die Platine (ZIP-Datei).
* `/ESPHome/` - Die `.yaml` Konfigurationsdatei für das ESP32-S3 Mainboard.
* `/Arduino/` - Der `.ino` Sketch für den Bluetooth-Empfänger (D1 Mini).

---

## 🛠️ Schritt 1: Die Platine fertigen lassen
Lade die ZIP-Datei aus dem Ordner `/Gerber/` bei einem Platinenfertiger deiner Wahl (z. B. über AliExpress oder JLCPCB) hoch. Das Board nutzt zwei Lagen (Top/Bottom). Alle Toleranzen sind Standard, du brauchst keine teuren Sonderfertigungs-Optionen wählen.

## 🛒 Schritt 2: Bauteile besorgen & Bestückung
Die nötigen SMD- und THT-Bauteile bekommst du problemlos und günstig bei Shops wie Amazon oder AliExpress. Eine genaue Stückliste findest du weiter unten.

**Wichtige Löthinweise:**
1. **Thermik:** Achte darauf, dass das untere Pad (Exposed Pad) des TPA3110D2-Chips gut mit den Thermal-Vias auf der Platine verlötet ist.
2. **GND-Jumper (GNDC):** Schließe den Jumper an H4, um die saubere Elektronik-Masse mit der Power-Masse zu verbinden (Star-Ground Konzept für rauschfreien Sound).
3. **Terminierung:** Die 22-Ohm-Widerstände sitzen absichtlich extrem nah an den GPIOs der ESPs. Vergiss diese nicht, sie verhindern Audio-Verzerrungen auf dem I2S-Bus!

---

## 💻 Schritt 3: Software 1 - Der Bluetooth-ESP (D1 Mini)
Der D1 Mini ist ausschließlich für den Bluetooth-Empfang zuständig und triggert die automatische Umschaltung.

1. Öffne die `.ino` Datei in der **Arduino IDE**.
2. Installiere über den Bibliotheksverwalter folgende Libraries: `ESP32-A2DP` (von pschatzmann) und `WiFiManager` (von tzapu).
3. **WICHTIG VOR DEM FLASHEN:** Wenn der D1 Mini bereits auf die Hauptplatine gelötet ist, **ziehe zwingend das 24V-Netzteil ab**, bevor du das USB-Kabel einsteckst! (Schutz vor Spannungskollisionen).
4. Flashe den Code auf den ESP32 D1 Mini.
5. **Erster Start:** Der ESP spannt für 60 Sekunden ein WLAN namens `INSANE-SETUP` auf. Verbinde dich mit dem Handy und trage dein Heim-WLAN ein.

---

## 🏠 Schritt 4: Software 2 - Das Mainboard (ESP32-S3 N16R8)
Der S3 steuert LEDs, Lüfter, Home Assistant Streams und den Hardware-Multiplexer.

1. Binde den S3 in dein **ESPHome** Dashboard ein.
2. Kopiere den kompletten Inhalt der beiliegenden `.yaml` Datei in deine ESPHome-Konfiguration.
3. Passe oben im Code deine WLAN-Daten (`!secret`) an.
4. Flashe das Board (z. B. initial über USB, danach via OTA). 
5. **Hinweis:** Der Code aktiviert automatisch den 8MB Octal-PSRAM des S3. Der Audio-Puffer ist damit gigantisch und Streams laufen absolut ruckelfrei.

---

## 🔌 Schritt 5: Verkabelung & Erster Start
1. Verbinde deine Lautsprecher an den Schraubklemmen (`L+ / L-` und `R+ / R-`).
2. Schließe deine WS2811 LED-Streifen an die 4 Zonen-Ausgänge an.
3. **Lüfter:** Schließe deinen **5V Gehäuselüfter** an. Der Pluspol kommt an die 5V-Spannungsschiene, der Minuspol wird über den BC547B Transistor per PWM (GPIO 42) automatisch temperaturgesteuert.
4. **Power On:** Verbinde das 24V Netzteil. 

*Standardmäßig ist das System im WLAN-Modus (Home Assistant). Sobald du dich mit dem Handy per Bluetooth verbindest und "Play" drückst, schaltet der Hardware-Multiplexer blitzschnell und knackfrei auf den Bluetooth-Stream um!*

---

## 🛒 Stückliste (BOM - Bill of Materials)

### 🧠 Mikrocontroller & Module
| Bauteil / Bezeichnung | Menge | Beschreibung |
| :--- | :--- | :--- |
| **ESP32-S3-DevKitC-1 N16R8** | 1 | Das Mainboard (Wichtig: Auf die Variante mit 16MB Flash und 8MB PSRAM achten!) |
| **ESP32 D1 Mini BL** | 1 | Das Bluetooth-Empfängermodul |
| **PCM5102A Modul** | 1 | High-Fidelity I2S Audio DAC |
| **MP1584EN Modul** | 1 | Step-Down Konverter (Erzeugt 5V aus 24V) |

### 🎵 Audio & Logik-ICs (SMD)
| Bauteil / Bezeichnung | Menge | Beschreibung |
| :--- | :--- | :--- |
| **TPA3110D2PWP** | 1 | 15W+15W Class-D Audio-Verstärker-Chip |
| **SN74CB3Q3257PWR** | 1 | 4-Kanal Hochgeschwindigkeits-Multiplexer (Der Hardware-Switch!) |
| **SN74AHCT125N** | 1 | Quad Level-Shifter (Macht aus 3.3V saubere 5V für die WS2811 LEDs) |
| **LM75AD** | 3 | I2C Temperatur-Sensoren für die Klima-Überwachung |

### ⚡ Leistungselektronik & Kühlung
| Bauteil / Bezeichnung | Menge | Beschreibung |
| :--- | :--- | :--- |
| **BC547B** | 1 | NPN-Transistor (Für die PWM-Steuerung des Lüfters) |
| **1N5822** | 1 | Schottky-Diode (Freilaufdiode zum Schutz des Lüfter-Transistors) |
| **5V Gehäuselüfter** | 1 | Für die aktive Kühlung des Gehäuses |
| **Sicherungen (FUSE)** | 5 | RND 205-00232 SMD-Sicherungen (Für den 24V-Eingang und die LED-Zonen) |

### 🧲 Passive Bauteile (Kondensatoren & Spulen)
| Bauteil / Bezeichnung | Menge | Beschreibung |
| :--- | :--- | :--- |
| **1000µF / 50V Elko** | 2 | Pufferkondensatoren für die 24V Verstärker-Spannung |
| **470µF / 50V Elko** | 4 | Pufferkondensatoren für die LED-Datenleitungen |
| **12µH SMD-Spule** | 4 | Ausgangsfilter für den TPA3110 Verstärker |
| **4.7µH SMD-Spule** | 1 | Für den Step-Down Schaltkreis |
| **220nF Keramik**| 4 | Filter-Kondensatoren am Audio-Ausgang |
| **100nF Keramik**| 12+ | Entkopplungskondensatoren (Über die Platine verteilt) |
| **1µF Keramik** | 4 | Für den TPA3110 Audio-Eingang |

### 🔌 Widerstände
| Bauteil / Bezeichnung | Menge | Beschreibung |
| :--- | :--- | :--- |
| **10kΩ SMD** | 3+ | Pull-Up / Pull-Down (z. B. für den Lüfter oder den Amp-Gain) |
| **22Ω - 33Ω SMD** | 6 | I2S-Terminierungswiderstände (Direkt an den TX-Pins von S3 und D1 Mini anbringen!) |

---

## ⚖️ Lizenz
Dieses komplette Projekt (Hardware und Software) steht unter der [CC BY-NC-SA 4.0 Lizenz](https://creativecommons.org/licenses/by-nc-sa/4.0/). 
Das bedeutet: Nachbauen und Anpassen für private Zwecke ist ausdrücklich erwünscht, jede kommerzielle Nutzung oder der Verkauf sind strikt verboten!

---

## 👨‍💻 Entwickelt von

| [<img src="https://avatars.githubusercontent.com/u/43302033?v=4" width="100"><br><sub>**Christopher**</sub>](https://github.com/babeinlovexd) |
| :---: |

---
