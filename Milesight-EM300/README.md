## **Milesight EM300 - Water Leak Detector Blueprint Guide**

The **Milesight EM300 Water Leak Detector** monitors and detects water leaks in
various environments, providing real-time alerts to prevent damage. It also
monitors battery levels and RSSI for reliable operation. This guide provides
step-by-step instructions to set up the sensor, register it with **The Things
Network (TTN)**, and integrate it with **Blynk IoT** for data visualization and
control.

## **Step 1: Unpacking and Initial Setup**

### **1.1 Required Components**
- **Milesight EM300 Water Leak Detector**
- **LoRaWAN Gateway** for connectivity

### **1.2 Initial Setup**
1. **Verify Package Contents:** Make sure all components are included and undamaged.
2. **Install the Batteries:** Insert the batteries into the sensor, ensuring the correct polarity.
3. **Power On the Sensor:** Hold the power button for 3 seconds. The LED will confirm activation.

## **Step 2: Prepare The Things Network (TTN) for integration**

### **2.1 Setting Up the LoRaWAN Gateway**

1. **Log in to the TTN Console:** Visit the [TTN Console](https://console.cloud.thethings.network/).
2. **Add a Gateway:**
   - Navigate to **Gateways** > **Add Gateway**.
   - Enter:
     - **Gateway EUI** (found on the gateway label)
     - **Gateway ID** (e.g., `my-lorawan-gateway`)
     - **Frequency Plan** for your region (see the table below)
   - Click **Register Gateway**.
3. **Configure the Gateway:**
   - Follow the manufacturer's instructions to connect the gateway to TTN.
   - Ensure the gateway is online and visible in the TTN Console.

![App](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/Milesight-EM300/Images/gateway.png)

**Frequency Plans**
| **Frequency Plan** | **Region**            | **Description**                                                                 |
|--------------------|-----------------------|---------------------------------------------------------------------------------|
| **EU868**          | Europe                | Operates at 868 MHz. Commonly used across the EU for LoRaWAN deployments.       |
| **US915**          | North America         | Operates at 915 MHz. Used in the United States, Canada, and Mexico.             |
| **AS923**          | Asia-Pacific          | Operates at 923 MHz. Covers countries like Japan, Australia, and New Zealand.   |
| **IN865**          | India                 | Operates at 865 MHz. Dedicated plan for deployments in India.                   |
| **AU915**          | Australia/New Zealand | Operates at 915 MHz. Preferred for LoRaWAN in Australia and New Zealand.        |
| **KR920**          | South Korea           | Operates at 920 MHz. Allocated specifically for South Korea.                    |
| **RU864**          | Russia                | Operates at 864 MHz. Used exclusively within Russia.                            |

### **2.2 Creating a New Application**
1. **Log in to TTN Console**.
2. **Create an Application:**
   - Navigate to **Applications** > **Add Application**.
   - Enter:
     - **Application ID**: A unique name (e.g., `water-leak-monitor`).
     - **Description**: (e.g., `Monitoring water leaks in critical areas`).
   - Click **Create Application**.

![App](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/Milesight-EM300/Images/create-form.png)

> **Note:**
> To ensure smooth operation, it’s recommended that all devices within a TTN
> application are of the same sensor type (e.g., EM300). If you’d like to use
> different types of sensors, consider creating a separate application for each
> sensor type. This helps maintain better compatibility and performance.

### **2.3 Setting Up the Payload Formatter in the TTN Application**

1. Open the created application and, from the left-hand menu, select **Payload Formatters**.

![Formater](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/Milesight-EM300/Images/formater.png)

2. Select the **Uplink** tab and choose **Custom JavaScript Formatter**.
3. Paste the following formatter code and click **Save Changes**:

```javascript
function decodeUplink(input) {
    var res = Decoder(input.bytes, input.fPort);
    if (res.error) {
        return {
            errors: [res.error],
        };
    }
    return {
        data: res,
    };
}
/**
 * Payload Decoder for The Things Network
 *
 * Copyright 2021 Milesight IoT
 *
 * @product EM300-SLD / EM300-ZLD
 */
function Decoder(bytes, port) {
    var decoded = {};

    for (var i = 0; i < bytes.length;) {
        var channel_id = bytes[i++];
        var channel_type = bytes[i++];
        // BATTERY
        if (channel_id === 0x01 && channel_type === 0x75) {
            decoded.battery = bytes[i];
            i += 1;
        }
        // TEMPERATURE
        else if (channel_id === 0x03 && channel_type === 0x67) {
            // ℃
            decoded.temperature = readInt16LE(bytes.slice(i, i + 2)) / 10;
            i += 2;

            // ℉
            // decoded.temperature = readInt16LE(bytes.slice(i, i + 2)) / 10 * 1.8 + 32;
            // i +=2;
        }
        // HUMIDITY
        else if (channel_id === 0x04 && channel_type === 0x68) {
            decoded.humidity = bytes[i] / 2;
            i += 1;
        }
        // WATER LEAK
        else if (channel_id === 0x05 && channel_type === 0x00) {
            decoded.water = (bytes[i] === 0) ? 0 : 1;
            i += 1;
        } else {
            break;
        }
    }

    return decoded;
}

/* ******************************************
 * bytes to number
 ********************************************/
function readUInt16LE(bytes) {
    var value = (bytes[1] << 8) + bytes[0];
    return value & 0xffff;
}

function readInt16LE(bytes) {
    var ref = readUInt16LE(bytes);
    return ref > 0x7fff ? ref - 0x10000 : ref;
}

```

### **2.4 Pairing the Sensor with the TTN Application**
1. **[Download and install Milesight ToolBox App](https://www.milesight.com/iot/resources/download-center/#milesight-toolbox)**

2. **Open the Milesight ToolBox App**:
   - Pair the sensor via NFC.
   - Navigate to **Settings** -> **LoRaWAN Settings**.

![App](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/Milesight-EM300/Images/mobile-2.png)

3. **Configure LoRaWAN Parameters**:
   - **DevEUI**: Use the default value (found on the sensor label).
   - **AppEUI**: Use the manufacturer’s default value or generate a new one.
   - **AppKey**: Use the manufacturer’s default or generate a new one.
   - **Frequency Plan**: Match the frequency plan configured in TTN.
   - **RX2 Data Rate**: Set to DR3 (SF9, 125 kHz).
   - **Spreading Factor**: Set to SF10-DR2.
   - **Default Application Port**: Set to 85.
   - Use the **Write** button to save these settings via NFC.

![Key](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/Milesight-EM300/Images/mobile.png)

### **2.5 Adding the Sensor as an End Device in TTN console**

1. Open the TTN console, select your application (created in step 2.2) and click **Register End Device**.
2. From the LoRaWAN Device Repository:
   - **Brand**: Milesight
   - **Model**: EM300-ZLD
   - **Hardware/Firmware Version**: Use the latest version if unsure
   - **Profile/Region**: Based on the Frequency Plan table above

![End dev](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/Milesight-EM300/Images/end-dev-1.png)

3. Enter:
   - **DevEUI**, **JoinEUI (AppEUI)**, and **AppKey** from Step 2.4
   - A unique **End Device ID**
4. Click **Register Device**

![End dev](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/Milesight-EM300/Images/end-dev-2.png)

### **2.6 Configuring MQTT Integration in TTN**
1. **Navigate to TTN Integration Settings**:
   - In the TTN Console, open your application and select **Integrations**.
2. **Select MQTT**:
   - Click **MQTT** from the available integration options.
3. **You’ll need these details to set up the MQTT integration in Blynk**:
   - **Server Address**
   - **Port**
   - **Username**
   - **Password**: Click **Generate new API key** and copy the generated key. Copy and keep it secure.

![Key](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/Milesight-EM300/Images/integarion-mqtt-key.png)

## **Step 3: Prepare Blynk side for integration**

1. **Click "Use Blueprint"** at the top of the EM300 blueprint page.
2. **Set Up MQTT in Blynk:**
   - Navigate to **Developer Zone** -> **Integrations** -> **The Things Stack** -> **Add**, and choose the template named **Milesight EM300 ZLD**.

![Add intefration](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/Milesight-EM300/Images/add.png)

  - Enter the data from step 2.6:
     - **Hostname:** MQTT server address with port `1883` or `8883` (e.g., `eu1.cloud.thethings.network:8883`)
     - **Username**
     - **Password:** The copied API key
   - Click **Connect**.

![Connect](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/Milesight-EM300/Images/connect.png)


## **Step 4: Onboarding the Sensor to Blynk**

You can onboard the sensor in two ways:

1. **Automatic Device Creation – Recommended**
   As soon as the sensor sends data to TTN, it will automatically appear on the Blynk Cloud.

![dev online](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/Milesight-EM300/Images/dev-online.png)

2. **Manual Device Creation – If Something Goes Wrong**
   - Navigate to **Devices** → **Create Device**, and select the **Milesight-EM300** template.
   - In the **Info & Metadata** tab, enter the **TheThingsNetwork Device** field using the device name from TTN.

![TTN-dev](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/Milesight-EM300/Images/ttn-dev.png)
![TTN-dev](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/Milesight-EM300/Images/ttn-dev-in-ttn.png)
![TTN-dev](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/Milesight-EM300/Images/ttn-dev-fill.png)

## **Step 5: Monitoring and Analyzing Data**

**Dashboard Overview**
The dashboard is preconfigured, providing an intuitive interface for real-time monitoring. Both web and mobile dashboards offer the same functionality.

At the top of the dashboard, users can view the device name, online status, and last known location, with options to add location tags for better organization. A green **Online** indicator confirms active connectivity. If water is detected, a red alert banner appears and remains visible until the condition is resolved. Beneath the alert, the **Water Status History** bar provides a timeline, with green indicating dry periods and red marking water detection events.

The dashboard also displays the device’s **battery level**, with replacement or recharge recommended below 20% to ensure continuous operation. Current **humidity** and **temperature** readings are shown to monitor environmental conditions, and historical graphs are available for trend analysis. Users can adjust the displayed timeframe from **Live** up to **one year**. Device settings, such as reporting intervals and thresholds, can be modified via the **Edit** button.

Regularly checking the device’s connection, battery status, and water detection alerts is essential for maintaining reliable performance and timely incident response.

![dev online](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/Milesight-EM300/Images/dev-online-2.png)

## **Step 6: Alerts & Automations**

1. In the Blynk Console, open **Automations**.
2. Create triggers based on **Device State** or **Sensor Value**.
   - Example: `water == 1` → Send notification
   - Example: `Temperature < 10` → Update dashboard label

## **Step 7: Adding Location in Blynk**

1. Navigate to the **Location** section in Blynk.
2. Enter the address or drag the map pin to the correct location.

![Location](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/Milesight-EM300/Images/location-2.png)

3. Click **Save**.
4. In the device's **Info & Metadata**, assign the saved location.

![Location](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/Milesight-EM300/Images/location-3.png)
![Location](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/Milesight-EM300/Images/location-3.2.png)
![Location](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/Milesight-EM300/Images/location-4.png)

## **Step 8: Error Handling and Troubleshooting**

- **Sensor Not Responding**: Check battery orientation and charge. Try a reset.
- **No Connectivity**: Recheck gateway setup and frequency plan.
- **Missing Data**: Update your **Payload Formatter** in TTN’s Uplink/Downlink settings.

## **Next Steps**
- Explore the Blynk Web Console and mobile app.
- Review [Blynk’s Virtual Pins documentation](https://docs.blynk.io/en/blynk.console/templates/datastreams).
- [Share devices with other users](https://docs.blynk.io/en/blynk.console/devices/device-sharing).
- Customize the integration for your own use case.
- Try onboarding the sensor using static tokens.
