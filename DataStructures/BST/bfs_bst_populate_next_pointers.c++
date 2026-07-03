/*
LeetCode 116: Populating Next Right Pointers in Each Node

You are given a perfect binary tree where all leaves are on the same level, 
and every parent has two children. The binary tree has the following definition:

struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
};

Populate each next pointer to point to its next right node. 
If there is no next right node, the next pointer should be set to NULL.
Initially, all next pointers are set to NULL.

Example:
Input: root = [1,2,3,4,5,6,7]
Output: [1,#,2,3,#,4,5,6,7,#]
Explanation: Given the above perfect binary tree, your function should populate each next pointer to point to its next right node.
*/

#include <iostream>
#include <queue>

using namespace std;

struct Node {
    int val;
    Node *left;
    Node *right;
    Node *next;

    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}
};

class Solution {
public:
    Node* connect(Node* root) {
        if (!root) return nullptr;
        
        queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            int levelSize = q.size();
            
            for (int i = 0; i < levelSize; i++) {
                Node* curr = q.front();
                q.pop();
                
                // If this is not the last node in the current level,
                // point its 'next' to the front of the queue.
                if (i < levelSize - 1) {
                    curr->next = q.front();
                }
                
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
        }
        return root;
    }
    
    void printLevelsWithNext(Node* root) {
        Node* levelStart = root;
        while (levelStart) {
            Node* curr = levelStart;
            while (curr) {
                cout << curr->val << (curr->next ? " -> " : " -> NULL");
                curr = curr->next;
            }
            cout << endl;
            levelStart = levelStart->left;
        }
    }

    void destroyTree(Node* root) {
        if (!root) return;
        destroyTree(root->left);
        destroyTree(root->right);
        delete root;
    }
};

int main() {
    Solution sol;

    // Constructing a perfect binary tree: [1,2,3,4,5,6,7]
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    sol.connect(root);
    
    cout << "Connections using 'next' pointers:" << endl;
    sol.printLevelsWithNext(root);

    sol.destroyTree(root);
    return 0;
}
