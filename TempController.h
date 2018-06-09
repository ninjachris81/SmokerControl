#ifndef TEMPCONTROLLER_H
#define TEMPCONTROLLER_H

#include <AbstractIntervalTask.h>
#include <AnalogTempSensor.h>

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

private:
  float outsideHumidity = 0.0;
  float outsideTemperature = 0.0;
  
  float insideTemperature = 0.0;

  DHT *dht;

  AnalogTempSensor *analogTemp; 
};


#endif
