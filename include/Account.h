/**
 * @file Account.h
 * @brief Definicja bazowej klasy konta bankowego
 * 
 * Plik zawiera abstrakcyjną klasę bazową Account oraz enum AccountStatus.
 * Klasa Account jest bazą dla wszystkich typów kont w systemie.
 */

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "Currency.h"

/**
 * @enum AccountStatus
 * @brief Status konta bankowego
 */
enum class AccountStatus {
    ACTIVE,   ///< Konto aktywne - można wykonywać operacje
    BLOCKED,  ///< Konto zablokowane - operacje niedozwolone
    CLOSED    ///< Konto zamknięte
};


/**
 * @class Account
 * @brief Abstrakcyjna klasa bazowa reprezentująca konto bankowe
 * 
 * Klasa definiuje podstawowe atrybuty i operacje dla wszystkich typów kont.
 * Jest klasą abstrakcyjną - nie można tworzyć jej instancji bezpośrednio.
 * 
 * @note Klasy pochodne: SavingsAccount, InvestmentAccount, CurrencyAccount
 */
class Account {
protected:
    std::string iban;        ///< Numer IBAN konta
    double balance;          ///< Saldo konta
    Currency currency;       ///< Waluta konta
    AccountStatus status;    ///< Status konta
    std::string creationDate;///< Data utworzenia konta

public:
    /**
     * @brief Konstruktor konta
     * @param iban Numer IBAN (unikalny identyfikator)
     * @param initialBalance Początkowe saldo
     * @param currency Waluta konta
     * @param creationDate Data utworzenia (format: YYYY-MM-DD)
     */
    Account(const std::string& iban, double initialBalance,
            Currency currency, const std::string& creationDate);
    
    /**
     * @brief Wirtualny destruktor
     */
    virtual ~Account();

    // Gettery
    
    /** @brief Pobiera numer IBAN konta */
    std::string getIban() const;
    
    /** @brief Pobiera aktualne saldo */
    double getBalance() const;
    
    /** @brief Pobiera walutę konta */
    Currency getCurrency() const;
    
    /** @brief Pobiera status konta */
    AccountStatus getStatus() const;
    
    /** @brief Pobiera datę utworzenia */
    std::string getCreationDate() const;

    // Settery
    
    /** 
     * @brief Ustawia status konta 
     * @param status Nowy status
     */
    void setStatus(AccountStatus status);

    // Operacje
    
    /**
     * @brief Wpłata na konto
     * @param amount Kwota do wpłaty (musi być > 0)
     * @throw AccountBlockedException gdy konto jest zablokowane
     * @throw InvalidOperationException gdy kwota <= 0
     */
    virtual void deposit(double amount);
    
    /**
     * @brief Wypłata z konta
     * @param amount Kwota do wypłaty (musi być > 0 i <= saldo)
     * @throw AccountBlockedException gdy konto jest zablokowane
     * @throw InvalidOperationException gdy kwota <= 0
     * @throw InsufficientFundsException gdy brak środków
     */
    virtual void withdraw(double amount);

    // Metody abstrakcyjne (pure virtual)
    
    /**
     * @brief Oblicza miesięczne opłaty za prowadzenie konta
     * @return Kwota opłat
     */
    virtual double calculateMonthlyFees() const = 0;
    
    /**
     * @brief Zwraca tekstową reprezentację konta
     * @return String z informacjami o koncie
     */
    virtual std::string toString() const = 0;
};

#endif // ACCOUNT_H
