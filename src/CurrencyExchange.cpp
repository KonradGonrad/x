#include "CurrencyExchange.h"
#include "Exceptions.h"
#include <sstream>

std::map<std::pair<Currency, Currency>, double> CurrencyExchange::defaultRates = {
    {{Currency::PLN, Currency::EUR}, 0.22},
    {{Currency::PLN, Currency::USD}, 0.24},
    {{Currency::PLN, Currency::GBP}, 0.19},
    {{Currency::PLN, Currency::CHF}, 0.22},
    {{Currency::EUR, Currency::PLN}, 4.50},
    {{Currency::USD, Currency::PLN}, 4.15},
    {{Currency::GBP, Currency::PLN}, 5.25},
    {{Currency::CHF, Currency::PLN}, 4.55},
    {{Currency::EUR, Currency::USD}, 1.08},
    {{Currency::USD, Currency::EUR}, 0.93}
};

CurrencyExchange::CurrencyExchange(long id, CurrencyAccountPtr sourceAccount,
                                   CurrencyAccountPtr targetAccount,
                                   double sourceAmount, double exchangeRate)
    : Transaction(id, sourceAmount, TransactionType::CURRENCY_EXCHANGE),
      sourceAccount(sourceAccount), targetAccount(targetAccount),
      sourceAmount(sourceAmount), exchangeRate(exchangeRate) {}

CurrencyExchange::~CurrencyExchange() {}

CurrencyAccountPtr CurrencyExchange::getSourceAccount() const { return sourceAccount; }
CurrencyAccountPtr CurrencyExchange::getTargetAccount() const { return targetAccount; }
double CurrencyExchange::getSourceAmount() const { return sourceAmount; }
double CurrencyExchange::getTargetAmount() const { return sourceAmount * exchangeRate; }
double CurrencyExchange::getExchangeRate() const { return exchangeRate; }

double CurrencyExchange::getDefaultRate(Currency from, Currency to) {
    if (from == to) return 1.0;
    auto it = defaultRates.find({from, to});
    if (it != defaultRates.end()) return it->second;
    throw CurrencyExchangeException("No exchange rate available for pair");
}

void CurrencyExchange::execute() {
    if (!sourceAccount) throw ValidationException("Source account is null");
    if (!targetAccount) throw ValidationException("Target account is null");
    
    if (sourceAccount->getBalance() < sourceAmount) {
        throw InsufficientFundsException(sourceAmount, sourceAccount->getBalance());
    }
    
    double targetAmount = sourceAmount * exchangeRate;
    
    sourceAccount->withdraw(sourceAmount);
    targetAccount->deposit(targetAmount);
    
    // Apply spread fees
    sourceAccount->updateBalanceAfterExchange(sourceAmount);
}

std::string CurrencyExchange::toString() const {
    std::ostringstream oss;
    oss << "CurrencyExchange[id=" << id
        << ", " << sourceAmount << " " << currencyToString(sourceAccount->getCurrency())
        << " -> " << getTargetAmount() << " " << currencyToString(targetAccount->getCurrency())
        << ", rate=" << exchangeRate << "]";
    return oss.str();
}
