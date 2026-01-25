#include "TransactionRepository.h"

std::vector<TransactionPtr> TransactionRepository::findByType(TransactionType type) const {
    return filter([type](const TransactionPtr& t) {
        return t->getType() == type;
    });
}

std::vector<TransactionPtr> TransactionRepository::findByDateRange(std::time_t from, std::time_t to) const {
    return filter([from, to](const TransactionPtr& t) {
        return t->getDate() >= from && t->getDate() <= to;
    });
}

std::vector<TransactionPtr> TransactionRepository::findByAmountRange(double minAmount, double maxAmount) const {
    return filter([minAmount, maxAmount](const TransactionPtr& t) {
        return t->getAmount() >= minAmount && t->getAmount() <= maxAmount;
    });
}

double TransactionRepository::getTotalAmount() const {
    double total = 0;
    for (const auto& t : items) {
        if (t) total += t->getAmount();
    }
    return total;
}

double TransactionRepository::getTotalAmountByType(TransactionType type) const {
    double total = 0;
    for (const auto& t : items) {
        if (t && t->getType() == type) total += t->getAmount();
    }
    return total;
}
