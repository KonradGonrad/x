#include "CompanyClient.h"
#include "Address.h"
#include <sstream>

CompanyClient::CompanyClient(int internalId, Address* address,
                             const std::string& phoneNumber,
                             const std::string& email,
                             const std::string& companyName,
                             const std::string& nip,
                             const std::string& regon,
                             const std::string& krs)
    : Client(internalId, address, phoneNumber, email),
      companyName(companyName), nip(nip), regon(regon), krs(krs) {}

CompanyClient::~CompanyClient() {}

std::string CompanyClient::getCompanyName() const { return companyName; }
std::string CompanyClient::getNip() const { return nip; }
std::string CompanyClient::getRegon() const { return regon; }
std::string CompanyClient::getKrs() const { return krs; }

std::string CompanyClient::getTaxIdentifier() const {
    return nip;
}

std::string CompanyClient::toString() const {
    std::ostringstream oss;
    oss << "CompanyClient[id=" << internalId
        << ", name=" << companyName
        << ", nip=" << nip
        << ", accounts=" << accounts.size() << "]";
    return oss.str();
}
