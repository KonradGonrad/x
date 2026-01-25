#include "Address.h"
#include <sstream>

Address::Address(const std::string& street, const std::string& houseNumber,
                 const std::string& city, const std::string& zipCode,
                 const std::string& country)
    : street(street), houseNumber(houseNumber), city(city),
      zipCode(zipCode), country(country) {}

Address::~Address() {}

std::string Address::getStreet() const { return street; }
std::string Address::getHouseNumber() const { return houseNumber; }
std::string Address::getCity() const { return city; }
std::string Address::getZipCode() const { return zipCode; }
std::string Address::getCountry() const { return country; }

void Address::setStreet(const std::string& street) { this->street = street; }
void Address::setCity(const std::string& city) { this->city = city; }

std::string Address::toString() const {
    std::ostringstream oss;
    oss << street << " " << houseNumber << ", " << zipCode << " " << city;
    return oss.str();
}
