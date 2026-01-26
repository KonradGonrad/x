#include "MarketDataService.h"
#include <sstream>

MarketDataService::MarketDataService() {
    loadDefaultData();
}

MarketDataService::~MarketDataService() {}

double MarketDataService::getRate(Currency currency) const {
    auto it = currentRates.find(currency);
    if (it != currentRates.end()) {
        return it->second;
    }
    return 0.0;
}

void MarketDataService::setRate(Currency currency, double rate) {
    if (rate > 0) {
        currentRates[currency] = rate;
    }
}

double MarketDataService::getStockPrice(const std::string& ticker) const {
    auto it = stockPrices.find(ticker);
    if (it != stockPrices.end()) {
        return it->second;
    }
    return 0.0;
}

void MarketDataService::setStockPrice(const std::string& ticker, double price) {
    if (price > 0) {
        stockPrices[ticker] = price;
    }
}

void MarketDataService::loadDefaultData() {
    setRate(Currency::PLN, 1.0);
    setRate(Currency::EUR, 4.55);
    setRate(Currency::USD, 4.17);
    setRate(Currency::GBP, 5.26);
    setRate(Currency::CHF, 4.76);

    setStockPrice("AAPL", 178.50);
    setStockPrice("GOOGL", 141.25);
    setStockPrice("MSFT", 378.90);
    setStockPrice("AMZN", 178.75);
    setStockPrice("CDR", 125.60);
    setStockPrice("PKO", 45.30);
    setStockPrice("PKN", 98.75);
}

std::string MarketDataService::toString() const {
    std::ostringstream oss;
    oss << "MarketDataService[\n";
    oss << "  ExchangeRates:\n";
    for (const auto& pair : currentRates) {
        std::string currencyStr;
        switch (pair.first) {
            case Currency::PLN: currencyStr = "PLN"; break;
            case Currency::EUR: currencyStr = "EUR"; break;
            case Currency::USD: currencyStr = "USD"; break;
            case Currency::GBP: currencyStr = "GBP"; break;
            case Currency::CHF: currencyStr = "CHF"; break;
        }
        oss << "    " << currencyStr << " = " << pair.second << "\n";
    }
    oss << "  StockPrices:\n";
    for (const auto& pair : stockPrices) {
        oss << "    " << pair.first << " = " << pair.second << "\n";
    }
    oss << "]";
    return oss.str();
}
