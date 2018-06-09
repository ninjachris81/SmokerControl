#include "DisplayController.h"
#include <LogHelper.h>

#include "WifiController.h"
#include "TempController.h"

#include "TaskIDs.h"

DisplayController::DisplayController() : AbstractIntervalTask(500) {
}

void DisplayController::init() {
  LOG_PRINTLN("Init display");

  display.begin(0x3C);

  display.clearDisplay();
}

void DisplayController::update() {
  display.setLine(0, "Clients:     " + String(taskManager->getTask<WifiController*>(WIFI_CONTROLLER)->getConnectedClients()));
  display.setLine(1, "OutTemp:     " + String(taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getOutsideTemperature()) + " C");
  display.setLine(2, "OutHumidity: " + String(taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getOutsideHumidity()) + " %");
  display.setLine(3, "InTemp:      " + String(taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getInsideTemperature()) + " C");
  display.setLine(4, F("rrrrr"));
  display.setLine(5, F("rrrrrr"));
  display.setLine(6, F("rrrrrrr"));
  display.setLine(7, F("rrrrrrrr"));
  display.render();
}
