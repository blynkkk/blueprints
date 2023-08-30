#!/usr/bin/env bash
mkdir -p zips

function pack {
    pushd "$2"
    #echo `pwd`
    zip -r "$1" "."
    popd
    mv "$2/$1" ./zips/
}

pack Arduino_Ethernet_PlatformIO.zip                "Arduino Ethernet/Firmware/PlatformIO"
#pack Asset_Tracker_Particle.zip                    "Asset Tracker/Firmware/Particle"
#pack ESP32_CAM_Arduino.zip                         "ESP32 CAM/Firmware/Arduino"
pack ESP32_Blinking_LED_Edgent_Arduino.zip          "ESP32 Blinking LED Edgent/Firmware/Arduino"
pack ESP32_Blinking_LED_Edgent_PlatformIO.zip       "ESP32 Blinking LED Edgent/Firmware/PlatformIO"
#pack ESP32_Weather_Station_Arduino.zip             "ESP32 Weather Station/Firmware/Arduino"
pack ESP32_Weather_Station_PlatformIO.zip           "ESP32 Weather Station/Firmware/PlatformIO"
pack ESP32_Weather_Station_Edgent_Arduino.zip       "ESP32 Weather Station Edgent/Firmware/Arduino"
pack ESP32_Weather_Station_Edgent_PlatformIO.zip    "ESP32 Weather Station Edgent/Firmware/PlatformIO"
pack Access_OpenWrt_Router_Remotely_Lua.zip         "Access OpenWrt Router Remotely/Firmware/Lua"
#pack Blynk.NCP_compatible_Boards_PlatformIO.zip     "Blynk.NCP compatible Boards/Firmware/PlatformIO"
pack WioTerminal_Arduino.zip                        "WioTerminal Edgent/Firmware/Arduino"
pack WioTerminal_PlatformIO.zip                     "WioTerminal Edgent/Firmware/PlatformIO"
