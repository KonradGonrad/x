#ifndef BANKSERVICE_H
#define BANKSERVICE_H

#include <vector>
#include <string>

class Client;
class Account;
class Transaction;
class TransactionRepository;
class MarketDataService;
class Address;

class BankService {
private:
    std::string bankName;
    std::string bankSwift;
    std::string bankNip;
    Address* headOffice;

public:
    BankService();
    ~BankService();

    // Core methods
    void registerClient(Client* c);
    Account* createAccount(Client* c, const std::string& type);
    void processSession();
};

#endif // BANKSERVICE_H