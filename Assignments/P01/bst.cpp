#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
     int data;
     Node* left; // left child
     Node* right; // right child

     Node(int x) { 
          data = x;
          left = right = nullptr; // initialize children to nullptr
     }
};

class GraphvizBST { 
public:
     static void saveDotFile(const std::string& filename, const std::string& dotContent) { // Save DOT content to a file
          std::ofstream outFile(filename); // Open file for writing
          if (outFile.is_open()) {
               outFile << dotContent; // Write DOT content to file
               outFile.close();
               std::cout << "DOT file saved: " << filename << std::endl; 
          }
          else {
               std::cerr << "Error: Could not open file " << filename << std::endl;
          }
     }

     static std::string generateDot(const Node* root) { // Generate DOT representation of the BST
          std::string dot = "digraph BST {\n"; 
          dot += "    node [fontname=\"Arial\"];\n"; 
          dot += generateDotHelper(root); // Recursive helper to generate DOT content
          dot += "}\n";
          return dot;
     }

private:
     static std::string generateDotHelper(const Node* node) { // Recursive helper to generate DOT content
          if (!node)
               return "";
          std::string result;
          if (node->left) {
               result += "    " + std::to_string(node->data) + " -> " + std::to_string(node->left->data) + " [label=\"L\"];\n"; // Edge to left child
               result += generateDotHelper(node->left); // Recursive call for left subtree
          }
          else {
               std::string nullNode = "nullL" + std::to_string(node->data); // Create a null node for left child
               result += "    " + nullNode + " [shape=point];\n"; // Define null node
               result += "    " + std::to_string(node->data) + " -> " + nullNode + ";\n"; // Edge to null node
          }
          if (node->right) {
               result += "    " + std::to_string(node->data) + " -> " + std::to_string(node->right->data) + " [label=\"R\"];\n"; // Edge to right child
               result += generateDotHelper(node->right); // Recursive call for right subtree
          }
          else {
               std::string nullNode = "nullR" + std::to_string(node->data); // Create a null node for right child
               result += "    " + nullNode + " [shape=point];\n"; // Define null node
               result += "    " + std::to_string(node->data) + " -> " + nullNode + ";\n"; // Edge to null node
          }
          return result;
     }
};

class Bst {
     Node* root;

     void _print(Node* subroot) { 
          if (!subroot) {
               return;
          }
          else {
               _print(subroot->left);
               cout << subroot->data << " ";
               _print(subroot->right);
          }
     }
     void _insert(Node*& subroot, int x) { // Node*& to modify the pointer itself
          if (!subroot) { // if(root == nullptr)
               subroot = new Node(x); 
          }
          else {
               if (x < subroot->data) {    // go left
                    _insert(subroot->left, x); // recursive call
               }
               else {
                    _insert(subroot->right, x); // go right
               }
          }
     }
     int _ipl(Node* root, int depth = 0) {
          if (!root)
               return 0; // Base case: Empty subtree contributes 0 to IPL
          return depth + _ipl(root->left, depth + 1) + _ipl(root->right, depth + 1); // Recursive case: Sum depth and IPL of subtrees
     }

    

     Node* _deleteNode(Node* subroot, int key) { // helper function to delete nodes recursively
          if (!subroot) { // base case: key not found
               return nullptr;
          }
          if (key < subroot->data) { 
               subroot->left = _deleteNode(subroot->left, key); // go left
          }
          else if (key > subroot->data) {
               subroot->right = _deleteNode(subroot->right, key); // go right
          }
          else {
                              
               if (!subroot->left) { // no left child
                    Node* temp = subroot->right; // promote right child
                    delete subroot; // free memory
                    return temp;
               }
               
               else if (!subroot->right) { // no right child
                    Node* temp = subroot->left; // promote left child
                    delete subroot; // free memory
                    return temp;
               }

               // two children
               Node* temp = subroot->right; // find inorder successor
               while (temp->left) // go to leftmost node
                    temp = temp->left;

               subroot->data = temp->data; // copy inorder successor's data
               subroot->right = _deleteNode(subroot->right, temp->data); // delete inorder successor
          }

          return subroot;
     
          
        
     }

public:
     Bst() { root = nullptr; }
     void insert(int x) { _insert(root, x); } 
     bool search(int key) { return 0; }
     void print() { _print(root); }
     void saveDotFile(const std::string& filename) {
          std::string dotContent = GraphvizBST::generateDot(root);
          GraphvizBST::saveDotFile(filename, dotContent);}
     void deleteNode(int key) { root = _deleteNode(root, key);} 
     
