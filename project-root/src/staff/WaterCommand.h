#ifndef WATERCOMMAND_H
#define WATERCOMMAND_H
#include "StaffCommand.h"
#include <string>

class WaterCommand : public StaffCommand {
public:
    void execute(std::string type) override;
};


#endif //WATERCOMMAND_H