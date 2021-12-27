#include <Arduino.h>
#include "time.h"
#include "monitor.h"
#include "ioControl.h"
#include "config.h"
#include "state.h"
#include "server.h"

// IoControl controller
IoControl ioControl;
// OLED display controller
Monitor monitor;

// Arduino Initialize
void setup()
{
    // Initialize display
    // TODO: show boot screen
    monitor.setup();
    monitor.refresh();

    // Setup GPIO interrupt
    ioControl.setup();

    // Setup HTTP server
    server::setup();
}

// Update state var related to time
void updateClock()
{
    // https://randomnerdtutorials.com/esp32-date-time-ntp-client-server-arduino/
    if (state::wirelessConnected && state::timeSyncRequired)
    {
        // Sync time from server
        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
        state::timeSyncRequired = false;
    }
    if (!state::timeSyncRequired)
    {
        // Update time in state
        struct tm timeinfo;
        if (!getLocalTime(&timeinfo))
        {
            return;
        }
        state::setTime(&timeinfo);
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
    monitor.refresh();
    // Refresh IO
    ioControl.refresh();
    delay(10);
}
