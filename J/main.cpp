#include <iostream>
#include "IMediator.h"
#include "IColleague.h"
#include "IObserver.h"
#include "ISubject.h"
#include "Customer.h"
#include "Plant.h"
#include "StaffMember.h"
#include "StaffManager.h"
#include "StaffSalesman.h"
#include "StaffGardener.h"
#include "StaffCommand.h"
#include "StaffReaction.h"
#include "StaffAction.h"

using namespace std;

// =================================================================
// TEMPLATE METHOD PATTERN TEST
// =================================================================
void testTemplateMethod() {
    cout << "\n========================================\n";
    cout << "  TEMPLATE METHOD PATTERN\n";
    cout << "========================================\n";
    cout << "Different staff types follow same work cycle structure\n\n";

    // Create a manager and demonstrate their standardised work routine
    StaffManager* manager = new StaffManager("Heather");
    // templateWorkCycle() defines the skeleton: mainDuty → workDuty → subDuty
    // Each method is implemented differently by each staff type
    manager->templateWorkCycle();
    cout << "\n";
    delete manager;  // Clean up

    // Create a gardener and demonstrate their standardised work routine
    StaffGardener* gardener = new StaffGardener("Carlos");
    // templateWorkCycle() defines the skeleton: mainDuty → workDuty → subDuty
    // Each method is implemented differently by each staff type
    gardener->templateWorkCycle();
    cout << "\n";
    delete gardener;  // Clean up

    // Create salesman and demonstrate their standardised work routine
    StaffSalesman* salesman = new StaffSalesman("Kendall");
    salesman->templateWorkCycle();  // Calls mainDuty(), workDuty(), subDuty() in sequence
    delete salesman;
}

// =================================================================
// MEDIATOR PATTERN TEST
// =================================================================
void testMediator() {
    cout << "\n========================================\n";
    cout << "  MEDIATOR PATTERN (Customer <-> Staff)\n";
    cout << "========================================\n";

    // Create participants
    Customer* customer = new Customer("Logan");
    StaffSalesman* salesman = new StaffSalesman("James");

    // Connect customer to salesman as mediator
    customer->setMediator(salesman);

    // Customer sends request - it goes through salesman's notify() method
    // salesman processes request and sends response back to customer
    customer->sendRequest("I need help");

    // Clean up
    delete customer;
    delete salesman;

}

// =================================================================
// OBSERVER PATTERN TEST
// =================================================================
void testObserver() {
    cout << "\n========================================\n";
    cout << "  OBSERVER PATTERN (Plant -> Staff)\n";
    cout << "========================================\n";

    // Create plant and staff observer
    Plant* plant = new Plant("Succulent");
    StaffGardener* gardener = new StaffGardener("Carlos");

    // Gardener subscribes to plant notifications
    plant->Attach(gardener);

    // Plant signals needs - triggers notification to all observers
    plant->signalNeed("water");  // triggers gardener->Update()
    cout << "\n";
    // Demonstrate multiple plant needs
    plant->signalNeed("repotting");
    cout << "\n";
    plant->signalNeed("pest_control");
    cout << "\n";
    plant->signalNeed("sunlight_adjustment");
    cout << "\n";
    // Each signalNeed() calls:
    // 1. plant->current_need_ = need
    // 2. plant->Notify()
    // 3. gardener->Update("need for plant ___")
    // 4. gardener creates StaffAction and executes command

    delete plant;
    delete gardener;

}

// =================================================================
// COMMAND PATTERN TEST
// =================================================================
void testCommand() {
    cout << "\n========================================\n";
    cout << "  COMMAND PATTERN\n";
    cout << "========================================\n";

    // Basic command demonstration
    StaffAction* action = new StaffAction();
    action->setOnStart(new StaffReaction("greet"));    // Pre-action command
    action->setOnFinish(new StaffReaction("farewell")); // Post-action command
    action->doCommand("Actions");  // Executes: greet → main action → farewell

    // Extension: Specialized command
    cout << "\n--- Chained Commands ---\n";
    WaterCommand* waterCmd = new WaterCommand();
    waterCmd->execute("Cactus");

    delete action;

}

// =================================================================
// MULTIPLE CUSTOMERS TEST
// =================================================================
void testMultipleCustomers() {
    cout << "\n========================================\n";
    cout << "  MULTIPLE CUSTOMERS DEMONSTRATION\n";
    cout << "========================================\n";

    // Create a manager who will mediate all customer requests
    StaffManager* manager = new StaffManager("Boss");

    // Create three different customers
    Customer* customer1 = new Customer("John");
    Customer* customer2 = new Customer("Paul");
    Customer* customer3 = new Customer("George");

    // Connect all customers to the same manager mediator
    customer1->setMediator(manager);
    customer2->setMediator(manager);
    customer3->setMediator(manager);

    // Each customer sends requests through the manager
    // The manager's notify() method will handle these sequentially
    customer1->sendRequest("Need help");
    customer2->sendRequest("Have question");
    customer3->sendRequest("Want refund");

    // Clean up all dynamically allocated objects
    delete customer1;
    delete customer2;
    delete customer3;
    delete manager;
}

// =================================================================
// MAIN FUNCTION
// =================================================================
int main() {
    // Program header
    cout << "************************************************\n";
    cout << "    DESIGN PATTERNS BASELINE DEMONSTRATION\n";
    cout << "************************************************\n";

    // Run each pattern test in sequence
    testTemplateMethod();        // Template Method Pattern
    testMediator();              // Mediator Pattern
    testObserver();              // Observer Pattern
    testCommand();               // Command Pattern
    testMultipleCustomers();     // Multiple Customers Scenario

    return 0;
}