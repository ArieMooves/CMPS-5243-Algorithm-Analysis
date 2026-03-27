#pragma once

#include "bst.hpp"
#include <algorithm>

class Avl : public Bst {
private:
    // Height helper
    int height(Node *node) const {
        return node ? node->height : 0;
    }

    // Balance factor
    int balanceFactor(Node *node) const {
        return node ? height(node->left) - height(node->right) : 0;
    }

    // Update height
    void updateHeight(Node *node) {
        if (node) {
            counters.structural_ops++; // maintaining structure
            node->height = 1 + std::max(height(node->left), height(node->right));
        }
    }

    // Right rotation
    Node *rotateRight(Node *y) {
        counters.structural_ops++;   // rotation is structural
        counters.shifts_relinks++;   // pointer rewiring

        Node *x = y->left;
        Node *t2 = x->right;

        x->right = y;
        y->left = t2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // Left rotation
    Node *rotateLeft(Node *x) {
        counters.structural_ops++;
        counters.shifts_relinks++;

        Node *y = x->right;
        Node *t2 = y->left;

        y->left = x;
        x->right = t2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // Rebalance tree
    Node *rebalance(Node *node) {
        updateHeight(node);

        int bf = balanceFactor(node);

        counters.comparisons++;
        if (bf > 1) {
            counters.comparisons++;
            if (balanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left); // LR
            }
            return rotateRight(node); // LL
        }

        counters.comparisons++;
        if (bf < -1) {
            counters.comparisons++;
            if (balanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right); // RL
            }
            return rotateLeft(node); // RR
        }

        return node;
    }

    // Insert helper
    Node *insert(Node *node, int value, bool &inserted) {
        if (!node) {
            counters.structural_ops++;
            inserted = true;
            return new Node(value);
        }

        counters.comparisons++;
        if (value < node->data) {
            node->left = insert(node->left, value, inserted);
        } else {
            counters.comparisons++;
            if (value > node->data) {
                node->right = insert(node->right, value, inserted);
            } else {
                inserted = false; // duplicate
                return node;
            }
        }

        return rebalance(node);
    }

    // Delete helper
    Node *erase(Node *node, int value, bool &erased) {
        if (!node) {
            erased = false;
            return nullptr;
        }

        counters.comparisons++;
        if (value < node->data) {
            node->left = erase(node->left, value, erased);
        } else {
            counters.comparisons++;
            if (value > node->data) {
                node->right = erase(node->right, value, erased);
            } else {
                erased = true;

                // 0 or 1 child
                if (!node->left || !node->right) {
                    counters.structural_ops++;

                    Node *child = node->left ? node->left : node->right;
                    delete node;
                    return child;
                }

                // 2 children
                Node *successor = findMin(node->right);
                node->data = successor->data;

                node->right = erase(node->right, successor->data, erased);
            }
        }

        return rebalance(node);
    }

public:
    Avl() : Bst() {}

    // ➕ INSERT
    bool insert(int value) {
        counters.inserts++;

        bool inserted = false;
        root = insert(root, value, inserted);
        return inserted;
    }

    // DELETE
    bool erase(int value) {
        counters.deletes++;

        bool erased = false;
        root = erase(root, value, erased);
        return erased;
    }

    // LOOKUP (reuse BST)
    bool contains(int value) {
        counters.lookups++;
        return Bst::contains(value);
    }

    const char *name() const {
        return "AVL";
    }

    int height() const {
        return height(root);
    }
};
