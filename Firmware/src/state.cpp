#include "state.h"

namespace state
{

    /* Clock synchronization */

    bool timeSyncRequired = true;

    String lastSyncTime = "never";

    bool clockInitialized = false;

    String displayTime = "--:--";

    // Format time display as string
    void setTime(tm *timeinfo)
    {
        char buffer[6];
        snprintf(buffer, sizeof(buffer), "%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min);
        displayTime = String(buffer);
    }

    /* Wi-Fi */

    bool wirelessConnected = false;

    String localIP = "unknown";

    String wirelessRSSI = "unknown";

    /* Message display */

    bool showMsg = false;

    String displayMsg = "";

    unsigned long messageEndTime = 0;

    // Display a message on screen
    void newMessage(String msg)
    {
        showMsg = true;
        displayMsg = msg;
        messageEndTime = millis() + MSG_DISPLAY_MS;
    }

    String getMessage()
    {
        // When there is a message to show, and within display time
        if (showMsg && (millis() < messageEndTime))
        {
            return displayMsg;
        }
        else
        {
            showMsg = false;
        }
        return "";
    }

    /* Display mode */

    DisplayMode displayMode = REGULAR;

    /* Switch */

    bool switchOn = false;

};
