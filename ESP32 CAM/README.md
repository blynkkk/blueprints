## Introduction

This bluepint is used to show the video stream in the Video Streaming Widget in the mobile Blynk IoT app.

## 1.Components

1. ESP32 CAM.
2. USB cable (USB->micro USB).
3. Programmer hardware (USB COM UART TTL CH340G, USB–UART FT232RL or other).
4. Cables for connecting ESP32CAM with programmer (If you do not use ESP32-CAM-MB).

USB–UART FT232RL 

![USB–UART FT232RL](https://github.com/blynkkk/blueprints/assets/110888025/a401b940-13f0-4e82-b4e1-76a1fbb41a1d)

USB COM UART TTL CH340G

![USB COM UART TTL CH340G](https://github.com/blynkkk/blueprints/assets/110888025/44b0ac48-6e11-4ef4-820b-c447a90a32e9)

**Recommendation to use ESP32-CAM-MB**

![ESP-32-CAM MB](https://github.com/blynkkk/blueprints/assets/110888025/e162d8b7-b61b-45d5-91e3-196e9bfbcdae)

## 2.Software preparation

1. Install [Arduino IDE](https://docs.arduino.cc/software/ide-v1/tutorials/Windows) (This project uses this program) or [PlatformIO](https://platformio.org/install).
2. Install last [Blynk library](https://docs.blynk.io/en/blynk-library-firmware-api/installation) for your IDE.
3. Select the correct board and port in your IDE settings.
4. Install the ESP32 board support if you are using Arduino IDE.
5. Create a new sketch.




