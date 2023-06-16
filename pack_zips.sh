#!/bin/bash
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
#pack ESP32_Weather_Station_Arduino.zip             "ESP32 Weather Station/Firmware/Arduino"
pack ESP32_Weather_Station_PlatformIO.zip           "ESP32 Weather Station/Firmware/PlatformIO"
pack ESP32_Weather_Station_Edgent_Arduino.zip       "ESP32 Weather Station Edgent/Firmware/Arduino"
pack ESP32_Weather_Station_Edgent_PlatformIO.zip    "ESP32 Weather Station Edgent/Firmware/PlatformIO"
