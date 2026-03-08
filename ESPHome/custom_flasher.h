#pragma once
#include "esphome.h"
#include "bl_firmware.h" // Das ist deine konvertierte .bin Datei

namespace custom_flasher {

  void write_firmware(esphome::uart::UARTComponent *uart) {
    if (bl_firmware_bin_len == 0) {
      ESP_LOGE("FLASHER", "Fehler: Firmware-Array ist leer!");
      return;
    }

    ESP_LOGI("FLASHER", "Starte Firmware-Upload an WROOM (%d Bytes)...", bl_firmware_bin_len);

    // Blockgröße definieren (1024 Bytes pro Chunk ist ein guter Standard für den ESP32-UART)
    const int CHUNK_SIZE = 1024;
    int offset = 0;

    // Sende die Daten in kleinen Blöcken, damit der Puffer nicht überläuft
    while (offset < bl_firmware_bin_len) {
        int bytes_to_send = std::min((unsigned int)CHUNK_SIZE, bl_firmware_bin_len - offset);
        
        // Array-Block an den UART schreiben
        uart->write_array(&bl_firmware_bin[offset], bytes_to_send);
        
        offset += bytes_to_send;
        
        // Log-Ausgabe alle ~10% zur Kontrolle
        if (offset % (CHUNK_SIZE * 10) == 0 || offset == bl_firmware_bin_len) {
            ESP_LOGD("FLASHER", "Fortschritt: %d / %d Bytes", offset, bl_firmware_bin_len);
        }
        
        // WICHTIG: Kurze Pause, damit der Watchdog des S3 nicht resettet 
        // und der WROOM Zeit hat, die Daten in den internen Flash zu brennen
        delay(15); 
    }

    ESP_LOGI("FLASHER", "Upload abgeschlossen! Warte auf WROOM Reboot...");
  }
}