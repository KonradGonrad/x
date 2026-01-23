#ifndef TRANSFER_H
#define TRANSFER_H

#include "Transaction.h"

class Account;

class Transfer : public Transaction {
private:
    Account* sender;
    Account* receiver;

public:
    Transfer(const std::string& transactionId, double amount,
             const std::string& description,
             Account* sender, Account* receiver);
    ~Transfer() override;

    // Override abstract methods
    bool execute() override;
};

#endif // TRANSFER_H