# **Multi-Connectivity IoT Starter with Blues Notecard**

A single firmware, three-connectivity-type demo — Cellular, Wi-Fi, and LoRaWAN — powered by Blues Notecard and fully integrated with Blynk IoT. Includes a real-world setup with identical units deployed in the lab, in the field, and on the move. Tracks temperature, voltage, pressure, door status, and signal strength — with alerts and bi-directional control. Perfect for testing or deploying multi-network IoT solutions with zero backend setup.

## **Step 1: Understanding the Hardware Architecture**

### **1.1 Core Components (Identical for All Three Devices)**
- **Blues Notecarrier F** - Main development board with Feather-compatible slot
- **Blues Swan (STM32-based)** - Feather-compatible host microcontroller
- **LiPo Battery** - Power source for portable operation
- **Reed Switch** - Door open/close detection sensor
- **SparkFun BMP581 Sensor** - Temperature and barometric pressure measurement (Qwiic connection)

### **1.2 Variable Components (Different Notecard Types)**
- **Notecard Cellular** - For cellular network connectivity
- **Notecard Wi-Fi** - For Wi-Fi network connectivity
- **Notecard LoRa** - For LoRaWAN network connectivity

### **1.3 Physical Installation**
1. **Mount the reed switch** on the refrigerator door frame
2. **Place the BMP581 sensor** inside the refrigerator for accurate temperature readings
3. **Position the main device** externally for optimal connectivity
4. **Ensure proper antenna placement** based on the Notecard type being used

The main carrier/development board is the Notecarrier F (1). It has a slot for a Feather-compatible host (in this case the STM32-based Blues Swan) (2). The Notecarrier's power source is a small LiPo battery (3). The Notecard (4) is what can be swapped out for Cellular, Wi-Fi, or LoRa.

![Hardware Setup](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/blues/Images/hw-setup.png)

## **Step 2: Setting Up Blues Notehub**

