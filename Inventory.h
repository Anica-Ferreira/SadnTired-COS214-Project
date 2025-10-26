#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>
#include <map>
#include "Plant.h"

class Inventory {
private:
    std::vector<Plant*> plants;

public:
    ~Inventory();

    void addPlant(Plant* plant);
    std::vector<Plant*> getAll() const;
    Plant* get(int index) const;
    int size() const;

    void waterAll();
    void passTimeAll();

    void printStockCounts() const;

    void removePlant(Plant* plant);
    // Moves all ready-for-sale plants from this inventory to another
    void moveReadyPlantsTo(Inventory& store);
};

#endif // INVENTORY_H