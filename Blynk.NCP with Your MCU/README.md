## Introduction

`TODO`

## Components Used in This Project

You will need:
- Raspberry Pi Pico
- One of the supported connectivity modules (see the table below)
- Breadboard and some jumper wires

## 1. Flash `Blynk.NCP` firmware to your connectivity module

1. Please follow the official firmware flashing guide. This is usually supplied by the module vendor.
2. Blynk.NCP is shipped as a combined firmware, so you only need to flash a single file (flash at address `0`).
3. Select the corresponding firmware file, depending on your module type:

Connectivity module              | NCP firmware               | Chipset         | Connectivity | Provisioning | Interaction
:--                              | :---                       | :---            | ---          | ---          | ---
[Adafruit AirLift][20]           | [link][generic_esp32_4M]   | `ESP32`         | WiFi 2.4     | BLE          | RGB LED
[Macchina SuperB][21]            | [link][generic_esp32_4M]   | `ESP32`         | WiFi 2.4     | BLE          | Green LED
ESP-WROOM-32 4MB<br>(no PSRAM)   | [link][generic_esp32_4M]   | `ESP32`         | WiFi 2.4     | BLE          |
[TTGO T-Internet-POE][22]        | [link][lilygo_poe]         | `ESP32+LAN8720` | WiFi 2.4, Ethernet POE | BLE    |
[Seeed WT32-ETH01][23]           | [link][wt32_eth01]         | `ESP32+LAN8720` | WiFi 2.4, Ethernet     | BLE    |
[Witty Cloud][24]                | [link][generic_esp8266_4M] | `ESP8266`       | WiFi 2.4     | WiFiAP       | RGB LED, User Button
[DFRobot WiFi Bee][25]           | [link][generic_esp8266_4M] | `ESP8266`       | WiFi 2.4     | WiFiAP       | User Button
ESP-07S, ESP-12F                 | [link][generic_esp8266_4M] | `ESP8266`       | WiFi 2.4     | WiFiAP       |


You can also check the full list of the [Blynk.NCP firmware files](https://github.com/blynkkk/BlynkNcpDriver/releases/latest).

## 2. Assemble the board

Connect Blynk.NCP to the Primary MCU of your choice (i.e. `STM32`, `ATmega`, `RP2040` or `ATSAMD`) using UART.  
For example, here's how to connect the XBee form factor modules (`Macchina SuperB`, `DFRobot WiFi Bee`) to the `Raspberry Pi Pico` board:

![Blynk.NCP breadboard](./Images/PiPico-XBee-BlynkNCP.png)

## 3. Use the Blynk-provided library to communicate with the NCP

There are several options here:
- [`BlynkNcpDriver`](https://github.com/blynkkk/BlynkNcpDriver) - a low-level, `C99` compatible driver with minimal dependencies
- [`Blynk library`](https://github.com/blynkkk/blynk-library) provides an optional `C++11` convenience wrapper for the driver

In this project, we'll use the full-fledged Blynk library.

## 3. Prepare the `Primary MCU` Firmware and Upload It to Your Device

`TODO`

The expected debug output looks like this:
```log
[1345] NCP responding (baud 115200, 2289 us)
[1349] Blynk.NCP firmware: 0.4.6
[1684] State: Configuration
```

## 5. Use the **Blynk mobile app** (iOS/Android) to configure your new device

`TODO`



[20]: https://www.adafruit.com/product/4201
[21]: https://www.macchina.cc/catalog/m2-accessories/superb
[22]: https://www.lilygo.cc/products/t-internet-poe
[23]: https://www.seeedstudio.com/Ethernet-module-based-on-ESP32-series-WT32-ETH01-p-4736.html
[24]: https://protosupplies.com/product/esp8266-witty-cloud-esp-12f-wifi-module/
[25]: https://www.dfrobot.com/product-1279.html

[generic_esp8266_4M]: https://github.com/blynkkk/BlynkNcpDriver/releases/latest/download/BlynkNCP_generic_esp8266_4M.flash.bin
[generic_esp32_4M]: https://github.com/blynkkk/BlynkNcpDriver/releases/latest/download/BlynkNCP_generic_esp32_4M.flash.bin
[lilygo_poe]: https://github.com/blynkkk/BlynkNcpDriver/releases/latest/download/BlynkNCP_lilygo_poe.flash.bin
[wt32_eth01]: https://github.com/blynkkk/BlynkNcpDriver/releases/latest/download/BlynkNCP_wt32_eth01.flash.bin
