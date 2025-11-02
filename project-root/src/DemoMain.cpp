#include "core/NurserySystemFacade.h"
#include "inventory/Inventory.h"
#include "customer/ShoppingCart.h"
#include "products/DecorativePot.h"
#include "products/GiftWrapping.h"
#include "customer/CustomerCommand.h"

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

/* ------------------------------------------ MAIN FUNCTION ------------------------------------------ */

int main() {
    NurserySystemFacade nursery;

    int choice;

    do{
        clearConsole();

        cout << "\033[1;32m";
        cout << "======================================\033[0m\n";
        cout << "Welcome to the Plant Nursery Simulator\n";
        cout << "\033[1;32m======================================\n\n";
        cout << "\033[0m";

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
                    cout << "\033[1;32m\t\t      --- Customer Menu ---\n\n\033[0m";

                    cout << "1. Browse Plants  |  2. View Cart  |  3. Search Plants  |   0. <--Back \n\n";
                    cout << "Choice: ";

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
                            while (browsing) {
                                
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
                                    if (plantChoice == 0) {
                                        browsing = false;
                                        break;
                                    }
                                    if (plantChoice > 0 && plantChoice <= (int)uniquePlants.size()) {
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
                                        }
                                    }
                                }
                            }
                        }break;

                        case 2:
                        {   
                            /* ------------------------------------------ VIEW CART ------------------------------------------ */
                            
                            bool viewingCart = true;
                            while (viewingCart) {
                                clearConsole();
                                
                                cout << "\033[1;32m\t\t\t     --- Cart Summary ---\n\n\033[0m";
                                cout << "\t\t1. Checkout |  2. Remove Item |  0. <-- Back \n\n";

                                nursery.viewCart();

                                cout << "\nChoice: ";
                                int cartChoice = readInt();

                                switch (cartChoice) {
                                    case 1:
                                    {
                                        cout << "\033[1;32mCart cleared successfully!\033[0m\n";
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

                        /* ------------------------------------------ SEARCH ------------------------------------------ */ 
                        case 3:
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
                                            }
                                        }
                                        searching = false;
                                    }
                                }
                            }
                        }break;

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
                cout << "\033[1;32m\t--- Staff Menu ---\n\n\033[0m";
                
                break;
            }

            //EXIT
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


    return 0;
}