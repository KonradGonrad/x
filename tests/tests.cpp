#define BOOST_TEST_MODULE BankTests
#include <boost/test/unit_test.hpp>
#include <memory>
#include <fstream>
#include "SavingsAccount.h"
#include "InvestmentAccount.h"
#include "IndividualClient.h"
#include "CompanyClient.h"
#include "Transfer.h"
#include "Address.h"
#include "BankException.h"
#include "Repository.h"
#include "Persistence.h"
#include "BankService.h"

// Test 1: Deposit increases balance
BOOST_AUTO_TEST_CASE(Deposit_IncreasesBalance) {
    SavingsAccount account("PL12345678901234567890123456", 1000.0, 
                           Currency::PLN, "2026-01-01", 0.05);
    
    account.deposit(500.0);
    
    BOOST_CHECK_EQUAL(account.checkBalance(), 1500.0);
}

// Test 2: Withdraw decreases balance
BOOST_AUTO_TEST_CASE(Withdraw_DecreasesBalance) {
    SavingsAccount account("PL12345678901234567890123456", 1000.0, 
                           Currency::PLN, "2026-01-01", 0.05);
    
    account.withdraw(300.0);
    
    BOOST_CHECK_EQUAL(account.checkBalance(), 700.0);
}

// Test 3: Withdraw throws exception when not enough money
BOOST_AUTO_TEST_CASE(Withdraw_ThrowsWhenNotEnoughMoney) {
    SavingsAccount account("PL12345678901234567890123456", 100.0, 
                           Currency::PLN, "2026-01-01", 0.05);
    
    BOOST_CHECK_THROW(account.withdraw(500.0), InsufficientFundsException);
}

// Test 4: Transfer moves money between accounts
BOOST_AUTO_TEST_CASE(Transfer_MovesMoney) {
    auto sender = std::make_shared<SavingsAccount>("PL11111111111111111111111111", 1000.0, 
                                                    Currency::PLN, "2026-01-01", 0.05);
    auto receiver = std::make_shared<SavingsAccount>("PL22222222222222222222222222", 500.0, 
                                                      Currency::PLN, "2026-01-01", 0.05);
    
    Transfer transfer(1, 300.0, "Test", sender, receiver);
    transfer.execute();
    
    BOOST_CHECK_EQUAL(sender->checkBalance(), 700.0);
    BOOST_CHECK_EQUAL(receiver->checkBalance(), 800.0);
}

// Test 5: Invalid amount throws exception
BOOST_AUTO_TEST_CASE(Deposit_ThrowsOnNegativeAmount) {
    SavingsAccount account("PL12345678901234567890123456", 1000.0, 
                           Currency::PLN, "2026-01-01", 0.05);
    
    BOOST_CHECK_THROW(account.deposit(-100.0), InvalidAmountException);
}

// Test 6: Template Repository add and count
BOOST_AUTO_TEST_CASE(Repository_AddAndCount) {
    Repository<Account> repo;
    auto acc1 = std::make_shared<SavingsAccount>("PL11111111111111111111111111", 1000.0, 
                                                  Currency::PLN, "2026-01-01", 0.05);
    auto acc2 = std::make_shared<SavingsAccount>("PL22222222222222222222222222", 2000.0, 
                                                  Currency::PLN, "2026-01-01", 0.05);
    
    repo.add(acc1);
    repo.add(acc2);
    
    BOOST_CHECK_EQUAL(repo.count(), 2);
}

// Test 7: Template Repository findIf
BOOST_AUTO_TEST_CASE(Repository_FindIf) {
    Repository<Account> repo;
    auto acc1 = std::make_shared<SavingsAccount>("PL11111111111111111111111111", 1000.0, 
                                                  Currency::PLN, "2026-01-01", 0.05);
    auto acc2 = std::make_shared<SavingsAccount>("PL22222222222222222222222222", 2000.0, 
                                                  Currency::PLN, "2026-01-01", 0.05);
    
    repo.add(acc1);
    repo.add(acc2);
    
    auto found = repo.findIf([](const std::shared_ptr<Account>& a) {
        return a->checkBalance() == 2000.0;
    });
    
    BOOST_CHECK(found != nullptr);
    BOOST_CHECK_EQUAL(found->checkBalance(), 2000.0);
}

// Test 8: Persistence save and load
BOOST_AUTO_TEST_CASE(Persistence_SaveAndLoad) {
    std::vector<std::shared_ptr<Account>> accounts;
    accounts.push_back(std::make_shared<SavingsAccount>("PL12345678901234567890123456", 
                                                         1500.0, Currency::PLN, "2026-01-01", 0.05));
    
    AccountPersistence persistence;
    persistence.save("test_accounts.dat", accounts);
    
    auto loaded = persistence.load("test_accounts.dat");
    
    BOOST_CHECK_EQUAL(loaded.size(), 1);
    BOOST_CHECK_EQUAL(loaded[0]->checkBalance(), 1500.0);
    
    std::remove("test_accounts.dat");
}

// Test 9: Client add account and count
BOOST_AUTO_TEST_CASE(Client_AddAccountAndCount) {
    auto address = std::make_shared<Address>("Street", "1", "City", "00-000", "Country");
    auto client = std::make_shared<IndividualClient>(1, address, "John", "Doe", "12345678901");
    
    auto account = std::make_shared<SavingsAccount>("PL12345678901234567890123456", 
                                                     1000.0, Currency::PLN, "2026-01-01", 0.05);
    client->addAccount(account);
    
    BOOST_CHECK_EQUAL(client->countAccounts(), 1);
}

// Test 10: BankService registers client
BOOST_AUTO_TEST_CASE(BankService_RegisterClient) {
    auto bankAddress = std::make_shared<Address>("Bank St", "1", "Warsaw", "00-001", "Poland");
    BankService bank("TestBank", "TESTPLPW", bankAddress);
    
    auto clientAddress = std::make_shared<Address>("Client St", "2", "Warsaw", "00-002", "Poland");
    auto client = std::make_shared<IndividualClient>(1, clientAddress, "Jan", "Kowalski", "98765432101");
    
    bank.registerClient(client);
    
    BOOST_CHECK_EQUAL(bank.countClients(), 1);
}
