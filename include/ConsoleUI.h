/**
 * @file ConsoleUI.h
 * @brief Interfejs konsolowy systemu bankowego
 * 
 * Klasa odpowiedzialna za interakcję z użytkownikiem przez terminal.
 * Implementuje menu tekstowe i obsługę operacji bankowych.
 */

#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>

class BankService;
class Client;
class Account;
class MarketDataService;
class TransactionRepository;

/**
 * @class ConsoleUI
 * @brief Klasa interfejsu konsolowego (Console interface class)
 * 
 * Umożliwia użytkownikowi interakcję z systemem bankowym
 * przez menu tekstowe w terminalu.
 * (Enables user interaction with banking system through text menu in terminal.)
 */
class ConsoleUI {
private:
    std::vector<BankService*> banks;           ///< Lista banków (Bank list)
    MarketDataService* marketData;              ///< Serwis danych rynkowych (Market data service)
    TransactionRepository* transactionRepo;     ///< Repozytorium transakcji (Transaction repository)
    bool running;                               ///< Flaga działania programu (Running flag)

    /**
     * @brief Wyświetla separator z tytułem (Displays separator with title)
     * @param title Tytuł sekcji (Section title)
     */
    void printSeparator(const std::string& title) const;

    /**
     * @brief Wyświetla główne menu (Displays main menu)
     */
    void printMainMenu() const;

    /**
     * @brief Wyświetla menu banku (Displays bank menu)
     * @param bank Wskaźnik do banku (Pointer to bank)
     */
    void printBankMenu(BankService* bank) const;

    /**
     * @brief Wyświetla listę klientów banku (Displays bank clients list)
     * @param bank Wskaźnik do banku (Pointer to bank)
     */
    void displayClients(BankService* bank) const;

    /**
     * @brief Wyświetla konta klienta (Displays client accounts)
     * @param client Wskaźnik do klienta (Pointer to client)
     */
    void displayClientAccounts(Client* client) const;

    /**
     * @brief Pobiera wybór użytkownika (Gets user choice)
     * @param min Minimalna wartość (Minimum value)
     * @param max Maksymalna wartość (Maximum value)
     * @return Wybrana opcja (Selected option)
     */
    int getChoice(int min, int max) const;

    /**
     * @brief Pobiera kwotę od użytkownika (Gets amount from user)
     * @return Wprowadzona kwota (Entered amount)
     */
    double getAmount() const;

    /**
     * @brief Czeka na Enter (Waits for Enter)
     */
    void waitForEnter() const;

    /**
     * @brief Obsługuje operacje na koncie (Handles account operations)
     * @param account Wskaźnik do konta (Pointer to account)
     */
    void handleAccountOperations(Account* account);

    /**
     * @brief Wykonuje wpłatę (Performs deposit)
     * @param account Wskaźnik do konta (Pointer to account)
     */
    void performDeposit(Account* account);

    /**
     * @brief Wykonuje wypłatę (Performs withdrawal)
     * @param account Wskaźnik do konta (Pointer to account)
     */
    void performWithdrawal(Account* account);

    /**
     * @brief Wykonuje przelew (Performs transfer)
     * @param sourceAccount Konto źródłowe (Source account)
     */
    void performTransfer(Account* sourceAccount);

    /**
     * @brief Wyświetla kursy walut (Displays exchange rates)
     */
    void displayExchangeRates() const;

    /**
     * @brief Wyświetla ceny akcji (Displays stock prices)
     */
    void displayStockPrices() const;

public:
    /**
     * @brief Konstruktor (Constructor)
     */
    ConsoleUI();

    /**
     * @brief Destruktor (Destructor)
     */
    ~ConsoleUI();

    /**
     * @brief Dodaje bank do interfejsu (Adds bank to interface)
     * @param bank Wskaźnik do banku (Pointer to bank)
     */
    void addBank(BankService* bank);

    /**
     * @brief Ustawia serwis danych rynkowych (Sets market data service)
     * @param service Wskaźnik do serwisu (Pointer to service)
     */
    void setMarketDataService(MarketDataService* service);

    /**
     * @brief Ustawia repozytorium transakcji (Sets transaction repository)
     * @param repo Wskaźnik do repozytorium (Pointer to repository)
     */
    void setTransactionRepository(TransactionRepository* repo);

    /**
     * @brief Uruchamia interfejs konsolowy (Starts console interface)
     * 
     * Główna pętla programu z menu tekstowym.
     * (Main program loop with text menu.)
     */
    void run();
};

#endif // CONSOLEUI_H
