#include "FairIrCodes.h"
#include "IrSignal.h"

void setup() {
  Serial.begin(115200);
}

void loop() {
  irPlayback(FAIR_ON_OFF);
  delay(1000);
}
