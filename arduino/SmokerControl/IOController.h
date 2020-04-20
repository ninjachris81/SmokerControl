#ifndef IOCONTROLLER_H
#define IOCONTROLLER_H

#include <AbstractIdleTask.h>

#include "Debug.h"
#include "Pins.h"

#define STATES_COUNT 1

#define HEATING_RELAY 0

class IOController : public AbstractIdleTask {
public:
  IOController();
  
  void init();

  void setState(uint8_t index, bool on);

  bool getState(uint8_t index);
  
private:
  bool mStates[STATES_COUNT];

};


#endif
