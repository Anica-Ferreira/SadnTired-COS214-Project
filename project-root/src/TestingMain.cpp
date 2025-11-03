/*#include "core/NurserySystemFacade.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void testCustomerOperations(NurserySystemFacade& nursery) {
    /*cout << "\n=== TESTING CUSTOMER OPERATIONS ===" << endl;

    // Set customer information (no login required)
    nursery.setCustomer("John", "Doe", "john.doe@email.com", "123-456-7890");

    // Browse plants
    cout << "\n1. Browsing all plants:" << endl;
    cout << nursery.browseAllPlants() << endl;

    // Search plants
    cout << "\n2. Searching for 'Rose':" << endl;
    cout << nursery.searchPlants("Rose") << endl;

    // Filter plants by type
    cout << "\n3. Filtering flowers:" << endl;
    cout << nursery.filterPlantsByType("Flower") << endl;

    // Get plant information
    cout << "\n4. Getting Rose information:" << endl;
    cout << nursery.getPlantInfo("Rose") << endl;

    // Check stock
    cout << "\n5. Checking Rose stock:" << endl;
    cout << nursery.checkPlantStock("Rose") << endl;

    // Add to cart
    cout << "\n6. Adding Rose to cart:" << endl;
    cout << nursery.addToCart("Rose", 2) << endl;

    // View cart
    cout << "\n7. Viewing cart:" << endl;
    cout << nursery.viewCart() << endl;

    // Ask staff question
    cout << "\n8. Asking staff question:" << endl;
    cout << nursery.askStaffQuestion("How often should I water roses?") << endl;

    // Get recommendations
    cout << "\n9. Getting plant recommendations:" << endl;
    cout << nursery.requestPlantRecommendation("medium", "small", "beginner") << endl;
}

void testNurseryManagement(NurserySystemFacade& nursery) {
    cout << "\n=== TESTING NURSERY MANAGEMENT ===" << endl;

    // View nursery status
    cout << "\n1. Viewing nursery status:" << endl;
    cout << nursery.viewNurseryStatus() << endl;

    // Water specific plant
    cout << "\n2. Watering Rose in nursery:" << endl;
    cout << nursery.waterPlant("Rose") << endl;

    // Water all plants
    cout << "\n3. Watering all plants:" << endl;
    cout << nursery.waterAllPlants() << endl;

    // Pass time for plants
    cout << "\n4. Passing time for all plants:" << endl;
    cout << nursery.passTimeForAllPlants() << endl;

    // Move plant to shop
    cout << "\n5. Moving Rose to shop:" << endl;
    cout << nursery.movePlantToShop("Rose") << endl;

    // Check stock counts
    cout << "\n6. Getting stock counts:" << endl;
    cout << nursery.getStockCounts() << endl;
}

void testStaffOperations(NurserySystemFacade& nursery) {
    cout << "\n=== TESTING STAFF OPERATIONS ===" << endl;

    // Assign staff task
    cout << "\n3. Assigning task to staff:" << endl;
    cout << nursery.assignStaffTask(1, "Water all plants in greenhouse B") << endl;
}

void testCommandPattern(NurserySystemFacade& nursery) {
    cout << "\n=== TESTING COMMAND PATTERN ===" << endl;

    // Set a different customer
    nursery.setCustomer("Alice", "Smith", "alice.smith@email.com", "987-654-3210");

    // Test various commands
    cout << "\n1. Executing purchase command:" << endl;
    cout << nursery.executeCustomerCommand("purchase", "Tulip", 3) << endl;

    cout << "\n2. Executing stock check command:" << endl;
    cout << nursery.executeCustomerCommand("check_stock", "Cactus") << endl;

    cout << "\n3. Executing plant info command:" << endl;
    cout << nursery.executeCustomerCommand("get_info", "Bonsai") << endl;

    cout << "\n4. Executing question command:" << endl;
    cout << nursery.executeCustomerCommand("ask_question", "", 0,
                                          "What's the best soil for succulents?") << endl;

    cout << "\n5. Executing recommendation command:" << endl;
    cout << nursery.executeCustomerCommand("get_recommendation", "", 0, "",
                                          "low", "apartment", "beginner") << endl;
}

void testCheckoutProcess(NurserySystemFacade& nursery) {
    cout << "\n=== TESTING CHECKOUT PROCESS ===" << endl;

    // Set customer
    nursery.setCustomer("Bob", "Johnson", "bob.johnson@email.com");

    // Add multiple items to cart
    cout << "\n1. Adding items to cart:" << endl;
    cout << nursery.addToCart("Sunflower", 1) << endl;
    cout << nursery.addToCart("Snake Plant", 2) << endl;

    // View cart
    cout << "\n2. Cart contents:" << endl;
    cout << nursery.viewCart() << endl;

    // Get cart summary
    cout << "\n3. Cart summary:" << endl;
    cout << nursery.getCartSummary() << endl;

    // Checkout
    cout << "\n4. Checking out:" << endl;
    cout << nursery.checkout() << endl;

    // Try to view empty cart
    cout << "\n5. Viewing cart after checkout:" << endl;
    cout << nursery.viewCart() << endl;
}

void testPlantLifecycle(NurserySystemFacade& nursery) {
    cout << "\n=== TESTING PLANT LIFECYCLE ===" << endl;

    // Show initial nursery state
    cout << "\n1. Initial nursery state:" << endl;
    cout << nursery.viewNurseryStatus() << endl;

    // Water plants multiple times to see state changes
    cout << "\n2. Watering plants multiple times:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "\nWatering cycle " << (i + 1) << ":" << endl;
        cout << nursery.waterAllPlants() << endl;

        // Pass time between waterings
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << nursery.passTimeForAllPlants() << endl;
    }

    // Move ready plants to shop
    cout << "\n3. Moving ready plants to shop:" << endl;
    cout << nursery.movePlantToShop("Rose") << endl;
    cout << nursery.movePlantToShop("Tulip") << endl;

    // Show final states
    cout << "\n4. Final nursery state:" << endl;
    cout << nursery.viewNurseryStatus() << endl;

    cout << "\n5. Final shop state:" << endl;
    cout << nursery.browseAllPlants() << endl;
}

void testErrorConditions(NurserySystemFacade& nursery) {
    cout << "\n=== TESTING ERROR CONDITIONS ===" << endl;

    // Try operations without setting customer
    nursery.resetCustomer();

    cout << "\n1. Trying to add to cart without customer:" << endl;
    cout << nursery.addToCart("Rose", 1) << endl;

    cout << "\n2. Trying to checkout without customer:" << endl;
    cout << nursery.checkout() << endl;

    cout << "\n3. Trying to ask question without customer:" << endl;
    cout << nursery.askStaffQuestion("Test question") << endl;

    // Set customer but try invalid operations
    nursery.setCustomer("Test", "User", "test@email.com");

    cout << "\n4. Trying to checkout empty cart:" << endl;
    cout << nursery.checkout() << endl;

    cout << "\n5. Trying to get info for non-existent plant:" << endl;
    cout << nursery.getPlantInfo("NonExistentPlant") << endl;

    cout << "\n6. Trying to move non-existent plant:" << endl;
    cout << nursery.movePlantToShop("NonExistentPlant") << endl;
}

void testBundlesAndSpecialFeatures(NurserySystemFacade& nursery) {
    cout << "\n=== TESTING BUNDLES AND SPECIAL FEATURES ===" << endl;

    nursery.setCustomer("Eve", "Wilson", "eve.wilson@email.com");


    // Get bundle details
    cout << "\n2. Getting bundle details:" << endl;
    // This would typically be implemented to show specific bundle info

    // Test plant health report
    cout << "\n3. Getting plant health report:" << endl;
    cout << nursery.getPlantHealthReport() << endl;

    // Test fertilize plant
    cout << "\n4. Fertilizing a plant:" << endl;
    cout << nursery.fertilizePlant("Rose") << endl;
}

void runComprehensiveTest() {
    cout << "🚀 STARTING COMPREHENSIVE NURSERY SYSTEM TEST" << endl;
    cout << "=============================================" << endl;

    // Create the main facade (this initializes the entire system)
    NurserySystemFacade nurserySystem;

    // Run all test suites
    testCustomerOperations(nurserySystem);
    testNurseryManagement(nurserySystem);
    testStaffOperations(nurserySystem);
    testCommandPattern(nurserySystem);
    testCheckoutProcess(nurserySystem);
    testPlantLifecycle(nurserySystem);
    testErrorConditions(nurserySystem);
    testBundlesAndSpecialFeatures(nurserySystem);

    cout << "\n🎉 ALL TESTS COMPLETED SUCCESSFULLY!" << endl;
    cout << "=============================================" << endl;
}

void runQuickDemo() {
    cout << "\n🌿 QUICK DEMO: NURSERY SYSTEM IN ACTION" << endl;
    cout << "=============================================" << endl;

    NurserySystemFacade nursery;

    // Quick demonstration of main features
    cout << "\n1. Setting up customer..." << endl;
    nursery.setCustomer("Demo", "User", "demo@nursery.com");

    cout << "\n2. Browsing plants..." << endl;
    cout << nursery.browseAllPlants() << endl;

    cout << "\n3. Checking nursery status..." << endl;
    cout << nursery.viewNurseryStatus() << endl;

    cout << "\n4. Watering plants..." << endl;
    cout << nursery.waterAllPlants() << endl;

    cout << "\n5. Making a purchase..." << endl;
    cout << nursery.addToCart("Sunflower", 2) << endl;
    cout << nursery.checkout() << endl;

    cout << "\n✅ DEMO COMPLETED!" << endl;
}

int main() {
    /*cout << "🌱 PLANT NURSERY MANAGEMENT SYSTEM - BACKEND TEST" << endl;
    cout << "=============================================" << endl;

    int choice;
    cout << "\nChoose test mode:" << endl;
    cout << "1. Comprehensive Test (All Features)" << endl;
    cout << "2. Quick Demo (Main Features)" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter choice (1-3): ";
    cin >> choice;

    switch(choice) {
        case 1:
            runComprehensiveTest();
            break;
        case 2:
            runQuickDemo();
            break;
        case 3:
            cout << "Exiting..." << endl;
            return 0;
        default:
            cout << "Invalid choice. Running comprehensive test." << endl;
            runComprehensiveTest();
    }

    // Keep console open
    cout << "\nPress Enter to exit...";
    cin.ignore();
    cin.get();*/

    //return 0;
//}