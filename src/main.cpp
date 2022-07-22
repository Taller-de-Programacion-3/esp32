#include <Arduino.h>
#include <WiFi.h>
#include <memory>
#include "ControllerServer.hpp"
#include "TasksResponse.hpp"
#include "constants.h"

const char ssid[] = "telecentro-4093";
const char key[] = "tele-7146058";
int status = WL_IDLE_STATUS;

std::unique_ptr<WiFiClient> wifiClient;

void turnOnLed(uint8_t led) {
    analogWrite(led, 255);
}
void turnOffLed(uint8_t led) {
    analogWrite(led, 0);
}

void setup() {
    // Test led
    pinMode(Led_Red, OUTPUT);
    pinMode(Led_Green, OUTPUT);

    turnOnLed(Led_Green);
    delay(2000);
    turnOffLed(Led_Green);

    // Connect to Wi-Fi
    Serial.begin(115200);

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

    // It is connected!
    Serial.println("You're connected to the network");

}

void loop() {

    ControllerServer server("https://taller3-backend.herokuapp.com/devices/tasks/esp32");

    TasksResponse tasks = server.getTasks();

    while (tasks.hasMoreTasks()) {
        auto task = tasks.getNextTask();
        task->execute();
        task->sendResponse(server);
    }

    delay(5000);
}