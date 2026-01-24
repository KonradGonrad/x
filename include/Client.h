/**
 * @file Client.h
 * @brief Definicja abstrakcyjnej klasy bazowej Client
 * 
 * Klasa Client reprezentuje klienta banku. Jest klasą abstrakcyjną
 * z której dziedziczą IndividualClient i CompanyClient.
 */

#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include "Address.h"

class Account;  // Forward declaration

/**
 * @class Client
 * @brief Abstrakcyjna klasa bazowa reprezentująca klienta banku
 * 
 * Przechowuje podstawowe dane klienta oraz listę jego kont.
 * Klient może mieć wiele kont różnych typów.
 * 
 * @note Klasy pochodne: IndividualClient, CompanyClient
 */
class Client {
protected:
    int internalId;                    ///< Wewnętrzny identyfikator klienta
    Address* address;                  ///< Adres klienta (wskaźnik)
    std::string phoneNumber;           ///< Numer telefonu
    std::string email;                 ///< Adres email
    std::vector<Account*> accounts;    ///< Lista kont klienta

public:
    /**
     * @brief Konstruktor klienta
     * @param internalId Unikalny identyfikator
     * @param address Wskaźnik do adresu (przejmuje własność)
     * @param phoneNumber Numer telefonu
     * @param email Adres email
     */
    Client(int internalId, Address* address, const std::string& phoneNumber,
           const std::string& email);
    
    /**
     * @brief Wirtualny destruktor - zwalnia pamięć adresu i kont
     */
    virtual ~Client();

    // Gettery
    
    /** @brief Pobiera wewnętrzny ID klienta */
    int getInternalId() const;
    
    /** @brief Pobiera wskaźnik do adresu */
    Address* getAddress() const;
    
    /** @brief Pobiera numer telefonu */
    std::string getPhoneNumber() const;
    
    /** @brief Pobiera adres email */
    std::string getEmail() const;
    
    /** @brief Pobiera referencję do listy kont */
    const std::vector<Account*>& getAccounts() const;

    // Settery
    
    /** @brief Ustawia nowy adres (zwalnia poprzedni) */
    void setAddress(Address* address);
    
    /** @brief Ustawia numer telefonu */
    void setPhoneNumber(const std::string& phoneNumber);
    
    /** @brief Ustawia adres email */
    void setEmail(const std::string& email);

    // Zarządzanie kontami
    
    /**
     * @brief Dodaje konto do listy kont klienta
     * @param account Wskaźnik do konta (przejmuje własność)
     */
    void addAccount(Account* account);
    
    /**
     * @brief Usuwa konto o podanym IBAN
     * @param iban Numer IBAN konta do usunięcia
     * @return true jeśli konto zostało usunięte
     */
    bool removeAccount(const std::string& iban);
    
    /**
     * @brief Wyszukuje konto po numerze IBAN
     * @param iban Numer IBAN
     * @return Wskaźnik do konta lub nullptr
     */
    Account* findAccount(const std::string& iban) const;

    // Metody abstrakcyjne
    
    /**
     * @brief Pobiera identyfikator podatkowy klienta
     * @return PESEL dla osób fizycznych, NIP dla firm
     */
    virtual std::string getTaxIdentifier() const = 0;
    
    /**
     * @brief Zwraca tekstową reprezentację klienta
     * @return String z informacjami o kliencie
     */
    virtual std::string toString() const = 0;
};

#endif // CLIENT_H
