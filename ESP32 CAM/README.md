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
Tools->Port->chose port
8. Create a new sketch.




