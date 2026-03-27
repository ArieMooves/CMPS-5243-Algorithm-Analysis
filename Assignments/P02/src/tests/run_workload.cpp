// run_workload.cpp
#include "../include/bst.hpp"
#include "../include/avl.hpp"
#include "../include/hashTables.hpp"
#include "../include/LinkedList.hpp"
#include "../include/sortedArraySet.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <filesystem>  // C++17 for directory iteration
#include "json.hpp"

using json = nlohmann::json;
namespace fs = std::filesystem;
using namespace std;

// Helper function to run workload on a container and return counters
template <typename Container>
Counters runOps(Container &c, const json &workload) {
    c.reset();  // reset counters

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

// Helper function to print counters nicely in a table
void printCounters(const string &name, const Counters &c) {
    cout << left << setw(15) << name
         << setw(15) << c.comparisons
         << setw(15) << c.structural_ops
         << setw(15) << c.inserts
         << setw(15) << c.deletes
         << setw(15) << c.lookups
         << setw(15) << c.resize_events
         << endl;
}

int main() {
    string folder = "work_files";

    // Iterate through all JSON files in work_files
    for (const auto &entry : fs::directory_iterator(folder)) {
        if (entry.path().extension() != ".json") continue;

        string filename = entry.path().string();
        cout << "\n=== Running workload: " << filename << " ===\n";

        ifstream f(filename);
        if (!f) {
            cerr << "Error: Could not open " << filename << endl;
            continue;
        }

        json workload;
        f >> workload;

        // Initialize all data structures
        Bst bst;
        Avl avl;
        HashTable ht(101);
        LinkedList ll;
        SortedArraySet sas;

        // Run workload and collect counters
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

        printCounters("BST", bstC);
        printCounters("AVL", avlC);
        printCounters("HashTable", htC);
        printCounters("LinkedList", llC);
        printCounters("SortedArray", sasC);
    }

    return 0;
}
