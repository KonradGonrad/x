/**
 * @file tests.cpp
 * @brief Comprehensive unit tests for the banking system
 * 
 * Tests cover: Address, Account types, Client types, Transactions,
 * Repositories, MarketDataService, BankService, and Exception handling.
 */

#include "TestFramework.h"
#include "Exceptions.h"
#include "Address.h"
#include "SavingsAccount.h"
#include "InvestmentAccount.h"
#include "CurrencyAccount.h"
#include "IndividualClient.h"
#include "CompanyClient.h"
#include "Transfer.h"
#include "StockOperation.h"
#include "CurrencyExchange.h"
#include "TransactionRepository.h"
#include "MarketDataService.h"
#include "ClientRepository.h"
#include "BankService.h"

#include <iostream>
#include <memory>

// ============================================================================
// ADDRESS TESTS
// ============================================================================

void testAddressCreation(TestFramework& tf) {
    auto addr = std::make_shared<Address>("Marszałkowska", "1", "Warszawa", "00-001", "Polska");
    
    TEST_EQUAL(addr->getStreet(), "Marszałkowska");
    TEST_EQUAL(addr->getHouseNumber(), "1");
    TEST_EQUAL(addr->getCity(), "Warszawa");
    TEST_EQUAL(addr->getZipCode(), "00-001");
    TEST_EQUAL(addr->getCountry(), "Polska");
}

void testAddressToString(TestFramework& tf) {
    auto addr = std::make_shared<Address>("Długa", "10", "Kraków", "30-100", "Polska");
    std::string str = addr->toString();
    
    TEST_ASSERT(str.find("Długa") != std::string::npos);
    TEST_ASSERT(str.find("Kraków") != std::string::npos);
}

// ============================================================================
// SAVINGS ACCOUNT TESTS
// ============================================================================

void testSavingsAccountCreation(TestFramework& tf) {
    auto acc = std::make_shared<SavingsAccount>("PL12345678901234567890123456", 1000.0, Currency::PLN, "2026-01-01");
    
    TEST_EQUAL(acc->getIban(), "PL12345678901234567890123456");
    TEST_APPROX(acc->getBalance(), 1000.0, 0.01);
    TEST_EQUAL(acc->getCurrency(), Currency::PLN);
    TEST_EQUAL(acc->getStatus(), AccountStatus::ACTIVE);
}

void testSavingsAccountDeposit(TestFramework& tf) {
    auto acc = std::make_shared<SavingsAccount>("PL11111111111111111111111111", 500.0, Currency::PLN, "2026-01-01");
    
    acc->deposit(250.0);
    TEST_APPROX(acc->getBalance(), 750.0, 0.01);
}

void testSavingsAccountWithdraw(TestFramework& tf) {
    auto acc = std::make_shared<SavingsAccount>("PL22222222222222222222222222", 1000.0, Currency::PLN, "2026-01-01");
    
    acc->withdraw(300.0);
    TEST_APPROX(acc->getBalance(), 700.0, 0.01);
}

void testSavingsAccountInsufficientFunds(TestFramework& tf) {
    auto acc = std::make_shared<SavingsAccount>("PL33333333333333333333333333", 100.0, Currency::PLN, "2026-01-01");
    
    TEST_THROWS(acc->withdraw(200.0), InsufficientFundsException);
}

void testSavingsAccountInterestCapitalization(TestFramework& tf) {
    auto acc = std::make_shared<SavingsAccount>("PL44444444444444444444444444", 12000.0, Currency::PLN, "2026-01-01", 0.05);
    
    double before = acc->getBalance();
    acc->capitalizeInterest();
    double after = acc->getBalance();
    
    TEST_ASSERT(after > before);
    TEST_APPROX(after, 12000.0 + 12000.0 * (0.05 / 12.0), 0.01);
}

void testSavingsAccountInactiveDeposit(TestFramework& tf) {
    auto acc = std::make_shared<SavingsAccount>("PL55555555555555555555555555", 1000.0, Currency::PLN, "2026-01-01");
    acc->setStatus(AccountStatus::CLOSED);
    
    TEST_THROWS(acc->deposit(100.0), AccountNotActiveException);
}

