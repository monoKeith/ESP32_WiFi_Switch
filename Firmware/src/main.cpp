#include <Arduino.h>
#include <WiFi.h>
#include "time.h"
#include "monitor.h"
#include "ioControl.h"
#include "config.h"
#include "state.h"



// IoControl controller
IoControl ioControl;
// OLED display controller
Monitor monitor;

// Arduino Initialize
void setup()
{
    // Initialize display
    monitor.setup();
    monitor.refresh();
    
    // Setup GPIO interrupt
    ioControl.setup();

    // Start Wi-Fi
    WiFi.begin(ssid, password);
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
    // Update WiFi status
    state::wirelessConnected = (WiFi.status() == WL_CONNECTED);
    // Update clock
    updateClock();

    // Refresh monitor
    monitor.refresh();
    // Refresh IO
    ioControl.refresh();
    delay(10);
}
