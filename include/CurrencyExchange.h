#ifndef CURRENCYEXCHANGE_H
#define CURRENCYEXCHANGE_H

#include "Transaction.h"
#include "Currency.h"
#include <string>

class CurrencyAccount;
class MarketDataService;

class CurrencyExchange : public Transaction {
private:
    CurrencyAccount* account;
    Currency targetCurrency;
    double usedRate;
    MarketDataService* market;

public:
    CurrencyExchange(long id, double amount, CurrencyAccount* account,
                     Currency targetCurrency, double usedRate,
                     MarketDataService* market);
    ~CurrencyExchange() override;

    // Getters
    CurrencyAccount* getAccount() const;
    Currency getTargetCurrency() const;
    double getUsedRate() const;
    MarketDataService* getMarket() const;

    // Override abstract methods
    bool execute() override;
    std::string toString() const override;
};

#endif // CURRENCYEXCHANGE_H
