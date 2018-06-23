#include "TempController.h"

#include "AnalogTempSensor.h"

#include "TaskIDs.h"
#include "IOController.h"
#include "AnalogChannels.h"

TempController::TempController() : AbstractIntervalTask(500) {
  
}

TempController::~TempController() {
  delete dht;
}

void TempController::init() {
  dht = new DHT(PIN_DHT11, DHT11);
  dht->begin();

  outsideHumidity.init(10, 0);
  outsideTemperature.init(10, 0);

  insideTemp.init(10, 0);
  meatTemp.init(10, 0);
}

void TempController::update() {
  float f = dht->readHumidity();
  if (!isnan(f)) outsideHumidity.pushValue(f);
  
  f = dht->readTemperature();
  if (!isnan(f)) outsideTemperature.pushValue(f);

  insideTemp.pushValue(taskManager->getTask<IOController*>(IO_CONTROLLER)->analogRead(CHANNEL_INSIDE_TEMP));
  meatTemp.pushValue(taskManager->getTask<IOController*>(IO_CONTROLLER)->analogRead(CHANNEL_MEAT_TEMP));
}

float TempController::getOutsideHumidity() {
  return outsideHumidity.getValue();
}

float TempController::getOutsideTemperature() {
  return outsideTemperature.getValue();
}

float TempController::getInsideTemperature() {
  return AnalogTempSensor::toCelsius(insideTemp.getValue(), 6000);
}

float TempController::getMeatTemperature() {
  return AnalogTempSensor::toCelsius(meatTemp.getValue(), 6000);
}

