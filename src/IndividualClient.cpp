#include "IndividualClient.h"
#include "Account.h"
#include <sstream>

IndividualClient::IndividualClient(int internalId, Address* address,
                                   const std::string& phoneNumber, const std::string& email,
                                   const std::string& firstName, const std::string& lastName,
                                   const std::string& pesel)
    : Client(internalId, address, phoneNumber, email),
      firstName(firstName), lastName(lastName), pesel(pesel) {}

IndividualClient::~IndividualClient() {}

std::string IndividualClient::getFirstName() const {
    return firstName;
}

std::string IndividualClient::getLastName() const {
    return lastName;
}

std::string IndividualClient::getPesel() const {
    return pesel;
}

void IndividualClient::setFirstName(const std::string& firstName) {
    this->firstName = firstName;
}

void IndividualClient::setLastName(const std::string& lastName) {
    this->lastName = lastName;
}

void IndividualClient::setPesel(const std::string& pesel) {
    this->pesel = pesel;
}

std::string IndividualClient::getTaxIdentifier() const {
    return pesel;
}

std::string IndividualClient::toString() const {
    std::ostringstream oss;
    oss << "IndividualClient[id=" << internalId
        << ", name=" << firstName << " " << lastName
        << ", pesel=" << pesel
        << ", email=" << email
        << ", phone=" << phoneNumber
        << ", address=" << (address ? address->toString() : "N/A")
        << ", accountsCount=" << accounts.size() << "]";
    return oss.str();
}
