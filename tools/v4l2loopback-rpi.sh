#!/bin/bash
if [ -z "$1" ]; then
  echo "Please specify a video file."
  exit 1
fi
readonly VIDEO_SRC="$1"
readonly CAM_DEST="/dev/video0"

sudo apt install raspberrypi-kernel-headers
sudo apt install v4l2loopback-dkms
sudo apt install ffmpeg
sudo modprobe v4l2loopback

echo "Streaming video '$VIDEO_SRC' to device '$CAM_DEST'..."
ffmpeg -re -i "$VIDEO_SRC" -map 0:v -f v4l2 "$CAM_DEST"
sudo rmmod v4l2loopback
exit 0
