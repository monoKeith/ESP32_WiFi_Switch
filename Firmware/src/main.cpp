#include <Arduino.h>
#include "config.h"
#include "state.h"
#include "monitor.h"
#include "ioControl.h"
#include "server.h"
#include "clockControl.h"

// stack sizes?
const int STACK_SIZE_LARGE = 65536;
const int STACK_SIZE_SMALL = 32768;
const int STACK_SIZE_TINY = 16384;

void connectionWatch(void *pvParameters)
{
    // Start Wi-Fi
    // https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/
    while (true)
    {
        if (state::wirelessConnected)
        {
            // Check again in 5s
            delay(5000);
            continue;
        }

        // Setup connection
        WiFi.disconnect();
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, password);

        unsigned long startAttemptTime = millis();

        while (!state::wirelessConnected && (millis() - startAttemptTime < WIFI_TIMEOUT_MS))
        {
            delay(500);
        }
    }
}

void monitorThread(void *pvParameters)
{
    // Initialize display
    // TODO: show boot screen
    monitor::setup();

    while (true)
    {
        // Delay for 50ms, ~14 fps
        delay(50);
        // Refresh monitor, takes about 20ms?
        monitor::refresh();
    }
}

void ioThread(void *pvParameters)
{
    while (true)
    {
        // Delay for 100ms
        delay(100);
        // Refresh IO
        ioControl::refresh();
    }
}

// Arduino Initialize
void setup()
{
    // Setup WiFi connection watchdog
    xTaskCreatePinnedToCore(connectionWatch,
                            "ConnectionThread",
                            STACK_SIZE_TINY,
                            NULL,
                            5,
                            NULL,
                            CONFIG_ARDUINO_RUN_CORE0);

    // Setup display
    xTaskCreate(monitorThread,
                "MonitorThread",
                STACK_SIZE_SMALL,
                NULL,
                2,
                NULL);

    // Setup clock
    clockControl::setup();

    // Setup web server
    server::setup();

    // Setup GPIO interrupt (for buttons)
    ioControl::setup();
    xTaskCreate(ioThread,
                "IoThread",
                STACK_SIZE_TINY,
                NULL,
                1,
                NULL);
}

// Arduino run loop
void loop()
{
    // Update WiFi status
    state::wirelessConnected = (WiFi.status() == WL_CONNECTED);
    if (state::wirelessConnected)
    {
        // Update local IP and RSSI
        state::localIP = WiFi.localIP().toString();
        state::wirelessRSSI = String(WiFi.RSSI()) + "dBm";
    }

    // Update clock, clock control cannot run as a Task?
    clockControl::update();

    // Done
    delay(500);
}
