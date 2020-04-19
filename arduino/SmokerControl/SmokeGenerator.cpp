#include "SmokeGenerator.h"

SmokeGenerator::SmokeGenerator() : AbstractIntervalTask(100) {
  startTime = 0;
}

void SmokeGenerator::init() {
  emitterServo.attach(PIN_SMOKE_SERVO);
  emitterServo.write(0);
}

void SmokeGenerator::update() {
  switch(smokeState) {
    case SMOKE_RELOAD:
      if (millis() - startTime > EMIT_DURATION_MS) {
            // stop
            smokeState = SMOKE_IDLE;
            startTime = 0;
            emitterServo.write(0);
      }
      break;
  }  
}

void SmokeGenerator::emitSmoke() {
  if (smokeState==SMOKE_IDLE) {
    smokeState = SMOKE_RELOAD;
    startTime = millis();
    emitterServo.write(90);
  }
}
