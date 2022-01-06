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

    void setup()
    {
        display.init();
        display.flipScreenVertically();
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
