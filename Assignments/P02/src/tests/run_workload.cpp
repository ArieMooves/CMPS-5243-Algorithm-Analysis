#include "bst.hpp"
#include "avl.hpp"
#include "hashTables.hpp"
#include "LinkedList.hpp"
#include "sortedArraySet.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include "workload_generator.cpp"  

int main() {
    
    std::string filename = "workload.json";
    generateWorkload(filename, 1000); // pseudo-function from workload_generator

    // Create structures
    Bst bst;
    Avl avl;
    HashTable ht(101);
    LinkedList ll;
    SortedArraySet sas;

    // Load workload
    std::ifstream f(filename);
    nlohmann::json j;
    f >> j;

    // Run operations
    for (auto &op : j) {
        int value = op["value"];
        std::string action = op["op"];

        if (action == "insert") {
            bst.insert(value);
            avl.insert(value);
            ht.insert(value);
            ll.insert(value);
            sas.insert(value);
        } else if (action == "delete") {
            bst.erase(value);
            avl.erase(value);
            ht.erase(value);
            ll.erase(value);
            sas.erase(value);
        } else if (action == "lookup") {
            bst.contains(value);
            avl.contains(value);
            ht.contains(value);
            ll.contains(value);
            sas.contains(value);
        }
    }

    // Print counters 
    std::cout << "BST: " << bst.getCounters() << std::endl;
    std::cout << "AVL: " << avl.getCounters() << std::endl;
    std::cout << "HashTable size: " << ht.size() << std::endl;
    std::cout << "LinkedList size: " << ll.size() << std::endl;
    std::cout << "SortedArraySet size: " << sas.size() << std::endl;

    return 0;
}
