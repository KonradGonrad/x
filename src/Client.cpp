#include "Client.h"
#include "Account.h"

#include <algorithm>

Client::Client(int internalId, Address* address, const std::string& phoneNumber,
               const std::string& email)
    : internalId(internalId), address(address), phoneNumber(phoneNumber), email(email) {}

Client::~Client() {
    for (Account* account : accounts) {
        delete account;
    }
    accounts.clear();
    delete address;
}

int Client::getInternalId() const {
    return internalId;
}

Address* Client::getAddress() const {
    return address;
}

std::string Client::getPhoneNumber() const {
    return phoneNumber;
}

std::string Client::getEmail() const {
    return email;
}

const std::vector<Account*>& Client::getAccounts() const {
    return accounts;
}

void Client::setAddress(Address* address) {
    delete this->address;
    this->address = address;
}

void Client::setPhoneNumber(const std::string& phoneNumber) {
    this->phoneNumber = phoneNumber;
}

void Client::setEmail(const std::string& email) {
    this->email = email;
}

void Client::addAccount(Account* account) {
    if (account != nullptr) {
        accounts.push_back(account);
    }
}

bool Client::removeAccount(const std::string& iban) {
    auto it = std::find_if(accounts.begin(), accounts.end(),
        [&iban](Account* acc) { return acc != nullptr && acc->getIban() == iban; });
    
    if (it != accounts.end()) {
        delete *it;
        accounts.erase(it);
        return true;
    }
    return false;
}

Account* Client::findAccount(const std::string& iban) const {
    for (Account* account : accounts) {
        if (account != nullptr && account->getIban() == iban) {
            return account;
        }
    }
    return nullptr;
}
