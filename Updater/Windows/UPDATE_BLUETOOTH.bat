@echo off
cd /d "%~dp0"

chcp 65001 >nul
color 0b
title Insane Sound System V5 - Bluetooth Auto-Flasher

echo.
echo    ██ ███   ██  ██████  █████  ███   ██ ███████ 
echo    ██ ████  ██ ██      ██   ██ ████  ██ ██      
echo    ██ ██ ██ ██  █████  ███████ ██ ██ ██ █████   ━━━━
echo    ██ ██  ████      ██ ██   ██ ██  ████ ██      
echo    ██ ██   ███ ██████  ██   ██ ██   ███ ███████
echo.
echo        ISS  BLUETOOTH V5 AUTO-FLASHER TOOL
echo =======================================================
echo.

set "FIRMWARE_FILE="
:: Suche zuerst lokal nach irgendeiner *.merged.bin
for %%f in (*merged.bin) do (
    set "FIRMWARE_FILE=%%f"
    goto :FileFound
)

:FileFound
if "%FIRMWARE_FILE%"=="" (
    echo [INFO] Keine lokale Firmware-Datei gefunden.
    echo.
    choice /C JN /M "Die Firmware wird benötigt. Möchtest du sie jetzt von GitHub herunterladen?"
    if errorlevel 2 (
        echo.
        echo [ABBRUCH] Ohne Firmware kann der Flash-Vorgang nicht gestartet werden.
        pause
        exit /b
    )
    
    echo.
    echo [INFO] Suche auf GitHub nach Updates...
    
    :: Nutzt PowerShell mit User-Agent, um die GitHub-API nach *.merged.bin zu durchsuchen
    powershell -NoProfile -Command "$ErrorActionPreference = 'Stop'; $ua = 'Mozilla/5.0'; $repoUrl = 'https://api.github.com/repos/babeinlovexd/insane-sound-system/contents/Firmware?ref=V5-dev'; try { $files = Invoke-RestMethod -Uri $repoUrl -UserAgent $ua; $target = $files | Where-Object { $_.name -like '*merged.bin' } | Select-Object -First 1; if ($target) { Write-Host ('[OK] Gefunden auf GitHub: ' + $target.name); Invoke-WebRequest -Uri $target.download_url -OutFile $target.name -UserAgent $ua; $target.name | Out-File -FilePath 'temp_name.txt' -Encoding ascii; } else { exit 1 } } catch { exit 1 }"

    if errorlevel 1 (
        color 0c
        echo.
        echo [FEHLER] Konnte keine Firmware auf GitHub oder lokal finden!
        pause
        exit /b
    )
    
    :: Den gefundenen Namen einlesen
    set /p FIRMWARE_FILE=<temp_name.txt
    del temp_name.txt
)

echo [INFO] Firmware-Datei gefunden: %FIRMWARE_FILE%
echo.

if not exist "esptool.exe" (
    echo [INFO] Flasher-Engine esptool.exe nicht gefunden.
    echo.
    choice /C JN /M "Das Flasher-Tool wird benötigt. Möchtest du es jetzt herunterladen?"
    if errorlevel 2 (
        echo.
        echo [ABBRUCH] Ohne Flasher-Engine kann nicht geflasht werden.
        pause
        exit /b
    )
    
    echo.
    echo [INFO] Lade stabile Version direkt herunter...
    echo Bitte einen Moment Geduld...
    
    powershell -NoProfile -Command "$ErrorActionPreference = 'Stop'; [Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12; try { Invoke-WebRequest -Uri 'https://github.com/espressif/esptool/releases/download/v4.8.1/esptool-v4.8.1-win64.zip' -OutFile 'esptool.zip'; Expand-Archive -Path 'esptool.zip' -DestinationPath 'temp_esptool' -Force; Move-Item -Path 'temp_esptool\*\esptool.exe' -Destination '.\esptool.exe' -Force; Remove-Item -Recurse -Force 'temp_esptool'; Remove-Item -Force 'esptool.zip'; Write-Host '[OK] Download erfolgreich!' -ForegroundColor Green } catch { Write-Host '[FEHLER] Download fehlgeschlagen: ' $_.Exception.Message -ForegroundColor Red; exit 1 }"
    
    if errorlevel 1 (
        color 0c
        echo.
        echo [FEHLER] Konnte esptool.exe nicht herunterladen!
        echo Bitte prüfe deine Internetverbindung.
        pause
        exit /b
    )
    echo.
)


echo SCHRITT 1: VORBEREITUNG
echo 1. Gehe in dein Home Assistant.
echo 2. Öffne das Dashboard für dein Insane Sound System.
echo 3. Drücke dort den Button "WROOM in Flash-Modus setzen".
echo.
pause
echo.

echo SCHRITT 2: VERBINDUNG
set /p ip="Gib die IP-Adresse deines Insane Sound Systems ein z.B. 192.168.178.50 : "
echo.

set MAX_TRIES=3
set TRY_COUNT=0

:PingLoop
set /a TRY_COUNT+=1
echo [INFO] Prüfe Verbindung zu %ip% (Versuch %TRY_COUNT%/%MAX_TRIES%)...
ping -n 1 -w 2000 %ip% >nul
if not errorlevel 1 goto PingSuccess

if %TRY_COUNT% LSS %MAX_TRIES% (
    echo [WARNUNG] Keine Antwort vom Board. Neuer Versuch in 2 Sekunden...
    timeout /t 2 >nul
    goto PingLoop
)

color 0c
echo.
echo [FEHLER] Das Board unter %ip% antwortet nach %MAX_TRIES% Versuchen nicht!
echo Ist das Insane Sound System eingeschaltet und im selben WLAN?
echo.
pause
exit /b

:PingSuccess
echo [OK] Verbindung erfolgreich hergestellt!
echo.

echo =======================================================
echo VERBINDE MIT %ip% UND FLASHE BLUETOOTH-MODUL...
echo /!\ BITTE DAS SYSTEM JETZT NICHT VOM STROM TRENNEN /!\
echo =======================================================
echo.

esptool.exe --port socket://%ip%:8888 write_flash 0x0 "%FIRMWARE_FILE%"

if errorlevel 1 (
    color 0c
    echo.
    echo =======================================================
    echo [FEHLER] Der Flash-Vorgang ist fehlgeschlagen!
    echo Hast du den Button "WROOM in Flash-Modus setzen" gedrueckt?
    echo =======================================================
    pause
    exit /b
)


color 0a
echo.
echo =======================================================
echo                      BÄÄÄM! FERTIG! 
echo =======================================================
echo Dein Insane Sound System hat jetzt die Faehigkeit "Bluetooth" :)
echo.
echo Bitte trenne das Insane Sound System jetzt für 5 Sekunden vom Strom 
echo und stecke es danach wieder ein.
echo =======================================================
pause