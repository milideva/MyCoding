
#include <vector>
#include <list>
#include <iostream>
#include <unordered_set>
#include <queue>

using namespace std;
 
/*

236. Lowest Common Ancestor of a Binary Tree

Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is
defined between two nodes p and q as the lowest node in T that has both p and q
as descendants (where we allow a node to be a descendant of itself).”

This solution assumes parent pointer is present in a node.

Example 1:
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.

Example 2:
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.

Example 3:
Input: root = [1,2], p = 1, q = 2
Output: 1

*/

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode *parent;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr), parent(nullptr) {}
};

class Solution {
public:
  TreeNode* lowestCommonAncestor (TreeNode* p, TreeNode * q) {
    unordered_set <TreeNode *> uset;
    if (!p || !q) return nullptr;
    
    // Path from p to root
    TreeNode* curr = p;
    while (curr) {
      uset.insert(curr);
      curr = curr->parent;
    }

    // Path from q to root, first common node is LCA
    curr = q;
    while (curr) {
      if (uset.find(curr) != uset.end()) return curr;
      curr = curr->parent;
    }

    return nullptr;
  }
};

// MARKER is a sentinel value used to represent a null/empty node in the level-order input vector.
// Since int cannot be null in C++, we use -1 as a marker to represent the absence of a child
// node at a specific position, mirroring LeetCode's 'null' representation in their binary tree inputs.
const int MARKER = -1;

// Builds a tree from a standard LeetCode-style level-order vector.
// Use MARKER to represent null/empty nodes.
TreeNode* createTreeFromLevelOrder(const vector<int>& arr) {
    if (arr.empty() || arr[0] == MARKER) return nullptr;

    TreeNode* root = new TreeNode(arr[0]);
    queue<TreeNode*> q;
    q.push(root);

    size_t i = 1;
    while (!q.empty() && i < arr.size()) {
        TreeNode* current = q.front();
        q.pop();
       // We process next two nodes, left first and then right
        // Process Left Child
        if (i < arr.size() && arr[i] != MARKER) {
            TreeNode *left = new TreeNode(arr[i]);
            left->parent = current; // Instantly wire parent connection safely
            current->left = left;
            q.push(left);
        }

        i++;

        // Process Right Child
        if (i < arr.size() && arr[i] != MARKER) {
            TreeNode *right = new TreeNode(arr[i]);
            right->parent = current; // Instantly wire parent connection safely
           current->right = right;
            q.push(right);
        }
        i++;
    }

    return root;
}

// Helper to find a node by value (useful for testing)
TreeNode* findNode(TreeNode* root, int val) {
    if (!root || root->val == val) return root;
    TreeNode* left = findNode(root->left, val);
    if (left) return left;
    return findNode(root->right, val);
}

// Helper to free memory
void destroyTree(TreeNode* root) {
    if (!root) return;
    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
}

int main() {
    Solution sol;

    // Example 1: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
    // Using MARKER for 'null' nodes.
    vector<int> nodes1 = {3, 5, 1, 6, 2, 0, 8, MARKER, MARKER, 7, 4};
    TreeNode* root1 = createTreeFromLevelOrder(nodes1);

    TreeNode* p1 = findNode(root1, 5);
    TreeNode* q1 = findNode(root1, 1);

    TreeNode* lca1 = sol.lowestCommonAncestor(p1, q1);
    cout << "Example 1: LCA of 5 and 1 is " << (lca1 ? to_string(lca1->val) : "null") << " (Expected: 3)" << endl;

    // Example 2: p = 5, q = 4
    TreeNode* p2 = findNode(root1, 5);
    TreeNode* q2 = findNode(root1, 4);
    TreeNode* lca2 = sol.lowestCommonAncestor(p2, q2);
    cout << "Example 2: LCA of 5 and 4 is " << (lca2 ? to_string(lca2->val) : "null") << " (Expected: 5)" << endl;

    destroyTree(root1);

    // Example 3: root = [1,2], p = 1, q = 2
    vector<int> nodes3 = {1, 2};
    TreeNode* root3 = createTreeFromLevelOrder(nodes3);

    TreeNode* p3 = findNode(root3, 1);
    TreeNode* q3 = findNode(root3, 2);
    TreeNode* lca3 = sol.lowestCommonAncestor(p3, q3);
    cout << "Example 3: LCA of 1 and 2 is " << (lca3 ? to_string(lca3->val) : "null") << " (Expected: 1)" << endl;

    destroyTree(root3);

    return 0;
}
