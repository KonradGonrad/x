#include "CurrencyExchange.h"
#include "CurrencyAccount.h"
#include "MarketDataService.h"
#include <sstream>
#include <iomanip>

CurrencyExchange::CurrencyExchange(long id, double amount, CurrencyAccount* account,
                                   Currency targetCurrency, double usedRate,
                                   MarketDataService* market)
    : Transaction(id, amount, TransactionType::CURRENCY_EXCHANGE),
      account(account), targetCurrency(targetCurrency),
      usedRate(usedRate), market(market) {}

CurrencyExchange::~CurrencyExchange() {}

CurrencyAccount* CurrencyExchange::getAccount() const {
    return account;
}

Currency CurrencyExchange::getTargetCurrency() const {
    return targetCurrency;
}

double CurrencyExchange::getUsedRate() const {
    return usedRate;
}

MarketDataService* CurrencyExchange::getMarket() const {
    return market;
}

bool CurrencyExchange::execute() {
    if (!account || !market) {
        return false;
    }
    account->updateBalanceAfterExchange(amount);
    return true;
}

std::string CurrencyExchange::toString() const {
    std::ostringstream oss;
    auto timeinfo = std::localtime(&date);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    oss << "CurrencyExchange[id=" << id
        << ", amount=" << amount
        << ", rate=" << usedRate
        << ", date=" << buffer
        << "]";
    return oss.str();
}
