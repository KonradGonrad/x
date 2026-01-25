#ifndef BANK_SERVICE_H
#define BANK_SERVICE_H

#include <string>
#include <memory>
#include "Currency.h"
#include "Address.h"
#include "ClientRepository.h"
#include "TransactionRepository.h"
#include "MarketDataService.h"
#include "CurrencyAccount.h"
#include "InvestmentAccount.h"

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
    TransactionRepository& getTransactionRepository();
    MarketDataService& getMarketDataService();

    void registerClient(ClientPtr client);
    AccountPtr createAccount(ClientPtr client, const std::string& accountType,
                            double initialBalance, Currency currency);

    void executeTransfer(AccountPtr from, AccountPtr to, double amount);
    void executeCurrencyExchange(CurrencyAccountPtr source, CurrencyAccountPtr target, double amount);
    void executeStockOperation(InvestmentAccountPtr account, const std::string& ticker, int quantity, bool isBuy);

    void processSession();
    std::string toString() const;

private:
    std::string bankName, bankSwift, bankNip;
    AddressPtr headOffice;
    ClientRepository clientRepo;
    TransactionRepository transactionRepo;
    MarketDataService marketData;
    long nextTransactionId;
};

using BankServicePtr = std::shared_ptr<BankService>;

#endif
