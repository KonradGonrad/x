#include "InvestmentAccount.h"
#include <sstream>

InvestmentAccount::InvestmentAccount(const std::string& iban, double initialBalance,
                                             Currency currency, const std::string& creationDate,
                                     double brokerageFee)
    : Account(iban, initialBalance, currency, creationDate),
      brokerageFee(brokerageFee) {}

InvestmentAccount::~InvestmentAccount() {}

double InvestmentAccount::getBrokerageFee() const {
    return brokerageFee;
}

const std::map<std::string, int>& InvestmentAccount::getPortfolio() const {
    return portfolio;
}

void InvestmentAccount::setBrokerageFee(double fee) {
    this->brokerageFee = fee;
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
        << ", cashBalance=" << balance
        << ", holdings=" << portfolio.size()
        << ", brokerageFee=" << (brokerageFee * 100) << "%"
        << ", status=" << (status == AccountStatus::ACTIVE ? "ACTIVE" :
                          status == AccountStatus::BLOCKED ? "BLOCKED" : "CLOSED")
        << ", creationDate=" << creationDate << "]";
    return oss.str();
}