// ============================================================================
// INVESTMENT ACCOUNT TESTS
// ============================================================================

void testInvestmentAccountCreation(TestFramework& tf) {
    auto acc = std::make_shared<InvestmentAccount>("PL66666666666666666666666666", 50000.0, Currency::PLN, "2026-01-01", 0.005);
    
    TEST_APPROX(acc->getBrokerageFee(), 0.005, 0.0001);
    TEST_ASSERT(acc->getPortfolio().empty());
}

void testInvestmentAccountBuyStock(TestFramework& tf) {
    auto acc = std::make_shared<InvestmentAccount>("PL77777777777777777777777777", 10000.0, Currency::PLN, "2026-01-01", 0.01);
    
    acc->buyStock("AAPL", 10, 175.0);
    
    TEST_ASSERT(acc->getPortfolio().count("AAPL") > 0);
    TEST_EQUAL(acc->getPortfolio().at("AAPL"), 10);
    TEST_ASSERT(acc->getBalance() < 10000.0);
}

void testInvestmentAccountSellStock(TestFramework& tf) {
    auto acc = std::make_shared<InvestmentAccount>("PL88888888888888888888888888", 10000.0, Currency::PLN, "2026-01-01", 0.01);
    
    acc->buyStock("MSFT", 5, 100.0);
    double balanceAfterBuy = acc->getBalance();
    
    acc->sellStock("MSFT", 3, 110.0);
    
    TEST_EQUAL(acc->getPortfolio().at("MSFT"), 2);
    TEST_ASSERT(acc->getBalance() > balanceAfterBuy);
}

void testInvestmentAccountSellMoreThanOwned(TestFramework& tf) {
    auto acc = std::make_shared<InvestmentAccount>("PL99999999999999999999999999", 10000.0, Currency::PLN, "2026-01-01", 0.01);
    
    acc->buyStock("GOOGL", 5, 140.0);
    
    TEST_THROWS(acc->sellStock("GOOGL", 10, 150.0), InvalidOperationException);
}

// ============================================================================
// CURRENCY ACCOUNT TESTS
// ============================================================================

void testCurrencyAccountCreation(TestFramework& tf) {
    auto acc = std::make_shared<CurrencyAccount>("PL10101010101010101010101010", 5000.0, Currency::EUR, "2026-01-01", 0.02);
    
    TEST_EQUAL(acc->getCurrency(), Currency::EUR);
    TEST_APPROX(acc->getSpread(), 0.02, 0.001);
}

void testCurrencyAccountExchangeFee(TestFramework& tf) {
    auto acc = std::make_shared<CurrencyAccount>("PL20202020202020202020202020", 1000.0, Currency::USD, "2026-01-01", 0.01);
    
    double before = acc->getBalance();
    acc->updateBalanceAfterExchange(100.0);
    
    TEST_ASSERT(acc->getBalance() < before);
}

// ============================================================================
// CLIENT TESTS
// ============================================================================

void testIndividualClientCreation(TestFramework& tf) {
    auto addr = std::make_shared<Address>("Kwiatowa", "5", "Gdańsk", "80-001", "Polska");
    auto client = std::make_shared<IndividualClient>(1, addr, "500123456", "jan@email.pl", "Jan", "Kowalski", "90010112345");
    
    TEST_EQUAL(client->getFirstName(), "Jan");
    TEST_EQUAL(client->getLastName(), "Kowalski");
    TEST_EQUAL(client->getPesel(), "90010112345");
    TEST_EQUAL(client->getTaxIdentifier(), "90010112345");
}

void testCompanyClientCreation(TestFramework& tf) {
    auto addr = std::make_shared<Address>("Biznesowa", "100", "Poznań", "60-001", "Polska");
    auto client = std::make_shared<CompanyClient>(2, addr, "223334455", "firma@corp.pl", "TechCorp Sp. z o.o.", "1234567890", "123456789", "0000012345");
    
    TEST_EQUAL(client->getCompanyName(), "TechCorp Sp. z o.o.");
    TEST_EQUAL(client->getNip(), "1234567890");
    TEST_EQUAL(client->getTaxIdentifier(), "1234567890");
}

