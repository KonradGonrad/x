#ifndef INVESTMENT_ACCOUNT_H
#define INVESTMENT_ACCOUNT_H

#include "Account.h"
#include <map>

class InvestmentAccount : public Account {
public:
    InvestmentAccount(const std::string& iban, double initialBalance,
                      Currency currency, const std::string& creationDate,
                      double brokerageFee = 0.002);
    ~InvestmentAccount() override;

    double getBrokerageFee() const;
    void setBrokerageFee(double fee);
    const std::map<std::string, int>& getPortfolio() const;
    void buyStock(const std::string& ticker, int amount, double price);
    void sellStock(const std::string& ticker, int amount, double price);
    // Override abstract methods    
    double calculateMonthlyFees() const override;
    std::string toString() const override;

private:
    double brokerageFee;
    std::map<std::string, int> portfolio;
};

using InvestmentAccountPtr = std::shared_ptr<InvestmentAccount>;

#endif  // INVESTMENTACCOUNT_H
