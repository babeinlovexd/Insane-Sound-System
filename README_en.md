# 🔊 Insane Sound System V5
<div align="center">
  <img src="https://img.shields.io/github/v/release/babeinlovexd/Insane-Sound-System?style=for-the-badge&color=2ecc71" alt="Latest Release">
  <img src="https://img.shields.io/badge/Status-Stable-2ecc71?style=for-the-badge" alt="Status">
  <img src="https://img.shields.io/badge/ESPHome-Ready-03A9F4?style=for-the-badge&logo=esphome" alt="ESPHome">
  <img src="https://img.shields.io/badge/Hardware-V5.4-f39c12?style=for-the-badge&logo=pcb" alt="Hardware Version">
  <img src="https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-lightgrey?style=for-the-badge&logo=creative-commons" alt="License: CC BY-NC-SA 4.0">
</div>
<br>

🌍 **[Lies das auf Deutsch](README.md)**

Welcome to the **Insane Sound System V5**, the ultimate, smart high-end Wi-Fi & Bluetooth speaker controller!

Months of development, countless prototypes, sweat, tears, and the relentless desire to create the absolute perfect audio hub went into this PCB. The **Insane Sound System V5** is the ultimate result of this madness.

**What is the Insane Sound System anyway?**
It's not just an amplifier board. It is the uncompromising, smart centerpiece for your self-built high-end audio box. It combines audiophile hardware with the infinite flexibility of smart homes, giving you absolute control over sound, light, and hardware - all on a tiny, professional 100x100mm PCB.

### 🔥 What can this thing do?
This board is armed to the teeth with features:
* **Seamless Dual Audio Sources:** Stream music via Wi-Fi (Home Assistant/ESPHome) or connect your phone directly via Bluetooth. A dedicated hardware multiplexer switches losslessly and completely pop-free between the audio sources.
* **Bluetooth with Metadata:** The Bluetooth chip not only streams music but also sends the title, artist, album, and play/pause status straight to your smart home dashboard.
* **Insane Turbo Mode:** Too quiet? A digitally switchable gain boost on the hardware level extracts maximum volume from the TPA3110 amplifier.
* **3-Zone RGB Lightshow:** Control up to three separate 24V WS28xx LED strips straight from the board (with built-in level shifters for clean 5V data signals). Including effects like "Knight Rider", "Fireworks", or "Rainbow".
* **Smart Thermal Management:** Three independent temperature sensors (I2C) monitor the amplifier, voltage regulators, and case temperature. If it gets hot, the system steplessly turns up a 5V PWM case fan. If there's a risk of heat death, the automatic emergency shutdown kicks in.
* **Fully Automatic Power Saving Logic:** The amplifier and DAC are put into standby (mute) on the hardware side when no music is playing. No background noise, no unnecessary power consumption.
* **Over-The-Air (OTA) Updates for ALL Chips:** Flash not only the main system via Wi-Fi but also – thanks to our custom InsaneFlasher – the separated Bluetooth chip completely wirelessly over the network!

This version was developed entirely from scratch. The goal: Maximum audio performance, foolproof operation, and a hardware design that can be professionally manufactured while still being completely relaxed to assemble at home.

<img src="Images/3.png" width="400" alt="Insane Sound System V5 - 3D Render">

## ✨ What's new in V5? (Hardware & Features)

We didn't do things by halves. V5 brings massive under-the-hood upgrades:

