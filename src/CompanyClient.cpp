#include "CompanyClient.h"
#include "Account.h"
#include <sstream>

CompanyClient::CompanyClient(int internalId, Address* address,
                             const std::string& phoneNumber, const std::string& email,
                             const std::string& companyName, const std::string& nip,
                             const std::string& regon, const std::string& krs)
    : Client(internalId, address, phoneNumber, email),
      companyName(companyName), nip(nip), regon(regon), krs(krs) {}

CompanyClient::~CompanyClient() {}

std::string CompanyClient::getCompanyName() const {
    return companyName;
}

std::string CompanyClient::getNip() const {
    return nip;
}

std::string CompanyClient::getRegon() const {
    return regon;
}

std::string CompanyClient::getKrs() const {
    return krs;
}

void CompanyClient::setCompanyName(const std::string& companyName) {
    this->companyName = companyName;
}

void CompanyClient::setNip(const std::string& nip) {
    this->nip = nip;
}

void CompanyClient::setRegon(const std::string& regon) {
    this->regon = regon;
}

void CompanyClient::setKrs(const std::string& krs) {
    this->krs = krs;
}

std::string CompanyClient::getTaxIdentifier() const {
    return nip;
}

std::string CompanyClient::toString() const {
    std::ostringstream oss;
    oss << "CompanyClient[id=" << internalId
        << ", name=" << companyName
        << ", nip=" << nip
        << ", regon=" << regon
        << ", krs=" << krs
        << ", email=" << email
        << ", phone=" << phoneNumber
        << ", address=" << (address ? address->toString() : "N/A")
        << ", accountsCount=" << accounts.size() << "]";
    return oss.str();
}
