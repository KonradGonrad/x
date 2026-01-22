#ifndef CURRENCYACCOUNT_H
#define CURRENCYACCOUNT_H

#include "Account.h"

class CurrencyAccount : public Account {
private:
    std::string baseCurrency;
    double exchangeRateToBase;

    double spread;  // e.g., 0.02 for 2% spread

public:
    CurrencyAccount(const std::string& iban, double initialBalance,
                    const std::string& currency, const std::string& creationDate,
                    const std::string& baseCurrency = "PLN");
    ~CurrencyAccount() override;

    // Currency operations
    double convertToBase() const;
    double convertFromBase(double baseAmount) const;

    // Override abstract methods
    double calculateMonthlyFees() const override;
    void updateBalanceAfterExchange(double amount);
};

#endif // CURRENCYACCOUNT_H