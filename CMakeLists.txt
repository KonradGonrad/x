cmake_minimum_required(VERSION 3.10)
project(BankingSystem_v5_Tests VERSION 5.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Library sources (without main.cpp and tests.cpp)
set(LIB_SOURCES
    src/Address.cpp
    src/Account.cpp
    src/SavingsAccount.cpp
    src/InvestmentAccount.cpp
    src/CurrencyAccount.cpp
    src/Client.cpp
    src/IndividualClient.cpp
    src/CompanyClient.cpp
    src/Transaction.cpp
    src/Transfer.cpp
    src/StockOperation.cpp
    src/CurrencyExchange.cpp
    src/TransactionRepository.cpp
    src/MarketDataService.cpp
    src/BankService.cpp
)

# Create static library
add_library(banking_lib STATIC ${LIB_SOURCES})
target_include_directories(banking_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Main executable (optional demo)
# add_executable(banking_demo src/main.cpp)
# target_link_libraries(banking_demo banking_lib)

# Test executable
add_executable(banking_tests src/tests.cpp)
target_link_libraries(banking_tests banking_lib)

# Enable testing
enable_testing()
add_test(NAME UnitTests COMMAND banking_tests)

# Print configuration
message(STATUS "Building Banking System v5 with Tests")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