void testClientAddAccount(TestFramework& tf) {
    auto addr = std::make_shared<Address>("Testowa", "1", "Łódź", "90-001", "Polska");
    auto client = std::make_shared<IndividualClient>(3, addr, "111222333", "test@test.pl", "Anna", "Nowak", "85050512345");
    
    auto acc = std::make_shared<SavingsAccount>("PL30303030303030303030303030", 2000.0, Currency::PLN, "2026-01-01");
    
    client->addAccount(acc);
    
    TEST_EQUAL(client->getAccounts().size(), 1u);
}

void testClientFindAccount(TestFramework& tf) {
    auto addr = std::make_shared<Address>("Szukana", "7", "Wrocław", "50-001", "Polska");
    auto client = std::make_shared<IndividualClient>(4, addr, "999888777", "szukam@mail.pl", "Piotr", "Szukacz", "77070712345");
    
    auto acc1 = std::make_shared<SavingsAccount>("PL40404040404040404040404040", 1000.0, Currency::PLN, "2026-01-01");
    auto acc2 = std::make_shared<InvestmentAccount>("PL50505050505050505050505050", 5000.0, Currency::PLN, "2026-01-01");
    
    client->addAccount(acc1);
    client->addAccount(acc2);
    
    auto found = client->findAccount("PL50505050505050505050505050");
    TEST_EQUAL(found->getIban(), "PL50505050505050505050505050");
}

void testClientFindAccountNotFound(TestFramework& tf) {
    auto addr = std::make_shared<Address>("Pusta", "0", "Sopot", "81-001", "Polska");
    auto client = std::make_shared<IndividualClient>(5, addr, "000000000", "pusta@mail.pl", "Ewa", "Pusta", "66060612345");
    
    TEST_THROWS(client->findAccount("PL00000000000000000000000000"), NotFoundException);
}

// ============================================================================
// TRANSACTION TESTS
// ============================================================================

void testTransferExecution(TestFramework& tf) {
    auto sender = std::make_shared<SavingsAccount>("SENDER1234567890123456789012", 2000.0, Currency::PLN, "2026-01-01");
    auto receiver = std::make_shared<SavingsAccount>("RECV01234567890123456789012", 500.0, Currency::PLN, "2026-01-01");
    
    auto transfer = std::make_shared<Transfer>(1, 500.0, sender, receiver);
    transfer->execute();
    
    TEST_APPROX(sender->getBalance(), 1500.0, 0.01);
    TEST_APPROX(receiver->getBalance(), 1000.0, 0.01);
}

void testTransferInsufficientFunds(TestFramework& tf) {
    auto sender = std::make_shared<SavingsAccount>("SENDER2234567890123456789012", 100.0, Currency::PLN, "2026-01-01");
    auto receiver = std::make_shared<SavingsAccount>("RECV02234567890123456789012", 500.0, Currency::PLN, "2026-01-01");
    
    auto transfer = std::make_shared<Transfer>(2, 500.0, sender, receiver);
    
    TEST_THROWS(transfer->execute(), InsufficientFundsException);
}

void testStockOperationBuy(TestFramework& tf) {
    auto acc = std::make_shared<InvestmentAccount>("STOCK1234567890123456789012", 10000.0, Currency::PLN, "2026-01-01", 0.01);
    
    auto op = std::make_shared<StockOperation>(3, acc, "CDR", 10, 125.0, true);
    op->execute();
    
    TEST_EQUAL(acc->getPortfolio().at("CDR"), 10);
}

void testStockOperationSell(TestFramework& tf) {
    auto acc = std::make_shared<InvestmentAccount>("STOCK2234567890123456789012", 10000.0, Currency::PLN, "2026-01-01", 0.01);
    
    acc->buyStock("PKO", 20, 50.0);
    
    auto op = std::make_shared<StockOperation>(4, acc, "PKO", 10, 55.0, false);
    op->execute();
    
    TEST_EQUAL(acc->getPortfolio().at("PKO"), 10);
}

// ============================================================================
// REPOSITORY TESTS
// ============================================================================

