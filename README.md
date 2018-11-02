# openhab-domotics-zh
OpenHAB Domotics with Raspberry Pi 3

## Installation

### SD Card Image
Download the latest SD Card image from the release page and use a tool such as *Etcher* to flash your SD Card.

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

To enable the cloud service you have to obtain the credentials needed to register your device and bind it to a user account.

TBD

### SSH Access
The default hostname of your Raspberry Pi will be `openhabianpi`. Furthermore the default user for SSH access is `openhabian` with password `openhabian`.
If your are on a public network it is recommended to change the default credentials as soon as possible to secure the access to your Raspberry Pi.
By default SSH should be already enabled on the Raspberry Pi. You need only access to a computer with a Terminal such that you can use SSH (for ex.: `ssh openhabian@openhabianpi`).
If you can not connect to the Raspberry Pi make shure that your computer is on the same network as with the Raspberry Pi or else try to find the IP address of the Raspberry Pi with tools such as *NMAP*.
Just in case that the hostname `openhabianpi` is not working you can try to replace it with the IP address obtained from the NMAP scan. 

See also:
 - [SSH (Secure Shell)](https://www.raspberrypi.org/documentation/remote-access/ssh/)
 - [Downloading Nmap](https://nmap.org/download.html)

### SD Card Backup
Once you are happy with the current configuration it is recommended to backup the SD Card such that you do not loose important settings.
See also: [Backups](https://www.raspberrypi.org/documentation/linux/filesystem/backup.md)
