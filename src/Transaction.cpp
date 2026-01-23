#include "Transaction.h"

Transaction::Transaction(long id, double amount, TransactionType type)
    : id(id), amount(amount), type(type) {
    date = std::time(nullptr);
}

Transaction::~Transaction() {}

long Transaction::getId() const { return id; }
std::time_t Transaction::getDate() const { return date; }
double Transaction::getAmount() const { return amount; }
TransactionType Transaction::getType() const { return type; }
