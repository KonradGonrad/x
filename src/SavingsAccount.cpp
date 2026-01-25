#include "SavingsAccount.h"
#include "Exceptions.h"
#include <sstream>

SavingsAccount::SavingsAccount(const std::string& iban, double initialBalance,
                               Currency currency, const std::string& creationDate,
                               double interestRate)
    : Account(iban, initialBalance, currency, creationDate),
      interestRate(interestRate) {}

SavingsAccount::~SavingsAccount() {}

double SavingsAccount::getInterestRate() const { return interestRate; }

void SavingsAccount::setInterestRate(double rate) {
    if (rate < 0) throw ValidationException("Interest rate cannot be negative");
    interestRate = rate;
}

void SavingsAccount::capitalizeInterest() {
    if (status != AccountStatus::ACTIVE) throw AccountNotActiveException(iban);
    if (balance > 0) balance += balance * (interestRate / 12.0);
}

double SavingsAccount::calculateMonthlyFees() const {
    return (balance < 1000.0) ? 5.0 : 0.0;
}

std::string SavingsAccount::toString() const {
    std::ostringstream oss;
    oss << "SavingsAccount[iban=" << iban << ", balance=" << balance
        << ", rate=" << (interestRate * 100) << "%]";
    return oss.str();
}
