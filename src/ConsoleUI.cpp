/**
 * @file ConsoleUI.cpp
 * @brief Implementacja interfejsu konsolowego (Console UI implementation)
 */

#include "ConsoleUI.h"
#include "BankService.h"
#include "Client.h"
#include "IndividualClient.h"
#include "CompanyClient.h"
#include "Account.h"
#include "SavingsAccount.h"
#include "InvestmentAccount.h"
#include "CurrencyAccount.h"
#include "MarketDataService.h"
#include "TransactionRepository.h"
#include "Transfer.h"
#include "Currency.h"
#include "Exceptions.h"

ConsoleUI::ConsoleUI()
    : marketData(nullptr), transactionRepo(nullptr), running(true) {}

ConsoleUI::~ConsoleUI() {}

void ConsoleUI::addBank(BankService* bank) {
    banks.push_back(bank);
}

void ConsoleUI::setMarketDataService(MarketDataService* service) {
    marketData = service;
}

void ConsoleUI::setTransactionRepository(TransactionRepository* repo) {
    transactionRepo = repo;
}

void ConsoleUI::printSeparator(const std::string& title) const {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << std::string(60, '=') << std::endl;
}

void ConsoleUI::printMainMenu() const {
    printSeparator("SYSTEM BANKOWY - MENU GLOWNE");
    std::cout << "\n  Dostepne banki:\n";
    for (size_t i = 0; i < banks.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << banks[i]->getBankName() << std::endl;
    }
    std::cout << "\n  " << (banks.size() + 1) << ". Kursy walut\n";
    std::cout << "  " << (banks.size() + 2) << ". Ceny akcji\n";
    std::cout << "  0. Wyjscie\n";
    std::cout << "\n  Wybierz opcje: ";
}

void ConsoleUI::printBankMenu(BankService* bank) const {
    printSeparator(bank->getBankName() + " - MENU");
    std::cout << "\n  1. Lista klientow\n";
    std::cout << "  2. Informacje o banku\n";
    std::cout << "  0. Powrot\n";
    std::cout << "\n  Wybierz opcje: ";
}

void ConsoleUI::displayClients(BankService* bank) const {
    printSeparator("LISTA KLIENTOW - " + bank->getBankName());
    
    const auto& clients = bank->getClients();
    if (clients.empty()) {
        std::cout << "\n  Brak klientow.\n";
        return;
    }
    
    for (size_t i = 0; i < clients.size(); ++i) {
        std::cout << "\n  " << (i + 1) << ". " << clients[i]->toString() << std::endl;
        
        // Wyświetl konta klienta
        const auto& accounts = clients[i]->getAccounts();
        for (const auto& acc : accounts) {
            std::cout << "     -> " << acc->toString() << std::endl;
        }
    }
}

void ConsoleUI::displayClientAccounts(Client* client) const {
    std::cout << "\n  Konta klienta:\n";
    const auto& accounts = client->getAccounts();
    for (size_t i = 0; i < accounts.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << accounts[i]->toString() << std::endl;
    }
}

int ConsoleUI::getChoice(int min, int max) const {
    int choice;
    while (true) {
        if (std::cin >> choice) {
            if (choice >= min && choice <= max) {
                return choice;
            }
            std::cout << "  Nieprawidlowa opcja. Wybierz " << min << "-" << max << ": ";
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "  Nieprawidlowe dane. Sprobuj ponownie: ";
        }
    }
}

double ConsoleUI::getAmount() const {
    double amount;
    std::cout << "  Podaj kwote: ";
    while (!(std::cin >> amount) || amount <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  Nieprawidlowa kwota. Podaj liczbe dodatnia: ";
    }
    return amount;
}

