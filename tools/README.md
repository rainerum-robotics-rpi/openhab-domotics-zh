# openhab-domotics-zh
OpenHAB Domotics with Raspberry Pi 3

## Image Creation
This article describes the detail on how to create the customized OpenHAB image.

See also:
 - [OpenHAB - Raspberry Pi](https://www.openhab.org/docs/installation/rasppi.html)
 - [OpenHABian - Hassle-free openHAB Setup](https://www.openhab.org/docs/installation/openhabian.html)

## First Time Setup
1. Grab the [latest OpenHABian image release from the OpenHAB website](https://github.com/openhab/openhabian/releases) that is based on Raspbian Lite.
2. Download and/or install [a suitable tool to read and write image files](https://thepihut.com/blogs/raspberry-pi-tutorials/17789160-backing-up-and-restoring-your-raspberry-pis-sd-card).
3. Write the extracted image file to an SD card that is larger than the file size of the image. Wait until the process has finished and extract the SD card.
4. Insert the SD card in to a Raspberry Pi and attach a Display. Start the Raspberry Pi and wait until it has finished booting (this may take up to 1/2 hour).
5. Open the Web UI http://openhabianpi:8080/ and select on the *Initial Setup* page the *Standard* recommended setup item. It will take a few moments until the UI gets installed. Once you see the *PAPER UI* item you can proceed by clicking on it. Select on the left side the *Add-ons* tab and then select the *BINDINGS* heading. Search for *mqtt* and select to install the **MQTT Binding**.
6. Open a terminal window and SSH to the Raspberry Pi `ssh openhabian@openhabianpi` and execute following commands (choose the master branch the get the latest stable):
    1. `git clone https://github.com/rainerum-robotics-rpi/openhab-domotics-zh.git`
    2. `cd openhab-domotics-zh`
    3. `sudo ./install.sh`
    4. When you get asked for a MQTT password keep the *password empty* and proceed with *OK*
7. Go back to the Web UI and select: TBD default UI

## OpenHABian Image Preparation
1. Shutdown the Raspberry Pi and put the SD card in to the card reader slot of your computer.
2. Read the SD card image with a [suitable tool](https://thepihut.com/blogs/raspberry-pi-tutorials/17789160-backing-up-and-restoring-your-raspberry-pis-sd-card). Name the file with a memorable name such as `openhabianpi.img`.
3. Start VirtualBox and setup a [Raspberry Pi Desktop machine](https://github.com/rainerum-robotics-rpi/raspbian-mods/releases/latest). Furthermore setup the VM to use [a shared folder](https://www.virtualbox.org/manual/UserManual.html#sharedfolders) to read the copied SD card image. Copy the image file in the selected shared folder. Otherwise you can use also some other Linux OS machine.
4. Within the the VM copy the file from the shared folder to the user directory.
5. Wait until it has finished loading and get a copy of this repository and execute the command from within this folder `sudo ./prepare-rpi-image /path/to/openhabianpi.img`. After the script has finished it will create a new image file with current *DATE* prepended to its name.
6. Copy the generated file back to the shared folder and shut down the VM.
7. With the VM shut down compress the new image with any ZIP tool.
