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
  uint8_t currentLine = 0;

  enum SCREEN_ID {
    SCREEN_PREHEATING,
    SCREEN_ONGOING,
    SCREEN_FINISHED
  };

  SSD1306Text display;
  SCREEN_ID currentScreen = SCREEN_PREHEATING;

  void nextLine(String t);

  String alignText(String left, String right, uint8_t charsWidth = CHARS_WIDTH);
  String alignCenter(String t, uint8_t charsWidth = CHARS_WIDTH);

};

#endif
