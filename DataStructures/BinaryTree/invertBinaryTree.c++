#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

/*
226. Invert Binary Tree
Given the root of a binary tree, invert the tree, and return its root.

Input: root = [4,2,7,1,3,6,9]
Output: [4,7,2,9,6,3,1]

Input: root = [2,1,3]
Output: [2,3,1]

Example

Before invert :
       6
     /   \
   13     5
  / \    / \
 7   8  1   3

After invert :
       6
     /   \
    5     13
   / \   /  \
  3   1 8    7

*/
struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// MARKER is a sentinel value used to represent a null/empty node in the level-order input vector.
const int MARKER = -1;

class Solution
{

public:
  TreeNode *invertTree(TreeNode *root)
  {
    if (!root)
      return nullptr;
    TreeNode *left = invertTree(root->left);
    TreeNode *right = invertTree(root->right);
    root->left = right;
    root->right = left;
    return root;
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

static void inorder(TreeNode *root)
{
  if (root)
  {
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
  }
}

void printTreeInorder(TreeNode *n)
{
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

int main()
{
  // root = [4,2,7,1,3,6,9]
  vector<int> nodes = {4, 2, 7, 1, 3, 6, 9};
  TreeNode *root = createTreeFromLevelOrder(nodes);

  cout << "Before invert:" << endl;
  printTreeInorder(root);

  Solution sol;
  root = sol.invertTree(root);

  cout << "After invert:" << endl;
  printTreeInorder(root);

  destroyTree(root);
  return 0;
}
