#ifndef IOCONTROL_H
#define IOCONTROL_H

#include <Arduino.h>
#include "state.h"
#include "config.h"

namespace ioControl
{
    // Must call to register interruptions
    extern void setup();
    // Refresh output
    extern void refresh();

    extern void white();
    extern void gray();
    extern void black();

};

#endif