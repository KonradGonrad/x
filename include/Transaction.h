#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "DateTime.h"

class Account;  // Forward declaration


class Transaction {
protected:  // ZMIANA: private -> protected
    long id;
    std::time_t date;
    double amount;
    TransactionType type;

public:
    Transaction(long id, double amount, TransactionType type);
    virtual ~Transaction();

    long getId() const;
    std::time_t getDate() const;
    double getAmount() const;
    TransactionType getType() const;
    std::string getTypeString() const;

    virtual bool execute() = 0;
    virtual std::string toString() const = 0;
};

#endif // TRANSACTION_H