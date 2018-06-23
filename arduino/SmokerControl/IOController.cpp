#include "IOController.h"

IOController::IOController() : AbstractIdleTask() {
  
}

IOController::~IOController() {
  delete mux;
}

void IOController::init() {
  mux = new CD74HC4067(PIN_MUX0, PIN_MUX1, PIN_MUX2, PIN_MUX3);
  pinMode(PIN_ANALOG_MUX, INPUT);
}

int IOController::analogRead(uint8_t channel) {
  //mux->channel(channel);
  //return analogRead(PIN_ANALOG_MUX);
  return 0;
}
