🎮 ESP32 i-BUS to BLE Gamepad
![RC Dashboard Screenshot](assets/esp32.png)

(FlySky 6CH)This project transforms a FlySky RC Transmitter into a high-performance Wireless Bluetooth Gamepad using an ESP32.
It is specifically optimized for flight simulators like PicaSim and works seamlessly on Windows 11.

## 📁 Project Structure
```text
├── include/
│   ├── ble_task.h      # BLE task and HID configuration
│   ├── ibus_task.h     # i-BUS protocol parsing headers
│   └── main.h          # Global shared variables and Mutex
├── src/
│   ├── ble_task.cpp    # Analog mapping, Deadzone logic & BLE transmission
│   ├── ibus_task.cpp   # Serial i-BUS data processing (Task-based)
│   └── main.cpp        # System initialization & FreeRTOS task creation
├── platformio.ini      # Library dependencies & Build settings
└── README.md           # Project documentation


✨ Key FeaturesZero-Latency Response: Built on FreeRTOS with dual-core task distribution for maximum speed.
6-Channel Analog Precision: Supports 4 primary stick axes plus 2 additional switches/potentiometers.
Advanced Split-Mapping: Ensures a perfect 1500 center point with independent scaling for positive and negative ranges to prevent stick "jumps".
Smart Deadzone: Integrated $10\text{-}15$ point neutral zone to eliminate stick jitter and drift.

🛠️ Hardware SetupWiring Diagram

FlySky Receiver (i-BUS)     ESP32 Pin
VCC (5V)                    VIN / 5V
GND                         GND
Signal (i-BUS)              GPIO 16 (RX2)

🚀 Installation & Build1.

Requirements

PlatformIO installed in VS Code.
ESP32 DevKit V1 or similar.2.
DependenciesEnsure your platformio.ini includes the following libraries
lib_deps =
    bmellink/IBusBM @ ^1.1.4
    https://github.com/lemmingDev/ESP32-BLE-Gamepad.git

![RC Dashboard Screenshot](assets/esp32.png)
