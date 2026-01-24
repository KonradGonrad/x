#ifndef TRANSACTION_REPOSITORY_H
#define TRANSACTION_REPOSITORY_H

#include "Repository.h"
#include "Transaction.h"
#include <vector>

class TransactionRepository : public Repository<Transaction, long> {
public:
    std::vector<TransactionPtr> findByType(TransactionType type) const;
    std::vector<TransactionPtr> findByDateRange(std::time_t from, std::time_t to) const;
    std::vector<TransactionPtr> findByAmountRange(double minAmount, double maxAmount) const;
    double getTotalAmount() const;
    double getTotalAmountByType(TransactionType type) const;

private:
    long getKey(const TransactionPtr& item) const override {
        return item->getId();
    }
};

using TransactionRepositoryPtr = std::shared_ptr<TransactionRepository>;

#endif // TRANSACTIONREPOSITORY_H