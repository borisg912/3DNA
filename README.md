# 3DNA - Interactive DNA Learning Model

**3DNA** is an educational 3D-printed DNA model that combines physical structure with interactive electronics to help students understand DNA base pairing through hands-on learning.

**Website**: [Project showcase and app downloads](Website)

## 🧬 Project Overview

This project creates a flat cylindrical DNA model with:
- **Magnetic DNA bases** with color-coded NeoPixel LEDs and unique resistor values for identification
- **Interactive base pairing game** that validates correct DNA base connections
- **Smart home integration** with multiple connectivity options
- **Companion applications** for Android and Windows

## 📦 Components

### Hardware
- **ESP32-C6** microcontroller on custom PCB (3-3.3V logic)
- **13 DNA bases** (12 helix positions + 1 foundation) with NeoPixels and resistors
- **2x CD74HC4067 multiplexers**: one at 3.3V for resistor voltage divider, one at 5V for NeoPixel control
- **SN74AHCT125N** buffer gate for driving 5V signals from ESP32's 3V
- **TEMT6000** ambient light sensor for dynamic brightness control
- **MPU-6500** gyroscope/inclinometer for spatial orientation
- **DFPlayer Mini** for audio feedback
- **BQ25895** power management IC with USB/USB-C quick charging (up to 9V, 25W@3A)
- **MP8715** voltage regulator (5-9V to 5V)
- **4x 18650 Li-ion batteries** (user-replaceable) with per-cell protection: PPTC fuses + AO3401A + DW01 + FS8205A
- **FQP30N06L** MOSFET for fan control
- **BAT54C** Schottky diode
- **NeoPixel strips** for visual effects (5V)
- **Touch button** for user interaction
- **Backboard button** for system functions

### Software
- **ESP-IDF firmware** for ESP32-C6
- **Android application** for mobile control
- **Windows UWP application** for desktop

## 🎯 Features

### Interactive Learning Mode
- **Base Identification**: Each base has a unique resistor value read via voltage divider
- **Color Coding**: NeoPixels light up in base-specific colors (A, T, C, G)
- **Pair Validation**: Check correct base pairing (A-T, C-G) with visual feedback
- **Error Highlighting**: Wrong bases light up in red for easy identification

### Smart Home Mode
- **Multi-protocol connectivity**: Wi-Fi, Bluetooth/BLE, Zigbee, Thread
- **Remote control**: Control NeoPixels via companion apps
- **Motion sensing**: Gyroscope triggers commands on movement
- **Ambient lighting**: Dynamic brightness based on environment

### Power Management
- **Battery operation**: 2-4 cell configuration
- **USB charging**: With power delivery management
- **Sleep modes**: Low-power states for battery conservation
- **Thermal management**: Fan control based on temperature

## 🛠️ Development Status

- **Hardware**: PCB design in KiCad (v4.1 final)
- **Firmware**: ESP-IDF framework with modular components
- **Mobile**: Android app foundation
- **Desktop**: Windows UWP app starter

## 📁 Project Structure

```
3DNA/
├── Embedded/          KiCad PCB files
├── EmbeddedCode/      ESP32-C6 firmware (ESP-IDF)
├── AppAndroid/        Android mobile app
├── AppWindows/        Windows UWP desktop app
├── Website/           Project showcase website
└── Assets/            Graphics and media
```

## 📄 Documentation

- [English README](README.md)
- [Български README](README.BG.md)

## 🤝 Contributing

This is a school project developed for educational purposes. Contributions and feedback are welcome for improving the learning experience and technical implementation.

## 📜 License

This project is licensed under **GNU GPL v3** - see [LICENSE](LICENSE) for details.

---

*Built with passion for education and technology*

