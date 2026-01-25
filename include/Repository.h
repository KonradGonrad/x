#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include "Exceptions.h"

template<typename T, typename KeyType = int>
class Repository {
public:
    using Ptr = std::shared_ptr<T>;
    using Collection = std::vector<Ptr>;

    virtual ~Repository() = default;

    void add(Ptr item) {
        if (!item) throw ValidationException("Cannot add null item");
        items.push_back(item);
    }

    Ptr findById(KeyType id) const {
        for (const auto& item : items) {
            if (item && getKey(item) == id) return item;
        }
        return nullptr;
    }

    Ptr getById(KeyType id) const {
        auto item = findById(id);
        if (!item) throw NotFoundException("Item with given ID");
        return item;
    }

    bool remove(KeyType id) {
        auto it = std::remove_if(items.begin(), items.end(),
            [this, &id](const Ptr& item) { return item && getKey(item) == id; });
        if (it != items.end()) {
            items.erase(it, items.end());
            return true;
        }
        return false;
    }

    const Collection& getAll() const { return items; }
    size_t count() const { return items.size(); }

    std::vector<Ptr> filter(std::function<bool(const Ptr&)> predicate) const {
        std::vector<Ptr> result;
        for (const auto& item : items) {
            if (item && predicate(item)) result.push_back(item);
        }
        return result;
    }

protected:
    virtual KeyType getKey(const Ptr& item) const = 0;
    Collection items;
};

#endif
