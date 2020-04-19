#include "DisplayController.h"
#include <LogHelper.h>

//#include "WifiController.h"
#include "TempController.h"
#include "SmokerController.h"

#include "TaskIDs.h"

DisplayController::DisplayController() : AbstractIntervalTask(500) {
}

void DisplayController::init() {
  LOG_PRINTLN("Init display");

  display.begin(0x3C);

  display.clearDisplay();
}

void DisplayController::update() {
  if (taskManager->getTask<SmokerController*>(SMOKER_CONTROLLER)->isRunning()) {
    currentScreen = SCREEN_ONGOING;
  } else {
    currentScreen = SCREEN_HOME;
  }
  
  switch(currentScreen) {
    case SCREEN_HOME:
      //display.setLine(0, "Clients:    " + String(taskManager->getTask<WifiController*>(WIFI_CONTROLLER)->getConnectedClients()));
      display.setLine(1, alignText("InsideTemp1:", String(taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getInsideTemperature1()) + " C"));
      display.setLine(2, alignText("InsideTemp2:", String(taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getInsideTemperature2()) + " C"));
      display.setLine(3, alignText("MeatTemp1:", String(taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getMeatTemperature1()) + " C"));
      display.setLine(4, alignText("MeatTemp2:", String(taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getMeatTemperature2()) + " C"));
      display.setLine(5, F("---------------------"));
      display.setLine(6, String("Ready to start"));
      display.setLine(7, F(""));
      break;
    case SCREEN_ONGOING:
      display.setLine(0, taskManager->getTask<SmokerController*>(SMOKER_CONTROLLER)->getCurrentProfile().name);
      display.setLine(1, alignText("InsideTmp:", String(taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getInsideTemperature()) + " C"));
      display.setLine(2, alignText("InsideTgt:", String(taskManager->getTask<SmokerController*>(SMOKER_CONTROLLER)->getCurrentProfile().insideTemp) + " C"));
      display.setLine(3, alignText("MeatTemp:", String(taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getMeatTemperature()) + " C"));
      display.setLine(4, alignText("MeatTgt:", String(taskManager->getTask<SmokerController*>(SMOKER_CONTROLLER)->getCurrentProfile().meatTargetTemp) + " C"));
      display.setLine(5, alignText("MeatDelta:", String(taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getMeatTemperature() - taskManager->getTask<SmokerController*>(SMOKER_CONTROLLER)->getCurrentProfile().meatTargetTemp) + " C"));
      float duration = taskManager->getTask<SmokerController*>(SMOKER_CONTROLLER)->getDuration() / 1000;
      display.setLine(6, alignText("Duration:", String(duration, 0) + " s"));
      break;
  }
  
  display.render();
}

String DisplayController::alignText(String left, String right, uint8_t charsWidth) {
  String returnStr = "";

  returnStr.concat(left);

  for (uint8_t i=0;i<charsWidth - (left.length()+right.length());i++) {
    returnStr.concat(" ");
  }

  returnStr.concat(right);
  
  return returnStr;
}
