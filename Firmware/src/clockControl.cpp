#include "clockControl.h"
#include "ESP32TimerInterrupt.h"
#include "ESP32_ISR_Timer.h"

namespace clockControl
{

    // Timer to update clock periodically
    // https://github.com/khoih-prog/ESP32TimerInterrupt/blob/master/examples/TimerInterruptTest/TimerInterruptTest.ino
    void IRAM_ATTR ClockSyncRequest(void *timerNo)
    {
        TIMER_ISR_START(timerNo);
        state::timeSyncRequired = true;
        TIMER_ISR_END(timerNo);
    }

    ESP32Timer ITimer0(0);

    void setup()
    {
        // Setup timer
        ITimer0.attachInterruptInterval(TIME_SYNC_INTERVAL_MINUTES * 60000000, ClockSyncRequest);
    }

    void updateLocalTime()
    {
        // Update time in state
        struct tm timeinfo;
        if (!getLocalTime(&timeinfo))
        {
            return;
        }
        state::setTime(&timeinfo);
    }

    // Update clock on demand
    void update()
    {
        // https://randomnerdtutorials.com/esp32-date-time-ntp-client-server-arduino/
        if (state::wirelessConnected && state::timeSyncRequired)
        {
            // Sync time from server
            configTime(GMT_OFFSET_S, DAYLIGHT_OFFSET_S, NTP_SERVER);
            state::timeSyncRequired = false;
            state::clockInitialized = true;
            updateLocalTime();
            state::lastSyncTime = state::displayTime;
        }
        else if (state::clockInitialized)
        {
            updateLocalTime();
        }
    }

}