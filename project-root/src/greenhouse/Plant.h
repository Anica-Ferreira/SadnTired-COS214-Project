#ifndef PLANT_H
#define PLANT_H

using namespace std;
#include <string>
#include <iostream>//J
#include <list>//J
#include <iomanip> 
#include "WateringStrategy.h"
#include "PlantState.h"
#include "../core/ISubject.h"//J
#include "../core/IObserver.h"    //J

class Plant {
private://all J
    list<IObserver*> observers_;//list of pointers
    string current_need_;
protected:
    //Stats/Plant Info
    string name;//Plant name
    string type;//plant type/ subclass
    string description;
    double price;
    double waterLevel;

    //Design Pattern Pointers
    WateringStrategy* wateringStrategy;
    PlantState* state;

    //State and Strategy
    int wateringCount;//
    virtual int getRequiredWaterings() const = 0;
    void increaseWateringCount();//waters?
    bool isReadyForSale() const;//changes to ready

public:
    //Constructors & Destructors
    Plant(const string& name, const string& type, double price, WateringStrategy* strategy,const string& description = "");
    virtual ~Plant();

    //Getters
    string getStateName() const;
    double getWaterLevel() const;
    string getName() const;
    string getType() const;
    double getPrice() const;
    string getDescription() const;

    //Setters
    void setWaterLevel(double level);
    void setState(PlantState* newState);

    void water();
    void passTime();  // Simulates time passing, decreasing water level
    WateringStrategy* getStrategy() const; // Declared here

    // Allow PlantState classes to access protected members
    friend class PlantState;
    friend class PlantedState;
    friend class WateredState;
    friend class DryState;
    friend class ReadyForSaleState;

    //J
    void Attach(IObserver* observer) ; //add observer to list
    void Detach(IObserver* observer) ; //remove observer from list
    void Notify() ;//loop through observers and update on all
    void signalNeed(string need);//set need and call notify, extension

    //for demo main
    void printSummary(int stock) const;
};

class Succulent : public Plant {
protected:
    int getRequiredWaterings() const override;

public:
    Succulent(const string& name, double price, WateringStrategy* strategy, const string& description = "");
};

class Flower : public Plant {
protected:
    int getRequiredWaterings() const override;

public:
    Flower(const string& name, double price, WateringStrategy* strategy, const string& description = "");
};

class Tree : public Plant {
protected:
    int getRequiredWaterings() const override;

public:
    Tree(const string& name, double price, WateringStrategy* strategy, const string& description = "");
};

#endif // PLANT_H