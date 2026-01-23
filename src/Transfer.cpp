#include "Transfer.h"
#include "Account.h"
#include <sstream>

Transfer::Transfer(long id, double amount, Account* sender, Account* receiver)
    : Transaction(id, amount, TransactionType::TRANSFER),
      sender(sender), receiver(receiver) {}

Transfer::~Transfer() {}

Account* Transfer::getSender() const { return sender; }
Account* Transfer::getReceiver() const { return receiver; }

bool Transfer::execute() {
    if (sender == nullptr || receiver == nullptr) {
        return false;
    }
    if (sender->getBalance() < amount) {
        return false;
    }
    sender->withdraw(amount);
    receiver->deposit(amount);
    return true;
}

std::string Transfer::toString() const {
    std::ostringstream oss;
    oss << "Transfer[id=" << id
        << ", amount=" << amount << "]";
    return oss.str();
}
