#ifndef BUZZERCONTROLLER_H
#define BUTTONCONTROLLER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


#include <AbstractIntervalTask.h>
#include "Pins.h"

class BuzzerController : public AbstractIntervalTask {
public:
    BuzzerController();

    void init();
    
    void update();

    void beep(uint16_t duration);

private:
  uint64_t startTime = 0;
  uint16_t currentDuration = 0;

};

#endif /* BUZZERCONTROLLER_H */
