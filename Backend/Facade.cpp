#include "Facade.h"

// Subsystem class declarations (would normally be in separate files)
class InventorySystem {
public:
    void checkAvailability(const std::string& plantName) {
        std::cout << "Inventory: Checking availability for " << plantName << std::endl;
    }
    
    void updateStock(const std::string& plantName, int quantity) {
        std::cout << "Inventory: Updating stock for " << plantName << " by " << quantity << std::endl;
    }
    
    void getStockInfo(const std::string& plantName) {
        std::cout << "Inventory: Getting stock info for " << plantName << std::endl;
    }
};

class PaymentSystem {
public:
    void processPayment(double amount, const std::string& description) {
        std::cout << "Payment: Processing payment of $" << amount << " for " << description << std::endl;
    }
    
    void processRefund(double amount, const std::string& reason) {
        std::cout << "Payment: Processing refund of $" << amount << " for reason: " << reason << std::endl;
    }
    
    bool validatePayment() {
        std::cout << "Payment: Validating payment details" << std::endl;
        return true;
    }
};

class PlantCareSystem {
public:
    void waterPlant(const std::string& plantName) {
        std::cout << "PlantCare: Watering " << plantName << std::endl;
    }
    
    void fertilizePlant(const std::string& plantName) {
        std::cout << "PlantCare: Fertilizing " << plantName << std::endl;
    }
    
    void prunePlant(const std::string& plantName) {
        std::cout << "PlantCare: Pruning " << plantName << std::endl;
    }
    
    void getCareInstructions(const std::string& plantName) {
        std::cout << "PlantCare: Getting care instructions for " << plantName << std::endl;
    }
};

class CustomerServiceSystem {
public:
    void logInteraction(const std::string& customerAction) {
        std::cout << "CustomerService: Logging interaction - " << customerAction << std::endl;
    }
    
    void providePlantInfo(const std::string& plantName) {
        std::cout << "CustomerService: Providing information about " << plantName << std::endl;
    }
    
    void handleComplaint(const std::string& issue) {
        std::cout << "CustomerService: Handling complaint - " << issue << std::endl;
    }
};

// Facade implementation
Facade::Facade() {
    inventory = new InventorySystem();
    payment = new PaymentSystem();
    plantCare = new PlantCareSystem();
    customerService = new CustomerServiceSystem();
    std::cout << "Facade: Nursery management system initialized" << std::endl;
}

Facade::~Facade() {
    delete inventory;
    delete payment;
    delete plantCare;
    delete customerService;
    std::cout << "Facade: Nursery management system shutdown" << std::endl;
}

void Facade::purchasePlant(const std::string& plantName, int quantity, double amount) {
    std::cout << "\n=== Facade: Processing Plant Purchase ===" << std::endl;
    customerService->logInteraction("Purchase request for " + plantName);
    inventory->checkAvailability(plantName);
    
    if (payment->validatePayment()) {
        payment->processPayment(amount, plantName + " purchase");
        inventory->updateStock(plantName, -quantity);
        customerService->logInteraction("Purchase completed for " + plantName);
    }
    
    std::cout << "=== Purchase Process Complete ===\n" << std::endl;
}

void Facade::requestPlantCare(const std::string& plantName, const std::string& careType) {
    std::cout << "\n=== Facade: Processing Plant Care Request ===" << std::endl;
    customerService->logInteraction("Care request for " + plantName);
    
    if (careType == "water") {
        plantCare->waterPlant(plantName);
    } else if (careType == "fertilize") {
        plantCare->fertilizePlant(plantName);
    } else if (careType == "prune") {
        plantCare->prunePlant(plantName);
    } else {
        std::cout << "Facade: Unknown care type requested" << std::endl;
    }
    
    customerService->logInteraction("Care completed for " + plantName);
    std::cout << "=== Care Process Complete ===\n" << std::endl;
}

void Facade::checkPlantStock(const std::string& plantName) {
    std::cout << "\n=== Facade: Checking Plant Stock ===" << std::endl;
    customerService->logInteraction("Stock check for " + plantName);
    inventory->getStockInfo(plantName);
    std::cout << "=== Stock Check Complete ===\n" << std::endl;
}

void Facade::processRefund(const std::string& plantName, const std::string& reason) {
    std::cout << "\n=== Facade: Processing Refund ===" << std::endl;
    customerService->logInteraction("Refund request for " + plantName);
    customerService->handleComplaint(reason);
    payment->processRefund(25.0, reason); // Default amount for demo
    inventory->updateStock(plantName, 1);
    std::cout << "=== Refund Process Complete ===\n" << std::endl;
}

void Facade::getPlantInfo(const std::string& plantName) {
    std::cout << "\n=== Facade: Getting Plant Information ===" << std::endl;
    customerService->providePlantInfo(plantName);
    plantCare->getCareInstructions(plantName);
    std::cout << "=== Information Retrieval Complete ===\n" << std::endl;
}