# 🔊 Insane Sound System V5
<div align="center">
  <img src="https://img.shields.io/github/v/release/babeinlovexd/Insane-Sound-System?style=for-the-badge&color=2ecc71" alt="Latest Release">
  <img src="https://img.shields.io/badge/Status-Stable-2ecc71?style=for-the-badge" alt="Status">
  <img src="https://img.shields.io/badge/ESPHome-Ready-03A9F4?style=for-the-badge&logo=esphome" alt="ESPHome">
  <img src="https://img.shields.io/badge/Hardware-V5.5-f39c12?style=for-the-badge&logo=pcb" alt="Hardware Version">
  <img src="https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-lightgrey?style=for-the-badge&logo=creative-commons" alt="License: CC BY-NC-SA 4.0">
</div>
<br>

🌍 **[Read this in English](README_en.md)**

Willkommen beim **Insane Sound System V5** dem ultimativen, smarten High-End WLAN & Bluetooth Lautsprecher-Controller!

Monatelange Entwicklung, unzählige Prototypen, Schweiß, Tränen und der unbändige Wille, die absolut perfekte Audio-Zentrale zu erschaffen, sind in diese Platine geflossen. Das **Insane Sound System V5** ist das ultimative Resultat dieses Wahnsinns. 

**Was ist das Insane Sound System überhaupt?**
Es ist nicht einfach nur ein Verstärker-Board. Es ist das kompromisslose, smarte Herzstück für deine selbstgebaute High-End-Audiobox. Es verbindet audiophile Hardware mit der unendlichen Flexibilität von Smart Homes und gibt dir die absolute Kontrolle über Sound, Licht und Hardware – alles auf einer winzigen, professionellen 100x100mm Platine.

### 🔥 Was kann das Teil ALLES?
Dieses Board ist bis unter die Zähne bewaffnet mit Features:
* **Nahtlose Dual-Audio-Quellen:** Streame Musik über WLAN (Home Assistant/ESPHome) oder verbinde dein Handy direkt über Bluetooth. Ein dedizierter Hardware-Multiplexer schaltet verlustfrei und absolut knackfrei zwischen den Audioquellen um.
* **Bluetooth mit Metadaten:** Der Bluetooth-Chip streamt nicht nur Musik, sondern schickt Titel, Interpret, Album und den Play/Pause-Status direkt auf dein Smart-Home-Dashboard.
* **Insane Turbo Mode:** Zu leise? Ein digital schaltbarer Gain-Boost auf Hardware-Ebene holt die maximale Lautstärke aus dem TPA3110-Verstärker heraus.
* **3-Zonen RGB-Lichtshow:** Steuere bis zu drei separate 24V WS28xx-LED-Streifen direkt über die Platine (mit integriertem Level-Shifter für saubere 5V-Datensignale). Inklusive Effekten wie "Knight Rider", "Feuerwerk" oder "Regenbogen".
* **Smartes Thermomanagement:** Drei unabhängige Temperatursensoren (I2C) überwachen Verstärker, Spannungsregler und Gehäusetemperatur. Wird es heiß, regelt das System stufenlos einen 5V-PWM-Gehäuselüfter hoch. Droht der Hitzetod, greift die automatische Notabschaltung.
* **Vollautomatische Stromspar-Logik:** Der Verstärker und der DAC werden hardwareseitig in den Standby (Mute) geschickt, wenn keine Musik spielt. Kein Grundrauschen, kein unnötiger Stromverbrauch.
* **Over-The-Air (OTA) Updates für ALLE Chips:** Flashe nicht nur das Hauptsystem über WLAN, sondern – dank unseres massgeschneiderten InsaneFLasher – auch den abgetrennten Bluetooth-Chip komplett drahtlos über das Netzwerk!

Diese Version wurde von Grund auf neu entwickelt. Das Ziel: Maximale Audio-Leistung, idiotensichere Bedienung und ein Hardware-Design, das sich professionell fertigen und trotzdem völlig entspannt zu Hause zusammenbauen lässt.

<img src="Images/3.png" width="400" alt="Insane Sound System V5 - 3D Render">

## ✨ Was ist neu in V5? (Hardware & Features)

Wir haben keine halben Sachen gemacht. V5 bringt massive Upgrades unter der Haube:

* **Kompaktes 100x100mm Design:** Die Platine passt in fast jedes Gehäuse und bleibt genau unter der magischen Grenze, um bei PCB-Herstellern extrem günstig bestellt werden zu können. Bessere Thermik und optimales Routing auf kleinstem Raum!
* **Handlötfreundliches SMD-Design:** Das Board besteht zu 90% aus SMD-Bauteilen für kürzere, saubere Signalwege und ein modernes Design. **Keine Panik:** Die kleinsten Bauteile sind strikt auf die **Größe 1206** limitiert! Du brauchst kein Mikroskop und keine ruhigen Chirurgen-Hände, alles lässt sich völlig entspannt von Hand löten.
* **Dual-Brain Architektur:** Ein moderner ESP32-S3 steuert als Haupt-Hirn Home Assistant, WLAN und LEDs. Ein dedizierter ESP32-WROOM-32E kümmert sich *ausschließlich* um verlustfreies Bluetooth-Audio.
* **Echter Hardware-Multiplexer:** Der SN74CB3Q3257 Chip schaltet das I2S-Audiosignal blitzschnell und ohne nerviges Knacken zwischen WLAN (S3) und Bluetooth (WROOM) um.
* **Smartes Temperatur-Management:** Drei LM75A-Sensoren überwachen den Verstärker (TPA3110), die Spannungsregler und die ESP32-Umgebung. Ein 5V-Gehäuselüfter wird stufenlos per PWM gesteuert, sobald es im Gehäuse warm wird.
* **Over-The-Air Bluetooth Updates:** Das WROOM-Modul kann jetzt komplett drahtlos über WLAN geflasht werden. Kein USB-Kabel, kein Schrauben – einfach per Knopfdruck im Dashboard!

  > **💡 Hinweis zur Audio-Architektur:** Das Insane Sound System nutzt ab Version 5.2 die hochmoderne, modulare `platform: speaker` Audio-Pipeline von ESPHome (kompatibel mit ESPHome 2026.3.0+). Dein ESP32 profitiert dadurch von nativem Transcoding, wodurch Home Assistant (ab 2024.10+) die Audio-Streams rechenschonend weiterleitet. Das sorgt für stabilere Verbindungen und macht das System zum idealen Partner für Music Assistant!

<img src="Images/2.svg" width="400" alt="Platinen Layout 2D Ansicht">

---

## 🛒 Einkaufsliste & Bauteile (BOM)

Die komplette und detaillierte Liste aller benötigten Bauteile findest du im Ordner `BOM/` (als Datei `BOM_insane-sound-system-v5_xxxx-xx-xx.csv`). 

Fast alle Standard-Komponenten (wie die 1206 Widerstände, Kondensatoren, ESP-Module und den Verstärker-Chip) kannst du problemlos in vielen Shops bestellen. 

---

## 🛠️ Die Schritt-für-Schritt Anleitung

Jeder kann dieses System bauen. Folge einfach stur diesen Schritten:

### Schritt 1: Hardware löten
1. Bestelle die Platine anhand der Gerber-Dateien im Ordner `Gerber/`.
2. Löte zuerst die SMD-Bauteile (Größe 1206) auf. Beginne mit den flachen Bauteilen (Widerstände, Kondensatoren) und arbeite dich zu den größeren Chips vor.
3. **WICHTIG:** Verlöte das große Masse-Pad (Exposed Pad / EP) auf der Unterseite des ESP32-WROOM zwingend mit der Platine! Das ist nicht nur für die Erdung wichtig, sondern fungiert als essenzieller Kühlkörper. Ohne diese Verbindung überhitzt der Chip.

### 🛠️ Bestückungshilfe
Hier findest du die interaktive Stückliste (iBOM) für das Insane Sound System:
<a href="https://htmlpreview.github.io/?https://github.com/babeinlovexd/Insane-Sound-System/blob/main/BOM/PCB_insane%20sound%20system%20v5.1_rev0.html">👉 <b>Interaktive Bestückungshilfe</b></a>

### Schritt 2: ESPHome vorbereiten (Mainboard S3)
Aus Sicherheitsgründen nutzt dieses Projekt ausgelagerte Passwörter. 
1. Erstelle in deinem Home Assistant / ESPHome-Ordner eine neue Datei namens `secrets.yaml`.
2. Füge exakt diese Struktur mit deinen eigenen, echten Daten ein:
   ```yaml
   api_encryption_key: "DEIN_API_KEY"
   ota_password: "DEIN_OTA_PASSWORD"
   wifi_ssid: "DEIN_WLAN_NAME"
   wifi_password: "DEIN_WLAN_PASSWORT"
   ap_password: "DEIN_FALLBACK_HOTSPOT_PASSWORT"
   web_server_username: "DEIN_WEB_SERVER_BENUTZERNAME"
   web_server_password: "DEIN_WEB_SERVER_PASSWORT"
   ```
3. Lade die Datei `insane-sound-system-v5.yaml` aus dem Ordner `ESPHome/` in dein ESPHome-Dashboard hoch.
4. **LEDs und Front-Panel aktivieren (Packages):** In der `insane-sound-system-v5.yaml` findest du ganz oben unter `packages:` Konfigurationsblöcke für verschiedene LED-Streifen (WS2811, WS2814, WS2805) sowie das optionale Front-Panel.
   * **LEDs:** Markiere den Block des LED-Typs, den du nutzt, und entferne die Rauten (`#`) am Anfang der Zeilen (Tipp: Block markieren und `Strg` + `#` drücken). Es darf **nur ein** LED-Block gleichzeitig aktiv sein!
   * **Front-Panel (Optional):** Falls du die Frontpanel-Erweiterung (OLED & Tasten) nutzt, entferne auf dieselbe Weise die Rauten vor `frontpanel:`, `url:` und `file:`.