void testClientRepositoryAdd(TestFramework& tf) {
    ClientRepository repo;
    
    auto addr = std::make_shared<Address>("Repo", "1", "Test", "00-000", "PL");
    auto client = std::make_shared<IndividualClient>(100, addr, "111", "r@r.pl", "Repo", "Test", "12345678901");
    
    repo.add(client);
    
    TEST_EQUAL(repo.count(), 1u);
}

void testClientRepositoryFindById(TestFramework& tf) {
    ClientRepository repo;
    
    auto addr = std::make_shared<Address>("Find", "2", "City", "11-111", "PL");
    auto client = std::make_shared<IndividualClient>(200, addr, "222", "f@f.pl", "Find", "Me", "22345678901");
    
    repo.add(client);
    
    auto found = repo.findById(200);
    TEST_ASSERT(found.has_value());
    TEST_EQUAL(found.value()->getInternalId(), 200);
}

void testClientRepositoryGetById(TestFramework& tf) {
    ClientRepository repo;
    
    auto addr = std::make_shared<Address>("Get", "3", "Town", "22-222", "PL");
    auto client = std::make_shared<IndividualClient>(300, addr, "333", "g@g.pl", "Get", "It", "33345678901");
    
    repo.add(client);
    
    auto found = repo.getById(300);
    TEST_EQUAL(found->getInternalId(), 300);
}

void testClientRepositoryGetByIdNotFound(TestFramework& tf) {
    ClientRepository repo;
    
    TEST_THROWS(repo.getById(999), NotFoundException);
}

void testTransactionRepositoryFindByType(TestFramework& tf) {
    TransactionRepository repo;
    
    auto acc1 = std::make_shared<SavingsAccount>("TR123456789012345678901234", 1000.0, Currency::PLN, "2026-01-01");
    auto acc2 = std::make_shared<SavingsAccount>("TR223456789012345678901234", 1000.0, Currency::PLN, "2026-01-01");
    
    repo.add(std::make_shared<Transfer>(1, 100.0, acc1, acc2));
    repo.add(std::make_shared<Transfer>(2, 200.0, acc1, acc2));
    
    auto transfers = repo.findByType(TransactionType::TRANSFER);
    TEST_EQUAL(transfers.size(), 2u);
}

void testTransactionRepositoryTotalAmount(TestFramework& tf) {
    TransactionRepository repo;
    
    auto acc1 = std::make_shared<SavingsAccount>("TA123456789012345678901234", 5000.0, Currency::PLN, "2026-01-01");
    auto acc2 = std::make_shared<SavingsAccount>("TA223456789012345678901234", 5000.0, Currency::PLN, "2026-01-01");
    
    repo.add(std::make_shared<Transfer>(1, 100.0, acc1, acc2));
    repo.add(std::make_shared<Transfer>(2, 250.0, acc1, acc2));
    repo.add(std::make_shared<Transfer>(3, 150.0, acc1, acc2));
    
    TEST_APPROX(repo.getTotalAmount(), 500.0, 0.01);
}

// ============================================================================
// MARKET DATA SERVICE TESTS
// ============================================================================

void testMarketDataServiceGetQuote(TestFramework& tf) {
    MarketDataService mds;
    
    auto quote = mds.getStockQuote("AAPL");
    TEST_EQUAL(quote.ticker, "AAPL");
    TEST_ASSERT(quote.price > 0);
}

void testMarketDataServiceQuoteNotFound(TestFramework& tf) {
    MarketDataService mds;
    
    TEST_THROWS(mds.getStockQuote("UNKNOWN"), MarketDataException);
}

void testMarketDataServiceUpdateQuote(TestFramework& tf) {
    MarketDataService mds;
    
    mds.updateStockQuote("AAPL", 200.0);
    auto quote = mds.getStockQuote("AAPL");
    
    TEST_APPROX(quote.price, 200.0, 0.01);
}

void testMarketDataServiceExchangeRate(TestFramework& tf) {
    MarketDataService mds;
    
    double rate = mds.getExchangeRate(Currency::PLN, Currency::EUR);
    TEST_ASSERT(rate > 0);
    TEST_ASSERT(rate < 1);
}

