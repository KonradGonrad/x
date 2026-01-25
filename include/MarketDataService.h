#ifndef MARKET_DATA_SERVICE_H
#define MARKET_DATA_SERVICE_H

#include <string>
#include <map>
#include <vector>
#include <memory>
#include "Currency.h"

struct StockQuote {
    std::string ticker;
    double price;
    double change;
    double changePercent;
    std::string lastUpdate;
};

class MarketDataService {
public:
    MarketDataService();
    ~MarketDataService();

    StockQuote getStockQuote(const std::string& ticker) const;
    void updateStockQuote(const std::string& ticker, double price);
    bool hasStock(const std::string& ticker) const;
    std::vector<std::string> getAllTickers() const;

    double getExchangeRate(Currency from, Currency to) const;
    void updateExchangeRate(Currency currency, double rateToPln);
    std::map<Currency, double> getAllRates() const;

    void simulateMarketMovement();

private:
    std::map<std::string, StockQuote> stockQuotes;
    std::map<Currency, double> exchangeRates;
    void initializeDefaultData();
};

using MarketDataServicePtr = std::shared_ptr<MarketDataService>;

#endif
