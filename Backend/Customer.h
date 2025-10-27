// Customer.h - UPDATED
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
using namespace std;

class CustomerCommand;

class Customer {
private:
    string name;
    string email;
    string phoneNum;
    string surname;
    vector<CustomerCommand*> commandHistory;

public:
    Customer();
    Customer(const string& customerName, const string& customerSurname,
             const string& customerEmail, const string& customerPhone = "");
    ~Customer();

    // Getters
    string getName() const { return name + " " + surname; }
    string getEmail() const { return email; }
    string getPhone() const { return phoneNum; }
    string getSurname() const { return surname; }

    // Setters - FIXED (remove const)
    void setName(const string& newName) { name = newName; }
    void setEmail(const string& newEmail) { email = newEmail; }
    void setPhone(const string& newPhone) { phoneNum = newPhone; }
    void setSurname(const string& newSurname) { surname = newSurname; }

    // Command execution methods
    void executeCommand(CustomerCommand* command);
    void showCommandHistory() const;

    // Customer actions that will be handled by commands
    string purchasePlant(const string& plantName, int quantity);
    string requestPlantCare(const string& plantName, const string& careType);
    string checkPlantStock(const string& plantName);
    string requestRefund(const string& plantName, const string& reason);
    string getPlantInfo(const string& plantName);

private:
    void cleanup();
};

#endif