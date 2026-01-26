#include "SavingsAccount.h"
#include <sstream>

SavingsAccount::SavingsAccount(const std::string& iban, double initialBalance,
                               Currency currency, const std::string& creationDate,
                               double interestRate)
    : Account(iban, initialBalance, currency, creationDate),
      interestRate(interestRate) {}

SavingsAccount::~SavingsAccount() {}

double SavingsAccount::getInterestRate() const {
    return interestRate;
}

void SavingsAccount::setInterestRate(double interestRate) {
    this->interestRate = interestRate;
}

void SavingsAccount::capitalizeInterest() {
    if (status == AccountStatus::ACTIVE && balance > 0) {
        double interest = balance * (interestRate / 12.0);
        balance += interest;
    }
}

double SavingsAccount::calculateMonthlyFees() const {
    if (balance < 1000.0) {
        return 5.0;
    }
    return 0.0;
}

std::string SavingsAccount::toString() const {
    std::ostringstream oss;
    oss << "SavingsAccount[iban=" << iban
        << ", balance=" << balance
        << ", interestRate=" << (interestRate * 100) << "%"
        << ", status=" << (status == AccountStatus::ACTIVE ? "ACTIVE" :
                          status == AccountStatus::BLOCKED ? "BLOCKED" : "CLOSED")
        << ", creationDate=" << creationDate << "]";
    return oss.str();
}
