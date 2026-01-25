#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <memory>
#include "Currency.h"

enum class AccountStatus { ACTIVE, BLOCKED, CLOSED };

class Account {
public:
    Account(const std::string& iban, double initialBalance,
            Currency currency, const std::string& creationDate);
    virtual ~Account();

    std::string getIban() const;
    double getBalance() const;
    Currency getCurrency() const;
    AccountStatus getStatus() const;
    std::string getCreationDate() const;

    void setStatus(AccountStatus status);
    virtual void deposit(double amount);
    virtual void withdraw(double amount);

    virtual double calculateMonthlyFees() const = 0;
    virtual std::string toString() const = 0;

protected:
    std::string iban;
    double balance;
    Currency currency;
    AccountStatus status;
    std::string creationDate;
};

using AccountPtr = std::shared_ptr<Account>;

#endif
