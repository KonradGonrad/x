#ifndef CURRENCYACCOUNT_H
#define CURRENCYACCOUNT_H

#include "Account.h"

class CurrencyAccount : public Account {
private:
    double spread;  // e.g., 0.02 for 2% spread

public:
    CurrencyAccount(const std::string& iban, double initialBalance,
                    Currency currency, const std::string& creationDate,
                    double spread = 0.005);
    ~CurrencyAccount() override;

    // Currency operations
    double getSpread() const;
    void setSpread(double spread);
    void updateBalanceAfterExchange(double amount);
    // Override abstract methods
    double calculateMonthlyFees() const override;
    std::string toString() const override;
};

#endif // CURRENCYACCOUNT_H