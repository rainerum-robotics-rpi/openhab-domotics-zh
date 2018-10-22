#!/bin/bash

readonly ENV_ARCH=$(dpkg --print-architecture)
readonly BIN_PROXY="devices-proxy"

install_wiringpi_env() {
  sudo apt-get update
  #sudo apt-get upgrade -y
  sudo apt-get install wiringpi
  cd $BIN_PROXY
  make
  tar -czf ../../build/$BIN_PROXY-$ENV_ARCH.tar.gz .
  sudo make install
  cd ..
}

setup_gpio() {
  local isI2cDisabled=$(sudo raspi-config nonint get_i2c)
  if [ $isI2cDisabled -eq 1 ]; then
    sudo raspi-config nonint do_i2c 0
    echo "Enabled I2C devices. Please reboot afterwards!"
  fi
  local isDht11Enabled=$(cat /boot/config.txt | grep ^dtoverlay=dht11 | wc -l)
  if [ $isDht11Enabled -eq 0 ]; then
    echo "dtoverlay=dht11,gpiopin=4" | sudo tee -a /boot/config.txt
    echo "Enabled DHT11 GPIO driver. Please reboot afterwards!"
  fi
}

setup_gpio
install_wiringpi_env
exit 0
