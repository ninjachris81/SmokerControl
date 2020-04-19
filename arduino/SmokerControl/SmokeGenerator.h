#ifndef SMOKEGENERATOR_H
#define SMOKEGENERATOR_H

#include <AbstractIntervalTask.h>

#include <Servo.h>

#include "Debug.h"
#include "Pins.h"

#define EMIT_DURATION_MS 1000

class SmokeGenerator : public AbstractIntervalTask {
public:
  SmokeGenerator();
  
  void init();

  void update();

  void emitSmoke();

private:
  uint64_t startTime;

  enum SMOKE_STATE {
    SMOKE_IDLE,
    SMOKE_RELOAD
  };

  SMOKE_STATE smokeState = SMOKE_IDLE;

  Servo emitterServo;

};


#endif
