#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>

class Address;
class Account;

class Client {
protected:
    int internalId;
    Address* address;
    std::string phoneNumber;
    std::string email;
    std::vector<Account*> accounts;

public:
    Client(int internalId, Address* address, const std::string& phoneNumber,
           const std::string& email);
    virtual ~Client();

    int getInternalId() const;
    Address* getAddress() const;
    std::string getPhoneNumber() const;
    std::string getEmail() const;
    const std::vector<Account*>& getAccounts() const;

    void setPhoneNumber(const std::string& phone);
    void setEmail(const std::string& email);

    void addAccount(Account* account);
    Account* findAccount(const std::string& iban) const;

    virtual std::string getTaxIdentifier() const = 0;
    virtual std::string toString() const = 0;
};

#endif
