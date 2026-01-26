#include "TransactionRepository.h"
#include "Transaction.h"
#include "Account.h"
#include <sstream>

TransactionRepository::TransactionRepository() {}

TransactionRepository::~TransactionRepository() {
    for (Transaction* tx : completedTransactions) {
        delete tx;
    }
    completedTransactions.clear();
    while (!pendingTransactions.empty()) {
        delete pendingTransactions.front();
        pendingTransactions.pop();
    }
}

void TransactionRepository::save(Transaction* transaction) {
    if (transaction != nullptr) {
        completedTransactions.push_back(transaction);
    }
}

std::vector<Transaction*> TransactionRepository::getHistory(Account* account) const {
    return completedTransactions;
}

std::queue<Transaction*> TransactionRepository::getPending() const {
    return pendingTransactions;
}

void TransactionRepository::addPendingTransaction(Transaction* transaction) {
    if (transaction != nullptr) {
        pendingTransactions.push(transaction);
    }
}

Transaction* TransactionRepository::getNextPendingTransaction() {
    if (pendingTransactions.empty()) {
        return nullptr;
    }
    Transaction* tx = pendingTransactions.front();
    pendingTransactions.pop();
    return tx;
}

bool TransactionRepository::hasPendingTransactions() const {
    return !pendingTransactions.empty();
}

size_t TransactionRepository::getPendingCount() const {
    return pendingTransactions.size();
}

void TransactionRepository::addCompletedTransaction(Transaction* transaction) {
    if (transaction != nullptr) {
        completedTransactions.push_back(transaction);
    }
}

const std::vector<Transaction*>& TransactionRepository::getCompletedTransactions() const {
    return completedTransactions;
}

size_t TransactionRepository::getCompletedCount() const {
    return completedTransactions.size();
}

std::string TransactionRepository::toString() const {
    std::ostringstream oss;
    oss << "TransactionRepository[pending=" << pendingTransactions.size()
        << ", completed=" << completedTransactions.size() << "]";
    return oss.str();
}
