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
    CurrencyExchange(const std::string& transactionId, double amount,
                     const std::string& description,
                     CurrencyAccount* account, Currency targetCurrency,
                     double usedRate, MarketDataService* market);
    ~CurrencyExchange() override;

    // Override abstract methods
    bool execute() override;
};

#endif // CURRENCYEXCHANGE_H