## Introduction

This blueprint shows how to connect Dual-MCU boards to Blynk.

## How It Works

In a Dual-Microcontroller Unit (MCU) setup, Blynk allows to off-load network connectivity to a Network Co-Processor (NCP), with the application/business logic residing on the primary MCU. It's particularly useful for IoT projects that have specific requirements for the primary MCU or when using Blynk for retrofitting existing products.

`Blynk.NCP` ships with some unique features:

- Dynamic Provisioning (`BLE`-assisted **Blynk.Inject**)
- Advanced Network Manager: `WiFi` (up to 16 saved networks), `Ethernet`, `Cellular` (depending on hardware)
- `Time`, `Timezone` and `Location` APIs
- Persistent automations (automation scenarios that work even if device is offline) - *soon*

## Components Used in This Project

This project is compatible with some widely available IoT boards that have a Dual-MCU architecture:

- [Arduino Nano RP2040 Connect][1]
- [Arduino Nano 33 IoT][2]
- [Arduino MKR WiFi 1010][3]
- [RPi Pico][7] + [ESP8266][8]
- [TTGO T-PicoC3][6] - *soon*
- [Arduino UNO R4 WiFi][4] - *soon*
- [Arduino Portenta C33][5] - *soon*

## 1. Flash the Blynk.NCP firmware

This is a **PlatformIO** project. We recommend using [**VSCode**][pio_vscode] or [**PIO CLI**][pio_cli].

> **Note:** This operation overwrites both the MCU and the NINA module firmware.  
Don't worry, you will be able to [restore the stock firmware][restore] easily.

To flash the NCP firmware, you need to connect your board using a USB cable, then run:

```sh
pio run --environment rp2040connect --target upload_ncp
```

The `environment` flag should correspond to your board type.  
Possible options are: `rp2040connect`, `nano33iot`, `mkrwifi1010`, `pico_esp8266`

## 2. Prepare the Main Firmware and Upload It to Your Device

Open `src/main.cpp` and fill in [information from your Blynk Template](https://bit.ly/BlynkInject):

```cpp
#define BLYNK_TEMPLATE_ID           "TMPxxxxxx"
#define BLYNK_TEMPLATE_NAME         "MyDevice"
```

Build and flash the example project:

```sh
pio run --environment rp2040connect --target upload
pio device monitor
```

Use your Blynk.App (iOS/Android) to connect the device to the cloud.

## Next steps

* Explore the Blynk Web Console and [Blynk IoT app](https://docs.blynk.io/en/downloads/blynk-apps-for-ios-and-android), try controlling your device from both
* Explore [Blynk Documentation](https://docs.blynk.io/en/) 
* Learn how to work with [Virtual Pin Datastreams](https://docs.blynk.io/en/getting-started/using-virtual-pins-to-control-physical-devices) 
* Read more about [Automations](https://docs.blynk.io/en/concepts/automations)
* Modify the code for your needs

## Disclaimer

> The community edition of **Blynk.NCP** is available for personal use and evaluation.
If you're interested in using **Blynk.NCP** for commercial applications, feel free to [contact Blynk][blynk_sales]. Thank you!

## Related Links

[Blynk Troubleshooting guide](https://docs.blynk.io/en/troubleshooting/general-issues)  
[Documentation](https://docs.blynk.io/en/)  




[blynk_sales]: https://blynk.io/en/contact-us-business
[pio_vscode]: https://docs.platformio.org/en/stable/integration/ide/vscode.html#ide-vscode
[pio_cli]: https://docs.platformio.org/en/stable/core/index.html
[restore]: ./docs/RestoreFirmware.md


[1]: https://store.arduino.cc/products/arduino-nano-rp2040-connect
[2]: https://store.arduino.cc/products/arduino-nano-33-iot
[3]: https://store.arduino.cc/products/arduino-mkr-wifi-1010
[4]: https://store-usa.arduino.cc/pages/unor4
[5]: https://www.arduino.cc/pro/hardware-product-portenta-c33
[6]: https://www.lilygo.cc/products/lilygo%C2%AE-t-picoc3-esp32-c3-rp2040-1-14-inch-lcd-st7789v
[7]: https://www.raspberrypi.com/products/raspberry-pi-pico
[8]: https://www.waveshare.com/pico-esp8266.htm
