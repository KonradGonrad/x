#ifndef CURRENCY_ACCOUNT_H
#define CURRENCY_ACCOUNT_H

#include "Account.h"

class CurrencyAccount : public Account {
public:
    CurrencyAccount(const std::string& iban, double initialBalance,
                    Currency currency, const std::string& creationDate,
                    double spread = 0.02);
    ~CurrencyAccount() override;

    double getSpread() const;
    void setSpread(double spread);
    void updateBalanceAfterExchange(double amount);
    // Override abstract methods    
    double calculateMonthlyFees() const override;
    std::string toString() const override;

private:
    double spread;
};

using CurrencyAccountPtr = std::shared_ptr<CurrencyAccount>;

#endif // CURRENCYACCOUNT_H
