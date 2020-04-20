#ifndef SMOKERCONTROLLER_H
#define SMOKERCONTROLLER_H

#include <AbstractIntervalTask.h>
#include "Debug.h"

#include "Pins.h"
#include "BehaviorProperty.h"
#include "Simulation.h"

#define PROP_HEATER 0

#define TARGET_TEMP_TOLERANCE 5.0

#define HEATER_DELAY_MS 20000

class SmokerController : public AbstractIntervalTask, public Property<bool>::ValueChangeListener {
public:
  struct SmokerProfile {
    String name;
    float insideTemp;
    float meatTargetTemp;
    bool autoStop;
  };

  enum SMOKER_STATUS {
    STATUS_PREHEATING,
    STATUS_READY,
    STATUS_RUNNING,
    STATUS_TARGET_REACHED,
    STATUS_FINISHED
  };

  SmokerController();
  
  void init();

  void update();

  void onPropertyValueChange(uint8_t id, bool newValue, bool oldValue);

  void start();

  void stop();

  void finish();

  uint64_t getDuration();

  SMOKER_STATUS getStatus();

  SmokerProfile getCurrentProfile();

private:
  uint64_t startTime;
  uint64_t endTime;

  void setStatus(SMOKER_STATUS newState);

  SMOKER_STATUS mStatus = STATUS_PREHEATING;
  
  BehaviorProperty<bool> heaterState;
  
  SmokerProfile currentProfile;

#ifdef IS_SIMULATION
  uint8_t simulationDelay = 0;
#endif

};


#endif
