#include "IndividualClient.h"
#include <sstream>

IndividualClient::IndividualClient(int internalId, AddressPtr address,
                                   const std::string& phoneNumber,
                                   const std::string& email,
                                   const std::string& firstName,
                                   const std::string& lastName,
                                   const std::string& pesel)
    : Client(internalId, address, phoneNumber, email),
      firstName(firstName), lastName(lastName), pesel(pesel) {}

IndividualClient::~IndividualClient() {}

std::string IndividualClient::getFirstName() const { return firstName; }
std::string IndividualClient::getLastName() const { return lastName; }
std::string IndividualClient::getPesel() const { return pesel; }

std::string IndividualClient::getTaxIdentifier() const { return pesel; }

std::string IndividualClient::toString() const {
    std::ostringstream oss;
    oss << "IndividualClient[id=" << internalId
        << ", name=" << firstName << " " << lastName
        << ", accounts=" << accounts.size() << "]";
    return oss.str();
}
