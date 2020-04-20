#include <LogHelper.h>
#include <SmoothValue.h>
#include <TaskManager.h>

#include "TempController.h"
#include "SmokerController.h"
#include "DisplayController.h"
#include "SmokeGenerator.h"
#include "IOController.h"
#include "BuzzerController.h"

TaskManager tm;

TempController tempController;
SmokerController smokerController;
DisplayController displayController;
SmokeGenerator smokeGenerator;
IOController ioController;
BuzzerController buzzerController;

void setup(void) {
  LOG_INIT();

  tm.registerTask(&tempController);
  tm.registerTask(&smokerController);
  tm.registerTask(&displayController);
  tm.registerTask(&smokeGenerator);
  tm.registerTask(&ioController);
  tm.registerTask(&buzzerController);

  tm.init();

  LOG_PRINTLN(F("Init complete"));

  buzzerController.beep();

  //smokerController.start();
}

void loop()
{
  tm.update();
  delay(10);
}
