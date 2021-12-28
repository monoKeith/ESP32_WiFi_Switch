#ifndef STATE_H
#define STATE_H

#include <Arduino.h>
#include "time.h"
#include "config.h"

namespace state
{

    /* Clock synchronization */

    extern String lastSyncTime;

    extern bool clockInitialized;
    extern String displayTime;
    extern void setTime(tm *timeinfo);
    extern bool timeSyncRequired;

    /* Wi-Fi */

    extern bool wirelessConnected;
    extern String localIP;
    extern String wirelessRSSI;

    /* Message display */

    extern bool showMsg;
    extern String displayMsg;
    extern unsigned long messageEndTime;
    extern void newMessage(String msg);
    extern String getMessage();

    enum DisplayMode
    {
        REGULAR,
        DEBUG,
        OFF
    };
    extern DisplayMode displayMode;

    /* Switch */

    extern bool switchOn;

}

#endif