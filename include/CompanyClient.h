#ifndef COMPANYCLIENT_H
#define COMPANYCLIENT_H

#include "Client.h"
#include <string>

class CompanyClient : public Client {
private:
    std::string nip;  // Polish tax ID number
    std::string regon;  // Polish statistical number
    std::string companyName;  // e.g., "LLC", "SA", "SP"
    std::string krs;  // National Court Register number


public:
    CompanyClient(int internalId, Address* address,
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
};

#endif // COMPANYCLIENT_H