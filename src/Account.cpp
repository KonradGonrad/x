#include "Account.h"

Account::Account(const std::string& iban, double initialBalance,
                 Currency currency, const std::string& creationDate)
    : iban(iban), balance(initialBalance), currency(currency),
      status(AccountStatus::ACTIVE), creationDate(creationDate) {}

Account::~Account() {}

std::string Account::getIban() const { return iban; }
double Account::getBalance() const { return balance; }
Currency Account::getCurrency() const { return currency; }
AccountStatus Account::getStatus() const { return status; }
std::string Account::getCreationDate() const { return creationDate; }

void Account::setStatus(AccountStatus status) { this->status = status; }

void Account::deposit(double amount) {
    if (status == AccountStatus::ACTIVE && amount > 0) {
        balance += amount;
    }
}

void Account::withdraw(double amount) {
    if (status == AccountStatus::ACTIVE && amount > 0 && amount <= balance) {
        balance -= amount;
    }
}
