#ifndef IR_REMOTE_H
#define IR_REMOTE_H

enum IrRemote {
  IR_I2C_ADDRESS = 0x08,
  IR_ACK,
  IR_HEAT_UP,
  IR_HEAT_DOWN,
  IR_TEMP_UP,
  IR_TEMP_DOWN,
  IR_ON_OFF,
  IR_STANDBY
};

extern int irBegin(void);
extern int irPing(void);
extern void irCmd(enum IrRemote);
extern void irHandleCmd(char *cmd);

#endif
