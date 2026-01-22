#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>

class Account;  // Forward declaration

struct DateTime
{
    int rok;
    int miesiac;
    int dzien;
    int godzina;
    int minuta;
};


class Transaction {
private:
    int id;
    DateTime date;
    double amount;
    DateTime date;
public:
    Transaction(const std::string& transactionId, double amount,
                const std::string& description);
    virtual ~Transaction();

    // Abstract methods
    virtual bool execute() = 0;
};

#endif // TRANSACTION_H