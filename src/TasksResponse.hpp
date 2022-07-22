//
// Created by javier on 22/07/22.
//

#ifndef TEST_TASKSRESPONSE_HPP
#define TEST_TASKSRESPONSE_HPP


#include "Task.hpp"
#include <cJSON.h>
#include <vector>
#include <memory>
#include <WString.h>

class TasksResponse {
    std::unique_ptr<cJSON> parsed_payload{};
    std::vector<std::unique_ptr<Task>> tasksList;

public:
    explicit TasksResponse(const String& string);

    bool hasMoreTasks();

    std::unique_ptr<Task> getNextTask();

};


#endif //TEST_TASKSRESPONSE_HPP
