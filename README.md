<!DOCTYPE html>
<html lang="de">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Insane Sound System V4 - Dokumentation</title>
    <style>
        body {
            font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif;
            line-height: 1.6;
            max-width: 900px;
            margin: 0 auto;
            padding: 20px;
            color: #24292e;
            background-color: #ffffff;
        }
        h1, h2, h3 {
            border-bottom: 1px solid #eaecef;
            padding-bottom: 0.3em;
            margin-top: 24px;
        }
        h1 { font-size: 2em; }
        h2 { font-size: 1.5em; }
        table {
            width: 100%;
            border-collapse: collapse;
            margin-top: 15px;
            margin-bottom: 24px;
        }
        th, td {
            border: 1px solid #dfe2e5;
            padding: 8px 13px;
            text-align: left;
        }
        th { background-color: #f6f8fa; font-weight: 600; }
        tr:nth-child(even) { background-color: #fcfcfc; }
        code {
            background-color: #rgba(27,31,35,0.05);
            padding: 0.2em 0.4em;
            border-radius: 3px;
            font-family: "SFMono-Regular", Consolas, "Liberation Mono", Menlo, monospace;
            font-size: 85%;
        }
        .note {
            background-color: #fffbdd;
            border-left: 4px solid #e3ca12;
            padding: 15px;
            margin-bottom: 20px;
            border-radius: 0 4px 4px 0;
        }
        .warning {
            background-color: #ffeef0;
            border-left: 4px solid #d73a49;
            padding: 15px;
            margin-bottom: 20px;
            border-radius: 0 4px 4px 0;
        }
    </style>
</head>
<body>

    <h1>🚀 Insane Sound System (V4)</h1>
    <p>Willkommen beim <strong>Insane Sound System V4</strong>! Dies ist eine kompromisslose, WLAN- und Bluetooth-fähige Audio-Matrix auf Basis des ESP32-S3 und eines ESP32 D1 Mini. Es kombiniert High-Fidelity I2S-Audio, automatische Quellenumschaltung per Hardware-Multiplexer, einen Class-D Verstärker und 4-Zonen WS2811-LED-Steuerung auf einem einzigen, optimierten Custom-PCB.</p>

    <h2>📦 Verzeichnis-Inhalt</h2>
    <ul>
        <li><code>/Gerber/</code> - Die Produktionsdaten für die Platine (ZIP-Datei).</li>
        <li><code>/ESPHome/</code> - Die <code>.yaml</code> Konfigurationsdatei für das ESP32-S3 Mainboard.</li>
        <li><code>/Arduino/</code> - Der <code>.ino</code> Sketch für den Bluetooth-Empfänger (D1 Mini).</li>
    </ul>

    <h2>🛠️ Schritt 1: Die Platine fertigen lassen</h2>
    <p>Lade die ZIP-Datei aus dem Ordner <code>/Gerber/</code> bei einem Platinenfertiger deiner Wahl hoch (z. B. AliExpress oder JLCPCB). Das Board nutzt zwei Lagen (Top/Bottom). Alle Toleranzen sind Standard, du brauchst keine teuren Sonderfertigungs-Optionen wählen.</p>

    <h2>🛒 Schritt 2: Bauteile besorgen & Bestückung</h2>
    <p>Die nötigen SMD- und THT-Bauteile bekommst du problemlos und günstig bei Shops wie <strong>Amazon</strong> oder <strong>AliExpress</strong>.</p>
    
    <div class="note">
        <strong>Wichtige Löthinweise:</strong>
        <ol>
            <li><strong>Thermik:</strong> Achte darauf, dass das untere Pad (Exposed Pad) des TPA3110D2-Chips gut mit den Thermal-Vias auf der Platine verlötet ist.</li>
            <li><strong>GND-Jumper (H4):</strong> Schließe den Jumper an H4, um die saubere Elektronik-Masse mit der Power-Masse zu verbinden (Star-Ground Konzept für rauschfreien Sound).</li>
            <li><strong>Terminierung:</strong> Die 22-Ohm-Widerstände sitzen absichtlich extrem nah an den GPIOs der ESPs. Vergiss diese nicht, sie verhindern Audio-Verzerrungen auf dem I2S-Bus!</li>
        </ol>
    </div>

    <h2>💻 Schritt 3: Software 1 - Der Bluetooth-ESP (D1 Mini)</h2>
    <p>Der D1 Mini ist ausschließlich für den Bluetooth-Empfang zuständig und triggert die automatische Umschaltung.</p>
    <ol>
        <li>Öffne die <code>.ino</code> Datei in der <strong>Arduino IDE</strong>.</li>
        <li>Installiere über den Bibliotheksverwalter folgende Libraries: <code>ESP32-A2DP</code> (von pschatzmann) und <code>WiFiManager</code> (von tzapu).</li>
    </ol>
    
    <div class="warning">
        <strong>WICHTIG VOR DEM FLASHEN:</strong> Wenn der D1 Mini bereits auf die Hauptplatine gelötet ist, <strong>ziehe zwingend das 24V-Netzteil ab</strong>, bevor du das USB-Kabel einsteckst! (Schutz vor Spannungskollisionen).
    </div>
    
    <ol start="3">
        <li>Flashe den Code auf den ESP32 D1 Mini.</li>
        <li><strong>Erster Start:</strong> Der ESP spannt für 60 Sekunden ein WLAN namens <code>INSANE-SETUP</code> auf. Verbinde dich mit dem Handy und trage dein Heim-WLAN ein. Zukünftige Updates kannst du dann bequem kabellos per OTA (Over-The-Air) flashen!</li>
    </ol>

    <h2>🏠 Schritt 4: Software 2 - Das Mainboard (ESP32-S3 N16R8)</h2>
    <p>Der S3 steuert LEDs, Lüfter, Home Assistant Streams und den Hardware-Multiplexer.</p>
    <ol>
        <li>Binde den S3 in dein <strong>ESPHome</strong> Dashboard ein.</li>
        <li>Kopiere den kompletten Inhalt der beiliegenden <code>.yaml</code> Datei in deine ESPHome-Konfiguration.</li>
        <li>Passe oben im Code deine WLAN-Daten (<code>!secret</code>) an.</li>
        <li>Flashe das Board (z. B. initial über USB, danach via OTA).</li>
        <li><strong>Hinweis:</strong> Der Code aktiviert automatisch den 8MB Octal-PSRAM des S3. Der Audio-Puffer ist damit gigantisch und Streams laufen absolut ruckelfrei.</li>
    </ol>

    <h2>🔌 Schritt 5: Verkabelung & Erster Start</h2>
    <ol>
        <li>Verbinde deine Lautsprecher an den Schraubklemmen (<code>L+ / L-</code> und <code>R+ / R-</code>).</li>
        <li>Schließe deine 24V WS2811 LED-Streifen an die 4 Zonen-Ausgänge an.</li>
        <li><strong>Lüfter:</strong> Schließe deinen <strong>5V Gehäuselüfter</strong> an. Der Pluspol kommt an die 5V-Spannungsschiene, der Minuspol wird über den BC547B Transistor per PWM (GPIO 42) automatisch temperaturgesteuert.</li>
        <li><strong>Power On:</strong> Verbinde das 24V Netzteil.</li>
    </ol>
    <p><em>Standardmäßig ist das System im WLAN-Modus (Home Assistant). Sobald du dich mit dem Handy per Bluetooth verbindest und "Play" drückst, schaltet der Hardware-Multiplexer blitzschnell und knackfrei auf den Bluetooth-Stream um!</em></p>

    <hr>

    <h2>🛒 Stückliste (BOM - Bill of Materials)</h2>

    <h3>🧠 Mikrocontroller & Module</h3>
    <table>
        <tr><th>Bauteil / Bezeichnung</th><th>Menge</th><th>Beschreibung</th></tr>
        <tr><td><strong>ESP32-S3-DevKitC-1 N16R8</strong></td><td>1</td><td>Das Mainboard (Wichtig: Variante mit 16MB Flash und 8MB PSRAM!)</td></tr>
        <tr><td><strong>ESP32 D1 Mini BL</strong></td><td>1</td><td>Das Bluetooth-Empfängermodul</td></tr>
        <tr><td><strong>PCM5102A Modul</strong></td><td>1</td><td>High-Fidelity I2S Audio DAC</td></tr>
        <tr><td><strong>MP1584EN Modul</strong></td><td>1</td><td>Step-Down Konverter (Erzeugt 5V aus den 24V)</td></tr>
    </table>

    <h3>🎵 Audio & Logik-ICs (SMD)</h3>
    <table>
        <tr><th>Bauteil / Bezeichnung</th><th>Menge</th><th>Beschreibung</th></tr>
        <tr><td><strong>TPA3110D2PWP</strong></td><td>1</td><td>15W+15W Class-D Audio-Verstärker-Chip</td></tr>
        <tr><td><strong>SN74CB3Q3257PWR</strong></td><td>1</td><td>4-Kanal Hochgeschwindigkeits-Multiplexer (Der Switch!)</td></tr>
        <tr><td><strong>SN74AHCT125N</strong></td><td>1</td><td>Quad Level-Shifter (Macht aus 3.3V saubere 5V für die LEDs)</td></tr>
        <tr><td><strong>LM75AD</strong></td><td>3</td><td>I2C Temperatur-Sensoren für die Klima-Überwachung</td></tr>
    </table>

    <h3>⚡ Leistungselektronik & Kühlung</h3>
    <table>
        <tr><th>Bauteil / Bezeichnung</th><th>Menge</th><th>Beschreibung</th></tr>
        <tr><td><strong>BC547B</strong></td><td>1</td><td>NPN-Transistor (Für die PWM-Steuerung des 5V-Lüfters)</td></tr>
        <tr><td><strong>1N5822</strong></td><td>1</td><td>Schottky-Diode (Freilaufdiode zum Schutz des Transistors)</td></tr>
        <tr><td><strong>5V Gehäuselüfter</strong></td><td>1</td><td>Für die aktive Kühlung (Spannung über Step-Down)</td></tr>
        <tr><td><strong>Sicherungen (FUSE)</strong></td><td>5</td><td>RND 205-00232 SMD-Sicherungen (24V-Eingang und LED-Zonen)</td></tr>
    </table>

    <h3>🧲 Passive Bauteile (Kondensatoren & Spulen)</h3>
    <table>
        <tr><th>Bauteil / Bezeichnung</th><th>Menge</th><th>Beschreibung</th></tr>
        <tr><td><strong>1000µF / 50V Elko</strong></td><td>2</td><td>Pufferkondensatoren für die 24V Verstärker-Spannung</td></tr>
        <tr><td><strong>470µF / 50V Elko</strong></td><td>4</td><td>Pufferkondensatoren für die LED-Datenleitungen</td></tr>
        <tr><td><strong>12µH SMD-Spule</strong></td><td>4</td><td>Ausgangsfilter für den TPA3110 Verstärker</td></tr>
        <tr><td><strong>4.7µH SMD-Spule</strong></td><td>1</td><td>Für den Step-Down Schaltkreis</td></tr>
        <tr><td><strong>220nF Keramik</strong></td><td>4</td><td>Filter-Kondensatoren am Audio-Ausgang</td></tr>
        <tr><td><strong>100nF Keramik</strong></td><td>12+</td><td>Entkopplungskondensatoren (Über die Platine verteilt)</td></tr>
        <tr><td><strong>1µF Keramik</strong></td><td>4</td><td>Für den TPA3110 Audio-Eingang</td></tr>
    </table>

    <h3>🔌 Widerstände</h3>
    <table>
        <tr><th>Bauteil / Bezeichnung</th><th>Menge</th><th>Beschreibung</th></tr>
        <tr><td><strong>10kΩ SMD</strong></td><td>3+</td><td>Pull-Up / Pull-Down (z. B. Lüfter, Amp-Gain)</td></tr>
        <tr><td><strong>22Ω - 33Ω SMD</strong></td><td>6</td><td>I2S-Terminierung (An TX-Pins von S3 und D1 Mini anbringen!)</td></tr>
    </table>
	
	<h2>⚖️ Lizenz</h2>
	<p>
		Dieses komplette Projekt (Hardware und Software) steht unter der 
		<a href="https://creativecommons.org/licenses/by-nc-sa/4.0/" target="_blank" rel="noopener noreferrer">CC BY-NC-SA 4.0 Lizenz</a>.<br>
		Das bedeutet: Nachbauen und Anpassen für private Zwecke ist ausdrücklich erwünscht, jede kommerzielle Nutzung oder der Verkauf sind strikt verboten!
	</p>

</body>
</html>
