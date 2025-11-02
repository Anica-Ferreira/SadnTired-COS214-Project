#ifndef INVENTORY_H
#define INVENTORY_H

using namespace std;
#include <vector>
#include <string>
#include <map>
#include "../greenhouse/Plant.h"

class Inventory {
private:
    vector<Plant*> plants;
public:
    ~Inventory();

    void addPlant(Plant* plant);
    vector<Plant*> getAll() const;
    Plant* get(int index) const;
    Plant* get(const string& name) const;
    int size() const;

    void waterAll();
    void passTimeAll();

    void printStockCounts() const;

    void removePlant(Plant* plant);
    // Moves all ready-for-sale plants from this inventory to another
    void moveReadyPlantsTo(Inventory* other);

    //get quantity of specific plant by name
    int getQuantity(const string& plantName) const;

};

#endif // INVENTORY_H