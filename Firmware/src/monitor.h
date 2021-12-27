#ifndef DISPLAY_H
#define DISPLAY_H

// For a connection via I2C using the Arduino Wire include:
#include <Arduino.h>
#include <Wire.h>        // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h" // legacy: #include "SSD1306.h"
#include "time.h"
#include "state.h"
#include "config.h"
// OR #include "SH1106Wire.h"   // legacy: #include "SH1106.h"

// For a connection via I2C using brzo_i2c (must be installed) include:
// #include <brzo_i2c.h>        // Only needed for Arduino 1.6.5 and earlier
// #include "SSD1306Brzo.h"
// OR #include "SH1106Brzo.h"

// For a connection via SPI include:
// #include <SPI.h>             // Only needed for Arduino 1.6.5 and earlier
// #include "SSD1306Spi.h"
// OR #include "SH1106SPi.h"

// Optionally include custom images
// #include "images.h"

// Initialize the OLED display using Arduino Wire:
class Monitor
{

public:

    // Must call during initialization to init I2C connection
    void setup();
    // Update content of monitor based on current state
    void refresh();

protected:
    SSD1306Wire display = SSD1306Wire(0x3c, SDA_PIN, SCL_PIN);
    void drawFontFaceDemo();
    void drawTextFlowDemo();
    void drawTextAlignmentDemo();
    void drawRectDemo();
    void drawCircleDemo();
    void drawProgressBarDemo();
    void drawImageDemo();

};

#endif