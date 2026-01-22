#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

class Address {
private:
    std::string street;
    std::string city;
    std::string postalCode;
    std::string country;

public:
    Address(const std::string& street, const std::string& city,
            const std::string& postalCode, const std::string& country);
    ~Address();

    std::string toString() const;
};

#endif // ADDRESS_H