#ifndef SERVER_H
#define SERVER_H

#include <Arduino.h>
#include <WiFi.h>
#include "config.h"
#include "state.h"
// ESPAsyncWebServer imports:
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

namespace server
{
    extern void setup();
}

#endif