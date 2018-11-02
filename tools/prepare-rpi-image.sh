#!/bin/bash

extractSlimImgFilename() {
  local imgFilename="$1"
  local dir=$(dirname "$imgFilename")
  local file=$(basename "$imgFilename")
  local filename="${file%.*}"
  local extension="${file##*.}"
  local now="$(date +'%Y-%m-%d')"
  if [ ! -f "$imgFilename" ]; then
    echo "$imgFilename file not found."
    exit 1
  elif [[ "${extension,,}" != "img" ]]; then
    echo "$imgFilename is not a valid image file."
    exit 2
  fi
  echo "$dir/$now-$filename.$extension"
}

if [ "$EUID" -ne 0 ]
  then echo "Please run this script as root or sudo."
  exit 0
fi

if [ -z "$1" ]; then
  echo "No image file argument supplied."
  exit 0
fi

readonly RPI_FILE_IN="$1"
readonly RPI_FILE_OUT=$(extractSlimImgFilename "$RPI_FILE_IN")

if [ ! -f pishrink.sh ]; then
  echo "Downloading PiShrink script ..."
  wget https://raw.githubusercontent.com/Drewsif/PiShrink/master/pishrink.sh
fi

if [ -z "`which parted`" ]; then
  apt -y install parted
fi

bash pishrink.sh "$RPI_FILE_IN" "$RPI_FILE_OUT"
sync

exit 0
