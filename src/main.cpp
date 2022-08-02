#include <Arduino.h>
#include <WiFi.h>
#include <memory>
#include <esp32/pm.h>
#include <esp_pm.h>
#include <esp_bt.h>
#include "ControllerServer.hpp"
#include "TasksResponse.hpp"
#include "constants.h"

const char ssid[] = "telecentro-4093";
const char key[] = "tele-7146058";
int status = WL_IDLE_STATUS;

void turnOnLed(uint8_t led) {
    analogWrite(led, 255);
}
void turnOffLed(uint8_t led) {
    analogWrite(led, 0);
}

void set_cpu_frequency() {
    // Set CPU frequency to lowest
    Serial.println("Setting CPU frequency");
    esp_pm_config_esp32_t config = {
            .max_freq_mhz=40,
            .min_freq_mhz=40,
    };
    auto res = esp_pm_configure(&config);
    if (res == ESP_ERR_INVALID_ARG) {
        Serial.println("Invalid arguments");
    } else if (res == ESP_ERR_NOT_SUPPORTED) {
        Serial.println("Config not supported");
    } else if (res == ESP_OK) {
        Serial.println("Configured CPU frequency OK");
    }
}

void setup() {
    // Disable bluetooth
    esp_bt_controller_disable();

    // Test led
    pinMode(Led_Red, OUTPUT);
    pinMode(Led_Green, OUTPUT);

    turnOnLed(Led_Green);
    delay(500);
    turnOffLed(Led_Green);

    // Initiate serial port for logging
    Serial.begin(115200);

    set_cpu_frequency();

    // Connect to Wi-Fi
    status = WiFiClass::status();

    // attempt to connect to Wifi network:
    while ( status != WL_CONNECTED) {
        Serial.print("Attempting to connect to network, SSID: ");
        Serial.println(ssid);
        WiFi.begin(ssid, key);
        status = WiFi.waitForConnectResult();

        // wait 10 seconds for connection:
        delay(10000);
    }
    Serial.println("You're connected to the network");
    // It is connected!
}

void loop() {

    ControllerServer server("http://taller3.loca.lt/devices/tasks/esp32");

    TasksResponse tasks = server.getTasks();

    while (tasks.hasMoreTasks()) {
        auto task = tasks.getNextTask();
        task->execute();
        task->sendResponse(server);
    }

    sleep(5);
}