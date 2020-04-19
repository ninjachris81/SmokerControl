#ifndef SMOKERCONTROLLER_H
#define SMOKERCONTROLLER_H

#include <AbstractIntervalTask.h>
#include "Debug.h"

#include "Pins.h"
#include "BehaviorProperty.h"

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

  SmokerController();
  
  void init();

  void update();

  void onPropertyValueChange(uint8_t id, bool newValue, bool oldValue);

  void start();

  void stop();

  uint64_t getDuration();

  bool isRunning();

  SmokerProfile getCurrentProfile();

private:
  uint64_t startTime;

  bool mIsRunning = false;
  
  BehaviorProperty<bool> heaterState;
  
  SmokerProfile currentProfile;
};


#endif
