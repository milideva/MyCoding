#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
  Problem: Binary Search Tree (BST) Operations: Successor, Predecessor, Insertion

  Problem Description:
  Implement core BST operations:
  - Successor: Find the node with the smallest value larger than the 
    given node.
  - Predecessor: Find the node with the largest value smaller than the 
    given node.
  - Insertion: Add a new value to the BST while maintaining its property.

  Algorithm:
  - Successor: Smallest element in right subtree if it exists; 
    else closest left-turn ancestor.
  - Predecessor: Largest element in left subtree if it exists; 
    else closest right-turn ancestor.

  Complexity Analysis:
  - Time Complexity: O(H) where H is the tree height.
  - Space Complexity: O(H) for recursion stack.
*/

struct Node {
    int key;
    Node *left, *right;
    Node(int x) : key(x), left(nullptr), right(nullptr) {}
};

class BST {
public:
    Node* insert(Node* root, int key) {
        if (!root) return new Node(key);
        if (key < root->key) root->left = insert(root->left, key);
        else if (key > root->key) root->right = insert(root->right, key);
        return root;
    }

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

    void destroy(Node* root) {
        if (!root) return;
        destroy(root->left);
        destroy(root->right);
        delete root;
    }
};

void test(Node* root, int key, int expectedSucc, int expectedPred) {
    BST bst;
    Node* succ = bst.getSuccessor(root, key);
    Node* pred = bst.getPredecessor(root, key);
    
    cout << "Key: " << key;
    if (succ) cout << " Succ: " << succ->key; else cout << " Succ: None";
    if (pred) cout << " Pred: " << pred->key; else cout << " Pred: None";
    
    bool pass = true;
    if (succ && succ->key != expectedSucc && expectedSucc != -1) pass = false;
    if (!succ && expectedSucc != -1) pass = false;
    if (pred && pred->key != expectedPred && expectedPred != -1) pass = false;
    if (!pred && expectedPred != -1) pass = false;
    
    cout << (pass ? " [PASS]" : " [FAIL]") << endl;
}

int main() {
    BST bst;
    Node* root = nullptr;
    int keys[] = {100, 50, 150, 30, 60, 170, 10, 40, 55, 75};
    for (int k : keys) root = bst.insert(root, k);

    test(root, 50, 55, 40);
    test(root, 75, 100, 60);
    test(root, 170, -1, 150);

    bst.destroy(root);
    return 0;
}
