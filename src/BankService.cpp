#include "BankService.h"
#include "Client.h"
#include "Account.h"
#include "SavingsAccount.h"
#include "Address.h"
#include <sstream>
#include <iomanip>
#include <ctime>

BankService::BankService(const std::string& bankName, const std::string& bankSwift,
                         Address* headOffice)
    : bankName(bankName), bankSwift(bankSwift), headOffice(headOffice) {}

BankService::~BankService() {
    for (Client* client : clients) {
        delete client;
    }
    clients.clear();
    delete headOffice;
}

std::string BankService::getBankName() const { return bankName; }
std::string BankService::getBankSwift() const { return bankSwift; }
Address* BankService::getHeadOffice() const { return headOffice; }
const std::vector<Client*>& BankService::getClients() const { return clients; }

void BankService::registerClient(Client* client) {
    if (client != nullptr) {
        clients.push_back(client);
    }
}

Account* BankService::createAccount(Client* client, const std::string& accountType,
                                    double initialBalance, Currency currency) {
    if (client == nullptr || initialBalance < 0) {
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
        account = new SavingsAccount(iban, initialBalance, currency, creationDate);
    }

    if (account != nullptr) {
        client->addAccount(account);
    }

    return account;
}

std::string BankService::toString() const {
    std::ostringstream oss;
    oss << "BankService[name=" << bankName
        << ", swift=" << bankSwift
        << ", clients=" << clients.size() << "]";
    return oss.str();
}