void testMarketDataServiceSameCurrencyRate(TestFramework& tf) {
    MarketDataService mds;
    
    double rate = mds.getExchangeRate(Currency::PLN, Currency::PLN);
    TEST_APPROX(rate, 1.0, 0.001);
}

// ============================================================================
// BANK SERVICE TESTS
// ============================================================================

void testBankServiceCreation(TestFramework& tf) {
    auto addr = std::make_shared<Address>("Bankowa", "1", "Warszawa", "00-001", "Polska");
    BankService bank("TestBank", "TESTPLPW", "9999999999", addr);
    
    TEST_EQUAL(bank.getBankName(), "TestBank");
    TEST_EQUAL(bank.getBankSwift(), "TESTPLPW");
}

void testBankServiceRegisterClient(TestFramework& tf) {
    auto bankAddr = std::make_shared<Address>("Centrala", "1", "Warszawa", "00-001", "PL");
    BankService bank("Bank", "SWIFT123", "1111111111", bankAddr);
    
    auto clientAddr = std::make_shared<Address>("Kliencka", "5", "Kraków", "30-001", "PL");
    auto client = std::make_shared<IndividualClient>(1, clientAddr, "500600700", "klient@bank.pl", "Adam", "Klient", "80080812345");
    
    bank.registerClient(client);
    
    TEST_EQUAL(bank.getClientRepository().count(), 1u);
}

void testBankServiceCreateAccount(TestFramework& tf) {
    auto bankAddr = std::make_shared<Address>("Główna", "10", "Gdańsk", "80-001", "PL");
    BankService bank("MójBank", "MOJBPLPW", "2222222222", bankAddr);
    
    auto clientAddr = std::make_shared<Address>("Domowa", "3", "Gdynia", "81-001", "PL");
    auto client = std::make_shared<IndividualClient>(10, clientAddr, "123456789", "acc@test.pl", "Ewa", "Testowa", "99099912345");
    
    bank.registerClient(client);
    
    auto account = bank.createAccount(client, "Savings", 1000.0, Currency::PLN);
    
    TEST_ASSERT(account != nullptr);
    TEST_APPROX(account->getBalance(), 1000.0, 0.01);
    TEST_EQUAL(client->getAccounts().size(), 1u);
}

void testBankServiceExecuteTransfer(TestFramework& tf) {
    auto bankAddr = std::make_shared<Address>("Transfer", "1", "Łódź", "90-001", "PL");
    BankService bank("TransferBank", "TRNSPLPW", "3333333333", bankAddr);
    
    auto addr1 = std::make_shared<Address>("A", "1", "X", "00-001", "PL");
    auto addr2 = std::make_shared<Address>("B", "2", "Y", "00-002", "PL");
    
    auto client1 = std::make_shared<IndividualClient>(1, addr1, "111", "a@a.pl", "A", "A", "11111111111");
    auto client2 = std::make_shared<IndividualClient>(2, addr2, "222", "b@b.pl", "B", "B", "22222222222");
    
    bank.registerClient(client1);
    bank.registerClient(client2);
    
    auto acc1 = bank.createAccount(client1, "Savings", 5000.0, Currency::PLN);
    auto acc2 = bank.createAccount(client2, "Savings", 1000.0, Currency::PLN);
    
    bank.executeTransfer(acc1, acc2, 1000.0);
    
    TEST_APPROX(acc1->getBalance(), 4000.0, 0.01);
    TEST_APPROX(acc2->getBalance(), 2000.0, 0.01);
    TEST_EQUAL(bank.getTransactionRepository().count(), 1u);
}

// ============================================================================
// EXCEPTION TESTS
// ============================================================================

void testValidationException(TestFramework& tf) {
    try {
        throw ValidationException("Test validation error");
    } catch (const BankException& e) {
        TEST_ASSERT(std::string(e.what()).find("validation") != std::string::npos ||
                   std::string(e.what()).find("Test") != std::string::npos);
    }
}

void testInsufficientFundsExceptionDetails(TestFramework& tf) {
    try {
        throw InsufficientFundsException(1000.0, 500.0);
    } catch (const InsufficientFundsException& e) {
        TEST_APPROX(e.getRequested(), 1000.0, 0.01);
        TEST_APPROX(e.getAvailable(), 500.0, 0.01);
    }
}

