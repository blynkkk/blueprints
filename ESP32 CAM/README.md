## Introduction

This bluepint is used to show the video stream in the Video Streaming Widget in the mobile Blynk IoT app.

## 1.Components

1. ESP32 CAM.
2. USB cable (USB->micro USB).
3. Programmer hardware (USB COM UART TTL CH340G, USB–UART FT232RL or other).
4. Cables for connecting ESP32 CAM with programmer (If you do not use ESP32-CAM-MB).

USB–UART FT232RL 

![USB–UART FT232RL](https://github.com/blynkkk/blueprints/assets/110888025/a401b940-13f0-4e82-b4e1-76a1fbb41a1d)

USB COM UART TTL CH340G

![USB COM UART TTL CH340G](https://github.com/blynkkk/blueprints/assets/110888025/44b0ac48-6e11-4ef4-820b-c447a90a32e9)

**Recommendation to use ESP32-CAM-MB**

![ESP-32-CAM MB](https://github.com/blynkkk/blueprints/assets/110888025/e162d8b7-b61b-45d5-91e3-196e9bfbcdae)

## 2.Software preparation

1. If you need a USB driver for your ESP32 CAM, please install the [USB DRIVER](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/establish-serial-connection.html#connect-esp32-to-pc)
1. Install [Arduino IDE](https://docs.arduino.cc/software/ide-v1/tutorials/Windows) (This project uses this program) or [PlatformIO](https://platformio.org/install).
2. Add Additional Boards Manager URLs for ESP32
File->Preferences
Add this link `https://dl.espressif.com/dl/package_esp32_index.json` to Additional Boards Manager URLs section and click ok button.

![additional](https://github.com/blynkkk/blueprints/assets/110888025/4c0a7df8-cb36-4a9a-8310-6e592ee83e31)

3. Add Library for ESP32 CAM
Tools->Board->Board Manager
Enter ESP32 to search field and choose ESP32 by Espressif Systems and click install button

![manager](https://github.com/blynkkk/blueprints/assets/110888025/66bc3e27-2feb-4b43-97a8-524f4c6c5ec9)

5. Install last [Blynk library](https://docs.blynk.io/en/blynk-library-firmware-api/installation) for your IDE.
6. Select the board for ESP32 CAM
Tools->Board->esp32->AI Thinker ESP32-CAM

![boardesp32CAM](https://github.com/blynkkk/blueprints/assets/110888025/1e7ecb64-ec6a-4e8a-8838-04d39addcac0)

7. Select port for Board (after connection device)
Tools->Port->choose port
8. Create new sketch.

## 3. Preparation ESP32 CAM

Connect via USB cable ESP32 CAM with PC (If you use ESP32-CAM-MB).
If you use another programmer, please follow follow the instructions.
Follow the next schematic diagram (5V connection recommendation):

![ESP32-CAM-FTDI-programmer-5V-supply](https://github.com/blynkkk/blueprints/assets/110888025/69ffb999-a86f-4a07-aa38-57d00cf5bed9)

**The board is ready for upload sketch**

## 4. Preparation blueprint

1. Click use blueprint button

![use blueprint button](https://github.com/blynkkk/blueprints/assets/110888025/265f99c9-12d5-48f2-a6d4-f9526eddabe2)

2. Hover to Activate device section and click

![activate device](https://github.com/blynkkk/blueprints/assets/110888025/a4f8dbbc-bb70-4104-9586-c6f55f2a5f9a)

## 5. Firmware preparation and device connection

1. Please download [Firmware acrhive](https://github.com/blynkkk/blueprints/raw/main/ESP32%20CAM/Firmware/CameraWebServer.zip)
2. Unzip the archive and open `CameraWebServer.ino` in Arduino IDE
3. Set your WiFi credentials in code:

![wifi](https://github.com/blynkkk/blueprints/assets/110888025/c0841b1d-d8f8-4d82-be5b-3a36b963f92a)

4. Set your Authtoken in code:
First copy your Authtoken from New Device Activation tab:

![Auth](https://github.com/blynkkk/blueprints/assets/110888025/550e7f54-e17d-4c77-9711-c4ceea1830ec)

Paste Authtoken to code:

![token](https://github.com/blynkkk/blueprints/assets/110888025/e667374c-868f-412b-94f9-2f2a69951533)

5. Upload sketch.
6. Open serial monitor in Arduino IDE
7. Set 115200 baud in serial monitor

![baud](https://github.com/blynkkk/blueprints/assets/110888025/89955289-93cd-45eb-b0d2-a7963b7b3940)

8. Disconnect wires (GND and IO1 pins)

![pins](https://github.com/blynkkk/blueprints/assets/110888025/be4c3f25-6267-4164-b1af-bedab847e1cb)

9. Click reset button in ESP32 CAM or dicconnect and connect USB cable
10. In the serial monitor you will see a successful connection to Blynk and starting Camera webserver and local url on which the webserver.

![iplocal](https://github.com/blynkkk/blueprints/assets/110888025/06060748-2e17-42ac-a011-51ccf8939822)

11. The device will be automatically created in Blynk console and device dashboard will be opened










