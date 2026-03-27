#pragma once

#include "counters.hpp"
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <string>

using json = nlohmann::json;
using namespace std;

class Bst {
protected:
    struct Node {
        int data;
        Node *left;
        Node *right;
        int height;  // REQUIRED for AVL

        explicit Node(int value)
            : data(value), left(nullptr), right(nullptr), height(1) {}
    };

    Node *root;
    mutable Counters counters;

    // Recursive insert helper
    bool insert(Node *&node, int value) {
        counters.comparisons++;
        if (!node) {
            counters.structural_ops++;
            node = new Node(value);
            return true;
        }

        counters.comparisons++;
        if (value < node->data) {
            return insert(node->left, value);
        }

        counters.comparisons++;
        if (value > node->data) {
            return insert(node->right, value);
        }

        return false; // duplicate
    }

    // Recursive search helper
    bool contains(Node *node, int value) const {
        if (!node) return false;

        counters.comparisons++;
        if (value == node->data) return true;

        counters.comparisons++;
        if (value < node->data)
            return contains(node->left, value);

        return contains(node->right, value);
    }

    // Find minimum (used in delete)
    Node *findMin(Node *node) const {
        while (node && node->left) {
            counters.comparisons++;
            node = node->left;
        }
        return node;
    }

    // Delete helper
    bool erase(Node *&node, int value) {
        if (!node) return false;

        counters.comparisons++;
        if (value < node->data)
            return erase(node->left, value);

        counters.comparisons++;
        if (value > node->data)
            return erase(node->right, value);

        // FOUND NODE

        // Case 1: leaf
        if (!node->left && !node->right) {
            counters.structural_ops++;
            delete node;
            node = nullptr;
            return true;
        }

        // Case 2: one child (right)
        if (!node->left) {
            counters.structural_ops++;
            Node *temp = node;
            node = node->right;
            delete temp;
            return true;
        }

        // Case 3: one child (left)
        if (!node->right) {
            counters.structural_ops++;
            Node *temp = node;
            node = node->left;
            delete temp;
            return true;
        }

        // Case 4: two children
        Node *successor = findMin(node->right);
        node->data = successor->data;

        return erase(node->right, successor->data);
    }

    // Cleanup
    void clear(Node *node) {
        if (!node) return;

        clear(node->left);
        clear(node->right);

        counters.structural_ops++;
        delete node;
    }

public:
    Bst() : root(nullptr) {}

    ~Bst() {
        clear(root);
    }

    // Reset structure
    void reset() {
        clear(root);
        root = nullptr;
    }

    // Reset counters
    void reset_counters() {
        counters = Counters{};
    }

    Counters getCounters() {
        return counters;
    }

    // INSERT
    bool insert(int value) {
        counters.inserts++;
        return insert(root, value);
    }

    // LOOKUP
    bool contains(int value) {
        counters.lookups++;
        return contains(root, value);
    }

    // DELETE
    bool erase(int value) {
        counters.deletes++;
        return erase(root, value);
    }

    virtual const char *name() const {
        return "BST";
    }
};
