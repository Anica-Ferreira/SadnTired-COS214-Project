#include "WebAPIAdapter.h"
#include "NurserySystemFacade.h"
#include <iostream>

using namespace std;

WebAPIAdapter::WebAPIAdapter(NurserySystemFacade* facade) : nurseryFacade(facade) {
    cout << "WebAPIAdapter initialized" << endl;
}

WebAPIAdapter::~WebAPIAdapter() {
    cout << "WebAPIAdapter destroyed" << endl;
}

string WebAPIAdapter::getShopProducts() {
    if (nurseryFacade) {
        return nurseryFacade->browseAllPlants();
    }
    return "{\"error\": \"System not available\"}";
}

string WebAPIAdapter::getNurseryPlants() {
    if (nurseryFacade) {
        return nurseryFacade->viewNurseryStatus();
    }
    return "{\"error\": \"System not available\"}";
}

string WebAPIAdapter::waterPlant(const string& plantName) {
    if (nurseryFacade) {
        return nurseryFacade->waterPlant(plantName);
    }
    return "{\"error\": \"System not available\"}";
}

string WebAPIAdapter::movePlantToShop(const string& plantName) {
    if (nurseryFacade) {
        return nurseryFacade->movePlantToShop(plantName);
    }
    return "{\"error\": \"System not available\"}";
}


string WebAPIAdapter::createCustomer(const string& name, const string& email) {
    return "{\"status\": \"success\", \"message\": \"Customer " + name + " created\", \"email\": \"" + email + "\"}";
}

string WebAPIAdapter::getRandomPlants() {
    if (nurseryFacade) {
        return nurseryFacade->browseAllPlants();
    }
    return "{\"error\": \"System not available\"}";
}

string WebAPIAdapter::getRandomBundle() {
    if (nurseryFacade) {
        return nurseryFacade->viewAvailableBundles();
    }
    return "{\"error\": \"System not available\"}";
}