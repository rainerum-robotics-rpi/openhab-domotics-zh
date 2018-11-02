#!/bin/bash

wget http://mirrors.standaloneinstaller.com/video-sample/lion-sample.3gp
./v4l2loopback-rpi.sh lion-sample.3gp
exit 0
