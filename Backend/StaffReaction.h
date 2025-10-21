#ifndef STAFFREACTION_H
#define STAFFREACTION_H
#include "StaffCommand.h"


class StaffReaction : public StaffCommand {
public:
    void execute(string type) override;
};


#endif //STAFFREACTION_H