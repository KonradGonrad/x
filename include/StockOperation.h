#ifndef STOCKOPERATION_H
#define STOCKOPERATION_H

#include "Transaction.h"
#include <string>

class InvestmentAccount;
class MarketDataService;

class StockOperation : public Transaction {
private:
    InvestmentAccount* account;
    std::string ticker;
    int quantity;
    MarketDataService* market;

public:
    StockOperation(long id, double amount, InvestmentAccount* account,
                   const std::string& ticker, int quantity,
                   MarketDataService* market);
    ~StockOperation() override;

    // Getters
    InvestmentAccount* getAccount() const;
    std::string getTicker() const;
    int getQuantity() const;
    MarketDataService* getMarket() const;

    // Override abstract methods
    bool execute() override;
    std::string toString() const override;
};

#endif // STOCKOPERATION_H
