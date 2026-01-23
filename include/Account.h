#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "Currency.h"
#include "AccountStatus.h"

class Account {
protected:
    std::string iban;
    double balance;
    Currency currency;
    AccountStatus status;
    std::string creationDate;

public:
    Account(const std::string& iban, double initialBalance,
            const std::string& currency, const std::string& creationDate);
    virtual ~Account();

    std::string getIban() const;
    double getBalance() const;
    Currency getCurrency() const;
    AccountStatus getStatus() const;
    std::string getCreationDate() const;

    void setStatus(AccountStatus status);
    // Operations
    virtual void deposit(double amount);
    virtual void withdraw(double amount);

    // Abstract methods
    virtual double calculateMonthlyFees() const = 0;
    virtual std::string toString() const = 0;
};

#endif // ACCOUNT_H