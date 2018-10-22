// Olimexino 85s
// PB1 -> IR LED

#include <USIWire.h>
#include "FairIrCodes.h"
#include "IrSignal.h"

enum IrCommand {
  I2C_ADDRESS = 0x08,
  ACK,
  HEAT_UP,
  HEAT_DOWN,
  TEMP_UP,
  TEMP_DOWN,
  ON_OFF,
  STANDBY
};

/*
#define LED_DDR  DDRB
#define LED_PORT PORTB
#define LED_PIN  PB1
*/

int irState = STANDBY;

void setup() {
  Wire.begin(I2C_ADDRESS);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
}

void loop() {
  switch(irState) {
  case HEAT_UP:
    irPlayback(FAIR_HEAT_UP);
    irState = STANDBY;
    break;
  case HEAT_DOWN:
    irPlayback(FAIR_HEAT_DOWN);
    irState = STANDBY;
    break;
  case TEMP_UP:
    irPlayback(FAIR_TEMP_UP);
    irState = STANDBY;
    break;
  case TEMP_DOWN:
    irPlayback(FAIR_TEMP_DOWN);
    irState = STANDBY;
    break;
  case ON_OFF:
    irPlayback(FAIR_ON_OFF);
    irState = STANDBY;
    break;
  default:
    // Maybe we should do something more that has deeper meaning xD.
    delay(10);
  }
}

// Function that executes whenever data is requested by master.
void requestEvent() {
  Wire.write((uint8_t)ACK);
}

// Function that executes whenever data is received from master.
void receiveEvent(int howMany) {
  // Clear rx buffer.
  while(howMany--) {
    const uint8_t data = Wire.read();
    if((data >= HEAT_UP) && (data <= ON_OFF)) {
      irState = data;
      break;
    }
  }
  while(howMany--) {
    Wire.read(); // Discard leftovers.
  }
}

