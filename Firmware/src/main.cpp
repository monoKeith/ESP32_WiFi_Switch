#include <Arduino.h>
#include "time.h"
#include "monitor.h"
#include "ioControl.h"
#include "config.h"
#include "state.h"
#include "server.h"

#include "ESP32TimerInterrupt.h"
#include "ESP32_ISR_Timer.h"

// IoControl controller
IoControl ioControl;

// Timer to update clock periodically
// https://github.com/khoih-prog/ESP32TimerInterrupt/blob/master/examples/TimerInterruptTest/TimerInterruptTest.ino
void IRAM_ATTR ClockSyncRequest(void *timerNo)
{
    TIMER_ISR_START(timerNo);
    state::timeSyncRequired = true;
    TIMER_ISR_END(timerNo);
}

ESP32Timer ITimer0(0);

// Arduino Initialize
void setup()
{
    // Initialize display
    // TODO: show boot screen
    monitor::setup();
    monitor::refresh();

    // Setup GPIO interrupt
    ioControl.setup();

    // Setup HTTP server
    server::setup();

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
void updateClock()
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

// Arduino run loop
void loop()
{
    // Update server status
    server::update();
    server::processRequests();

    // Update clock
    updateClock();

    // Refresh monitor
    monitor::refresh();
    // Refresh IO
    ioControl.refresh();
    delay(10);
}
