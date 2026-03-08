import os

# Namen der Dateien
input_file = "bl_firmware.bin"
output_file = "bl_firmware.h"

print(f"Lese {input_file} ein...")

try:
    with open(input_file, "rb") as f:
        data = f.read()

    print("Schreibe C-Array... Bitte warten (kann ein paar Sekunden dauern).")
    
    with open(output_file, "w") as f:
        f.write("const unsigned char bl_firmware_bin[] = {\n")
        
        # Wandelt die Bytes in Hex um und schreibt 16 Stück pro Zeile
        hex_array = [f"0x{b:02x}" for b in data]
        for i in range(0, len(hex_array), 16):
            f.write("  " + ", ".join(hex_array[i:i+16]) + ",\n")
            
        f.write("};\n")
        f.write(f"const unsigned int bl_firmware_bin_len = {len(data)};\n")

    print(f"BÄM! {output_file} wurde perfekt erstellt!")
    print(f"Dateigröße: {len(data)} Bytes.")

except FileNotFoundError:
    print(f"Fehler: Die Datei {input_file} wurde in diesem Ordner nicht gefunden.")