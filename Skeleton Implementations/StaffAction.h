#ifndef STAFFACTION_H
#define STAFFACTION_H
#include <string>

#include "StaffCommand.h"
#include <iostream>
using namespace std;

class StaffAction {
private:
    StaffCommand* start;
    StaffCommand* finish;
public:
    ~StaffAction() {
        delete start;
        delete finish;
    }

    void setOnStart(StaffCommand* command);
    void setOnFinish(StaffCommand* command);

    void doCommand();
};


#endif //STAFFACTION_H