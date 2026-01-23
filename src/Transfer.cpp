#include "Transfer.h"
#include "Account.h"
#include <sstream>
#include <iomanip>

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
    if (sender->getBalance() < getAmount()) {
        return false;
    }
    sender->withdraw(getAmount());
    receiver->deposit(getAmount());
    return true;
}

std::string Transfer::toString() const {
    std::ostringstream oss;
    oss << "Transfer[id=" << getId()
        << ", amount=" << getAmount() << "]";
    return oss.str();
}
