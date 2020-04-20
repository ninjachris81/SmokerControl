#include "IOController.h"
#include <LogHelper.h>

IOController::IOController() : AbstractIdleTask() {
}

void IOController::init() {
  pinMode(PIN_HEATER, OUTPUT);

  setState(HEATING_RELAY, false);
}

void IOController::setState(uint8_t index, bool on) {
  switch(index) {
    case HEATING_RELAY:
      mStates[index] = on;
      digitalWrite(PIN_HEATER, on ? LOW : HIGH);
      
      LOG_PRINT(F("IO set to "));
      LOG_PRINT(index);
      LOG_PRINT(F(" to "));
      LOG_PRINTLN(on);
      break;
    default:
      break;
  }
}

bool IOController::getState(uint8_t index) {
  return mStates[index];
}
