/*
 * ======================================================================================
 * PROJECT: INSANE-BL V5 (Pure Bluetooth & UART)
 * COMPATIBILITY: ESP32 Core 3.x + ESP32-A2DP v1.8.3+
 * PINOUT: BCK=27, LRCK=25, DATA=26, STATUS=14, RX0=3, TX0=1
 * ======================================================================================
 */
String firmware_version = "5.5.6";
#include "BluetoothA2DPSink.h"
#include "ESP_I2S.h"

// Der Pin, der dem S3 (Mux) sagt, ob Musik läuft
#define STATUS_PIN 14

const uint8_t I2S_SCK = 27;
const uint8_t I2S_WS = 25;
const uint8_t I2S_SDOUT = 26;

I2SClass i2s;
BluetoothA2DPSink a2dp_sink(i2s);

// --- VARIABLEN FÜR AUTO-DISCONNECT ---
unsigned long pauseStartTime = 0;
bool isConnected = false;
bool isPlaying = false;
const unsigned long DISCONNECT_TIMEOUT = 300000; // 300.000 ms = 5 Minuten
// ------------------------------------------

// ======================================================================================
// 1. HARDWARE MUX TRIGGER & STATUS
// ======================================================================================
void play_status_callback(esp_avrc_playback_stat_t playback) {
  if (playback == ESP_AVRC_PLAYBACK_PLAYING) {
    digitalWrite(STATUS_PIN, HIGH);
    Serial.println("STATUS:PLAY"); 
    isPlaying = true; // Status merken
  } else {
    digitalWrite(STATUS_PIN, LOW);  
    Serial.println("STATUS:PAUSE");
    isPlaying = false; // Status merken
    pauseStartTime = millis(); // Timer starten bei Pause/Stop
  }
}

void connection_state_changed(esp_a2d_connection_state_t state, void *ptr) {
  if (state == ESP_A2D_CONNECTION_STATE_CONNECTED) {
    Serial.println("SYS_MSG: VERBUNDEN!");
    isConnected = true;  // Status merken
    isPlaying = false;   // Beim Verbinden spielt noch nichts
    pauseStartTime = millis(); // Timer starten, falls man sich verbindet aber nichts abspielt
  } else if (state == ESP_A2D_CONNECTION_STATE_DISCONNECTED) {
    Serial.println("SYS_MSG: GETRENNT.");
    digitalWrite(STATUS_PIN, LOW); 
    Serial.println("STATUS:OFFLINE");
    isConnected = false; // Status merken
    isPlaying = false;
  }
}

// ======================================================================================
// 2. METADATEN FÜR ESPHOME (Serial -> S3)
// ======================================================================================
void avrc_metadata_callback(uint8_t id, const uint8_t *text) {
  switch (id) {
    case ESP_AVRC_MD_ATTR_TITLE:  Serial.printf("TITLE:%s\n", text); break;
    case ESP_AVRC_MD_ATTR_ARTIST: Serial.printf("ARTIST:%s\n", text); break;
    case ESP_AVRC_MD_ATTR_ALBUM:  Serial.printf("ALBUM:%s\n", text); break;
    default: break;
  }
}
void volume_change_callback(int volume) {
  // Sendet die neue Lautstärke an den ESP32-S3 (ESPHome)
  Serial.printf("VOL:%d\n", volume);
}

// ======================================================================================
// MAIN SETUP & LOOP
// ======================================================================================
void setup() {
    // 115200 Baud ist zwingend nötig für ESPHome Kommunikation & das Flashen!
    Serial.begin(115200); 
    delay(200); // Kurz warten, bis der S3 (ESPHome) bereit ist
    Serial.print("VERSION:");
    Serial.println(firmware_version);

    pinMode(STATUS_PIN, OUTPUT);
    digitalWrite(STATUS_PIN, LOW);
    i2s.setPins(I2S_SCK, I2S_WS, I2S_SDOUT);
    if (!i2s.begin(I2S_MODE_STD, 44100, I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_STEREO, I2S_STD_SLOT_BOTH)) {
      Serial.println("SYS_MSG: Failed to initialize I2S!");
    }
    
    a2dp_sink.set_avrc_metadata_callback(avrc_metadata_callback);
    a2dp_sink.set_avrc_rn_playstatus_callback(play_status_callback);
    a2dp_sink.set_on_connection_state_changed(connection_state_changed);
    a2dp_sink.set_on_volumechange(volume_change_callback);

    // Startet sofort ohne WLAN-Wartezeit!
    a2dp_sink.start("INSANE-BL V5");
    Serial.println("SYS_MSG: Bluetooth gestartet und bereit.");
}

void loop() {
  // --- Auto-Disconnect Timer prüfen ---
  if (isConnected && !isPlaying) {
    if (millis() - pauseStartTime > DISCONNECT_TIMEOUT) {
      Serial.println("SYS_MSG: Auto-Disconnect wegen Inaktivität.");
      a2dp_sink.disconnect();
      isConnected = false; // Verhindert mehrfaches Auslösen, bis der Callback es bestätigt
    }
  }
  // -----------------------------------------

  // Empfängt Steuerbefehle vom S3 direkt über Serial (UART0)
  static String buffer = "";
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      String cmd = buffer;
      buffer = "";
      cmd.trim();
      if (cmd == "PLAY") a2dp_sink.play();
      else if (cmd == "PAUSE") a2dp_sink.pause();
      else if (cmd == "NEXT") a2dp_sink.next();
      else if (cmd == "PREV") a2dp_sink.previous();
      else if (cmd.startsWith("SET_VOL:")) {
        int vol = cmd.substring(8).toInt();
        a2dp_sink.set_volume(vol);
      }
    } else if (c != '\r') {
      buffer += c;
    }
  }
}