void testNotFoundException(TestFramework& tf) {
    TEST_THROWS(throw NotFoundException("Test entity"), NotFoundException);
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
    TestFramework tf;
    
    std::cout << "========================================" << std::endl;
    std::cout << "   BANKING SYSTEM UNIT TESTS" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
    
    // Address tests
    tf.runTest("Address creation", testAddressCreation);
    tf.runTest("Address toString", testAddressToString);
    
    // SavingsAccount tests
    tf.runTest("SavingsAccount creation", testSavingsAccountCreation);
    tf.runTest("SavingsAccount deposit", testSavingsAccountDeposit);
    tf.runTest("SavingsAccount withdraw", testSavingsAccountWithdraw);
    tf.runTest("SavingsAccount insufficient funds", testSavingsAccountInsufficientFunds);
    tf.runTest("SavingsAccount interest capitalization", testSavingsAccountInterestCapitalization);
    tf.runTest("SavingsAccount inactive deposit", testSavingsAccountInactiveDeposit);
    
    // InvestmentAccount tests
    tf.runTest("InvestmentAccount creation", testInvestmentAccountCreation);
    tf.runTest("InvestmentAccount buy stock", testInvestmentAccountBuyStock);
    tf.runTest("InvestmentAccount sell stock", testInvestmentAccountSellStock);
    tf.runTest("InvestmentAccount sell more than owned", testInvestmentAccountSellMoreThanOwned);
    
    // CurrencyAccount tests
    tf.runTest("CurrencyAccount creation", testCurrencyAccountCreation);
    tf.runTest("CurrencyAccount exchange fee", testCurrencyAccountExchangeFee);
    
    // Client tests
    tf.runTest("IndividualClient creation", testIndividualClientCreation);
    tf.runTest("CompanyClient creation", testCompanyClientCreation);
    tf.runTest("Client add account", testClientAddAccount);
    tf.runTest("Client find account", testClientFindAccount);
    tf.runTest("Client find account not found", testClientFindAccountNotFound);
    
    // Transaction tests
    tf.runTest("Transfer execution", testTransferExecution);
    tf.runTest("Transfer insufficient funds", testTransferInsufficientFunds);
    tf.runTest("StockOperation buy", testStockOperationBuy);
    tf.runTest("StockOperation sell", testStockOperationSell);
    
    // Repository tests
    tf.runTest("ClientRepository add", testClientRepositoryAdd);
    tf.runTest("ClientRepository findById", testClientRepositoryFindById);
    tf.runTest("ClientRepository getById", testClientRepositoryGetById);
    tf.runTest("ClientRepository getById not found", testClientRepositoryGetByIdNotFound);
    tf.runTest("TransactionRepository findByType", testTransactionRepositoryFindByType);
    tf.runTest("TransactionRepository total amount", testTransactionRepositoryTotalAmount);
    
    // MarketDataService tests
    tf.runTest("MarketDataService get quote", testMarketDataServiceGetQuote);
    tf.runTest("MarketDataService quote not found", testMarketDataServiceQuoteNotFound);
    tf.runTest("MarketDataService update quote", testMarketDataServiceUpdateQuote);
    tf.runTest("MarketDataService exchange rate", testMarketDataServiceExchangeRate);
    tf.runTest("MarketDataService same currency rate", testMarketDataServiceSameCurrencyRate);
    
    // BankService tests
    tf.runTest("BankService creation", testBankServiceCreation);
    tf.runTest("BankService register client", testBankServiceRegisterClient);
    tf.runTest("BankService create account", testBankServiceCreateAccount);
    tf.runTest("BankService execute transfer", testBankServiceExecuteTransfer);
    
    // Exception tests
    tf.runTest("ValidationException", testValidationException);
    tf.runTest("InsufficientFundsException details", testInsufficientFundsExceptionDetails);
    tf.runTest("NotFoundException", testNotFoundException);
    
    // Print summary
    std::cout << std::endl;
    tf.printSummary();
    
    return tf.allPassed() ? 0 : 1;
}
