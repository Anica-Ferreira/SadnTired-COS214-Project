#include "StaffReaction.h"

StaffReaction::StaffReaction(std::string action) : action_(action) {}

void StaffReaction::execute(std::string type) {
    std::cout << "Executing " << action_ << " for " << type << std::endl;
}