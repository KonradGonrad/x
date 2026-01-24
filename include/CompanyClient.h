#ifndef COMPANY_CLIENT_H
#define COMPANY_CLIENT_H

#include "Client.h"

class CompanyClient : public Client {
public:
    CompanyClient(int internalId, AddressPtr address,
                  const std::string& phoneNumber, const std::string& email,
                  const std::string& companyName, const std::string& nip,
                  const std::string& regon, const std::string& krs);
    ~CompanyClient() override;

    std::string getCompanyName() const;
    std::string getNip() const;
    std::string getRegon() const;
    std::string getKrs() const;

    std::string getTaxIdentifier() const override;
    std::string toString() const override;

private:
    std::string companyName, nip, regon, krs;
};

using CompanyClientPtr = std::shared_ptr<CompanyClient>;

#endif