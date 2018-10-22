// Arduino Uno

#include <Wire.h>

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

void setup() {
  Serial.begin(115200);
  Wire.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Init");
}

void loop() {
  bool isConnected = sendIrCommand(ACK);
  if(isConnected) {
    sendIrCommand(HEAT_UP);
    delay(100);
    sendIrCommand(HEAT_DOWN);
    delay(100);
    sendIrCommand(TEMP_UP);
    delay(100);
    sendIrCommand(TEMP_DOWN);
    delay(100);
    sendIrCommand(ON_OFF);
    delay(100);
  }
}

bool sendIrCommand(const IrCommand cmd) {
  delay(500);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  if(cmd == ACK) {
    Wire.requestFrom(I2C_ADDRESS, 1);
    if(Wire.available() && (Wire.read() == ACK)) {
      Serial.println("Slave ACK");
      return true;
    }
    while(Wire.available()) {
      Wire.read();
    }
    Serial.println("Slave NACK");
    return false;
  }
  Serial.print((cmd == HEAT_UP) ? "HU " : "");
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write((uint8_t)cmd);
  Serial.print("Tx Bytes: ");
  Serial.println(Wire.endTransmission());
  return true;
}
