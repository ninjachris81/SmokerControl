#ifndef TEMPCONTROLLER_H
#define TEMPCONTROLLER_H

#include <AbstractIntervalTask.h>
#include <AnalogTempSensor.h>
#include <Adafruit_MAX31865.h>

#include "Debug.h"
#include "Pins.h"

// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF1      438.0
#define RREF2      439.4
// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL  100.0

class TempController : public AbstractIntervalTask {
public:
  TempController();
  ~TempController();
  
  void init();

  void update();

  float getInsideTemperature();
  float getInsideTemperature1();
  float getInsideTemperature2();
  
  float getMeatTemperature();
  float getMeatTemperature1();
  float getMeatTemperature2();

private:
  Adafruit_MAX31865 *max1;
  Adafruit_MAX31865 *max2;
  
  SmoothValue insideTemp1;
  SmoothValue insideTemp2;
  
  AnalogTempSensor meatTemp1;
  AnalogTempSensor meatTemp2;

  void updateTemp(Adafruit_MAX31865* maxRef, SmoothValue *temp, float rref);
  
};


#endif
