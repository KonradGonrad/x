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
    CompanyClient(const int& clientId, const std::string& name,
                  Address* address, const std::string& nip,
                  const std::string& regon, const std::string& companyName,
                  const std::string& krs);
    ~CompanyClient() override;


    // Override abstract methods
    std::string getClientType() const override;
    double calculateTotalFees() const override;
    std::string toString() const override;
};

#endif // COMPANYCLIENT_H