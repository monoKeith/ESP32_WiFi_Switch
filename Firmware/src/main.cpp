#include <Arduino.h>
#include "config.h"
#include "state.h"
#include "monitor.h"
#include "ioControl.h"
#include "server.h"
#include "clockControl.h"

// stack size 64 KBytes?
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
            // Check again in 10s
            delay(10000);
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
        // Delay for 50ms, ~15 fps
        delay(50);
        // Refresh monitor
        monitor::refresh();
    }
}

void serverThread(void *pvParameters)
{
    // Setup HTTP server
    server::setup();

    while (true)
    {
        // Delay for 10ms
        delay(10);
        // Update server status
        server::update();
        server::processRequests();
    }
}

void clockThread(void *pvParameters)
{
    // Setup clock
    clockControl::setup();

    while (true)
    {
        // Delay for 500ms
        delay(500);
        // Update clock
        clockControl::update();
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
    xTaskCreatePinnedToCore(connectionWatch,
                            "ConnectionThread",
                            STACK_SIZE_TINY,
                            NULL,
                            configMAX_PRIORITIES - 1,
                            NULL,
                            CONFIG_ARDUINO_RUN_CORE0);

    xTaskCreate(serverThread,
                "ServerThread",
                STACK_SIZE_LARGE,
                NULL,
                5,
                NULL);

    xTaskCreate(monitorThread,
                "MonitorThread",
                STACK_SIZE_SMALL,
                NULL,
                2,
                NULL);

    xTaskCreate(clockThread,
                "ClockThread",
                STACK_SIZE_SMALL,
                NULL,
                4,
                NULL);

    // Setup GPIO interrupt
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
    // Do nothing
    delay(1000);
}