5. Schließe den **ESP32-S3** per USB an deinen Rechner an und flashe ihn das allererste Mal ganz normal über das Kabel.

<img src="Images/1.svg" width="300" alt="Detailansicht Bottom">

## 🚀 Das offizielle InsaneFlasher Tool (All-in-One)

Schluss mit komplizierten Kommandozeilen! Das Insane Sound System V5 kommt jetzt mit einem eigenen, professionellen Hub für **Windows, macOS und Linux**.

Der **InsaneFlasher** ist dein zentrales Dashboard zur Steuerung, Überwachung und Wartung deines Insane Sound System`s. Dank ZeroConf-Technologie findet das Tool dein Insane Sound System automatisch im Netzwerk.

### ✨ Features des Tools
* **Live Telemetrie-Dashboard:** Überwache Temperaturen (inkl. dynamischer Warn-Balken!), Audio-Quellen, WLAN-Signal und laufende Bluetooth-Metadaten in Echtzeit (1-Sekunden-Takt).
* **One-Click OTA Flashing:** Update den internen Bluetooth-Chip (WROOM) komplett kabellos. Der Main-ESP32 (S3) fungiert als unsichtbare Bridge (`socket://<IP>:8888`) und flasht den WROOM über seine Hardware-Pins – kein USB-Kabel nötig!
* **Automatischer Versions-Check:** Das Tool gleicht die WROOM-Firmware deiner Box automatisch mit GitHub ab und meldet sich, sobald ein Update bereitsteht.
* **Favoriten-Speicher:** Speichere deine festen Insane Sound Systeme ab, um den Netzwerk-Scan beim nächsten Start zu überspringen.
* **Hardware-Reset:** Zwinge den WROOM-Chip per Fernwartung zu einem sauberen Reboot, falls sich das Bluetooth mal aufhängt.

### Schritt 3: Das Bluetooth-Modul flashen (mit dem InsaneFlasher)
Sobald dein Mainboard (S3) im WLAN läuft, flashen wir den Bluetooth-Chip (WROOM) drahtlos:

**🪟 Für Windows-Nutzer (Empfohlen):**
1. Lade dir die neueste `InsaneFlasher.exe` aus dem `InsaneFlasher/Windows/` Ordner herunter.
2. Doppelklick auf die `.exe` – das Tool startet sofort (keine Installation nötig).

**🍎/🐧 Für macOS & Linux Nutzer:**
1. Stelle sicher, dass Python 3 auf deinem System installiert ist, und lade dir den Quellcode `InsaneFlasher.py` aus dem `InsaneFlasher/Linux_Mac/` Ordner herunter.
2. Installiere die nötigen Pakete im Terminal: `pip install customtkinter requests esptool zeroconf pillow packaging`
3. Starte das Tool: `python3 InsaneFlasher.py`

**Der Flash-Vorgang:**
Wähle dein Insane Sound System im Tool aus und klicke einfach auf den großen roten Button **"UPDATE JETZT INSTALLIEREN"**. Das Tool lädt automatisch die neueste Firmware herunter, bringt den Chip in den Flash-Modus, installiert das Update und startet das Insane Sound System neu. Lehn dich einfach zurück!

**Glückwunsch! Dein Insane Sound System V5 ist jetzt voll einsatzbereit!**

<img src="Images/4.svg" width="800" alt="Schematic">

---

## ⚖️ Lizenz
Dieses komplette Projekt (Hardware und Software) steht unter der [CC BY-NC-SA 4.0 Lizenz](https://creativecommons.org/licenses/by-nc-sa/4.0/). 
Das bedeutet: Nachbauen und Anpassen für private Zwecke ist ausdrücklich erwünscht, jede kommerzielle Nutzung oder der Verkauf sind strikt verboten!

---

## ☕ Support dieses Projekts
V5 hat extrem viel Zeit, Nerven und Kaffee gekostet. Wenn dir das System gefällt und du meine Arbeit unterstützen möchtest, freue ich mich riesig über einen virtuellen Kaffee!

<a href="https://www.paypal.me/babeinlovexd">
  <img src="https://img.shields.io/badge/Donate-PayPal-blue.svg?style=for-the-badge&logo=paypal" alt="Donate mit PayPal">
</a>

Jeder Cent fließt direkt in die Entwicklung von V6 und neue Prototypen! 🚀
---

## 👨‍💻 Entwickelt von

| [<img src="https://avatars.githubusercontent.com/u/43302033?v=4" width="100"><br><sub>**Christopher**</sub>](https://github.com/babeinlovexd) |
| :---: |

---





