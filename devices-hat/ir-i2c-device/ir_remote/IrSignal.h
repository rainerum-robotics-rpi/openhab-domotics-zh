#pragma once

#include <stdint.h>
#include <avr/interrupt.h>
#include <Arduino.h>

struct PulseSpaceCode {
  const uint16_t pulse_us;
  const uint16_t space_us;
};

struct IrSignal {
  const PulseSpaceCode * pulse_space_codes;
  const uint8_t pulse_space_length;
};

void irPlayback(const IrSignal & irSignal) {
  const uint8_t pin = 13;
  const PulseSpaceCode * psCodes = irSignal.pulse_space_codes;
  const uint8_t len = irSignal.pulse_space_length;
  Serial.print("len="); Serial.println(len);
  pinMode(pin,OUTPUT);
  for(uint8_t i = 0; i < len; i++) {
    int32_t pulse_us = psCodes[i].pulse_us;
    uint16_t space_us = psCodes[i].space_us;
    cli();
    while(pulse_us > 0) {
      digitalWrite(pin,HIGH);
      delayMicroseconds(10);
      digitalWrite(pin,LOW);
      delayMicroseconds(10);
      pulse_us -= 26;
    }
    sei();
    delayMicroseconds(space_us);
  }
}
