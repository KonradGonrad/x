#ifndef MARKETDATASERVICE_H
#define MARKETDATASERVICE_H

#include "Currency.h"
#include <string>
#include <map>

class MarketDataService {
private:
    std::map<Currency, double> currentRates;
    std::map<std::string, double> stockPrices;

public:
    MarketDataService();
    ~MarketDataService();

    // Core methods from UML
    double getRate(Currency c) const;
    double getStockPrice(const std::string& ticker) const;
};

#endif // MARKETDATASERVICE_H