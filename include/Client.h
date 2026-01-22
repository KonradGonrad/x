#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include "Address.h"

class Account;  // Forward declaration

class Client {
protected:
    std::string email;
    std::string phoneNumber;
    int clientId;
    std::string name;

    Address* address;
    std::vector<Account*> accounts;

public:
    Client(const int& clientId, const std::string& name, Address* address);
    virtual ~Client();

    // Account management
    void addAccount(Account* account);
    bool removeAccount(const std::string& iban);
    Account* findAccount(const std::string& iban) const;

    // Abstract methods
    virtual std::string getClientType() const = 0;
    virtual double calculateTotalFees() const = 0;
    virtual std::string toString() const = 0;
};

#endif // CLIENT_H