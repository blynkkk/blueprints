# **SenseCAP S2120 8-in-1 LoRaWAN Weather Sensor Blueprint Guide**

This guide explains how to set up the **SenseCAP S2120 8-in-1 LoRaWAN Weather
Sensor**, register it with **The Things Network (TTN)**, and integrate it with
**Blynk IoT** for data visualization and control.

## **How to Use This Blueprint**

### **Step 1: Unpacking and Initial Setup**

#### **1.1 Required Components**

- **SenseCAP S2120 8-in-1 LoRaWAN Weather Sensor**:
  Measures air temperature, humidity, wind speed/direction, rainfall, UV index, barometric pressure, and light intensity.
- **LoRaWAN Gateway**:
  Connects the sensor to TTN.
- **Antenna**:
  Required for wireless communication.
- **Power Supply**:
  Includes three 1.5V AA batteries and a 0.5W solar panel. Optionally, use an external battery box with six AA batteries.
- **Mounting Accessories**:
  Includes clamps, screws, and a pole stand for secure installation.

#### **1.2 Initial Setup**

1. **Unpack Components**:
   - Ensure all items are present and undamaged.

2. **Attach Antenna**:
   - Connect the antenna securely to the sensor.

3. **Install Batteries**:
   - Insert three 1.5V AA batteries (check polarity). For extended use, connect the external battery box.

4. **Power On the Sensor**:
   - The sensor powers on automatically when batteries are inserted.

5. **Mount the Sensor**:
   - Position the sensor in an open area. Use a compass to align the **North (N)** marker for accurate wind direction measurements.

### **Step 2: Configuring the Sensor Using SenseCAP Mate App**

#### **Steps for Configuration**:

1. **Download the SenseCAP Mate App**:
   - Install the app from the [Google Play
   Store](https://play.google.com/store/apps/details?id=com.seeedstudio.sensecap)
   or [Apple App Store](https://apps.apple.com/app/sensecap-mate/id1520727287).

2. **Pair the Sensor**:
   - Enable Bluetooth on your smartphone.
   - Open the app and scan for available devices.
   - Select the SenseCAP S2120 sensor from the list.

3. **Configure LoRaWAN Parameters**:
   - Navigate to **LoRaWAN Settings** in the app.
   - Enter the following:
     - **DevEUI**: Found on the sensor label.
     - **AppEUI**: Provided by TTN or the sensor documentation.
     - **AppKey**: Provided in the sensor documentation.
   - Select the appropriate **Frequency Plan** for your region (e.g., EU868, US915).
   - Save the settings.

4. **Set Measurement Intervals (Optional)**:
   - Adjust the **Measurement Interval** and **GPS Interval** for your specific application needs.

5. **Verify Configuration**:
   - Check the app for the sensor’s connection status and ensure all settings are applied correctly.

### **Step 3: Registering the Sensor on The Things Network (TTN)**

#### **3.1 Create a New Application**

1. **Log in to TTN Console**:
   - Visit the [TTN Console](https://console.cloud.thethings.network/) and log in.

2. **Create an Application**:
   - Navigate to **Applications** > **Add Application**.
   - Fill in the following fields:
     - **Application ID**: Enter a unique name for the application (e.g., `sensecap-weather-station`).
     - **Description**: Optionally add a description (e.g., `Weather sensor for monitoring environmental parameters`).
     - **Handler**: Select the appropriate handler for your region (e.g., `eu1.cloud.thethings.network` for Europe).
   - Click **Create Application** to save and register your new application.

#### **3.2 Add the Sensor as an End Device**

1. **Navigate to the Application**:
   - Open the application you just created.

2. **Add an End Device**:
   - Click **Add End Device** and select **Manually**.

3. **Provide Device Details**:
   - Input the following:
     - **DevEUI**: Found on the sensor label.
     - **AppEUI**: Use the AppEUI associated with your application or sensor documentation.
     - **AppKey**: Use the AppKey provided with your sensor documentation.

4. **Select Frequency Plan**:
   - Choose the frequency plan configured for your region (e.g., **EU868** or **US915**).

5. **Save and Register**:
   - Click **Register End Device** to complete the setup.

#### **3.3 Add a Custom Uplink Payload Formatter**

1. **Navigate to Payload Formatters**:
   - In the TTN Console, open your device’s settings and go to **Payload Formatters** > **Uplink**.

2. **Enter the Formatter Code**:

```javascript
function decodeUplink(input) {
    var data = {};
    data.temperature = input.bytes[0] / 10;
    data.humidity = input.bytes[1];
    data.wind_speed = input.bytes[2] / 10;
    data.wind_direction = input.bytes[3] * 1.5;
    data.pressure = (input.bytes[4] << 8 | input.bytes[5]) / 10;
    data.uv_index = input.bytes[6];
    data.light_intensity = input.bytes[7] * 1000;
    return {
        data: data,
    };
}
```

3. **Save the Formatter**:
   - Click **Save Changes** to activate the formatter.

4. **Verify Uplink Data**:
   - Go to the **Live Data** tab in TTN to ensure decoded data is visible.

### **Step 4: Integrating TTN with Blynk**

#### **4.1 Configure MQTT Integration in TTN**

1. **Set Up MQTT Integration**:
   - Navigate to **Integrations** in your TTN application.
   - Click **Add Integration** > **MQTT**.

2. **Copy Integration Details**:
   - Copy the following fields for use in Blynk:
     - **Server Address**: e.g., `eu1.cloud.thethings.network`.
     - **Port**: Use `1883` (unsecured) or `8883` (secured).
     - **Username**: Your TTN **AppID**.
     - **Password**: Generate an MQTT API key in TTN and copy it.

#### **4.2 Configure TTN Integration in Blynk**

1. **Log in to Blynk Console**:
   - Access the [Blynk Console](https://blynk.cloud).

2. **Use the Blueprint**:
   - Navigate to **Blueprints** and select **SenseCAP S2120 Weather Sensor Blueprint**.

3. **Add TTN Integration**:
   - Go to **Integrations** > **Add Integration**.
   - Select **The Things Stack** and fill in the following:
     - **Integration Name**: SenseCAP-TTN.
     - **Server Address**: Paste the TTN MQTT server address.
     - **Port**: Use `1883` or `8883`.
     - **Username**: Enter your TTN **AppID**.
     - **Password**: Use the MQTT API key.

4. **Map Datastreams**:
   - Match TTN payload fields (e.g., temperature, wind speed) to Blynk datastreams.

5. **Save and Activate**:
   - Save the configuration to start receiving data.

### **Step 5: Monitoring and Controlling the Sensor**

1. **Real-Time Data Visualization**:
   - Access the Blynk dashboard to monitor temperature, humidity, wind speed, rainfall, and more.

2. **Send Downlink Commands**:
   - Adjust measurement intervals or reboot the device using Blynk controls.

3. **Analyze Historical Data**:
   - Use Blynk’s graph widgets to review trends over time.


