#include "server.h"

namespace server
{

    WiFiServer server;
    WiFiClient client;

    bool serverRunning = false;

    void setup()
    {
        // Start Wi-Fi
        WiFi.begin(ssid, password);
        // Init a server
        server = WiFiServer(80);
    }

    void update()
    {
        // Update WiFi status
        state::wirelessConnected = (WiFi.status() == WL_CONNECTED);
        if (state::wirelessConnected){
            if (!serverRunning){
                server.begin();
                serverRunning = true;
            }
        } else {
            serverRunning = false;
        }
    }

    void processRequests()
    {
        // https://randomnerdtutorials.com/esp32-web-server-arduino-ide/
        if (!state::wirelessConnected)
            return;

        client = server.available();

        if (!client){
            client.stop();
            return;
        }

        unsigned long timeoutMark = millis() + HTTP_TIMEOUT_MS;

        String header = "";
        String currentLine = "";

        while (client.connected() && (millis() < timeoutMark))
        {
            if (client.available())
            {
                char c = client.read();
                header += c;
                if (c == '\n')
                {
                    if (currentLine.length() == 0)
                    {
                        // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                        // and a content-type so the client knows what's coming, then a blank line:
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();

                        // turns the GPIO on and off
                        if (header.indexOf("GET /switch/on") >= 0)
                        {
                            // ON
                            state::newMessage("Switch ON (HTTP)");
                            state::switchOn = true;
                        }
                        else if (header.indexOf("GET /switch/off") >= 0)
                        {
                            // OFF
                            state::newMessage("Switch OFF (HTTP)");
                            state::switchOn = false;
                        }

                        // Display the HTML web page
                        client.println("<!DOCTYPE html><html>");
                        client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
                        client.println("<link rel=\"icon\" href=\"data:,\">");
                        // CSS to style the on/off buttons
                        // Feel free to change the background-color and font-size attributes to fit your preferences
                        client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
                        client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
                        client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
                        client.println(".button2 {background-color: #555555;}</style></head>");

                        // Web Page Heading
                        client.println("<body><h1>ESP32 WiFi Switch</h1>");

                        String currentState = (state::switchOn ? "ON" : "OFF");
                        client.println("<p>Switch - Current state: " + currentState + "</p>");

                        if (!state::switchOn)
                        {
                            client.println("<p><a href=\"/switch/on\"><button class=\"button\">ON</button></a></p>");
                        }
                        else
                        {
                            client.println("<p><a href=\"/switch/off\"><button class=\"button button2\">OFF</button></a></p>");
                        }

                        client.println("</body></html>");
                        client.println();
                        break;
                    }
                    else
                    {
                        currentLine = "";
                    }
                }
                else if (c != '\r')
                {
                    currentLine += c;
                }
            }
        }
        // Close the connection
        client.stop();
    }
}