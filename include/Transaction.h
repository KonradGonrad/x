#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>
#include <memory>

enum class TransactionType {
    DEPOSIT, WITHDRAWAL, TRANSFER, STOCK_PURCHASE, STOCK_SALE, CURRENCY_EXCHANGE
};

class Transaction {
public:
    Transaction(long id, double amount, TransactionType type);
    virtual ~Transaction();

    long getId() const;
    std::time_t getDate() const;
    double getAmount() const;
    TransactionType getType() const;
    std::string getTypeString() const;

protected:
    long id;
    std::time_t date;
    double amount;
    TransactionType type;
};

using TransactionPtr = std::shared_ptr<Transaction>;

#endif // TRANSACTION_H