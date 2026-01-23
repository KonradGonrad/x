#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "Account.h"

class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount(const std::string& iban, double initialBalance,
                   const std::string& currency, const std::string& creationDate,
                   double interestRate, int withdrawalLimit = 3);
    ~SavingsAccount() override;

    // Override abstract methods
    double calculateMonthlyFees() const override;
    
    // Savings account specific methods
    void capitalizeInterest();
};

#endif // SAVINGSACCOUNT_H