* **Compact 100x100mm Design:** The PCB fits in almost any enclosure and stays just under the magic limit to be ordered extremely cheaply from PCB manufacturers. Better thermals and optimal routing in the smallest of spaces!
* **Hand-soldering friendly SMD Design:** The board consists of 90% SMD components for shorter, cleaner signal paths and a modern design. **Don't panic:** The smallest components are strictly limited to **size 1206**! You don't need a microscope or steady surgeon hands; everything can be soldered completely relaxed by hand.
* **Dual-Brain Architecture:** A modern ESP32-S3 serves as the main brain controlling Home Assistant, Wi-Fi, and LEDs. A dedicated ESP32-WROOM-32E cares *exclusively* about lossless Bluetooth audio.
* **Real Hardware Multiplexer:** The SN74CB3Q3257 chip switches the I2S audio signal lightning-fast and without annoying pops between Wi-Fi (S3) and Bluetooth (WROOM).
* **Smart Temperature Management:** Three LM75A sensors monitor the amplifier (TPA3110), the voltage regulators, and the ESP32 environment. A 5V case fan is steplessly controlled via PWM as soon as it gets warm in the case.
* **Over-The-Air Bluetooth Updates:** The WROOM module can now be flashed completely wirelessly via Wi-Fi. No USB cable, no screwing - just at the push of a button in the dashboard!

  > **💡 Note on Audio Architecture:** The Insane Sound System v5.2 now uses the cutting-edge, modular `platform: speaker` audio pipeline of ESPHome (compatible with ESPHome 2026.3.0+). Your ESP32 benefits from native transcoding, meaning Home Assistant (from 2024.10+) efficiently streams the audio, taking the computational load off the microcontroller. This ensures much more stable streams, making it the perfect partner for Music Assistant!

<img src="Images/2.svg" width="400" alt="PCB Layout 2D View">

---

## 🛒 Shopping List & Components (BOM)

You can find the complete and detailed list of all required components in the `BOM/` folder (as file `BOM_insane-sound-system-v5_xxxx-xx-xx.csv`).

Almost all standard components (like the 1206 resistors, capacitors, ESP modules, and the amplifier chip) can easily be ordered in many shops.

---

## 🛠️ Step-by-Step Guide

Anyone can build this system. Just stubbornly follow these steps:

### Step 1: Solder Hardware
1. Order the PCB using the Gerber files in the `Gerber/` folder.
2. Solder the SMD components (size 1206) first. Start with the flat components (resistors, capacitors) and work your way up to the larger chips.
3. **IMPORTANT:** Solder the large ground pad (Exposed Pad / EP) on the bottom of the ESP32-WROOM to the PCB without fail! This is not only important for grounding but also acts as an essential heatsink. Without this connection, the chip will overheat.

### 🛠️ Assembly Aid
Here you can find the interactive Bill of Materials (iBOM) for the Insane Sound System:
<a href="https://htmlpreview.github.io/?https://github.com/babeinlovexd/Insane-Sound-System/blob/main/BOM/PCB_insane%20sound%20system%20v5.1_rev0.html">👉 <b>Interactive Assembly Aid</b></a>

### Step 2: Prepare ESPHome (Mainboard S3)
For security reasons, this project uses externalized passwords.
1. Create a new file called `secrets.yaml` in your Home Assistant / ESPHome folder.
2. Insert exactly this structure with your own, real data:
   ```yaml
   api_encryption_key: "YOUR_API_KEY"
   ota_password: "YOUR_OTA_PASSWORD"
   wifi_ssid: "YOUR_WIFI_NAME"
   wifi_password: "YOUR_WIFI_PASSWORD"
   ap_password: "YOUR_FALLBACK_HOTSPOT_PASSWORD"
   web_server_username: "YOUR_WEB_SERVER_USERNAME"
   web_server_password: "YOUR_WEB_SERVER_PASSWORD"
   ```
3. Upload the file `insane-sound-system-v5.yaml` from the `ESPHome/` folder to your ESPHome dashboard.
4. The Web-Interface Design (`insane-style.css`): The project comes with a custom design for the local web interface. You will find the required file in the downloaded project files in the `webserver/` folder.
   * **Important:** This CSS file must absolutely be copied into exactly the same folder on your server where your `.yaml` file is located (usually `/config/esphome/` or `/homeassistant/esphome/`).
   * **How do I do that?** Since the standard ESPHome dashboard doesn't offer a direct file upload for CSS files, it is best to use an add-on like the **"File editor"**, **"Studio Code Server"**, or a **"Filebrowser"** in Home Assistant. Simply navigate to your ESPHome folder there and upload the `insane-style.css` right next to the `insane-sound-system-v5.yaml`. Only then will the compiler correctly embed the design when flashing!
