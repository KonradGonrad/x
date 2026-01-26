cmake_minimum_required(VERSION 3.20)
project(BankingSystem VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# Note: Do NOT define CPPHTTPLIB_OPENSSL_SUPPORT - we don't use HTTPS

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/external)

# Find required libraries for networking (Windows)
if(WIN32)
    set(EXTRA_LIBS ws2_32)
endif()

# Core library sources (without main.cpp for reuse in tests)
set(CORE_SOURCES
    src/Address.cpp
    src/Client.cpp
    src/IndividualClient.cpp
    src/CompanyClient.cpp
    src/Account.cpp
    src/SavingsAccount.cpp
    src/InvestmentAccount.cpp
    src/CurrencyAccount.cpp
    src/Transaction.cpp
    src/Transfer.cpp
    src/StockOperation.cpp
    src/CurrencyExchange.cpp
    src/MarketDataService.cpp
    src/TransactionRepository.cpp
    src/BankService.cpp
    src/DataPersistence.cpp
)

# Main application sources
set(APP_SOURCES
    ${CORE_SOURCES}
    src/ConsoleUI.cpp
    src/WebServer.cpp
    src/main.cpp
)

# Main executable
add_executable(banking_system ${APP_SOURCES})

# Link libraries (Windows sockets for httplib)
if(WIN32)
    target_link_libraries(banking_system ${EXTRA_LIBS})
endif()

# Output directory for main app
set_target_properties(banking_system PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)

# ============================================================================
# Tests
# ============================================================================

# Test executable
add_executable(banking_tests 
    tests/tests.cpp
    ${CORE_SOURCES}
)

# Link libraries for tests (Windows)
if(WIN32)
    target_link_libraries(banking_tests ${EXTRA_LIBS})
endif()

# Output directory for tests
set_target_properties(banking_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)

# Enable testing
enable_testing()

# Add test
add_test(NAME BankingSystemTests COMMAND banking_tests)

