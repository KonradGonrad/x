#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Account;  // Forward declaration

class Transaction {
private:
    int id;
    DateTime date;
    double amount;
    TransactionType type;

public:
    Transaction(const std::string& transactionId, double amount,
                const std::string& description);
    virtual ~Transaction();

    // Getters
    std::string getTransactionId() const;
    std::string getTimestamp() const;
    double getAmount() const;
    std::string getStatus() const;
    std::string getDescription() const;

    // Setters
    void setStatus(const std::string& status);
    void setTimestamp(const std::string& timestamp);

    // Abstract methods
    virtual bool execute() = 0;
    virtual std::string getTransactionType() const = 0;
    virtual std::string toString() const = 0;
};

#endif // TRANSACTION_H