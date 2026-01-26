#include "DataPersistence.h"
#include "BankService.h"
#include "Client.h"
#include "Account.h"
#include "Address.h"
#include "IndividualClient.h"
#include "CompanyClient.h"
#include "Currency.h"

#include <iostream>
#include <iomanip>
#include <ctime>
#include <filesystem>

namespace fs = std::filesystem;

DataPersistence::DataPersistence(const std::string& directory)
    : dataDirectory(directory) {
    ensureDirectoryExists();
}

DataPersistence::~DataPersistence() {}

bool DataPersistence::ensureDirectoryExists() const {
    try {
        if (!fs::exists(dataDirectory)) {
            fs::create_directories(dataDirectory);
        }
        return true;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error creating directory: " << e.what() << std::endl;
        return false;
    }
}

std::string DataPersistence::getFullPath(const std::string& filename) const {
    return dataDirectory + "/" + filename;
}

bool DataPersistence::fileExists(const std::string& filename) const {
    return fs::exists(getFullPath(filename));
}

bool DataPersistence::saveBank(BankService* bank, const std::string& filename) const {
    if (!bank) return false;

    std::ofstream file(getFullPath(filename));
    if (!file.is_open()) {
        std::cerr << "Cannot open file for writing: " << filename << std::endl;
        return false;
    }

    file << "# Bank data - auto generated\n";
    file << "# Save date: ";
    
    auto now = std::time(nullptr);
    file << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S") << "\n\n";

    file << "[BANK]\n";
    file << "name=" << bank->getBankName() << "\n";
    file << "swift=" << bank->getBankSwift() << "\n";
    file << "nip=" << bank->getBankNip() << "\n";

    Address* addr = bank->getHeadOffice();
    if (addr) {
        file << "\n[ADDRESS]\n";
        file << "street=" << addr->getStreet() << "\n";
        file << "houseNumber=" << addr->getHouseNumber() << "\n";
        file << "city=" << addr->getCity() << "\n";
        file << "zipCode=" << addr->getZipCode() << "\n";
        file << "country=" << addr->getCountry() << "\n";
    }

    const auto& clients = bank->getClients();
    file << "\n[CLIENTS]\n";
    file << "count=" << clients.size() << "\n";

    int clientIndex = 0;
    for (const auto& client : clients) {
        file << "\n[CLIENT_" << clientIndex++ << "]\n";
        file << "id=" << client->getInternalId() << "\n";
        file << "phone=" << client->getPhoneNumber() << "\n";
        file << "email=" << client->getEmail() << "\n";
        file << "taxId=" << client->getTaxIdentifier() << "\n";

        IndividualClient* individual = dynamic_cast<IndividualClient*>(client);
        CompanyClient* company = dynamic_cast<CompanyClient*>(client);

        if (individual) {
            file << "type=individual\n";
            file << "firstName=" << individual->getFirstName() << "\n";
            file << "lastName=" << individual->getLastName() << "\n";
            file << "pesel=" << individual->getPesel() << "\n";
        } else if (company) {
            file << "type=company\n";
            file << "companyName=" << company->getCompanyName() << "\n";
            file << "nip=" << company->getNip() << "\n";
            file << "regon=" << company->getRegon() << "\n";
            file << "krs=" << company->getKrs() << "\n";
        }

        const auto& accounts = client->getAccounts();
        file << "accountsCount=" << accounts.size() << "\n";
        
        int accIndex = 0;
        for (const auto& account : accounts) {
            file << "account_" << accIndex << "_iban=" << account->getIban() << "\n";
            file << "account_" << accIndex << "_balance=" << std::fixed 
                 << std::setprecision(2) << account->getBalance() << "\n";
            file << "account_" << accIndex << "_currency=" 
                 << currencyToString(account->getCurrency()) << "\n";
            file << "account_" << accIndex << "_date=" << account->getCreationDate() << "\n";
            accIndex++;
        }
    }

    file.close();
    std::cout << "Saved bank data to: " << getFullPath(filename) << std::endl;
    return true;
}

bool DataPersistence::saveClients(const std::vector<Client*>& clients, const std::string& filename) const {
    std::ofstream file(getFullPath(filename));
    if (!file.is_open()) {
        return false;
    }

    file << "# Client list\n";
    file << "count=" << clients.size() << "\n\n";

    for (const auto& client : clients) {
        file << client->toString() << "\n";
    }

    file.close();
    return true;
}

bool DataPersistence::saveAccount(Account* account, const std::string& filename) const {
    if (!account) return false;

    std::ofstream file(getFullPath(filename));
    if (!file.is_open()) {
        return false;
    }

    file << "iban=" << account->getIban() << "\n";
    file << "balance=" << std::fixed << std::setprecision(2) << account->getBalance() << "\n";
    file << "currency=" << currencyToString(account->getCurrency()) << "\n";
    file << "status=" << static_cast<int>(account->getStatus()) << "\n";
    file << "creationDate=" << account->getCreationDate() << "\n";

    file.close();
    return true;
}

std::string DataPersistence::loadFromFile(const std::string& filename) const {
    std::ifstream file(getFullPath(filename));
    if (!file.is_open()) {
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}
