#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>
#include <memory>

class Address {
public:
    Address(const std::string& street, const std::string& houseNumber,
            const std::string& city, const std::string& zipCode,
            const std::string& country);
    ~Address();

    std::string getStreet() const;
    std::string getHouseNumber() const;
    std::string getCity() const;
    std::string getZipCode() const;
    std::string getCountry() const;

    void setStreet(const std::string& street);
    void setCity(const std::string& city);

    std::string toString() const;

private:
    std::string street;
    std::string houseNumber;
    std::string city;
    std::string zipCode;
    std::string country;
};

using AddressPtr = std::shared_ptr<Address>;

#endif // ADDRESS_H