#include "InvestmentAccount.h"
#include "Exceptions.h"
#include <sstream>

InvestmentAccount::InvestmentAccount(const std::string& iban, double initialBalance,
                                     Currency currency, const std::string& creationDate,
                                     double brokerageFee)
    : Account(iban, initialBalance, currency, creationDate),
      brokerageFee(brokerageFee) {}

InvestmentAccount::~InvestmentAccount() {}

double InvestmentAccount::getBrokerageFee() const { return brokerageFee; }

void InvestmentAccount::setBrokerageFee(double fee) {
    if (fee < 0) throw ValidationException("Brokerage fee cannot be negative");
    brokerageFee = fee;
}

const std::map<std::string, int>& InvestmentAccount::getPortfolio() const {
    return portfolio;
}

void InvestmentAccount::buyStock(const std::string& ticker, int amount, double price) {
    if (status != AccountStatus::ACTIVE) throw AccountNotActiveException(iban);
    if (amount <= 0) throw ValidationException("Stock amount must be positive");
    if (ticker.empty()) throw ValidationException("Ticker cannot be empty");
    
    double totalCost = amount * price;
    double fee = totalCost * brokerageFee;
    double required = totalCost + fee;
    
    if (required > balance) throw InsufficientFundsException(required, balance);
    
    balance -= required;
    portfolio[ticker] += amount;
}

void InvestmentAccount::sellStock(const std::string& ticker, int amount, double price) {
    if (status != AccountStatus::ACTIVE) throw AccountNotActiveException(iban);
    if (amount <= 0) throw ValidationException("Stock amount must be positive");
    
    auto it = portfolio.find(ticker);
    if (it == portfolio.end() || it->second < amount) {
        throw InvalidOperationException("Insufficient shares to sell");
    }
    
    double totalValue = amount * price;
    double fee = totalValue * brokerageFee;
    
    portfolio[ticker] -= amount;
    if (portfolio[ticker] == 0) portfolio.erase(ticker);
    
    balance += (totalValue - fee);
}

double InvestmentAccount::calculateMonthlyFees() const {
    return balance * (brokerageFee / 12.0);
}

std::string InvestmentAccount::toString() const {
    std::ostringstream oss;
    oss << "InvestmentAccount[iban=" << iban << ", balance=" << balance
        << ", holdings=" << portfolio.size() << "]";
    return oss.str();
}
