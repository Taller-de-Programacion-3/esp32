//
// Created by javier on 22/07/22.
//

#include <Arduino.h>
#include <WString.h>
#include "LedOnTask.hpp"
#include "constants.h"
#include "ControllerServer.hpp"
#include "ResponseBuilder.h"

LedOnTask::LedOnTask(int id): taskId(id) {}

void LedOnTask::execute() {
    analogWrite(Led_Red, 255);
}

void LedOnTask::sendResponse(ControllerServer &server) {
    auto fields = std::map<String, int>();
    fields.emplace(std::pair<String, int>("value", 1));
    fields.emplace(std::pair<String, int>("id", this->taskId));
    String response = ResponseBuilder::buildJSONResponse(fields);
    server.sendResponse(response.c_str());
}


