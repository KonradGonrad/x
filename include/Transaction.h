/**
 * @file Transaction.h
 * @brief Definicja abstrakcyjnej klasy bazowej Transaction
 * 
 * Reprezentuje transakcję bankową. Klasy pochodne implementują
 * konkretne typy transakcji: Transfer, StockOperation, CurrencyExchange.
 */

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>

class Account;  // Forward declaration

/**
 * @enum TransactionType
 * @brief Typ transakcji bankowej
 */
enum class TransactionType {
    DEPOSIT,           ///< Wpłata
    WITHDRAWAL,        ///< Wypłata
    TRANSFER,          ///< Przelew między kontami
    STOCK_PURCHASE,    ///< Zakup akcji
    CURRENCY_EXCHANGE  ///< Wymiana walut
};

/**
 * @class Transaction
 * @brief Abstrakcyjna klasa bazowa dla transakcji bankowych
 * 
 * Definiuje wspólne atrybuty i interfejs dla wszystkich typów transakcji.
 * Każda transakcja ma unikalny ID, datę, kwotę i typ.
 * 
 * @note Klasy pochodne: Transfer, StockOperation, CurrencyExchange
 */
class Transaction {
protected:
    long id;              ///< Unikalny identyfikator transakcji
    std::time_t date;     ///< Data i czas transakcji
    double amount;        ///< Kwota transakcji
    TransactionType type; ///< Typ transakcji

public:
    /**
     * @brief Konstruktor transakcji
     * @param id Unikalny identyfikator
     * @param amount Kwota transakcji
     * @param type Typ transakcji
     */
    Transaction(long id, double amount, TransactionType type);
    
    /**
     * @brief Wirtualny destruktor
     */
    virtual ~Transaction();

    // Gettery
    
    /** @brief Pobiera ID transakcji */
    long getId() const;
    
    /** @brief Pobiera datę transakcji */
    std::time_t getDate() const;
    
    /** @brief Pobiera kwotę transakcji */
    double getAmount() const;
    
    /** @brief Pobiera typ transakcji jako enum */
    TransactionType getType() const;
    
    /** @brief Pobiera typ transakcji jako string */
    std::string getTypeString() const;

    // Metody abstrakcyjne
    
    /**
     * @brief Wykonuje transakcję
     * @return true jeśli transakcja się powiodła
     * @throw BankException przy błędzie
     */
    virtual bool execute() = 0;
    
    /**
     * @brief Zwraca tekstową reprezentację transakcji
     * @return String z informacjami o transakcji
     */
    virtual std::string toString() const = 0;
};

#endif // TRANSACTION_H
