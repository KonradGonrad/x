#include "Client.h"
#include "Exceptions.h"

Client::Client(int internalId, AddressPtr address, const std::string& phoneNumber,
               const std::string& email)
    : internalId(internalId), address(address), phoneNumber(phoneNumber),
      email(email) {}

Client::~Client() {}

int Client::getInternalId() const { return internalId; }
AddressPtr Client::getAddress() const { return address; }
std::string Client::getPhoneNumber() const { return phoneNumber; }
std::string Client::getEmail() const { return email; }
const std::vector<AccountPtr>& Client::getAccounts() const { return accounts; }

void Client::setPhoneNumber(const std::string& phone) { phoneNumber = phone; }
void Client::setEmail(const std::string& email) { this->email = email; }

void Client::addAccount(AccountPtr account) {
    if (!account) throw ValidationException("Cannot add null account");
    accounts.push_back(account);
}

AccountPtr Client::findAccount(const std::string& iban) const {
    for (const auto& acc : accounts) {
        if (acc && acc->getIban() == iban) return acc;
    }
    throw NotFoundException("Account with IBAN: " + iban);
}
