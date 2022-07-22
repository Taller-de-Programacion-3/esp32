//
// Created by javier on 22/07/22.
//

#ifndef TEST_LEDONTASK_HPP
#define TEST_LEDONTASK_HPP


#include "Task.hpp"

class LedOnTask: public virtual Task {
    int taskId;
public:
    explicit LedOnTask(int id);

    void execute() override;

    void sendResponse(ControllerServer& server) override;

};


#endif //TEST_LEDONTASK_HPP
