#ifndef FACADE_H
#define FACADE_H

#include <iostream>
#include <string>

// Forward declarations of subsystem classes
class InventorySystem;
class PaymentSystem;
class PlantCareSystem;
class CustomerServiceSystem;

class Facade {
private:
    InventorySystem* inventory;
    PaymentSystem* payment;
    PlantCareSystem* plantCare;
    CustomerServiceSystem* customerService;

public:
    Facade();
    ~Facade();

    // Simplified interface methods
    void purchasePlant(const std::string& plantName, int quantity, double amount);
    void requestPlantCare(const std::string& plantName, const std::string& careType);
    void checkPlantStock(const std::string& plantName);
    void processRefund(const std::string& plantName, const std::string& reason);
    void getPlantInfo(const std::string& plantName);
};

#endif // FACADE_H