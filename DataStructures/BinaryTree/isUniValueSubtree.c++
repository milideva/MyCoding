#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

/*
 Given the root of a binary tree, return the number of uni-value
 subtrees. A uni-value subtree means all nodes of the subtree have the
 same value.
*/

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// MARKER is a sentinel value used to represent a null/empty node in the level-order input vector.
const int MARKER = -1;

class Solution {
  int count = 0;
  bool isUnival (TreeNode* root) {
    if (!root) return true;

    bool left = isUnival(root->left);
    bool right = isUnival(root->right);

    if (!left || !right) return false;

    if (root->left && root->val != root->left->val) return false;
    if (root->right && root->val != root->right->val) return false;

    count++;
    return true;
  }

public:
  int countUnivalSubtrees(TreeNode* root) {
    count = 0;
    if (!root) return 0;
    isUnival(root);
    return count;
  }
};

///////////////////////////////// Test code ////////////////////////////////////////

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

void destroyTree(TreeNode* node) {
    if (!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

int main () {
  Solution sol;

  // Example 1: root = [5,1,5,5,5,null,5]
  vector<int> nodes1 = {5, 1, 5, 5, 5, MARKER, 5};
  TreeNode *root1 = createTreeFromLevelOrder(nodes1);

  int countUni = sol.countUnivalSubtrees(root1);
  cout << "Example 1 countUniValueSubtree: " << countUni << " (Expected: 4)" << endl;

  // Example 2: root = [5,5,5,5,5,null,5]
  vector<int> nodes2 = {5, 5, 5, 5, 5, MARKER, 5};
  TreeNode *root2 = createTreeFromLevelOrder(nodes2);
  countUni = sol.countUnivalSubtrees(root2);
  cout << "Example 2 countUniValueSubtree: " << countUni << " (Expected: 6)" << endl;

  destroyTree(root1);
  destroyTree(root2);

  return 0;
}
