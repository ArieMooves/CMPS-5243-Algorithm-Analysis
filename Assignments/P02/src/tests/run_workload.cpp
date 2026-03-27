// run_workload.cpp
#include "../include/bst.hpp"
#include "../include/avl.hpp"
#include "../include/hashTables.hpp"
#include "../include/LinkedList.hpp"
#include "../include/sortedArraySet.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>  // for table formatting
#include "json.hpp" // make sure this is available as nlohmann::json

using json = nlohmann::json;
using namespace std;

// Helper function to run workload on a container
template <typename Container>
Counters runOps(Container &c, const json &workload) {
    c.reset(); // reset counters

    for (const auto &op : workload) {
        int value = op["value"];
        string action = op["op"];

        if (action == "insert") {
            c.insert(value);
        } else if (action == "delete") {
            c.erase(value);
        } else if (action == "lookup") {
            c.contains(value);
        }
    }

    return c.getCounters();
}

int main() {
    string filename = "workload.json";

    // Check if file exists
    ifstream f(filename);
    if (!f) {
        cerr << "Error: Could not open " << filename << endl;
        return 1;
    }

    json workload;
    f >> workload;

    // Initialize all data structures
    Bst bst;
    Avl avl;
    HashTable ht(101);
    LinkedList ll;
    SortedArraySet sas;

    // Run workload on each structure and collect counters
    Counters bstC = runOps(bst, workload);
    Counters avlC = runOps(avl, workload);
    Counters htC  = runOps(ht, workload);
    Counters llC  = runOps(ll, workload);
    Counters sasC = runOps(sas, workload);

    // Print table header
    cout << left << setw(15) << "Structure"
         << setw(15) << "Comparisons"
         << setw(15) << "StructOps"
         << setw(15) << "Inserts"
         << setw(15) << "Deletes"
         << setw(15) << "Lookups"
         << setw(15) << "ResizeEv"
         << endl;

    auto printCounters = [](const string &name, const Counters &c) {
        cout << left << setw(15) << name
             << setw(15) << c.comparisons
             << setw(15) << c.structural_ops
             << setw(15) << c.inserts
             << setw(15) << c.deletes
             << setw(15) << c.lookups
             << setw(15) << c.resize_events
             << endl;
    };

    printCounters("BST", bstC);
    printCounters("AVL", avlC);
    printCounters("HashTable", htC);
    printCounters("LinkedList", llC);
    printCounters("SortedArray", sasC);

    return 0;
}
