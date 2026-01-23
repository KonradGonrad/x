#include "InvestmentAccount.h"
#include <sstream>

InvestmentAccount::InvestmentAccount(const std::string& iban, double initialBalance,
                                     Currency currency, const std::string& creationDate,
                                     double brokerageFee)
    : Account(iban, initialBalance, currency, creationDate),
      brokerageFee(brokerageFee) {}

InvestmentAccount::~InvestmentAccount() {}

double InvestmentAccount::getBrokerageFee() const { return brokerageFee; }

void InvestmentAccount::setBrokerageFee(double fee) {
    if (fee >= 0) {
        brokerageFee = fee;
    }
}

const std::map<std::string, int>& InvestmentAccount::getPortfolio() const {
    return portfolio;
}

void InvestmentAccount::buyStock(const std::string& ticker, int amount) {
    if (status != AccountStatus::ACTIVE || amount <= 0 || balance < amount) {
        return;
    }
    balance -= amount;
    portfolio[ticker] += amount;
}

double InvestmentAccount::calculateMonthlyFees() const {
    return balance * (brokerageFee / 12.0);
}

std::string InvestmentAccount::toString() const {
    std::ostringstream oss;
    oss << "InvestmentAccount[iban=" << iban
        << ", balance=" << balance
        << ", holdings=" << portfolio.size()
        << ", fee=" << (brokerageFee * 100) << "%]";
    return oss.str();
}
