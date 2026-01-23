#ifndef CURRENCYACCOUNT_H
#define CURRENCYACCOUNT_H

#include "Account.h"

class CurrencyAccount : public Account {
private:
    double spread;

public:
    CurrencyAccount(const std::string& iban, double initialBalance,
                    const std::string& currency, const std::string& creationDate,
                    double spread);
    ~CurrencyAccount() override;

    // Override abstract methods
    double calculateMonthlyFees() const override;
    void updateBalanceAfterExchange(double amount);
};

#endif // CURRENCYACCOUNT_H