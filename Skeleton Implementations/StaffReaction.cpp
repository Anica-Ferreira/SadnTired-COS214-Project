#include "StaffReaction.h"

#include <iostream>
#include <ostream>

void StaffReaction::execute(string type) {
    if (type == "CustomerCommand") {//will do actual work
        cout << "Customer's Command leads me to a Command of my own" << endl;
    }
    else if (type == "PlantRequest") {//will split into separate commands
        cout << "Plant needs assistance, so a Command of mine helps" << endl;
    }
}
