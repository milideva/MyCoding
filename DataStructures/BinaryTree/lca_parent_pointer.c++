
#include <vector>
#include <list>
#include <iostream>
#include <unordered_set>
#include <queue>

using namespace std;
 
/*
  LeetCode 1650: Lowest Common Ancestor of a Binary Tree III

  Problem Description:
  Given two nodes of a binary tree p and q, return their lowest common 
  ancestor (LCA). Each node has a reference to its parent node. The 
  definition for Node is as follows:

  class Node {
      public int val;
      public Node left;
      public Node right;
      public Node parent;
  }

  According to the definition of LCA on Wikipedia: "The lowest common 
  ancestor of two nodes p and q in a tree T is the lowest node that 
  has both p and q as descendants (where we allow a node to be a 
  descendant of itself)."

  Algorithm: Path Intersection (using Hash Set)
  1. Traverse from p upwards to the root, adding each node to a hash set.
  2. Traverse from q upwards to the root. The first node encountered that 
     is already in the hash set is the LCA.

  Complexity Analysis:
  - Time Complexity: O(H)
    Reason: We traverse the height of the tree twice—once for p and once 
    for q. In the worst case (skewed tree), this is O(N).
  - Space Complexity: O(H)
    Reason: We store the path from p to the root in an unordered_set.

  Alternative Approaches (Space Optimized):
  - Two Pointers (Linked List Intersection logic): 
    - Calculate depths of p and q. 
    - Advance the deeper node until it's at the same level as the other.
    - Advance both together until they meet.
    - Time: O(H), Space: O(1).
  - Difference in Heights:
    - Same logic as finding the intersection of two linked lists.
  
  Comparison:
  - The Hash Set approach is easier to implement but uses O(H) extra space.
  - The Depth-adjustment approach (O(1) space) is preferred if memory is
    a constraint.

  Brute Force comparison:
  - Without using the parent pointers or a hash set, you would have to 
    perform a full LC 236 style O(N) search from the root. 
  - The parent-pointer approach is better when the nodes are deep in the 
    tree but close to each other, as it avoids visiting unrelated branches.
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

        // Move to the next element for the next child
        i++;

        // Process Right Child
        if (i < arr.size() && arr[i] != MARKER) {
            TreeNode *right = new TreeNode(arr[i]);
            right->parent = current; // Instantly wire parent connection safely
           current->right = right;
            q.push(right);
        }

        // Move to the next element for the next node
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
