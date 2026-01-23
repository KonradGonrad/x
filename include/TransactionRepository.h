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

    // Core methods from UML
    void save(Transaction* t);
    std::vector<Transaction*> getHistory(Account* acc) const;
    std::queue<Transaction*> getPending() const;
};

#endif // TRANSACTIONREPOSITORY_H