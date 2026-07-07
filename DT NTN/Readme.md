# **Connecting a Nordic nRF9151 with DT IoT and Blynk**

## **Introduction**

This guide walks through connecting a Nordic nRF9151 development kit to the Blynk IoT platform using Deutsche Telekom's Non-Terrestrial Network (NTN) satellite connectivity. The nRF9151 connects via Deutsche Telekom's Device-to-Cloud (D2C) platform, which forwards telemetry to Blynk; Blynk receives and visualises that data through its Data Converter pipeline.

By the end of this guide, your device will send GPS location and sensor data from anywhere on the planet to a Blynk web dashboard and mobile app, with no cellular coverage required.

The full path the data travels:

nRF9151 → Satellite or cellular → Deutsche Telekom D2C → Blynk Data Converter → Blynk Device

Unlike a store-and-forward satellite network, this path is near-real-time: device to dashboard typically takes 8 to 20 seconds.

## **Prerequisites**

**Hardware**

* Nordic nRF9151 SMA DK (A1 silicon revision or newer; earlier revisions do not support NTN)  
* NTN-capable antenna (2 GHz S and L band). An external antenna is recommended for reliability.  
* GPS antenna. NTN requires a GPS fix before connecting, so the device can calculate satellite timing-advance offset.  
* USB-C data cable (not charging-only)

**Accounts**

