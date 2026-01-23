#ifndef TRANSFER_H
#define TRANSFER_H

#include "Transaction.h"

class Account;

class Transfer : public Transaction {
private:
    Account* sender;
    Account* receiver;

public:
     Transfer(long id, double amount, Account* sender, Account* receiver);
    ~Transfer() override;

    Account* getSender() const;
    Account* getReceiver() const;

    // Override abstract methods
    bool execute() override;
    std::string toString() const override;
};

#endif // TRANSFER_H