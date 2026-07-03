#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/*
366. Find Leaves of Binary Tree

Given the root of a binary tree, collect a tree's nodes as if you were doing this:

Collect all the leaf nodes.
Remove all the leaf nodes.
Repeat until the tree is empty.

Input: root = [1,2,3,4,5]
Output: [[4,5,3],[2],[1]]

       1
      / \
     2   3
    / \
   4   5

Explanation:
[[3,5,4],[2],[1]] and [[3,4,5],[2],[1]] are also considered correct answers since per each level it does not matter the order \
on which elements are returned.
Example 2:

Input: root = [1]
Output: [[1]]


Constraints:

The number of nodes in the tree is in the range [1, 100].
-100 <= Node.val <= 100
*/

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr){}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// MARKER is a sentinel value used to represent a null/empty node in the level-order input vector.
const int MARKER = -999;

class Solution {
  vector <vector <int>> ans;
  int getHeight (TreeNode *root) {
    if (!root)
      return -1;
    int lh = getHeight(root->left);
    int rh = getHeight(root->right);
    int h = max(lh, rh) + 1;
    if ((int)ans.size() == h) {
      ans.push_back({});
    }
    ans[h].push_back(root->val);
    return h;
  }
public:
  vector<vector<int>> findLeaves(TreeNode* root) {
    getHeight(root);
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

void print_vec_vec (vector <vector <int>> &res, string str) {
  cout << endl << str << endl;
  for (auto v: res) {
    for (auto e : v) {
      cout << e << " ";
    }
    cout << endl;
  }
}

void destroyTree(TreeNode* node) {
    if (!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

int main () {

  // root = [1,2,3,4,5]
  vector<int> nodes = {1, 2, 3, 4, 5};
  TreeNode *root = createTreeFromLevelOrder(nodes);

  printTreeInorder(root);

  Solution sol;
  auto ans = sol.findLeaves(root);

  print_vec_vec(ans, "answer for findLeaves()");

  destroyTree(root);
  return 0;
}
