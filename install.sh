#!/bin/bash

readonly ENV_ARCH=$(dpkg --print-architecture)
readonly ENV_OHBC=$(which openhabian-config)
readonly BIN_PROXY="devices-proxy"
readonly LIB_PAHO="paho.mqtt.c-v1.3.0"

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
  mqtt_setup #Invoke setup from OpenHAB
}

setup_ohb_mqtt_binding() {
  local MqttConf="/etc/openhab2/services/mqtt.cfg"
  local MqttBroker="rpidevicesproxy.url=tcp://localhost:1883"
  if [[ -z "$ENV_OHBC" ]]; then
    return #Fail silently
  fi
  if [ ! -f "$MqttConf" ]; then
    echo "Found OpenHAB installation but not mqtt.cfg file. Did you install the MQTT Binding in OpenHAB?"
    return
  fi
  if [ -z "$(cat $MqttConf | grep ^$MqttBroker)" ]; then
    echo "$MqttBroker" >> "$MqttConf"
  fi
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
  local BuildDir="$( cd -P "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/build"
  local BuildSrc="$BIN_PROXY-$ENV_ARCH"
  local BdLibSrc="$LIB_PAHO-$ENV_ARCH"
  cd "$BuildDir"
  if [ ! -d "$BuildDir/$BdLibSrc" ]; then
    mkdir "$BuildDir/$BdLibSrc"
  fi
  tar -xzf "$BuildDir/$BdLibSrc.tar.gz" -C "$BuildDir/$BdLibSrc"
  cd "$BuildDir/$BdLibSrc"
  make install
  cd "$BuildDir"
  if [ ! -d "$BuildDir/$BuildSrc" ]; then
    mkdir "$BuildDir/$BuildSrc"
  fi
  tar -xzf "$BuildDir/$BuildSrc.tar.gz" -C "$BuildDir/$BuildSrc/"
  cd "$BuildDir/$BuildSrc"
  make install
  cd "$BuildDir/.."
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

setup_openhab_extras() {
  local OhbExtrasDir="$( cd -P "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/openhab"
  apt update
  apt -y install fswebcam
  cd "$OhbExtrasDir"
  make install
  cd "$OhbExtrasDir/.."
}

if [[ $EUID -ne 0 ]]; then
  echo "This script must be run as root. Did you mean 'sudo ${BASH_SOURCE[0]}'?" 1>&2
  exit 1
fi

setup_gpio
install_wiringpi
install_mqtt
install_proxy
setup_ohb_mqtt_binding
setup_openhab_extras
exit 0
