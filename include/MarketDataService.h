#ifndef MARKETDATASERVICE_H
#define MARKETDATASERVICE_H

#include "Currency.h"
#include <string>
#include <map>

class MarketDataService {
private:
    std::map<Currency, double> currentRates;    // Currency -> rate
    std::map<std::string, double> stockPrices;  // Ticker -> price

public:
    MarketDataService();
    ~MarketDataService();

    // Exchange rates
    double getRate(Currency currency) const;
    void setRate(Currency currency, double rate);

    // Stock prices
    double getStockPrice(const std::string& ticker) const;
    void setStockPrice(const std::string& ticker, double price);

    // Utility
    void loadDefaultData();
    std::string toString() const;
};

#endif // MARKETDATASERVICE_H
