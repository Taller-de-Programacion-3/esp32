#include <Arduino.h>
#include <WiFi.h>
#include <memory>

const char ssid[] = "telecentro-4093";
const char key[] = "tele-7146058";
int status = WL_IDLE_STATUS;

std::unique_ptr<WiFiClient> client;

void setup() {
    // write your initialization code here
    Serial.begin(115200);
    client.reset(new WiFiClient());

    // attempt to connect to Wifi network:
    while ( status != WL_CONNECTED) {
        Serial.print("Attempting to connect to network, SSID: ");
        Serial.println(ssid);
        WiFi.begin(ssid, key);
        status = WiFi.waitForConnectResult();

        // wait 10 seconds for connection:
        delay(10000);
    }

    // once you are connected :
    Serial.println("You're connected to the network");

    if (client->connect("google.com", 80)) {
        Serial.println("Connected!");
        client->println("GET /search?q=arduino HTTP/1.0");
        client->println();
        auto response = client->readStringUntil('\n');
        Serial.println(response);
        client->stop();
    }
}

void loop() {
    delay(1000);

    Serial.println("Loop");
}