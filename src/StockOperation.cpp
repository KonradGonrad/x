#include "StockOperation.h"
#include "Exceptions.h"
#include <sstream>

StockOperation::StockOperation(long id, InvestmentAccountPtr account,
                               const std::string& ticker, int quantity,
                               double pricePerShare, bool isBuy)
    : Transaction(id, quantity * pricePerShare,
                  isBuy ? TransactionType::STOCK_PURCHASE : TransactionType::STOCK_SALE),
      account(account), ticker(ticker), quantity(quantity),
      pricePerShare(pricePerShare), isBuy(isBuy) {}

StockOperation::~StockOperation() {}

InvestmentAccountPtr StockOperation::getAccount() const { return account; }
std::string StockOperation::getTicker() const { return ticker; }
int StockOperation::getQuantity() const { return quantity; }
double StockOperation::getPricePerShare() const { return pricePerShare; }
bool StockOperation::isBuyOperation() const { return isBuy; }
double StockOperation::getTotalValue() const { return quantity * pricePerShare; }

void StockOperation::execute() {
    if (!account) throw ValidationException("Account is null");
    
    if (isBuy) {
        account->buyStock(ticker, quantity, pricePerShare);
    } else {
        account->sellStock(ticker, quantity, pricePerShare);
    }
}

std::string StockOperation::toString() const {
    std::ostringstream oss;
    oss << "StockOperation[id=" << id
        << ", " << (isBuy ? "BUY" : "SELL")
        << " " << quantity << "x " << ticker
        << " @ " << pricePerShare << "]";
    return oss.str();
}