     int ipl() {
          return _ipl(root); // Start IPL calculation from root at depth 0
     }
};

bool unique_value(int* arr, int n, int x) { // check if x is unique in arr
     for (int i = 0; i < n; i++) {
          if (arr[i] == x) {
               return false;
          }
     }
     return true;
}

int main() {
     Bst tree; // create random BST tree (big)
     int root = (1 << 15) / 2; // edit: pow() returned double, and produced errror in some compilers
     int max = (1 << 15) - 1;
     vector<int> arr; // to store unique values
     arr.push_back(root);
     tree.insert(root);
     for (int i = 1; i < 5000; i++) { // insert 5000 unique random values -- size reduced to 
          int r = rand() % max;
          while (!unique_value(arr.data(), arr.size(), r)) { 
               r = rand() % max;
          }
          tree.insert(r);
          arr.push_back(r); 
     }
     
     
     tree.print();
     tree.saveDotFile("\n\nbst_snapshot.dot"); // Save the BST structure to a DOT file

     Bst tree2; // create small BST for testing IPL
     tree2.insert(10);
     tree2.insert(5);
     tree2.insert(15);
     tree2.insert(2);
     tree2.insert(7);
     tree2.insert(20);
     cout << "Internal Path Length: " << tree2.ipl() << endl ; // Calculate and print IPL

     Bst emptytree; // create empty BST for testing deletion from empty tree
     cout << "\n\nBefore delete (empty tree):\n";
     emptytree.print(); // should print nothing

     emptytree.deleteNode(10); //delete from an empty tree
     emptytree.saveDotFile("empty_tree.dot"); // Save empty tree to DOT file
     cout << "Internal Path Length: " << emptytree.ipl() << endl; // Calculate and print IPL

     Bst singleNodeTree; // create single node BST for testing deletion
     singleNodeTree.insert(10); // insert single node
     cout << "\n\nBefore delete (single node):\n";
     singleNodeTree.print();

     singleNodeTree.deleteNode(10); // delete the only node
     cout << "\nAfter delete:\n";
     singleNodeTree.print(); // should print nothing
     singleNodeTree.saveDotFile("single_node_tree.dot"); // Save single node tree to DOT file
     cout << "Internal Path Length: " << singleNodeTree.ipl() << endl; // Calculate and print IPL

     Bst MultiNodeTree; // create multi-node BST for testing deletion
     MultiNodeTree.insert(22);
     MultiNodeTree.insert(24);
     MultiNodeTree.insert(19);
     MultiNodeTree.insert(3);
     MultiNodeTree.insert(29);
     MultiNodeTree.insert(1);
     cout << "\n\nBefore delete (multi-node):\n";
     MultiNodeTree.print();

     MultiNodeTree.deleteNode(1); // delete a leaf node
     cout << "\nAfter delete:\n";
     MultiNodeTree.print();
     MultiNodeTree.saveDotFile("multi_node_tree.dot"); // Save multi-node tree to DOT file
     cout << "Internal Path Length: " << MultiNodeTree.ipl() << endl; // Calculate and print IPL

     Bst removal; // create small BST for testing deletion with two children
     removal.insert(10);
     removal.insert(5);
     removal.insert(15);
     removal.insert(2);
     removal.insert(7);
     removal.insert(20);

     cout << "\nBefore delete (two children):\n";
     removal.print();
     removal.deleteNode(10);
     cout << "\nAfter delete:\n";
     removal.print();

     Bst removal2; // create small BST for testing deletion with one child
     removal2.insert(10);
     removal2.insert(5);
     removal2.insert(15);
     removal2.insert(2);
     removal2.insert(7);
     removal2.insert(20);

     cout << "\n\nBefore delete (one child):\n";
     removal2.print();
     removal2.deleteNode(15);
     cout << "\nAfter delete:\n";
     removal2.print();

     Bst removal3; // create small BST for testing deletion of leaf node
     removal3.insert(10);
     removal3.insert(5);
     removal3.insert(15);
     removal3.insert(2);
     removal3.insert(7);
     removal3.insert(20);

     cout << "\n\nBefore delete (Leaf Node):\n";
     removal3.print();
     removal3.deleteNode(20);
     cout << "\nAfter delete:\n";
     removal3.print();
   
     return 0;
}
