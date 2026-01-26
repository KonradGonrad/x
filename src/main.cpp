#include <iostream>
#include <iomanip>
#include <cstring>

#include "BankService.h"
#include "IndividualClient.h"
#include "CompanyClient.h"
#include "SavingsAccount.h"
#include "InvestmentAccount.h"
#include "CurrencyAccount.h"
#include "Transfer.h"
#include "StockOperation.h"
#include "CurrencyExchange.h"
#include "TransactionRepository.h"
#include "MarketDataService.h"
#include "Currency.h"
#include "Address.h"
#include "WebServer.h"
#include "ConsoleUI.h"

void runConsoleUI(BankService* bank1, BankService* bank2, BankService* bank3,
                  MarketDataService* marketData, TransactionRepository* transactionRepo);

void printSeparator(const std::string& title) {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << std::string(70, '=') << std::endl;
}

void printAccountDetails(const std::string& clientName, const std::vector<Account*>& accounts) {
    std::cout << "\n" << clientName << " Accounts:" << std::endl;
    std::cout << std::string(70, '-') << std::endl;
    for (const auto& acc : accounts) {
        std::cout << acc->toString() << std::endl;
    }
}

void runDemo(BankService* bank1, BankService* bank2, BankService* bank3,
             IndividualClient* individual1, CompanyClient* company1, IndividualClient* individual2,
             Account* savings1, Account* investment1, Account* currency1_usd,
             Account* savings2, Account* investment2,
             MarketDataService* marketData);

void runWebServer(BankService* bank1, BankService* bank2, BankService* bank3,
                  MarketDataService* marketData, TransactionRepository* transactionRepo,
                  int port);

