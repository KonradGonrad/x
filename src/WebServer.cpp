/**
 * @file WebServer.cpp
 * @brief Implementacja serwera HTTP
 */

// Windows version configuration for cpp-httplib
#ifdef _WIN32
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0A00  // Windows 10
#endif
#endif

// IMPORTANT: Make sure CPPHTTPLIB_OPENSSL_SUPPORT is NOT defined
// We only need HTTP, not HTTPS for this local development server
#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
#undef CPPHTTPLIB_OPENSSL_SUPPORT
#endif

#include "WebServer.h"
#include "external/httplib.h"
#include "BankService.h"
#include "Client.h"
#include "IndividualClient.h"
#include "CompanyClient.h"
#include "Account.h"
#include "SavingsAccount.h"
#include "InvestmentAccount.h"
#include "CurrencyAccount.h"
#include "Transaction.h"
#include "Transfer.h"
#include "StockOperation.h"
#include "CurrencyExchange.h"
#include "TransactionRepository.h"
#include "MarketDataService.h"
#include "Address.h"
#include "Currency.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

// ============================================================================
// Constructor & Destructor
// ============================================================================

WebServer::WebServer(int port, const std::string& webRoot)
    : port(port), webRoot(webRoot), marketData(nullptr), 
      transactionRepo(nullptr), running(false) {
}

WebServer::~WebServer() {
    stop();
}

// ============================================================================
// Configuration Methods
// ============================================================================

void WebServer::addBank(BankService* bank) {
    if (bank != nullptr) {
        banks.push_back(bank);
    }
}

void WebServer::setMarketDataService(MarketDataService* market) {
    this->marketData = market;
}

void WebServer::setTransactionRepository(TransactionRepository* repo) {
    this->transactionRepo = repo;
}

// ============================================================================
// JSON Conversion Helpers
// ============================================================================

std::string WebServer::clientToJson(Client* client) const {
    std::ostringstream json;
    json << std::fixed << std::setprecision(2);
    
    json << "{";
    json << "\"id\":" << client->getInternalId() << ",";
    json << "\"email\":\"" << client->getEmail() << "\",";
    json << "\"phone\":\"" << client->getPhoneNumber() << "\",";
    json << "\"taxId\":\"" << client->getTaxIdentifier() << "\",";
    
    // Address
    Address* addr = client->getAddress();
    if (addr) {
        json << "\"address\":\"" << addr->toString() << "\",";
    }
    
    // Determine client type and add specific fields
    IndividualClient* individual = dynamic_cast<IndividualClient*>(client);
    CompanyClient* company = dynamic_cast<CompanyClient*>(client);
    
    if (individual) {
        json << "\"type\":\"individual\",";
        json << "\"firstName\":\"" << individual->getFirstName() << "\",";
        json << "\"lastName\":\"" << individual->getLastName() << "\",";
        json << "\"pesel\":\"" << individual->getPesel() << "\",";
        json << "\"name\":\"" << individual->getFirstName() << " " << individual->getLastName() << "\"";
    } else if (company) {
        json << "\"type\":\"company\",";
        json << "\"companyName\":\"" << company->getCompanyName() << "\",";
        json << "\"nip\":\"" << company->getNip() << "\",";
        json << "\"regon\":\"" << company->getRegon() << "\",";
        json << "\"krs\":\"" << company->getKrs() << "\",";
        json << "\"name\":\"" << company->getCompanyName() << "\"";
    }
    
    json << "}";
    return json.str();
}

