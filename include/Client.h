#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "Address.h"

class Client {
protected:
    int internalId;
    Address* address;
    std::string phoneNumber;
    std::string email;

public:
    Client(const int& internalId, Address* address);
    virtual ~Client();

    // Abstract method
    virtual std::string getTaxIdentifier() const = 0;
};

#endif // CLIENT_H