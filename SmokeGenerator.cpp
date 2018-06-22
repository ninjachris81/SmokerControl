#include "SmokeGenerator.h"

SmokeGenerator::SmokeGenerator() : AbstractIntervalTask(500) {
  
}

void SmokeGenerator::init() {
}

void SmokeGenerator::update() {
  switch(smokeState) {
    case SMOKE_RELOAD:
    
    break;
  }  
}

void SmokeGenerator::emitSmoke() {
  if (smokeState==SMOKE_IDLE) {
    smokeState = SMOKE_RELOAD;
  }
}

