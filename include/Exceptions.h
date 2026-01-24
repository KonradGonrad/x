#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class BankException : public std::runtime_error {
public:
    explicit BankException(const std::string& message) : std::runtime_error(message) {}
};

class InsufficientFundsException : public BankException {
public:
    InsufficientFundsException(double requested, double available)
        : BankException("Insufficient funds: requested " + std::to_string(requested) +
                       ", available " + std::to_string(available)),
          requested(requested), available(available) {}
    double getRequested() const { return requested; }
    double getAvailable() const { return available; }
private:
    double requested, available;
};

class AccountNotActiveException : public BankException {
public:
    explicit AccountNotActiveException(const std::string& iban)
        : BankException("Account not active: " + iban), iban(iban) {}
    std::string getIban() const { return iban; }
private:
    std::string iban;
};

class NotFoundException : public BankException {
public:
    explicit NotFoundException(const std::string& entity) : BankException("Not found: " + entity) {}
};

class ValidationException : public BankException {
public:
    explicit ValidationException(const std::string& message) : BankException("Validation error: " + message) {}
};

class InvalidOperationException : public BankException {
public:
    explicit InvalidOperationException(const std::string& message) : BankException("Invalid operation: " + message) {}
};

class CurrencyExchangeException : public BankException {
public:
    explicit CurrencyExchangeException(const std::string& message) : BankException("Exchange error: " + message) {}
};

class MarketDataException : public BankException {
public:
    explicit MarketDataException(const std::string& message) : BankException("Market data error: " + message) {}
};

#endif
 // EXCEPTIONS_H