#ifndef CURRENCY_H
#define CURRENCY_H

#include <string>
#include <ostream>

/**
 * @enum Currency
 * @brief Enumeration of supported currencies in the banking system
 */
enum class Currency {
    PLN,
    USD,
    EUR,
    GBP,
    CHF
};

/**
 * @brief Convert Currency enum to string representation
 * @param currency The currency to convert
 * @return String representation of the currency (e.g., "PLN", "USD")
 */
inline std::string currencyToString(Currency currency) {
    switch (currency) {
        case Currency::PLN: return "PLN";
        case Currency::USD: return "USD";
        case Currency::EUR: return "EUR";
        case Currency::GBP: return "GBP";
        case Currency::CHF: return "CHF";
        default: return "UNKNOWN";
    }
}

/**
 * @brief Convert string to Currency enum
 * @param str The string to convert
 * @return Currency enum value
 */
inline Currency stringToCurrency(const std::string& str) {
    if (str == "PLN") return Currency::PLN;
    if (str == "USD") return Currency::USD;
    if (str == "EUR") return Currency::EUR;
    if (str == "GBP") return Currency::GBP;
    if (str == "CHF") return Currency::CHF;
    return Currency::PLN; // Default
}

/**
 * @brief Operator wyjścia dla Currency
 * @param os Strumień wyjściowy
 * @param currency Waluta
 * @return Referencja do strumienia
 */
inline std::ostream& operator<<(std::ostream& os, Currency currency) {
    os << currencyToString(currency);
    return os;
}

#endif // CURRENCY_H