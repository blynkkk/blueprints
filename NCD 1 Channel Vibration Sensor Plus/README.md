## Introduction

Set up and launch your project with the [Industrial
IoT Wireless Vibration Temperature Sensor
V3](https://store.ncd.io/product/industrial-iot-wireless-vibration-temperature-sensor-v3/), sending vibration and temperature data wirelessly to the
Blynk IoT platform via the NCD Enterprise IIoT Gateway. This blueprint provides
a ready-to-use web and mobile dashboards, allowing you to monitor sensor data
in real-time.

## How To Use This Blueprint

### Step 1: Unpacking and Initial Setup

- [**Wireless Vibration Temperature Sensor:**](https://store.ncd.io/product/industrial-iot-wireless-vibration-temperature-sensor-v3/) Measures vibration and temperature.
- [**NCD Enterprise
Gateway**](https://store.ncd.io/product/enterprise-iiot-gateway/) or
[**Enterprise IIoT Gateway Lite**](https://store.ncd.io/product/enterprise-iiot-gateway-lite/): Receives data
from the sensor and sends it to Blynk.
- **Antennas:** For wireless communication.
- **Batteries (if applicable):** Power source for the sensor.
- **Mounting accessories:** To securely install the sensor.

### 2. Configuring the NCD Enterprise IIoT Gateway

#### 1 Required Components:
- NCD Enterprise IIoT Gateway
- Antennas

**Attach antennas to the sensor and gateway:** This enables wireless communication.

The NCD Enterprise IIoT Gateway facilitates seamless integration and communication between various IoT devices and networks.

If you haven't set up the gateway yet, please visit Blynk Cloud and use the blueprint for the gateway for a clearer setup: [Blynk Cloud Blueprint](https://blynk.cloud/dashboard/88287/blueprints/Library/TMPL40YtWwLlq).
If you have already set it up, you can proceed without further action.

#### 2 Access Interfaces

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
   - Select the template: **NCD 1 Channel Vibration Sensor Plus**.
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

     - Connect to the Gateway by ETH or WIFI.

![SSH](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/NCD%20Environmental%20Air%20Quality%20Sensor/Image/dashboard-ncdio.png)

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

1. Copy the [flow file](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/NCD%201%20Channel%20Vibration%20Sensor%20Plus/Firmware/flow.json)
   - In Node-RED, press **CTRL + I** or use the menu to select **Import**. For all types of sensors, you need to import the new flow, and a single flow will work for all sensors of this type.
   - Paste the copied code or upload the flow file (.json).

![Import](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/NCD%20Environmental%20Air%20Quality%20Sensor/Image/import.png)

- If you see a message like **"Some of the nodes you are importing already exist in your workspace,"** choose **"Import copy."**

![Import Copy](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/NCD%20Environmental%20Air%20Quality%20Sensor/Image/import-copy.png)

 Your flow should look like this:

![Node-RED Flow](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/NCD%201%20Channel%20Vibration%20Sensor%20Plus/Image/flow.png)

2. **Set the filename of the token file:**
   - In the dashboard, find the node named **Provide filename with token**, click on it.

    ![Setup filename](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/NCD%20Environmental%20Air%20Quality%20Sensor/Image/filename-token.png)

    Enter the token filename that you previously transferred to the gateway. Ensure the filename follows the required format, which must include only numbers before “_tokens.csv.” Valid examples include 15, 15_tokens, or 15_tokens.csv. Avoid adding extra characters or spaces to ensure compatibility.

    ![Type filename](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/NCD%201%20Channel%20Vibration%20Sensor%20Plus/Image/type-filename.png)


### 7. Running the Sample Using Node-RED

1. **Deploy the Flow:**
   - Click the Deploy button in Node-RED to activate the flow. Once the flow is running, the MQTT node’s status indicator will turn green and show “Connected” when data is successfully received from the sensor and transmitted to the cloud.

2. **Test Your Setup:**
   - Go to Blynk.cloud to check the sensor data and verify everything is working.
   - The Blynk Web Dashboard consists of three main tabs: **Dashboard**, **Historical Data**, and **Settings and Diagnosis**. Below are detailed descriptions of each tab with corresponding screenshots:

     - **Dashboard Tab:**
       - This tab provides a real-time overview of the key parameters being monitored.
       - You can see metrics such as Total Vibration Level, Estimated Motor Speed, and Battery Level.
       - Additionally, detailed data for X, Y, and Z axes are presented, including Maximum Acceleration, RMS Acceleration, Velocity, and Displacement.
       - The red color indicates areas of concern or values that might need attention, helping you quickly identify potential issues.

	![Dashboard View](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/NCD%201%20Channel%20Vibration%20Sensor%20Plus/Image/tab1.png)

     - **Historical Data Tab:**
       - This tab allows you to view historical trends of the collected data over different time intervals, such as 1 hour, 6 hours, 1 day, and more.
       - Graphs display data for RMS Acceleration, Max Acceleration, Velocity, and Displacement for each axis, providing insights into the behavior of the system over time.
       - This tab is crucial for identifying patterns, understanding the performance of your system, and making data-driven decisions.

	![Historical Data](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/NCD%201%20Channel%20Vibration%20Sensor%20Plus/Image/tab2.png)

     - **Settings and Diagnosis Tab:**
       - In this tab, you can configure notification thresholds for critical parameters like vibration, temperature, and battery levels.
       - The tab allows for proactive maintenance by notifying you when certain parameters exceed predefined limits.
       - Additionally, you can view custom charts that help in detailed analysis of specific data points, ensuring that your system operates within optimal conditions.

     - **The Blynk mobile app** provides the same functionality as the web dashboard, allowing you to monitor and manage your system on the go. You can access real-time data, view historical trends, and configure notification thresholds directly from your mobile device. This ensures continuous monitoring and timely alerts, helping you maintain optimal system performance anytime, anywhere.

3. **Analyze and Adjust:**
   - After reviewing the data on each tab, make necessary adjustments to your settings or setup. The dashboard, historical data, and settings provide a comprehensive view of your system’s health and performance, allowing you to maintain it efficiently.

Adding more sensors will work automatically—when the gateway receives a message from a new sensor, it will process it. You only need to create new tokens when you see a message in the debug log similar to the one in **Troubleshooting 4** and device automatically will be created in blynk.cloud.

🎥 **Watch the Video Guide**
[![Watch the video](https://img.youtube.com/vi/2IdSoBFrduU/maxresdefault.jpg)](https://youtu.be/2IdSoBFrduU)

### Next Steps

After setting up your system and addressing any issues, you can expand and optimize your project with the following steps:

- Explore the Blynk Web Console and Blynk IoT app, start monitoring your sensor data from both.
- [Set up notifications and log events with Automations.](https://docs.blynk.io/en/concepts/automations).
- [Discover how to Share Devices with other users](https://docs.blynk.io/en/blynk.console/devices/device-sharing).
- Learn how to work with [Virtual Pins](https://docs.blynk.io/en/getting-started/how-to-display-any-sensor-data-in-blynk-app) and [MQTT API](https://docs.blynk.io/en/blynk.cloud-mqtt-api/device-mqtt-api) to customize the code for specific needs.

### Troubleshooting

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
    Please create more static tokens for NCD 1 Channel Vibration Sensor Plus (sensor type = 80).
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

