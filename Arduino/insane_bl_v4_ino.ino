/*
 * ======================================================================================
 * PROJECT: INSANE-BL V4 (Hardware Mux, UART, OTA & WiFiManager)
 * COMPATIBILITY: ESP32 Core 3.x + ESP32-A2DP v1.8.3+
 * PINOUT: BCK=27, LRCK=25, DATA=26, STATUS=14, RX2=16, TX2=17
 * ======================================================================================
 */

#include "BluetoothA2DPSink.h"
#include "driver/i2s_std.h"
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <WiFiManager.h> 

#define STATUS_PIN 14
#define RX2_PIN 16
#define TX2_PIN 17

BluetoothA2DPSink a2dp_sink;
i2s_chan_handle_t tx_handle = NULL; 

// ======================================================================================
// 1. HARDWARE MUX TRIGGER
// ======================================================================================
void play_status_callback(esp_avrc_playback_stat_t playback) {
  if (playback == ESP_AVRC_PLAYBACK_PLAYING) {
    digitalWrite(STATUS_PIN, HIGH); 
    Serial2.println("STATUS:PLAY"); 
    Serial.println("STATUS: Mux auf BL geschaltet (HIGH)");
  } else {
    digitalWrite(STATUS_PIN, LOW);  
    Serial2.println("STATUS:PAUSE");
    Serial.println("STATUS: Mux auf WLAN geschaltet (LOW)");
  }
}

void connection_state_changed(esp_a2d_connection_state_t state, void *ptr) {
  if (state == ESP_A2D_CONNECTION_STATE_CONNECTED) {
    Serial.println("✅ VERBUNDEN!");
  } else if (state == ESP_A2D_CONNECTION_STATE_DISCONNECTED) {
    Serial.println("❌ GETRENNT.");
    digitalWrite(STATUS_PIN, LOW); 
    Serial2.println("STATUS:OFFLINE");
  }
}

// ======================================================================================
// 2. METADATEN FÜR ESPHOME (Serial2)
// ======================================================================================
void avrc_metadata_callback(uint8_t id, const uint8_t *text) {
  switch (id) {
    case ESP_AVRC_MD_ATTR_TITLE:  Serial2.printf("TITLE:%s\n", text); break;
    case ESP_AVRC_MD_ATTR_ARTIST: Serial2.printf("ARTIST:%s\n", text); break;
    case ESP_AVRC_MD_ATTR_ALBUM:  Serial2.printf("ALBUM:%s\n", text); break;
    default: break;
  }
}

// ======================================================================================
// 3. I2S CORE 3.X SETUP 
// ======================================================================================
void setup_my_i2s() {
    i2s_chan_config_t chan_cfg = {
        .id = I2S_NUM_0,
        .role = I2S_ROLE_MASTER,
        .dma_desc_num = 6,
        .dma_frame_num = 240,
        .auto_clear = true
    };
    i2s_new_channel(&chan_cfg, &tx_handle, NULL);

    i2s_std_config_t std_cfg = {
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(44100),
        .slot_cfg = I2S_STD_MSB_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_STEREO),
        .gpio_cfg = {
            .mclk = I2S_GPIO_UNUSED,
            .bclk = GPIO_NUM_27, // BCK
            .ws   = GPIO_NUM_25, // LRCK
            .dout = GPIO_NUM_26, // DATA
            .din  = I2S_GPIO_UNUSED,
            .invert_flags = { .mclk_inv = false, .bclk_inv = false, .ws_inv = false }
        },
    };
    i2s_channel_init_std_mode(tx_handle, &std_cfg); 
    i2s_channel_enable(tx_handle);
}

void audio_data_callback(const uint8_t *data, uint32_t length) {
    size_t bytes_written;
    if (tx_handle) {
        i2s_channel_write(tx_handle, data, length, &bytes_written, portMAX_DELAY);
    }
}

// ======================================================================================
// MAIN SETUP & LOOP
// ======================================================================================
void setup() {
    Serial.begin(115200); 
    Serial2.begin(9600, SERIAL_8N1, RX2_PIN, TX2_PIN); 

    pinMode(STATUS_PIN, OUTPUT);
    digitalWrite(STATUS_PIN, LOW); 

    // --- WIFI MANAGER SETUP ---
    WiFiManager wifiManager;
    
    // Wichtig: Timeout setzen! Wenn du 60 Sekunden lang keine WLAN-Daten eingibst,
    // beendet er das Setup und startet einfach normal mit Bluetooth weiter.
    wifiManager.setConfigPortalTimeout(60);
    
    Serial.println("Prüfe WLAN / Starte Setup-Portal...");
    
    // Erstellt den Hotspot "INSANE-SETUP", falls das alte WLAN weg ist
    if (!wifiManager.autoConnect("INSANE-SETUP")) {
      Serial.println("WLAN Setup Timeout! Starte System nur mit Bluetooth.");
    } else {
      Serial.println("\nWLAN verbunden! IP: " + WiFi.localIP().toString());
      ArduinoOTA.setHostname("INSANE-BL-V4");
      ArduinoOTA.begin();
      Serial.println("OTA Update-Service gestartet.");
    }

    // --- AUDIO SETUP ---
    setup_my_i2s();
    
    a2dp_sink.set_avrc_metadata_callback(avrc_metadata_callback);
    a2dp_sink.set_avrc_rn_playstatus_callback(play_status_callback);
    a2dp_sink.set_on_connection_state_changed(connection_state_changed);
    a2dp_sink.set_stream_reader(audio_data_callback, false);

    a2dp_sink.start("INSANE-BL V4");
    Serial.println("Bluetooth System bereit...");
}

void loop() {
  // OTA Updates verarbeiten, falls WLAN verbunden ist
  if (WiFi.status() == WL_CONNECTED) {
    ArduinoOTA.handle();
  }

  // Empfängt Steuerbefehle vom S3
  if (Serial2.available()) {
    String cmd = Serial2.readStringUntil('\n');
    cmd.trim(); 

    if (cmd == "PLAY") a2dp_sink.play();
    else if (cmd == "PAUSE") a2dp_sink.pause();
    else if (cmd == "NEXT") a2dp_sink.next();
    else if (cmd == "PREV") a2dp_sink.previous();
    else if (cmd.startsWith("SET_VOL:")) {
      int vol = cmd.substring(8).toInt();
      a2dp_sink.set_volume(vol);
      Serial.printf("S3 hat Volume auf %d gesetzt\n", vol);
    }
  }
  delay(10); 
}