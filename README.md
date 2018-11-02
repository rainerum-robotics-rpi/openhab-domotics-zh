# openhab-domotics-zh
OpenHAB Domotics with Raspberry Pi 3

## Installation

TBD

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
Replace `YOUR_WIFI_SSID` and `YOUR_WIFI_PASSWORD` with your Wifi credentials. If your are in a different country change also `IT` to the ISO code your country, such that you can also use 5GHz networks with the Raspberry Pi 3+ or bether models.
*Beware: if you change anything else of this file it may break the automatic setup process of any wifi connection. Also this file overwrites any content that is located at `/etc/wpa_supplicant/wpa_supplicant.conf`.*
