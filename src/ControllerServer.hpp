//
// Created by javier on 22/07/22.
//

#ifndef TEST_CONTROLLERSERVER_HPP
#define TEST_CONTROLLERSERVER_HPP


#include <HTTPClient.h>
#include "TasksResponse.hpp"

class ControllerServer {
private:
    HTTPClient httpClient;

public:
    explicit ControllerServer(const char *host);

    TasksResponse getTasks();

    int sendResponse(const String& response);

};


#endif //TEST_CONTROLLERSERVER_HPP
