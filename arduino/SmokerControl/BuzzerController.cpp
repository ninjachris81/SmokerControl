#include "BuzzerController.h"
#include <LogHelper.h>
#include "Pins.h"

BuzzerController::BuzzerController() : AbstractIntervalTask(50) {
}

void BuzzerController::init() {
  pinMode(PIN_BUZZER, OUTPUT);
}

void BuzzerController::update() {
  if (startTime>0) {
    if (millis() - startTime > currentDuration) {
      noTone(PIN_BUZZER);
      digitalWrite(PIN_BUZZER, HIGH);
      startTime = 0;
    }
  }
}

void BuzzerController::beep(uint16_t duration) {
  if (startTime>0) return;    // still active
  
  currentDuration = duration;
  
  tone(PIN_BUZZER, 1000, duration);
  startTime = millis();
}