std::string WebServer::accountToJson(Account* account) const {
    std::ostringstream json;
    json << std::fixed << std::setprecision(2);
    
    json << "{";
    json << "\"iban\":\"" << account->getIban() << "\",";
    json << "\"balance\":" << account->getBalance() << ",";
    json << "\"currency\":\"" << currencyToString(account->getCurrency()) << "\",";
    json << "\"status\":\"" << (account->getStatus() == AccountStatus::ACTIVE ? "ACTIVE" : 
                                 account->getStatus() == AccountStatus::BLOCKED ? "BLOCKED" : "CLOSED") << "\",";
    json << "\"creationDate\":\"" << account->getCreationDate() << "\",";
    json << "\"monthlyFee\":" << account->calculateMonthlyFees() << ",";
    
    // Determine account type
    SavingsAccount* savings = dynamic_cast<SavingsAccount*>(account);
    InvestmentAccount* investment = dynamic_cast<InvestmentAccount*>(account);
    CurrencyAccount* currency = dynamic_cast<CurrencyAccount*>(account);
    
    if (savings) {
        json << "\"type\":\"savings\",";
        json << "\"interestRate\":" << (savings->getInterestRate() * 100);
    } else if (investment) {
        json << "\"type\":\"investment\",";
        json << "\"brokerageFee\":" << (investment->getBrokerageFee() * 100) << ",";
        json << "\"holdings\":" << investment->getPortfolio().size() << ",";
        
        // Portfolio details
        json << "\"portfolio\":[";
        const auto& portfolio = investment->getPortfolio();
        bool first = true;
        for (const auto& [ticker, qty] : portfolio) {
            if (!first) json << ",";
            json << "{\"ticker\":\"" << ticker << "\",\"quantity\":" << qty << "}";
            first = false;
        }
        json << "]";
    } else if (currency) {
        json << "\"type\":\"currency\",";
        json << "\"spread\":" << (currency->getSpread() * 100);
    }
    
    json << "}";
    return json.str();
}

std::string WebServer::transactionToJson(Transaction* transaction) const {
    std::ostringstream json;
    json << std::fixed << std::setprecision(2);
    
    json << "{";
    json << "\"id\":" << transaction->getId() << ",";
    json << "\"amount\":" << transaction->getAmount() << ",";
    json << "\"type\":\"" << transaction->getTypeString() << "\",";
    
    // Format date
    std::time_t date = transaction->getDate();
    char dateStr[64];
    std::strftime(dateStr, sizeof(dateStr), "%Y-%m-%d %H:%M:%S", std::localtime(&date));
    json << "\"date\":\"" << dateStr << "\"";
    
    json << "}";
    return json.str();
}

std::string WebServer::bankToJson(BankService* bank) const {
    std::ostringstream json;
    json << std::fixed << std::setprecision(2);
    
    json << "{";
    json << "\"name\":\"" << bank->getBankName() << "\",";
    json << "\"swift\":\"" << bank->getBankSwift() << "\",";
    json << "\"nip\":\"" << bank->getBankNip() << "\",";
    
    Address* addr = bank->getHeadOffice();
    if (addr) {
        json << "\"address\":\"" << addr->toString() << "\",";
    }
    
    json << "\"clientCount\":" << bank->getClients().size() << ",";
    
    // Calculate total balance
    double totalBalance = 0;
    int accountCount = 0;
    for (const auto& client : bank->getClients()) {
        for (const auto& acc : client->getAccounts()) {
            totalBalance += acc->getBalance();
            accountCount++;
        }
    }
    json << "\"totalBalance\":" << totalBalance << ",";
    json << "\"accountCount\":" << accountCount;
    
    json << "}";
    return json.str();
}

std::string WebServer::marketDataToJson() const {
    std::ostringstream json;
    json << std::fixed << std::setprecision(4);
    
    json << "{\"rates\":{";
    json << "\"USD\":" << marketData->getRate(Currency::USD) << ",";
    json << "\"EUR\":" << marketData->getRate(Currency::EUR) << ",";
    json << "\"GBP\":" << marketData->getRate(Currency::GBP) << ",";
    json << "\"CHF\":" << marketData->getRate(Currency::CHF) << ",";
    json << "\"PLN\":" << marketData->getRate(Currency::PLN);
    json << "},\"stocks\":{";
    
    // Common stock tickers
    std::vector<std::string> tickers = {"AAPL", "GOOGL", "MSFT", "AMZN", "TSLA", "META"};
    bool first = true;
    for (const auto& ticker : tickers) {
        double price = marketData->getStockPrice(ticker);
        if (price > 0) {
            if (!first) json << ",";
            json << "\"" << ticker << "\":" << price;
            first = false;
        }
    }
    json << "}}";
    return json.str();
}

// ============================================================================
// Server Control
// ============================================================================

