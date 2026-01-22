#ifndef BANKSERVICE_H
#define BANKSERVICE_H

#include <vector>
#include <string>

class Client;
class Account;
class Transaction;
class TransactionRepository;
class MarketDataService;

class BankService {
private:
    std::vector<Client*> clients;
    TransactionRepository* transactionRepository;
    MarketDataService* marketDataService;
    int nextClientId;
    int nextTransactionId;

    // Helper methods
    std::string generateClientId();
    std::string generateTransactionId();
    std::string generateIban();

public:
    BankService();
    ~BankService();

    // Client management
    bool registerClient(Client* client);
    bool removeClient(const std::string& clientId);
    Client* findClient(const std::string& clientId) const;
    const std::vector<Client*>& getAllClients() const;

    // Account management
    Account* createSavingsAccount(const std::string& clientId, double initialBalance,
                                  const std::string& currency, double interestRate);
    Account* createInvestmentAccount(const std::string& clientId, double initialBalance,
                                     const std::string& currency);
    Account* createCurrencyAccount(const std::string& clientId, double initialBalance,
                                   const std::string& currency);
    Account* findAccount(const std::string& iban) const;

    // Transaction management
    bool createTransfer(const std::string& sourceIban, const std::string& destIban,
                        double amount, const std::string& description);
    bool createStockOperation(const std::string& accountIban, const std::string& symbol,
                              int quantity, bool isBuy);
    bool createCurrencyExchange(const std::string& sourceIban, const std::string& destIban,
                                double amount);

    // Processing
    int processPendingTransactions();

    // Services access
    TransactionRepository* getTransactionRepository() const;
    MarketDataService* getMarketDataService() const;

    // Validation
    bool validateIban(const std::string& iban) const;
    bool validateClientId(const std::string& clientId) const;

    std::string toString() const;
};

#endif // BANKSERVICE_H