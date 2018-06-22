#ifndef TEMPCONTROLLER_H
#define TEMPCONTROLLER_H

#include <AbstractIntervalTask.h>
#include <SmoothValue.h>

#include "Debug.h"
#include "Pins.h"

#include "DHT.h"

class TempController : public AbstractIntervalTask {
public:
  TempController();
  ~TempController();
  
  void init();

  void update();

  float getOutsideHumidity();
  float getOutsideTemperature();
  float getInsideTemperature();
  float getMeatTemperature();

private:
  float outsideHumidity = 0.0;
  float outsideTemperature = 0.0;

  DHT *dht;

  SmoothValue insideTemp;
  SmoothValue meatTemp;
};


#endif
