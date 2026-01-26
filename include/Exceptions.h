/**
 * @file Exceptions.h
 * @brief Hierarchia wyjatkow systemu bankowego
 * 
 * Zawiera klasy wyjatkow uzywane do sygnalizacji bledow w operacjach bankowych.
 */

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

/**
 * @class BankException
 * @brief Bazowa klasa wyjatkow dla systemu bankowego
 */
class BankException : public std::exception {
protected:
    std::string message;  ///< Komunikat bledu

public:
    explicit BankException(const std::string& msg) : message(msg) {}
    
    const char* what() const noexcept override {
        return message.c_str();
    }
};

/**
 * @class InsufficientFundsException
 * @brief Wyjatek rzucany przy braku wystarczajacych srodkow
 */
class InsufficientFundsException : public BankException {
private:
    double requested;  ///< Zadana kwota
    double available;  ///< Dostepna kwota

public:
    InsufficientFundsException(double requested, double available)
        : BankException("Insufficient funds: requested " + 
                       std::to_string(requested) + ", available " + 
                       std::to_string(available)),
          requested(requested), available(available) {}

    double getRequested() const { return requested; }
    double getAvailable() const { return available; }
};

/**
 * @class InvalidOperationException
 * @brief Wyjatek rzucany przy nieprawidlowej operacji
 */
class InvalidOperationException : public BankException {
public:
    explicit InvalidOperationException(const std::string& msg)
        : BankException("Nieprawidlowa operacja: " + msg) {}
};

/**
 * @class AccountBlockedException
 * @brief Wyjatek rzucany przy operacji na zablokowanym koncie
 */
class AccountBlockedException : public BankException {
private:
    std::string iban;

public:
    explicit AccountBlockedException(const std::string& iban)
        : BankException("Konto zablokowane: " + iban), iban(iban) {}
    
    std::string getIban() const { return iban; }
};

/**
 * @class ClientNotFoundException
 * @brief Wyjatek rzucany gdy nie znaleziono klienta
 */
class ClientNotFoundException : public BankException {
private:
    int clientId;

public:
    explicit ClientNotFoundException(int clientId)
        : BankException("Nie znaleziono klienta o ID: " + std::to_string(clientId)),
          clientId(clientId) {}
    
    int getClientId() const { return clientId; }
};

/**
 * @class AccountNotFoundException
 * @brief Wyjatek rzucany gdy nie znaleziono konta
 */
class AccountNotFoundException : public BankException {
private:
    std::string iban;

public:
    explicit AccountNotFoundException(const std::string& iban)
        : BankException("Nie znaleziono konta: " + iban), iban(iban) {}
    
    std::string getIban() const { return iban; }
};

#endif // EXCEPTIONS_H
