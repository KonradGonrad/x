#include "MarketDataService.h"
#include "Exceptions.h"
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iomanip>

MarketDataService::MarketDataService() {
    initializeDefaultData();
}

MarketDataService::~MarketDataService() {}

void MarketDataService::initializeDefaultData() {
    // Default stock quotes
    stockQuotes["AAPL"] = {"AAPL", 175.50, 2.30, 1.33, "2026-01-28"};
    stockQuotes["GOOGL"] = {"GOOGL", 140.25, -1.15, -0.81, "2026-01-28"};
    stockQuotes["MSFT"] = {"MSFT", 378.90, 4.50, 1.20, "2026-01-28"};
    stockQuotes["AMZN"] = {"AMZN", 185.60, 3.20, 1.75, "2026-01-28"};
    stockQuotes["CDR"] = {"CDR", 125.40, -2.80, -2.18, "2026-01-28"};
    stockQuotes["PKO"] = {"PKO", 52.35, 0.85, 1.65, "2026-01-28"};
    
    // Default exchange rates (to PLN)
    exchangeRates[Currency::PLN] = 1.0;
    exchangeRates[Currency::EUR] = 4.32;
    exchangeRates[Currency::USD] = 3.98;
    exchangeRates[Currency::GBP] = 5.05;
    exchangeRates[Currency::CHF] = 4.48;
}

StockQuote MarketDataService::getStockQuote(const std::string& ticker) const {
    auto it = stockQuotes.find(ticker);
    if (it == stockQuotes.end()) {
        throw MarketDataException("Stock not found: " + ticker);
    }
    return it->second;
}

void MarketDataService::updateStockQuote(const std::string& ticker, double price) {
    auto it = stockQuotes.find(ticker);
    if (it != stockQuotes.end()) {
        double oldPrice = it->second.price;
        it->second.change = price - oldPrice;
        it->second.changePercent = (it->second.change / oldPrice) * 100;
        it->second.price = price;
    } else {
        stockQuotes[ticker] = {ticker, price, 0, 0, "2026-01-28"};
    }
}

bool MarketDataService::hasStock(const std::string& ticker) const {
    return stockQuotes.find(ticker) != stockQuotes.end();
}

std::vector<std::string> MarketDataService::getAllTickers() const {
    std::vector<std::string> tickers;
    for (const auto& pair : stockQuotes) {
        tickers.push_back(pair.first);
    }
    return tickers;
}

double MarketDataService::getExchangeRate(Currency from, Currency to) const {
    if (from == to) return 1.0;
    
    auto fromIt = exchangeRates.find(from);
    auto toIt = exchangeRates.find(to);
    
    if (fromIt == exchangeRates.end() || toIt == exchangeRates.end()) {
        throw MarketDataException("Exchange rate not available");
    }
    
    // Convert via PLN
    return fromIt->second / toIt->second;
}

void MarketDataService::updateExchangeRate(Currency currency, double rateToPln) {
    if (rateToPln <= 0) {
        throw ValidationException("Exchange rate must be positive");
    }
    exchangeRates[currency] = rateToPln;
}

std::map<Currency, double> MarketDataService::getAllRates() const {
    return exchangeRates;
}

void MarketDataService::simulateMarketMovement() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    
    for (auto& pair : stockQuotes) {
        double changePercent = ((std::rand() % 1000) - 500) / 10000.0; // -5% to +5%
        double newPrice = pair.second.price * (1 + changePercent);
        updateStockQuote(pair.first, newPrice);
    }
    
    for (auto& pair : exchangeRates) {
        if (pair.first != Currency::PLN) {
            double changePercent = ((std::rand() % 200) - 100) / 10000.0; // -1% to +1%
            pair.second *= (1 + changePercent);
        }
    }
}
