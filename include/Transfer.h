#ifndef TRANSFER_H
#define TRANSFER_H

#include "Transaction.h"

class Account;

class Transfer : public Transaction {
private:
    Account* sourceAccount;
    Account* destinationAccount;
    std::string sourceIban;
    std::string destinationIban;

public:
    Transfer(const std::string& transactionId, double amount,
             const std::string& description,
             Account* sourceAccount, Account* destinationAccount);
    ~Transfer() override;

    // Override abstract methods
    bool execute() override;
};

#endif // TRANSFER_H