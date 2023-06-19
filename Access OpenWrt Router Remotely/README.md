## Introduction

Blynk is mostly used with boards like Arduino or a Raspberry Pi, but why not run it on other devices? ;)
I've spent a weekend creating an app for my router. System and network charts, stats, notifications, WiFi control, and more!
This tutorial also explains some basic ideas behind creating such apps, so you could easily adapt it to work with the **Raspberry Pi** and the like.

## Components Used in This Project

You'll need an OpenWrt-compatible router.
Alternatively, some IoT development boards come with OpenWrt out-of-the-box, like **Onion Omega**, **VoCore**, **LinkIt Smart 7688** and others.

**Attention!** Installing OpenWrt manually can brick your device. But once completed, it unlocks full power and control. I'm not brave enough to provide any instructions here, as they may be different for every router model. **But if you already have OpenWrt on your router, you'll be able to start with this tutorial in no time.**

On the device side, I'll be using **Lua** to script the needed functionality. I could also use **Python** or **Node.js**, but unfortunately, these options are not always available due to a lack of resources on some routers. Or **C/C++**, but it's not so convenient to work with (cross-compiling for every change, etc.)

We'll be mostly using pre-installed software (available on any OpenWrt-enabled router).
For example, **Lua** is simple to use and learn, and it's used by the default OpenWrt web interface (**LuCI**).
To access some advanced functionality, I had to install additional software packages.

## Skills Required

I assume that you already know:

- How to open and use an SSH terminal on your OpenWrt router
- How to upload/edit files on your router (using FileZilla or scp/sftp)
- How to work with the Linux console

## Try it out!

Open an **SSH connection to your OpenWrt router** and run:

#### Install required packages

```sh
opkg update
opkg install lua luasocket luasec
opkg install wget nano unzip openssl-util libustream-wolfssl
```

#### Install the Blynk IoT platform script

```sh
cd /root
wget --no-check-certificate -q https://github.com/blynkkk/blueprints/releases/latest/download/Access_OpenWrt_Router_Remotely_Lua.zip -o BlynkExample.zip
mkdir -p ./blynk
unzip BlynkExample.zip -d ./blynk/
cd ./blynk
```

#### Edit the Lua script to include your Blynk credentials

```sh
nano blynkmon.lua
```

Replace these lines with the information provided by the Blynk platform:

```lua
local template_id = "TMPxxxxxx"
local template_name = "Device"
local auth = "YourAuthToken"
```

To save the file, hit `Ctrl+O`, then `Enter`. Close the editor by hitting `Ctrl+X`.

#### Now it's time to run the example:

```log
root@OpenWrt:~/blynkmon# lua ./blynkmon.lua
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ for Lua v0.2.0

Connecting Blynk (secure)...
Ready. Ping: 11ms
```

This means a **secure, bi-directional** connection to the cloud is established!
Your device should appear online in the Blynk Cloud and in the App.

## Autorun in the background

For now, the script has to be manually executed, but I want to make it run **in the background** automatically when the router is powered up.

This is done by creating a system service:

```sh
cd /root/blynk/
cp blynkmon /etc/init.d/blynkmon
chmod a+x /etc/init.d/blynkmon
service blynkmon enable
service blynkmon start
```

## Project Breakdown

The creation process of this project is explained in detail in this [tutorial](https://www.hackster.io/projects/6c23c2)

## Next Steps
* Explore the Blynk Web Console and [Blynk IoT app](https://docs.blynk.io/en/downloads/blynk-apps-for-ios-and-android), try controlling your device from both
* Explore [Blynk Documentation](https://docs.blynk.io/en/) and learn how to work with [Virtual Pins](https://docs.blynk.io/en/getting-started/using-virtual-pins-to-control-physical-devices)
* Learn more about [Automations](https://docs.blynk.io/en/concepts/automations)
* Learn how to [share Device](https://docs.blynk.io/en/concepts/users) with other users
* Modify the code for your needs
* Connect more devices using this template

## Troubleshooting

