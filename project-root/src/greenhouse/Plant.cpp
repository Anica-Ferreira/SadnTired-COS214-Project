/**
 * @class [Plant]
 * @brief [Implementation of the Plant class and its derived classes]
 * @details [Handles plant lifecycle, watering strategies, and state management]
 * @authors [Anica Ferreira, Anika Coetzer, Chloe Kruger, Daniel Stevens, Jordan Reddy]
 */

#include "Plant.h"

/**
 * @brief [Constructs a new Plant object]
 * @param[in] name [Plant name]
 * @param[in] type [Plant type]
 * @param[in] price [Plant price]
 * @param[in] strategy [Watering strategy for the plant]
 * @param[in] description [Plant description]
 */
Plant::Plant(const string& name, const string& type, double price, WateringStrategy* strategy, const string& description)
    : name(name), type(type), description(description), price(price),
      waterLevel(0.0), wateringStrategy(strategy), state(new PlantedState()), wateringCount(0) {}
     
/**
 * @brief [Destroys the Plant object and cleans up resources]
 */      
Plant::~Plant() {
    delete state;
    delete wateringStrategy;
}

//Getters
/**
 * @brief [Gets the current state name of the plant]
 * @return [Current state name]
 */
string Plant::getStateName() const {
    return state->getStateName();
}

/**
 * @brief [Gets the current water level of the plant]
 * @return [Current water level]
 */
double Plant::getWaterLevel() const {
    return waterLevel;
}

/**
 * @brief [Gets the current name of the plant]
 * @return [Current name]
 */
string Plant::getName() const {
    return name;
}

/**
 * @brief [Gets the current type of the plant]
 * @return [Current type]
 */
string Plant::getType() const {
    return type;
}

/**
 * @brief [Gets the current price of the plant]
 * @return [Current price]
 */
double Plant::getPrice() const {
    return price;
}

/**
 * @brief [Gets the current description of the plant]
 * @return [Current description]
 */
string Plant::getDescription() const {
    return description;
}

/**
 * @brief [Gets the watering strategy of the plant]
 * @return [Pointer to water strategy]
 */
WateringStrategy* Plant::getStrategy() const {
    return wateringStrategy;
}

//Setters

/**
 * @brief [Sets the water level of the plant]
 * @param[in] level [New water level]
 */
void Plant::setWaterLevel(double level) {
    waterLevel = level;
}

/**
 * @brief [Sets the state of the plant]
 * @param[in] newState [New state]
 */
void Plant::setState(PlantState* newState) {
    if (state != newState) {
        delete state;
        state = newState;
    }
}

/**
 * @brief [Waters the plant using its watering strategy]
 */
void Plant::water() {
    state->handleWatering(this);
}

/**
 * @brief [Advances time for the plant, affecting its state]
 */
void Plant::passTime() {
    state->handlePassTime(this);
}

/**
 * @brief [Increases the watering count]
 */
void Plant::increaseWateringCount() {
    wateringCount++;
}

/**
 * @brief [Checks if the plant is ready for sale]
 * @return [True if plant is ready for sale, false otherwise]
 */
bool Plant::isReadyForSale() const {
    return wateringCount >= getRequiredWaterings();
}


// Succulent

/**
 * @brief [Constructs a new Succulent object]
 * @param[in] name [Succulent name]
 * @param[in] price [Succulent price]
 * @param[in] strategy [Watering strategy for succulent]
 * @param[in] description [Succulent description]
 */
Succulent::Succulent(const string& name, double price, WateringStrategy* strategy, const string& description)
    : Plant(name, "Succulent", price, strategy, description) {}


/**
 * @brief [Gets the number of waterings required for succulent to be ready]
 * @return [Required waterings count]
 */    
int Succulent::getRequiredWaterings() const {
    return 5;  // Succulents need fewer waterings
}

// Flower

/**
 * @brief [Constructs a new Flower object]
 * @param[in] name [Flower name]
 * @param[in] price [Flower price]
 * @param[in] strategy [Watering strategy for flower]
 * @param[in] description [Flower description]
 */
Flower::Flower(const string& name, double price, WateringStrategy* strategy, const string& description)
    : Plant(name, "Flower", price, strategy, description) {}

/**
 * @brief [Gets the number of waterings required for flower to be ready]
 * @return [Required waterings count]
 */
int Flower::getRequiredWaterings() const {
    return 10;  // Flowers need moderate waterings
}

// Tree

/**
 * @brief [Constructs a new Tree object]
 * @param[in] name [Tree name]
 * @param[in] price [Tree price]
 * @param[in] strategy [Watering strategy for tree]
 * @param[in] description [Tree description]
 */
Tree::Tree(const string& name, double price, WateringStrategy* strategy, const string& description)
    : Plant(name, "Tree", price, strategy, description) {}

/**
 * @brief [Gets the number of waterings required for tree to be ready]
 * @return [Required waterings count]
 */
int Tree::getRequiredWaterings() const {
    return 15;  // Trees need more waterings to mature
}

//Jordan's

/**
 * @brief [Attaches an observer to the plant]
 * @param[in] observer [Pointer to the observer to attach]
 */
void Plant::Attach(IObserver* observer) {
    observers_.push_back(observer);
}//add observer to list

/**
 * @brief [Detaches an observer from the plant]
 * @param[in] observer [Pointer to the observer to detach]
 */
void Plant::Detach(IObserver* observer) {
    observers_.remove(observer);
}//remove observer from list

/**
 * @brief [Notifies all attached observers of plant state changes]
 */
void Plant::Notify() {
    for (auto* o : observers_) {
        o->Update(current_need_ + " for plant " + name);
    }
}//loop through observers and update on all

/**
 * @brief [Signals a need and notifies observers]
 * @param[in] need [The need message to signal]
 */
void Plant::signalNeed(string need) {
    current_need_ = need;
    Notify();
}//set need and call notify, extension

void Plant::printSummary(int stock) const {
    const string color = "\033[96m";
    const string reset = "\033[0m";

    cout << string(45, '=') << "\n";

    cout << color;
    cout << left << setw(15) << "Name:";
    cout << reset << name << "\n";

    cout << color;
    cout << left << setw(15) << "Type:";
    cout << reset << type << "\n";

    cout << color;
    cout << left << setw(15) << "Price:";
    cout << reset << "R" << fixed << setprecision(2) << price << "\n";

    cout << color;
    cout << left << setw(15) << "Stock:";
    cout << reset << stock << "\n";

    cout << color;
    cout << left << setw(15) << "Description:";
    cout << reset << description << "\n";

    cout << string(45, '=') << "\n\n";
}