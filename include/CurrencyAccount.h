#ifndef CURRENCYACCOUNT_H
#define CURRENCYACCOUNT_H

#include "Account.h"

class CurrencyAccount : public Account {
private:
    double spread;

public:
    CurrencyAccount(const std::string& iban, double initialBalance,
                    Currency currency, const std::string& creationDate,
                    double spread = 0.02);
    ~CurrencyAccount() override;

    // Getters
    double getSpread() const;

    // Setters
    void setSpread(double spread);

    // Currency operations
    void updateBalanceAfterExchange(double amount);

    // Override abstract methods
    double calculateMonthlyFees() const override;
    std::string toString() const override;
};

#endif // CURRENCYACCOUNT_H
