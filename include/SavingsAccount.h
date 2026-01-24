#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "Account.h"

class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount(const std::string& iban, double initialBalance,
                   Currency currency, const std::string& creationDate,
                   double interestRate = 0.03);
    ~SavingsAccount() override;

    // Getters
    double getInterestRate() const;

    // Setters
    void setInterestRate(double interestRate);

    // Operations
    void capitalizeInterest();

    // Override abstract methods
    double calculateMonthlyFees() const override;
    std::string toString() const override;
};

#endif // SAVINGSACCOUNT_H
