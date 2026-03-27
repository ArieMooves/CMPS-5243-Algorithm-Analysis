#pragma once

#include "counters.hpp"
#include <vector>

class HashTable {
private:
    std::vector<std::vector<int>> table;
    std::size_t capacity;
    std::size_t count;
    mutable Counters counters;

    const double LOAD_FACTOR = 0.75;

    std::size_t hash(int key) const {
        return static_cast<std::size_t>(key) * 2654435761u;
    }

    std::size_t indexFor(int key) const {
        return hash(key) % capacity;
    }

    //Resize 
    void resize() {
        counters.resize_events++;
        counters.structural_ops++;

        std::size_t newCap = capacity * 2;
        std::vector<std::vector<int>> newTable(newCap);

        for (auto &bucket : table) {
            for (int val : bucket) {
                std::size_t idx = hash(val) % newCap;
                newTable[idx].push_back(val);
            }
        }

        table = std::move(newTable);
        capacity = newCap;
    }

public:
    explicit HashTable(std::size_t cap = 7)
        : table(cap), capacity(cap), count(0) {}

    void reset() {
        table.clear();
        table.resize(7);
        capacity = 7;
        count = 0;
    }

    void reset_counters() {
        counters = Counters{};
    }

    Counters getCounters() {
        return counters;
    }

    bool insert(int key) {
        counters.inserts++;

        if ((double)count / capacity >= LOAD_FACTOR) {
            resize();
        }

        std::size_t idx = indexFor(key);
        auto &bucket = table[idx];

        for (int val : bucket) {
            counters.comparisons++;
            if (val == key)
                return false;
        }

        counters.structural_ops++;
        bucket.push_back(key);
        count++;
        return true;
    }

    bool contains(int key) {
        counters.lookups++;

        std::size_t idx = indexFor(key);
        auto &bucket = table[idx];

        for (int val : bucket) {
            counters.comparisons++;
            if (val == key)
                return true;
        }

        return false;
    }

    bool erase(int key) {
        counters.deletes++;

        std::size_t idx = indexFor(key);
        auto &bucket = table[idx];

        for (std::size_t i = 0; i < bucket.size(); i++) {
            counters.comparisons++;

            if (bucket[i] == key) {
                counters.structural_ops++;
                bucket[i] = bucket.back();
                bucket.pop_back();
                count--;
                return true;
            }
        }

        return false;
    }
};
