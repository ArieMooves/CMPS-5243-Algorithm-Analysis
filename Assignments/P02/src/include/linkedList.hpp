#include <iostream>

class LinkedList {
private:
    struct Node {
        int data;
        Node *next;

        Node(int v) : data(v), next(nullptr) {}
    };

    Node *head;
    std::size_t counter;  // Tracks number of elements

public:
    LinkedList() : head(nullptr), counter(0) {}

    ~LinkedList() {
        Node *curr = head;

        while (curr) {
            Node *temp = curr;
            curr = curr->next;
            delete temp;
        }

        counter = 0; 
    }

    bool insert(int value) {
        if (contains(value))
            return false;

        Node *n = new Node(value);

        n->next = head;
        head = n;

        counter++;  // increment count
        return true;
    }

    bool contains(int value) const {
        Node *curr = head;

        while (curr) {
            if (curr->data == value)
                return true;

            curr = curr->next;
        }

        return false;
    }

    bool erase(int value) {
        Node *curr = head;
        Node *prev = nullptr;

        while (curr) {
            if (curr->data == value) {

                if (prev)
                    prev->next = curr->next;
                else
                    head = curr->next;

                delete curr;
                counter--;  // decrement count
                return true;
            }

            prev = curr;
            curr = curr->next;
        }

        return false;
    }

    void print() const {
        Node *curr = head;

        while (curr) {
            std::cout << curr->data << " ";
            curr = curr->next;
        }

        std::cout << "\n";
    }

    // Returns number of elements
    std::size_t size() const {
        return counter;
    }
};
