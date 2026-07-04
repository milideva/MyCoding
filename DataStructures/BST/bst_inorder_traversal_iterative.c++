#include <iostream>
#include <stack>
#include <vector>

using namespace std;

/*
  LeetCode 94: Binary Tree Inorder Traversal (Iterative)

  Algorithm: Explicit Stack
  1. Use a stack to simulate recursion.
  2. While `curr` is not null or stack is not empty:
     - Push all left children of `curr` onto the stack.
     - Pop the top node, visit it (add to result).
     - Set `curr` to the right child of the popped node.

  Complexity Analysis:
  - Time Complexity: O(N)
  - Space Complexity: O(H).
*/

struct Node {
    int key;
    Node *left, *right;
    Node(int x) : key(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<int> inorderTraversal(Node* root) {
        vector<int> res;
        stack<Node*> stk;
        Node* curr = root;

        while (curr || !stk.empty()) {
            while (curr) {
                stk.push(curr);
                curr = curr->left;
            }
            curr = stk.top();
            stk.pop();
            res.push_back(curr->key);
            curr = curr->right;
        }
        return res;
    }

    void destroy(Node* root) {
        if (!root) return;
        destroy(root->left);
        destroy(root->right);
        delete root;
    }
};

int main() {
    Node* root = new Node(100);
    root->left = new Node(50);
    root->right = new Node(150);
    root->left->left = new Node(30);
    root->left->right = new Node(60);

    Solution sol;
    vector<int> res = sol.inorderTraversal(root);
    
    cout << "Inorder Traversal: ";
    for (int x : res) cout << x << " ";
    cout << endl;

    sol.destroy(root);
    return 0;
}
