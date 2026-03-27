#pragma once

#include <cstddef>
#include <vector>

class HashTable {
private:
    std::vector<std::vector<int>> table;
    std::size_t capacity;
    std::size_t counter;  // Tracks number of elements

    // Integer hash function
    std::size_t hash(int key) const {
        return static_cast<std::size_t>(key) * 2654435761u;
    }

    // Compress hash value into a valid bucket index
    std::size_t indexFor(int key) const {
        return hash(key) % capacity;
    }

public:
    explicit HashTable(std::size_t cap = 101)
        : table(cap), capacity(cap), counter(0) {}

    bool insert(int key) {
        std::size_t idx = indexFor(key);
        auto &bucket = table[idx];

        // Ignore duplicates
        for (int value : bucket) {
            if (value == key) {
                return false;
            }
        }

        bucket.push_back(key);
        counter++;  // increment count
        return true;
    }

    bool contains(int key) const {
        std::size_t idx = indexFor(key);
        const auto &bucket = table[idx];

        for (int value : bucket) {
            if (value == key) {
                return true;
            }
        }

        return false;
    }

    bool erase(int key) {
        std::size_t idx = indexFor(key);
        auto &bucket = table[idx];

        for (std::size_t i = 0; i < bucket.size(); i++) {
            if (bucket[i] == key) {
                // swap-pop delete: fast, order not preserved
                bucket[i] = bucket.back();
                bucket.pop_back();
                counter--;  // decrement count
                return true;
            }
        }

        return false;
    }

    // Returns number of elements in the hash table
    std::size_t size() const {
        return counter;
    }
};
