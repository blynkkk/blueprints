## Introduction

Header Constructor is a new feature for Blynk mobile apps. It's a customizable top bar that expands design options and makes you app look so complete! See it for yourself - we prepared a Blueprint with a fancy Tesla app assembled from just Blynk's UI components, controlled from the ESP32 board.

## Components Used in This Project

You can use pretty much any ESP32 dev board. No additional hardware is needed.

* [Blynk App](https://docs.blynk.io/en/downloads/blynk-apps-for-ios-and-android) and Blynk Console
* Arduino IDE to upload a firmware
* ESP32 DEVKIT board
* Data USB cable (charging-only will not work)

## 1. Prepare Required Software

1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Install [Blynk library](https://docs.blynk.io/en/blynk-library-firmware-api/installation)
3. Install the [ESP32 board support](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)
4. Select the correct board and port in the **Tools** menu

## 2. Prepare the Firmware and Upload It to Your Device

When using Blynk, you need to place TemplateID and Template Name in your sketch. We will provide you with the sketch where all of this info is already included. Just follow the next steps:

1. Click on the **Activate device** action in Template Home tab (this tab should open automatically once you've pressed the Use Blueprint button)
2. Download zip arhive 
3. Upload the sketch to your device: in Arduino IDE go to **Sketch** > **Add File** >
 Select sketch from the zip archive >
 Press **Upload** button
4. Scan a QR code to start the device activation process in the app
5. In the app click **Start**
6. Connect to "Blynk ... " network
7. Select network your device will use and click **Continue**
8. Your device is connected now! Click **Finish** to open your device. You also will see your device in the Blynk Console

_Check the **Troubleshooting** section at the end of this tutorial if you have issues uploading the firmware and getting the device online_  

## 3. Let's Play Around!
1. Change the your device state - ...
2. Change what is visible in the header - hide battery or device status
3. Open the page to see the historical data chart
4. Try out how it looks with the different theme (light / dark)

## 4. Header Structure

Here's a quick dive into Header Constructor structure. You can add labels such as Connection Status and Last Reported timestamp, display an image inside the device's header, or assign Standalone Pages to the Header Buttons. Experiment with colors and background images to customize it as you like.
![mobile-header-constructor-overview](https://github.com/blynkkk/blueprints/assets/120122081/7644c6a7-1ab6-4dee-9cf4-c8fb60c82d1b)


## Next Steps

Here are some ideas on how you can style your app with Headers - try to recreate them or come up with your own! 
Follow this detailed [guide](https://docs.blynk.io/en/blynk.apps/device-header-constructor) to set things up.
![device-header-design-examples](https://github.com/blynkkk/blueprints/assets/120122081/30f23e0b-aa30-4e30-b77a-20482f8c610e)


## Troubleshooting

If you have any issues with flashing the firmware or your device doesn't go online, delete the device and try connecting it again considering the below checklist
* Make sure you have the latest [Blynk Library](https://docs.blynk.io/en/blynk-library-firmware-api/installation) installed
* Check that all used libraries are up to date
* Check that all the dependencies and configurations are correct
* Check your sketch for errors. Click the **Verify** button to compile your sketch without uploading it
* Check your board and port selections
* Check your connections. Your board needs to be connected with a data USB cable (charge-only cables will not work). Make sure the cable is fully inserted in the port on each end. Try a different USB cable, and avoid hubs and other adapters if possible. Remove connections to the board pins, especially the 0 (RX) and 1 (TX) digital pins.
* If you are trying to provision your device the second time or want to connect it to a different WiFi network, you need to reset the hardware configuration. To do so, hold the **Boot** button for 10 seconds.
* Check [Troubleshooting guide](https://docs.blynk.io/en/getting-started/activating-devices/blynk-edgent-wifi-provisioning#troubleshooting) for WiFi provisioning

## Related Links
[Blynk Troubleshooting guide](https://docs.blynk.io/en/troubleshooting/general-issues)  
[Documentation](https://docs.blynk.io/en/)
