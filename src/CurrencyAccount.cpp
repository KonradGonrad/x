#include "CurrencyAccount.h"
#include <sstream>

CurrencyAccount::CurrencyAccount(const std::string& iban, double initialBalance,
                                 Currency currency, const std::string& creationDate,
                                 double spread)
    : Account(iban, initialBalance, currency, creationDate),
      spread(spread) {}

CurrencyAccount::~CurrencyAccount() {}

double CurrencyAccount::getSpread() const {
    return spread;
}

void CurrencyAccount::setSpread(double spread) {
    if (spread > 0) {
        this->spread = spread;
    }
}

void CurrencyAccount::updateBalanceAfterExchange(double amount) {
    if (status == AccountStatus::ACTIVE && amount > 0) {
        double fee = amount * spread;
        balance -= fee;
    }
}

double CurrencyAccount::calculateMonthlyFees() const {
    double flatFee = 10.0;
    double percentageFee = balance * 0.001;
    return flatFee + percentageFee;
}

std::string CurrencyAccount::toString() const {
    std::ostringstream oss;
    oss << "CurrencyAccount[iban=" << iban
        << ", balance=" << balance
        << ", spread=" << (spread * 100) << "%"
        << ", status=" << (status == AccountStatus::ACTIVE ? "ACTIVE" :
                          status == AccountStatus::BLOCKED ? "BLOCKED" : "CLOSED")
        << ", creationDate=" << creationDate << "]";
    return oss.str();
}
