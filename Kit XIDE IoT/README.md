## Introduction

This blueprint will guide you through launching your project with the [XIDE IoT Framework](https://docs.microside.com/en).

The sample project uses the following devices from the Kit XIDE IoT, which allows to measure temperature, humidity and ambient ligth, read four switchs, one potentiometer position, 3 analog signals, control four digital outputs and one RGB led.

## Components Used in This Project

* [X-NODE/XC01-ESP32-S3 WiFi & Bluetooth Controller](https://docs.microside.com/en/user-manuals/xide/x-nodes/xc01-mcu-wifi-ble/r5/xc01-mcu-wifi-ble-esp32-s3)
* [X-NODE/XN01 - Digital Inputs](https://docs.microside.com/en/user-manuals/xide/x-nodes/xn01-digital-inputs/a-r2/xn01-digital-inputs)
* [X-NODE/XN02 - Digital Outputs](https://docs.microside.com/en/user-manuals/xide/x-nodes/xn02-digital-outputs/a-r2/xn02-digital-outputs)
* [X-NODE/XN03 - Analog Inputs/Outputs](https://docs.microside.com/en/user-manuals/xide/x-nodes/xn03-analog-inputs-outputs/a-r2/xn03-analog-inputs-outputs)
* [X-NODE/XN04 - Temperature/Humidity/Ambient Ligth Sensor](https://docs.microside.com/en/user-manuals/xide/x-nodes/xn04-temp-hum-lum/a-r2/xn04-temp-hum-lum)
* [X-BOARD / XB01 - IoTrainer](https://docs.microside.com/en/user-manuals/xide/x-board/xb01-iotrainer) (optional)
* USB type C cable
* Arduino IDE or PlatformIO to upload firmware
* Blynk Console and Blynk App for web and mobile dashboards

## How To Use This Blueprint

### I. Prepare Your Hardware

1. Assemble the hardware kit, place all the X-NODEs in one of the X-BOARD's [mikroBUS™](https://www.mikroe.com/mikrobus) sockets, placement order is not important, however, make sure the [XC01](https://docs.microside.com/en/user-manuals/xide/x-nodes/xc01-mcu-wifi-ble/r5/xc01-mcu-wifi-ble-esp32-s3) USB-C connector is not blocked in order to program and power the board. If you don't have an X-BOARD you can stack all the X-NODEs on top of oneanother.

2. Before powering the board check that all X-NODEs are correctly placed, misaligments could potentially damage the device.

3. Once the hardware is assembled, connect it to your computer through the USB cable.

![xide kit assembly instructions](https://github.com/blynkkk/blueprints/blob/main/Kit%20XIDE%20IoT/Images/xide-assembly-instructions.jpg?raw=true)

### II. Prepare Required Software

1. Install [Arduino IDE](https://www.arduino.cc/en/software) or [PlatformIO](https://platformio.org/install)  
_If you are using Arduino IDE, follow the next steps (skip for PlatformIO)_
2. Install the [ESP32 Board in the Arduino IDE](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html)*
3. Install [Blynk library](https://docs.blynk.io/en/blynk-library-firmware-api/installation)
4. Select the board ESP32S3-Dev-Module and configure it according to this image:

![](https://github.com/blynkkk/blueprints/blob/main/Kit%20XIDE%20IoT/Images/arduino-board-cfg.png?raw=true)

5. Select the correct port of your device

Note:
*On Arduino IDE, make sure to pick version 2.0.17 or lower on the board manager, higher version might not compile at the time of writting this manual, this issue might be fixed in future updates.

## III. Prepare the Firmware and Upload It to Your Device

You need to specify the Blynk TemplateID in your firmware. This information will be provided, alongside a sketch to program the device.

1. Click on the **Activate device** action in Template Home tab (this tab should open automatically once you've pressed the Use Blueprint button)
2. Download zip arhive 
3. Flash your device
* For Arduino IDE:
 *Go to **Sketch*** > ***Add File*** >
 *Select sketch from the zip archive* >
 *Press **Upload** button*
* For PlatformIO:
*Open project* >
*Press **PlatformIO: Upload***

_Check the **Troubleshooting** section at the end of this tutorial if you have issues uploading the firmware_

## IV. Connect your device to your WiFi network
For this step you need to download Blynk App on your mobile phone

1. Scan a QR code to start the device activation process in the app
2. In the app click **Start**
3. Connect to "Blynk ... " network
4. Select network your device will use and click **Continue**
5. Your device is connected now! Click **Finish** to open your device. You also will see your device in the Blynk Console

![Blynk App WiFi provisioning steps](https://github.com/blynkkk/blueprints/blob/main/Kit%20XIDE%20IoT/Images/blynk-app-wifi-provision-steps.jpg?raw=true)

6. Explore your device on Blynk Console and Blynk App

![Blynk Dashboard on Blynk.Console and Blynk.App](https://github.com/blynkkk/blueprints/blob/main/Kit%20XIDE%20IoT/Images/blynk-console.jpg?raw=true)

## V. Set Up Notifications
Let's configure notifications on your phone to keep you informed when the temperature or humidity falls outside the comfortable range. This way, you can take action to restore optimal levels as soon as possible.
1. Go to the **Automations** tab 
2. Click **+Create automation** and choose **Device state**
3. Select your device, then the **datastream** that will trigger the notification, for this example choose **Temperature**
4. Select one of the conditions that will trigger the notification and set a value to compare against, for example, **is greater than or equal to...** 30°C.
5. Click on **+ Add Action**, then **Send an app notfication**, set a title and a message for the notification
6. Choose a name and cover for the automation then click Save

![Blynk App setting up notifications](https://github.com/blynkkk/blueprints/blob/main/Kit%20XIDE%20IoT/Images/blynk-app-setup-notifications-steps.jpg?raw=true)

## VI. Next Steps
* Explore [Blynk Documentation](https://docs.blynk.io/en/) and learn how to work with [Virtual Pins](https://docs.blynk.io/en/getting-started/using-virtual-pins-to-control-physical-devices)
* Modify the code to match your requirements
* Explore [XIDE Documentation](https://docs.microside.com/en/user-manuals/xide/x-nodes) and learn how to work with X-NODEs to quickly build IoT projects
* Build your own hardware solution with XIDE
* Deploy more devices

## Troubleshooting

### There is multiple compile errors on Arduino IDE

* Make sure to pick version 2.0.17 or lower on the board manager, higher version might not compile at the time of writting this manual, this issue might be fixed in future updates.
* On the Library Manager pick version 1.3.2 or higher for the Blynk Library
* Double check your board settings so they match Step 4 of section [2. Prepare your software](#2-prepare-required-software)

### Compile succeds but uploading to the board fails

* Check if the serial port exist, on the Arduino IDE check the Serial Ports with the [XC01]() disconnected, then connect it to the computer with the USB cable, check again, if no new Serial Port shows up, on the [XC01]() press and hold the Boot Button, press and release the Reset Button, if still does not show up try with a different USB cable and port. 
* If the serial port is available but cannot be open, then using the Arduino IDE's Serial Monitor try opening the serial port, if the port is busy make sure no other app on your computer has it opened, try disconnecting and connecting again the [XC01]().

### How to Reset a Device Configuration

If your mobile device does not detect the Blynk network, then you most likely need to reset the configuration of your ESP32. Follow the steps below.

Open the serial port terminal.

Press and hold the Boot button on your ESP32 for 10 seconds. The serial port monitor terminal should display the following message:

```
[XXXXX] Hold the button for 10 seconds to reset the configuration…
```

After 10 seconds, release the Boot button. You should see the following in the terminal:

```
[XXXXX] RUNNING => RESET_CONFIG
[XXXXX] Resetting configuration!
[XXXXX] Configuration stored to flash
[XXXXX] RESET_CONFIG => WAIT_CONFIG
[XXXXX] Scanning networks..
```

Search the Blynk network again with your mobile device using the QR code.

### The potentiometer changes the value of ADC1, ADC2 and ADC3 datastreams as well

When there is nothing connected to the **analog inputs** of the XN03 there will be a *ghost* reading between the analog inputs and the potentiometer, this is due to the multiplexed nature of the ADC, once a signal is connected to an input it will show the correct value.

### Data is updated at very irregular intervals

This blueprint tries to make the most out of free accounts which have a hard cap of [device messages](https://docs.blynk.io/en/blynk.console/limits#organization-limits), with up to 19 datastreams it would run out relatively fast, to keep a reasonable system responsiveness and data usage, it will only update data once a datastream has changed in a noticeable way. You can upgrade your account and modify the firmware to remove this limit, however, be reasonable with the amount of data sent to the cloud at the same time, as too much data may cause other set of issues, for example the [flood error](https://docs.blynk.io/en/troubleshooting/developer-mode#flood-error).
