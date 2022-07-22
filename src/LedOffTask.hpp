//
// Created by javier on 22/07/22.
//

#ifndef TEST_LEDOFFTASK_HPP
#define TEST_LEDOFFTASK_HPP


#include "Task.hpp"

class LedOffTask: public virtual Task {
    int taskId;
public:
    explicit LedOffTask(int id);

    void execute() override;

    void sendResponse(ControllerServer& server) override;

};


#endif //TEST_LEDOFFTASK_HPP
