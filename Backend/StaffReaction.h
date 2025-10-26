#ifndef STAFFREACTION_H
#define STAFFREACTION_H

#include "StaffCommand.h"
#include <string>
#include <vector>

class StaffReaction : public StaffCommand {
private:
    std::string action_;

public:
    StaffReaction(std::string action);

    void execute(std::string type) override;

};

// Extension: Specialized commands
class WaterCommand : public StaffCommand {
private:
    bool was_executed_ = false;

public:
    void execute(std::string type) override {
        std::cout << "Watering plant (" << type << ")..." << std::endl;
        was_executed_ = true;
    }

};

#endif // STAFFREACTION_H