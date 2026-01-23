#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

class Address {
private:
    std::string street;
    std::string houseNumber;
    std::string city;
    std::string zipCode;
    std::string country;

public:
    Address(const std::string& street, const std::string& houseNumber,
            const std::string& city, const std::string& zipCode,
            const std::string& country);
    ~Address();

    std::string toString() const;
};

#endif // ADDRESS_H