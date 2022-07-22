//
// Created by javier on 22/07/22.
//

#include <Arduino.h>
#include <memory>
#include <cJSON.h>
#include "LedOffTask.hpp"
#include "constants.h"
#include "ControllerServer.hpp"

LedOffTask::LedOffTask(int id): taskId(id) {

}

void LedOffTask::execute() {
    analogWrite(Led_Red, 0);
}

void LedOffTask::sendResponse(ControllerServer &server) {
    auto taskResult = std::unique_ptr<cJSON>(cJSON_CreateObject());

    cJSON_AddNumberToObject(taskResult.get(), "id", this->taskId);
    cJSON_AddNumberToObject(taskResult.get(), "value", 0);

    auto taskResultArray = std::unique_ptr<cJSON>(cJSON_CreateArray());
    cJSON_AddItemToArray(taskResultArray.get(), taskResult.get());

    server.sendResponse(cJSON_Print(taskResultArray.get()));
}
