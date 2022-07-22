#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <cJSON.h>
#include <memory>
const char ssid[] = "telecentro-4093";
const char key[] = "tele-7146058";
int status = WL_IDLE_STATUS;

std::unique_ptr<HTTPClient> httpClient;
std::unique_ptr<WiFiClient> wifiClient;

void setup() {
    // write your initialization code here
    Serial.begin(115200);

    httpClient.reset(new HTTPClient());
    wifiClient.reset(new WiFiClient());

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

}

void loop() {
    delay(5000);
    auto success = httpClient->begin("https://taller3-backend.herokuapp.com/devices/tasks/esp32");
    if (success) {
        Serial.println("Connected!");
        auto httpStatusCode = httpClient->GET();
        if (httpStatusCode > 0) {
            if (httpStatusCode == HTTP_CODE_OK) {

                Serial.println("Response OK");
                auto payload = httpClient->getString();

                // Parse JSON
                auto json = std::unique_ptr<cJSON>(cJSON_Parse(payload.c_str()));
                auto tasks = cJSON_GetObjectItem(json.get(), "tasks");

                Serial.println("Got tasks:");

                // Iterate over tasks array
                auto task = tasks->child;
                while (task) {
                    Serial.println(cJSON_Print(task));
                    task = task->next;
                }

            } else {
                Serial.println("Response Not OK");
                Serial.println(httpStatusCode);
            }
        } else {
            Serial.printf("GET failed with error %s\n", httpClient->errorToString(httpStatusCode).c_str());
        }
    }
}