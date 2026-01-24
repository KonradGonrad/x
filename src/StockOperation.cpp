#include "StockOperation.h"
#include "InvestmentAccount.h"
#include "MarketDataService.h"
#include <sstream>
#include <iomanip>

StockOperation::StockOperation(long id, double amount, InvestmentAccount* account,
                               const std::string& ticker, int quantity,
                               MarketDataService* market)
    : Transaction(id, amount, TransactionType::STOCK_PURCHASE),
      account(account), ticker(ticker), quantity(quantity), market(market) {}

StockOperation::~StockOperation() {}

InvestmentAccount* StockOperation::getAccount() const {
    return account;
}

std::string StockOperation::getTicker() const {
    return ticker;
}

int StockOperation::getQuantity() const {
    return quantity;
}

MarketDataService* StockOperation::getMarket() const {
    return market;
}

bool StockOperation::execute() {
    if (!account || !market) {
        return false;
    }
    account->buyStock(ticker, quantity);
    return true;
}

std::string StockOperation::toString() const {
    std::ostringstream oss;
    auto timeinfo = std::localtime(&date);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    oss << "StockOperation[id=" << id
        << ", ticker=" << ticker
        << ", quantity=" << quantity
        << ", amount=" << amount
        << ", date=" << buffer
        << "]";
    return oss.str();
}
