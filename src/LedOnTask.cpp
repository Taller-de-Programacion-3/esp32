//
// Created by javier on 22/07/22.
//

#include <Arduino.h>
#include <memory>
#include <cJSON.h>
#include "LedOnTask.hpp"
#include "constants.h"
#include "ControllerServer.hpp"

LedOnTask::LedOnTask(int id): taskId(id) {}

void LedOnTask::execute() {
    analogWrite(Led_Red, 255);
}

void LedOnTask::sendResponse(ControllerServer &server) {
    auto taskResult = std::unique_ptr<cJSON>(cJSON_CreateObject());

    cJSON_AddNumberToObject(taskResult.get(), "id", taskId);
    cJSON_AddNumberToObject(taskResult.get(), "value", 1);

    auto taskResultArray = std::unique_ptr<cJSON>(cJSON_CreateArray());
    cJSON_AddItemToArray(taskResultArray.get(), taskResult.get());

    server.sendResponse(cJSON_Print(taskResultArray.get()));
}
