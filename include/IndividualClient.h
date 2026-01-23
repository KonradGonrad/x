#ifndef INDIVIDUALCLIENT_H
#define INDIVIDUALCLIENT_H

#include "Client.h"

class IndividualClient : public Client {
private:
    std::string firstName;
    std::string lastName;
    std::string pesel;

public:
    IndividualClient(int internalId, Address* address,
                     const std::string& phoneNumber, const std::string& email,
                     const std::string& firstName, const std::string& lastName,
                     const std::string& pesel);
    ~IndividualClient() override;

    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getPesel() const;

    std::string getTaxIdentifier() const override;
    std::string toString() const override;
};

#endif
