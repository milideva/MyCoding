#include <vector>
#include <iostream>
#include <queue>
#include <string>

using namespace std;

/*
  LeetCode 199: Binary Tree Right Side View

  Problem Description:
  Given the root of a binary tree, imagine yourself standing on the 
  right side of it. Return the values of the nodes you can see 
  ordered from top to bottom.

  Example 1:
  Input: root = [1,2,3,null,5,null,4]
  Output: [1,3,4]

  Example 2:
  Input: root = [1,null,3]
  Output: [1,3]

  Example 3:
  Input: root = []
  Output: []

  Algorithm: Breadth-First Search (BFS) / Level Order Traversal
  1. Perform a standard level-order traversal using a queue.
  2. For each level, iterate through all nodes currently in the queue.
  3. The last node processed in each level is the one visible from the right side.
  4. Add that node's value to the result vector.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We visit every node in the tree exactly once.
  - Space Complexity: O(W)
    Reason: The queue stores nodes of the current level. W is the maximum 
    width of the tree (up to N/2).

  Alternative Approaches:
  - DFS (Root -> Right -> Left):
    - Logic: Use recursion and track the current depth. If the current 
      depth is equal to the size of the result vector, this is the 
      first time we've reached this depth from the right, so add the 
      node value.
    - Time: O(N), Space: O(H).
    - Comparison: DFS is slightly more space-efficient on average (H < W 
      for many trees), but BFS is more intuitive for "view" problems.

  Brute Force comparison:
  - Find all nodes at each level `i` using separate DFS calls, and pick 
    the rightmost one.
  - Time: O(N * H), which is O(N^2) in the worst case.
  - Standard BFS/DFS reduces this to optimal O(N).
*/

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector <int> rsview;
        if (!root) return rsview;
        queue <TreeNode *> q;
        q.push(root);

        while (!q.empty()) {
            int sz = q.size();
            vector <TreeNode *> level;
            TreeNode *curr;
            for (int i = 0; i < sz; i++) {
                curr = q.front(); q.pop();

                if (curr->left) {
                    q.push(curr->left);
                }
                if (curr->right) {
                    q.push(curr->right);
                }
            }
            rsview.push_back(curr->val);
        }
        return rsview;
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

//=========================================================================
// Test Suite
//=========================================================================

void test(const string& label, const vector<int>& treeArr, const vector<int>& expected) {
    cout << "Testing: " << label << endl;
    TreeNode* root = createTreeFromLevelOrder(treeArr);
    Solution sol;
    vector<int> result = sol.rightSideView(root);

    bool pass = (result == expected);
    cout << "  [" << (pass ? "PASS" : "FAIL") << "] Result: [";
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << (i == result.size() - 1 ? "" : ", ");
    }
    cout << "]" << endl;

    if (!pass) {
        cout << "    Expected: [";
        for (int i = 0; i < expected.size(); ++i) {
            cout << expected[i] << (i == expected.size() - 1 ? "" : ", ");
        }
        cout << "]" << endl;
    }
    destroyTree(root);
}

int main() {
    // Example 1: [1,2,3,null,5,null,4]
    test("Standard Balanced Tree", {1, 2, 3, MARKER, 5, MARKER, 4}, {1, 3, 4});

    // Example 2: [1,null,3]
    test("Right Skewed", {1, MARKER, 3}, {1, 3});

    // Example 3: []
    test("Empty Tree", {}, {});

    // Example 4: [1, 2]
    test("Left child only", {1, 2}, {1, 2});

    // Example 5: [1, 2, 3, 4]
    test("Deep left branch", {1, 2, 3, 4, MARKER, MARKER, MARKER}, {1, 3, 4});

    return 0;
}
