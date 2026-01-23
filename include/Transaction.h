#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "DateTime.h"

class Account;  // Forward declaration


class Transaction {
private:
    int id;
    DateTime date;
    double amount;
public:
    Transaction(const std::string& transactionId, double amount,
                const std::string& description);
    virtual ~Transaction();

    // Abstract methods
    virtual bool execute() = 0;
};

#endif // TRANSACTION_H