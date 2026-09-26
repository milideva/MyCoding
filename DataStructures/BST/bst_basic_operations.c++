#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

/*
  Problem: Binary Search Tree (BST) Operations: Successor, Predecessor, Insertion, and Deletion

  Problem Description:
  Implement and compare core BST operations:
  - Insertion: Add a new value to the BST while maintaining its property.
  - Successor: Find the node with the smallest value larger than the given node.
  - Predecessor: Find the node with the largest value smaller than the given node.
  - Deletion (Recursive & Iterative): Remove a key from the BST while preserving its structure.

  =============================================================================
  Complexity Analysis:
  =============================================================================
  - Insertion (Recursive):
    - Time Complexity: Best O(1) if root; Average O(H) (O(log N)); Worst O(H) (O(N) for skewed tree).
    - Space Complexity: O(H) auxiliary space due to call stack.
  
  - Successor / Predecessor (Iterative):
    - Time Complexity: Best O(1); Average O(H) (O(log N)); Worst O(H) (O(N) for skewed tree).
    - Space Complexity: O(1) auxiliary space.

  - Recursive Deletion (deleteNode):
    - Time Complexity: Best O(1); Average O(H) (O(log N)); Worst O(H) (O(N) for skewed tree).
    - Space Complexity: O(H) auxiliary space due to call stack.

  - Iterative Deletion (deleteNodeIterative):
    - Time Complexity: Best O(1); Average O(H) (O(log N)); Worst O(H) (O(N) for skewed tree).
    - Space Complexity: O(1) auxiliary space (no call stack overhead, highly optimal).
*/

struct Node {
    int key;
    Node *left, *right;
    Node(int x) : key(x), left(nullptr), right(nullptr) {}
};

class BST {
public:
    // Insertion (Recursive)
    Node* insert(Node* root, int key) {
        if (!root) return new Node(key);
        if (key < root->key) root->left = insert(root->left, key);
        else if (key > root->key) root->right = insert(root->right, key);
        return root;
    }

