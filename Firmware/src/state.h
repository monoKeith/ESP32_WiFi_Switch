#ifndef STATE_H
#define STATE_H

#include <Arduino.h>
#include "time.h"
#include "config.h"

namespace state{

    // Clock synchronization
    extern String lastSyncTime;

    // Clock related vars
    extern bool clockInitialized;
    extern String displayTime;
    extern void setTime(tm *timeinfo);
    extern bool timeSyncRequired;
    extern bool wirelessConnected;

    // Message related vars
    extern bool showMsg;
    extern String displayMsg;
    extern unsigned long messageEndTime;
    extern void newMessage(String msg);
    extern String getMessage();

    // Output vars
    extern bool switchOn;

    // Display mode
    enum DisplayMode {
        REGULAR,
        DEBUG,
        OFF
    };
    extern DisplayMode displayMode;
}


#endif