#include "Transaction.h"
#include <sstream>

Transaction::Transaction(long id, double amount, TransactionType type)
    : id(id), amount(amount), type(type) {
    date = std::time(nullptr);
}

Transaction::~Transaction() {}

long Transaction::getId() const { return id; }
std::time_t Transaction::getDate() const { return date; }
double Transaction::getAmount() const { return amount; }
TransactionType Transaction::getType() const { return type; }

std::string Transaction::getTypeString() const {
    switch (type) {
        case TransactionType::DEPOSIT: return "DEPOSIT";
        case TransactionType::WITHDRAWAL: return "WITHDRAWAL";
        case TransactionType::TRANSFER: return "TRANSFER";
        case TransactionType::STOCK_PURCHASE: return "STOCK_PURCHASE";
        case TransactionType::STOCK_SALE: return "STOCK_SALE";
        case TransactionType::CURRENCY_EXCHANGE: return "CURRENCY_EXCHANGE";
        default: return "UNKNOWN";
    }
}

std::string Transaction::toString() const {
    std::ostringstream oss;
    oss << "Transaction[id=" << id << ", type=" << getTypeString()
        << ", amount=" << amount << "]";
    return oss.str();
}
