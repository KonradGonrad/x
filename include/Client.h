#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include <memory>
#include "Account.h"
#include "Address.h"

class Client {
public:
    Client(int internalId, AddressPtr address, const std::string& phoneNumber,
           const std::string& email);
    virtual ~Client();

    int getInternalId() const;
    AddressPtr getAddress() const;
    std::string getPhoneNumber() const;
    std::string getEmail() const;
    const std::vector<AccountPtr>& getAccounts() const;

    void setPhoneNumber(const std::string& phone);
    void setEmail(const std::string& email);

    void addAccount(AccountPtr account);
    AccountPtr findAccount(const std::string& iban) const;
     // Abstract method
    virtual std::string getTaxIdentifier() const = 0;
    virtual std::string toString() const = 0;

private:
    int internalId;
    AddressPtr address;
    std::string phoneNumber;
    std::string email;
    std::vector<AccountPtr> accounts;
};

using ClientPtr = std::shared_ptr<Client>;

#endif // CLIENT_H
