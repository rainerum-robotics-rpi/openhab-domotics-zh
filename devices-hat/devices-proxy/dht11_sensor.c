#include "dht11_sensor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static float getValue(FILE * fp) {
  static char cmdBuf[8];
  memset(cmdBuf, 0, sizeof(cmdBuf));
  if(NULL == fp) {
    return NAN;
  }
  if(NULL != fgets(cmdBuf, sizeof(cmdBuf)-1, fp)) {
    float val = strtof(cmdBuf, NULL);
    return val / 1000.0f;
  }
  return NAN;
}

void dht11_refresh(float* outTempDegC, float* outRelHumPrcnt) {
  static const char * cmdTmp =
    "/bin/cat /sys/devices/platform/dht11@0/iio:device0/in_temp_input";
  static const char * cmdHum =
    "/bin/cat /sys/devices/platform/dht11@0/iio:device0/in_humidityrelative_input";
  FILE * fpTmp = popen(cmdTmp, "r");
  FILE * fpHum = popen(cmdHum, "r");
  *outTempDegC = getValue(fpTmp);
  *outRelHumPrcnt = getValue(fpHum);
  pclose(fpTmp);
  pclose(fpHum);
}
