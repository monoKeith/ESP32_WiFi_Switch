#ifndef IOCONTROL_H
#define IOCONTROL_H

#include <Arduino.h>
#include "state.h"
#include "config.h"

class IoControl
{
public:
    // Must call to register interruptions
    void setup();
    // Refresh output
    void refresh();

protected:
    static void white();
    static void gray();
    static void black();

};

#endif