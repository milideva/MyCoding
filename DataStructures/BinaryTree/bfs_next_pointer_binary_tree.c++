/**
 * Problem: Populating Next Right Pointers in Each Node
 * You are given a binary tree where each node has a 'next' pointer. 
 * Initially, all next pointers are set to NULL. Populate each next 
 * pointer to point to its next right node.
 * 
 * Strategy: BFS (Level Order Traversal)
 * - For each level, iterate through nodes and link them using the queue's front element.
 * 
 * Time Complexity: O(N) - Every node is visited once.
 * Space Complexity: O(W) - W is the maximum width of the tree.
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
    int val;
    Node *left, *right, *next;
    Node(int x) : val(x), left(nullptr), right(nullptr), next(nullptr) {}
};

class Solution {
public:
    /**
     * Populates the 'next' pointers using BFS.
     */
    Node* connect(Node* root) {
        if (!root) return nullptr;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                Node* curr = q.front();
                q.pop();

                // Link to the next node in the same level
                if (i < size - 1) {
                    curr->next = q.front();
                }

                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
        }
        return root;
    }
};

/**
 * Utility to print levels using 'next' pointers.
 */
void printLevels(Node* root) {
    Node* levelStart = root;
    while (levelStart) {
        Node* curr = levelStart;
        while (curr) {
            cout << curr->val << (curr->next ? " -> " : " -> NULL");
            curr = curr->next;
        }
        cout << endl;

        // Find the first node of the next level
        Node* nextLevel = nullptr;
        curr = levelStart;
        while (curr && !nextLevel) {
            if (curr->left) nextLevel = curr->left;
            else if (curr->right) nextLevel = curr->right;
            curr = curr->next;
        }
        levelStart = nextLevel;
    }
}

int main() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    Solution sol;
    sol.connect(root);

    cout << "Populated 'next' pointers level-by-level:" << endl;
    printLevels(root);

    return 0;
}
