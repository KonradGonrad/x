#ifndef INVESTMENTACCOUNT_H
#define INVESTMENTACCOUNT_H

#include "Account.h"
#include <map>
#include <string>

class InvestmentAccount : public Account {
private:
    double brokerageFee;
    std::map<std::string, int> portfolio;  // ticker -> ilosc akcji

public:
    InvestmentAccount(const std::string& iban, double initialBalance,
                      Currency currency, const std::string& creationDate,
                      double brokerageFee = 0.02);
    ~InvestmentAccount() override;

    double getBrokerageFee() const;
    void setBrokerageFee(double fee);
    const std::map<std::string, int>& getPortfolio() const;

    // Stock operations
    void buyStock(const std::string& ticker, int amount);

    // Override abstract methods
    double calculateMonthlyFees() const override;
    std::string toString() const override;
};

#endif // INVESTMENTACCOUNT_H