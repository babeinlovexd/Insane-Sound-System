/*
 * ======================================================================================
 * PROJECT: INSANE-BL V5 (Pure Bluetooth & UART)
 * COMPATIBILITY: ESP32 Core 3.x + ESP32-A2DP v1.8.3+
 * PINOUT: BCK=27, LRCK=25, DATA=26, STATUS=14, RX0=3, TX0=1
 * ======================================================================================
 */
String firmware_version = "5.4.0"; 
#include "BluetoothA2DPSink.h"
#include "driver/i2s_std.h"

// Der Pin, der dem S3 (Mux) sagt, ob Musik läuft
#define STATUS_PIN 14

BluetoothA2DPSink a2dp_sink;
i2s_chan_handle_t tx_handle = NULL; 

// ======================================================================================
// 1. HARDWARE MUX TRIGGER & STATUS
// ======================================================================================
void play_status_callback(esp_avrc_playback_stat_t playback) {
  if (playback == ESP_AVRC_PLAYBACK_PLAYING) {
    digitalWrite(STATUS_PIN, HIGH);
    Serial.println("STATUS:PLAY"); 
  } else {
    digitalWrite(STATUS_PIN, LOW);  
    Serial.println("STATUS:PAUSE");
  }
}

void connection_state_changed(esp_a2d_connection_state_t state, void *ptr) {
  if (state == ESP_A2D_CONNECTION_STATE_CONNECTED) {
    Serial.println("SYS_MSG: VERBUNDEN!");
  } else if (state == ESP_A2D_CONNECTION_STATE_DISCONNECTED) {
    Serial.println("SYS_MSG: GETRENNT.");
    digitalWrite(STATUS_PIN, LOW); 
    Serial.println("STATUS:OFFLINE");
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
// 3. I2S CORE 3.X SETUP (Audio zum Multiplexer)
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
            .bclk = (gpio_num_t)27, // BCK
            .ws   = (gpio_num_t)25, // LRCK
            .dout = (gpio_num_t)26, // DATA
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
    // 115200 Baud ist zwingend nötig für ESPHome Kommunikation & das Flashen!
    Serial.begin(115200); 
    Serial.print("VERSION:");
    Serial.println(firmware_version);

    pinMode(STATUS_PIN, OUTPUT);
    digitalWrite(STATUS_PIN, LOW); 

    setup_my_i2s();
    
    a2dp_sink.set_avrc_metadata_callback(avrc_metadata_callback);
    a2dp_sink.set_avrc_rn_playstatus_callback(play_status_callback);
    a2dp_sink.set_on_connection_state_changed(connection_state_changed);
    a2dp_sink.set_stream_reader(audio_data_callback, false);
    a2dp_sink.set_on_volumechange(volume_change_callback);

    // Startet sofort ohne WLAN-Wartezeit!
    a2dp_sink.start("INSANE-BL V5");
    Serial.println("SYS_MSG: Bluetooth gestartet und bereit.");
}

void loop() {
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