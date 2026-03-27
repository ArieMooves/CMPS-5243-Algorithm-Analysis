// run_workload.cpp
#include "bst.hpp"
#include "avl.hpp"
#include "hashTable.hpp"
#include "LinkedList.hpp"
#include "sortedArraySet.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <filesystem>
#include "json.hpp"

using json = nlohmann::json;
namespace fs = std::filesystem;
using namespace std;

// Helper function to run workload on a container and return counters
template <typename Container>
Counters runOps(Container &c, const json &workload) {
    c.reset();

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

// Print counters in table format
void printCountersMarkdown(const string &name, const Counters &c) {
    cout << "| " << left << setw(12) << name
         << " | " << setw(10) << c.comparisons
         << " | " << setw(9) << c.structural_ops
         << " | " << setw(7) << c.inserts
         << " | " << setw(7) << c.deletes
         << " | " << setw(7) << c.lookups
         << " | " << setw(9) << c.resize_events
         << " |\n";
}

int main() {
    string folder = "work_files";

    for (const auto &entry : fs::directory_iterator(folder)) {
        if (entry.path().extension() != ".json") continue;

        string filename = entry.path().string();
        cout << "\n### Workload: " << entry.path().filename().string() << "\n";

        ifstream f(filename);
        if (!f) {
            cerr << "Error: Could not open " << filename << endl;
            continue;
        }

        json workload;
        f >> workload;

        // Initialize all structures
        Bst bst;
        Avl avl;
        HashTable ht(101);
        LinkedList ll;
        SortedArraySet sas;

        // Run operations
        Counters bstC = runOps(bst, workload);
        Counters avlC = runOps(avl, workload);
        Counters htC  = runOps(ht, workload);
        Counters llC  = runOps(ll, workload);
        Counters sasC = runOps(sas, workload);

        // Print markdown table header
        cout << "| Structure     | Comparisons | StructOps | Inserts | Deletes | Lookups | ResizeEv |\n";
        cout << "|---------------|------------|-----------|--------|--------|--------|----------|\n";

        printCountersMarkdown("BST", bstC);
        printCountersMarkdown("AVL", avlC);
        printCountersMarkdown("HashTable", htC);
        printCountersMarkdown("LinkedList", llC);
        printCountersMarkdown("SortedArray", sasC);
    }

    return 0;
}
