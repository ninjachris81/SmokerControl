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
  String cStatus;
  
  currentLine = 0;
  
  switch(taskManager->getTask<SmokerController*>(SMOKER_CONTROLLER)->getStatus()) {
    case SmokerController::STATUS_PREHEATING:
      cStatus = F("Preheating");
      currentScreen = SCREEN_PREHEATING;
      break;
    case SmokerController::STATUS_READY:
      cStatus = F("Ready");
      currentScreen = SCREEN_ONGOING;
      break;
    case SmokerController::STATUS_RUNNING:
      cStatus = F("Smoking");
      currentScreen = SCREEN_ONGOING;
      break;
    case SmokerController::STATUS_TARGET_REACHED:
      cStatus = F("Target reached");
      currentScreen = SCREEN_FINISHED;
      break;
    case SmokerController::STATUS_FINISHED:
      cStatus = F("Finished");
      currentScreen = SCREEN_FINISHED;
      break;
    default:
      LOG_PRINTLN(F("Unknown status"));
      break;
  }
  
  float duration = taskManager->getTask<SmokerController*>(SMOKER_CONTROLLER)->getDuration() / 1000;

  switch(currentScreen) {
    case SCREEN_PREHEATING:
      nextLine(alignCenter(F("Smoker Control")));
      nextLine(F("---------------------"));
      nextLine(alignCenter(cStatus));
      nextLine(""); 
      nextLine(alignText("InsideTemp1:", String(taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getInsideTemperature1()) + " C"));
      nextLine(alignText("InsideTemp2:", String(taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getInsideTemperature2()) + " C"));
      nextLine(alignText("InsideTmp:", String(taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getInsideTemperature()) + " C"));
      nextLine(alignText("InsideTgt:", String(taskManager->getTask<SmokerController*>(SMOKER_CONTROLLER)->getCurrentProfile().insideTemp) + " C"));
      break;
    case SCREEN_ONGOING:
      nextLine(alignCenter(taskManager->getTask<SmokerController*>(SMOKER_CONTROLLER)->getCurrentProfile().name));
      nextLine(F("---------------------"));
      nextLine(alignText("InsideTmp:", String(taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getInsideTemperature()) + " C"));
      nextLine(alignText("InsideTgt:", String(taskManager->getTask<SmokerController*>(SMOKER_CONTROLLER)->getCurrentProfile().insideTemp) + " C"));
      nextLine(alignText("MeatTemp:", String(taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getMeatTemperature()) + " C"));
      nextLine(alignText("MeatTgt:", String(taskManager->getTask<SmokerController*>(SMOKER_CONTROLLER)->getCurrentProfile().meatTargetTemp) + " C"));
      nextLine(alignText("MeatDelta:", String(taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getMeatTemperature() - taskManager->getTask<SmokerController*>(SMOKER_CONTROLLER)->getCurrentProfile().meatTargetTemp) + " C"));
      nextLine(alignText("Duration:", String(duration, 0) + " s"));
      break;
    case SCREEN_FINISHED:
      nextLine(alignCenter(taskManager->getTask<SmokerController*>(SMOKER_CONTROLLER)->getCurrentProfile().name));
      nextLine(F("---------------------"));
      nextLine(alignCenter(cStatus));
      nextLine(""); 
      nextLine(alignText("InsideTmp:", String(taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getInsideTemperature()) + " C"));
      nextLine(alignText("MeatTemp:", String(taskManager->getTask<TempController*>(TEMP_CONTROLLER)->getMeatTemperature()) + " C"));
      nextLine(alignText("Duration:", String(duration, 0) + " s"));
      nextLine(""); 
      break;
    default:
      LOG_PRINTLN(F("Unknown screen"));
  }
  
  display.render();
}

void DisplayController::nextLine(String t) {
  display.setLine(currentLine, t);
  currentLine++;
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

String DisplayController::alignCenter(String t, uint8_t charsWidth) {
  String returnStr = "";

  for (uint8_t i=0;i<(charsWidth - t.length()) / 2;i++) {
    returnStr.concat(" ");
  }

  returnStr.concat(t);

  return returnStr;
}
