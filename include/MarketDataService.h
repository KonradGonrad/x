#ifndef MARKET_DATA_SERVICE_H
#define MARKET_DATA_SERVICE_H

#include <string>
#include <map>
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

    // Stock quotes
    StockQuote getStockQuote(const std::string& ticker) const;
    void updateStockQuote(const std::string& ticker, double price);
    bool hasStock(const std::string& ticker) const;
    std::vector<std::string> getAllTickers() const;

    // Currency rates (PLN base)
    double getExchangeRate(Currency from, Currency to) const;
    void updateExchangeRate(Currency currency, double rateToPlN);
    std::map<Currency, double> getAllRates() const;

    // Simulated market data
    void simulateMarketMovement();

private:
    std::map<std::string, StockQuote> stockQuotes;
    std::map<Currency, double> exchangeRates; // Rate to PLN
    
    void initializeDefaultData();
};

using MarketDataServicePtr = std::shared_ptr<MarketDataService>;

#endif // MARKET_DATA_SERVICE_H