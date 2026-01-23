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
    StockOperation(const std::string& transactionId, double amount,
                   const std::string& description,
                   InvestmentAccount* account, const std::string& ticker,
                   int quantity, MarketDataService* market);
    ~StockOperation() override;

    // Override abstract methods
    bool execute() override;
};

#endif // STOCKOPERATION_H