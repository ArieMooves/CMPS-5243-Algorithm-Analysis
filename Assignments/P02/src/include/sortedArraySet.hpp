#pragma once

#include "counters.hpp"
#include <cstddef>
#include <iostream>

class SortedArraySet {
private:
    int *data;
    std::size_t count;
    std::size_t capacity;

    Counters counters;

    // Resize array
    void resize(std::size_t newCapacity) {
        counters.resize_events++;
        counters.structural_ops++;

        int *newData = new int[newCapacity];

        for (std::size_t i = 0; i < count; i++) {
            newData[i] = data[i];
            counters.shifts_relinks++; // copying elements = movement
        }

        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

    // Binary search (lower bound)
    std::size_t lowerBound(int value) const {
        std::size_t left = 0;
        std::size_t right = count;

        while (left < right) {
            std::size_t mid = left + (right - left) / 2;

            counters.comparisons++; // data[mid] < value
            if (data[mid] < value) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        return left;
    }

public:
    explicit SortedArraySet(std::size_t initialCapacity = 10)
        : data(new int[initialCapacity]), count(0), capacity(initialCapacity) {}

    ~SortedArraySet() {
        delete[] data;
    }

    // Reset structure
    void reset() {
        delete[] data;
        data = new int[10];
        count = 0;
        capacity = 10;
    }

    // Reset counters
    void reset_counters() {
        counters = Counters{};
    }

    Counters getCounters() {
        return counters;
    }

    std::size_t size() const {
        return count;
    }

    bool empty() const {
        return count == 0;
    }

    // LOOKUP
    bool contains(int value) {
        counters.lookups++;

        if (count == 0)
            return false;

        std::size_t pos = lowerBound(value);

        counters.comparisons++; // check equality
        return pos < count && data[pos] == value;
    }

    // INSERT
    bool insert(int value) {
        counters.inserts++;

        std::size_t pos = lowerBound(value);

        // duplicate check
        if (pos < count) {
            counters.comparisons++;
            if (data[pos] == value)
                return false;
        }

        // resize if needed
        if (count == capacity) {
            resize(capacity * 2);
        }

        // shift elements right
        for (std::size_t i = count; i > pos; i--) {
            data[i] = data[i - 1];
            counters.shifts_relinks++;   // shifting cost
            counters.structural_ops++;
        }

        data[pos] = value;
        counters.structural_ops++;

        count++;
        return true;
    }

    // DELETE
    bool erase(int value) {
        counters.deletes++;

        if (count == 0)
            return false;

        std::size_t pos = lowerBound(value);

        if (pos >= count) return false;

        counters.comparisons++;
        if (data[pos] != value)
            return false;

        // shift elements left
        for (std::size_t i = pos; i + 1 < count; i++) {
            data[i] = data[i + 1];
            counters.shifts_relinks++;   // shifting cost
            counters.structural_ops++;
        }

        count--;
        return true;
    }

    void print() const {
        std::cout << "[";
        for (std::size_t i = 0; i < count; i++) {
            std::cout << data[i];
            if (i + 1 < count)
                std::cout << ", ";
        }
        std::cout << "]\n";
    }
};
