#!/bin/bash

readonly ENV_ARCH=$(dpkg --print-architecture)
readonly LIB_MQTT_C="paho.mqtt.c"
readonly LIB_MQTT_C_VER="v1.3.0"
readonly LIB_MQTT_C_SRC="https://github.com/eclipse/$LIB_MQTT_C/archive/$LIB_MQTT_C_VER.tar.gz"

install_mqtt_env() {
  sudo apt-get update
  #sudo apt-get upgrade -y
  sudo apt-get install mosquitto
  sudo apt-get install mosquitto-clients
  sudo apt-get install libssl-dev
  wget $LIB_MQTT_C_SRC
  tar -xf $LIB_MQTT_C_VER.tar.gz
  #git clone https://github.com/eclipse/paho.mqtt.c.git
  cd $LIB_MQTT_C*
  make
  tar -czf ../../build/$LIB_MQTT_C-$LIB_MQTT_C_VER-$ENV_ARCH.tar.gz .
  sudo make install
  cd ..
  rm $LIB_MQTT_C_VER.tar.gz*
}

install_mqtt_env
exit 0
