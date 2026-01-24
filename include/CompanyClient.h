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
    CompanyClient(int internalId, Address* address,
                  const std::string& phoneNumber, const std::string& email,
                  const std::string& companyName, const std::string& nip,
                  const std::string& regon, const std::string& krs);
    ~CompanyClient() override;

    // Getters
    std::string getCompanyName() const;
    std::string getNip() const;
    std::string getRegon() const;
    std::string getKrs() const;

    // Setters
    void setCompanyName(const std::string& companyName);
    void setNip(const std::string& nip);
    void setRegon(const std::string& regon);
    void setKrs(const std::string& krs);

    // Override abstract methods
    std::string getTaxIdentifier() const override;
    std::string toString() const override;
};

#endif // COMPANYCLIENT_H
