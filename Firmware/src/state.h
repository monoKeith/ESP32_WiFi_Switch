#ifndef STATE_H
#define STATE_H

#include <Arduino.h>
#include "time.h"

class State
{
public:
    String displayTime = "--:--";
    void setTime(tm *timeinfo);

    bool timeSyncRequired = true;
    bool wirelessConnected = false;
};

#endif