/**
 * @file BankService.h
 * @brief Główna klasa serwisu bankowego
 * 
 * Zarządza klientami i kontami w banku.
 */

#ifndef BANKSERVICE_H
#define BANKSERVICE_H

#include <vector>
#include <string>
#include "Currency.h"

class Client;
class Account;
class Address;

/**
 * @typedef ClientList
 * @brief Alias dla listy klientów
 */
typedef std::vector<Client*> ClientList;

/**
 * @class BankService
 * @brief Główna klasa zarządzająca bankiem
 * 
 * Odpowiada za rejestrację klientów, tworzenie kont i przetwarzanie sesji.
 */
class BankService {
private:
    std::string bankName;    ///< Nazwa banku
    std::string bankSwift;   ///< Kod SWIFT
    std::string bankNip;     ///< NIP banku
    Address* headOffice;     ///< Adres siedziby głównej
    ClientList clients;      ///< Lista klientów banku

public:
    /**
     * @brief Konstruktor
     * @param bankName Nazwa banku
     * @param bankSwift Kod SWIFT
     * @param bankNip NIP banku
     * @param headOffice Adres siedziby (przejmuje własność)
     */
    BankService(const std::string& bankName, const std::string& bankSwift,
                const std::string& bankNip, Address* headOffice);
    
    /**
     * @brief Destruktor - zwalnia pamięć klientów i adresu
     */
    ~BankService();

    // Gettery
    std::string getBankName() const;
    std::string getBankSwift() const;
    std::string getBankNip() const;
    Address* getHeadOffice() const;
    const ClientList& getClients() const;

    /**
     * @brief Rejestruje nowego klienta w banku
     * @param client Wskaźnik do klienta (przejmuje własność)
     */
    void registerClient(Client* client);

    /**
     * @brief Tworzy nowe konto dla klienta
     * @param client Klient dla którego tworzone jest konto
     * @param accountType Typ konta: "Savings", "Investment", "Currency"
     * @param initialBalance Początkowe saldo
     * @param currency Waluta konta
     * @return Wskaźnik do utworzonego konta lub nullptr
     */
    Account* createAccount(Client* client, const std::string& accountType,
                          double initialBalance, Currency currency);

    /**
     * @brief Przetwarza miesięczną sesję - nalicza opłaty
     */
    void processSession();

    /**
     * @brief Zwraca reprezentację tekstową banku
     */
    std::string toString() const;
};

#endif // BANKSERVICE_H
