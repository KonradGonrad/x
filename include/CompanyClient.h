#ifndef COMPANYCLIENT_H
#define COMPANYCLIENT_H

#include "Client.h"
#include <string>

class CompanyClient : public Client {
private:
    std::string companyName;
    std::string nip;
    std::string regon;
    std::string krs;

public:
    CompanyClient(const int& internalId, Address* address,
                  const std::string& companyName, const std::string& nip,
                  const std::string& regon, const std::string& krs);
    ~CompanyClient() override;

    // Override abstract method
    std::string getTaxIdentifier() const override;
};

#endif // COMPANYCLIENT_H
