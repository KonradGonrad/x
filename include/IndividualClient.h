#ifndef INDIVIDUAL_CLIENT_H
#define INDIVIDUAL_CLIENT_H

#include "Client.h"

class IndividualClient : public Client {
public:
    IndividualClient(int internalId, AddressPtr address,
                     const std::string& phoneNumber, const std::string& email,
                     const std::string& firstName, const std::string& lastName,
                     const std::string& pesel);
    ~IndividualClient() override;

    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getPesel() const;

    std::string getTaxIdentifier() const override;
    std::string toString() const override;

private:
    std::string firstName, lastName, pesel;
};

using IndividualClientPtr = std::shared_ptr<IndividualClient>;

#endif
