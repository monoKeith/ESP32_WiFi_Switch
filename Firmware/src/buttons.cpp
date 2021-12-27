#include "buttons.h"


// Initialize interruption
void Buttons::setup()
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
}

void Buttons::white()
{
    state::newMessage("white");
}

void Buttons::gray()
{
    state::newMessage("gray");
}

void Buttons::black()
{
    state::newMessage("black");
}