5. **Activate LEDs and Front Panel (Packages):** In the `insane-sound-system-v5.yaml` file, near the top under `packages:`, you will find configuration blocks for different LED strips (WS2811, WS2814, WS2805) and the optional Front Panel.
   * **LEDs:** Highlight the block corresponding to the LED type you are using and remove the hash (`#`) symbols at the beginning of the lines (Tip: Select the block and press `Ctrl` + `#`). **Only one** LED block can be active at a time!
   * **Front Panel (Optional):** If you are using the front panel extension (OLED & Buttons), remove the hash symbols in the same way before `frontpanel:`, `url:` and `file:`.
6. Connect the **ESP32-S3** to your computer via USB and flash it normally via the cable for the very first time.

<img src="Images/1.svg" width="300" alt="Detailed View Bottom">

## 🚀 The official InsaneFlasher Tool (All-in-One)

No more complicated command lines! The Insane Sound System V5 now comes with its own, professional hub for **Windows, macOS, and Linux**.

The **InsaneFlasher** is your central dashboard to control, monitor, and maintain your Insane Sound System. Thanks to ZeroConf technology, the tool automatically finds your Insane Sound System on the network.

### ✨ Features of the Tool
* **Live Telemetry Dashboard:** Monitor temperatures (incl. dynamic warning bars!), audio sources, Wi-Fi signal, and running Bluetooth metadata in real-time (1-second intervals).
* **One-Click OTA Flashing:** Update the internal Bluetooth chip (WROOM) completely wirelessly. The main ESP32 (S3) acts as an invisible bridge (`socket://<IP>:8888`) and flashes the WROOM via its hardware pins - no USB cable required!
* **Automatic Version Check:** The tool automatically compares the WROOM firmware of your box with GitHub and notifies you as soon as an update is available.
* **Favorites Storage:** Save your fixed Insane Sound Systems to skip the network scan on the next start.
* **Hardware Reset:** Force a clean reboot of the WROOM chip via remote maintenance in case the Bluetooth hangs up.

### Step 3: Flash the Bluetooth Module (with the InsaneFlasher)
As soon as your mainboard (S3) runs in Wi-Fi, we flash the Bluetooth chip (WROOM) wirelessly:

**🪟 For Windows Users (Recommended):**
1. Download the latest `InsaneFlasher.exe` from the `InsaneFlasher/Windows/` folder.
2. Double-click on the `.exe` - the tool starts immediately (no installation required).

**🍎/🐧 For macOS & Linux Users:**
1. Make sure Python 3 is installed on your system, and download the source code `InsaneFlasher.py` from the `InsaneFlasher/Linux_Mac/` folder.
2. Install the necessary packages in the terminal: `pip install customtkinter requests esptool zeroconf pillow packaging`
3. Start the tool: `python3 InsaneFlasher.py`

**The Flash Process:**
Select your Insane Sound System in the tool and simply click on the large red button **"INSTALL UPDATE NOW"** (or similar depending on language). The tool automatically downloads the latest firmware, puts the chip into flash mode, installs the update, and restarts the Insane Sound System. Just sit back!

**Congratulations! Your Insane Sound System V5 is now fully operational!**

<img src="Images/4.svg" width="800" alt="Schematic">

---

## ⚖️ License
This entire project (hardware and software) is licensed under the [CC BY-NC-SA 4.0 License](https://creativecommons.org/licenses/by-nc-sa/4.0/).
This means: Rebuilding and modifying for private purposes is expressly encouraged; any commercial use or sale is strictly prohibited!

---

## ☕ Support this Project
V5 took an extreme amount of time, nerves, and coffee. If you like the system and would like to support my work, I'd be incredibly happy about a virtual coffee!

<a href="https://www.paypal.me/babeinlovexd">
  <img src="https://img.shields.io/badge/Donate-PayPal-blue.svg?style=for-the-badge&logo=paypal" alt="Donate with PayPal">
</a>

Every cent flows directly into the development of V6 and new prototypes! 🚀
---

## 👨‍💻 Developed by

| [<img src="https://avatars.githubusercontent.com/u/43302033?v=4" width="100"><br><sub>**Christopher**</sub>](https://github.com/babeinlovexd) |
| :---: |

---
