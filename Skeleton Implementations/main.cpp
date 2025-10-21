#include <iostream>
#include "StaffMember.h"
#include "StaffManager.h"
#include "StaffSalesman.h"
#include "StaffGardener.h"
#include "Customer.h"
#include "StaffAction.h"
#include "StaffReaction.h"

void templateMethod(StaffMember* employee) {
    employee->templateWorkCycle();
}

void observerMethod() {
    Customer* customer = new Customer();
    Customer* plant = new Customer();
    StaffMember* observer1= new StaffManager("Logan", *customer);
    StaffMember* observer2= new StaffSalesman("Carlos", *customer);
    StaffMember* observer3= new StaffGardener("James", *plant);

    customer->CreateMessage("KAREN!");
    observer1->RemoveMeFromTheList();
    customer->CreateMessage("What kind of plant is this?");
    observer2->RemoveMeFromTheList();
    plant->CreateMessage("More Water Over Here!");
    observer3->RemoveMeFromTheList();

    delete plant;
    delete customer;
}

void mediatorMethod() {
    Customer* customer = new Customer();
    StaffMember* mediator = new StaffSalesman("Logan", *customer);

    cout << "Customer triggers behaviour A: \n";
    customer->doA();
    cout << endl;
    cout << "Customer triggers behaviour B: \n";
    customer->doB();

    delete customer;
}

void commandMethod() {
    StaffAction* invoker = new StaffAction();
    invoker->setOnStart(new StaffReaction());
    Customer* customer = new Customer();
    invoker->setOnFinish(new StaffReaction());
    invoker->doCommand();

    delete invoker;
    delete customer;
}

int main() {

    cout << endl;
    cout<< "-------------------------------Template Method Showcase--------------------------------" << endl;
    cout << endl;
    Customer* sharedCustomer = new Customer();

    StaffManager* manager = new StaffManager("George", *sharedCustomer);
    templateMethod(manager);

    StaffSalesman* salesman = new StaffSalesman("John", *sharedCustomer);
    templateMethod(salesman);

    StaffGardener* gardener = new StaffGardener("Paul", *sharedCustomer);
    templateMethod(gardener);

    delete gardener;
    delete salesman;
    delete manager;
    delete sharedCustomer;

    cout<< "-----------------------------------Observer Showcase------------------------------------" << endl;
    cout << endl;
    observerMethod();
    cout << endl;

    cout<< "-----------------------------------Mediator Showcase------------------------------------" << endl;
    cout << endl;
    mediatorMethod();
    cout << endl;

    cout<< "------------------------------------Command Showcase------------------------------------" << endl;
    cout << endl;
    commandMethod();
    cout << endl;
    cout<< "----------------------------------------------------------------------------------------" << endl;

    return 0;
}