void ConsoleUI::waitForEnter() const {
    std::cout << "\n  Nacisnij Enter aby kontynuowac...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void ConsoleUI::handleAccountOperations(Account* account) {
    bool inAccount = true;
    while (inAccount) {
        printSeparator("OPERACJE NA KONCIE");
        std::cout << "\n  " << account->toString() << "\n\n";
        std::cout << "  1. Wplata\n";
        std::cout << "  2. Wyplata\n";
        std::cout << "  3. Przelew\n";
        std::cout << "  0. Powrot\n";
        std::cout << "\n  Wybierz opcje: ";
        
        int choice = getChoice(0, 3);
        
        switch (choice) {
            case 1:
                performDeposit(account);
                break;
            case 2:
                performWithdrawal(account);
                break;
            case 3:
                performTransfer(account);
                break;
            case 0:
                inAccount = false;
                break;
        }
    }
}

void ConsoleUI::performDeposit(Account* account) {
    double amount = getAmount();
    try {
        account->deposit(amount);
        std::cout << "\n  [OK] Wplata " << std::fixed << std::setprecision(2) 
                  << amount << " " << currencyToString(account->getCurrency()) 
                  << " zakonczona sukcesem!\n";
        std::cout << "  Nowe saldo: " << account->getBalance() << " " 
                  << currencyToString(account->getCurrency()) << std::endl;
    } catch (const BankException& e) {
        std::cout << "\n  [FAIL] Blad: " << e.what() << std::endl;
    }
    waitForEnter();
}

void ConsoleUI::performWithdrawal(Account* account) {
    double amount = getAmount();
    try {
        account->withdraw(amount);
        std::cout << "\n  [OK] Wyplata " << std::fixed << std::setprecision(2) 
                  << amount << " " << currencyToString(account->getCurrency()) 
                  << " zakonczona sukcesem!\n";
        std::cout << "  Nowe saldo: " << account->getBalance() << " " 
                  << currencyToString(account->getCurrency()) << std::endl;
    } catch (const InsufficientFundsException& e) {
        std::cout << "\n  [FAIL] Niewystarczajace srodki: " << e.what() << std::endl;
    } catch (const BankException& e) {
        std::cout << "\n  [FAIL] Blad: " << e.what() << std::endl;
    }
    waitForEnter();
}

void ConsoleUI::performTransfer(Account* sourceAccount) {
    std::cout << "\n  Podaj IBAN konta docelowego: ";
    std::string targetIban;
    std::cin >> targetIban;
    
    // Szukaj konta docelowego we wszystkich bankach
    Account* targetAccount = nullptr;
    for (auto* bank : banks) {
        for (auto* client : bank->getClients()) {
            for (auto* acc : client->getAccounts()) {
                if (acc->getIban() == targetIban) {
                    targetAccount = acc;
                    break;
                }
            }
            if (targetAccount) break;
        }
        if (targetAccount) break;
    }
    
    if (!targetAccount) {
        std::cout << "\n  [FAIL] Nie znaleziono konta o podanym IBAN.\n";
        waitForEnter();
        return;
    }
    
    if (targetAccount == sourceAccount) {
        std::cout << "\n  [FAIL] Nie mozna przelewac na to samo konto.\n";
        waitForEnter();
        return;
    }
    
    double amount = getAmount();
    
    try {
        if (sourceAccount->getBalance() < amount) {
            throw InsufficientFundsException(amount, sourceAccount->getBalance());
        }
        
        sourceAccount->withdraw(amount);
        targetAccount->deposit(amount);
        
        std::cout << "\n  [OK] Przelew " << std::fixed << std::setprecision(2) 
                  << amount << " " << currencyToString(sourceAccount->getCurrency()) 
                  << " wykonany!\n";
        std::cout << "  Z: " << sourceAccount->getIban() << " (saldo: " 
                  << sourceAccount->getBalance() << ")\n";
        std::cout << "  Na: " << targetAccount->getIban() << " (saldo: " 
                  << targetAccount->getBalance() << ")\n";
                  
    } catch (const InsufficientFundsException& e) {
        std::cout << "\n  [FAIL] Niewystarczajace srodki: " << e.what() << std::endl;
    } catch (const BankException& e) {
        std::cout << "\n  [FAIL] Blad: " << e.what() << std::endl;
    }
    waitForEnter();
}

