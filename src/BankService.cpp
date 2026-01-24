#include "BankService.h"
#include "Client.h"
#include "SavingsAccount.h"
#include "InvestmentAccount.h"
#include "CurrencyAccount.h"
#include "Exceptions.h"
#include <sstream>
#include <iomanip>
#include <ctime>

BankService::BankService(const std::string& bankName, const std::string& bankSwift,
                         const std::string& bankNip, AddressPtr headOffice)
    : bankName(bankName), bankSwift(bankSwift), bankNip(bankNip),
      headOffice(headOffice) {}

BankService::~BankService() {}

std::string BankService::getBankName() const { return bankName; }
std::string BankService::getBankSwift() const { return bankSwift; }
std::string BankService::getBankNip() const { return bankNip; }
AddressPtr BankService::getHeadOffice() const { return headOffice; }

ClientRepository& BankService::getClientRepository() { return clientRepo; }
const ClientRepository& BankService::getClientRepository() const { return clientRepo; }

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
    oss << "BankService[name=" << bankName << ", clients=" << clientRepo.count() << "]";
    return oss.str();
}
