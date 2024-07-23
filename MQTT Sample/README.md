## Introduction

This blueprint will guide you in launching your project with our [MQTT Sample](https://github.com/Blynk-Technologies/Blynk-MQTT-Samples).

The sample project simulates a heater device:

- The room heats up when the set temperature exceeds the current temperature.
- The room cools down when the set temperature is lower than the current temperature or if the heater is off.
- The device can also be controlled via the **Terminal** widget (type `help` for a list of commands).

## How To Use This Blueprint

The `MQTT Air Cooler/Heater` blueprint is compatible with various MQTT clients, developed in different programming languages.

Please **follow the instructions in the readme file** of the example that you like the most:

- [**Python 3**](https://github.com/Blynk-Technologies/Blynk-MQTT-Samples/blob/main/Python3/README.md) - suitable for use on Single Board Computers (SBCs) like `Raspberry Pi` and some Industrial IoT gateways
- [**MicroPython**](https://github.com/Blynk-Technologies/Blynk-MQTT-Samples/blob/main/MicroPython/README.md) - a fun and easy way of creating the device firmware
- [**Arduino / PlatformIO**](https://github.com/Blynk-Technologies/Blynk-MQTT-Samples/blob/main/Arduino_Blynk_MQTT/README.md) - a pre-configured project that supports over 15 connectivity-enabled boards, including the `Espressif ESP32`, `Raspberry Pi Pico W`, `Nano 33 IoT`, `Nano RP2040 Connect`, `UNO R4 WiFi`, `Seeed Wio Terminal`, etc.
- [**Plain C**](https://github.com/Blynk-Technologies/Blynk-MQTT-Samples/blob/main/C_libmosquitto/README.md) with the `Mosquitto` library - tailored for advanced use cases needing high performance, compact size, or system-level integration
- [**Lua**](https://github.com/Blynk-Technologies/Blynk-MQTT-Samples/blob/main/Lua_OpenWrt/README.md) - ready for deployment on `OpenWrt`-based routers and SBCs like `Onion Omega2`
- [**HTML5 / JavaScript**](https://github.com/Blynk-Technologies/Blynk-MQTT-Samples/blob/main/HTML5_WebSocket/README.md) - thanks to the `WebSocket` technology, this example can be used [directly from the browser](https://bit.ly/Blynk-HTML5-MQTT-Sample)
- [**ESP-IDF Cellular**](https://github.com/Blynk-Technologies/Blynk-MQTT-Samples/blob/main/ESP-IDF-Cellular/README.md) - for Espressif ESP32 devices with a cellular modem

## Next Steps

* Explore the Blynk Web Console and [Blynk IoT app](https://docs.blynk.io/en/downloads/blynk-apps-for-ios-and-android), try controlling your device from both
* Explore [Blynk Documentation](https://docs.blynk.io/en/) and learn how to work with [Virtual Pins](https://docs.blynk.io/en/getting-started/using-virtual-pins-to-control-physical-devices)
* Learn more about [Automations](https://docs.blynk.io/en/concepts/automations)
* Learn how to [Share Device](https://docs.blynk.io/en/concepts/users) with other users
* Modify the code for your needs
* Add more devices

## Troubleshooting

* Make sure you have the latest versions of the software you're using
* Check that all used libraries are up to date
* Check that all the dependencies and configurations are correct
* Check your code for errors

## Related Links

- [Blynk MQTT API documentation](https://docs.blynk.io/en/blynk.cloud-mqtt-api/device-mqtt-api)
- [Blynk Troubleshooting guide](https://docs.blynk.io/en/troubleshooting/general-issues)
- [Blynk Documentation](https://docs.blynk.io/en/)
