#include "SmokerController.h"
#include <LogHelper.h>

#include "TempController.h"
#include "SmokeGenerator.h"
#include "TaskIDs.h"

SmokerController::SmokerController() : AbstractIntervalTask(1000) {
  // Pulled Pork
  smokerProfiles[0].name = F("Pulled Pork");
  smokerProfiles[0].insideTemp = 110;
  smokerProfiles[0].meatTargetTemp = 80;
  smokerProfiles[0].autoStop = true;
}

void SmokerController::init() {
  pinMode(PIN_HEATER, OUTPUT);

  heaterState.init(PROP_HEATER, false, HEATER_DELAY_MS);
}

void SmokerController::update() {
  if (isRunning) {
    heaterState.setValue(smokerProfiles[currentProfile].insideTemp>taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getInsideTemperature());

    // check meat target temp
    if (taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getMeatTemperature()>=smokerProfiles[currentProfile].meatTargetTemp) {
      // target temp reached
      if (smokerProfiles[currentProfile].autoStop) {
        stop();
      }
    }
  } else {
    heaterState.setValue(false);
  }
}

void SmokerController::start(uint8_t smokerProfile) {
  LOG_PRINT(F("Starting with profile "));
  LOG_PRINTLN(smokerProfiles[smokerProfile].name);
  
  currentProfile = smokerProfile;
  startTime = millis();
  isRunning = true;
}

void SmokerController::stop() {
  LOG_PRINTLN(F("Stopping"));
  
  isRunning = false;
}

uint64_t SmokerController::getDuration() {
  if (isRunning) return 0;
  return millis() - startTime;
}

uint8_t SmokerController::getProfileCount() {
  return PROFILE_COUNT;
}

String SmokerController::getProfileName(uint8_t smokerProfile) {
  return smokerProfiles[smokerProfile].name;
}

SmokerController::SmokerProfile SmokerController::getCurrentProfile() {
  return smokerProfiles[currentProfile];
}

void SmokerController::onPropertyValueChange(uint8_t id, bool value) {
  LOG_PRINT(F("IO set to "));
  LOG_PRINT(id);
  LOG_PRINT(F(" to "));
  LOG_PRINTLN(value);
  
  switch(id) {
    case PROP_HEATER:
      digitalWrite(PIN_HEATER, value ? LOW : HIGH);
      break;
  }
}

