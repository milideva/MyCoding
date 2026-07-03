#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/*
1022. Sum of Root To Leaf Binary Numbers

You are given the root of a binary tree where each node has a value 0
or 1. Each root-to-leaf path represents a binary number starting with
the most significant bit.

For example, if the path is 0 -> 1 -> 1 -> 0 -> 1, then this could
represent 01101 in binary, which is 13.  For all leaves in the tree,
consider the numbers represented by the path from the root to that
leaf. Return the sum of these numbers.

The test cases are generated so that the answer fits in a 32-bits
integer.

*/

/*
  LeetCode 1022: Sum of Root To Leaf Binary Numbers

  Algorithm: Pre-order DFS
  Similar to LeetCode 129, but the path represents a binary number. 
  Calculation: `currentValue = (parentValue << 1) | node->val`.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: Every node is visited once.
  - Space Complexity: O(H)
    Reason: Recursion stack depth.

  Comparison:
  - This is essentially a specialized version of the "Sum Root to Leaf Numbers"
    problem using base 2 instead of base 10.

  Brute Force comparison:
  - Similar to LC 129, a brute force would involve explicit path storage 
    and conversion. 
  - By using the bit-shifting logic `(val << 1) | node->val`, we avoid 
    extra space for path arrays and achieve O(N) efficiency.
*/

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr){}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// MARKER is a sentinel value used to represent a null/empty node in the level-order input vector.
const int MARKER = -1;

class Solution {

public:

  void dfs (TreeNode *node, int val, int& ans) {
    if (!node) return;
    val = (val * 2) + node->val;
    if (!node->left && !node->right) {
      ans += val;
      return;
    }
    dfs(node->left, val, ans);
    dfs(node->right, val, ans);
  }
  int sumRootToLeaf (TreeNode* root) {
    int ans = 0;
    dfs(root, 0, ans);
    return ans;
  }
};

// Builds a tree from a standard LeetCode-style level-order vector.
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
            current->left = left;
            q.push(left);
        }

        // Move to the next element for the next child
        i++;

        // Process Right Child
        if (i < arr.size() && arr[i] != MARKER) {
            TreeNode *right = new TreeNode(arr[i]);
            current->right = right;
            q.push(right);
        }

        // Move to the next element for the next node
        i++;
    }

    return root;
}

static void inorder (TreeNode *root)  {
    if (root) {
        inorder(root->left);
        cout << root->val << " ";
        inorder(root->right);
    }
}


void printTreeInorder (TreeNode *n) {
  cout << "Inorder: ";
  inorder(n);
  cout << endl;
}

void destroyTree(TreeNode* node) {
    if (!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

int main () {
  // Example 1: root = [1,0,1,0,1,0,1]
  // Paths: 100(4), 101(5), 110(6), 111(7). Sum = 22.
  vector<int> nodes1 = {1, 0, 1, 0, 1, 0, 1};
  TreeNode *root1 = createTreeFromLevelOrder(nodes1);

  printTreeInorder(root1);

  Solution sol;
  auto sum = sol.sumRootToLeaf(root1);
  cout << "sum: " << sum << " (Expected: 22)" << endl;

  destroyTree(root1);
  return 0;
}
