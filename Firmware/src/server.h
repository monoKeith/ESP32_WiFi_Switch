#ifndef SERVER_H
#define SERVER_H

#include <Arduino.h>
#include <WiFi.h>
#include "config.h"
#include "state.h"

namespace server
{
    extern void setup();
    extern void update();
    extern void processRequests();
}

#endif