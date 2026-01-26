#include "BankService.h"
#include "Client.h"
#include "Account.h"
#include "SavingsAccount.h"
#include "InvestmentAccount.h"
#include "CurrencyAccount.h"
#include "Address.h"

#include <sstream>
#include <iomanip>
#include <ctime>
#include <algorithm>

BankService::BankService(const std::string& bankName, const std::string& bankSwift,
                         const std::string& bankNip, Address* headOffice)
    : bankName(bankName), bankSwift(bankSwift), bankNip(bankNip), headOffice(headOffice) {}

BankService::~BankService() {
    for (auto* client : clients) {
        delete client;
    }
    clients.clear();
    delete headOffice;
}

std::string BankService::getBankName() const {
    return bankName;
}

std::string BankService::getBankSwift() const {
    return bankSwift;
}

std::string BankService::getBankNip() const {
    return bankNip;
}

Address* BankService::getHeadOffice() const {
    return headOffice;
}

const ClientList& BankService::getClients() const {
    return clients;
}

void BankService::registerClient(Client* client) {
    if (client != nullptr) {
        clients.push_back(client);
    }
}

Account* BankService::createAccount(Client* client, const std::string& accountType,
                                    double initialBalance, Currency currency) {
    if (!client || initialBalance < 0) {
        return nullptr;
    }

    auto now = std::time(nullptr);
    std::ostringstream dateOss;
    dateOss << std::put_time(std::localtime(&now), "%Y-%m-%d");
    std::string creationDate = dateOss.str();

    static int ibanCounter = 10000000;
    std::ostringstream ibanOss;
    ibanOss << "PL" << std::setfill('0') << std::setw(26) << ibanCounter++;
    std::string iban = ibanOss.str();

    Account* account = nullptr;

    if (accountType == "Savings") {
        account = new SavingsAccount(iban, initialBalance, currency, creationDate, 0.03);
    } else if (accountType == "Investment") {
        account = new InvestmentAccount(iban, initialBalance, currency, creationDate, 0.02);
    } else if (accountType == "Currency") {
        account = new CurrencyAccount(iban, initialBalance, currency, creationDate, 0.005);
    }

    if (account != nullptr) {
        client->addAccount(account);
    }

    return account;
}

void BankService::processSession() {
    for (Client* client : clients) {
        if (client != nullptr) {
            for (Account* account : client->getAccounts()) {
                if (account != nullptr && account->getStatus() == AccountStatus::ACTIVE) {
                    double fee = account->calculateMonthlyFees();
                    if (fee > 0 && account->getBalance() >= fee) {
                        account->withdraw(fee);
                    }
                }
            }
        }
    }
}

std::string BankService::toString() const {
    std::ostringstream oss;
    oss << "BankService[name=" << bankName
        << ", swift=" << bankSwift
        << ", nip=" << bankNip
        << ", clients=" << clients.size()
        << ", headOffice=" << (headOffice ? headOffice->toString() : "N/A") << "]";
    return oss.str();
}
