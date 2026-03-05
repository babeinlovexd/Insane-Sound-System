# 🛠️ Contributing to Insane Sound System V4

Erstmal: Danke, dass du überlegst, zu diesem Projekt beizutragen! Egal ob du einen Bug im ESPHome-Code gefunden hast, eine geniale neue Funktion vorschlagen möchtest oder das Platinen-Layout für die V5 verbessern willst – jede Hilfe ist willkommen.

Damit wir dieses Projekt übersichtlich und auf einem hohen Qualitätsstandard (Insane-Level!) halten können, beachte bitte die folgenden Richtlinien.

## 🐛 Bugs und Fehler melden (Issues)
Wenn du einen Fehler findest (z. B. das Board stürzt ab, der Lüfter dreht nicht), nutze bitte den **Issues**-Reiter. 
* **Prüfe vorher:** Gibt es das Issue vielleicht schon?
* **Sei präzise:** Beschreibe genau, was passiert ist. Nutzt du den ESP32-S3 N16R8? Welche Version der ESPHome-Firmware läuft bei dir? Welches Netzteil verwendest du?
* **Logs:** Füge bei Software-Problemen immer die entsprechenden Log-Ausgaben (aus ESPHome oder Arduino IDE) bei.

## 💡 Neue Ideen und Feature-Requests
Du hast eine Idee für eine Erweiterung (z. B. I2C-Display, Drehregler, Zigbee-Integration)?
* Bitte öffne dafür **kein** Issue! 
* Nutze stattdessen unsere **GitHub Discussions**. Dort können wir in der Community darüber brainstormen, ob und wie wir das Feature in das Board integrieren können, bevor jemand stundenlang Code schreibt.

## 🚀 Pull Requests (PRs) einreichen
Wenn du Code oder Hardware-Dateien verändert hast und diese Änderungen in das Hauptprojekt integrieren möchtest, stelle einen Pull Request. 

### Für Software (ESPHome / Arduino):
1. **Teste deinen Code:** Reiche nichts ein, was du nicht selbst auf der V4-Platine live getestet hast.
2. **Bleib sauber:** Halte dich an den bestehenden Code-Stil (Einrückungen in YAML, saubere Kommentare im `.ino` Sketch).
3. **Erkläre das "Warum":** Beschreibe in deinem PR genau, *welches* Problem dein Code löst oder *welches* neue Feature er bringt.

### Für Hardware (Gerber / KiCad / EasyEDA):
1. **Keine "blinden" Änderungen:** Wenn du Leiterbahnen verschiebst oder Komponenten austauschst, erkläre genau, warum das elektrotechnisch sinnvoll ist (z. B. "Bessere Wärmeabfuhr", "Geringere I2S-Interferenzen").
2. **Verfügbarkeit:** Wenn du neue Bauteile auf die BOM (Stückliste) setzt, achte darauf, dass diese weiterhin massentauglich und leicht z. B. bei AliExpress oder Amazon bestellbar sind.
3. **Sicherheit geht vor:** Änderungen am 24V-Power-Routing werden extrem streng geprüft. Die 2mm Leiterbahnbreite für die LEDs darf nicht unterschritten werden.

Vielen Dank für deine Zeit und dein Engagement! 🎧🔥
