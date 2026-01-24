/**
 * @file Address.h
 * @brief Klasa reprezentująca adres
 */

#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>
#include <ostream>

/**
 * @class Address
 * @brief Reprezentuje adres pocztowy
 */
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

    // Getters
    std::string getStreet() const;
    std::string getHouseNumber() const;
    std::string getCity() const;
    std::string getZipCode() const;
    std::string getCountry() const;

    // Setters
    void setStreet(const std::string& street);
    void setHouseNumber(const std::string& houseNumber);
    void setCity(const std::string& city);
    void setZipCode(const std::string& zipCode);
    void setCountry(const std::string& country);

    std::string toString() const;

    // Operatory porównania
    bool operator==(const Address& other) const;
    bool operator!=(const Address& other) const;
};

// Operator wyjścia do strumienia
std::ostream& operator<<(std::ostream& os, const Address& addr);

#endif // ADDRESS_H
