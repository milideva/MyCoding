#include <vector>
#include <iostream>

using namespace std;

/*
  LeetCode 129: Sum Root to Leaf Numbers

  Problem Description:
  You are given the root of a binary tree containing digits from 0 
  to 9 only. Each root-to-leaf path in the tree represents a number.
  For example, the root-to-leaf path 1 -> 2 -> 3 represents the 
  number 123.
  Return the total sum of all root-to-leaf numbers. Test cases are 
  generated so that the answer will fit in a 32-bit integer.

  Algorithm: Pre-order DFS
*/

/*
    Lets say the tree is:
                4
              /   \
            9      0
                     \
                      1
    DFS(4, 0) runs DFS(9, 4) + DFS(0, 4).
    DFS(9, 4) adds 49 to total.
    DFS(0, 4) adds runs DFS(NULL, 40) + DFS(1, 40).
    DFS(NULL, 40) doesn't do anything.
    DFS(1, 40) adds 401 to total.
    In the total == 450.

    If current == NULL return.
    If current->left == NULL && current->right == NULL there are no children.
        We will then  total += current->val and total += num * 10
    Else, recurse DFS(current->left, num*10 + current->val) and DFS(current->right, num*10 + current->val).
*/

/*
  LeetCode 129: Sum Root to Leaf Numbers

  Problem: Each root-to-leaf path represents a number (e.g., 1->2->3 = 123). 
  Return the sum of all such numbers.

  Algorithm: Pre-order DFS
  We traverse from root to leaf, maintaining the current path's numerical 
  value. For each node, `currentPathValue = parentValue * 10 + node->val`. 
  When a leaf is reached, we add the `currentPathValue` to the global sum.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We visit every node in the binary tree exactly once.
  - Space Complexity: O(H)
    Reason: Recursion stack depth is proportional to the tree height (H).

  Alternative Approaches:
  - Iterative DFS: Use a stack to store pairs of (TreeNode*, currentPathValue).
  - BFS (Level Order): Use a queue to store pairs. This is useful if the 
    tree is very deep.
  
  Comparison:
  - The recursive pre-order approach is the most efficient and readable
    for path-based problems like this.

  Brute Force Approach:
  - 1. Find all paths from root to leaves using a traversal.
  - 2. For each path (stored as a string or list), convert it to a number.
  - 3. Sum all those numbers.
  - Time: O(N * H) due to path copying and conversions.
  - Space: O(N * H) to store all paths.
  - The current approach is O(N) time and O(H) space, which is far better.
*/

/**
 * Definition for a binary tree node.
 */
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
    int sum = 0;
    void preOrder(TreeNode *root, int num)
    {
        if (!root)
        {
            return;
        }
        if (!root->left && !root->right)
        {
            sum += root->val;
            sum += num * 10;
        }

        preOrder(root->left, num * 10 + root->val);
        preOrder(root->right, num * 10 + root->val);
    }

public:
    int sumNumbers(TreeNode *root)
    {
        if (!root)
            return 0;
        preOrder(root, 0);
        return sum;
    }
};

void test(TreeNode *root)
{
    Solution sol;
    auto sum = sol.sumNumbers(root);
    cout << "sum: " << sum << endl;
}

int main(void)
{
    TreeNode *n1 = new TreeNode(1);
    TreeNode *n0 = new TreeNode(0, nullptr, n1);
    TreeNode *n9 = new TreeNode(9);
    TreeNode *root = new TreeNode(4, n9, n0);

    test(root);
    return 0;
}