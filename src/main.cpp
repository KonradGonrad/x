#include <iostream>
#include "BankService.h"
#include "IndividualClient.h"
#include "CompanyClient.h"
#include "SavingsAccount.h"
#include "InvestmentAccount.h"
#include "CurrencyAccount.h"
#include "Transfer.h"
#include "Address.h"

int main() {
    std::cout << "=== System Bankowy - Wersja Rozszerzona ===" << std::endl;

    Address* bankAddress = new Address("Bankowa", "1", "Warszawa", "00-001", "Polska");
    BankService bank("MojBank", "MOJBPLPW", "1234567890", bankAddress);

    // Klient indywidualny
    Address* addr1 = new Address("Testowa", "10", "Krakow", "30-001", "Polska");
    IndividualClient* client1 = new IndividualClient(1, addr1,
        "123456789", "jan@email.pl", "Jan", "Kowalski", "90010112345");
    bank.registerClient(client1);

    // Klient firmowy
    Address* addr2 = new Address("Biznesowa", "100", "Warszawa", "00-100", "Polska");
    CompanyClient* client2 = new CompanyClient(2, addr2,
        "987654321", "firma@email.pl", "TechCorp Sp. z o.o.",
        "9876543210", "123456789", "0000123456");
    bank.registerClient(client2);

    // Tworzenie roznych typow kont
    Account* savings = bank.createAccount(client1, "Savings", 5000.0, Currency::PLN);
    Account* investment = bank.createAccount(client1, "Investment", 10000.0, Currency::PLN);
    Account* currencyAcc = bank.createAccount(client2, "Currency", 2000.0, Currency::EUR);

    std::cout << "\nBank: " << bank.toString() << std::endl;
    std::cout << "\nKlient 1: " << client1->toString() << std::endl;
    std::cout << "Klient 2: " << client2->toString() << std::endl;

    std::cout << "\nKonta klienta 1:" << std::endl;
    std::cout << "  " << savings->toString() << std::endl;
    std::cout << "  " << investment->toString() << std::endl;

    std::cout << "\nKonta klienta 2:" << std::endl;
    std::cout << "  " << currencyAcc->toString() << std::endl;

    // Operacje na koncie oszczednosciowym
    std::cout << "\n--- Operacje na koncie oszczednosciowym ---" << std::endl;
    savings->deposit(1000.0);
    std::cout << "Po wplacie 1000: " << savings->getBalance() << " PLN" << std::endl;

    // Kapitalizacja odsetek
    SavingsAccount* savingsPtr = dynamic_cast<SavingsAccount*>(savings);
    if (savingsPtr) {
        savingsPtr->capitalizeInterest();
        std::cout << "Po kapitalizacji: " << savings->getBalance() << " PLN" << std::endl;
    }

    // Operacje na koncie inwestycyjnym
    std::cout << "\n--- Operacje na koncie inwestycyjnym ---" << std::endl;
    InvestmentAccount* invPtr = dynamic_cast<InvestmentAccount*>(investment);
    if (invPtr) {
        invPtr->buyStock("AAPL", 100);
        invPtr->buyStock("GOOGL", 50);
        std::cout << "Portfolio: " << invPtr->getPortfolio().size() << " pozycji" << std::endl;
        std::cout << "Saldo po zakupach: " << investment->getBalance() << " PLN" << std::endl;
    }

    // Przelew miedzy kontami
    std::cout << "\n--- Przelew ---" << std::endl;
    Transfer transfer(1, 500.0, savings, investment);
    if (transfer.execute()) {
        std::cout << "Przelew wykonany!" << std::endl;
        std::cout << "Savings: " << savings->getBalance() << " PLN" << std::endl;
        std::cout << "Investment: " << investment->getBalance() << " PLN" << std::endl;
    }

    // Naliczanie oplat
    std::cout << "\n--- Naliczanie oplat miesiecznych ---" << std::endl;
    std::cout << "Przed: Savings=" << savings->getBalance() << std::endl;
    bank.processSession();
    std::cout << "Po: Savings=" << savings->getBalance() << std::endl;

    std::cout << "\n=== Koniec ===" << std::endl;
    return 0;
}
