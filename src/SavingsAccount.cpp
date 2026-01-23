#include "SavingsAccount.h"
#include <sstream>

SavingsAccount::SavingsAccount(const std::string& iban, double initialBalance,
                               Currency currency, const std::string& creationDate,
                               double interestRate)
    : Account(iban, initialBalance, currency, creationDate),
      interestRate(interestRate) {}

SavingsAccount::~SavingsAccount() {}

double SavingsAccount::getInterestRate() const { return interestRate; }

void SavingsAccount::setInterestRate(double rate) {
    if (rate >= 0) {
        interestRate = rate;
    }
}

void SavingsAccount::capitalizeInterest() {
    if (getStatus() == AccountStatus::ACTIVE && getBalance() > 0) {
        double interest = getBalance() * (interestRate / 12.0);
        deposit(interest);
    }
}

double SavingsAccount::calculateMonthlyFees() const {
    if (getBalance() < 1000.0) {
        return 5.0;
    }
    return 0.0;
}

std::string SavingsAccount::toString() const {
    std::ostringstream oss;
    oss << "SavingsAccount[iban=" << getIban()
        << ", balance=" << getBalance()
        << ", rate=" << (interestRate * 100) << "%]";
    return oss.str();
}
