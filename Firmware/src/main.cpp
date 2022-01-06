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

void monitorThread(void *pvParameters)
{
    // Initialize display
    // TODO: show boot screen
    monitor::setup();

    while (true)
    {
        // Refresh monitor
        monitor::refresh();

        // Delay for 20ms
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
}

void serverThread(void *pvParameters)
{
    // Setup HTTP server
    server::setup();

    while (true)
    {
        // Update server status
        server::update();
        server::processRequests();

        // Delay for 10ms
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void clockThread(void *pvParameters)
{
    // Setup clock
    clockControl::setup();

    while (true)
    {
        // Update clock
        clockControl::update();
        // Delay for 500ms
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void ioThread(void *pvParameters)
{
    // Setup GPIO interrupt
    ioControl::setup();

    while (true)
    {
        // Refresh IO
        ioControl::refresh();

        // Delay for 100ms
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

// Arduino Initialize
void setup()
{
    xTaskCreate(monitorThread,
                "MonitorThread",
                STACK_SIZE_LARGE,
                NULL,
                3,
                NULL);

    xTaskCreate(ioThread,
                "IoThread",
                STACK_SIZE_TINY,
                NULL,
                1,
                NULL);

    xTaskCreate(serverThread,
                "ServerThread",
                STACK_SIZE_SMALL,
                NULL,
                4,
                NULL);

    xTaskCreate(clockThread,
                "ClockThread",
                STACK_SIZE_TINY,
                NULL,
                2,
                NULL);
}

// Arduino run loop
void loop()
{
    // Do nothing
    delay(1000);
}
