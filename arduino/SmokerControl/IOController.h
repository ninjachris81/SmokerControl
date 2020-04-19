#ifndef IOCONTROLLER_H
#define IOCONTROLLER_H

#include <AbstractIdleTask.h>

#include "Debug.h"
#include "Pins.h"

#define HEATING_RELAY 0

class IOController : public AbstractIdleTask {
public:
  IOController();
  
  void init();

  void setState(uint8_t index, bool on);
  
private:

};


#endif
