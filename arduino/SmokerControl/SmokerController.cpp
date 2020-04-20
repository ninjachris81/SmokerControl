#include "SmokerController.h"
#include <LogHelper.h>

#include "TempController.h"
#include "IOController.h"
#include "BuzzerController.h"

#include "SmokeGenerator.h"
#include "TaskIDs.h"

SmokerController::SmokerController() : AbstractIntervalTask(1000) {
  // Pulled Pork as default
  currentProfile.name = F("Pulled Pork");
  currentProfile.insideTemp = 110;
  currentProfile.meatTargetTemp = 80;
  currentProfile.autoStop = true;

  startTime = 0;
}

void SmokerController::init() {
  heaterState.init(PROP_HEATER, false, HEATER_DELAY_MS);
  heaterState.registerValueChangeListener(this);
}

void SmokerController::update() {

  bool setHeaterState = true;
  
  switch(mStatus) {
    case STATUS_PREHEATING:
#ifdef IS_SIMULATION
      simulationDelay = 0;
#endif
      if (taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getInsideTemperature()>=currentProfile.insideTemp) setStatus(STATUS_READY);
      break;
    case STATUS_READY:
#ifdef IS_SIMULATION
      simulationDelay++;
      if (simulationDelay>10) start();
#endif
      break;
    case STATUS_RUNNING:
      // check meat target temp
      if (taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getMeatTemperature()>=currentProfile.meatTargetTemp) {
        // target temp reached
        if (currentProfile.autoStop) {
          stop();
        } else {
          // keep going
        }
      }
#ifdef IS_SIMULATION
      simulationDelay = 0;
#endif
      break;
    case STATUS_TARGET_REACHED:
      setHeaterState = false;
      taskManager->getTask<BuzzerController*>(BUZZER_CONTROLLER)->beep();

#ifdef IS_SIMULATION
      simulationDelay++;
      if (simulationDelay>10) finish();
#endif

      break;    
    case STATUS_FINISHED:
      setHeaterState = false;
      break;
  }

  heaterState.update();
  
  if (setHeaterState) {
    heaterState.setValue(currentProfile.insideTemp>taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getInsideTemperature());
  } else {
    heaterState.setValue(false);
  }
}

void SmokerController::setStatus(SmokerController::SMOKER_STATUS newState) {
  LOG_PRINT(F("New status "));
  LOG_PRINTLN(newState);
  
  mStatus = newState;
}

void SmokerController::start() {
  LOG_PRINT(F("Starting with profile "));
  LOG_PRINTLN(currentProfile.name);
  
  startTime = millis();
  setStatus(STATUS_RUNNING);
}

void SmokerController::stop() {
  LOG_PRINTLN(F("Stopping"));
  endTime = millis();
  setStatus(STATUS_TARGET_REACHED);
}

void SmokerController::finish() {
  LOG_PRINTLN(F("Finishing"));
  setStatus(STATUS_FINISHED);
}

uint64_t SmokerController::getDuration() {
  if (mStatus<STATUS_RUNNING) return 0;
  if (mStatus==STATUS_RUNNING) return millis() - startTime;
  if (mStatus>STATUS_RUNNING) return endTime - startTime;
}

SmokerController::SMOKER_STATUS SmokerController::getStatus() {
  return this->mStatus;
}

SmokerController::SmokerProfile SmokerController::getCurrentProfile() {
  return currentProfile;
}

void SmokerController::onPropertyValueChange(uint8_t id, bool newValue, bool oldValue) {
  switch(id) {
    case PROP_HEATER:
      taskManager->getTask<IOController*>(IO_CONTROLLER)->setState(HEATING_RELAY, newValue);
      break;
  }
}
