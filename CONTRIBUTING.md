# 🛠️ Contributing to Insane Sound System V5

Erstmal: Danke, dass du überlegst, zu diesem Projekt beizutragen! Nach unzähligen Stunden Schweiß und Tränen bei der Entwicklung der V5 freuen wir uns über jeden, der hilft, dieses System noch brachialer zu machen. Egal ob du einen Bug im ESPHome-Code findest, eine geniale neue Funktion vorschlägst oder das Platinen-Layout verbessern willst – jede Hilfe ist willkommen.

Damit wir dieses Projekt übersichtlich und auf dem "Insane-Level" halten können, beachte bitte die folgenden Richtlinien.

## 🐛 Bugs und Fehler melden (Issues)
Wenn du einen Fehler findest (z. B. das Board stürzt ab, der Lüfter regelt falsch oder der OTA-Flasher hakt), nutze bitte den **Issues**-Reiter. 
* **Prüfe vorher:** Gibt es das Issue vielleicht schon?
* **Sei präzise:** Beschreibe genau, was passiert ist. Nutzt du den ESP32-S3? Welche Version der ESPHome-Firmware läuft bei dir? Welches Netzteil verwendest du? 
* **Logs:** Füge bei Software-Problemen immer die entsprechenden Log-Ausgaben (aus ESPHome oder dem Updater-Tool) bei.

## 💡 Neue Ideen und Feature-Requests
Du hast eine Idee für eine Erweiterung (z. B. zusätzliche Sensoren, neue LED-Effekte oder eine Erweiterungsplatine)?
* Bitte öffne dafür **kein** Issue! 
* Nutze stattdessen unsere **GitHub Discussions**. Dort können wir in der Community darüber brainstormen, ob und wie wir das Feature in das Board integrieren können, bevor jemand stundenlang Code schreibt.

## 🚀 Pull Requests (PRs) einreichen
Wenn du Code oder Hardware-Dateien verändert hast und diese Änderungen in das Hauptprojekt integrieren möchtest, stelle einen Pull Request. 

### Für Software (ESPHome / Arduino / Updater):
1. **Teste deinen Code:** Reiche nichts ein, was du nicht selbst auf der echten V5-Platine live getestet hast.
2. **Dual-Chip Logik beachten:** Änderungen am Hauptcode (S3) dürfen die Kommunikation zum Bluetooth-Chip (WROOM) über die UART-Schnittstelle nicht unterbrechen.
3. **Bleib sauber:** Halte dich an den bestehenden Code-Stil (Einrückungen in YAML, saubere Kommentare). Erkläre im PR genau, welches Problem dein Code löst.

### Für Hardware (Gerber / EasyEDA / KiCad):
Wir haben extrem viel Arbeit in das perfekte Layout der V5 gesteckt. Änderungen an der Platine müssen folgende **Hard-Rules** erfüllen:
1. **SMD-Größe:** Die kleinsten Bauteile müssen **strikt Größe 1206** bleiben. Alles, was kleiner ist, wird abgelehnt, da das Board handlötfreundlich bleiben muss.
2. **Board-Maße:** Das Layout darf die Grenze von **100x100mm** nicht überschreiten, um die Fertigungskosten für die Community niedrig zu halten.
3. **Power-Routing:** Die Leiterbahnen für die 24V-Versorgung und die LED-Zonen müssen für hohe Ströme ausgelegt bleiben (mind. 2mm Breite für LED-Power).
4. **Verfügbarkeit:** Neue Bauteile auf der BOM müssen massentauglich und leicht bei den Großen Shops bestellbar sein.

Vielen Dank für deine Zeit und dein Engagement! Lass uns die V5 gemeinsam zum besten DIY-Lautsprechersystem der Welt machen! 🎧🔥
