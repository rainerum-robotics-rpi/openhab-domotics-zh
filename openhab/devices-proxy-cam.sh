#!/bin/bash
readonly OHB_DIR="/etc/openhab2"
readonly CAM_IMG_DST="$OHB_DIR/html/cam_dev_video0.jpg"
readonly CAM_IMG_ERR="$OHB_DIR/html/cam-not-available.jpg"
readonly CAM_IMG_RES="$OHB_DIR/html/cam0.jpg"

camErr=$(fswebcam -q "$CAM_IMG_DST" 2>&1 >/dev/null)
if [ -n "$camErr" ]; then
  (>&2 echo "Could not capture from camera, linking to '$CAM_IMG_ERR'.")
  ln -s -f "$CAM_IMG_ERR" "$CAM_IMG_RES"
  exit 1
fi
echo "Captured image to '$CAM_IMG_DST', linking it to '$CAM_IMG_RES'."
ln -s -f "$CAM_IMG_DST" "$CAM_IMG_RES"
exit 0
