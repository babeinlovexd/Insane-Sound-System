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
for %%f in (*merged.bin) do (
    set "FIRMWARE_FILE=%%f"
    goto :FileFound
)

:FileFound
if "%FIRMWARE_FILE%"=="" (
    color 0c
    echo [FEHLER] Keine '.merged.bin' Datei gefunden!
    echo Bitte lege die kompilierte Firmware in denselben Ordner wie dieses Skript.
    echo.
    echo INFO: Aktueller Such-Ordner ist: %CD%
    echo.
    pause
    exit /b
)

echo [INFO] Firmware-Datei gefunden: %FIRMWARE_FILE%
echo.

if not exist "esptool.exe" (
    echo [INFO] Flasher-Engine esptool.exe nicht gefunden.
    echo [INFO] Lade stabile Version v4.8.1 direkt herunter...
    echo Bitte einen Moment Geduld...
    
    powershell -NoProfile -Command "$ErrorActionPreference = 'Stop'; [Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12; try { Invoke-WebRequest -Uri 'https://github.com/espressif/esptool/releases/download/v4.8.1/esptool-v4.8.1-win64.zip' -OutFile 'esptool.zip'; Expand-Archive -Path 'esptool.zip' -DestinationPath 'temp_esptool' -Force; Move-Item -Path 'temp_esptool\*\esptool.exe' -Destination '.\esptool.exe' -Force; Remove-Item -Recurse -Force 'temp_esptool'; Remove-Item -Force 'esptool.zip'; Write-Host '[OK] Download erfolgreich!' -ForegroundColor Green } catch { Write-Host '[FEHLER] Download fehlgeschlagen: ' $_.Exception.Message -ForegroundColor Red; exit 1 }"
    
    if errorlevel 1 (
        color 0c
        echo.
        echo [FEHLER] Konnte esptool.exe nicht herunterladen! 
        echo Bitte pruefe deine Internetverbindung.
        pause
        exit /b
    )
    echo.
)


echo SCHRITT 1: VORBEREITUNG
echo 1. Gehe in dein Home Assistant.
echo 2. Oeffne das Dashboard fuer dein Insane Sound System.
echo 3. Druecke dort den Button "WROOM in Flash-Modus setzen".
echo.
pause
echo.


echo SCHRITT 2: VERBINDUNG
set /p ip="Gib die IP-Adresse deines Insane Sound Systems ein (z.B. 192.168.178.50): "
echo.

echo [INFO] Pruefe Verbindung zu %ip%...
ping -n 1 -w 2000 %ip% >nul
if errorlevel 1 (
    color 0c
    echo [FEHLER] Das Board unter %ip% antwortet nicht!
    echo Ist das Insane Sound System eingeschaltet und im selben WLAN?
    echo.
    pause
    exit /b
)


echo.
echo =======================================================
echo VERBINDE MIT %ip% UND FLASHE BLUETOOTH-MODUL...
echo /!\ BITTE DAS INSANE SOUND SYSTEM JETZT NICHT VOM STROM TRENNEN /!\
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
echo Bitte trenne die Box jetzt fuer 5 Sekunden vom Strom 
echo und stecke sie danach wieder ein.
echo =======================================================
pause