#ifndef STAFFCOMMAND_H
#define STAFFCOMMAND_H
#include <string>
using namespace std;

class StaffCommand {
public:
    virtual void execute(string type) = 0;
};


#endif //STAFFCOMMAND_H