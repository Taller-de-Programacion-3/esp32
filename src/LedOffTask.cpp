//
// Created by javier on 22/07/22.
//

#include <Arduino.h>
#include <WString.h>
#include <memory>
#include <cJSON.h>
#include <map>
#include "LedOffTask.hpp"
#include "constants.h"
#include "ControllerServer.hpp"
#include "ResponseBuilder.h"

LedOffTask::LedOffTask(int id): taskId(id) {

}

void LedOffTask::execute() {
    analogWrite(Led_Red, 0);
}

void LedOffTask::sendResponse(ControllerServer &server) {
    auto fields = std::map<String, int>();
    fields.emplace(std::pair<String, int>("value", 0));
    fields.emplace(std::pair<String, int>("id", this->taskId));
    String response = ResponseBuilder::buildJSONResponse(fields);
    server.sendResponse(response.c_str());
}
