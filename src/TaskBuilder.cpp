//
// Created by javier on 22/07/22.
//

#include "TaskBuilder.hpp"
#include "LedOnTask.hpp"
#include "LedOffTask.hpp"
#include "NullTask.h"

std::unique_ptr<Task> TaskBuilder::buildTask(const String &name, int id, String params) {
    if (name == String("Led On")) {
        return std::unique_ptr<Task>(new LedOnTask(id));
    } else if (name == String("Led Off")) {
        return std::unique_ptr<Task>(new LedOffTask(id));
    }
    return std::unique_ptr<Task>(new NullTask());
}
