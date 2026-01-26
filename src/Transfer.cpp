#include "Transfer.h"
#include "Account.h"
#include "Exceptions.h"
#include <sstream>
#include <iomanip>

Transfer::Transfer(long id, double amount, Account* sender, Account* receiver)
    : Transaction(id, amount, TransactionType::TRANSFER),
      sender(sender), receiver(receiver) {}

Transfer::~Transfer() {}

Account* Transfer::getSender() const {
    return sender;
}

Account* Transfer::getReceiver() const {
    return receiver;
}

bool Transfer::execute() {
    if (!sender) {
        throw InvalidOperationException("Brak konta nadawcy");
    }
    if (!receiver) {
        throw InvalidOperationException("Brak konta odbiorcy");
    }
    sender->withdraw(amount);
    receiver->deposit(amount);
    return true;
}

std::string Transfer::toString() const {
    std::ostringstream oss;
    auto timeinfo = std::localtime(&date);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    oss << "Transfer[id=" << id
        << ", amount=" << amount
        << ", date=" << buffer
        << "]";
    return oss.str();
}
