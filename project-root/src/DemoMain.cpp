#include "core/NurserySystemFacade.h"
#include "inventory/Inventory.h"
#include "customer/ShoppingCart.h"
#include "products/DecorativePot.h"
#include "products/GiftWrapping.h"
#include "customer/CustomerCommand.h"
#include "products/ProductBundle.h"
#include "staff/StaffMember.h"
#include "staff/StaffSalesman.h"
#include "staff/StaffGardener.h"
#include "staff/StaffManager.h"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <limits>
#include <algorithm>
#include <iomanip> 

using namespace std;

/* ------------------------------------------ HELPER FUNCTIONS ------------------------------------------ */

//Clear the console for menu swaps
void clearConsole() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

//read + validate the input
int readInt() {
    int value;
    if (!(cin >> value)) {
        cin.clear(); // clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1;
    }
    return value;
}

void erasePreviousLine() {
    cout << "\033[1A"
         << "\033[2K";
}


bool promptYesNo(const string& message) {
    char choice;
    do {
        cout << message << " (y/n): ";
        cin >> choice;
        choice = tolower(choice);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (choice != 'y' && choice != 'n');
    return choice == 'y';
}

//format into "cards" because I miss websites :(
void displayPlantCard(int index, const string& name, double price, int width = 22, int indent = 6) {
    string border(width, '-');
    string indentation(indent, ' ');

    cout << indentation << "+" << border << "+\n";

    string numberedName = to_string(index) + ". " + name;
    int paddingName = (width - numberedName.length()) / 2;
    cout << indentation << "|" 
         << string(paddingName, ' ') 
         << "\033[95m" << numberedName << "\033[0m"
         << string(width - numberedName.length() - paddingName, ' ') 
         << "|\n";

    string priceStr = "R" + to_string(price); 
    priceStr = priceStr.substr(0, priceStr.find(".") + 3);
    int paddingPrice = (width - priceStr.length()) / 2;
    cout << indentation << "|" 
         << string(paddingPrice, ' ') << priceStr
         << string(width - priceStr.length() - paddingPrice, ' ') 
         << "|\n";

    cout << indentation << "+" << border << "+\n";
}

void pressEnterToContinue() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void displaySpecialBundlesMenu(NurserySystemFacade* facade) {
    // Get bundles as Product*
    vector<Product*> bundles = facade->getSpecialBundles();

    clearConsole();
    cout << "\033[1;32m\t\t\t--- ✿ Special Bundles ✿ ---\033[0m\n\n";

    int index = 1;
    const int screenWidth = 70;
    const string line = string(screenWidth, '-');

    for (Product* p : bundles) {
        if (ProductBundle* bundle = dynamic_cast<ProductBundle*>(p)) {
            cout << "\033[1;32m" << line << "\033[0m\n";

            string title = "Bundle #" + to_string(index) + ": " + bundle->getTitle();
            int padding = (screenWidth - title.length()) / 2;
            cout << string(padding, ' ') << "\033[1;35m" << title << "\033[0m\n\n";

            cout << bundle->getDescription() << "\n";

            cout << "\033[1;32m" << line << "\033[0m\n\n";

        } else {
            // Single product fallback
            cout << "\033[1;36mItem #" << index << ":\033[0m " << p->getDescription() << "\n";
            cout << "\033[1;32m" << line << "\033[0m\n\n";
        }

        index++;
    }

    cout << "0. <-- Back\n\n";
    cout << "Select a bundle to add to cart: ";

    int choice = readInt();
    if (choice > 0 && choice <= (int)bundles.size()) {
        Product* selected = bundles[choice - 1];
        facade->getCart()->addProduct(selected);
        cout << "\nAdded \"" << selected->getTitle() << "\" to your cart!\n";

        cout << "\nPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
}

/* ------------------------------------------ MAIN FUNCTION ------------------------------------------ */

int main() {
    NurserySystemFacade nursery;
    StaffMember* gardener = new StaffGardener("Mr. Green");
    StaffMember* manager = new StaffManager("Mr. Man");
    StaffMember* salesman = new StaffSalesman("Mr. Money");

    vector<Plant*> nurseryPlants = nursery.getNurseryInventory()->getAll();
    for (Plant* p : nurseryPlants) {
        p->Attach(gardener);
    }

    int choice;

    do{
        clearConsole();

        cout << "\033[38;5;34m";
        cout << "======================================\033[0m\n";
        cout << "Welcome to the Plant Nursery Simulator\n";
        cout << "\033[38;5;34m======================================\033[0m\n";

        cout << "\033[1;36m\nSelect a user type:\n\033[0m";
        cout << " 1. Customer\n";
        cout << " 2. Staff Member\n";
        cout << " 0. Exit\n\n";
        cout << "Choice: ";

        choice = readInt();
        
        //MAIN MENU STAFF/CUSTOMER
        switch (choice) {
            

            /* ------------------------------------------ CUSTOMER ------------------------------------------ */
            case 1:
            {   
                int custChoice;

                do {
                    clearConsole();
                    cout << "\033[1;32m\t\t\t\t         --- Customer Menu ---\n\n\033[0m";

                    cout << "\033[1;32m|\033[0m" << " 1. Browse Plants " << "\033[1;32m|\033[0m" << " 2. Search Plants " << "\033[1;32m|\033[0m" << " 3. Special Bundles " << "\033[1;32m|\033[0m" << " 4. View Cart " << "\033[1;32m|\033[0m"   << " 5. Customer Support " << "\033[1;32m|\033[0m" << " 0. <--Back " << "\033[1;32m|\033[0m\n\n"; cout << "Choice: ";

                    custChoice = readInt();

                    switch (custChoice) {

                        /* ------------------------------------------ BROWSE PLANTS ------------------------------------------ */
                        case 1: 
                        {
                            
                            vector<Plant*> shopPlants = nursery.getShopInventory()->getAll();

                            if (shopPlants.empty()) {
                                bool waitBack = true;
                                while (waitBack) {
                                    clearConsole();
                                    cout << "\033[1;32m\t    --- Available Plants ---\n\n\033[0m";
                                    cout << "No plants available in the shop. Come back soon!\n\n";
                                    cout << "0. <-- Back\n\n";
                                    cout << "Choice: ";
                                    int tmp = readInt();
                                    if (tmp == 0) {
                                        waitBack = false;
                                    }
                                    
                                }
                                break;
                            }

                            bool browsing = true;
                            while (browsing){
                                
                                clearConsole();
                                cout << "\033[1;32m\t    --- Available Plants ---\n\n\033[0m";

                                //track unique plants
                                vector<Plant*> shopPlants = nursery.getShopInventory()->getAll();
                                vector<Plant*> uniquePlants;
                                vector<string> displayed;

                                for (Plant* plant : shopPlants) {
                                    string name = plant->getName();
                                    if (find(displayed.begin(), displayed.end(), name) != displayed.end()) continue;
                                    displayed.push_back(name);
                                    uniquePlants.push_back(plant);

                                    displayPlantCard(uniquePlants.size(), plant->getName(), plant->getPrice(), 22, 12);
                                }
                                
                                cout << "0. <-- Back" << endl;

                                Plant* selectedPlant = NULL;
                                int plantChoice = -1;

                                //Prompt user to select a plant
                                cout << "\nSelect a Plant: ";
                                while (true) {
                                    plantChoice = readInt();
                                    if (plantChoice == 0){
                                        browsing = false;
                                        break;
                                    }
                                    if(plantChoice > 0 && plantChoice <= (int)uniquePlants.size()) {
                                        selectedPlant = uniquePlants[plantChoice - 1];
                                        break;
                                    }
                                }

                                //View selected plant
                                if (selectedPlant) {
                                    clearConsole();

                                    cout << "\033[1;32m\t--- Viewing " << selectedPlant->getName() <<  " details" << " ---\n\n\033[0m";
                                    
                                    GetPlantInfoCommand infoCmd(selectedPlant->getName(), &nursery);
                                    infoCmd.execute(NULL);

                                    char addChoice;
                                    do {
                                        cout << "Proceed to customisation? (y/n): ";
                                        cin >> addChoice;
                                        addChoice = tolower(addChoice);
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    } while (addChoice != 'y' && addChoice != 'n');

                                    /* ------------------------------------------ CUSTOMIZE PLANT ------------------------------------------ */
                                    if (addChoice == 'y') {
                                        
                                        // STEP 1 CUSTOMIZE POT //
                                        DecorativePot::PotType selectedPot = DecorativePot::NONE;
                                        int potChoice = -1;

                                        do {
                                            clearConsole();
                                            cout << "\033[1;32m\t  --- Customise your " << selectedPlant->getName() << " ---\n\n\033[0m";
                                            cout << "\033[1;36mSelect a pot type:\n\033[0m";
                                            cout << " 0. None\n";
                                            cout << left << setw(20) << " 1. Classic Pot" << "+R" << DecorativePot::getPotPrice(DecorativePot::CLASSIC) << "\n";
                                            cout << left << setw(20) << " 2. Rotund Pot" << "+R" << DecorativePot::getPotPrice(DecorativePot::ROTUND) << "\n";
                                            cout << left << setw(20) << " 3. Square Pot" << "+R" << DecorativePot::getPotPrice(DecorativePot::SQUARE) << "\n";
                                            cout << left << setw(20) << " 4. Vase Pot" << "+R" << DecorativePot::getPotPrice(DecorativePot::VASE) << "\n\nChoice: ";
                                
                                            potChoice = readInt();

                                            if(potChoice >= 0 && potChoice <= 4) break;

                                        }while (true);

                                        switch (potChoice) {
                                            case 1: selectedPot = DecorativePot::CLASSIC; break;
                                            case 2: selectedPot = DecorativePot::ROTUND; break;
                                            case 3: selectedPot = DecorativePot::SQUARE; break;
                                            case 4: selectedPot = DecorativePot::VASE; break;
                                            case 0: selectedPot = DecorativePot::NONE; break;
                                        }

                                        // STEP 2 CUSTOMIZE WRAPPING //
                                        GiftWrapping::WrappingType selectedWrap = GiftWrapping::NONE;
                                        int wrapChoice = -1;

                                        do{
                                            clearConsole();
                                            cout << "\033[1;32m\t  --- Customise your " << selectedPlant->getName() << " ---\n\n\033[0m";
                                            cout << "\033[1;36mSelect a wrapping type:\n\033[0m";
                                            cout << " 0. None\n";
                                            cout << left << setw(20) << " 1. Brown Paper" << "R" << GiftWrapping::getWrappingPrice(GiftWrapping::BROWN_PAPER) << "\n";
                                            cout << left << setw(20) << " 2. Floral Wrap" << "R" << GiftWrapping::getWrappingPrice(GiftWrapping::FLORAL_WRAP) << "\n";
                                            cout << left << setw(20) << " 3. Red Bow" << "R" << GiftWrapping::getWrappingPrice(GiftWrapping::RED_BOW) << "\n\nChoice: ";

                                            wrapChoice = readInt();

                                            if(wrapChoice >= 0 && wrapChoice <= 3) break;

                                        }while (true);

                                        switch(wrapChoice) {
                                            case 1: selectedWrap = GiftWrapping::BROWN_PAPER; break;
                                            case 2: selectedWrap = GiftWrapping::FLORAL_WRAP; break;
                                            case 3: selectedWrap = GiftWrapping::RED_BOW; break;
                                            case 0: selectedWrap = GiftWrapping::NONE; break;
                                        }

                                        /* ------------------------------------------ FINAL PRODUCT ------------------------------------------ */
                                        
                                        //build the order finally...
                                        nursery.startNewOrder();
                                        nursery.setOrderPlant(selectedPlant);
                                        nursery.addOrderPot(selectedPot);
                                        nursery.addOrderWrapping(selectedWrap);

                                        Product* finalProduct = nursery.finalizeOrder();

                                        clearConsole();
                                        cout << "\033[1;32m\t\t\t--- Your Final Product ---\n\n\033[0m";
                                        
                                        
                                        cout << "\033[1;36m" << left << setw(15) << "Name:" << "\033[0m" << finalProduct->getName() << "\n";
                                        cout << "\033[1;36m" << left << setw(15) << "Description:" << "\033[0m" << finalProduct->getDescription() << "\n";
                                        cout << "\033[1;36m" << left << setw(15) << "Total Price:" << "\033[0m" << "R" << fixed << setprecision(2) << finalProduct->getPrice() << "\n\n";

                                        if (promptYesNo("Do you want to add this product to your cart?")) {
                                                nursery.addToCart(finalProduct);
                                                nursery.getShopInventory()->removePlant(selectedPlant);
                                                selectedPlant = NULL;
                                                pressEnterToContinue();
                                        }
                                    }
                                }
                            }
                        }break;

                        case 4:
                        {   
                            /* ------------------------------------------ VIEW CART ------------------------------------------ */
                            
                            bool viewingCart = true;
                            while (viewingCart) {
                                clearConsole();
                                
                                cout << "\033[1;32m\t\t\t     --- Cart Summary ---\n\n\033[0m";
                                cout << "\t\t"  << "\033[1;32m|\033[0m 1. Checkout " << "\033[1;32m|\033[0m 2. Remove Item " << "\033[1;32m|\033[0m 0. <-- Back " << "\033[1;32m|\033[0m\n\n";

                                nursery.viewCart();

                                cout << "\nChoice: ";
                                int cartChoice = readInt();

                                switch (cartChoice) {
                                    /* ------------------------------------------ CHECKOUT ------------------------------------------ */
                                    case 1:
                                    {   
                                        ShoppingCart* cart = nursery.getCart();
                                        if (cart && !cart->getItems().empty()) {
                                            double total = 0.0;
                                            for (Product* p : cart->getItems()) {
                                                total += p->getPrice();
                                            }

                                            clearConsole();
                                            cout << "\033[1;32m--- Thank you for your purchase!-- \n\033[0m\n";
                                            cout << "Total amount paid: R" << fixed << setprecision(2) << total << "\n\n";

                                            cart->clear();

                                            pressEnterToContinue();
                                        } else {
                                            cout << "\033[1;31mYour cart is empty.\033[0m\n";
                                            pressEnterToContinue();
                                        }
                                    }break;
                                    
                                    case 2:
                                    {   
                                        /* ------------------------------------------ REMOVE ITEM FROM CART ------------------------------------------ */
                                        cout << "Enter the number of the item to remove: ";
                                        int itemNumber = readInt();
                                        ShoppingCart* cart = nursery.getCart();
                                        if(cart) {
                                            if (itemNumber > 0 && itemNumber <= cart->getItems().size()) {
                                                Product* removed = cart->removeProduct(itemNumber - 1);
                                                if (removed) {
                                                    Plant* basePlant = removed->getBasePlant();
                                                    if (basePlant) {
                                                        nursery.getShopInventory()->addPlant(basePlant);
                                                    }
                                                    delete removed;
                                                }
                                            }
                                        }
                                    }break;
                                        
                                        
                                        
                                    case 0:
                                        viewingCart = false;
                                        break;
                                    default:
                                        cout << "\033[1;31mInvalid choice. Try again.\033[0m\n";
                                        break;
                                }

                            }
                        }
                        break;

                        /* ------------------------------------------ CUSTOMER SUPPORT ------------------------------------------ */
                        case 5: 
                        {
                            bool inSupport = true;
                            while (inSupport){
                                clearConsole();
                                cout << "\033[1;32m\t--- Customer Support ---\033[0m\n\n";
                                cout << "1. Request a plant\n";
                                cout << "2. Ask for advice\n";
                                cout << "3. Get plant recommendation\n";
                                cout << "0. Back\n\nChoice: ";
                                int supportChoice = readInt();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                                /* ------------------------------------------ CHECK STOCK ------------------------------------------ */
                                switch (supportChoice) {
                                
                                    case 1: {
                                        cout << "Enter plant name you want: ";
                                        string plantName;
                                        getline(cin, plantName);

                                        string response = nursery.executeCustomerCommand(
                                            "check_stock",
                                            plantName,
                                            0,
                                            "", "", "", "",
                                            DecorativePot::NONE,
                                            GiftWrapping::NONE
                                        );
                                        cout << "\nResponse: " << response << "\n";

                                        if(response.find("available in the shop") != string::npos) {
                                            cout << "\nWould you like to add this to your cart? (y/n): ";
                                            char choice;
                                            cin >> choice;
                                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                                            if (choice == 'y' || choice == 'Y') {
                                                Plant* selectedPlant = nursery.getShopInventory()->get(plantName);
                                                if (selectedPlant) {
                                                    
                                                    nursery.startNewOrder();
                                                    nursery.setOrderPlant(selectedPlant);
                                                    nursery.addOrderPot(DecorativePot::NONE);
                                                    nursery.addOrderWrapping(GiftWrapping::NONE);

                                                    Product* selectedProduct = nursery.finalizeOrder();
                                                    nursery.getCart()->addProduct(selectedProduct);

                                                    cout << "\n'" << plantName << "' has been added to your cart!\n";
                                                }
                                            }
                                        }

                                        pressEnterToContinue();
                                        break;
                                    }
                                    case 2: {
                                        cout << "Enter the plant you want advice on: ";
                                        string question;
                                        getline(cin, question);

                                        string response = nursery.executeCustomerCommand(
                                            "ask_question",
                                            "",
                                            0,
                                            question,
                                            "",
                                            "",
                                            "",
                                            DecorativePot::NONE,
                                            GiftWrapping::NONE
                                        );
                                        cout << "\nResponse: " << response << "\n";
                                        pressEnterToContinue();
                                        break;
                                    }
                                    case 3: {
                                        string sunlight, space, experience;

                                        //Validate sunlight
                                        while (true) {
                                            cout << "Enter sunlight condition (low/medium/high): ";
                                            getline(cin, sunlight);
                                            if (sunlight == "low" || sunlight == "medium" || sunlight == "high") break;
                                            cout << "Invalid input. Please enter low, medium, or high.\n";
                                        }

                                        //Validate space
                                        while (true) {
                                            cout << "Enter space availability (small/medium/large): ";
                                            getline(cin, space);
                                            if (space == "small" || space == "medium" || space == "large") break;
                                            cout << "Invalid input. Please enter small, medium, or large.\n";
                                        }

                                        //Validate experience
                                        while (true) {
                                            cout << "Enter experience level (beginner/intermediate/expert): ";
                                            getline(cin, experience);
                                            if (experience == "beginner" || experience == "intermediate" || experience == "expert") break;
                                            cout << "Invalid input. Please enter beginner, intermediate, or expert.\n";
                                        }

                                        string response = nursery.executeCustomerCommand(
                                            "get_recommendation",
                                            "",
                                            0,
                                            "",
                                            sunlight,
                                            space,
                                            experience,
                                            DecorativePot::NONE,
                                            GiftWrapping::NONE
                                        );
                                        pressEnterToContinue();
                                        break;
                                    }
                                    case 0:
                                        inSupport = false;
                                        break;
                                    default:
                                        cout << "Invalid choice. Try again.\n";
                                        pressEnterToContinue();
                                    }
                                }
                                break;
                            }

                        /* ------------------------------------------ SEARCH ------------------------------------------ */ 
                        case 2:
                        {   
                            bool backToMenu = false;

                            while (!backToMenu) {
                                clearConsole();
                                
                                cout << "\033[1;32m\t\t      --- Search Plants ---\n\n\033[0m";
                                cout << "0. <-- Back\n" << endl;
                                cout << "Enter a keyword to search:";
                                
                                string keyword;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                getline(cin, keyword);

                                if (keyword == "0") {
                                    backToMenu = true;
                                    break;
                                }

                                vector<Plant*> searchResults = nursery.getPlantsByKeyword(keyword);

                                if (searchResults.empty()) {
                                    cout << "\nNo plants found matching \"" << keyword << "\". Try again.\n";
                                    cout << "Press Enter to continue...";
                                    cin.get();
                                    continue; 
                                }

                                bool searching = true;
                                while (searching) {
                                    clearConsole();
                                    cout << "\033[1;32m\t--- Search Results for \"" << keyword << "\" ---\n\n\033[0m";

                                    vector<Plant*> uniquePlants;
                                    vector<string> displayed;

                                    for (Plant* plant : searchResults) {
                                        string name = plant->getName();
                                        if (find(displayed.begin(), displayed.end(), name) != displayed.end()) continue;
                                        displayed.push_back(name);
                                        uniquePlants.push_back(plant);

                                        displayPlantCard(uniquePlants.size(), plant->getName(), plant->getPrice(), 22, 12);
                                    }

                                    cout << "0. <-- Back" << endl;

                                    Plant* selectedPlant = nullptr;
                                    int plantChoice = -1;

                                    cout << "\nSelect a Plant: ";
                                    while (true) {
                                        plantChoice = readInt();
                                        if (plantChoice == 0) {
                                            searching = false;
                                            break;
                                        }
                                        if (plantChoice > 0 && plantChoice <= (int)uniquePlants.size()) {
                                            selectedPlant = uniquePlants[plantChoice - 1];
                                            break;
                                        }
                                    }

                                    if (selectedPlant) {
                                        clearConsole();

                                        cout << "\033[1;32m\t--- Viewing " << selectedPlant->getName() <<  " details" << " ---\n\n\033[0m";
                                        
                                        GetPlantInfoCommand infoCmd(selectedPlant->getName(), &nursery);
                                        infoCmd.execute(NULL);

                                        char addChoice;
                                        do {
                                            cout << "Proceed to customisation? (y/n): ";
                                            cin >> addChoice;
                                            addChoice = tolower(addChoice);
                                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        } while (addChoice != 'y' && addChoice != 'n');

                                        /* ------------------------------------------ CUSTOMIZE PLANT ------------------------------------------ */
                                        if (addChoice == 'y') {
                                            
                                            // STEP 1 CUSTOMIZE POT //
                                            DecorativePot::PotType selectedPot = DecorativePot::NONE;
                                            int potChoice = -1;

                                            do {
                                                clearConsole();
                                                cout << "\033[1;32m\t  --- Customise your " << selectedPlant->getName() << " ---\n\n\033[0m";
                                                cout << "\033[1;36mSelect a pot type:\n\033[0m";
                                                cout << " 0. None\n";
                                                cout << left << setw(20) << " 1. Classic Pot" << "+R" << DecorativePot::getPotPrice(DecorativePot::CLASSIC) << "\n";
                                                cout << left << setw(20) << " 2. Rotund Pot" << "+R" << DecorativePot::getPotPrice(DecorativePot::ROTUND) << "\n";
                                                cout << left << setw(20) << " 3. Square Pot" << "+R" << DecorativePot::getPotPrice(DecorativePot::SQUARE) << "\n";
                                                cout << left << setw(20) << " 4. Vase Pot" << "+R" << DecorativePot::getPotPrice(DecorativePot::VASE) << "\n\nChoice: ";
                                    
                                                potChoice = readInt();

                                                if(potChoice >= 0 && potChoice <= 4) break;

                                            }while (true);

                                            switch (potChoice) {
                                                case 1: selectedPot = DecorativePot::CLASSIC; break;
                                                case 2: selectedPot = DecorativePot::ROTUND; break;
                                                case 3: selectedPot = DecorativePot::SQUARE; break;
                                                case 4: selectedPot = DecorativePot::VASE; break;
                                                case 0: selectedPot = DecorativePot::NONE; break;
                                            }

                                            // STEP 2 CUSTOMIZE WRAPPING //
                                            GiftWrapping::WrappingType selectedWrap = GiftWrapping::NONE;
                                            int wrapChoice = -1;

                                            do{
                                                clearConsole();
                                                cout << "\033[1;32m\t  --- Customise your " << selectedPlant->getName() << " ---\n\n\033[0m";
                                                cout << "\033[1;36mSelect a wrapping type:\n\033[0m";
                                                cout << " 0. None\n";
                                                cout << left << setw(20) << " 1. Brown Paper" << "R" << GiftWrapping::getWrappingPrice(GiftWrapping::BROWN_PAPER) << "\n";
                                                cout << left << setw(20) << " 2. Floral Wrap" << "R" << GiftWrapping::getWrappingPrice(GiftWrapping::FLORAL_WRAP) << "\n";
                                                cout << left << setw(20) << " 3. Red Bow" << "R" << GiftWrapping::getWrappingPrice(GiftWrapping::RED_BOW) << "\n\nChoice: ";

                                                wrapChoice = readInt();

                                                if(wrapChoice >= 0 && wrapChoice <= 3) break;

                                            }while (true);

                                            switch(wrapChoice) {
                                                case 1: selectedWrap = GiftWrapping::BROWN_PAPER; break;
                                                case 2: selectedWrap = GiftWrapping::FLORAL_WRAP; break;
                                                case 3: selectedWrap = GiftWrapping::RED_BOW; break;
                                                case 0: selectedWrap = GiftWrapping::NONE; break;
                                            }

                                            /* ------------------------------------------ FINAL PRODUCT ------------------------------------------ */
                                            
                                            //build the order finally...
                                            nursery.startNewOrder();
                                            nursery.setOrderPlant(selectedPlant);
                                            nursery.addOrderPot(selectedPot);
                                            nursery.addOrderWrapping(selectedWrap);

                                            Product* finalProduct = nursery.finalizeOrder();

                                            clearConsole();
                                            cout << "\033[1;32m\t\t\t--- Your Final Product ---\n\n\033[0m";
                                            
                                            
                                            cout << "\033[1;36m" << left << setw(15) << "Name:" << "\033[0m" << finalProduct->getName() << "\n";
                                            cout << "\033[1;36m" << left << setw(15) << "Description:" << "\033[0m" << finalProduct->getDescription() << "\n";
                                            cout << "\033[1;36m" << left << setw(15) << "Total Price:" << "\033[0m" << "R" << fixed << setprecision(2) << finalProduct->getPrice() << "\n\n";

                                            if (promptYesNo("Do you want to add this product to your cart?")) {
                                                    nursery.addToCart(finalProduct);
                                                    nursery.getShopInventory()->removePlant(selectedPlant);
                                                    selectedPlant = NULL;
                                                    pressEnterToContinue();
                                            }
                                        }
                                        searching = false;
                                    }
                                }
                            }
                        }break;

                        /* ------------------------------------------ SPECIAL BUNDLES ------------------------------------------ */
                        case 3:
                        {
                            displaySpecialBundlesMenu(&nursery);
                            break;
                        }
                            

                        case 0: break;
                        default: cout << "\033[1;31mInvalid option\033[0m\n";
                    }
                } while (custChoice != 0);
                break;


                break;
            }

            /* ------------------------------------------ STAFF MENU ------------------------------------------ */   
            case 2:
            {   
                bool inStaffMenu = true;

                while (inStaffMenu) {
                    clearConsole();
                    cout << "\033[1;32m";
                    cout << "\033[0m\n";

                    cout << "\033[1;32m\t\t\t\t--- Staff Menu ---\n\n\033[0m";

                    cout << "\033[1;32m|\033[0m 1. Go to Nursery \033[1;32m|\033[0m 2. View Notifications \033[1;32m|\033[0m 3. View Daily tasks \033[1;32m|\033[0m 0. <-- Back \033[1;32m|\033[0m\n\n";
                    
                    cout << "\nChoice: ";

                    int staffChoice = readInt();

                    switch (staffChoice)
                    {
                        case 1:
                        { 
                            bool gardening = true;

                            while (gardening) {
                                clearConsole();
                                cout << "\033[1;32m\t\t\t\t--- Nursery ---\033[0m\n\n";
                                cout << "\033[1;32m|\033[0m 1. Pass Time \033[1;32m|\033[0m 2. Water a Plant \033[1;32m|\033[0m 3. Water All Plants \033[1;32m|\033[0m 4. Move Ready Plants \033[1;32m|\033[0m 0. <-- Back \033[1;32m|\033[0m\n\n";

                                vector<Plant*> nurseryPlants = nursery.getNurseryInventory()->getAll();

                                if (nurseryPlants.empty()) {
                                    cout << "No plants currently in the nursery.\n\n";
                                } else {
                                    cout << "\033[38;5;34m-----------------------------------\033[0m";
                                    cout << "\n        Plants in Nursery\n";
                                    cout << "\033[38;5;34m-----------------------------------\033[0m\n\n";

                                    int i = 0;
                                    for (Plant* p : nurseryPlants) {
                                        string stateName = p->getStateName();
                                        string coloredState;

                                        if (stateName == "Dry") {
                                            coloredState = "\033[1;31m[" + stateName + "]\033[0m";
                                        } else if (stateName == "Ready for Sale") {
                                            coloredState = "\033[1;32m[" + stateName + "]\033[0m";
                                        } else {
                                            coloredState = "\033[1;34m[" + stateName + "]\033[0m";
                                        }

                                        cout << i + 1 << ". " << p->getName() << " " << coloredState;

                                        if (stateName != "Ready for Sale") {
                                            cout << "  Water lvl: " << (int)p->getWaterLevel();
                                        }

                                        cout << "\n";
                                        i++;
                                    }
                                    cout << "\n";
                                }

                                cout << "Choice: ";
                                int gardenerChoice = readInt();

                                switch (gardenerChoice) {

                                    /* ------------------------------------------ SIMULATE TIME ------------------------------------------ */
                                    case 1: {
                                        nursery.getNurseryInventory()->passTimeAll();
                                        cout << "\033[1;32m\nTime has passed for all plants.\n\033[0m";
                                        pressEnterToContinue();
                                        break;
                                    }

                                    /* ------------------------------------------ WATER SINGLE PLANT ------------------------------------------ */
                                    case 2: {
                                        if (nurseryPlants.empty()) {
                                            cout << "\nNo plants to water.\n";
                                            pressEnterToContinue();
                                            break;
                                        }

                                        int plantChoice = -1;
                                        Plant* selectedPlant = nullptr;

                                        while (true) {
                                            cout << "\nSelect a plant to water (0 to go back): ";
                                            plantChoice = readInt();
                                            if (plantChoice == 0) break;
                                            if (plantChoice > 0 && plantChoice <= (int)nurseryPlants.size()) {
                                                selectedPlant = nurseryPlants[plantChoice - 1];
                                                break;
                                            }
                                            cout << "Invalid choice. Try again.\n";
                                        }

                                        if (selectedPlant) {
                                            selectedPlant->water();
                                            cout << "\033[1;32m\n" << selectedPlant->getName() << " has been watered.\033[0m" << endl;
                                        }

                                        pressEnterToContinue();
                                        break;
                                    }

                                    /* ------------------------------------------ WATER ALL PLANTS ------------------------------------------ */
                                    case 3: {
                                        nursery.getNurseryInventory()->waterAll();
                                        cout << "\033[1;32m\nAll plants have been watered.\n\033[0m";
                                        pressEnterToContinue();
                                        break;
                                    }

                                    /* ------------------------------------------ MOVE TO STORE ------------------------------------------ */
                                    case 4: {
                                        nursery.getNurseryInventory()->moveReadyPlantsTo(nursery.getShopInventory());
                                        cout << "\033[1;32m\nAll ready plants have been moved.\n\033[0m";
                                        pressEnterToContinue();
                                        break;
                                    }

                                    /* ------------------------------------------ BACK ------------------------------------------ */
                                    case 0: {
                                        gardening = false;
                                        break;
                                    }

                                    default:
                                        cout << "Invalid choice.\n";
                                        pressEnterToContinue();
                                        break;
                                }
                            }

                            
                            break;
                        }

                        /* ------------------------------------------ View Notifications ------------------------------------------ */
                        case 2: 
                        {
                            bool viewingNotifications = true;

                            while (viewingNotifications) {
                                clearConsole();
                                cout << "\033[1;32m\t\t\t\t--- Plant Notifications ---\033[0m\n\n";

                                // Gardener will receive notifications
                                StaffMember* selectedStaff = gardener;

                                // Trigger all plants to notify gardener if needed
                                bool anyNotifications = false;
                                vector<Plant*> nurseryPlants = nursery.getNurseryInventory()->getAll();

                                for (Plant* p : nurseryPlants) {
                                    string state = p->getStateName();
                                    if (state == "Dry") {
                                        p->signalNeed("\033[1;31mDry\033[0m");
                                        anyNotifications = true;
                                    } else if (state == "Ready for Sale") {
                                        p->signalNeed("\033[1;32mReady to move to shop\033[0m"); 
                                        anyNotifications = true;
                                    }
                                }

                                if (!anyNotifications) {
                                    cout << "\033[1;36mAll plants' needs are met. No action required currently.\033[0m\n\n";
                                }

                                cout << "\n0. <-- Back\n";
                                string dummy;
                                getline(cin, dummy);
                                if (dummy == "0") viewingNotifications = false;
                            }

                            break;
                        }

                        /* ------------------------------------------ View Daily Tasks ------------------------------------------ */
                        case 3:
                        {
                            bool viewingTasks = true;

                            while (viewingTasks) {
                                clearConsole();
                                
                                cout << "\033[1;32m\t\t\t\t--- View Daily Tasks ---\033[0m\n\n";

                                cout << "1. Gardener\n";
                                cout << "2. Salesman\n";
                                cout << "3. Manager\n\n";
                                cout << "0. <-- Back\n\n";

                                cout << "Select your staff role: ";
                                int roleChoice = readInt();

                                switch (roleChoice)
                                {
                                    case 1:
                                        // Task message in cyan
                                        cout << "\n\033[1;36mHere are your daily tasks, Gardener:\033[0m\n";
                                        gardener->templateWorkCycle();
                                        pressEnterToContinue();
                                        break;

                                    case 2:
                                        cout << "\n\033[1;36mHere are your daily tasks, Salesman:\033[0m\n";
                                        salesman->templateWorkCycle();
                                        pressEnterToContinue();
                                        break;

                                    case 3:
                                        cout << "\n\033[1;36mHere are your daily tasks, Manager:\033[0m\n";
                                        manager->templateWorkCycle();
                                        pressEnterToContinue();
                                        break;

                                    case 0:
                                        viewingTasks = false;
                                        break;

                                    default:
                                        cout << "\033[1;31mInvalid choice. Try again.\033[0m\n";
                                        pressEnterToContinue();
                                        break;
                                }
                            }
                            break;
                        }

                        /* ------------------------------------------ BACK ------------------------------------------ */
                        case 0:
                            inStaffMenu = false;
                            break;

                        default:
                            cout << "Invalid choice.\n";
                            break;
                    }
                }
                
                break;
            }
            
            case 0:
            {   
                clearConsole();
                cout << "\033[1;32m\nThank you for visiting the Plant Nursery Simulator. Come back soon!\033[0m\n\n";
                break;
            }
                
            //WRONG ANSWER
            default:
            {
                cout << "\033[1;31mInvalid option. Try again.\033[0m\n";
            }
        }
    }while (choice != 0);

    delete gardener;
    delete salesman;
    delete manager;

    return 0;
}