#include "StaffAction.h"

void StaffAction::setOnStart(StaffCommand* cmd) {
    onStart_ = cmd;
}

void StaffAction::setOnFinish(StaffCommand* cmd) {
    onFinish_ = cmd;
}

void StaffAction::doCommand(std::string type) {
    if (onStart_) onStart_->execute(type);
    std::cout << "Performing main action..." << std::endl;//can be removed and replaced with onStart only
    if (onFinish_) onFinish_->execute(type);
}

StaffAction::~StaffAction() {
    delete onStart_;
    delete onFinish_;
}