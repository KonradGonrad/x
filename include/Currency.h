#ifndef CURRENCY_H
#define CURRENCY_H

#include <string>

enum class Currency { PLN, EUR, USD, GBP, CHF };

inline std::string currencyToString(Currency c) {
    switch (c) {
        case Currency::PLN: return "PLN";
        case Currency::EUR: return "EUR";
        case Currency::USD: return "USD";
        case Currency::GBP: return "GBP";
        case Currency::CHF: return "CHF";
        default: return "UNKNOWN";
    }
}
//missclick usunięte było --- IGNORE ---
inline Currency stringToCurrency(const std::string& s) {
    if (s == "PLN") return Currency::PLN;
    if (s == "EUR") return Currency::EUR;
    if (s == "USD") return Currency::USD;
    if (s == "GBP") return Currency::GBP;
    if (s == "CHF") return Currency::CHF;
    return Currency::PLN;
}

#endif
    // CURRENCY_H