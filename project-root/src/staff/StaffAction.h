#ifndef STAFFACTIONS_H
#define STAFFACTIONS_H

#include "StaffCommand.h"
#include <string>

class StaffAction {
private:
    StaffCommand* onStart_ = nullptr;
    StaffCommand* onFinish_ = nullptr;

public:
    void setOnStart(StaffCommand* cmd);

    void setOnFinish(StaffCommand* cmd);

    void doCommand(std::string type = "");

    ~StaffAction();
};

#endif // STAFFACTIONS_H