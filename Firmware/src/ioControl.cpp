#include "ioControl.h"

// Initialize interruption
void IoControl::setup()
{
    // White
    pinMode(WHITE_BUTTON_PIN, INPUT_PULLUP);
    attachInterrupt(WHITE_BUTTON_PIN, white, FALLING);
    // Gray
    pinMode(GRAY_BUTTON_PIN, INPUT_PULLUP);
    attachInterrupt(GRAY_BUTTON_PIN, gray, FALLING);
    // Black
    pinMode(BLACK_BUTTON_PIN, INPUT_PULLUP);
    attachInterrupt(BLACK_BUTTON_PIN, black, FALLING);

    // Output pin
    pinMode(SWITCH_PIN, OUTPUT);
}

/* Button Press Callback functions */

void IoControl::white()
{
    state::newMessage("Switch ON (Local)");
    state::switchOn = true;
}

void IoControl::gray()
{
    state::newMessage("Switch OFF (Local)");
    state::switchOn = false;
}

void IoControl::black()
{
    switch (state::displayMode)
    {
    case state::DisplayMode::REGULAR:
        state::displayMode = state::DisplayMode::DEBUG;
        break;

    case state::DisplayMode::DEBUG:
        state::displayMode = state::DisplayMode::OFF;
        break;

    default:
        state::displayMode = state::DisplayMode::REGULAR;
        break;
    }
}

/* IO output control */

void IoControl::refresh()
{
    // switch
    digitalWrite(SWITCH_PIN, state::switchOn ? HIGH : LOW);
}