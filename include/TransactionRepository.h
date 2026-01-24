#ifndef TRANSACTIONREPOSITORY_H
#define TRANSACTIONREPOSITORY_H

#include <vector>
#include <queue>
#include <string>

class Transaction;
class Account;

class TransactionRepository {
private:
    std::vector<Transaction*> completedTransactions;
    std::queue<Transaction*> pendingTransactions;

public:
    TransactionRepository();
    ~TransactionRepository();

    // Repository operations (UML methods)
    void save(Transaction* transaction);
    std::vector<Transaction*> getHistory(Account* account) const;
    std::queue<Transaction*> getPending() const;

    // Completed transactions (list)
    void addCompletedTransaction(Transaction* transaction);
    const std::vector<Transaction*>& getCompletedTransactions() const;
    size_t getCompletedCount() const;

    // Pending transactions (queue)
    void addPendingTransaction(Transaction* transaction);
    Transaction* getNextPendingTransaction();
    bool hasPendingTransactions() const;
    size_t getPendingCount() const;

    // Utility
    std::string toString() const;
};

#endif // TRANSACTIONREPOSITORY_H
