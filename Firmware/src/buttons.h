#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>
#include "state.h"
#include "config.h"

class Buttons
{
public:
    void setup();

protected:
    static void white();
    static void gray();
    static void black();

};

#endif