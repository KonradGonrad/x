#include <string>

// Zmień "enum class" na "struct"
struct Currency {
    std::string code;    // np. "USD"
    std::string name;    // np. "Dolar amerykański"
    std::string symbol;  // np. "$"
    double exchangeRate; // np. 3.98
};