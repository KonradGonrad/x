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

#endif
