## Introduction

This guide will help you set up and launch your project using the [3-Channel
Industrial IoT Wireless AC Current Monitor
Sensor](https://store.ncd.io/product/3-channel-industrial-iot-wireless-ac-current-monitor-sensor/).
You will learn how to monitor AC current and send the data wirelessly to the
NCD Enterprise IIoT Gateway and the Blynk IoT platform.

## How To Use This Blueprint

### Step 1: Unpacking and Initial Setup

#### 1.1 Required Components:
- [**Wireless AC Current Monitor
Sensor:**](https://store.ncd.io/product/3-channel-industrial-iot-wireless-ac-current-monitor-sensor/)
Monitors AC current levels across 3 channels and sends data wirelessly.
- [**NCD Enterprise
Gateway**](https://store.ncd.io/product/enterprise-iiot-gateway/) or
[**Enterprise IIoT Gateway
Lite**](https://store.ncd.io/product/enterprise-iiot-gateway-lite/): Receives
data from the sensor and sends it to Blynk.
- **Antennas:** For wireless communication.
- **Batteries (if applicable):** Power source for the sensor.
- **Mounting accessories:** To securely install the sensor.

#### 1.2 Initial Setup:
1. **Unpack all components:** Ensure you have all the required parts.
2. **Attach antennas to the sensor and gateway:** This enables wireless communication.

### Step 2: Configuring the NCD Gateway

The NCD Gateway connects your sensor to the internet and the Blynk platform. You can connect the gateway via Ethernet, Wi-Fi, or LTE.

#### 2.1 Ethernet Configuration

Ethernet provides a stable and fast connection.

1. **Connect Ethernet Cable:**
   - Plug one end of an Ethernet cable into the ETH1 port on the gateway.
   - Plug the other end into your router or network switch.

2. **Power On the Gateway:**
   - Connect the power adapter to the gateway and plug it into a power outlet.
   - The gateway should power on, indicated by the power LED lighting up.

3. **Access the Web Interface:**
   - Open a web browser on a computer connected to the same network.
   - Enter the gateway’s IP address (you can find this in your router’s connected devices list) to access the web interface.

4. **Optional: Static IP Configuration:**
   - If you need a fixed IP for the gateway, navigate to "Network > Ethernet" in the web interface and set a static IP.

#### 2.2 Wi-Fi Configuration

Wi-Fi allows wireless communication between the gateway and your network.

1. **Connect to the Gateway:**
   - Use an Ethernet cable to connect your computer to the gateway’s ETH1 port.

2. **Access the Web Interface:**
   - Open a web browser and enter the gateway’s default IP address (typically `192.168.0.1`).
   - Log in using the default credentials provided in the device’s documentation.

3. **Set Up Wi-Fi:**
   - In the web interface, go to "Interface > Wi-Fi".
   - Choose between **Access Point (AP) Mode** or **Client Mode**:
     - **AP Mode:** The gateway creates its own Wi-Fi network.
     - **Client Mode:** The gateway connects to an existing Wi-Fi network.
   - Enter the SSID (network name) and password of your Wi-Fi network if using Client Mode.
   - Click “Submit” to save the settings.

4. **Disconnect Ethernet Cable:**
   - Once Wi-Fi is set up, you can disconnect the Ethernet cable.

#### 2.3 LTE Configuration

LTE is ideal for remote locations where Ethernet or Wi-Fi isn't available.

**More Information:**
To get more details about setting up the NCD Gateway, including other connectivity options and advanced configurations, visit the [NCD Enterprise IIoT Gateway Blueprint on Blynk](https://blynk.io/blueprints/ncd-enterprise-iiot-gateway).

#### 2.4 Choosing Connectivity Interfaces

The NCD Enterprise IIoT Gateway offers three main connectivity options: Ethernet, Wi-Fi, and LTE. You can choose the one that best suits your setup.

#### 2.5 Access Interfaces

1. **Web Configuration:** Access the configuration interface at `http://[domain_or_ip]` using `ncdio` / `ncdB3ast` for login.
   - **Domain Name:** The domain name format is `ncd-xxxx.local`, where `xxxx` are the last 4 characters of the Gateway's MAC address. The MAC address can be found on the side of the device. For example, if the last 4 characters of your Gateway's MAC address are `c398`, the domain name would be `http://ncd-c398.local`.
   - **Network Settings:** Configure static IPs, DNS, and firewall rules as needed.
   - **Customizations:** Set up user accounts, logging, and notifications for specific events.
2. **Node-Red:** Visit `http://[domain_or_ip]:1880` to use Node-Red.
3. **SSH Access:** Connect via SSH with `ncdio` / `ncdB3ast` on port 22.

### Step 3: Setting Up Your Device in Blynk

1. **Use the Sensor Blueprint:** Click the **Use Blueprint** button.
2. **Activate the Device:** On the right panel, click the **Activate Device** button.
3. **Generate AuthToken:** Click the **Generate AuthToken** button. You'll need the generated AuthToken for the next step. Click button **Next**.

### Step 4: Accessing Node-RED on the Gateway

1. **Open Node-RED:**
   - In a web browser, navigate to `http://[gateway IP]:1880` or `http://[domain]:1880`.
   - Log in to the Node-RED dashboard using `ncdio` / `ncdB3ast`.

### Step 3: Setting Up Your Device in Blynk

1. **Use the Sensor Blueprint:** Click the **Use Blueprint** button.
2. **Activate the Device:** On the right panel, click the **Activate Device** button.
3. **Generate AuthToken:** Click the **Generate AuthToken** button. You'll need the generated AuthToken for the next step. Click **Next**.

### Step 4: Accessing Node-RED on the Gateway

1. **Open Node-RED:**
   - In a web browser, navigate to `http://[gateway IP]:1880` or `http://[domain]:1880`.
   - Log in to the Node-RED dashboard using `ncdio` / `ncdB3ast`.

### Step 5: Configuring the Node-RED Flow

1. **Import the Flow:**
   - Copy or download the firmware flow file from the second step of device activation.
![Flow](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/NCD-AC/NCD-3-Channel-AC-Current-Monitor/Image/2step.png)
   - In Node-RED, press **CTRL + I** or use the menu to select **Import**.
   - Paste the copied code or upload the flow file (.json).

2. **Set Up MQTT:**
   - Click on any of the highlighted MQTT-out node.

	![MQTT Out](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main//Image/flow-mqtt-out.png)

   - Select the highlighted icon.

	![MQTT Property](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main//Image/mqtt-property.jpg)

   - Go to the Security tab.

	![Broker Property](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main//Image/broker-property.png)

   - Enter the AuthToken generated by Blynk as a password for your device (use “device” as the username).

	![Security Tab](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main//Image/security-tab.png)

   Your flow should look like this:

![Flow](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/NCD-AC/NCD-3-Channel-AC-Current-Monitor/Image/flow.png)

### Step 6: Running the Sample Using Node-RED

1. **Deploy the Flow:**
   - Click the **Deploy** button in Node-RED to activate the flow.

2. **Test Your Setup:**
   - Go to Blynk.cloud to check the sensor data and verify everything is working.

    The dashboard provides a real-time view of your AC current data, battery
    status, and controls for managing notifications. Accessible via web or
    mobile, it allows you to monitor your device from anywhere.

    Key Components:
    - **Battery Indicator**: Shows the remaining battery life as a percentage. If the level is low, you may need to replace or recharge the battery.
    - **Current Monitoring (Channels 1, 2, 3)**: Displays real-time current readings (in amperes) for each channel.
    - **Historical Data (Graphs)**: Line charts show the current trends over time for each channel, helping you identify patterns or anomalies.
    - **Notification Sliders**: Set thresholds for receiving alerts when the current changes by a certain percentage.

![Dash](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/NCD-AC/NCD-3-Channel-AC-Current-Monitor/Image/screenshot-1.png)

### Next Steps

After setting up your system and addressing any issues, you can expand and optimize your project with the following steps:

- Explore the Blynk Web Console and Blynk IoT app, start monitoring your sensor data from both.
- [Set up notifications and log events with Automations.](https://docs.blynk.io/en/concepts/automations).
- [Discover how to Share Devices with other users](https://docs.blynk.io/en/blynk.console/devices/device-sharing).
- Add more sensors or [devices](https://docs.blynk.io/en/blynk.console/devices/actions-with-devices#create-device) to your setup.
- Learn how to work with [Virtual Pins](https://docs.blynk.io/en/getting-started/how-to-display-any-sensor-data-in-blynk-app) and [MQTT API](https://docs.blynk.io/en/blynk.cloud-mqtt-api/device-mqtt-api) to customize the code for specific needs.

### Troubleshooting

To ensure a smooth experience, make sure you are using the latest versions of the software and libraries. Below are some common issues you might encounter and their solutions:

#### Common Issues

1. **Connection Problems:**
   - Ensure the sensor is powered and within range.
   - Check firewall rules.

2. **Calibration Errors:**
   - Follow the software instructions to recalibrate the sensor.
   - Ensure the environment is stable during calibration.

3. **Node-RED Issues:**
   - **Flow Not Deploying:** Check for syntax errors or missing nodes.
   - **MQTT Connection Failure:** Verify MQTT broker settings and credentials.

### Related Links

- [Blynk MQTT API Documentation](https://docs.blynk.io/en/hardware-guides/mqtt-api)
- [Blynk Documentation](https://docs.blynk.io/en/)
- [Blynk Node-RED Guide](https://docs.blynk.io/en/hardware-guides/node-red)
- [Node-RED Documentation](https://nodered.org/docs/getting-started/local)
- [NCD Support](https://ncd.io/contact/)

