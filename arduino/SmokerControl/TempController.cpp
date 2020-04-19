#include "TempController.h"

#include "AnalogTempSensor.h"

#include "TaskIDs.h"
#include <LogHelper.h>

TempController::TempController() : AbstractIntervalTask(1000) {
  
}

TempController::~TempController() {
  delete max1;
  delete max2;
}

void TempController::init() {
  max1 = new Adafruit_MAX31865(PIN_INSIDE_MAX_CS1);
  max1->begin(MAX31865_3WIRE);  // set to 2WIRE or 4WIRE as necessary

  max2 = new Adafruit_MAX31865(PIN_INSIDE_MAX_CS2);
  max2->begin(MAX31865_3WIRE);  // set to 2WIRE or 4WIRE as necessary

  meatTemp1.init(PIN_MEAT_TEMP1, 10, 0, 100000.0);
  meatTemp2.init(PIN_MEAT_TEMP2, 10, 0, 100000.0);
}

void TempController::update() {
  meatTemp1.read();
  meatTemp2.read();

  updateTemp(max1, &insideTemp1, RREF1);
  updateTemp(max2, &insideTemp2, RREF2);
}

void TempController::updateTemp(Adafruit_MAX31865* maxRef, SmoothValue *temp, float rref) {
  uint16_t rtd = maxRef->readRTD();
  //LOG_PRINT("RTD value: "); 
  //LOG_PRINTLN(rtd);
  
  float ratio = rtd;
  ratio /= 32768;
  //Serial.print("Ratio = "); Serial.println(ratio,8);
  //Serial.print("Resistance = "); Serial.println(RREF*ratio,8);
  //LOG_PRINT("Temperature = "); 
  //LOG_PRINTLN(max1->temperature(RNOMINAL, RREF));

  // Check and print any faults
  uint8_t fault = maxRef->readFault();
  if (fault) {
    //Serial.print("Fault 0x"); Serial.println(fault, HEX);
    if (fault & MAX31865_FAULT_HIGHTHRESH) {
      LOG_PRINTLN(F("RTD High Threshold")); 
    }
    if (fault & MAX31865_FAULT_LOWTHRESH) {
      LOG_PRINTLN(F("RTD Low Threshold")); 
    }
    if (fault & MAX31865_FAULT_REFINLOW) {
      LOG_PRINTLN(F("REFIN- > 0.85 x Bias")); 
    }
    if (fault & MAX31865_FAULT_REFINHIGH) {
      LOG_PRINTLN("REFIN- < 0.85 x Bias - FORCE- open"); 
    }
    if (fault & MAX31865_FAULT_RTDINLOW) {
      LOG_PRINTLN(F("RTDIN- < 0.85 x Bias - FORCE- open")); 
    }
    if (fault & MAX31865_FAULT_OVUV) {
      LOG_PRINTLN(F("Under/Over voltage")); 
    }
    maxRef->clearFault();
  } else {
    temp->pushValue(maxRef->temperature(RNOMINAL, rref));
  }
}

float TempController::getInsideTemperature() {
  return (insideTemp1.getValue() + insideTemp2.getValue()) / 2;
}

float TempController::getInsideTemperature1() {
  return insideTemp1.getValue();
}

float TempController::getInsideTemperature2() {
  return insideTemp2.getValue();
}

float TempController::getMeatTemperature() {
  return (meatTemp1.getValueC() + meatTemp2.getValueC()) / 2;
}

float TempController::getMeatTemperature1() {
  return meatTemp1.getValueC();
}

float TempController::getMeatTemperature2() {
  return meatTemp2.getValueC();
}