### **2.1 Creating Your Notehub Project**
1. **Sign up for Notehub** at [notehub.io](https://notehub.io/)
2. **Create a New Project**:
   - Project Name: `Multi-Connectivity IoT Starter`
   - Note the **Product UID** - you'll need this for device configuration

![Notehub Project](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/blues/Images/nodehub.png)

### **2.2 Getting Notehub API Credentials for Blynk Integration**
You'll need these credentials later for the Blynk integration:

1. **In your Notehub project**, go to **Settings** → **Programmatic API access**
2. **Copy the Client ID** (format: `e50cbb73-2074-4c03-9b3f-35140f850d6e`)
3. **Generate a Client Secret**:
   - Click **Generate** button
   - **Copy the secret immediately** (it won't be displayed again)
   - Store it securely for the Blynk integration

![Notehub API Access](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/blues/Images/key.png)
![Notehub API Access](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/blues/Images/key-2.png)


### **2.3 Understanding Note Templates**
Note templates optimize data transmission, especially for LoRa which is bandwidth-constrained. Two templates are required:

**Sensor Data Template** (`fridge_sensors.qo`):
```json
{
  "voltage": 12.1,
  "temperature": 12.1,
  "pressure": 12,
  "bars": 12,
  "door_status": true,
  "_lat": 14.1,
  "_lon": 14.1
}
```

**Alert Template** (`fridge_alert.qo`):
```json
{
  "alert": true
}
```

![Notehub Template](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/blues/Images/event-alert.png)

## **Step 3: Firmware Configuration**

### **3.1 Download and Setup**
1. [**Download the complete firmware**](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/blues/blues/Firmware)
2. **Install required libraries**:
   - `note-arduino` SDK
   - `SparkFun BMP581 Arduino Library`
   - Standard Arduino libraries for I2C communication

### **3.2 Key Configuration Constants**
```cpp
// Update these values in your firmware
const char* PRODUCT_UID = "your-notehub-product-uid";
const char* WIFI_SSID = "your-wifi-network";
const char* WIFI_PASSWORD = "your-wifi-password";

// Timing constants
const unsigned long sensorReadPeriod = 30000; // 30 seconds default
const unsigned long doorOpenAlertPeriod = 10000; // 10 seconds
```

### **3.3 Universal Firmware Approach**
The beauty of this project is using **identical firmware** across all three radio types. The Notecard automatically handles radio-specific commands:

```cpp
// This works for all Notecard types
J *req = notecard.newRequest("hub.set");
JAddStringToObject(req, "product", PRODUCT_UID);
JAddStringToObject(req, "mode", "continuous");
JAddBoolToObject(req, "sync", true);
notecard.sendRequestWithRetry(req, 5);

// Wi-Fi config - ignored by Cellular and LoRa Notecards
req = notecard.newRequest("card.wifi");
JAddStringToObject(req, "ssid", WIFI_SSID);
JAddStringToObject(req, "password", WIFI_PASSWORD);
notecard.sendRequest(req);
```

## **Step 4: Sensor Data Collection**

### **4.1 Battery Voltage Monitoring**
```cpp
// Get battery voltage from Notecard
J *req = notecard.newRequest("card.voltage");
J *rsp = notecard.requestAndResponse(req);
double voltage = JGetNumber(rsp, "value");
```

### **4.2 Cellular Signal Strength (Cellular Only)**
```cpp
// Get signal strength (bars) for cellular Notecard
req = notecard.newRequest("card.wireless");
rsp = notecard.requestAndResponse(req);
int bars = JGetInt(rsp, "bars");
```

### **4.3 Environmental Sensors**
```cpp
// Read temperature and pressure from BMP581
float temperature = bmp581.getTemperature();
float pressure = bmp581.getPressure();

// Read door status from reed switch
bool door_open = digitalRead(REED_SWITCH_PIN);
```

### **4.4 Data Transmission**
```cpp
// Send sensor data to Notehub
J *req = notecard.newRequest("note.add");
JAddStringToObject(req, "file", "fridge_sensors.qo");
JAddBoolToObject(req, "sync", true);
J *body = JAddObjectToObject(req, "body");
JAddNumberToObject(body, "voltage", voltage);
JAddNumberToObject(body, "temperature", temperature);
JAddNumberToObject(body, "pressure", pressure);
JAddNumberToObject(body, "bars", bars);
JAddBoolToObject(body, "door_status", door_open);
notecard.sendRequest(req);
```

## **Step 5: Door Alert System**

### **5.1 Alert Logic**
The system monitors door status and sends alerts when doors are left open beyond the threshold:

```cpp
if (door_open && !alert_sent &&
    currentMillis - startMillisAlert >= doorOpenAlertPeriod) {

    J *req = notecard.newRequest("note.add");
    JAddStringToObject(req, "file", "fridge_alert.qo");
    JAddBoolToObject(req, "sync", true);
    J *body = JAddObjectToObject(req, "body");
    JAddBoolToObject(body, "alert", true);
    notecard.sendRequest(req);

    alert_sent = true;
}
```

### **5.2 SMS Notifications (Optional)**
Follow the [Blues Twilio SMS Guide](https://dev.blues.io/guides-and-tutorials/twilio-sms-guide/) to set up automatic SMS alerts when doors are left open.

## **Step 6: Blynk Integration Setup**

### **6.1 Using the Pre-Built Multi-Connectivity IoT Starter Template**

#### **6.1.1 Access the Blueprint Template**
1. **Click "Use Blueprint"** at the top of this Multi-Connectivity IoT Starter blueprint page
2. The **Multi-Connectivity IoT Starter** will be automatically added to your Blynk account

![Use Blueprint Button](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/blues/Images/use-bp.png)

#### **6.1.2 Template Overview**
The pre-built template includes:

**Pre-configured Datastreams:**
- **V0**: Battery Voltage (0-5V)
- **V1**: Temperature (-20 to 50°C)
- **V2**: Pressure (800-1200 hPa)
- **V3**: Signal Bars (0-5 bars)
- **V4**: Door Status (0=closed, 1=open)
- **V5**: Sync Frequency (10-300 seconds)
- **V6**: Alert Status (0=normal, 1=alert)

**Pre-designed Dashboard Widgets:**
- Battery voltage gauge with color coding
- Temperature gauge with freeze warnings
- Signal strength indicator (cellular only)
- Door status LED indicator
- Real-time alert banner
- Historical charts for trends
- Bi-directional sync frequency slider

![Blynk Template Overview](https://blueprint-assets.nyc3.cdn.digitaloceanspaces.com/blues/screenshot-2.png)

### **6.2 Set Up Blues Integration in Blynk**
1. **Navigate to Integrations** in your Blynk Console
2. **Click "Add New Integration"**
3. **Select "Blues"** from the available integrations
4. **Configure the Blues Integration**:

   **Connection Settings:**
   - **CLIENT ID**: Copy from your Notehub project settings (from Step 2.2)
     - Go to your Notehub project → **Settings** → **Programmatic API access**
     - Copy the **Client ID** (format: `e50cbb73-2074-4c03-9b3f-35140f850d6e`)

   - **CLIENT SECRET**: Generate in Notehub (from Step 2.2)
     - In the same **Programmatic API access** section
     - Click **Generate** to create a new client secret
     - Copy the generated secret immediately (it won't be shown again)

   **Data Mapping:**
   - The integration will automatically map Blues Products with Blynk Templates
   - Select your **Multi-Connectivity IoT Starter** template for data mapping

![Blues Integration Setup](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/blues/Images/integration.png)
![Blues Integration Setup](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/blues/Images/integration-2.png)

5. **Click "Connect"** to establish the integration
6. **Verify Connection**: The status should show "Connected" with a green indicator

![Blues Integration Setup](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/blues/Images/integration-3.png)

> **Note**: If you see "Broken" status, double-check that:
> - Your Client ID and Client Secret are correct
> - Your Notehub project has devices sending data
> - The API access is properly configured in Notehub

### **6.3 Data Mapping Configuration**
Once the Blues integration is connected, configure the data mapping:

1. **In the Data Mapping section**, you'll see your Notehub products
2. **Map your product** to the **Multi-Connectivity IoT Starter** template
3. **The mapping will automatically handle**:
   - Device creation from Notehub device names
   - Data routing from Notes to Blynk datastreams
   - Bi-directional communication for remote configuration

![Data Mapping](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/blues/Images/data-mapping.png)

### **6.4 Verify Integration**
1. **Check Integration Status**: Should show "Connected"
2. **Monitor Data Flow**:
   - Send test data from your Notecard
   - Verify data appears in Blynk devices
   - Check that all datastreams are receiving values correctly

> **Troubleshooting**: If integration shows "Broken":
> - Verify Client ID and Secret are correct
> - Ensure your Notehub project has active devices
> - Check that devices are sending the expected Note files (`fridge_sensors.qo`, `fridge_alert.qo`)

## **Step 7: Device Management and Monitoring**

### **7.1 Automatic Device Creation**
With the Blues integration properly configured, devices will be automatically created in Blynk when they first send data:

1. **Devices appear automatically** when Notecards send their first Notes
2. **Device names** match the Notecard device names from Notehub:
   - `Cellular Fridge`
   - `WiFi Fridge`
   - `LoRa Fridge`
3. **All datastreams** are automatically populated with sensor data

![Automatic Device Creation](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/blues/Images/devices.png)

### **7.2 Manual Device Creation (If Needed)**
If automatic creation doesn't work, you can manually create devices:

1. **Navigate to Devices** in Blynk Console
2. **Click "New Device"**
3. **Select "From Template"** → **"Multi-Connectivity IoT Starter"**
4. **Enter device details**:
   - **Device Name**: Match your Notehub device name exactly
   - **Auth Token**: Will be auto-generated
5. **Save the device**

### **7.3 Dashboard Overview**
The pre-built dashboard provides comprehensive monitoring capabilities:

**Real-time Monitoring:**
- **Battery voltage gauge** with color-coded warnings
- **Temperature display** with freeze alerts
- **Signal strength indicator** (cellular devices only)
- **Door status LED** (green=closed, red=open)
- **Alert banner** appears when door left open too long

**Historical Data:**
- **Temperature trends** over time
- **Battery discharge patterns**
- **Door opening frequency** analysis
- **Signal quality history** (cellular devices)

**Interactive Controls:**
- **Sync frequency slider** to adjust data transmission rate
- **Time range selectors** for historical charts
- **Device selection** to switch between multiple fridges

![Blynk Dashboard Overview](https://blueprint-assets.nyc3.cdn.digitaloceanspaces.com/blues/screenshot-2.png)
![Blynk Dashboard Overview](https://blueprint-assets.nyc3.cdn.digitaloceanspaces.com/blues/screenshot-3.png)

## **Step 8: Bi-Directional Communication**

### **8.1 Understanding Inbound Data**
Blynk can send configuration changes back to your devices through the Blues integration. This creates inbound Notes (`.qi` files) that your firmware can process.

### **8.2 Remote Configuration Updates**
The bi-directional communication allows you to:

1. **Adjust sync frequency** from the Blynk dashboard
2. **Update sensor thresholds** remotely
3. **Enable/disable features** without firmware updates
4. **Send commands** for diagnostic purposes

### **8.3 Processing Configuration Updates in Firmware**
```cpp
void updateSensorCadence() {
    // Check for inbound data from Blynk that will set the sensor cadence
    J *req = notecard.newRequest("file.changes");
    J *files = JAddArrayToObject(req, "files");
    JAddItemToArray(files, JCreateString("blynk.qi"));

    J *rsp = notecard.requestAndResponse(req);
    int total = JGetNumber(rsp, "total");

    if (total > 0) {
        // Get and process the inbound note
        req = notecard.newRequest("note.get");
        JAddStringToObject(req, "file", "blynk.qi");
        JAddBoolToObject(req, "delete", true);

        rsp = notecard.requestAndResponse(req);
        J *body = JGetObject(rsp, "body");

        if (JGetNumber(body, "Sync Freq")) {
            sensorReadPeriod = 1000 * JGetNumber(body, "Sync Freq");
        }
    }
}
```

## **Step 9: Device Deployment and Testing**

### **9.1 Device Identification**
Set unique device names in Notehub for easy identification:
- `Cellular Fridge`
- `Wi-Fi Fridge`
- `LoRa Fridge`

### **9.2 Testing Connectivity**
1. **Cellular Device**: Verify cellular connection and signal strength reporting
2. **Wi-Fi Device**: Confirm Wi-Fi network connection and data transmission
3. **LoRa Device**: Ensure LoRaWAN gateway connectivity and template optimization

### **9.3 Sensor Calibration**
1. **Temperature accuracy**: Compare BMP581 readings with known reference
2. **Door sensor**: Test reed switch positioning for reliable open/close detection
3. **Battery monitoring**: Verify voltage readings match actual battery levels

## **Step 10: Advanced Features and Monitoring**

### **10.1 Location Tracking**
For cellular devices, automatic location data is included:
- **Cell tower triangulation** provides approximate location
- **Timezone detection** for accurate timestamps
- **Country and region identification**

### **10.2 Data Analytics**
Monitor key metrics in Blynk:
- **Average door opening frequency**
- **Temperature trend analysis**
- **Battery discharge patterns**
- **Connectivity reliability** across different radio types

### **10.3 Maintenance Alerts**
Set up additional automations for:
- **Low battery warnings** (< 3.3V)
- **Temperature threshold alerts** (freezer too warm)
- **Connectivity loss notifications**
- **Extended door-open incidents**

## **Step 11: Troubleshooting and Optimization**

### **11.1 Common Issues**
- **No data transmission**: Check Notehub Product UID and network connectivity
- **Inaccurate temperature**: Verify BMP581 sensor placement and calibration
- **Missed door events**: Adjust reed switch positioning and debounce logic
- **Short battery life**: Optimize sensor reading frequency and sleep modes

### **11.2 Performance Optimization**
- **LoRa optimization**: Use templates and minimize payload size
- **Cellular data management**: Monitor data usage to stay within 500MB limit
- **Battery optimization**: Implement deep sleep between sensor readings
- **Alert optimization**: Prevent alert flooding with proper state management

### **11.3 Scaling Considerations**
- **Multiple refrigerators**: Use fleet management in Notehub
- **Different sensor types**: Expand template to include additional sensors
- **Custom alerts**: Implement complex alert logic based on multiple conditions
- **Integration expansion**: Connect to additional cloud platforms as needed

## **Step 12: Security and Best Practices**

### **12.1 Security Features**
- **Device authentication**: Automatic secure pairing with Notehub
- **Data encryption**: All transmissions encrypted by default
- **Certificate management**: Handled automatically by Blues infrastructure

### **12.2 Best Practices**
- **Regular firmware updates**: Keep note-arduino SDK updated
- **Battery maintenance**: Monitor and replace batteries proactively
- **Network redundancy**: Consider multiple connectivity options for critical applications
- **Data retention**: Configure appropriate data retention policies in Notehub

## **Next Steps**

- [Explore automations](https://docs.blynk.io/en/concepts/automations): set up triggers, alerts, and workflows without writing code
- [Mass provision devices with Static Tokens](https://docs.blynk.io/en/hardware-guides/blues#mass-device-provisioning-with-static-tokens)
- Scale your deployment with [organizations](https://docs.blynk.io/en/concepts/organizations), and role-based access
- Customize [web](https://docs.blynk.io/en/blynk.console/templates/dashboard) and [mobile](https://docs.blynk.io/en/blynk.apps/constructor) dashboards to match your specific use case and user roles
- Try satellite connectivity with [Notecard Satellite](https://blynk.io/product/blues-starnote-for-skylo-starter-kit).

## **Resources and Documentation**
- [Blues Developer Documentation](https://dev.blues.io/)
- [Notecard API Reference](https://dev.blues.io/api-reference/notecard-api/introduction/)
- [Blynk Blues Integration Guide](https://docs.blynk.io/en/hardware-guides/blues)
- [Complete Project Source Code](https://gist.github.com/rdlauer/bc3e2a9becd20e863a5a41b92b87374b)

