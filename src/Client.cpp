#include "Client.h"
#include "Account.h"
#include "Address.h"

Client::Client(int internalId, Address* address, const std::string& phoneNumber,
               const std::string& email)
    : internalId(internalId), address(address), phoneNumber(phoneNumber),
      email(email) {}

Client::~Client() {
    for (Account* acc : accounts) {
        delete acc;
    }
    accounts.clear();
    delete address;
}

int Client::getInternalId() const { return internalId; }
Address* Client::getAddress() const { return address; }
std::string Client::getPhoneNumber() const { return phoneNumber; }
std::string Client::getEmail() const { return email; }
const std::vector<Account*>& Client::getAccounts() const { return accounts; }

void Client::setPhoneNumber(const std::string& phone) { phoneNumber = phone; }
void Client::setEmail(const std::string& email) { this->email = email; }

void Client::addAccount(Account* account) {
    if (account != nullptr) {
        accounts.push_back(account);
    }
}

Account* Client::findAccount(const std::string& iban) const {
    for (Account* acc : accounts) {
        if (acc != nullptr && acc->getIban() == iban) {
            return acc;
        }
    }
    return nullptr;
}