int main(int argc, char* argv[]) {
    // Check for command line arguments
    bool webMode = false;
    bool consoleMode = false;
    int port = 8080;
    
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--web") == 0 || std::strcmp(argv[i], "-w") == 0) {
            webMode = true;
        } else if (std::strcmp(argv[i], "--console") == 0 || std::strcmp(argv[i], "-c") == 0) {
            consoleMode = true;
        } else if (std::strcmp(argv[i], "--port") == 0 || std::strcmp(argv[i], "-p") == 0) {
            if (i + 1 < argc) {
                port = std::atoi(argv[++i]);
            }
        } else if (std::strcmp(argv[i], "--help") == 0 || std::strcmp(argv[i], "-h") == 0) {
            std::cout << "Banking System - Usage:\n";
            std::cout << "  banking_system           Run demo mode (non-interactive)\n";
            std::cout << "  banking_system --console Run interactive console UI\n";
            std::cout << "  banking_system --web     Run web server mode\n";
            std::cout << "  banking_system -w -p 3000  Run web server on port 3000\n";
            std::cout << "\nOptions:\n";
            std::cout << "  -c, --console  Start interactive console UI\n";
            std::cout << "  -w, --web      Start web server (bonus feature)\n";
            std::cout << "  -p, --port     Set server port (default: 8080)\n";
            std::cout << "  -h, --help     Show this help\n";
            return 0;
        }
    }
    std::cout << "\n+====================================================================+" << std::endl;
    std::cout << "|           Banking System - Multi-Bank Demonstration              |" << std::endl;
    std::cout << "|                        C++20 Implementation                       |" << std::endl;
    std::cout << "+====================================================================+" << std::endl;

    // ===== INITIALIZE SERVICES =====
    MarketDataService* marketData = new MarketDataService();
    TransactionRepository* transactionRepo = new TransactionRepository();
    std::cout << "\nMarket Data Service initialized with default rates and prices." << std::endl;

    // ===== CREATE THREE BANKS =====
    printSeparator("Creating Three Bank Services");

    Address* bankOffice1 = new Address("Nowy Swiat", "25", "Warsaw", "00-029", "Poland");
    BankService* bank1 = new BankService("PKO Bank Polski", "PKOPPLPW", "0000000096", bankOffice1);
    std::cout << "[OK] Bank 1: " << bank1->toString() << std::endl;

    Address* bankOffice2 = new Address("Marszalkowska", "100", "Warsaw", "00-021", "Poland");
    BankService* bank2 = new BankService("ING Bank Slaski", "INGBPLPW", "0000000057", bankOffice2);
    std::cout << "[OK] Bank 2: " << bank2->toString() << std::endl;

    Address* bankOffice3 = new Address("Al. Jerozolimskie", "65", "Warsaw", "00-001", "Poland");
    BankService* bank3 = new BankService("mBank", "BREXPLPW", "0000000019", bankOffice3);
    std::cout << "[OK] Bank 3: " << bank3->toString() << std::endl;

    // ===== CREATE CLIENTS FOR BANK 1 =====
    printSeparator("Bank 1 - Creating Clients and Accounts");

    Address* addr1 = new Address("Krakowskie Przedmiescie", "13", "Warsaw", "00-081", "Poland");
    IndividualClient* individual1 = new IndividualClient(
        1001, addr1, "+48-22-555-0001", "jan.kowalski@email.com",
        "Jan", "Kowalski", "90010112345");
    bank1->registerClient(individual1);
    std::cout << "[OK] Registered: " << individual1->toString() << std::endl;

    // Create accounts for individual1
    Account* savings1 = bank1->createAccount(individual1, "Savings", 10000.0, Currency::PLN);
    std::cout << "  -> " << savings1->toString() << std::endl;

    Account* investment1 = bank1->createAccount(individual1, "Investment", 50000.0, Currency::PLN);
    std::cout << "  -> " << investment1->toString() << std::endl;

    Account* currency1_usd = bank1->createAccount(individual1, "Currency", 5000.0, Currency::USD);
    std::cout << "  -> " << currency1_usd->toString() << std::endl;

    // ===== CREATE CLIENTS FOR BANK 2 =====
    printSeparator("Bank 2 - Creating Clients and Accounts");

    Address* addr2 = new Address("Al. Jerozolimskie", "44", "Warsaw", "00-024", "Poland");
    CompanyClient* company1 = new CompanyClient(
        2001, addr2, "+48-22-555-0002", "contact@techcorp.pl",
        "TechCorp Sp. z o.o.", "1234567890", "123456789", "0000123456");
    bank2->registerClient(company1);
    std::cout << "[OK] Registered: " << company1->toString() << std::endl;

    // Create accounts for company1
    Account* savings2 = bank2->createAccount(company1, "Savings", 100000.0, Currency::PLN);
    std::cout << "  -> " << savings2->toString() << std::endl;

    Account* investment2 = bank2->createAccount(company1, "Investment", 250000.0, Currency::EUR);
    std::cout << "  -> " << investment2->toString() << std::endl;

    Account* currency2_gbp = bank2->createAccount(company1, "Currency", 20000.0, Currency::GBP);
    std::cout << "  -> " << currency2_gbp->toString() << std::endl;

    // ===== CREATE CLIENTS FOR BANK 3 =====
    printSeparator("Bank 3 - Creating Clients and Accounts");

    Address* addr3 = new Address("Pulaskiego", "7", "Gdansk", "80-863", "Poland");
    IndividualClient* individual2 = new IndividualClient(
        3001, addr3, "+48-58-555-0003", "maria.nowak@email.com",
        "Maria", "Nowak", "88010234567");
    bank3->registerClient(individual2);
    std::cout << "[OK] Registered: " << individual2->toString() << std::endl;

    // Create accounts for individual2
    Account* savings3 = bank3->createAccount(individual2, "Savings", 25000.0, Currency::PLN);
    std::cout << "  -> " << savings3->toString() << std::endl;

    Account* investment3 = bank3->createAccount(individual2, "Investment", 75000.0, Currency::USD);
    std::cout << "  -> " << investment3->toString() << std::endl;

    // ===== RUN MODE =====
    if (webMode) {
        runWebServer(bank1, bank2, bank3, marketData, transactionRepo, port);
    } else if (consoleMode) {
        runConsoleUI(bank1, bank2, bank3, marketData, transactionRepo);
    } else {
        runDemo(bank1, bank2, bank3, individual1, company1, individual2,
                savings1, investment1, currency1_usd, savings2, investment2, marketData);
    }

    // ===== CLEANUP =====
    delete bank1;
    delete bank2;
    delete bank3;
    delete marketData;
    delete transactionRepo;

    return 0;
}

// ============================================================================
// Console UI Mode (Interactive)
// ============================================================================

void runConsoleUI(BankService* bank1, BankService* bank2, BankService* bank3,
                  MarketDataService* marketData, TransactionRepository* transactionRepo) {
    ConsoleUI console;
    
    console.addBank(bank1);
    console.addBank(bank2);
    console.addBank(bank3);
    console.setMarketDataService(marketData);
    console.setTransactionRepository(transactionRepo);
    
    console.run();
}

// ============================================================================
// Web Server Mode (Bonus Feature)
// ============================================================================

