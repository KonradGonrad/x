#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <cmath>

struct TestResult {
    std::string testName;
    bool passed;
    std::string message;
    
    TestResult() : testName(""), passed(false), message("") {}
    TestResult(const std::string& name, bool p, const std::string& msg = "")
        : testName(name), passed(p), message(msg) {}
};

class TestFramework {
public:
    static TestFramework& getInstance() {
        static TestFramework instance;
        return instance;
    }

    void addResult(const TestResult& result) {
        results.push_back(result);
    }

    void runAll() {
        for (size_t i = 0; i < testFunctions.size(); i++) {
            testFunctions[i]();
        }
    }

    void registerTest(std::function<void()> testFunc) {
        testFunctions.push_back(testFunc);
    }

    void printSummary() const {
        int passed = 0, failed = 0;
        
        std::cout << "\n========== TEST RESULTS ==========\n" << std::endl;
        
        for (size_t i = 0; i < results.size(); i++) {
            const TestResult& r = results[i];
            if (r.passed) {
                std::cout << "[PASS] " << r.testName << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] " << r.testName;
                if (!r.message.empty()) {
                    std::cout << " - " << r.message;
                }
                std::cout << std::endl;
                failed++;
            }
        }
        
        std::cout << "\n===================================" << std::endl;
        std::cout << "Total: " << (passed + failed) << " | ";
        std::cout << "Passed: " << passed << " | ";
        std::cout << "Failed: " << failed << std::endl;
        
        if (failed == 0) {
            std::cout << "\n*** ALL TESTS PASSED! ***" << std::endl;
        }
    }

    void clear() {
        results.clear();
        testFunctions.clear();
    }

    int getFailedCount() const {
        int failed = 0;
        for (size_t i = 0; i < results.size(); i++) {
            if (!results[i].passed) failed++;
        }
        return failed;
    }

private:
    TestFramework() {}
    std::vector<TestResult> results;
    std::vector<std::function<void()>> testFunctions;
};

// Makra testowe
#define TEST_ASSERT(condition, testName) \
    do { \
        TestResult result(testName, (condition)); \
        if (!(condition)) { \
            result.message = "Assertion failed"; \
        } \
        TestFramework::getInstance().addResult(result); \
    } while(0)

#define TEST_EQUAL(expected, actual, testName) \
    do { \
        bool passed = ((expected) == (actual)); \
        TestResult result(testName, passed); \
        if (!passed) { \
            result.message = "Expected different value"; \
        } \
        TestFramework::getInstance().addResult(result); \
    } while(0)

#define TEST_DOUBLE_EQUAL(expected, actual, epsilon, testName) \
    do { \
        bool passed = (std::abs((expected) - (actual)) < (epsilon)); \
        TestResult result(testName, passed); \
        if (!passed) { \
            result.message = "Values differ by more than epsilon"; \
        } \
        TestFramework::getInstance().addResult(result); \
    } while(0)

#define TEST_THROWS(exceptionType, expression, testName) \
    do { \
        bool caught = false; \
        try { \
            expression; \
        } catch (const exceptionType&) { \
            caught = true; \
        } catch (...) { \
            caught = false; \
        } \
        TestResult result(testName, caught); \
        if (!caught) { \
            result.message = "Expected exception not thrown"; \
        } \
        TestFramework::getInstance().addResult(result); \
    } while(0)

#define TEST_NO_THROW(expression, testName) \
    do { \
        bool noThrow = true; \
        try { \
            expression; \
        } catch (...) { \
            noThrow = false; \
        } \
        TestResult result(testName, noThrow); \
        if (!noThrow) { \
            result.message = "Unexpected exception thrown"; \
        } \
        TestFramework::getInstance().addResult(result); \
    } while(0)

#define RUN_TEST(testFunc) \
    TestFramework::getInstance().registerTest(testFunc)

#endif
