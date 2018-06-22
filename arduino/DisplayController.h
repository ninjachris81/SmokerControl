#ifndef DISPLAYCONTROLLER_H
#define DISPLAYCONTROLLER_H

#include <AbstractIntervalTask.h>

#include "ssd1306_text.h"
#include "Debug.h"

class DisplayController : public AbstractIntervalTask {
  public:
    DisplayController();

    void init();

    void update();

private:
  enum SCREEN_ID {
    SCREEN_HOME,
    SCREEN_START
  };

  SSD1306Text display;
  SCREEN_ID currentScreen = SCREEN_HOME;

  uint8_t currentLine = 0;

};

#endif
