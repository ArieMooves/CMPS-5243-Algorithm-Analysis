
#include "bst.hpp"
#include "avl.hpp"
#include "hashTables.hpp"
#include "LinkedList.hpp"
#include "sortedArraySet.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <filesystem>
#include "json.hpp"
#include "run_workload.cpp"  

using json = nlohmann::json;
using namespace std;

// Helper to run workload
template <typename Container>
Counters runOps(Container &c, const json &workload) {
    c.reset(); // reset counters
    for (const auto &op : workload) {
        int value = op["value"];
        string action = op["op"];
        if (action == "insert") c.insert(value);
        else if (action == "delete") c.erase(value);
        else if (action == "lookup") c.contains(value);
    }
    return c.getCounters();
}

int main() {
    // Optionally, loop over all JSON files in work_files/
    string folder = "work_files";
    for (const auto &entry : filesystem::directory_iterator(folder)) {
        string filename = entry.path().string();
        cout << "Processing: " << filename << endl;

        ifstream f(filename);
        if (!f) { cerr << "Error opening " << filename << endl; continue; }

        json workload;
        f >> workload;

        // Initialize structures
        Bst bst;
        Avl avl;
        HashTable ht(101);
        LinkedList ll;
        SortedArraySet sas;

        // Run workloads
        Counters bstC = runOps(bst, workload);
        Counters avlC = runOps(avl, workload);
        Counters htC  = runOps(ht, workload);
        Counters llC  = runOps(ll, workload);
        Counters sasC = runOps(sas, workload);

        // Print table
        auto printCounters = [](const string &name, const Counters &c) {
            cout << left << setw(12) << name
                 << setw(12) << c.comparisons
                 << setw(12) << c.structural_ops
                 << setw(12) << c.inserts
                 << setw(12) << c.deletes
                 << setw(12) << c.lookups
                 << setw(12) << c.resize_events
                 << endl;
        };

        cout << left << setw(12) << "Structure"
             << setw(12) << "Comparisons"
             << setw(12) << "StructOps"
             << setw(12) << "Inserts"
             << setw(12) << "Deletes"
             << setw(12) << "Lookups"
             << setw(12) << "ResizeEv"
             << endl;

        printCounters("BST", bstC);
        printCounters("AVL", avlC);
        printCounters("HashTable", htC);
        printCounters("LinkedList", llC);
        printCounters("SortedArray", sasC);

        cout << string(80, '-') << endl;
    }

    return 0;
}
