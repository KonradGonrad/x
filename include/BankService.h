#ifndef BANKSERVICE_H
#define BANKSERVICE_H

#include <vector>
#include <string>
#include "Currency.h"

class Client;
class Account;
class Transaction;
class TransactionRepository;
class MarketDataService;
class Address;

class BankService {
public:
    BankService(const std::string& bankName, const std::string& bankSwift,
                const std::string& bankNip, AddressPtr headOffice);
    ~BankService();

    std::string getBankName() const;
    std::string getBankSwift() const;
    std::string getBankNip() const;
    AddressPtr getHeadOffice() const;
    
    ClientRepository& getClientRepository();
    const ClientRepository& getClientRepository() const;

    // Core methods
     void registerClient(ClientPtr client);
    AccountPtr createAccount(ClientPtr client, const std::string& accountType,
                            double initialBalance, Currency currency);
    void processSession();
    std::string toString() const;
    
private:
    std::string bankName;
    std::string bankSwift;
    std::string bankNip;
    AddressPtr headOffice;
    ClientRepository clientRepo;
};

using BankServicePtr = std::shared_ptr<BankService>;

#endif // BANKSERVICE_H