//
// Created by javier on 22/07/22.
//

#include "ControllerServer.hpp"

ControllerServer::ControllerServer(const char *host) {
    this->httpClient.begin(host);
}

TasksResponse ControllerServer::getTasks() {
        auto httpStatusCode = this->httpClient.GET();
        if (httpStatusCode > 0) {
            if (httpStatusCode == HTTP_CODE_OK) {
                String payload = this->httpClient.getString();
                TasksResponse response(payload);
                return response;
            } else {
                Serial.println("Response Not OK");
                Serial.println(httpStatusCode);
                throw std::runtime_error("HTTP Response not OK");
            }
        } else {
            Serial.printf("GET failed with error %s\n", HTTPClient::errorToString(httpStatusCode).c_str());
            throw std::runtime_error("Error making request");
        }
}

int ControllerServer::sendResponse(const String& response) {
    this->httpClient.POST(response.c_str());
    return 0;
}
