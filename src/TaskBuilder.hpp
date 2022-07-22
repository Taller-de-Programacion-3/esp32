//
// Created by javier on 22/07/22.
//

#ifndef TEST_TASKBUILDER_HPP
#define TEST_TASKBUILDER_HPP

#include <memory>
#include <WString.h>
#include "Task.hpp"

class TaskBuilder {
public:
    static std::unique_ptr<Task> buildTask(const String& name, int id, String params);
};


#endif //TEST_TASKBUILDER_HPP
