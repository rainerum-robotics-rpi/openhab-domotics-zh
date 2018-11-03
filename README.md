# openhab-domotics-zh
OpenHAB Domotics with Raspberry Pi 3

## Installation

### SD Card Image
Download the [latest SD Card image from the release page](https://github.com/rainerum-robotics-rpi/openhab-domotics-zh/releases/latest) and use a tool such as *Etcher* to flash your SD Card.

See also:
 - [Installing operating system images](https://www.raspberrypi.org/documentation/installation/installing-images/README.md)
 - [Balena Etcher](https://www.balena.io/etcher/)

If you have an Raspberry Pi 3 or a newer model then you can proceed to configure the Wifi connection (see also next section).
Insert the SD Card into the Raspberry Pi and wait until it has finished booting.
The first boot will take some time since the SD card gets reconfigured and adjusted to the actual SD Card memroy size.
Please wait until the ACT activty LED has finished to flash.

### Wifi
In case of an Raspberry 3 or newer you can add the credentials to your network following the guide from the Raspberry Pi Foundation.

See also:
 - [Setting up a Raspberry Pi headless](https://www.raspberrypi.org/documentation/configuration/wireless/headless.md)
 - [Setting WiFi up via the command line](https://www.raspberrypi.org/documentation/configuration/wireless/wireless-cli.md)

Add a new empty `wpa_supplicant.conf` file to the `boot` partition of your Raspberry Pi SD-Card and paste in the file following content:
```
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1
country=IT

network={
        ssid="YOUR_WIFI_SSID"
        psk="YOUR_WIFI_PASSWORD"
}
```
Replace `YOUR_WIFI_SSID` and `YOUR_WIFI_PASSWORD` with your Wifi credentials. If your are in a different country change also `IT` to the ISO code of your country, such that you can also use 5GHz networks with the Raspberry Pi 3+ or better models.

*Beware: if you change anything else of this file it may break the automatic setup process of any wifi connection. Also this file overwrites any content that is located at `/etc/wpa_supplicant/wpa_supplicant.conf`.*

### OpenHAB Cloud Service
This cloud service allows you to access your home automation panel also from remote places via https://www.myopenhab.org/ and/or your mobile devices with Android or iOS.
To enable the cloud service you will need SSH access to your Raspberry Pi to get the credentials needed to register your account (see also next section).

See also:
 - [myopenHAB - Mobile Apps](https://www.myopenhab.org/)
 - [openHAB Cloud Connector](https://www.openhab.org/addons/integrations/openhabcloud/)

To enable the cloud service you have to obtain the credentials needed to register your device and bind it to an user account.
1. Open the Web UI in a browser with the URL http://openhabianpi:8080/ there you should see the **PAPER UI** item where you can proceed by clicking on it. On the laft pane select **Add-ons**  and then choose the heading **MISC**. Search for *openhab* and then there should show up the **openHAB Cloud Connector** item where you then click on the **INSTALL** button on the right side. Wait until it has finished installing.
2. Proceed by clicking on the **Configuration** menu item on the left pane and then select the **Services** subitem. Under the heading of **IO** you should find **openHAB Cloud** item. Proceed by clicking on **CONFIGURE** button that opens a new panel. On the Panel you have to insert under **Base URL for the openHAB Cloud server** the URL https://myopenhab.org and then click on **SAVE**.
3. Go to https://myopenhab.org/ where you can register your Raspberry Pi. As you can see besides the email address and a password of your choice you will need also the **UUID** and **Secret** key such that you can bind the Raspberry Pi to the cloud service. For that you will need SSH access (see also next section).
4. Open with *SSH* a connection to your Raspberry Pi and obtain the credentials via:
    1. `cat /var/lib/openhab2/uuid`
    2. `cat /var/lib/openhab2/openhabcloud/secret`
5. Copy and paste both values to the input fields of the myopenhab web page and complete the registration with your email address and password of your choice. Accept the terms and privacy checkbox and proceed by clicking *Register*. You should have got a new email sent to you where your address gets verified.
6. The last step is within the SSH terminal where you type `sudo reboot`. That will restart the Raspberry Pi and enable remote access through *myopenhab*.

See also:

[![](http://img.youtube.com/vi/joz5f4ejJVc/0.jpg)](http://www.youtube.com/watch?v=joz5f4ejJVc "Complete Guide Setup openHAB Cloud Connector and myopenhab.org (Setup Remote Access)")

### SSH Access
The default hostname of your Raspberry Pi will be `openhabianpi`. Furthermore the default user for SSH access is `openhabian` with password `openhabian`.
If your are on a public network it is recommended to change the default credentials as soon as possible to secure the access to your Raspberry Pi.
By default SSH should be already enabled on the Raspberry Pi. You need only access to a computer with a Terminal such that you can use SSH (for ex.: `ssh openhabian@openhabianpi`).
If you can not connect to the Raspberry Pi make shure that your computer is on the same network as with the Raspberry Pi or else try to find the IP address of the Raspberry Pi with tools such as *NMAP*.
Just in case that the hostname `openhabianpi` is not working you can try to replace it with the IP address obtained from the NMAP scan. 

See also:
 - [SSH (Secure Shell)](https://www.raspberrypi.org/documentation/remote-access/ssh/)
 - [Downloading Nmap](https://nmap.org/download.html)
 - [openHABian Configuration Tool](https://www.openhab.org/docs/installation/openhabian.html#openhabian-configuration-tool)

As you can immagine it is recommended to change the default password `openhabian` as soon as possible such that nobody except you can enter the Raspberry Pi. For that you can start a SSH connection where you then enter the command `sudo openhabian-config`.

### SD Card Backup
Once you are happy with the current configuration it is recommended to backup the SD Card such that you do not loose important settings.
See also: [Backups](https://www.raspberrypi.org/documentation/linux/filesystem/backup.md)
