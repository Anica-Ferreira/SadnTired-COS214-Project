#include "RequestSystem.h"

RequestSystem::RequestSystem() : chainRoot(nullptr) {
    // Build the chain: Gardener -> Salesman -> Manager
    GardenerHandler* gardener = new GardenerHandler("James");
    SalesmanHandler* salesman = new SalesmanHandler("Carlos");
    ManagerHandler* manager = new ManagerHandler("Logan");
        
    // Set up the chain
    gardener->setNext(salesman);
    salesman->setNext(manager);
        
    chainRoot = gardener;
}
    
RequestSystem::~RequestSystem() {
    // Clean up the entire chain
    if (chainRoot) {
        delete chainRoot;
    }
}
    
void RequestSystem::processCustomerRequest(const string& requestType, Customer* customer, const string& details) {
    cout << "\n=== Processing Customer Request ===" << endl;
    cout << "Type: " << requestType << endl;
    cout << "Details: " << details << endl;
    cout << "-----------------------------------" << endl;
        
    if (chainRoot) {
        chainRoot->handleRequest(requestType, customer, details);
    }
        
    cout << "=== Request Processing Complete ===\n" << endl;
}
    
// Method to demonstrate the chain with various requests
void RequestSystem::demonstrateChain() {
    RequestSystem system;
    Customer* customer = new Customer();
        
    system.processCustomerRequest("ProductInfo", customer, "What type of soil for succulents?");
    system.processCustomerRequest("PlantCare", customer, "My fern is turning brown");
    system.processCustomerRequest("Pricing", customer, "Do you offer bulk discounts?");
    system.processCustomerRequest("Complaint", customer, "Unhappy with service");
    system.processCustomerRequest("UnknownType", customer, "This should not be handled");
        
    delete customer;
    // system destructor will clean up the chain
}