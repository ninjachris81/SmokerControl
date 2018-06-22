#ifndef SMOKEGENERATOR_H
#define SMOKEGENERATOR_H

#include <AbstractIntervalTask.h>

#include "Debug.h"
#include "Pins.h"

class SmokeGenerator : public AbstractIntervalTask {
public:
  SmokeGenerator();
  
  void init();

  void update();

  void emitSmoke();

private:
  enum SMOKE_STATE {
    SMOKE_IDLE,
    SMOKE_RELOAD
  };

  SMOKE_STATE smokeState = SMOKE_IDLE;

};


#endif
