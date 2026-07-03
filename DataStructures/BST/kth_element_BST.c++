/*

230. Kth Smallest Element in a BST
Medium
Topics
premium lock icon
Companies
Hint
Given the root of a binary search tree, and an integer k, return the kth smallest value (1-indexed) of all the values of the nodes in the tree.

 

Example 1:


Input: root = [3,1,4,null,2], k = 1
Output: 1
Example 2:


Input: root = [5,3,6,2,4,null,null,1], k = 3
Output: 3
 

Constraints:

The number of nodes in the tree is n.
1 <= k <= n <= 104
0 <= Node.val <= 104
 

Follow up: If the BST is modified often (i.e., we can do insert and delete operations) and you need to find the kth smallest frequently, how would you optimize?

*/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    // Returns true ONLY when the k-th element is successfully found
    bool inOrder(TreeNode* node, int& k, TreeNode*& result) {
        if (!node) return false; // Base case

        // 1. Traverse left subtree
        if (inOrder(node->left, k, result)) return true; // Early exit!

        // 2. Visit current node (Decrement and check)
        k--; 
        if (k == 0) {
            result = node; // Found the kth smallest!
            return true;   // Signal success up the call stack
        }

        // 3. Traverse right subtree
        return inOrder(node->right, k, result);
    }
public:
    int kthSmallest(TreeNode* root, int k) {
        TreeNode* result = nullptr;
        
        // k is passed by reference here, so it will be modified as we go
        if (inOrder(root, k, result) && result != nullptr) {
            return result->val;
        }
        
        return -1; 
    }
};

int main() {
    Solution sol;
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(1);
    root->right = new TreeNode(4);
    root->left->right = new TreeNode(2);

    // Test case: Find the 1st smallest element in the BST
    int k = 1;
    int result = sol.kthSmallest(root, k);
    std::cout << "The " << k << "th smallest element in the BST is: " << result << std::endl;

    // Test case: Find the 3rd smallest element in the BST
    k = 3;
    result = sol.kthSmallest(root, k);
    std::cout << "The " << k << "th smallest element in the BST is: " << result << std::endl;
    
    // Cleanup
    delete root;
    delete root->left;
    delete root->right;
    delete root->left->right;
    
    return 0;
}
