#ifndef DISPLAYCONTROLLER_H
#define DISPLAYCONTROLLER_H

#include <AbstractIntervalTask.h>

#include "ssd1306_text.h"
#include "Debug.h"

#define CHARS_WIDTH 21

class DisplayController : public AbstractIntervalTask {
  public:
    DisplayController();

    void init();

    void update();

private:
  enum SCREEN_ID {
    SCREEN_HOME,
    SCREEN_ONGOING
  };

  SSD1306Text display;
  SCREEN_ID currentScreen = SCREEN_HOME;

  String alignText(String left, String right, uint8_t charsWidth = CHARS_WIDTH);

};

#endif
