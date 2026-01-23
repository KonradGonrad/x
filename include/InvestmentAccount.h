#ifndef INVESTMENTACCOUNT_H
#define INVESTMENTACCOUNT_H

#include "Account.h"
#include <map>
#include <string>

class InvestmentAccount : public Account {
private:
    std::map<std::string, int> portfolio;
    double brokerageFee;

public:
    InvestmentAccount(const std::string& iban, double initialBalance,
                      const std::string& currency, const std::string& creationDate,
                      double brokerageFee);
    ~InvestmentAccount() override;

    // Stock operations
    void buyStock(const std::string& ticker, int amount);

    // Override abstract methods
    double calculateMonthlyFees() const override;
};

#endif // INVESTMENTACCOUNT_H