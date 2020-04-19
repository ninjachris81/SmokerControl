#include "IOController.h"
#include <LogHelper.h>

IOController::IOController() : AbstractIdleTask() {
  
}

void IOController::init() {
  pinMode(PIN_HEATER, OUTPUT);
}

void IOController::setState(uint8_t index, bool on) {
  LOG_PRINT(F("IO set to "));
  LOG_PRINT(index);
  LOG_PRINT(F(" to "));
  LOG_PRINTLN(on);
  
  digitalWrite(index, on ? LOW : HIGH);
}
