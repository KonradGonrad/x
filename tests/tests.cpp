/**
 * @file tests.cpp
 * @brief Testy jednostkowe systemu bankowego
 */

#include <iostream>
#include <memory>
#include <sstream>

#include "TestFramework.h"
#include "Account.h"
#include "SavingsAccount.h"
#include "InvestmentAccount.h"
#include "CurrencyAccount.h"
#include "Client.h"
#include "IndividualClient.h"
#include "CompanyClient.h"
#include "Address.h"
#include "Transfer.h"
#include "Currency.h"
#include "Exceptions.h"
#include "Repository.h"

// ============================================================================
// Testy Account
// ============================================================================

void testAccount(TestRunner& runner) {
    std::cout << "\n--- Testy Account ---\n";

    SavingsAccount savings("PL12345678901234567890123456", 1000.0, Currency::PLN, "2024-01-01", 0.03);
    
    // Test 1: Saldo poczatkowe
    TEST_EQUAL(1000.0, savings.getBalance(), "Account: saldo poczatkowe");
    
    // Test 2: Wplata
    savings.deposit(500.0);
    TEST_EQUAL(1500.0, savings.getBalance(), "Account: wplata 500");
    
    // Test 3: Wyplata
    savings.withdraw(200.0);
    TEST_EQUAL(1300.0, savings.getBalance(), "Account: wyplata 200");
    
    // Test 4: Wyjatek przy braku srodkow
    TEST_THROWS(InsufficientFundsException, savings.withdraw(5000.0), "Account: wyjatek brak srodkow");
    
    // Test 5: Wyjatek ujemna wplata
    TEST_THROWS(InvalidOperationException, savings.deposit(-100.0), "Account: wyjatek ujemna wplata");
}

// ============================================================================
// Testy Client
// ============================================================================

void testClient(TestRunner& runner) {
    std::cout << "\n--- Testy Client ---\n";

    Address* addr = new Address("Testowa", "1", "Warszawa", "00-001", "Polska");
    IndividualClient client(1, addr, "+48-123-456-789", "test@test.pl", "Jan", "Kowalski", "90010112345");

    // Test 6: Imie klienta
    TEST_STRING_EQUAL("Jan", client.getFirstName(), "Client: imie");
    
    // Test 7: Nazwisko klienta
    TEST_STRING_EQUAL("Kowalski", client.getLastName(), "Client: nazwisko");
    
    // Test 8: Poczatkowo brak kont
    TEST_ASSERT(client.getAccounts().empty(), "Client: brak kont poczatkowo");
    
    // Test 9: Dodanie konta
    Account* acc = new SavingsAccount("PL11111111111111111111111111", 5000.0, Currency::PLN, "2024-01-01");
    client.addAccount(acc);
    TEST_EQUAL((size_t)1, client.getAccounts().size(), "Client: jedno konto po dodaniu");
}

// ============================================================================
// Testy Transfer
// ============================================================================

void testTransfer(TestRunner& runner) {
    std::cout << "\n--- Testy Transfer ---\n";

    SavingsAccount sender("PL11111111111111111111111111", 1000.0, Currency::PLN, "2024-01-01");
    SavingsAccount receiver("PL22222222222222222222222222", 500.0, Currency::PLN, "2024-01-01");

    // Test 10: Wykonanie przelewu
    Transfer transfer1(1, 300.0, &sender, &receiver);
    bool result = transfer1.execute();
    TEST_ASSERT(result, "Transfer: wykonanie");
    
    // Test 11: Saldo nadawcy po przelewie
    TEST_EQUAL(700.0, sender.getBalance(), "Transfer: saldo nadawcy");
    
    // Test 12: Saldo odbiorcy po przelewie
    TEST_EQUAL(800.0, receiver.getBalance(), "Transfer: saldo odbiorcy");
    
    // Test 13: Wyjatek przy braku srodkow
    Transfer transfer2(2, 5000.0, &sender, &receiver);
    TEST_THROWS(InsufficientFundsException, transfer2.execute(), "Transfer: wyjatek brak srodkow");
}

// ============================================================================
// Testy Repository
// ============================================================================

void testRepository(TestRunner& runner) {
    std::cout << "\n--- Testy Repository ---\n";

    Repository<SavingsAccount, std::string> repo;

    // Test 14: Poczatkowo puste
    TEST_ASSERT(repo.empty(), "Repository: puste na poczatku");
    
    // Test 15: Dodanie elementu
    repo.add("ACC1", new SavingsAccount("PL00001", 1000.0, Currency::PLN, "2024-01-01"));
    TEST_EQUAL((size_t)1, repo.size(), "Repository: rozmiar 1");
    
    // Test 16: Pobranie elementu
    auto acc = repo.get("ACC1");
    TEST_ASSERT(acc != nullptr, "Repository: pobranie elementu");
    
    // Test 17: Wyjatek przy braku elementu
    TEST_THROWS(BankException, repo.get("NIEISTNIEJACY"), "Repository: wyjatek brakujacy element");
}

// ============================================================================
// Testy wyjatkow
// ============================================================================

void testExceptions(TestRunner& runner) {
    std::cout << "\n--- Testy Exceptions ---\n";

    // Test 18: InsufficientFundsException
    try {
        throw InsufficientFundsException(1000.0, 500.0);
    } catch (const InsufficientFundsException& e) {
        TEST_EQUAL(1000.0, e.getRequested(), "Exception: zadana kwota");
    }

    // Test 19: Hierarchia wyjatkow
    bool caughtByBase = false;
    try {
        throw ClientNotFoundException(999);
    } catch (const BankException& e) {
        caughtByBase = true;
    }
    TEST_ASSERT(caughtByBase, "Exception: hierarchia dziedziczenia");
}

// ============================================================================
// Testy Currency
// ============================================================================

void testCurrency(TestRunner& runner) {
    std::cout << "\n--- Testy Currency ---\n";

    // Test 20: Konwersja do string
    TEST_STRING_EQUAL("PLN", currencyToString(Currency::PLN), "Currency: PLN to string");
}

// ============================================================================
// Main
// ============================================================================

int main() {
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "  TESTY JEDNOSTKOWE - SYSTEM BANKOWY\n";
    std::cout << "========================================\n";

    TestRunner runner;

    testAccount(runner);
    testClient(runner);
    testTransfer(runner);
    testRepository(runner);
    testExceptions(runner);
    testCurrency(runner);

    runner.printSummary();

    return runner.allPassed() ? 0 : 1;
}
