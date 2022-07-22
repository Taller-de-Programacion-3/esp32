//
// Created by javier on 22/07/22.
//

#ifndef TEST_TASK_HPP
#define TEST_TASK_HPP

class ControllerServer;

class Task {
public:
    virtual void execute() = 0;

    virtual void sendResponse(ControllerServer& server) = 0;
};

#endif //TEST_TASK_HPP