* A Deutsche Telekom Device to Cloud (D2C) tenant. [https://hub.iot.telekom.com](https://hub.iot.telekom.com)  
* A Blynk account (Free and above)

**Software**

* [nRF Connect for Desktop](https://www.nordicsemi.com/Products/Development-tools/nrf-connect-for-desktop) (includes the Programmer and Serial Terminal apps)

* [nRF Util](https://www.nordicsemi.com/Products/Development-tools/nRF-Util) 

**Coverage**

This Blueprint is limited to Skylo’s NTN coverage: https://www.skylo.tech/resources/geographical-coverage

## **Step 1 — Prepare the hardware**

### 

### The nRF9151 comes with two chips and therefore two different firmware packages \- the cellular modem and the MCU. Depending on where you got your development board, you may or may not need to update both firmwares. It is important to verify this, as flashing the wrong firmware may erase pre-installed nuSIMs. You can verify your current firmware by using the AT command AT+CGMR.

### Also, if your nRF9151 board has be pre-provisioned with a DT nuSIM then the modem firmware has already been updated. DO NOT perform Step 1a as this will erase the nuSIM.

### **1a. Update the modem firmware**

The modem firmware that ships on the nRF9151 may not support NTN. Verify that it does, or update it before anything else.

1. Visit [https://www.nordicsemi.com/Products/nRF9151/Download](https://www.nordicsemi.com/Products/nRF9151/Download) and download the NTN version, "nRF9151 SiP NTN firmware".  
2. Open **nRF Connect for Desktop** and install the **Programmer** app if you haven't already.  
3. Connect the nRF9151 board to your computer with a USB-C data cable and power it on-  
4. In the Programmer app, select your device from the dropdown.  
5. Click **Add file** and select the downloaded ZIP.  
6. Click **Write** to flash the firmware.

   ![][image1]

### **1b. Flash the application firmware**

The application firmware is based on Nordic's [Asset Tracker Template](https://github.com/nrfconnect/Asset-Tracker-Template), NTN branch. Nordic's prebuilt binaries only cover the main (cellular) branch, so Blynk provides a prebuilt NTN binary.

**1\.** Go to the [nRF9151 NTN firmware releases page](https://github.com/Blynk-Technologies/Blynk-DT-nRF9151-NTN-Firmware/releases) and download the latest binary.

**2\.** Use the “**nRF Util**” program (see Software Pre-reqs) to flash the firmware to your board:

nrfutil.exe device program \--firmware \<your merged.hex file\> \--traits jlink \--options chip\_erase\_mode=ERASE\_RANGES\_TOUCHED\_BY\_FIRMWARE

### **1c. Verify the firmware is running**

**1\.** In nRF Connect for Desktop, open the **Serial Terminal** app and connect to your device.

**2\.** You should see log output as the firmware boots, searches for a GPS fix, and attempts NTN registration.

### **1d. Read the device IMEI**

You will need the IMEI in Step 5\. The IMEI QR code on the chip is often too small to scan, so read it over UART.

*Note: The UART command interface is only active after a GPS fix. Take the device outside with a clear view of the sky, GPS antenna connected, and wait for the fix before running the command.*

In the Serial Terminal, type (note the lowercase at at the start):

at AT+CGSN=1

You should see:

\+CGSN: 351358810123456  
OK

Write down this number — it is your device's IMEI.

## **Step 2 — Activate the SIM**

**This step is not needed if your board has nuSIM installed**

The nRF9151 SMA DK ships with three SIMs. One is a Deutsche Telekom SIM pre-provisioned for NTN.

**1\.** Find the SIM number printed on the back of the Deutsche Telekom SIM.

**2\.** Register it at [iot.telekom.com/nordic-sim](https://iot.telekom.com/nordic-sim).

**3\.** Wait for Deutsche Telekom to enable NTN on your SIM (up to 2 business days).

**Data allowance:** The dev-kit SIM includes 50 KB. Data is metered in 1-byte blocks regardless of payload size, so each message consumes at least one block.

## **Step 3 — Install the Blynk DT NTN Blueprint**

Blueprints are pre-built solutions that configure your Blynk workspace with the correct datastreams, dashboard widgets, and Data Converter script for a specific device type.

**1\.** Log in to [Blynk Console](https://blynk.cloud).

**2\.** Navigate to **Developer Zone \-\> Blueprints**.

**3\.** Find and select **DT NTN quickstart with nRF9151**.

**4\.** Click **Use Blueprint**. This copies it into your account as a new Template (under Developer Zone → Templates), pre-configured with datastreams, a dashboard, and the Data Converter.

## **Step 4 — Find the Data Converter Endpoint URL in your Blynk Template**

The Data Converter receives raw data from D2C and translates it into Blynk datastream values. The Blueprint already includes it; you just need its endpoint.

**1\.** In Blynk Console, go to **Templates** and open the **DT NTN** template.

**2\.** Select the **Data Converter** tab.

**3\.** Copy the **Endpoint URL**. It looks like:

https://fra1.blynk.cloud/converter/\<your\_token\>

The region prefix (e.g. fra1) matches the Blynk cloud your account lives on.

Keep this URL to hand; you will paste it into D2C in Step 5\.

***How matching works (multi-device):** the Data Converter routes each incoming message to the correct Blynk device by matching the SIM's **ICCID** against the device's ICCID metafield. The Blueprint's converter uses handler.useAuthMetaField('ICCID') so one endpoint serves all your devices.*

\>

***Advanced — customising the decoder:** the device sends raw bytes to minimise over-the-air cost. The converter parses the byte payload, extracts GPS location and device timestamp, computes in-flight duration, and writes the template datastreams. Edit the converter JavaScript to parse additional sensor fields from your firmware.*

![Blynk — Data Converter Endpoint](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/DT NTN/Images/Blynk-dc.png)

## **Step 5 — Configure Deutsche Telekom Device to Cloud (D2C)**

Open the following Deutsche Telekom website: [**https://hub.iot.telekom.com**](https://hub.iot.telekom.com) **and** sign in using your **Telekom Business Account**. The login credentials and account information were provided via email. Use the details from that email to complete the sign-in process.

Click on the tile “Data Provisioning” to access the Device to Cloud application. 

Device to Cloud (D2C) needs three linked objects: a Device, a Device Group, and an Application that forwards data to your Blynk endpoint.

### **5a. Create an NTN Device**

**1\.** Log in to your D2C tenant and navigate to **Devices**; create a new device.

**2\.** Set the type to **UDP**.

**3\.** Enter the **IMEI** from Step 1d.

**4\.** Give it a Device ID that helps identify the device (no spaces).

**5\.** Save. The status will show "Provisioning."

![D2C — device creation](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/DT NTN/Images/D2C-AddDevice.png)


### **5b. Integrate your Application Webhook (the forward to Blynk)**

An Application tells D2C where to send your device's data — this is the equivalent of a webhook pointing at your Blynk converter.

**1\.** Navigate to **Applications** and create a new application.

**2\.** Set the type to **Webhook**.

**3\.** For the Target URL, paste the Blynk **Data Converter Endpoint URL** from Step 4\.

**4\.** Save.

**5\.** Select “Edit Device” via Actions in the list and **assign your created device to the default Device Group** which has been automatically created for the Application before 

*Tip: You can create multiple Applications on the same Device Group to send the same data to multiple endpoints — useful for parallel monitoring and integration testing.*

## **Step 6 — Create a new device in Blynk**

**1\.** In Blynk Console, go to **Devices → Add New Device**.

**2\.** Select **From Template** and choose the **DT NTN** template from Step 3\.

**3\.** Give the device a name and click **Create**.

## **Step 7 — Set the Blynk device ICCID to match your SIM**

The Data Converter uses the **ICCID** metadata field to match incoming messages to the correct Blynk device.

**1\.** Open the newly created device in Blynk Console.

**2\.** Go to **Device Info → Metadata**.

**3\.** Set the **ICCID** field to your SIM's ICCID.

***Important:** The ICCID must match exactly. A mismatch is the most common reason data does not appear.*

## **Step 8 — Power up and verify**

**1\.** Take the device outside with a clear view of the sky. Both the GPS and NTN antennas need sky access.

**2\.** Power the device via USB or battery.

**3\.** In the Serial Terminal you should see: GPS fix acquired → NTN registration successful → first uplink sent.

**4\.** In the D2C console, your device should show an incoming message.

**5\.** In your Blynk dashboard, within 8 to 20 seconds of the uplink, the datastreams should update with location and timestamp.

![Blynk — dashboard](https://raw.githubusercontent.com/blynkkk/blueprints/refs/heads/main/DT NTN/Images/Blynk-dashboard.png)

**Expected behaviour**

* End-to-end latency (device to dashboard): 8 to 20 seconds over satellite.  
* GPS accuracy: \~200 m with basic GNSS (no assisted GPS).  
* The device sends periodically; the interval depends on firmware configuration.

You can also watch incoming messages under **Devices → your device → Timeline** in the Blynk Console.

## **Troubleshooting**

**No GPS fix**

* Confirm the GPS antenna is connected and the device is outside with a clear view of the sky.  
* A cold fix can take several minutes on first boot. Be patient.

**Device not connecting to NTN**

* Confirm A1 silicon or newer (earlier revisions do not support NTN).  
* Confirm the modem firmware was updated (Step 1a).  
* Confirm the SIM is activated and NTN-enabled by Deutsche Telekom (Step 2).

**Data not appearing in Blynk**

* Check the D2C console to confirm the uplink arrived.  
* Confirm the D2C Application Target URL matches your Blynk Data Converter Endpoint exactly (Step 4 / 5c).  
* Confirm the device's ICCID metafield matches the SIM exactly (Step 7).  
* Check the Data Converter logs in the template for decoder errors.

**IMEI command not responding**

* The UART command interface is only active after a GPS fix. Get a fix outside first.

## **Next steps**

* Add more devices: repeat the device \+ ICCID steps. One Data Converter endpoint serves all of them.  
* Customise the Data Converter JavaScript to parse additional sensor data from your firmware.  
* Set up [automations and alerts](https://docs.blynk.io/en/concepts/automations) for unusual readings.  
* Explore the Blynk mobile app to monitor devices on the go.

## **Related links**

* [Blynk Documentation](https://docs.blynk.io)  
* [Nordic nRF9151 Documentation](https://www.nordicsemi.com/Products/nRF9151)  
* [Nordic Asset Tracker Template (NTN branch)](https://github.com/nrfconnect/Asset-Tracker-Template)  
* [DT NTN SIM Registration](https://iot.telekom.com/nordic-sim)  
* [nRF Connect for Desktop](https://www.nordicsemi.com/Products/Development-tools/nrf-connect-for-desktop)

* [D2C Documentation](https://hub.iot.telekom.com/docs/device-to-cloud/getting-started/about/)

[image1]: <data:image/png;base64,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>