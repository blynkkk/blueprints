# Introduction

This blueprint is a quick-start tutorial for connecting the Arduino Leonardo board to Blynk using Ethernet. You will be able to control blinking of the built-in LED using a button on the web or mobile dashboard. You can also use this blueprint with similar boards, such as the Arduino Uno and Arduino Mega.

# 1. Components 

1. Arduino Leonardo / Uno / Mega board
2. Ethernet Shield
3. USB cable


# 2. Prepare your Hardware before flashing

1. Connect Ethernet Shield to the Arduino board
2. Connect Arduino board to computer with a USB cable
3. Insert Ethernet cable to Ethernet Shield
It should look like this:
*Picture*

# 3. Prepare required software

1. Install [Arduino IDE](https://www.arduino.cc/en/software) or [PlatformIO](https://platformio.org/install)
2. Install [Blynk library](https://docs.blynk.io/en/blynk-library-firmware-api/installation/install-blynk-library-in-arduino-ide) for your IDE
3. Install Ethernet Library for your IDE
4. Select the correct board and port in your IDE settings
5. Create a new sketch if you are using Arduino IDE


# 4. Prepare the Firmware and upload it to your device

We need to include TemplateID, AuthToken (unique identifier of your device), and WiFi credentials in the sketch.

1. Click on the Activate device action in the Template Home tab (this tab should open automatically once you've pressed the Use Blueprint button)
2. Follow the proposed steps to prepare and upload the code
3. Once the code is successfully uploaded the device dashboard will open automatically
4. Check the Troubleshooting section at the end of this tutorial if you have issues uploading the firmware


# Next steps after the device is activated

* Explore the Blynk [Web Console](blynk.cloud) and [Blynk IoT app](https://docs.blynk.io/en/downloads/blynk-apps-for-ios-and-android), try controlling your device from both
* Explore [Blynk Documentation](https://docs.blynk.io/en/getting-started/using-virtual-pins-to-control-physical-devices) and learn how to work with Virtual Pins
* Improve the code for your needs
* Add more devices


# Troubleshooting

* Make sure you have the latest [Blynk Library](https://docs.blynk.io/en/blynk-library-firmware-api/installation) installed
* Check that all the dependencies and configurations are correct
* Check your sketch for errors. Click the Verify button to compile your sketch without uploading it
* Check your board and port selections
* Check your connections. Your board needs to be connected with a data USB cable (charge-only cables will not work). Make sure the cable is fully inserted in the port on each end. Try a different USB cable, and avoid hubs and other adapters if possible. Remove connections to the board pins, especially the 0 (RX) and 1 (TX) digital pins.
* Check that your boards and libraries are up to date
