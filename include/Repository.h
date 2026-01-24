/**
 * @file Repository.h
 * @brief Generyczny szablon repozytorium z użyciem smart pointerów
 * 
 * Klasa szablonowa do przechowywania obiektów identyfikowanych przez klucz.
 * Używa std::shared_ptr do automatycznego zarządzania pamięcią.
 */

#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <memory>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include "Exceptions.h"

/**
 * @class Repository
 * @brief Generyczne repozytorium z użyciem std::shared_ptr
 */
template<typename T, typename KeyType = int>
class Repository {
private:
    std::map<KeyType, std::shared_ptr<T>> items;  ///< Przechowywane elementy

public:
    /**
     * @brief Konstruktor domyślny
     */
    Repository() = default;

    /**
     * @brief Destruktor - smart pointery automatycznie zwalniają pamięć
     */
    ~Repository() = default;

    /**
     * @brief Dodaje element do repozytorium
     * @param key Klucz identyfikujący element
     * @param item Wskaźnik do elementu
     */
    void add(const KeyType& key, T* item) {
        items[key] = std::shared_ptr<T>(item);
    }

    /**
     * @brief Dodaje element jako shared_ptr
     */
    void add(const KeyType& key, std::shared_ptr<T> item) {
        items[key] = item;
    }

    /**
     * @brief Pobiera element z repozytorium
     * @param key Klucz elementu
     * @return Shared pointer do elementu
     * @throw BankException gdy element nie istnieje
     */
    std::shared_ptr<T> get(const KeyType& key) const {
        auto it = items.find(key);
        if (it == items.end()) {
            throw BankException("Item not found in repository");
        }
        return it->second;
    }

    /**
     * @brief Sprawdza czy element istnieje
     */
    bool exists(const KeyType& key) const {
        return items.find(key) != items.end();
    }

    /**
     * @brief Usuwa element z repozytorium
     * @return true jesli usunieto
     */
    bool remove(const KeyType& key) {
        return items.erase(key) > 0;
    }

    /**
     * @brief Zwraca liczbe elementow
     */
    size_t size() const {
        return items.size();
    }

    /**
     * @brief Sprawdza czy puste
     */
    bool empty() const {
        return items.empty();
    }

    /**
     * @brief Czysci repozytorium
     */
    void clear() {
        items.clear();
    }

    /**
     * @brief Pobiera wszystkie elementy
     */
    std::vector<std::shared_ptr<T>> getAll() const {
        std::vector<std::shared_ptr<T>> result;
        result.reserve(items.size());
        for (const auto& pair : items) {
            result.push_back(pair.second);
        }
        return result;
    }

    /**
     * @brief Filtruje elementy wedlug predykatu
     * @param predicate Funkcja zwracajaca true dla elementow do zachowania
     */
    std::vector<std::shared_ptr<T>> filter(std::function<bool(const T&)> predicate) const {
        std::vector<std::shared_ptr<T>> result;
        for (const auto& pair : items) {
            if (predicate(*pair.second)) {
                result.push_back(pair.second);
            }
        }
        return result;
    }

    /**
     * @brief Wykonuje akcje dla kazdego elementu
     */
    void forEach(std::function<void(T&)> action) {
        for (auto& pair : items) {
            action(*pair.second);
        }
    }
};

#endif // REPOSITORY_H
