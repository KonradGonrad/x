/**
 * @file DataPersistence.h
 * @brief Klasa do zapisu i odczytu stanu systemu bankowego
 * 
 * Odpowiada za zapis do plikow i odczyt z plikow.
 */

#ifndef DATAPERSISTENCE_H
#define DATAPERSISTENCE_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class BankService;
class Client;
class Account;

/**
 * @class DataPersistence
 * @brief Klasa odpowiedzialna za zapis i odczyt danych do plikow
 */
class DataPersistence {
private:
    std::string dataDirectory;  ///< Sciezka do katalogu danych

public:
    /**
     * @brief Konstruktor
     * @param directory Katalog do przechowywania plikow danych
     */
    explicit DataPersistence(const std::string& directory = "data");
    
    /**
     * @brief Destruktor
     */
    ~DataPersistence();

    // Operacje zapisu
    
    /**
     * @brief Zapisuje dane banku do pliku
     * @param bank Wskaznik do serwisu bankowego
     * @param filename Nazwa pliku
     * @return true jesli zapis sie powiodl
     */
    bool saveBank(BankService* bank, const std::string& filename) const;

    /**
     * @brief Zapisuje liste klientow do pliku
     */
    bool saveClients(const std::vector<Client*>& clients, const std::string& filename) const;

    /**
     * @brief Zapisuje dane konta do pliku
     */
    bool saveAccount(Account* account, const std::string& filename) const;

    // Operacje odczytu
    
    /**
     * @brief Wczytuje dane tekstowe z pliku
     * @return Zawartosc pliku jako string
     */
    std::string loadFromFile(const std::string& filename) const;

    /**
     * @brief Sprawdza czy plik istnieje
     */
    bool fileExists(const std::string& filename) const;

    // Narzedzia pomocnicze

    /**
     * @brief Tworzy katalog danych jesli nie istnieje
     */
    bool ensureDirectoryExists() const;

    /**
     * @brief Pobiera pelna sciezke do pliku
     */
    std::string getFullPath(const std::string& filename) const;
};

#endif // DATAPERSISTENCE_H
