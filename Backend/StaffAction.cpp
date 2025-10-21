#include "StaffAction.h"

void StaffAction::setOnStart(StaffCommand *command) {
    this->start = command;
}

void StaffAction::setOnFinish(StaffCommand *command) {
    this->finish = command;
}

void StaffAction::doCommand() {
    cout << "Invoke Command:" << endl;
    if (this->start) {
        this->start->execute("CustomerCommand");
    }
    if (this->finish) {
        this->finish->execute("PlantRequest");
    }//will add actual staff member for actual work to be done in executes
}