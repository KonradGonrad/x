/**
 * @file WebServer.h
 * @brief Serwer HTTP dla REST API systemu bankowego
 * 
 * Udostępnia interfejs REST API dla operacji bankowych.
 * Używa biblioteki cpp-httplib.
 */

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <string>
#include <vector>
#include <functional>

class BankService;
class MarketDataService;
class TransactionRepository;

/**
 * @class WebServer
 * @brief HTTP server providing REST API for banking operations
 * 
 * Uses cpp-httplib library to serve static files and handle
 * JSON API requests for banking operations.
 */
class WebServer {
private:
    int port;
    std::string webRoot;
    std::vector<BankService*> banks;
    MarketDataService* marketData;
    TransactionRepository* transactionRepo;
    bool running;

    // JSON helper methods
    std::string clientToJson(class Client* client) const;
    std::string accountToJson(class Account* account) const;
    std::string transactionToJson(class Transaction* transaction) const;
    std::string bankToJson(BankService* bank) const;
    std::string marketDataToJson() const;

public:
    /**
     * @brief Construct a new Web Server
     * @param port Port number to listen on (default: 8080)
     * @param webRoot Path to static web files
     */
    WebServer(int port = 8080, const std::string& webRoot = "web");
    
    /**
     * @brief Destructor
     */
    ~WebServer();

    // Configuration
    void addBank(BankService* bank);
    void setMarketDataService(MarketDataService* marketData);
    void setTransactionRepository(TransactionRepository* repo);

    // Server control
    void start();
    void stop();
    bool isRunning() const;

    // Getters
    int getPort() const;
    std::string getWebRoot() const;
};

#endif // WEBSERVER_H
