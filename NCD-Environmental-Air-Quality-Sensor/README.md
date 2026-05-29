## Introduction

This sample project features a sensor that measures temperature, humidity, pressure, and air quality, and transmits these measurements wirelessly to Blynk for further visualization and insights.

## How To Use This Blueprint

### 1. Unpacking and Initial Setup

#### 1.1 Required Components:
- [Industrial IoT Long Range Wireless Environmental Temperature, Humidity, Pressure, and Air Quality Sensor](https://store.ncd.io/product/industrial-iot-long-range-wireless-environmental-temperature-humidity-pressure-air-quality-sensor/)
- One of the NCD Gateway options:
    - [NCD Enterprise IIoT Gateway](https://store.ncd.io/product/enterprise-iiot-gateway/)
    - [Enterprise IIoT Gateway Lite](https://store.ncd.io/product/enterprise-iiot-gateway-lite/)
- Antennas
- Batteries (if applicable)
- Mounting accessories

Ensure you have all necessary components. For detailed instructions on unpacking and initial setup, refer to the [drawing tab](https://store.ncd.io/product/industrial-iot-long-range-wireless-environmental-temperature-humidity-pressure-air-quality-sensor/#drawing) on the product page.

### 2. Configuring the NCD Enterprise IIoT Gateway

#### 2.1 Required Components:
- NCD Enterprise IIoT Gateway
- Antennas

The NCD Enterprise IIoT Gateway facilitates seamless integration and communication between various IoT devices and networks.

If you haven't set up the gateway yet, please visit Blynk Cloud and use the blueprint for the gateway for a clearer setup: [Blynk Cloud Blueprint](https://blynk.cloud/dashboard/88287/blueprints/Library/TMPL40YtWwLlq).
If you have already set it up, you can proceed without further action.

#### 2.5 Access Interfaces

1. **Web Configuration:** Access the configuration interface at `http://[domain_or_ip]` using the credentials `ncdio` / `ncdB3ast`.
   - **Domain Name:** The domain name format is `ncd-xxxx.local`, where `xxxx` are the last four characters of the Gateway's MAC address. The MAC address can be found on the side of the device. For example, if the last four characters of your Gateway's MAC address are `c398`, the domain name would be `http://ncd-c398.local`.
   - **Customization:** Set up user accounts, logging, and notifications for specific events.
2. **Node-RED:** Access Node-RED at `http://[domain_or_ip]:1880`.
3. **SSH Access:** Connect via SSH with `ncdio` / `ncdB3ast` on port 22.

### 3. Preparing Your Device in Blynk.Cloud

1. **Use the Sensor Blueprint:** Click the **Use Blueprint** button.
2. **Generate Static Tokens:**
   - Go to the **Developer Zone**.
   - Select **Static Tokens**.
   - Click **Generate Static Tokens** and choose **Generate Multiple**.
   - Select the template: **NCD Environmental Air Quality**.
   - Specify the number of tokens you need for your sensors.
3. **Download and Extract the Tokens File:**
   - Download the generated ZIP archive.
   - Extract it and locate the file named `*_tokens.csv` (the `*` represents a variable number).
   - Save this file.

### 4. Transferring the Token File to the Gateway

If SSH is not enabled on the gateway, follow these steps:
   - Open the Gateway's web dashboard at: `http://ncd-xxxx.local`using the credentials `ncdio` / `ncdB3ast`.
     - Go to **Service** > **SSH**.
     - Turn **ON** SSH, then click **Submit** and **Apply**.

![SSH](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/NCD-Environmental-Air-Quality-Sensor/Image/dashboard-ncdio.png)

#### File Transfer (Linux):

1. Open the terminal in the folder containing the token file by right-clicking and selecting "Open in Terminal."
2. Copy and use the following command to transfer the `*_tokens.csv` file to the Gateway:
   ```bash
   scp *_tokens.csv ncdio@ncd-xxxx.local:/home/ncdio/.node-red/
   ```
   Password: `ncdB3ast`

**Note:** Replace `xxxx` in `ncd-xxxx.local` with the last four characters of the Gateway's MAC address, which is printed on the device.

#### File Transfer (Windows):

1. Open the folder containing the token file.
2. Hold down **Shift**, right-click inside the folder, and select **"Open PowerShell window here"** or **"Open Command Prompt here"**.
3. Use the following command to transfer the `*_tokens.csv` file to the Gateway:

   ```powershell
   pscp -pw ncdB3ast *_tokens.csv ncdio@ncd-xxxx.local:/home/ncdio/.node-red/
   ```

   Password: `ncdB3ast`

4. If the `pscp` command is not found, download [PuTTY](https://www.putty.org/) and ensure `pscp.exe` is added to your system's environment variable path.

**Note:** Replace `xxxx` in `ncd-xxxx.local` with the last four characters of the Gateway's MAC address, which can be found on the device label.

### 5. Accessing Node-RED on the Gateway

1. Open a web browser and navigate to `http://[domain_or_ip]:1880`.
2. Log in to the Node-RED dashboard.

### 6. Configuring the Node-RED Flow

1. Copy the [flow file](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main//Firmware/flow.json)
   - In Node-RED, press **CTRL + I** or use the menu to select **Import**.
   - Paste the copied code or upload the flow file (.json).

![Import](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/NCD-Environmental-Air-Quality-Sensor/Image/import.png)

- If you see a message like **"Some of the nodes you are importing already exist in your workspace,"** choose **"Import copy."**

![Import Copy](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/NCD-Environmental-Air-Quality-Sensor/Image/import-copy.png)

 Your flow should look like this:

![Node-RED Flow](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/NCD-Environmental-Air-Quality-Sensor/Image/flow.png)

2. **Set the filename of the token file:**
   - In the dashboard, find the node named **Provide filename with token**, click on it.

    ![Setup filename](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/NCD-Environmental-Air-Quality-Sensor/Image/filename-token.png)

    And enter the token filename you transferred to the gateway.

    ![Type filename](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/NCD-Environmental-Air-Quality-Sensor/Image/type-filename.png)


### 7. Running the Sample Using Node-RED

1. **Deploy the Flow:**
   - Click the **Deploy** button in Node-RED to activate the flow. When the flow connects to the cloud, the MQTT node's status indicator will turn green and display "Connected."

2. **Test Your Setup:**
   - Go to Blynk.cloud to check the sensor data and verify everything is working.
     The Environmental Air Quality Dashboard provides a comprehensive,
     real-time visualization of key environmental parameters to help users
     monitor and analyze indoor air quality. This intuitive interface presents
     essential data points and insights, enabling informed decision-making to
     maintain a healthy environment.

![Dashboard](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/NCD-Environmental-Air-Quality-Sensor/Image/dashboard.png)

- **The Blynk mobile app** provides the same functionality as the web dashboard, allowing you to monitor and manage your system on the go. You can access real-time data, view historical trends, and configure notification thresholds directly from your mobile device. This ensures continuous monitoring and timely alerts, helping you maintain optimal system performance anytime, anywhere.


#### **Key Features:**

1. **Device Overview:**
   - Displays the device name, status (online/offline), and ownership information.
   - Provides easy access to device settings and configurations.

2. **Air Quality Metrics:**
   - **Indoor Air Quality Index (IAQ):** A visual gauge that presents the current air quality score, helping users quickly assess the environmental conditions.
   - **Status Interpretation:** A user-friendly message indicating the air quality level and its potential impact on health (e.g., "Air is GOOD 😊").
   - **Historical Data Trends:** Graphical representation of air quality variations over different timeframes for tracking long-term changes.

3. **Environmental Parameters:**
   - **Temperature:** Displays the current temperature value, often color-coded to indicate normal or critical levels.
   - **Humidity:** Monitors moisture levels in the environment, providing insights into comfort and potential health concerns.
   - **Pressure:** Shows atmospheric pressure readings, which can affect indoor climate conditions.
   - **Gas Resistance:** Represents the concentration of airborne pollutants, aiding in the detection of potential hazards.

4. **Battery Status:**
   - A dedicated gauge displaying the current battery level to ensure continuous monitoring and timely maintenance.

5. **Data Visualization & History:**
   - Offers live and historical data views, allowing users to analyze trends over various periods, such as hours, days, or months.

Adding more sensors will work automatically—when the gateway receives a message from a new sensor, it will process it. You only need to create new tokens when you see a message in the debug log similar to the one in **Troubleshooting 4** and device automatically will be created in blynk.cloud.

🎥 **Watch the Video Guide**
[![Watch the video](https://img.youtube.com/vi/3AUiQNrr--o/maxresdefault.jpg)](https://youtu.be/3AUiQNrr--o)

## Next Steps

- Explore the Blynk Web Console and IoT app to monitor sensor data.
- Read the Blynk Documentation to learn how to work with Virtual Pins.
- [Learn more about Automations](https://docs.blynk.io/en/concepts/automations).
- [Discover how to Share Devices with other users](https://docs.blynk.io/en/blynk.console/devices/device-sharing).
- Customize the code to meet your specific needs.

## Troubleshooting

1. **Connection Problems:**
   - Ensure the sensor is powered and within range.
   - Check network settings and firewall rules.
   - Verify the gateway's network connection.

2. **Calibration Errors:**
   - Follow the software instructions to recalibrate the sensor.
   - Ensure the environment is stable during calibration.

3. **Node-RED Issues:**
   - **Flow Not Deploying:** Check for syntax errors or missing nodes.
   - **MQTT Connection Failure:** Verify MQTT broker settings and credentials.

4. If you receive the following message, generate more tokens and upload the
   `*_tokens.csv` file to the Gateway, you don't need restart the flow for this. The file can contain only new tokens, or
    both new and old tokens:
    ```
    No unused tokens available for 00:13:a2:00:42:4f:17:12 in the tokens map.
    Please create more static tokens for NCD Environmental Air Quality (sensor type = 27).
    ```

5. If you see this error, upload the `*_tokens.csv` file and restart the flows:

    ```
        Error: /home/ncdio/.node-red/17_tokens.csv does not exist.
    ```

### Related Links

- [Blynk MQTT API Documentation](https://docs.blynk.io/en/hardware-guides/mqtt-api)
- [Blynk Documentation](https://docs.blynk.io/en/)
- [Blynk Node-RED Guide](https://docs.blynk.io/en/hardware-guides/node-red)
- [NCD Wireless Vibration Temperature Sensor Documentation](https://store.ncd.io/product/industrial-iot-wireless-vibration-temperature-sensor-v3/)
- [Node-RED Documentation](https://nodered.org/docs/getting-started/local)
- [NCD Support](https://ncd.io/contact/)

