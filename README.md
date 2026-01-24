# System Bankowy - Projekt C++20

Projekt zaliczeniowy z programowania obiektowego w C++.

## Funkcjonalności

- **Wielobankowy system** - obsługa wielu banków jednocześnie
- **Typy klientów** - osoby fizyczne (IndividualClient) i firmy (CompanyClient)
- **Typy kont** - oszczędnościowe, inwestycyjne, walutowe
- **Transakcje** - przelewy, zakup akcji, wymiana walut
- **Web UI** - interfejs webowy z REST API
- **Internacjonalizacja** - polski i angielski

## Struktura projektu

```
├── include/           # Pliki nagłówkowe (.h)
│   ├── Account.h      # klasa konta
│   ├── Client.h       # klasa klienta
│   ├── Transaction.h  # klasa transakcji
│   ├── Exceptions.h   # Hierarchia wyjątków
│   ├── Repository.h   # Szablon repozytorium
│   └── ...
├── src/               # Pliki źródłowe (.cpp)
├── tests/             # Testy jednostkowe
├── web/               # Interfejs webowy (HTML/CSS/JS)
└── CMakeLists.txt     # Konfiguracja CMake
```

## Wymagania

- C++20
- CMake 3.20+
- MinGW/GCC lub MSVC

## Kompilacja

```bash
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
mingw32-make -j8
```

## Uruchomienie

```bash
# Tryb demo (konsola)
./bin/banking_system

# Tryb serwera web
./bin/banking_system --web --port 3000
```

## Testy

```bash
./bin/banking_tests
```

Wynik: **59/59 testów zaliczonych**

## Zastosowane wzorce i techniki

### Dziedziczenie i polimorfizm
- `Account` → `SavingsAccount`, `InvestmentAccount`, `CurrencyAccount`
- `Client` → `IndividualClient`, `CompanyClient`
- `Transaction` → `Transfer`, `StockOperation`, `CurrencyExchange`

### Wyjątki
- `BankException` (bazowa)
- `InsufficientFundsException`
- `AccountBlockedException`
- `InvalidOperationException`
- `ClientNotFoundException`
- `AccountNotFoundException`

### Smart pointery i szablony
- `Repository<T, KeyType>` - repozytorium z `std::shared_ptr`

### Operatory
- `operator==`, `operator!=` dla `Address`
- `operator<<` dla `Address` i `Currency`

### STL
- `std::vector`, `std::map`, `std::queue`
- `std::find`, algorytmy
- `std::ostringstream` dla formatowania

## Dokumentacja

Generowanie dokumentacji Doxygen:
```bash
doxygen Doxyfile
```

## Autor

Antoni Ciszewski, Konrad Kargul
