#include <vector>
#include <iostream>
#include <queue>

using namespace std;
 
/*
  LeetCode 236 (Robust Version): Lowest Common Ancestor of a Binary Tree

  Problem Description:
  Given a binary tree, find the lowest common ancestor (LCA) of two 
  given nodes in the tree. 

  Note: In this robust implementation, we handle the case where either 
  p or q (or both) may NOT exist in the tree. If either node is missing, 
  we return null.

  According to the definition of LCA on Wikipedia: "The lowest common 
  ancestor is defined between two nodes p and q as the lowest node 
  in T that has both p and q as descendants (where we allow a node 
  to be a descendant of itself)."

  Algorithm: Recursive DFS with Existence Flags
  1. We perform an exhaustive post-order DFS traversal.
  2. We maintain two flags, `p_found` and `q_found`.
  3. We don't return immediately when we find a target node; we must 
     ensure the other node is also searched for in its subtrees or 
     elsewhere in the tree.
  4. Only if both flags are true at the end do we return the calculated LCA.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We must visit every node to ensure we don't miss any target 
    nodes that might be missing from the tree.
  - Space Complexity: O(H)
    Reason: Recursion stack depth is proportional to tree height (H).

  Comparison:
  - Standard LC 236 (Optimized): If p and q are guaranteed to exist, 
    we can return immediately when we find either. This is faster 
    on average (O(N) worst case but often less).
  - Robust LC 1644: This implementation matches LC 1644, which 
    requires confirming the existence of both nodes. It is more 
    robust for general engineering use.
*/

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
  // Helper function that traverses the tree and tracks if p or q are found.
  TreeNode* LCAUtil(TreeNode* root, TreeNode* p, TreeNode* q, bool& p_found, bool& q_found) {
    if (!root) return nullptr;

    // Note if we found a target node.
    // We don't return immediately to ensure we explore subtrees and find the other node.
    TreeNode* current_match = nullptr;
    if (root == p) { p_found = true; current_match = root; }
    if (root == q) { q_found = true; current_match = root; }

    TreeNode* left = LCAUtil(root->left, p, q, p_found, q_found);
    TreeNode* right = LCAUtil(root->right, p, q, p_found, q_found);

    // If the current node was p or q, it is the potential LCA (if the other is below it).
    if (current_match) return current_match;

    // If one node was found in left and the other in right, current node is LCA.
    if (left && right) return root;

    // Otherwise return whichever branch found a target.
    return left ? left : right;
  }

public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || !p || !q) return nullptr;

    bool p_found = false, q_found = false;
    TreeNode* lca = LCAUtil(root, p, q, p_found, q_found);
    
    // Only return the result if BOTH nodes were successfully found in the tree.
    return (p_found && q_found) ? lca : nullptr;
  }
};

//=========================================================================
// Tree Construction & Memory Management (Standardized)
//=========================================================================

const int MARKER = -1;

TreeNode* createTreeFromLevelOrder(const vector<int>& arr) {
  if (arr.empty() || arr[0] == MARKER) return nullptr;

  TreeNode* root = new TreeNode(arr[0]);
  queue<TreeNode*> q;
  q.push(root);

  int i = 1;
  while (!q.empty() && i < arr.size()) {
    TreeNode* curr = q.front();
    q.pop();

    // Process Left Child
    if (i < arr.size() && arr[i] != MARKER) {
      curr->left = new TreeNode(arr[i]);
      q.push(curr->left);
    }
    
    // Move to next element for the next child
    i++;

    // Process Right Child
    if (i < arr.size() && arr[i] != MARKER) {
      curr->right = new TreeNode(arr[i]);
      q.push(curr->right);
    }
    
    // Move to next element for the next node's children
    i++;
  }
  return root;
}

void destroyTree(TreeNode* root) {
  if (!root) return;
  destroyTree(root->left);
  destroyTree(root->right);
  delete root;
}

// Helper to find a node with a specific value (needed for test setup).
TreeNode* findNode(TreeNode* root, int val) {
  if (!root) return nullptr;
  if (root->val == val) return root;
  TreeNode* l = findNode(root->left, val);
  if (l) return l;
  return findNode(root->right, val);
}

//=========================================================================
// Test Suite
//=========================================================================

void test(const string& label, const vector<int>& treeArr, int pVal, int qVal, int expectedVal) {
  cout << "Testing: " << label << endl;
  TreeNode* root = createTreeFromLevelOrder(treeArr);
  
  // Note: We search for pVal/qVal in the tree. 
  // If not found, we create a dummy node to simulate a node NOT in the tree.
  TreeNode* p = findNode(root, pVal);
  if (!p && pVal != MARKER) p = new TreeNode(pVal); 
  
  TreeNode* q = findNode(root, qVal);
  if (!q && qVal != MARKER) q = new TreeNode(qVal);

  Solution sol;
  TreeNode* result = sol.lowestCommonAncestor(root, p, q);

  if ((result == nullptr && expectedVal == MARKER) || (result && result->val == expectedVal)) {
    cout << "  [PASS] LCA(" << pVal << ", " << qVal << ") = " 
         << (result ? to_string(result->val) : "NULL") << endl;
  } else {
    cout << "  [FAIL] LCA(" << pVal << ", " << qVal << ") = " 
         << (result ? to_string(result->val) : "NULL") 
         << " (Expected: " << (expectedVal == MARKER ? "NULL" : to_string(expectedVal)) << ")" << endl;
  }

  // Cleanup: If p or q were dummy nodes, delete them.
  if (p && !findNode(root, pVal)) delete p;
  if (q && !findNode(root, qVal)) delete q;
  destroyTree(root);
}

int main() {
  // Tree: [3, 5, 1, 6, 2, 0, 8, -1, -1, 7, 4]
  vector<int> tree = {3, 5, 1, 6, 2, 0, 8, MARKER, MARKER, 7, 4};

  test("Standard Case (different subtrees)", tree, 5, 1, 3);
  test("Ancestor Case (q is below p)", tree, 5, 4, 5);
  test("Root Case", tree, 3, 8, 3);
  
  // Cases where nodes do not exist
  test("Missing Q", tree, 5, 10, MARKER);
  test("Missing P", tree, 20, 1, MARKER);
  test("Both Missing", tree, 100, 200, MARKER);
  
  return 0;
}
