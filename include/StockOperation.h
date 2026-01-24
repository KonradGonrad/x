#ifndef STOCK_OPERATION_H
#define STOCK_OPERATION_H

#include "Transaction.h"
#include "InvestmentAccount.h"
#include <string>

class StockOperation : public Transaction {
public:
    StockOperation(long id, InvestmentAccountPtr account, const std::string& ticker,
                   int quantity, double pricePerShare, bool isBuy);
    ~StockOperation() override;

    InvestmentAccountPtr getAccount() const;
    std::string getTicker() const;
    int getQuantity() const;
    double getPricePerShare() const;
    bool isBuyOperation() const;
    double getTotalValue() const;

    void execute();
    std::string toString() const override;

private:
    InvestmentAccountPtr account;
    std::string ticker;
    int quantity;
    double pricePerShare;
    bool isBuy;
};

using StockOperationPtr = std::shared_ptr<StockOperation>;

#endif // STOCKOPERATION_H