//
// Created by javier on 22/07/22.
//

#include <memory>
#include <cJSON.h>
#include "ResponseBuilder.h"

String ResponseBuilder::buildJSONResponse(const std::map<String, int>& fields) {
    auto taskResult = std::unique_ptr<cJSON>(cJSON_CreateObject());

    for (const auto& field : fields) {
        cJSON_AddNumberToObject(taskResult.get(), field.first.c_str(), field.second);
        cJSON_AddNumberToObject(taskResult.get(), field.first.c_str(), field.second);
    }

    auto taskResultArray = std::unique_ptr<cJSON>(cJSON_CreateArray());
    cJSON_AddItemToArray(taskResultArray.get(), taskResult.get());

    String response(cJSON_Print(taskResultArray.get()));
    return response;
}
