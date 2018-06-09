#include "TempController.h"

TempController::TempController() : AbstractIntervalTask(1000) {
  
}

TempController::~TempController() {
  delete dht;
  delete analogTemp;
}

void TempController::init() {
  dht = new DHT(PIN_DHT11, DHT11);
  dht->begin();

  analogTemp = new AnalogTempSensor();
  analogTemp->init(PIN_ANALOG_TEMP, 10, 0, 6000);
}

void TempController::update() {
  outsideHumidity = dht->readHumidity();
  outsideTemperature = dht->readTemperature();

  analogTemp->read();
}

float TempController::getOutsideHumidity() {
  return outsideHumidity;
}

float TempController::getOutsideTemperature() {
  return outsideTemperature;
}

float TempController::getInsideTemperature() {
  return analogTemp->getValueC();
}

