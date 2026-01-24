#include "CurrencyAccount.h"
#include "Exceptions.h"
#include <sstream>

CurrencyAccount::CurrencyAccount(const std::string& iban, double initialBalance,
                                 Currency currency, const std::string& creationDate,
                                 double spread)
    : Account(iban, initialBalance, currency, creationDate), spread(spread) {}

CurrencyAccount::~CurrencyAccount() {}

double CurrencyAccount::getSpread() const { return spread; }

void CurrencyAccount::setSpread(double spread) {
    if (spread <= 0) throw ValidationException("Spread must be positive");
    this->spread = spread;
}

void CurrencyAccount::updateBalanceAfterExchange(double amount) {
    if (status != AccountStatus::ACTIVE) throw AccountNotActiveException(iban);
    if (amount <= 0) throw ValidationException("Exchange amount must be positive");
    double fee = amount * spread;
    if (fee > balance) throw InsufficientFundsException(fee, balance);
    balance -= fee;
}

double CurrencyAccount::calculateMonthlyFees() const {
    return 10.0 + balance * 0.001;
}

std::string CurrencyAccount::toString() const {
    std::ostringstream oss;
    oss << "CurrencyAccount[iban=" << iban << ", balance=" << balance
        << ", currency=" << currencyToString(currency) << "]";
    return oss.str();
}
