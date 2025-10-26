#ifndef STAFFREACTION_H
#define STAFFREACTION_H

#include "StaffCommand.h"
#include <string>
#include <vector>

class StaffReaction : public StaffCommand {
private:
    std::string action_;
    bool was_executed_ = false;

public:
    StaffReaction(std::string action) : action_(action) {}

    void execute(std::string type) override {
        std::cout << "Executing " << action_ << " for " << type << std::endl;
        was_executed_ = true;
    }

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

class PruneCommand : public StaffCommand {
private:
    bool was_executed_ = false;

public:
    void execute(std::string type) override {
        std::cout << "Pruning plant (" << type << ")..." << std::endl;
        was_executed_ = true;
    }

};

//for chaining commands
class ChainCommand : public StaffCommand {
private:
    std::vector<StaffCommand*> commands_;
    bool was_executed_ = false;

public:
    void addCommand(StaffCommand* cmd) {
        commands_.push_back(cmd);
    }

    void execute(std::string type) override {
        for (auto* cmd : commands_) {
            cmd->execute(type);
        }
        was_executed_ = true;
    }

    ~ChainCommand() {
        for (auto* cmd : commands_) {
            delete cmd;
        }
    }
};

#endif // STAFFREACTION_H