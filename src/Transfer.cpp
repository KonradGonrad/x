#include "Transfer.h"
#include "Exceptions.h"
#include <sstream>

Transfer::Transfer(long id, double amount, AccountPtr sender, AccountPtr receiver)
    : Transaction(id, amount, TransactionType::TRANSFER),
      sender(sender), receiver(receiver) {}

Transfer::~Transfer() {}

AccountPtr Transfer::getSender() const { return sender; }
AccountPtr Transfer::getReceiver() const { return receiver; }

void Transfer::execute() {
    if (!sender) throw ValidationException("Sender account is null");
    if (!receiver) throw ValidationException("Receiver account is null");
    if (sender->getBalance() < amount) {
        throw InsufficientFundsException(amount, sender->getBalance());
    }
    sender->withdraw(amount);
    receiver->deposit(amount);
}

std::string Transfer::toString() const {
    std::ostringstream oss;
    oss << "Transfer[id=" << id << ", amount=" << amount << "]";
    return oss.str();
}
