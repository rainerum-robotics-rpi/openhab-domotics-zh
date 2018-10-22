#include "ir_remote.h"

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static int dIr = 0;

int irBegin(void) {
  dIr = wiringPiI2CSetup(IR_I2C_ADDRESS);
  if(dIr <= 0) {
    fprintf(stderr, "Could not access I2C device: %s\n", strerror(errno));
    exit(1);
  }
  if(irPing() != 0) {
    exit(1);
  }
}

int irPing(void) {
  if(wiringPiI2CRead(dIr) != IR_ACK) {
    fprintf(stderr, "I2C device does not respond\n");
    return 1;
  }
  return 0;
}

static char* strIrCmd(enum IrRemote cmd) {
  switch(cmd) {
  case IR_I2C_ADDRESS:
    return "IR_I2C_ADDRESS";
  case IR_ACK:
    return "IR_ACK";
  case IR_HEAT_UP:
    return "IR_HEAT_UP";
  case IR_HEAT_DOWN:
    return "IR_HEAT_DOWN";
  case IR_TEMP_UP:
    return "IR_TEMP_UP";
  case IR_TEMP_DOWN:
    return "IR_TEMP_DOWN";
  case IR_ON_OFF:
    return "IR_ON_OFF";
  case IR_STANDBY:
    return "IR_STANDBY";
  default:
    return "IR_UNKNOWN";
  }
}

void irCmd(enum IrRemote cmd) {
  if((irPing() != 0) || ((IR_HEAT_UP > cmd) || (IR_ON_OFF < cmd))) {
    fprintf(stderr, "Could not send command: %s\n", strIrCmd(cmd));
  } else {
    wiringPiI2CWrite (dIr, cmd);
    printf("Send command: %s\n", strIrCmd(cmd));
    delay(50);
  }
}

void irHandleCmd(char *cmd) {
  int irCmdRcvd = 0;
  for(irCmdRcvd = IR_HEAT_UP; irCmdRcvd <= IR_ON_OFF; irCmdRcvd++) {
    int sz = strlen(strIrCmd(irCmdRcvd));
    if(strncmp(cmd, strIrCmd(irCmdRcvd), sz) == 0) {
      irCmd(irCmdRcvd);
      return;
    }
  }
  fprintf(stderr, "Could not handle command: %s\n", cmd);
}