void WebServer::start() {
    if (running) {
        std::cout << "Server already running on port " << port << std::endl;
        return;
    }

    httplib::Server svr;
    
    // Set error handler to see what's happening
    svr.set_error_handler([](const httplib::Request&, httplib::Response& res) {
        std::cerr << "HTTP Error: " << res.status << std::endl;
        res.set_content("Error " + std::to_string(res.status), "text/plain");
    });
    
    // ========================================================================
    // Static file serving
    // ========================================================================
    if (!svr.set_mount_point("/", webRoot)) {
        std::cerr << "ERROR: Could not mount web root directory: " << webRoot << std::endl;
        std::cerr << "Make sure the 'web' folder exists with index.html" << std::endl;
        return;
    }
    std::cout << "Mounted web root: " << webRoot << std::endl;
    
    // ========================================================================
    // API Routes
    // ========================================================================
    
    // GET /api/banks - List all banks
    svr.Get("/api/banks", [this](const httplib::Request&, httplib::Response& res) {
        std::ostringstream json;
        json << "[";
        for (size_t i = 0; i < banks.size(); ++i) {
            if (i > 0) json << ",";
            json << bankToJson(banks[i]);
        }
        json << "]";
        res.set_content(json.str(), "application/json");
    });
    
    // GET /api/banks/:id - Get specific bank
    svr.Get(R"(/api/banks/(\d+))", [this](const httplib::Request& req, httplib::Response& res) {
        size_t bankId = std::stoul(req.matches[1]);
        if (bankId < banks.size()) {
            res.set_content(bankToJson(banks[bankId]), "application/json");
        } else {
            res.status = 404;
            res.set_content("{\"error\":\"Bank not found\"}", "application/json");
        }
    });
    
    // GET /api/clients - List all clients across all banks
    svr.Get("/api/clients", [this](const httplib::Request&, httplib::Response& res) {
        std::ostringstream json;
        json << "[";
        bool first = true;
        for (auto& bank : banks) {
            for (auto& client : bank->getClients()) {
                if (!first) json << ",";
                json << clientToJson(client);
                first = false;
            }
        }
        json << "]";
        res.set_content(json.str(), "application/json");
    });
    
    // GET /api/accounts - List all accounts across all banks
    svr.Get("/api/accounts", [this](const httplib::Request&, httplib::Response& res) {
        std::ostringstream json;
        json << "[";
        bool first = true;
        for (auto& bank : banks) {
            for (auto& client : bank->getClients()) {
                for (auto& account : client->getAccounts()) {
                    if (!first) json << ",";
                    // Add owner info to account JSON
                    std::string accJson = accountToJson(account);
                    // Insert owner name before closing brace
                    std::string ownerName;
                    IndividualClient* ind = dynamic_cast<IndividualClient*>(client);
                    CompanyClient* comp = dynamic_cast<CompanyClient*>(client);
                    if (ind) {
                        ownerName = ind->getFirstName() + " " + ind->getLastName();
                    } else if (comp) {
                        ownerName = comp->getCompanyName();
                    }
                    accJson.pop_back(); // remove }
                    accJson += ",\"owner\":\"" + ownerName + "\",\"bank\":\"" + bank->getBankName() + "\",\"isActive\":" + 
                               (account->getStatus() == AccountStatus::ACTIVE ? "true" : "false") + "}";
                    json << accJson;
                    first = false;
                }
            }
        }
        json << "]";
        res.set_content(json.str(), "application/json");
    });
    
    // GET /api/banks/:id/clients - Get clients of a bank
    svr.Get(R"(/api/banks/(\d+)/clients)", [this](const httplib::Request& req, httplib::Response& res) {
        size_t bankId = std::stoul(req.matches[1]);
        if (bankId < banks.size()) {
            std::ostringstream json;
            json << "[";
            const auto& clients = banks[bankId]->getClients();
            for (size_t i = 0; i < clients.size(); ++i) {
                if (i > 0) json << ",";
                json << clientToJson(clients[i]);
            }
            json << "]";
            res.set_content(json.str(), "application/json");
        } else {
            res.status = 404;
            res.set_content("{\"error\":\"Bank not found\"}", "application/json");
        }
    });
    
    // GET /api/clients/:id/accounts - Get accounts of a client
    svr.Get(R"(/api/clients/(\d+)/accounts)", [this](const httplib::Request& req, httplib::Response& res) {
        int clientId = std::stoi(req.matches[1]);
        
        // Find client across all banks
        Client* foundClient = nullptr;
        for (auto& bank : banks) {
            for (auto& client : bank->getClients()) {
                if (client->getInternalId() == clientId) {
                    foundClient = client;
                    break;
                }
            }
            if (foundClient) break;
        }
        
        if (foundClient) {
            std::ostringstream json;
            json << "[";
            const auto& accounts = foundClient->getAccounts();
            for (size_t i = 0; i < accounts.size(); ++i) {
                if (i > 0) json << ",";
                json << accountToJson(accounts[i]);
            }
            json << "]";
            res.set_content(json.str(), "application/json");
        } else {
            res.status = 404;
            res.set_content("{\"error\":\"Client not found\"}", "application/json");
        }
    });
    
    // GET /api/accounts/:iban - Get specific account
    svr.Get(R"(/api/accounts/([A-Z0-9]+))", [this](const httplib::Request& req, httplib::Response& res) {
        std::string iban = req.matches[1];
        
        // Find account across all banks and clients
        Account* foundAccount = nullptr;
        for (auto& bank : banks) {
            for (auto& client : bank->getClients()) {
                for (auto& account : client->getAccounts()) {
                    if (account->getIban() == iban) {
                        foundAccount = account;
                        break;
                    }
                }
                if (foundAccount) break;
            }
            if (foundAccount) break;
        }
        
        if (foundAccount) {
            res.set_content(accountToJson(foundAccount), "application/json");
        } else {
            res.status = 404;
            res.set_content("{\"error\":\"Account not found\"}", "application/json");
        }
    });
    
    // POST /api/accounts/:iban/deposit - Deposit money
    svr.Post(R"(/api/accounts/([A-Z0-9]+)/deposit)", [this](const httplib::Request& req, httplib::Response& res) {
        std::string iban = req.matches[1];
        
        // Parse amount from body (simple parsing)
        double amount = 0;
        size_t pos = req.body.find("\"amount\":");
        if (pos != std::string::npos) {
            amount = std::stod(req.body.substr(pos + 9));
        }
        
        // Find account
        Account* foundAccount = nullptr;
        for (auto& bank : banks) {
            for (auto& client : bank->getClients()) {
                for (auto& account : client->getAccounts()) {
                    if (account->getIban() == iban) {
                        foundAccount = account;
                        break;
                    }
                }
                if (foundAccount) break;
            }
            if (foundAccount) break;
        }
        
        if (foundAccount && amount > 0) {
            foundAccount->deposit(amount);
            res.set_content("{\"success\":true,\"newBalance\":" + 
                std::to_string(foundAccount->getBalance()) + "}", "application/json");
        } else {
            res.status = 400;
            res.set_content("{\"error\":\"Invalid account or amount\"}", "application/json");
        }
    });
    
    // POST /api/accounts/:iban/withdraw - Withdraw money
    svr.Post(R"(/api/accounts/([A-Z0-9]+)/withdraw)", [this](const httplib::Request& req, httplib::Response& res) {
        std::string iban = req.matches[1];
        
        double amount = 0;
        size_t pos = req.body.find("\"amount\":");
        if (pos != std::string::npos) {
            amount = std::stod(req.body.substr(pos + 9));
        }
        
        // Find account
        Account* foundAccount = nullptr;
        for (auto& bank : banks) {
            for (auto& client : bank->getClients()) {
                for (auto& account : client->getAccounts()) {
                    if (account->getIban() == iban) {
                        foundAccount = account;
                        break;
                    }
                }
                if (foundAccount) break;
            }
            if (foundAccount) break;
        }
        
        if (foundAccount && amount > 0) {
            if (foundAccount->getBalance() >= amount) {
                foundAccount->withdraw(amount);
                res.set_content("{\"success\":true,\"newBalance\":" + 
                    std::to_string(foundAccount->getBalance()) + "}", "application/json");
            } else {
                res.status = 400;
                res.set_content("{\"error\":\"Insufficient funds\"}", "application/json");
            }
        } else {
            res.status = 400;
            res.set_content("{\"error\":\"Invalid account or amount\"}", "application/json");
        }
    });
    
    // POST /api/transfer - Transfer between accounts
    svr.Post("/api/transfer", [this](const httplib::Request& req, httplib::Response& res) {
        // Simple JSON parsing
        std::string fromIban, toIban;
        double amount = 0;
        
        size_t pos = req.body.find("\"from\":\"");
        if (pos != std::string::npos) {
            size_t start = pos + 8;
            size_t end = req.body.find("\"", start);
            fromIban = req.body.substr(start, end - start);
        }
        
        pos = req.body.find("\"to\":\"");
        if (pos != std::string::npos) {
            size_t start = pos + 6;
            size_t end = req.body.find("\"", start);
            toIban = req.body.substr(start, end - start);
        }
        
        pos = req.body.find("\"amount\":");
        if (pos != std::string::npos) {
            amount = std::stod(req.body.substr(pos + 9));
        }
        
        // Find accounts
        Account* fromAccount = nullptr;
        Account* toAccount = nullptr;
        
        for (auto& bank : banks) {
            for (auto& client : bank->getClients()) {
                for (auto& account : client->getAccounts()) {
                    if (account->getIban() == fromIban) fromAccount = account;
                    if (account->getIban() == toIban) toAccount = account;
                }
            }
        }
        
        if (fromAccount && toAccount && amount > 0) {
            static long transferId = 5000;
            Transfer* transfer = new Transfer(transferId++, amount, fromAccount, toAccount);
            
            if (transfer->execute()) {
                if (transactionRepo) {
                    transactionRepo->save(transfer);
                }
                res.set_content("{\"success\":true,\"message\":\"Transfer completed\"}", "application/json");
            } else {
                delete transfer;
                res.status = 400;
                res.set_content("{\"error\":\"Transfer failed - insufficient funds\"}", "application/json");
            }
        } else {
            res.status = 400;
            res.set_content("{\"error\":\"Invalid transfer parameters\"}", "application/json");
        }
    });
    
    // GET /api/market - Get market data
    svr.Get("/api/market", [this](const httplib::Request&, httplib::Response& res) {
        if (marketData) {
            res.set_content(marketDataToJson(), "application/json");
        } else {
            res.status = 500;
            res.set_content("{\"error\":\"Market data not available\"}", "application/json");
        }
    });
    
    // GET /api/transactions - Get all transactions
    svr.Get("/api/transactions", [this](const httplib::Request&, httplib::Response& res) {
        if (transactionRepo) {
            std::ostringstream json;
            json << "[";
            // Get completed transactions (we need a getter for this)
            json << "]";
            res.set_content(json.str(), "application/json");
        } else {
            res.set_content("[]", "application/json");
        }
    });
    
    // GET /api/summary - Get overall system summary
    svr.Get("/api/summary", [this](const httplib::Request&, httplib::Response& res) {
        std::ostringstream json;
        json << std::fixed << std::setprecision(2);
        
        int totalClients = 0;
        int totalAccounts = 0;
        double totalBalance = 0;
        
        for (auto& bank : banks) {
            for (auto& client : bank->getClients()) {
                totalClients++;
                for (auto& account : client->getAccounts()) {
                    totalAccounts++;
                    totalBalance += account->getBalance();
                }
            }
        }
        
        json << "{";
        json << "\"bankCount\":" << banks.size() << ",";
        json << "\"clientCount\":" << totalClients << ",";
        json << "\"accountCount\":" << totalAccounts << ",";
        json << "\"totalBalance\":" << totalBalance;
        json << "}";
        
        res.set_content(json.str(), "application/json");
    });
    
    // ========================================================================
    // Start server
    // ========================================================================
    
    running = true;
    std::cout << "\n";
    std::cout << "======================================================================\n";
    std::cout << "              Banking System Web Server                              \n";
    std::cout << "======================================================================\n";
    std::cout << "  Starting on http://localhost:" << port << " ...\n";
    std::cout << "======================================================================\n";
    std::cout << std::endl;
    std::cout.flush();
    
    // Try to bind first
    if (!svr.bind_to_port("127.0.0.1", port)) {
        std::cerr << "ERROR: Could not bind to port " << port << "!" << std::endl;
        std::cerr << "Port might be in use. Try another port with: --port <number>" << std::endl;
        running = false;
        return;
    }
    std::cout << "Successfully bound to port " << port << std::endl;
    std::cout << "Press Ctrl+C to stop the server" << std::endl;
    std::cout.flush();
    
    // Now listen (this blocks)
    svr.listen_after_bind();
    
    running = false;
}

void WebServer::stop() {
    running = false;
}

bool WebServer::isRunning() const {
    return running;
}

int WebServer::getPort() const {
    return port;
}

std::string WebServer::getWebRoot() const {
    return webRoot;
}
