/*

652. Find Duplicate Subtrees

Given the root of a binary tree, return all duplicate subtrees.

For each kind of duplicate subtrees, you only need to return the root node of any one of them.

Two trees are duplicate if they have the same structure with the same node values.



Example 1:

Input: root = [1,2,3,4,null,2,4,null,null,4]
Output: [[2,4],[4]]

Example 2:

Input: root = [2,1,1]
Output: [[1]]

Example 3:

Input: root = [2,2,2,3,null,3,null]
Output: [[2,3],[3]]

*/

#include <unordered_map>
#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

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
  unordered_map < string, vector <TreeNode *>> str2node;

  string serialize (TreeNode *node) {
    if (node == nullptr)
      return "#";
    string subtree;

    subtree += "(" + serialize(node->left) + to_string(node->val) + serialize(node->right) + ")";
    str2node[subtree].push_back(node);
    return subtree;
  }

public:
  vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
    str2node.clear();
    vector<TreeNode*> res;
    serialize(root);

    for (auto const& [str, nodes] : str2node) {
      if (nodes.size() > 1) {
        res.push_back(nodes[0]);
      }
    }

    return res;
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

static void inorder (TreeNode *root)  {
  if (root) {
    inorder(root->left);
    printf("%d ", root->val);
    inorder(root->right);
  }
}

void print_inorder (TreeNode *n) {
    printf("print_inorder: ");
    inorder(n);
    printf("\n");
}

void destroyTree(TreeNode* node) {
    if (!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

int main () {
  Solution sol;

  // Example 1: root = [1,2,3,4,null,2,4,null,null,4]
  vector<int> nodes1 = {1, 2, 3, 4, MARKER, 2, 4, MARKER, MARKER, 4};
  TreeNode *root1 = createTreeFromLevelOrder(nodes1);

  vector <TreeNode *> res = sol.findDuplicateSubtrees(root1);
  cout << "Example 1 duplicates:" << endl;
  for (auto n : res) {
      print_inorder(n);
  }

  destroyTree(root1);
  return 0;
}
