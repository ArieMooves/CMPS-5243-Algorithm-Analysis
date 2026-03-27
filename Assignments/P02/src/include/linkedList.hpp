#pragma once

#include "counters.hpp"
#include <iostream>

class LinkedList {
private:
    struct Node {
        int data;
        Node *next;

        Node(int v) : data(v), next(nullptr) {}
    };

    Node *head;
    std::size_t count;
    mutable Counters counters;

public:
    LinkedList() : head(nullptr), count(0) {}

    ~LinkedList() {
        Node *curr = head;
        while (curr) {
            Node *temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    void reset() {
        this->~LinkedList();
        head = nullptr;
        count = 0;
    }

    void reset_counters() {
        counters = Counters{};
    }

    Counters getCounters() {
        return counters;
    }

    void print() const {
        Node *curr = head;
        while (curr) {
            std::cout << curr->data << " ";
            curr = curr->next;
        }
        std::cout << "\n";
    }

    // INSERT
    bool insert(int value) {
        counters.inserts++;

        if (contains(value)) return false;

        Node *n = new Node(value);

        counters.structural_ops++;
        counters.shifts_relinks++;

        n->next = head;
        head = n;

        count++;
        return true;
    }

    // LOOKUP
    bool contains(int value) {
        counters.lookups++;

        Node *curr = head;

        while (curr) {
            counters.comparisons++;

            if (curr->data == value)
                return true;

            curr = curr->next;
        }

        return false;
    }

    // DELETE
    bool erase(int value) {
        counters.deletes++;

        Node *curr = head;
        Node *prev = nullptr;

        while (curr) {
            counters.comparisons++;

            if (curr->data == value) {
                counters.structural_ops++;
                counters.shifts_relinks++;

                if (prev)
                    prev->next = curr->next;
                else
                    head = curr->next;

                delete curr;
                count--;
                return true;
            }

            prev = curr;
            curr = curr->next;
        }

        return false;
    }
};
