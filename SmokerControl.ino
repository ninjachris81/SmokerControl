#include <LogHelper.h>
#include <SmoothValue.h>
#include <ESP8266WiFi.h>
#include <TaskManager.h>

#include "TempController.h"
#include "WifiController.h"
#include "SmokerController.h"
#include "DisplayController.h"

TaskManager tm;

TempController tempController;
WifiController wifiController;
SmokerController smokerController;
DisplayController displayController;

void setup(void) {
  LOG_INIT();

  tm.registerTask(&tempController);
  tm.registerTask(&wifiController);
  tm.registerTask(&smokerController);
  tm.registerTask(&displayController);

  tm.init();
  LOG_PRINTLN(F("Init complete"));
}

void loop()
{
  tm.update();
  delay(10);
}


