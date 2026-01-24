#include <iostream>
#include <memory>
#include "BankService.h"
#include "IndividualClient.h"
#include "CompanyClient.h"
#include "SavingsAccount.h"
#include "Transfer.h"
#include "Exceptions.h"

int main() {
    std::cout << "=== System Bankowy - Smart Pointery (v3) ===" << std::endl;

    try {
        auto bankAddress = std::make_shared<Address>("Bankowa", "1", "Warszawa", "00-001", "Polska");
        BankService bank("MojBank", "MOJBPLPW", "1234567890", bankAddress);

        // Tworzenie klientow z make_shared
        auto addr1 = std::make_shared<Address>("Testowa", "10", "Krakow", "30-001", "Polska");
        auto client1 = std::make_shared<IndividualClient>(1, addr1,
            "123456789", "jan@email.pl", "Jan", "Kowalski", "90010112345");
        bank.registerClient(client1);

        auto addr2 = std::make_shared<Address>("Biznesowa", "100", "Warszawa", "00-100", "Polska");
        auto client2 = std::make_shared<CompanyClient>(2, addr2,
            "987654321", "firma@email.pl", "TechCorp", "9876543210", "123456789", "0000123456");
        bank.registerClient(client2);

        // Tworzenie kont - zwracane jako shared_ptr
        auto savings = bank.createAccount(client1, "Savings", 5000.0, Currency::PLN);
        auto investment = bank.createAccount(client1, "Investment", 10000.0, Currency::PLN);
        auto currency = bank.createAccount(client2, "Currency", 2000.0, Currency::EUR);

        std::cout << "\nBank: " << bank.toString() << std::endl;
        std::cout << "Klient 1: " << client1->toString() << std::endl;
        std::cout << "Klient 2: " << client2->toString() << std::endl;

        // Operacje
        savings->deposit(1000.0);
        std::cout << "\nPo wplacie: " << savings->getBalance() << " PLN" << std::endl;

        // Przelew z shared_ptr
        auto transfer = std::make_shared<Transfer>(1, 500.0, savings, investment);
        transfer->execute();
        std::cout << "Po przelewie - Savings: " << savings->getBalance() << " PLN" << std::endl;

        // Repository - wyszukiwanie
        std::cout << "\n--- Test Repository ---" << std::endl;
        auto found = bank.getClientRepository().findById(1);
        if (found) {
            std::cout << "Znaleziono: " << found->toString() << std::endl;
        }

        // Filtrowanie
        auto filtered = bank.getClientRepository().filter([](const ClientPtr& c) {
            return c->getAccounts().size() > 1;
        });
        std::cout << "Klienci z >1 kontem: " << filtered.size() << std::endl;

        // use_count demo
        std::cout << "\n--- Smart Pointer use_count ---" << std::endl;
        std::cout << "savings use_count: " << savings.use_count() << std::endl;
        std::cout << "client1 use_count: " << client1.use_count() << std::endl;

        std::cout << "\n=== Koniec (destruktory wywolane automatycznie) ===" << std::endl;

    } catch (const BankException& e) {
        std::cerr << "Blad: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
