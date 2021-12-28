/**
   The MIT License (MIT)

   Copyright (c) 2018 by ThingPulse, Daniel Eichhorn
   Copyright (c) 2018 by Fabrice Weinberg

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.

   ThingPulse invests considerable time and money to develop these open source libraries.
   Please support us by buying our products (and not the clones) from
   https://thingpulse.com

*/

#include "monitor.h"

namespace monitor
{

    SSD1306Wire display = SSD1306Wire(0x3c, SDA_PIN, SCL_PIN);

    int counter = 1;

    void setup()
    {
        // Initialising the UI will init the display too.
        display.init();

        display.flipScreenVertically();
        display.setFont(ArialMT_Plain_10);
    }

    void drawFontFaceDemo()
    {
        // Font Demo1
        // create more fonts at http://oleddisplay.squix.ch/
        display.setTextAlignment(TEXT_ALIGN_LEFT);
        display.setFont(ArialMT_Plain_10);
        display.drawString(0, 0, "Hello Keith");
        display.setFont(ArialMT_Plain_16);
        display.drawString(0, 10, "Hello Keith");
        display.setFont(ArialMT_Plain_24);
        display.drawString(0, 26, "Hello Keith");
    }

    void drawTextFlowDemo()
    {
        display.setFont(ArialMT_Plain_10);
        display.setTextAlignment(TEXT_ALIGN_LEFT);
        display.drawStringMaxWidth(0, 0, 128,
                                   "Lorem ipsum\n dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore.");
    }

    void drawTextAlignmentDemo()
    {
        // Text alignment demo
        display.setFont(ArialMT_Plain_10);

        // The coordinates define the left starting point of the text
        display.setTextAlignment(TEXT_ALIGN_LEFT);
        display.drawString(0, 10, "Left aligned (0,10)");

        // The coordinates define the center of the text
        display.setTextAlignment(TEXT_ALIGN_CENTER);
        display.drawString(64, 22, "Center aligned (64,22)");

        // The coordinates define the right end of the text
        display.setTextAlignment(TEXT_ALIGN_RIGHT);
        display.drawString(128, 33, "Right aligned (128,33)");
    }

    void drawRectDemo()
    {
        // Draw a pixel at given position
        for (int i = 0; i < 10; i++)
        {
            display.setPixel(i, i);
            display.setPixel(10 - i, i);
        }
        display.drawRect(12, 12, 20, 20);

        // Fill the rectangle
        display.fillRect(14, 14, 17, 17);

        // Draw a line horizontally
        display.drawHorizontalLine(0, 40, 20);

        // Draw a line horizontally
        display.drawVerticalLine(40, 0, 20);
    }

    void drawCircleDemo()
    {
        for (int i = 1; i < 8; i++)
        {
            display.setColor(WHITE);
            display.drawCircle(32, 32, i * 3);
            if (i % 2 == 0)
            {
                display.setColor(BLACK);
            }
            display.fillCircle(96, 32, 32 - i * 3);
        }
    }

    void drawProgressBarDemo()
    {
        int progress = counter % 100;
        // draw the progress bar
        display.drawProgressBar(0, 32, 120, 10, progress);

        // draw the percentage as String
        display.setTextAlignment(TEXT_ALIGN_CENTER);
        display.drawString(64, 15, String(progress) + "%");
    }

    void drawImageDemo()
    {
        // see http://blog.squix.org/2015/05/esp8266-nodemcu-how-to-create-xbm.html
        // on how to create xbm files
        // display.drawXbm(34, 14, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
    }

    void drawDebugScreen()
    {
        // Clear
        display.clear();

        // Switch state
        display.setFont(ArialMT_Plain_24);
        display.setTextAlignment(TEXT_ALIGN_LEFT);
        display.drawStringMaxWidth(0, 0, 128, (state::switchOn ? "ON" : "OFF"));

        // Local time
        display.setFont(ArialMT_Plain_24);
        display.setTextAlignment(TEXT_ALIGN_RIGHT);
        display.drawStringMaxWidth(128, 0, 128, state::displayTime);

        // Connection status
        display.setFont(ArialMT_Plain_10);
        display.setTextAlignment(TEXT_ALIGN_LEFT);
        String connectionStatus;
        if (state::wirelessConnected)
            connectionStatus = state::localIP + " " + state::wirelessRSSI;
        else
            connectionStatus = "Wi-Fi... " + String(ssid);
        display.drawString(0, 24, connectionStatus);

        // Message or Last Sync time
        String msg = state::getMessage();
        display.setFont(ArialMT_Plain_10);
        display.setTextAlignment(TEXT_ALIGN_LEFT);
        display.drawString(0, 34, (msg.isEmpty() ? ("CLOCK SYNC: " + state::lastSyncTime) : msg));

        // Msg end time
        display.setFont(ArialMT_Plain_10);
        display.setTextAlignment(TEXT_ALIGN_LEFT);
        display.drawString(0, 44, "MSG_END:");
        display.setTextAlignment(TEXT_ALIGN_RIGHT);
        display.drawString(128, 44, String(state::messageEndTime));

        // Uptime
        display.setFont(ArialMT_Plain_10);
        display.setTextAlignment(TEXT_ALIGN_LEFT);
        display.drawString(0, 54, "UPTIME:");
        display.setTextAlignment(TEXT_ALIGN_RIGHT);
        display.drawString(128, 54, String(millis()));

        // Done
        display.display();
    }

    void drawScreen()
    {
        // Clear
        display.clear();

        String msg = state::getMessage();

        if (msg.isEmpty())
        {
            // Only display time, no message
            display.setFont(Roboto_Mono_Medium_35);
            display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
            display.drawString(64, 32 + SCREEN_Y_OFFSET, state::displayTime);
        }
        else
        {
            // Right corner: small time
            display.setFont(Roboto_Mono_Medium_15);
            display.setTextAlignment(TEXT_ALIGN_RIGHT);
            display.drawString(128, SCREEN_Y_OFFSET, state::displayTime);
            // Message
            display.setFont(Roboto_Mono_Medium_18);
            display.setTextAlignment(TEXT_ALIGN_LEFT);
            display.drawStringMaxWidth(0, 18 + SCREEN_Y_OFFSET, 128, msg);
        }

        // Done
        display.display();
    }

    void blackScreen()
    {
        // Clear
        display.clear();
        // Done
        display.display();
    }

    void refresh()
    {
        switch (state::displayMode)
        {
        case state::DisplayMode::REGULAR:
            drawScreen();
            break;

        case state::DisplayMode::DEBUG:
            drawDebugScreen();
            break;

        default:
            blackScreen();
            break;
        }
    }

}