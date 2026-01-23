#include <iostream>
#include "BankService.h"
#include "IndividualClient.h"
#include "SavingsAccount.h"
#include "Transfer.h"
#include "Address.h"

int main() {
    std::cout << "=== System Bankowy ===" << std::endl;

    Address* bankAddress = new Address("Bankowa", "1", "Warszawa", "00-001", "Polska");
    BankService bank("MojBank", "MOJBPLPW", bankAddress);

    Address* clientAddress = new Address("Testowa", "10", "Krakow", "30-001", "Polska");
    IndividualClient* client = new IndividualClient(1, clientAddress,
        "123456789", "jan@email.pl", "Jan", "Kowalski", "90010112345");

    bank.registerClient(client);

    Account* account = bank.createAccount(client, "Savings", 1000.0, Currency::PLN);

    std::cout << "Bank: " << bank.toString() << std::endl;
    std::cout << "Klient: " << client->toString() << std::endl;
    std::cout << "Konto: " << account->toString() << std::endl;

    account->deposit(500.0);
    std::cout << "Po wplacie 500: " << account->getBalance() << " PLN" << std::endl;

    account->withdraw(200.0);
    std::cout << "Po wyplacie 200: " << account->getBalance() << " PLN" << std::endl;

    std::cout << "\n=== Koniec ===" << std::endl;
    return 0;
}
