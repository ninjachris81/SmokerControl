#ifndef IOCONTROLLER_H
#define IOCONTROLLER_H

#include <AbstractIdleTask.h>
#include <CD74HC4067.h>

#include "Debug.h"
#include "Pins.h"

class IOController : public AbstractIdleTask {
public:
  IOController();
  ~IOController();
  
  void init();

  int analogRead(uint8_t channel);
  
private:
  CD74HC4067 *mux;
};


#endif
