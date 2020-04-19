#include "SmokerController.h"
#include <LogHelper.h>

#include "TempController.h"
#include "IOController.h"

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
  pinMode(PIN_HEATER, OUTPUT);

  heaterState.init(PROP_HEATER, false, HEATER_DELAY_MS);
}

void SmokerController::update() {
  if (mIsRunning) {
    heaterState.setValue(currentProfile.insideTemp>taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getInsideTemperature());

    // check meat target temp
    if (taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getMeatTemperature()>=currentProfile.meatTargetTemp) {
      // target temp reached
      if (currentProfile.autoStop) {
        stop();
      }
    }
  } else {
    heaterState.setValue(false);
  }
}

void SmokerController::start() {
  LOG_PRINT(F("Starting with profile "));
  LOG_PRINTLN(currentProfile.name);
  
  startTime = millis();
  mIsRunning = true;
}

void SmokerController::stop() {
  LOG_PRINTLN(F("Stopping"));
  
  mIsRunning = false;
}

uint64_t SmokerController::getDuration() {
  if (!mIsRunning) return 0;
  return millis() - startTime;
}

bool SmokerController::isRunning() {
  return this->mIsRunning;
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
