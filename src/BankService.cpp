#include "BankService.h"
#include "Client.h"
#include "SavingsAccount.h"
#include "InvestmentAccount.h"
#include "CurrencyAccount.h"
#include "Transfer.h"
#include "CurrencyExchange.h"
#include "StockOperation.h"
#include "Exceptions.h"
#include <sstream>
#include <iomanip>
#include <ctime>

BankService::BankService(const std::string& bankName, const std::string& bankSwift,
                         const std::string& bankNip, AddressPtr headOffice)
    : bankName(bankName), bankSwift(bankSwift), bankNip(bankNip),
      headOffice(headOffice), nextTransactionId(1) {}

BankService::~BankService() {}

std::string BankService::getBankName() const { return bankName; }
std::string BankService::getBankSwift() const { return bankSwift; }
std::string BankService::getBankNip() const { return bankNip; }
AddressPtr BankService::getHeadOffice() const { return headOffice; }

ClientRepository& BankService::getClientRepository() { return clientRepo; }
TransactionRepository& BankService::getTransactionRepository() { return transactionRepo; }
MarketDataService& BankService::getMarketDataService() { return marketData; }

void BankService::registerClient(ClientPtr client) {
    if (!client) throw ValidationException("Cannot register null client");
    clientRepo.add(client);
}

AccountPtr BankService::createAccount(ClientPtr client, const std::string& accountType,
                                      double initialBalance, Currency currency) {
    if (!client) throw ValidationException("Client cannot be null");
    if (initialBalance < 0) throw ValidationException("Initial balance cannot be negative");

    auto now = std::time(nullptr);
    std::ostringstream dateOss;
    dateOss << std::put_time(std::localtime(&now), "%Y-%m-%d");
    
    static int ibanCounter = 10000000;
    std::ostringstream ibanOss;
    ibanOss << "PL" << std::setfill('0') << std::setw(26) << ibanCounter++;

    AccountPtr account;

    if (accountType == "Savings") {
        account = std::make_shared<SavingsAccount>(ibanOss.str(), initialBalance, currency, dateOss.str());
    } else if (accountType == "Investment") {
        account = std::make_shared<InvestmentAccount>(ibanOss.str(), initialBalance, currency, dateOss.str());
    } else if (accountType == "Currency") {
        account = std::make_shared<CurrencyAccount>(ibanOss.str(), initialBalance, currency, dateOss.str());
    } else {
        throw ValidationException("Unknown account type: " + accountType);
    }

    client->addAccount(account);
    return account;
}

void BankService::executeTransfer(AccountPtr from, AccountPtr to, double amount) {
    auto transfer = std::make_shared<Transfer>(nextTransactionId++, amount, from, to);
    transfer->execute();
    transactionRepo.add(transfer);
}

void BankService::executeCurrencyExchange(CurrencyAccountPtr source, CurrencyAccountPtr target, double amount) {
    double rate = marketData.getExchangeRate(source->getCurrency(), target->getCurrency());
    auto exchange = std::make_shared<CurrencyExchange>(nextTransactionId++, source, target, amount, rate);
    exchange->execute();
    transactionRepo.add(exchange);
}

void BankService::executeStockOperation(InvestmentAccountPtr account, const std::string& ticker, int quantity, bool isBuy) {
    double price = marketData.getStockQuote(ticker).price;
    auto operation = std::make_shared<StockOperation>(nextTransactionId++, account, ticker, quantity, price, isBuy);
    operation->execute();
    transactionRepo.add(operation);
}

void BankService::processSession() {
    for (const auto& client : clientRepo.getAll()) {
        if (client) {
            for (const auto& account : client->getAccounts()) {
                if (account && account->getStatus() == AccountStatus::ACTIVE) {
                    double fee = account->calculateMonthlyFees();
                    if (fee > 0 && account->getBalance() >= fee) {
                        try { account->withdraw(fee); } catch (...) {}
                    }
                }
            }
        }
    }
}

std::string BankService::toString() const {
    std::ostringstream oss;
    oss << "BankService[name=" << bankName
        << ", clients=" << clientRepo.count()
        << ", transactions=" << transactionRepo.count() << "]";
    return oss.str();
}
