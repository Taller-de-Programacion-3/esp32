//
// Created by javier on 22/07/22.
//

#include "TasksResponse.hpp"
#include "Task.hpp"
#include <cJSON.h>
#include <Arduino.h>
#include "TaskBuilder.hpp"

bool TasksResponse::hasMoreTasks() {
    return !this->tasksList.empty();
}

std::unique_ptr<Task> TasksResponse::getNextTask() {
    auto task = std::move(this->tasksList.back());
    this->tasksList.pop_back();
    return task;
}

TasksResponse::TasksResponse(const String& string) {
    this->parsed_payload.reset(cJSON_Parse(string.c_str()));
    auto tasks = cJSON_GetObjectItem(this->parsed_payload.get(), "tasks");

    cJSON* task;
    cJSON_ArrayForEach(task, tasks) {
        Serial.println(cJSON_Print(task));
        auto taskNameJson = cJSON_GetObjectItemCaseSensitive(task, "task_name");
        auto taskIDJson = cJSON_GetObjectItemCaseSensitive(task, "id");
        auto taskParamsJson = cJSON_GetObjectItemCaseSensitive(task, "task_params");

        if (!cJSON_IsString(taskNameJson)) {
            Serial.println("Invalid task name");
            continue;
        }
        if (!cJSON_IsNumber(taskIDJson)) {
            Serial.println("Invalid task ID");
            continue;
        }
        if (!cJSON_IsObject(taskParamsJson)) {
            Serial.println("Invalid task params");
            continue;
        }

        auto taskName = taskNameJson->valuestring;
        auto taskId = taskIDJson->valueint;
        auto taskParams = taskParamsJson;

        this->tasksList.emplace_back(TaskBuilder::buildTask(taskName, taskId, cJSON_Print(taskParams)));
    }

}
