#include <iostream>
#include <memory>
#include "BankService.h"
#include "IndividualClient.h"
#include "CompanyClient.h"
#include "SavingsAccount.h"
#include "InvestmentAccount.h"
#include "CurrencyAccount.h"
#include "Transfer.h"
#include "StockOperation.h"
#include "CurrencyExchange.h"
#include "Exceptions.h"

int main() {
    std::cout << "=== System Bankowy - Serwisy (v4) ===" << std::endl;

    try {
        auto bankAddress = std::make_shared<Address>("Bankowa", "1", "Warszawa", "00-001", "Polska");
        BankService bank("MojBank", "MOJBPLPW", "1234567890", bankAddress);

        // Klienci
        auto addr1 = std::make_shared<Address>("Testowa", "10", "Krakow", "30-001", "Polska");
        auto client1 = std::make_shared<IndividualClient>(1, addr1,
            "123456789", "jan@email.pl", "Jan", "Kowalski", "90010112345");
        bank.registerClient(client1);

        // Konta
        auto savings = std::dynamic_pointer_cast<SavingsAccount>(
            bank.createAccount(client1, "Savings", 10000.0, Currency::PLN));
        auto investment = std::dynamic_pointer_cast<InvestmentAccount>(
            bank.createAccount(client1, "Investment", 50000.0, Currency::PLN));
        auto eurAccount = std::dynamic_pointer_cast<CurrencyAccount>(
            bank.createAccount(client1, "Currency", 5000.0, Currency::EUR));
        auto usdAccount = std::dynamic_pointer_cast<CurrencyAccount>(
            bank.createAccount(client1, "Currency", 3000.0, Currency::USD));

        std::cout << "\n--- MarketDataService ---" << std::endl;
        auto& market = bank.getMarketDataService();
        std::cout << "Kursy walut:" << std::endl;
        for (const auto& rate : market.getAllRates()) {
            std::cout << "  " << currencyToString(rate.first) << " = " << rate.second << " PLN" << std::endl;
        }
        
        std::cout << "\nNotowania akcji:" << std::endl;
        for (const auto& ticker : market.getAllTickers()) {
            auto quote = market.getStockQuote(ticker);
            std::cout << "  " << quote.ticker << ": " << quote.price
                      << " (" << (quote.change >= 0 ? "+" : "") << quote.changePercent << "%)" << std::endl;
        }

        std::cout << "\n--- Operacje gieldowe ---" << std::endl;
        std::cout << "Przed: " << investment->toString() << std::endl;
        
        bank.executeStockOperation(investment, "AAPL", 10, true);
        bank.executeStockOperation(investment, "CDR", 50, true);
        
        std::cout << "Po zakupach: " << investment->toString() << std::endl;
        std::cout << "Portfolio:" << std::endl;
        for (const auto& pos : investment->getPortfolio()) {
            std::cout << "  " << pos.first << ": " << pos.second << " szt." << std::endl;
        }

        std::cout << "\n--- Wymiana walut ---" << std::endl;
        std::cout << "EUR przed: " << eurAccount->getBalance() << std::endl;
        std::cout << "USD przed: " << usdAccount->getBalance() << std::endl;
        
        bank.executeCurrencyExchange(eurAccount, usdAccount, 1000.0);
        
        std::cout << "EUR po: " << eurAccount->getBalance() << std::endl;
        std::cout << "USD po: " << usdAccount->getBalance() << std::endl;

        std::cout << "\n--- Przelew ---" << std::endl;
        bank.executeTransfer(savings, investment, 2000.0);
        std::cout << "Savings: " << savings->getBalance() << " PLN" << std::endl;
        std::cout << "Investment: " << investment->getBalance() << " PLN" << std::endl;

        std::cout << "\n--- TransactionRepository ---" << std::endl;
        auto& txRepo = bank.getTransactionRepository();
        std::cout << "Wszystkich transakcji: " << txRepo.count() << std::endl;
        std::cout << "Suma obrotow: " << txRepo.getTotalAmount() << std::endl;
        
        auto stockTx = txRepo.findByType(TransactionType::STOCK_PURCHASE);
        std::cout << "Zakupy akcji: " << stockTx.size() << std::endl;
        
        for (const auto& tx : txRepo.getAll()) {
            std::cout << "  " << tx->toString() << std::endl;
        }

        std::cout << "\n--- Symulacja rynku ---" << std::endl;
        market.simulateMarketMovement();
        auto newQuote = market.getStockQuote("AAPL");
        std::cout << "AAPL po symulacji: " << newQuote.price
                  << " (" << (newQuote.change >= 0 ? "+" : "") << newQuote.changePercent << "%)" << std::endl;

        std::cout << "\n" << bank.toString() << std::endl;
        std::cout << "\n=== Koniec ===" << std::endl;

    } catch (const BankException& e) {
        std::cerr << "Blad: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
