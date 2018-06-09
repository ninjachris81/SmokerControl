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
  SSD1306Text display;
  
};

#endif
