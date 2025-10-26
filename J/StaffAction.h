#ifndef STAFFACTIONS_H
#define STAFFACTIONS_H

#include "StaffCommand.h"
#include <string>

class StaffAction {
private:
    StaffCommand* onStart_ = nullptr;
    StaffCommand* onFinish_ = nullptr;

public:
    void setOnStart(StaffCommand* cmd) {
        onStart_ = cmd;
    }

    void setOnFinish(StaffCommand* cmd) {
        onFinish_ = cmd;
    }

    void doCommand(std::string type = "") {
        if (onStart_) onStart_->execute(type);
        std::cout << "Performing main action..." << std::endl;
        if (onFinish_) onFinish_->execute(type);
    }

    ~StaffAction() {
        delete onStart_;
        delete onFinish_;
    }
};

#endif // STAFFACTIONS_H