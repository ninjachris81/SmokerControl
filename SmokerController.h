#ifndef SMOKERCONTROLLER_H
#define SMOKERCONTROLLER_H

#include <AbstractIntervalTask.h>
#include "Debug.h"

class SmokerController : public AbstractIntervalTask {
public:
  SmokerController();
  
  void init();

  void update();
};


#endif
