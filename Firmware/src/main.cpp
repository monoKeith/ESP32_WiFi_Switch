#include <Arduino.h>
#include <WiFi.h>
#include "time.h"
#include "monitor.h"
#include "config.h"
#include "state.h"

// State of everything
State state;
// OLED display controller
Monitor monitor(&state);

// Arduino Initialize
void setup()
{
    // Initialize
    monitor.setup();
    monitor.refresh();
    // Start Wi-Fi
    WiFi.begin(ssid, password);
    // TODO: Setup GPIO interrupt
}

void updateClock()
{
    if (state.wirelessConnected && state.timeSyncRequired)
    {
        // Sync time from server
        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
        state.timeSyncRequired = false;
    }
    if (!state.timeSyncRequired)
    {
        // Update time in state
        struct tm timeinfo;
        if (!getLocalTime(&timeinfo))
        {
            return;
        }
        state.setTime(&timeinfo);
    }
}

// Arduino run loop
void loop()
{
    // Update WiFi status
    state.wirelessConnected = (WiFi.status() == WL_CONNECTED);
    // Update clock
    updateClock();

    // Refresh monitor
    monitor.refresh();
    delay(10);
}
