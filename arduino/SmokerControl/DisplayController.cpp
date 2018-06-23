#include "DisplayController.h"
#include <LogHelper.h>

#include "WifiController.h"
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
  switch(currentScreen) {
    case SCREEN_HOME:
      display.setLine(0, "Clients:     " + String(taskManager->getTask<WifiController*>(WIFI_CONTROLLER)->getConnectedClients()));
      display.setLine(1, "OutTemp:     " + String(taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getOutsideTemperature()) + " C");
      display.setLine(2, "OutHumidity: " + String(taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getOutsideHumidity()) + " %");
      display.setLine(3, "InTemp:      " + String(taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getInsideTemperature()) + " C");
      display.setLine(4, "MeatTemp:    " + String(taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getMeatTemperature()) + " C");
      display.setLine(5, F("--------------------"));
      display.setLine(6, (currentLine==0 ? "> " : "") + String("Start"));
      display.setLine(7, F(""));
      break;
    case SCREEN_START:
      display.setLine(0, (currentLine==0 ? "> " : "") + String("Back"));
      for (uint8_t i=0; i<min((int)taskManager->getTask<SmokerController*>(SMOKER_CONTROLLER)->getProfileCount(), 7); i++) {
        display.setLine(i+1, (currentLine==i+1 ? "> " : "") + taskManager->getTask<SmokerController*>(SMOKER_CONTROLLER)->getProfileName(i));
      }
      break;
  }
  
  display.render();
}
