#ifndef TRANSFER_H
#define TRANSFER_H

#include "Transaction.h"
#include "Account.h"

class Transfer : public Transaction {
public:
    Transfer(long id, double amount, AccountPtr sender, AccountPtr receiver);
    ~Transfer() override;

    AccountPtr getSender() const;
    AccountPtr getReceiver() const;

    void execute();
    std::string toString() const override;

private:
    AccountPtr sender;
    AccountPtr receiver;
};

using TransferPtr = std::shared_ptr<Transfer>;

#endif