void runWebServer(BankService* bank1, BankService* bank2, BankService* bank3,
                  MarketDataService* marketData, TransactionRepository* transactionRepo,
                  int port) {
    WebServer server(port, "web");
    
    server.addBank(bank1);
    server.addBank(bank2);
    server.addBank(bank3);
    server.setMarketDataService(marketData);
    server.setTransactionRepository(transactionRepo);
    
    server.start();
}

// ============================================================================
// Demo Mode
// ============================================================================

void runDemo(BankService* bank1, BankService* bank2, BankService* bank3,
             IndividualClient* individual1, CompanyClient* company1, IndividualClient* individual2,
             Account* savings1, Account* investment1, Account* currency1_usd,
             Account* savings2, Account* investment2,
             MarketDataService* marketData) {
    
    // ===== SHOW INITIAL ACCOUNT STATES =====
    printSeparator("Initial Account Balances");
    printAccountDetails("Bank 1 - Jan Kowalski", individual1->getAccounts());
    printAccountDetails("Bank 2 - TechCorp", company1->getAccounts());
    printAccountDetails("Bank 3 - Maria Nowak", individual2->getAccounts());

    // ===== TEST 1: TRANSFER BETWEEN ACCOUNTS (SAME BANK) =====
    printSeparator("Test 1: Transfer Between Accounts (Bank 1)");
    std::cout << "\nTransferring 5000 PLN from Savings to Investment account..." << std::endl;
    
    Transfer* transfer1 = new Transfer(1001, 5000.0, savings1, investment1);
    if (transfer1->execute()) {
        std::cout << "[OK] Transfer successful: " << transfer1->toString() << std::endl;
    } else {
        std::cout << "[FAIL] Transfer failed" << std::endl;
    }
    
    std::cout << "\nUpdated balances:" << std::endl;
    std::cout << "  Savings:    " << savings1->toString() << std::endl;
    std::cout << "  Investment: " << investment1->toString() << std::endl;

    // ===== TEST 2: STOCK OPERATION =====
    printSeparator("Test 2: Stock Purchase (Bank 2)");
    std::cout << "\nBuying stocks for TechCorp investment account..." << std::endl;
    
    InvestmentAccount* investAcct2 = dynamic_cast<InvestmentAccount*>(investment2);
    if (investAcct2) {
        StockOperation* stockOp = new StockOperation(
            2001, 25000.0, investAcct2, "GOOGL", 50, marketData);
        
        std::cout << "Stock Purchase Details:" << std::endl;
        std::cout << "  Ticker: GOOGL" << std::endl;
        std::cout << "  Quantity: 50 shares" << std::endl;
        std::cout << "  Current Price: " << marketData->getStockPrice("GOOGL") << " USD" << std::endl;
        
        if (stockOp->execute()) {
            std::cout << "[OK] Stock purchase successful: " << stockOp->toString() << std::endl;
        } else {
            std::cout << "[FAIL] Stock purchase failed" << std::endl;
        }
        
        std::cout << "\nUpdated Investment Account:" << std::endl;
        std::cout << "  " << investAcct2->toString() << std::endl;
    }

    // ===== TEST 3: SAVINGS ACCOUNT INTEREST =====
    printSeparator("Test 3: Savings Account - Interest Capitalization (Bank 1)");
    std::cout << "\nApplying monthly interest to savings account..." << std::endl;
    
    SavingsAccount* savingsAcct1 = dynamic_cast<SavingsAccount*>(savings1);
    if (savingsAcct1) {
        std::cout << "Before: " << savingsAcct1->toString() << std::endl;
        savingsAcct1->capitalizeInterest();
        std::cout << "After:  " << savingsAcct1->toString() << std::endl;
    }

    // ===== TEST 4: CURRENCY EXCHANGE =====
    printSeparator("Test 4: Currency Exchange (Bank 1)");
    std::cout << "\nPerforming currency exchange on USD account..." << std::endl;
    
    CurrencyAccount* currencyAcct1 = dynamic_cast<CurrencyAccount*>(currency1_usd);
    if (currencyAcct1) {
        double spreadFee = 100.0;
        std::cout << "Exchange Details:" << std::endl;
        std::cout << "  Amount: " << spreadFee << " USD" << std::endl;
        std::cout << "  Target Currency: EUR" << std::endl;
        std::cout << "  Exchange Rate: " << marketData->getRate(Currency::EUR) << std::endl;
        
        CurrencyExchange* exchange = new CurrencyExchange(
            3001, spreadFee, currencyAcct1, Currency::EUR,
            marketData->getRate(Currency::EUR), marketData);
        
        std::cout << "Before: " << currencyAcct1->toString() << std::endl;
        if (exchange->execute()) {
            std::cout << "[OK] Exchange successful: " << exchange->toString() << std::endl;
        } else {
            std::cout << "[FAIL] Exchange failed" << std::endl;
        }
        std::cout << "After:  " << currencyAcct1->toString() << std::endl;
    }

    // ===== TEST 5: TRANSFER BETWEEN DIFFERENT BANKS =====
    printSeparator("Test 5: Transfer Between Different Banks");
    std::cout << "\nTransferring 2000 PLN from Bank 1 to Bank 2..." << std::endl;
    
    Transfer* transfer2 = new Transfer(4001, 2000.0, savings1, savings2);
    if (transfer2->execute()) {
        std::cout << "[OK] Cross-bank transfer successful: " << transfer2->toString() << std::endl;
    } else {
        std::cout << "[FAIL] Cross-bank transfer failed" << std::endl;
    }
    
    std::cout << "\nUpdated balances:" << std::endl;
    std::cout << "  Bank 1 (Jan Kowalski): " << savings1->toString() << std::endl;
    std::cout << "  Bank 2 (TechCorp):     " << savings2->toString() << std::endl;

    // ===== FINAL ACCOUNT STATES =====
    printSeparator("Final Account Balances");
    printAccountDetails("Bank 1 - Jan Kowalski", individual1->getAccounts());
    printAccountDetails("Bank 2 - TechCorp", company1->getAccounts());
    printAccountDetails("Bank 3 - Maria Nowak", individual2->getAccounts());

    // ===== MONTHLY FEE PROCESSING =====
    printSeparator("Processing Monthly Fees");
    std::cout << "\nCalculating monthly fees for all accounts..." << std::endl;
    
    double totalFees = 0.0;
    std::cout << "\nBank 1:" << std::endl;
    for (const auto& acc : individual1->getAccounts()) {
        double fee = acc->calculateMonthlyFees();
        totalFees += fee;
        std::cout << "  " << typeid(*acc).name() << " fee: " << std::fixed << std::setprecision(2) << fee << std::endl;
    }
    
    std::cout << "\nBank 2:" << std::endl;
    for (const auto& acc : company1->getAccounts()) {
        double fee = acc->calculateMonthlyFees();
        totalFees += fee;
        std::cout << "  " << typeid(*acc).name() << " fee: " << std::fixed << std::setprecision(2) << fee << std::endl;
    }
    
    std::cout << "\nBank 3:" << std::endl;
    for (const auto& acc : individual2->getAccounts()) {
        double fee = acc->calculateMonthlyFees();
        totalFees += fee;
        std::cout << "  " << typeid(*acc).name() << " fee: " << std::fixed << std::setprecision(2) << fee << std::endl;
    }
    
    std::cout << "\nTotal Monthly Fees: " << std::fixed << std::setprecision(2) << totalFees << " PLN" << std::endl;

    // ===== PROCESS SESSION =====
    printSeparator("Processing Banking Sessions");
    std::cout << "\nProcessing sessions for all banks..." << std::endl;
    bank1->processSession();
    std::cout << "[OK] Bank 1 session processed" << std::endl;
    
    bank2->processSession();
    std::cout << "[OK] Bank 2 session processed" << std::endl;
    
    bank3->processSession();
    std::cout << "[OK] Bank 3 session processed" << std::endl;

    // ===== CLEANUP =====
    printSeparator("Demo Complete");
    std::cout << "\n[OK] All banking operations completed successfully!" << std::endl;
    std::cout << "\nSummary:" << std::endl;
    std::cout << "  * 3 Banks created and operated" << std::endl;
    std::cout << "  * 3 Individual/Company clients registered" << std::endl;
    std::cout << "  * 9 Accounts created (3 per client)" << std::endl;
    std::cout << "  * Multiple transactions executed:" << std::endl;
    std::cout << "    - Internal transfers" << std::endl;
    std::cout << "    - Cross-bank transfers" << std::endl;
    std::cout << "    - Stock operations" << std::endl;
    std::cout << "    - Currency exchanges" << std::endl;
    std::cout << "    - Interest capitalization" << std::endl;
    std::cout << "  * Monthly fees calculated and processed" << std::endl;

    std::cout << "\n+====================================================================+\n" << std::endl;
}
