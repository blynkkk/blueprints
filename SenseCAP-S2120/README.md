## **SenseCAP S2120 8-in-1 Weather Sensor Blueprint Guide**

The **SenseCAP S2120 8-in-1 LoRaWAN Weather Sensor** is a powerful device
designed to measure and transmit key environmental data including **air
temperature**, **humidity**, **barometric pressure**, **wind speed**, **wind
direction**, **precipitation**, **solar radiation**, and **UV index**. This
guide walks you through setup, registration on **The Things Network (TTN)**,
and integration with **Blynk IoT** for real-time monitoring and control.

---

## **Step 1: Unpacking and Initial Setup**

### **1.1 Required Components**
- **SenseCAP S2120 Weather Sensor**
- **LoRaWAN Gateway** (e.g., SenseCAP Gateway)

### **1.2 Initial Setup**
1. **Check Package Contents**: Ensure all parts are present and undamaged.
2. **Install Batteries or Power Supply**: Follow the manual to correctly power up the sensor.
3. **Activate the Sensor**: The LED should blink or show status indicating it's ready to join the network.

---

## **Step 2: Registering the Sensor on The Things Network (TTN)**

### **2.1 Setting Up the LoRaWAN Gateway**
1. Log in to the [TTN Console](https://console.cloud.thethings.network/).
2. Navigate to **Gateways** > **Add Gateway** and fill in:
   - **Gateway EUI** (from the device label)
   - **Gateway ID** (e.g., `my-sensecap-gateway`)
   - **Frequency Plan** matching your region (EU868, US915, etc.)
   - Click **Register Gateway**
3. Follow manufacturer instructions to bring the gateway online.

!![App](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/SenseCAPS2120/SenseCAP-S2120/Image/gateway.png)


#### **Frequency Plans**
| **Frequency Plan** | **Region**            | **Description**                                                                 |
|--------------------|-----------------------|---------------------------------------------------------------------------------|
| **EU868**          | Europe                | Operates at 868 MHz. Commonly used across the EU for LoRaWAN deployments.       |
| **US915**          | North America         | Operates at 915 MHz. Used in the United States, Canada, and Mexico.             |
| **AS923**          | Asia-Pacific          | Operates at 923 MHz. Covers countries like Japan, Australia, and New Zealand.   |
| **IN865**          | India                 | Operates at 865 MHz. Dedicated plan for deployments in India.                   |
| **AU915**          | Australia/New Zealand | Operates at 915 MHz. Preferred for LoRaWAN in Australia and New Zealand.        |
| **KR920**          | South Korea           | Operates at 920 MHz. Allocated specifically for South Korea.                    |
| **RU864**          | Russia                | Operates at 864 MHz. Used exclusively within Russia.                            |

---

### **2.2 Creating a New Application**
1. **Log in to TTN Console**.
2. **Create an Application:**
   - Navigate to **Applications** > **Add Application**.
   - Enter:
     - **Application ID**: A unique name (e.g., `sensecap 8-in-1 weather station`).
     - **Description**: (e.g., `Weather Station`).
     - **Handler**: Select the handler for your region.
   - Click **Create Application**.

![App](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/SenseCAPS2120/SenseCAP-S2120/Image/create-form.png)

> **Note:**
> To ensure smooth operation, it’s recommended that all devices within a TTN
> application are of the same sensor type (e.g., SenseCAP-S2120). If you’d like to use
> different types of sensors, consider creating a separate application for each
> sensor type. This helps maintain better compatibility and performance.

The dashboard for the created application looks like this:

![App](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/SenseCAPS2120/SenseCAP-S2120/Image/dash-app.png)

---

### **2.3 Pairing the Sensor with the TTN Application**
1. **[Download and install SenseCAP Mate App](https://www.pgyer.com/sensecapmate)**

2. **Connect to Sensor to App**:
   - After the battery is installed, the red LED will be steady on. Also activate Bluetooth. Press button and hold for 3 seconds, the LED will flash at 1s frequency.
   - Please click the “Setup” button to turn on Bluetooth and click “ Scan ” to start scanning the sensor's Bluetooth.
   - Enter the pairing password. The default password is 000000.
   - Select the Sensor by BT ID (BT ID is on the bottom label of the sensor). Then, the basic information of the sensor will be displayed after entering.

![App](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/SenseCAPS2120/SenseCAP-S2120/Image/mobile-2.png)

3. **Configure parameters**:
   S2120 weather stations are manufactured to support universal frequency plan from 863MHz ~928MHz in one SKU. That is to say, every single device can support 7 frequency plans.
   - Set the corresponding frequency band based on the frequency band of the gateway.
   - Click the “Setting” and select the platform is “The Things Network”.
   - Select the Frequency Plan, if your gateway is US915, set the sensor to US915.
   - The device uses OTAA to join the LoRaWAN network by default. So, we can set the device EUI, App EUI and APP Key here.
       - **DevEUI**: Use the default value (found on the sensor label).
       - **AppEUI**: Use the manufacturer’s default value or generate a new one.
       - **AppKey**: Use the manufacturer’s default or generate a new one.
  - Click the “Send” button, send the setting to the sensor for it to take effect.
  - Click the “Home” button, the App will disconnect the Bluetooth connection. Then, the sensor will reboot.
  - When the device is disconnected from Bluetooth, the LED lights up for 5 seconds and then flashes as a breathing ligh


![Key](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/SenseCAPS2120/SenseCAP-S2120/Image/mobile.png)

---

### **2.4 Configuring MQTT Integration in TTN**
1. **Navigate to TTN Integration Settings**:
   - In the TTN Console, open your application and select **Integrations**.
2. **Select MQTT**:
   - Click **MQTT** from the available integration options.
3. **You’ll need these details to set up the MQTT integration in Blynk**:
   - **Server Address**
   - **Port**
   - **Username**
   - **Password**: Click **Generate new API key** and copy the generated key. Keep it secure.

![Key](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/SenseCAPS2120/SenseCAP-S2120/Image/integarion-mqtt-key.png)

   - In the **API Keys** section of the left menu, select the newly generated key.
   - Under **Rights**, select **Grant individual rights** and ensure the following permissions are enabled:
     - **View device keys in application**
     - **Create devices in application**
     - **Edit device keys in application**

![Key](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/SenseCAPS2120/SenseCAP-S2120/Image/edit-permition.png)

---

## **Step 3: Integrating TTN with Blynk**

### **3.1 Configuring Blynk Integration via MQTT**
1. **Click "Use Blueprint"** at the top of the blueprint page.
2. **Set Up MQTT in Blynk:**
   - Navigate to **Developer Zone** -> **Integrations** -> **The Things Stack** -> **Add**, and choose the template named **SenseCAP-S2120**.

![Key](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/SenseCAPS2120/SenseCAP-S2120/Image/add.png)

   - Enter the data from **Step 2:**
     - **Hostname:** MQTT server address with port `1883` or `8883` (e.g., `eu1.cloud.thethings.network:8883`)
     - **Username**
     - **Password:** The copied API key
   - Click **Connect**.

![Key](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/SenseCAPS2120/SenseCAP-S2120/Image/connect.png)

3. **Enable Automated Device Onboarding:**
   - Once connected, click **Edit** and toggle **Enable automated device onboarding**.
   - Specify the LoRaWAN version, frequency plan, and regional parameter version.
   - Enable "Support class B" and/or "Support class C" if required.
   - Specify The Things Stack component addresses (found under **Network Information** in the **Admin Panel**).
   - Save changes.

	![Key](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/SenseCAPS2120/SenseCAP-S2120/Image/advanced-complete.png)
---

## **Step 4: Onboarding the Sensor to Blynk**

1. Go to **Developer Zone** > **My Templates** > select **SenseCAP-S2120 Weather Station**, then click **Activate Device**.

![Key](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/SenseCAPS2120/SenseCAP-S2120/Image/dash-bp.png)

2. In the new window, enter the data provided in **Step 2.3:**
   - **Application Key**
   - **Join EUI**
   - **DevEUI**

![Key](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/SenseCAPS2120/SenseCAP-S2120/Image/sample-data.png)

3. Click **Next** and wait for the device to come online.

![Key](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/SenseCAPS2120/SenseCAP-S2120/Image/wait-for-dev.png)

---

## **Step 5: Monitoring and Analyzing Data**

### **5.1 Dashboard Overview**
The dashboard is preconfigured, providing an intuitive interface for real-time monitoring. Both web and mobile dashboards offer the same functionality.

![Key](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/SenseCAPS2120/SenseCAP-S2120/Image/img_1.png)

| Widget                 | Virtual Pin | Unit      |
|------------------------|-------------|-----------|
| Air Temperature        | V1          | °C        |
| Air Humidity           | V0          | %         |
| Barometric Pressure    | V2          | Pa        |
| Wind Speed             | V13         | m/s       |
| Wind Direction         | V12         | °         |
| Precipitation          | V9          | mm/h      |
| UV Index               | V11         | Index     |
| Light Intensity        | V7          | lux       |
| Battery Level          | V3          | %         |

---

### **5.2 Device Details Tab**

![Key](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/SenseCAPS2120/SenseCAP-S2120/Image/img_2.png)

| Widget                 | Virtual Pin | Description                        |
|------------------------|-------------|------------------------------------|
| Battery Level          | V3          | Shows remaining battery percent    |
| GPS Interval           | V5          | Reporting interval (if applicable) |
| Measurement Interval   | V8          | Current interval in seconds        |
| Set Interval           | V8          | Dropdown to update interval        |
| Firmware Version       | V4          | Version string                     |
| Hardware Version       | V6          | Version string                     |
| Reboot Device          | V10         | Remote reboot toggle               |

---

## **Step 6: Alerts & Automations**

1. Navigate to **Automations** in Blynk Console.
2. Choose **Device State** or **Sensor Value** triggers.
3. Example triggers:
   - **UV Index > 6** → send mobile notification
   - **Wind Speed > 10 m/s** → update dashboard label
4. Save and test automations.

---

## **Step 7: Adding Location in Blynk**

### **5.1 Configuring Location**
1. **Go to Location Section in Blynk**:
   - In the Blynk dashboard, navigate to the **Location** section.
2. **Add the Address**:
   - Enter the sensor's address or drag the pin on the map to the correct location.
   - Save the location.

![Key](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/SenseCAPS2120/SenseCAP-S2120/Image/location-2.png)

3. **Assign Location in Metadata**:
   - Navigate to device **Info & Metadata** in Blynk.
   - Assign the saved location to the device.

![Key](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/SenseCAPS2120/SenseCAP-S2120/Image/location-4.png)

🎥 **Watch the Video Guide for connect another LoraWAN device to Blynk**
[![Watch the video](https://img.youtube.com/vi/YbFF-Iec38w/maxresdefault.jpg)](https://youtu.be/YbFF-Iec38w)

## **Step 6: Error Handling and Troubleshooting**

### **6.1 Common Issues**
1. **Sensor Issues:**
   - Check battery polarity and charge
   - Reset the sensor if unresponsive
2. **Connectivity Problems:**
   - Verify LoRaWAN settings and gateway connection
   - Test MQTT integration
3. **Data Issues:**
   - Check the payload formatter in TTN
   - If only the battery level is displayed or data is missing, go to **TTN** > **Your Application** > **Payload Formatters** > **Uplink/Downlink**, update the code, and save changes

Uplink:
```
/**
 * Entry, decoder.js
 */
function decodeUplink (input, port) {
    // data split

    var bytes = input['bytes']
    // init
    bytes = bytes2HexString(bytes)
      .toLocaleUpperCase()

    let result = {
      'err': 0, 'payload': bytes, 'valid': true, messages: []
    }
    let result2 = []
    let splitArray = dataSplit(bytes)
    // data decoder
    let decoderArray = []
    for (let i = 0; i < splitArray.length; i++) {
      let item = splitArray[i]
      let dataId = item.dataId
      let dataValue = item.dataValue
      let messages = dataIdAndDataValueJudge(dataId, dataValue)
      decoderArray.push(...messages)
    }

    let output = {};

    // Merge each nested object from decoderArray into output
    for (let key in decoderArray) {
      Object.assign(output, decoderArray[key]);
    }

    return { data: output };

  }

  /**
   * data splits
   * @param bytes
   * @returns {*[]}
   */
  function dataSplit (bytes) {
    let frameArray = []

    for (let i = 0; i < bytes.length; i++) {
      let remainingValue = bytes
      let dataId = remainingValue.substring(0, 2)
      let dataValue
      let dataObj = {}
      switch (dataId) {
        case '01' :
        case '20' :
        case '21' :
        case '30' :
        case '31' :
        case '33' :
        case '40' :
        case '41' :
        case '42' :
        case '43' :
        case '44' :
        case '45' :
          dataValue = remainingValue.substring(2, 22)
          bytes = remainingValue.substring(22)
          dataObj = {
            'dataId': dataId, 'dataValue': dataValue
          }
          break
        case '02':
          dataValue = remainingValue.substring(2, 18)
          bytes = remainingValue.substring(18)
          dataObj = {
            'dataId': '02', 'dataValue': dataValue
          }
          break
        case '03' :
        case '06':
          dataValue = remainingValue.substring(2, 4)
          bytes = remainingValue.substring(4)
          dataObj = {
            'dataId': dataId, 'dataValue': dataValue
          }
          break
        case '05' :
        case '34':
          dataValue = bytes.substring(2, 10)
          bytes = remainingValue.substring(10)
          dataObj = {
            'dataId': dataId, 'dataValue': dataValue
          }
          break
        case '04':
        case '10':
        case '32':
        case '35':
        case '36':
        case '37':
        case '38':
        case '39':
          dataValue = bytes.substring(2, 20)
          bytes = remainingValue.substring(20)
          dataObj = {
            'dataId': dataId, 'dataValue': dataValue
          }
          break
        default:
          dataValue = '9'
          break
      }
      if (dataValue.length < 2) {
        break
      }
      frameArray.push(dataObj)
    }
    return frameArray
  }

  function dataIdAndDataValueJudge (dataId, dataValue) {
    let messages = []
    switch (dataId) {
      case '01':
        let temperature = dataValue.substring(0, 4)
        let humidity = dataValue.substring(4, 6)
        let illumination = dataValue.substring(6, 14)
        let uv = dataValue.substring(14, 16)
        let windSpeed = dataValue.substring(16, 20)
        messages = [{
            'Air Temperature': loraWANV2DataFormat(temperature, 10),
            'Air Humidity': loraWANV2DataFormat(humidity),
            'Light Intensity': loraWANV2DataFormat(illumination),
            'UV Index': loraWANV2DataFormat(uv, 10),
            'Wind Speed': loraWANV2DataFormat(windSpeed, 10)
          }]
          break
          case '02':
          let windDirection = dataValue.substring(0, 4);
          let rainfall = dataValue.substring(4, 12);
          let airPressure = dataValue.substring(12, 16);
          messages = [{
            'Wind Direction Sensor': loraWANV2DataFormat(windDirection),
            'Rain Gauge': loraWANV2DataFormat(rainfall, 1000),
            'Barometric Pressure': loraWANV2DataFormat(airPressure, 0.1)
          }]
          break
      case '03':
        let Electricity = dataValue
        messages = [{
          'Battery': loraWANV2DataFormat(Electricity)
        }]
        break
      case '04':
        let electricityWhether = dataValue.substring(0, 2)
        let hwv = dataValue.substring(2, 6)
        let bdv = dataValue.substring(6, 10)
        let sensorAcquisitionInterval = dataValue.substring(10, 14)
        let gpsAcquisitionInterval = dataValue.substring(14, 18)
        messages = [{
          'Battery': loraWANV2DataFormat(electricityWhether),
          'Hardware Version': `${loraWANV2DataFormat(hwv.substring(0, 2))}.${loraWANV2DataFormat(hwv.substring(2, 4))}`,
          'Firmware Version': `${loraWANV2DataFormat(bdv.substring(0, 2))}.${loraWANV2DataFormat(bdv.substring(2, 4))}`,
          'measureInterval': parseInt(loraWANV2DataFormat(sensorAcquisitionInterval)) * 60,
          'gpsInterval': parseInt(loraWANV2DataFormat(gpsAcquisitionInterval)) * 60
        }]
        break
      case '05':
        let sensorAcquisitionIntervalFive = dataValue.substring(0, 4)
        let gpsAcquisitionIntervalFive = dataValue.substring(4, 8)
        messages = [{
          'measureInterval': parseInt(loraWANV2DataFormat(sensorAcquisitionIntervalFive)) * 60,
          'gpsInterval': parseInt(loraWANV2DataFormat(gpsAcquisitionIntervalFive)) * 60
        }]
        break
      case '06':
        let errorCode = dataValue
        let descZh
        switch (errorCode) {
          case '00':
            descZh = 'CCL_SENSOR_ERROR_NONE'
            break
          case '01':
            descZh = 'CCL_SENSOR_NOT_FOUND'
            break
          case '02':
            descZh = 'CCL_SENSOR_WAKEUP_ERROR'
            break
          case '03':
            descZh = 'CCL_SENSOR_NOT_RESPONSE'
            break
          case '04':
            descZh = 'CCL_SENSOR_DATA_EMPTY'
            break
          case '05':
            descZh = 'CCL_SENSOR_DATA_HEAD_ERROR'
            break
          case '06':
            descZh = 'CCL_SENSOR_DATA_CRC_ERROR'
            break
          case '07':
            descZh = 'CCL_SENSOR_DATA_B1_NO_VALID'
            break
          case '08':
            descZh = 'CCL_SENSOR_DATA_B2_NO_VALID'
            break
          case '09':
            descZh = 'CCL_SENSOR_RANDOM_NOT_MATCH'
            break
          case '0A':
            descZh = 'CCL_SENSOR_PUBKEY_SIGN_VERIFY_FAILED'
            break
          case '0B':
            descZh = 'CCL_SENSOR_DATA_SIGN_VERIFY_FAILED'
            break
          case '0C':
            descZh = 'CCL_SENSOR_DATA_VALUE_HI'
            break
          case '0D':
            descZh = 'CCL_SENSOR_DATA_VALUE_LOW'
            break
          case '0E':
            descZh = 'CCL_SENSOR_DATA_VALUE_MISSED'
            break
          case '0F':
            descZh = 'CCL_SENSOR_ARG_INVAILD'
            break
          case '10':
            descZh = 'CCL_SENSOR_RS485_MASTER_BUSY'
            break
          case '11':
            descZh = 'CCL_SENSOR_RS485_REV_DATA_ERROR'
            break
          case '12':
            descZh = 'CCL_SENSOR_RS485_REG_MISSED'
            break
          case '13':
            descZh = 'CCL_SENSOR_RS485_FUN_EXE_ERROR'
            break
          case '14':
            descZh = 'CCL_SENSOR_RS485_WRITE_STRATEGY_ERROR'
            break
          case '15':
            descZh = 'CCL_SENSOR_CONFIG_ERROR'
            break
          case 'FF':
            descZh = 'CCL_SENSOR_DATA_ERROR_UNKONW'
            break
          default:
            descZh = 'CC_OTHER_FAILED'
            break
        }
        messages = [{
          measurementId: '4101', type: 'sensor_error_event', errCode: errorCode, descZh
        }]
        break
      case '10':
        let statusValue = dataValue.substring(0, 2)
        let { status, type } = loraWANV2BitDataFormat(statusValue)
        let sensecapId = dataValue.substring(2)
        messages = [{
          status: status, channelType: type, sensorEui: sensecapId
        }]
        break
      default:
        break
    }
    return messages
  }

  /**
   *
   * data formatting
   * @param str
   * @param divisor
   * @returns {string|number}
   */
  function loraWANV2DataFormat (str, divisor = 1) {
    let strReverse = bigEndianTransform(str)
    let str2 = toBinary(strReverse)
    if (str2.substring(0, 1) === '1') {
      let arr = str2.split('')
      let reverseArr = arr.map((item) => {
        if (parseInt(item) === 1) {
          return 0
        } else {
          return 1
        }
      })
      str2 = parseInt(reverseArr.join(''), 2) + 1
      return '-' + str2 / divisor
    }
    return parseInt(str2, 2) / divisor
  }

  /**
   * Handling big-endian data formats
   * @param data
   * @returns {*[]}
   */
  function bigEndianTransform (data) {
    let dataArray = []
    for (let i = 0; i < data.length; i += 2) {
      dataArray.push(data.substring(i, i + 2))
    }
    // array of hex
    return dataArray
  }

  /**
   * Convert to an 8-digit binary number with 0s in front of the number
   * @param arr
   * @returns {string}
   */
  function toBinary (arr) {
    let binaryData = arr.map((item) => {
      let data = parseInt(item, 16)
        .toString(2)
      let dataLength = data.length
      if (data.length !== 8) {
        for (let i = 0; i < 8 - dataLength; i++) {
          data = `0` + data
        }
      }
      return data
    })
    let ret = binaryData.toString()
      .replace(/,/g, '')
    return ret
  }

  /**
   * sensor
   * @param str
   * @returns {{channel: number, type: number, status: number}}
   */
  function loraWANV2BitDataFormat (str) {
    let strReverse = bigEndianTransform(str)
    let str2 = toBinary(strReverse)
    let channel = parseInt(str2.substring(0, 4), 2)
    let status = parseInt(str2.substring(4, 5), 2)
    let type = parseInt(str2.substring(5), 2)
    return { channel, status, type }
  }

  /**
   * channel info
   * @param str
   * @returns {{channelTwo: number, channelOne: number}}
   */
  function loraWANV2ChannelBitFormat (str) {
    let strReverse = bigEndianTransform(str)
    let str2 = toBinary(strReverse)
    let one = parseInt(str2.substring(0, 4), 2)
    let two = parseInt(str2.substring(4, 8), 2)
    let resultInfo = {
      one: one, two: two
    }
    return resultInfo
  }

  /**
   * data log status bit
   * @param str
   * @returns {{total: number, level: number, isTH: number}}
   */
  function loraWANV2DataLogBitFormat (str) {
    let strReverse = bigEndianTransform(str)
    let str2 = toBinary(strReverse)
    let isTH = parseInt(str2.substring(0, 1), 2)
    let total = parseInt(str2.substring(1, 5), 2)
    let left = parseInt(str2.substring(5), 2)
    let resultInfo = {
      isTH: isTH, total: total, left: left
    }
    return resultInfo
  }

  function bytes2HexString (arrBytes) {
    var str = ''
    for (var i = 0; i < arrBytes.length; i++) {
      var tmp
      var num = arrBytes[i]
      if (num < 0) {
        tmp = (255 + num + 1).toString(16)
      } else {
        tmp = num.toString(16)
      }
      if (tmp.length === 1) {
        tmp = '0' + tmp
      }
      str += tmp
    }
    return str
  }

```

Downlink:
```
function encodeDownlink(input) {
  const output = {
    bytes: [],
    fPort: 2,
    warnings: [],
    errors: []
  };

  // Check if the input has a "data" field and use that instead
  const commandInput = input.data ? input.data : input;

  // Predefined command mapping for "measureInterval" and "reboot" commands
  const commandMap = {
    measureInterval: {
      1: [0x00, 0x90, 0x00, 0x01, 0x00, 0x01, 0xA0, 0x05, 0x1E, 0x9A],
      5: [0x00, 0x90, 0x00, 0x05, 0x00, 0x01, 0xA0, 0x05, 0x0E, 0xB7],
      10: [0x00, 0x90, 0x00, 0x0A, 0x00, 0x01, 0xA0, 0x05, 0xF2, 0xDD],
      15: [0x00, 0x90, 0x00, 0x0F, 0x00, 0x01, 0xA0, 0x05, 0xA6, 0xFB],
      20: [0x00, 0x90, 0x00, 0x14, 0x00, 0x01, 0xA0, 0x05, 0x0A, 0x08],
      30: [0x00, 0x90, 0x00, 0x1E, 0x00, 0x01, 0xA0, 0x05, 0xA2, 0x44],
      60: [0x00, 0x90, 0x00, 0x3C, 0x00, 0x01, 0xA0, 0x05, 0xBB, 0x32]
    },
    reboot: [0x00, 0xC8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2B, 0x26]
  };

  try {
    // Handle "measureInterval" command
    if (commandInput.name === "measureInterval") {
      const intervalMinutes = commandInput.value / 60; // Convert seconds to minutes

      if (commandMap.measureInterval[intervalMinutes]) {
        output.bytes = commandMap.measureInterval[intervalMinutes];
      } else {
        output.errors.push("Invalid interval value: " + commandInput.value);
      }

    // Handle "reboot" command
    } else if (commandInput.name === "reboot") {
      output.bytes = commandMap.reboot;
    } else {
      output.errors.push("Unsupported command: " + JSON.stringify(commandInput));
    }
  } catch (err) {  // 'err' is the correct reference for the caught error
    output.errors.push("Encoding error: " + err.message + ". Input: " + JSON.stringify(commandInput));
  }

  return output;
}
function decodeDownlink(input) {
  return {
    data: {
      bytes: input.bytes
    },
    warnings: [],
    errors: []
  }
}

```

---

## **Next Steps**
- Explore the Blynk Web Console and IoT app to monitor sensor data
- Read the Blynk Documentation to learn about Virtual Pins
- [Learn how to Share Devices with other users](https://docs.blynk.io/en/blynk.console/devices/device-sharing)
- Customize the code to meet your specific needs
- Try onboarding the sensor using static tokens

---