    // Successor Search (Iterative)
    Node* getSuccessor(Node* root, int key) {
        Node* successor = nullptr;
        Node* curr = root;
        while (curr) {
            if (curr->key > key) {
                successor = curr;
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        return successor;
    }

    // Predecessor Search (Iterative)
    Node* getPredecessor(Node* root, int key) {
        Node* predecessor = nullptr;
        Node* curr = root;
        while (curr) {
            if (curr->key < key) {
                predecessor = curr;
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        }
        return predecessor;
    }

    // Search Helper (Iterative)
    bool search(Node* root, int key) {
        Node* curr = root;
        while (curr) {
            if (curr->key == key) return true;
            if (key < curr->key) curr = curr->left;
            else curr = curr->right;
        }
        return false;
    }

    // Helper to find the node with the minimum key in a given subtree
    Node* findMin(Node* node) {
        Node* curr = node;
        while (curr && curr->left) {
            curr = curr->left;
        }
        return curr;
    }

    // Recursive Deletion
    Node* deleteNode(Node* root, int key) {
        if (!root) return nullptr;

        if (key < root->key) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->key) {
            root->right = deleteNode(root->right, key);
        } else {
            // Node found
            if (!root->left) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (!root->right) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            // Two children case
            Node* temp = findMin(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
        return root;
    }

    // Iterative Deletion (O(1) Space)
    Node* deleteNodeIterative(Node* root, int key) {
        Node* curr = root;
        Node* parent = nullptr;

        // Step 1: Search for the node and its parent
        while (curr && curr->key != key) {
            parent = curr;
            if (key < curr->key) curr = curr->left;
            else curr = curr->right;
        }

        if (!curr) return root; // Key not found

        // Step 2: Handle node with at most 1 child
        if (!curr->left || !curr->right) {
            Node* newChild = curr->left ? curr->left : curr->right;

            if (!parent) return newChild; // Deleting the root

            if (parent->left == curr) parent->left = newChild;
            else parent->right = newChild;

            delete curr;
        } 
        // Step 3: Handle node with 2 children
        else {
            Node* succParent = curr;
            Node* succ = curr->right;
            while (succ->left) {
                succParent = succ;
                succ = succ->left;
            }

            // Copy successor value
            curr->key = succ->key;

            // Delete successor node
            if (succParent->left == succ) {
                succParent->left = succ->right;
            } else {
                succParent->right = succ->right;
            }

            delete succ;
        }

        return root;
    }

    // Destructor helper
    void destroy(Node* root) {
        if (!root) return;
        destroy(root->left);
        destroy(root->right);
        delete root;
    }
};

void run_test(const string& name, Node* actual, int expected_val) {
    int actual_val = actual ? actual->key : -1;
    bool passed = (actual && actual->key == expected_val) || (!actual && expected_val == -1);
    cout << name << ": Expected: " << (expected_val == -1 ? "None" : to_string(expected_val))
         << " Got: " << (actual ? to_string(actual_val) : "None") 
         << " " << (passed ? "PASS" : "FAIL") << endl;
}

void run_delete_test(const string& name, Node* root, int key, bool expected_found) {
    BST bst;
    bool found = bst.search(root, key);
    bool passed = (found == expected_found);
    cout << name << ": Expected: " << (expected_found ? "Found" : "Not Found")
         << " Got: " << (found ? "Found" : "Not Found")
         << " " << (passed ? "PASS" : "FAIL") << endl;
}

int main() {
    BST bst;
    
    // =========================================================================
    // Part 1: Basic Operations (Insertion, Successor, Predecessor)
    // =========================================================================
    cout << "--- Testing Basic BST Operations ---" << endl;
    Node* root = nullptr;
    int keys[] = {100, 50, 150, 30, 60, 170, 10, 40, 55, 75};
    for (int k : keys) root = bst.insert(root, k);

    run_test("Successor of 50", bst.getSuccessor(root, 50), 55);
    run_test("Predecessor of 50", bst.getPredecessor(root, 50), 40);
    run_test("Successor of 75", bst.getSuccessor(root, 75), 100);
    run_test("Predecessor of 75", bst.getPredecessor(root, 75), 60);
    run_test("Successor of 170", bst.getSuccessor(root, 170), -1);
    run_test("Predecessor of 170", bst.getPredecessor(root, 170), 150);

    // =========================================================================
    // Part 2: Recursive Deletion Tests
    // =========================================================================
    cout << "\n--- Testing Recursive Deletion (deleteNode) ---" << endl;
    // Leaf node deletion (10)
    root = bst.deleteNode(root, 10);
    run_delete_test("Delete Leaf Node (10)", root, 10, false);

    // Single-child node deletion (170)
    root = bst.deleteNode(root, 170);
    run_delete_test("Delete Single-Child Node (170)", root, 170, false);
    run_delete_test("Child 150 should still exist", root, 150, true);

    // Two-children node deletion (50)
    root = bst.deleteNode(root, 50);
    run_delete_test("Delete Two-Children Node (50)", root, 50, false);
    run_delete_test("Inorder successor 55 should exist", root, 55, true);

    // Root deletion (100)
    root = bst.deleteNode(root, 100);
    run_delete_test("Delete Root Node (100)", root, 100, false);
    
    bst.destroy(root);

    // =========================================================================
    // Part 3: Iterative Deletion Tests
    // =========================================================================
    cout << "\n--- Testing Iterative Deletion (deleteNodeIterative) ---" << endl;
    Node* rootIter = nullptr;
    for (int k : keys) rootIter = bst.insert(rootIter, k);

    // Leaf node deletion (10)
    rootIter = bst.deleteNodeIterative(rootIter, 10);
    run_delete_test("Delete Leaf Node (10)", rootIter, 10, false);

    // Single-child node deletion (170)
    rootIter = bst.deleteNodeIterative(rootIter, 170);
    run_delete_test("Delete Single-Child Node (170)", rootIter, 170, false);
    run_delete_test("Child 150 should still exist", rootIter, 150, true);

    // Two-children node deletion (50)
    rootIter = bst.deleteNodeIterative(rootIter, 50);
    run_delete_test("Delete Two-Children Node (50)", rootIter, 50, false);
    run_delete_test("Inorder successor 55 should exist", rootIter, 55, true);

    // Root deletion (100)
    rootIter = bst.deleteNodeIterative(rootIter, 100);
    run_delete_test("Delete Root Node (100)", rootIter, 100, false);

    bst.destroy(rootIter);
    return 0;
}
