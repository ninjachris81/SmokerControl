#include "BuzzerController.h"
#include <LogHelper.h>
#include "Pins.h"

BuzzerController::BuzzerController() : AbstractIntervalTask(BEEP_DURATION_MS) {
}

void BuzzerController::init() {
  pinMode(PIN_BUZZER, OUTPUT);
}

void BuzzerController::update() {
  if (currentAmountLeft>0) {
    if (currentIsBeep) {
      tone(PIN_BUZZER, 1000, BEEP_DURATION_MS);
    } else {
      currentAmountLeft--;
    }
  
    currentIsBeep = !currentIsBeep;
    if (currentAmountLeft==0) stop();
  }
}

void BuzzerController::stop() {
  noTone(PIN_BUZZER);
  digitalWrite(PIN_BUZZER, HIGH);
  currentAmountLeft = 0;
}

void BuzzerController::beep(uint8_t amount) {
  if (currentAmountLeft>0) return;
  
  currentAmountLeft = amount;
  currentIsBeep = true;
  updateNow();
}
