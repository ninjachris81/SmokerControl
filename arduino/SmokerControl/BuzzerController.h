#ifndef BUZZERCONTROLLER_H
#define BUTTONCONTROLLER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define BEEP_DURATION_MS 500

#include <AbstractIntervalTask.h>
#include "Pins.h"

class BuzzerController : public AbstractIntervalTask {
public:
    BuzzerController();

    void init();
    
    void update();

    void beep(uint8_t amount = 1);

    void stop();

private:
  uint8_t currentAmountLeft = 0;

  bool currentIsBeep = false;


};

#endif /* BUZZERCONTROLLER_H */
