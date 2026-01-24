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
    IndividualClient(int internalId, Address* address,
                     const std::string& phoneNumber, const std::string& email,
                     const std::string& firstName, const std::string& lastName,
                     const std::string& pesel);
    ~IndividualClient() override;

    // Getters
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getPesel() const;

    // Setters
    void setFirstName(const std::string& firstName);
    void setLastName(const std::string& lastName);
    void setPesel(const std::string& pesel);

    // Override abstract methods
    std::string getTaxIdentifier() const override;
    std::string toString() const override;
};

#endif // INDIVIDUALCLIENT_H
