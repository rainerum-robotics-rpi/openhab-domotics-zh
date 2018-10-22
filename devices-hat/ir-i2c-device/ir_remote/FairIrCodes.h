#pragma once

// IR Codes for FAIR remote controlled heater.

#include "IrSignal.h"

// INCREMENT FLAME HEAT
const PulseSpaceCode FAIR_HEAT_UP_PATTERNS[] {
  { .pulse_us = 6500, .space_us = 2550 },
  {             3200,             1750 },
  {              700,              950 },
  {              700,             1750 },
  {             4050,              900 },
  {              750,              900 },
  {              700,             1750 },
  {             3200,              900 },
  {              750,              900 },
  {             1550,            50100 },
};

const IrSignal FAIR_HEAT_UP {
  .pulse_space_codes = FAIR_HEAT_UP_PATTERNS,
  .pulse_space_length = (sizeof(FAIR_HEAT_UP_PATTERNS) / sizeof(PulseSpaceCode))
};

// DECREMENT FLAME HEAT
const PulseSpaceCode FAIR_HEAT_DOWN_PATTERNS[] {
  { .pulse_us = 6500, .space_us = 2550 },
  {             3250,             1700 },
  {              750,              900 },
  {              750,             1750 },
  {             2350,              900 },
  {              750,              900 },
  {              750,              900 },
  {              750,             1750 },
  {             2350,             1750 },
  {              700,              900 },
  {             1600,            50100 },
};

const IrSignal FAIR_HEAT_DOWN {
  .pulse_space_codes = FAIR_HEAT_DOWN_PATTERNS,
  .pulse_space_length = (sizeof(FAIR_HEAT_DOWN_PATTERNS) / sizeof(PulseSpaceCode))
};

// INCREMENT TEMPERATURE
const PulseSpaceCode FAIR_TEMP_UP_PATTERNS[] {
  { .pulse_us = 6500, .space_us = 2550 },
  {             3200,             1750 },
  {              700,              900 },
  {              750,             1750 },
  {             1550,              900 },
  {             1550,              950 },
  {              700,              950 },
  {              700,             1750 },
  {             1550,              900 },
  {              750,              900 },
  {              750,              900 },
  {             1550,            50100 },
};

const IrSignal FAIR_TEMP_UP {
  .pulse_space_codes = FAIR_TEMP_UP_PATTERNS,
  .pulse_space_length = (sizeof(FAIR_TEMP_UP_PATTERNS) / sizeof(PulseSpaceCode))
};

// DECREMENT TEMPERATURE
const PulseSpaceCode FAIR_TEMP_DOWN_PATTERNS[] {
  { .pulse_us = 6500, .space_us = 2550 },
  {             3200,             1700 },
  {              750,              900 },
  {              750,             1750 },
  {             3200,             1700 },
  {              750,              900 },
  {              750,             1750 },
  {             4000,             1750 },
  {             1550,            50100 },
};

const IrSignal FAIR_TEMP_DOWN {
  .pulse_space_codes = FAIR_TEMP_DOWN_PATTERNS,
  .pulse_space_length = (sizeof(FAIR_TEMP_DOWN_PATTERNS) / sizeof(PulseSpaceCode))
};

// SWITCH ON/OFF
const PulseSpaceCode FAIR_ON_OFF_PATTERNS[] {
  { .pulse_us = 6500, .space_us = 2550 },
  {             3200,             1750 },
  {              700,              950 },
  {              700,             1750 },
  {             1550,              900 },
  {              750,             1750 },
  {              700,              950 },
  {              700,             1750 },
  {             1550,              900 },
  {             1550,             1750 },
  {             1550,            50100 },

};

const IrSignal FAIR_ON_OFF {
  .pulse_space_codes = FAIR_ON_OFF_PATTERNS,
  .pulse_space_length = (sizeof(FAIR_ON_OFF_PATTERNS) / sizeof(PulseSpaceCode))
};

