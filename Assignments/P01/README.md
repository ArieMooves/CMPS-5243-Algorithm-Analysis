# P01: BST Delete
## Aretha Fontaine

The following project displays how a delete method can be implemented in a Binary Search Tree, allowing recursive node deletion. A Binary Search Tree is a tree based data structure created for different kinds of searches, insertion and deletion, where a node is allowed to have a maximum of two children. The left child has a value below its parent node, while the right child is greater than its parent node. Test cases are inserted to allow you to visualize the various traversal operations that can be performed with this new method (delete). The test cases displayed include deletion in various scenarios: single node tree, multiple node tree, empty tree, one child node, two children nodes, and leaf node. Deletion of leaf nodes does not require much effort, as the ideal steps to take are to cut/remove the reference to the node and reclaim the memory. Unfortunately, this concept does not ring true for nodes with two children. The delete method will take in two arguments, a pointer reference to the parent node and the node we want to delete, in this case we can call it the stinky node. After deleting the stinky node, look for the minimum value on the right side, and replace the stinky node’s value with this new node. Delete the duplicate of the new node, and this should successfully carry out the node deletion. My initial mistake was creating the delete method as a void method, when it's meant to return a node pointer. 


|   #   | File             | Description                                        |
| :---: | ---------------- | -------------------------------------------------- |
|   1   | [bst.cpp](https://github.com/ArieMooves/CMPS-5243-Algorithm-Analysis/blob/main/Assignments/P01/bst.cpp)        | Binary Search Tree original code with 'delete' method inserted.    |



### Instructions:

### GitHub Codespace: Taking the following steps allows bst to be executable
###                   /workspaces/CMPS-5243-Algorithm-Analysis/Assignments/P01
###                   $ g++ bst.cpp -o bst
###                   $ ./bst
