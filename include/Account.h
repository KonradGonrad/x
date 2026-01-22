#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
protected:
    std::string iban;
    double balance;
    std::string currency;
    std::string creationDate;
    bool active;

public:
    Account(const std::string& iban, double initialBalance,
            const std::string& currency, const std::string& creationDate);
    virtual ~Account();

    // Operations
    virtual bool deposit(double amount);
    virtual bool withdraw(double amount);

    // Abstract methods
    virtual double calculateMonthlyFees() const = 0;
};

#endif // ACCOUNT_H