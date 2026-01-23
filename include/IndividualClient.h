#ifndef INDIVIDUALCLIENT_H
#define INDIVIDUALCLIENT_H

#include "Client.h"
#include <string>

class IndividualClient : public Client {
private:
    std::string firstName;
    std::string lastName;
    std::string pesel;

public:
    IndividualClient(const int& internalId, Address* address,
                     const std::string& firstName, const std::string& lastName,
                     const std::string& pesel);
    ~IndividualClient() override;

    // Override abstract method
    std::string getTaxIdentifier() const override;
};

#endif // INDIVIDUALCLIENT_H
