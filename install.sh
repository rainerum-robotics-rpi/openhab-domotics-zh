#!/bin/bash

readonly ENV_ARCH=$(dpkg --print-architecture)
readonly ENV_OHBC=$(which openhabian-config)
readonly BIN_PROXY="devices-proxy"

invoke_ohbc() {
  # Find the absolute script location dir (e.g. BASEDIR=/opt/openhabian)
  SOURCE="${ENV_OHBC}"
  while [ -h "$SOURCE" ]; do
    BASEDIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
    SOURCE="$(readlink "$SOURCE")"
    [[ $SOURCE != /* ]] && SOURCE="$BASEDIR/$SOURCE"
  done
  BASEDIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
  SCRIPTNAME="$(basename $SOURCE)"

  # Include all subscripts
  # shellcheck source=/dev/null
  for shfile in $BASEDIR/functions/*.sh; do source "$shfile"; done
}

invoke_ohbc_mqtt() {
  invoke_ohbc
  mqtt_setup
}

install_mqtt() {
  if [ `systemctl status mosquitto | grep running | wc -l` -eq 1 ]; then
    return
  fi
  if [[ ! -z "$ENV_OHBC" ]]; then
    invoke_ohbc_mqtt
  else
    apt update
    apt -y install mosquitto
  fi
}

install_proxy() {
  local BuildDir="$( cd -P "$( dirname "$SOURCE" )" && pwd )/build"
  local BuildSrc="$BIN_PROXY-$ENV_ARCH"
  cd "$BuildDir"
  if [ ! -d "$BuildDir/$BuildSrc" ]; then
    mkdir "$BuildDir/$BuildSrc"
  fi
  tar -xzf "$BuildDir/$BuildSrc.tar.gz" -C "$BuildDir/$BuildSrc/"
  cd "$BuildDir/$BuildSrc"
  make install
}

install_wiringpi() {
  if [ `which gpio | wc -l` -eq 1 ]; then
    return
  fi
  apt update
  apt -y install wiringpi
}

setup_gpio() {
  local isI2cDisabled=$(sudo raspi-config nonint get_i2c)
  if [ $isI2cDisabled -eq 1 ]; then
    raspi-config nonint do_i2c 0
    echo "Enabled I2C devices. Please reboot afterwards!"
  fi
  local isDht11Enabled=$(cat /boot/config.txt | grep ^dtoverlay=dht11 | wc -l)
  if [ $isDht11Enabled -eq 0 ]; then
    echo "dtoverlay=dht11,gpiopin=4" | sudo tee -a /boot/config.txt
    echo "Enabled DHT11 GPIO driver. Please reboot afterwards!"
  fi
}

if [[ $EUID -ne 0 ]]; then
  echo "This script must be run as root. Did you mean 'sudo ${BASH_SOURCE[0]}'?" 1>&2
  exit 1
fi

setup_gpio
install_wiringpi
install_mqtt
install_proxy
exit 0
