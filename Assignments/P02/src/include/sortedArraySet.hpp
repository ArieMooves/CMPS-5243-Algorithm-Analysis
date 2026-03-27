#pragma once

#include <cstddef>
#include <iostream>

class SortedArraySet {
private:
    int *data;
    std::size_t count;     // <-- acts as the counter
    std::size_t capacity;

    void resize(std::size_t newCapacity) {
        int *newData = new int[newCapacity];

        for (std::size_t i = 0; i < count; i++) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

    // Returns the index where value is found,
    // or where it should be inserted to maintain sorted order.
    std::size_t lowerBound(int value) const {
        std::size_t left = 0;
        std::size_t right = count;

        while (left < right) {
            std::size_t mid = left + (right - left) / 2;

            if (data[mid] < value) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        return left;
    }

public:
    explicit SortedArraySet(std::size_t initialCapacity = 8)
        : data(new int[initialCapacity]), count(0), capacity(initialCapacity) {}

    ~SortedArraySet() {
        delete[] data;
        count = 0; // optional cleanup
    }

    // O(1) size access (same idea as counter in other structures)
    std::size_t size() const {
        return count;
    }

    bool empty() const {
        return count == 0;
    }

    bool contains(int value) const {
        if (count == 0) {
            return false;
        }

        std::size_t pos = lowerBound(value);
        return pos < count && data[pos] == value;
    }

    bool insert(int value) {
        std::size_t pos = lowerBound(value);

        // Duplicate guard
        if (pos < count && data[pos] == value) {
            return false;
        }

        // Resize if needed
        if (count == capacity) {
            resize(capacity * 2);
        }

        // Shift elements right
        for (std::size_t i = count; i > pos; i--) {
            data[i] = data[i - 1];
        }

        data[pos] = value;
        count++;   // <-- increment counter

        return true;
    }

    bool erase(int value) {
        if (count == 0) {
            return false;
        }

        std::size_t pos = lowerBound(value);

        if (pos >= count || data[pos] != value) {
            return false;
        }

        // Shift elements left
        for (std::size_t i = pos; i + 1 < count; i++) {
            data[i] = data[i + 1];
        }

        count--;   // <-- decrement counter

        return true;
    }

    void print() const {
        std::cout << "[";
        for (std::size_t i = 0; i < count; i++) {
            std::cout << data[i];
            if (i + 1 < count) {
                std::cout << ", ";
            }
        }
        std::cout << "]\n";
    }
};
