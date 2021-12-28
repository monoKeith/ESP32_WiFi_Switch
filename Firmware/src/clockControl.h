#ifndef CLOCKCONTROL_H
#define CLOCKCONTROL_H

#include <Arduino.h>
#include "state.h"
#include "time.h"
#include "config.h"

namespace clockControl
{
    extern void setup();
    extern void update();
}

#endif