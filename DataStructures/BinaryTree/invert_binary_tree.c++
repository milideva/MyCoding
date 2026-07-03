#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

/*
  LeetCode 226: Invert Binary Tree

  Problem: Given the root of a binary tree, invert the tree (mirror it) 
  and return its root.

  Algorithm: Recursive DFS (Post-order)
  1. Recursively invert the left subtree.
  2. Recursively invert the right subtree.
  3. Swap the left and right pointers of the current node.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We visit every node in the tree exactly once to perform the swap.
  - Space Complexity: O(H)
    Reason: Recursion stack space is proportional to the tree height (H).

  Alternative Approaches:
  - Iterative BFS: Use a queue. For each node dequeued, swap its children 
    and enqueue any non-null children.
    - Time: O(N)
    - Space: O(W) where W is the max width.
  - Iterative DFS: Use a stack to simulate the recursion.
    - Time: O(N)
    - Space: O(H)

  Comparison:
  - The recursive approach is the most idiomatic and readable.
  - BFS is useful if the tree is extremely deep (potential stack overflow),
    as the heap-allocated queue can typically handle more nodes than the
    thread's stack.

  Brute Force comparison:
  - Similar to "Double Tree", a brute force approach would be to copy the 
    entire tree into a new structure while swapping children during 
    construction. 
  - Time: O(N), Space: O(N) for the new tree.
  - The in-place swap is superior as it doesn't require extra memory for 
    new node allocations.
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
