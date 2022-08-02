//
// Created by javier on 22/07/22.
//

#ifndef TEST_NULLTASK_H
#define TEST_NULLTASK_H


#include "Task.hpp"

using namespace std;

class NullTask: virtual public Task {
    int taskId{};
public:
    NullTask(int id);
    void execute() override;
    void sendResponse(ControllerServer& server) override;
};


#endif //TEST_NULLTASK_H