void ConsoleUI::displayExchangeRates() const {
    printSeparator("KURSY WALUT (NBP)");
    
    if (!marketData) {
        std::cout << "\n  Brak danych rynkowych.\n";
        return;
    }
    
    std::cout << "\n  Waluta   |   Kurs (PLN)\n";
    std::cout << "  " << std::string(25, '-') << std::endl;
    
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "  EUR      |   " << marketData->getRate(Currency::EUR) << std::endl;
    std::cout << "  USD      |   " << marketData->getRate(Currency::USD) << std::endl;
    std::cout << "  GBP      |   " << marketData->getRate(Currency::GBP) << std::endl;
    std::cout << "  CHF      |   " << marketData->getRate(Currency::CHF) << std::endl;
}

void ConsoleUI::displayStockPrices() const {
    printSeparator("CENY AKCJI");
    
    if (!marketData) {
        std::cout << "\n  Brak danych rynkowych.\n";
        return;
    }
    
    std::cout << "\n  Ticker   |   Cena (USD)\n";
    std::cout << "  " << std::string(25, '-') << std::endl;
    
    std::vector<std::string> tickers = {"AAPL", "GOOGL", "MSFT", "TSLA", "AMZN"};
    std::cout << std::fixed << std::setprecision(2);
    for (const auto& ticker : tickers) {
        double price = marketData->getStockPrice(ticker);
        if (price > 0) {
            std::cout << "  " << std::left << std::setw(8) << ticker 
                      << " |   " << price << std::endl;
        }
    }
}

void ConsoleUI::run() {
    std::cout << "\n+============================================================+\n";
    std::cout << "|         SYSTEM BANKOWY - INTERFEJS KONSOLOWY              |\n";
    std::cout << "|              (Console User Interface)                      |\n";
    std::cout << "+============================================================+\n";
    
    while (running) {
        printMainMenu();
        
        int maxOption = static_cast<int>(banks.size()) + 2;
        int choice = getChoice(0, maxOption);
        
        if (choice == 0) {
            running = false;
            std::cout << "\n  Do widzenia!\n\n";
        } else if (choice <= static_cast<int>(banks.size())) {
            // Wybrano bank
            BankService* selectedBank = banks[choice - 1];
            bool inBank = true;
            
            while (inBank) {
                printBankMenu(selectedBank);
                int bankChoice = getChoice(0, 2);
                
                switch (bankChoice) {
                    case 1: {
                        displayClients(selectedBank);
                        
                        const auto& clients = selectedBank->getClients();
                        if (!clients.empty()) {
                            std::cout << "\n  Wybierz klienta (0 = powrot): ";
                            int clientChoice = getChoice(0, static_cast<int>(clients.size()));
                            
                            if (clientChoice > 0) {
                                Client* selectedClient = clients[clientChoice - 1];
                                displayClientAccounts(selectedClient);
                                
                                const auto& accounts = selectedClient->getAccounts();
                                if (!accounts.empty()) {
                                    std::cout << "\n  Wybierz konto (0 = powrot): ";
                                    int accChoice = getChoice(0, static_cast<int>(accounts.size()));
                                    
                                    if (accChoice > 0) {
                                        handleAccountOperations(accounts[accChoice - 1]);
                                    }
                                }
                            }
                        }
                        break;
                    }
                    case 2:
                        printSeparator("INFORMACJE O BANKU");
                        std::cout << "\n  " << selectedBank->toString() << std::endl;
                        std::cout << "  Liczba klientow: " << selectedBank->getClients().size() << std::endl;
                        waitForEnter();
                        break;
                    case 0:
                        inBank = false;
                        break;
                }
            }
        } else if (choice == static_cast<int>(banks.size()) + 1) {
            displayExchangeRates();
            waitForEnter();
        } else if (choice == static_cast<int>(banks.size()) + 2) {
            displayStockPrices();
            waitForEnter();
        }
    }
}
