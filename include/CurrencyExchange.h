#ifndef CURRENCY_EXCHANGE_H
#define CURRENCY_EXCHANGE_H

#include "Transaction.h"
#include "CurrencyAccount.h"
#include "Currency.h"
#include <map>

class CurrencyExchange : public Transaction {
public:
    CurrencyExchange(long id, CurrencyAccountPtr sourceAccount,
                     CurrencyAccountPtr targetAccount,
                     double sourceAmount, double exchangeRate);
    ~CurrencyExchange() override;

    CurrencyAccountPtr getSourceAccount() const;
    CurrencyAccountPtr getTargetAccount() const;
    double getSourceAmount() const;
    double getTargetAmount() const;
    double getExchangeRate() const;

    void execute();
    std::string toString() const override;

    // Static method for getting default rates
    static double getDefaultRate(Currency from, Currency to);

private:
    CurrencyAccountPtr sourceAccount;
    CurrencyAccountPtr targetAccount;
    double sourceAmount;
    double exchangeRate;
    
    static std::map<std::pair<Currency, Currency>, double> defaultRates;
};

using CurrencyExchangePtr = std::shared_ptr<CurrencyExchange>;

#endif // CURRENCYEXCHANGE_H