/**
 * @file TestFramework.h
 * @brief Prosty framework do testow jednostkowych
 * 
 * Minimalny framework testowy bez zewnetrznych zaleznosci.
 * Uzywa makr do asercji i grupowania testow.
 */

#ifndef TESTFRAMEWORK_H
#define TESTFRAMEWORK_H

#include <iostream>
#include <string>
#include <vector>
#include <functional>

/**
 * @struct TestResult
 * @brief Przechowuje wynik pojedynczego testu
 */
struct TestResult {
    std::string name;     ///< Nazwa testu
    bool passed;          ///< Czy test zaliczony
    std::string message;  ///< Komunikat bledu
};

/**
 * @class TestRunner
 * @brief Uruchamia testy i zbiera wyniki
 */
class TestRunner {
private:
    std::vector<TestResult> results;  ///< Wyniki testow
    int passed = 0;                   ///< Liczba zaliczonych
    int failed = 0;                   ///< Liczba niezaliczonych

public:
    /**
     * @brief Dodaje wynik testu
     * @param name Nazwa testu
     * @param success Czy test zaliczony
     * @param msg Komunikat bledu
     */
    void addResult(const std::string& name, bool success, const std::string& msg = "") {
        TestResult result;
        result.name = name;
        result.passed = success;
        result.message = msg;
        results.push_back(result);
        if (success) {
            passed++;
        } else {
            failed++;
        }
    }

    /**
     * @brief Wyswietla podsumowanie testow
     */
    void printSummary() const {
        std::cout << "\n============================================================\n";
        std::cout << "PODSUMOWANIE TESTOW\n";
        std::cout << "============================================================\n";
        
        for (size_t i = 0; i < results.size(); i++) {
            const TestResult& result = results[i];
            if (result.passed) {
                std::cout << "[PASS] ";
            } else {
                std::cout << "[FAIL] ";
            }
            std::cout << result.name;
            if (!result.message.empty()) {
                std::cout << " - " << result.message;
            }
            std::cout << "\n";
        }
        
        std::cout << "------------------------------------------------------------\n";
        std::cout << "Zaliczone: " << passed << "/" << (passed + failed) << "\n";
        std::cout << "Niezaliczone: " << failed << "/" << (passed + failed) << "\n";
        std::cout << "============================================================\n";
    }

    /**
     * @brief Zwraca true jesli wszystkie testy przeszly
     */
    bool allPassed() const {
        return failed == 0;
    }

    /**
     * @brief Zwraca liczbe zaliczonych
     */
    int getPassedCount() const { return passed; }

    /**
     * @brief Zwraca liczbe niezaliczonych
     */
    int getFailedCount() const { return failed; }
};

// ============================================================================
// Makra do testow
// ============================================================================

/**
 * @brief Makro sprawdzajace warunek
 */
#define TEST_ASSERT(condition, testName) \
    do { \
        if (condition) { \
            runner.addResult(testName, true); \
        } else { \
            runner.addResult(testName, false, "Warunek niespelniony: " #condition); \
        } \
    } while(0)

/**
 * @brief Makro sprawdzajace rownosc
 */
#define TEST_EQUAL(expected, actual, testName) \
    do { \
        if ((expected) == (actual)) { \
            runner.addResult(testName, true); \
        } else { \
            runner.addResult(testName, false, "Oczekiwano: " + std::to_string(expected) + ", otrzymano: " + std::to_string(actual)); \
        } \
    } while(0)

/**
 * @brief Makro sprawdzajace czy wyjatek zostal rzucony
 */
#define TEST_THROWS(exceptionType, expression, testName) \
    do { \
        bool exceptionThrown = false; \
        try { \
            expression; \
        } catch (const exceptionType&) { \
            exceptionThrown = true; \
        } catch (...) { \
            runner.addResult(testName, false, "Nieoczekiwany wyjatek"); \
            break; \
        } \
        if (exceptionThrown) { \
            runner.addResult(testName, true); \
        } else { \
            runner.addResult(testName, false, "Wyjatek nie zostal rzucony"); \
        } \
    } while(0)

/**
 * @brief Makro do testowania stringow
 */
#define TEST_STRING_EQUAL(expected, actual, testName) \
    do { \
        if ((expected) == (actual)) { \
            runner.addResult(testName, true); \
        } else { \
            runner.addResult(testName, false, std::string("Oczekiwano: '") + std::string(expected) + "', otrzymano: '" + std::string(actual) + "'"); \
        } \
    } while(0)

#endif // TESTFRAMEWORK_H
