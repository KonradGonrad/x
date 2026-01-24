#ifndef SAVINGS_ACCOUNT_H
#define SAVINGS_ACCOUNT_H

#include "Account.h"

class SavingsAccount : public Account {
public:
    SavingsAccount(const std::string& iban, double initialBalance,
                   Currency currency, const std::string& creationDate,
                   double interestRate = 0.03);
    ~SavingsAccount() override;

    double getInterestRate() const;
    void setInterestRate(double rate);
    void capitalizeInterest();

    double calculateMonthlyFees() const override;
    std::string toString() const override;

private:
    double interestRate;
};

using SavingsAccountPtr = std::shared_ptr<SavingsAccount>;

#endif
