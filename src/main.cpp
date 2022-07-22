#include <Arduino.h>
#include <cJSON.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <memory>

const char ssid[] = "telecentro-4093";
const char key[] = "tele-7146058";
int status = WL_IDLE_STATUS;

int Led_Red = 18;
int Led_Green = 19;

std::unique_ptr<HTTPClient> httpClient;
std::unique_ptr<WiFiClient> wifiClient;

void turnOnLed(uint8_t led) {
    analogWrite(led, 255);
}
void turnOffLed(uint8_t led) {
    analogWrite(led, 0);
}

void setup() {
    // Setup led pins
    pinMode(Led_Red, OUTPUT);
    pinMode(Led_Green, OUTPUT);

    turnOnLed(Led_Green);
    delay(2000);
    turnOffLed(Led_Green);

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
                cJSON* task = nullptr;
                cJSON_ArrayForEach(task, tasks) {
                    Serial.println(cJSON_Print(task));
                    auto taskNameJson = cJSON_GetObjectItemCaseSensitive(task, "task_name");
                    auto taskIDJson = cJSON_GetObjectItemCaseSensitive(task, "id");
                    if (!cJSON_IsString(taskNameJson)) {
                        Serial.println("Invalid task name");
                        continue;
                    }
                    if (!cJSON_IsNumber(taskIDJson)) {
                        Serial.println("Invalid task ID");
                        continue;
                    }
                    auto taskName = taskNameJson->valuestring;
                    int resultValue = -1;

                    Serial.printf("Task name %s\n", taskName);

                    if (String(taskName) == String("Led On")) {
                        Serial.println("Turning led on");
                        turnOnLed(Led_Red);
                        resultValue = 1;
                    }

                    if (String(taskName) == String("Led Off")) {
                        Serial.println("Turning led off");
                        turnOffLed(Led_Red);
                        resultValue = 0;
                    }

                    if (resultValue >= 0) {
                        auto taskId = taskIDJson->valueint;
                        auto taskResult = std::unique_ptr<cJSON>(cJSON_CreateObject());

                        cJSON_AddNumberToObject(taskResult.get(), "id", taskId);
                        cJSON_AddNumberToObject(taskResult.get(), "value", resultValue);

                        auto taskResultArray = std::unique_ptr<cJSON>(cJSON_CreateArray());
                        cJSON_AddItemToArray(taskResultArray.get(), taskResult.get());

                        Serial.printf("Sending result: %s\n", cJSON_Print(taskResultArray.get()));

                        httpClient->POST(cJSON_Print(taskResultArray.get()));
                    }
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