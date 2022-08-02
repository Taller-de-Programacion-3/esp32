//
// Created by javier on 22/07/22.
//

#include <map>
#include <WString.h>
#include "NullTask.h"
#include "ResponseBuilder.h"
#include "ControllerServer.hpp"

NullTask::NullTask(int id): taskId(id) {}

void NullTask::execute() {}

void NullTask::sendResponse(ControllerServer &server) {
    auto fields = std::map<String, int>();
    fields.emplace(std::pair<String, int>("not_supported", 1));
    fields.emplace(std::pair<String, int>("id", this->taskId));
    String response = ResponseBuilder::buildJSONResponse(fields);
    server.sendResponse(response.c_str());
}
