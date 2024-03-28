## Introduction

This blueprint will help you to kickstart our [MQTT Sample](https://github.com/Blynk-Technologies/Blynk-MQTT-Samples).

The template represents a heater device.
- When the `set temperature` is higher than the current (simulated), the room heats up
- When the `set temperature` is lower than the current, or the heater is off - the room cools down
- The device can also be operated using the `Terminal` widget (type `help` for a listt of commands).

## How To Use This Blueprint

The MQTT Sample blueprint is designed to work with a variety of MQTT clients, which are developed in different languages:

- **Python 3** - very easy to use on Single Board Computers (SBCs) like Raspberry Pi and some Industrial IoT gateways
- **MicroPython** - a fun and easy way of creating the device firmware
- **Arduino / PlatformIO** - a pre-configured project that supports more than 15 connectivity-enabled boards like Espressif ESP32, Raspberry Pi Pico W, Nano 33 IoT, Nano RP2040 Connect, UNO R4 WiFi, Seeed Wio Terminal, etc.
- **Plain C** using the Mosquitto library - for advanced use cases that require high performance, small size or system-level integration
- **Lua** - ready to use on `OpenWrt`-based routers and SBCs like `Onion Omega2`
- **HTML5 / JavaScript** - thanks to WebSockets, this example can be used [right from the browser](https://bit.ly/Blynk-HTML5-MQTT-Sample)

1. Download our MQTT Sample repository using [GitHub](https://github.com/Blynk-Technologies/Blynk-MQTT-Samples)
   or as a [ZIP file](https://github.com/Blynk-Technologies/Blynk-MQTT-Samples/archive/refs/heads/main.zip)
2. Click `Activate New Device` button in this Blueprint
3. Follow the readme file of the example that you like the most

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
