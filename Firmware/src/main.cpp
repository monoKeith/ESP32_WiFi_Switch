#include <Arduino.h>
#include "config.h"
#include "state.h"
#include "monitor.h"
#include "ioControl.h"
#include "server.h"
#include "clockControl.h"

// Arduino Initialize
void setup()
{
    // Initialize display
    // TODO: show boot screen
    monitor::setup();
    monitor::refresh();

    // Setup GPIO interrupt
    ioControl::setup();

    // Setup HTTP server
    server::setup();

    // Setup clock
    clockControl::setup();
}

// Arduino run loop
void loop()
{
    // Update server status
    server::update();
    server::processRequests();

    // Update clock
    clockControl::update();

    // Refresh monitor
    monitor::refresh();

    // Refresh IO
    ioControl::refresh();

    // Done
    delay(10);
}
