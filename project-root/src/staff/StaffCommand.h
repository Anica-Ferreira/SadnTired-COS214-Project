#ifndef STAFFCOMMAND_H
#define STAFFCOMMAND_H

#include <string>
#include <iostream>

class StaffCommand {
public:
    virtual void execute(std::string type) = 0;
    virtual ~StaffCommand() {}
};

#endif // STAFFCOMMAND_H