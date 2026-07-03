/*
  LeetCode 230: Kth Smallest Element in a BST

  Problem Description:
  Given the root of a binary search tree, and an integer k, return the 
  kth smallest value (1-indexed) of all the values of the nodes in 
  the tree.

  Algorithm: Iterative/Recursive In-order with Early Exit
  In-order traversal of a BST visits nodes in increasing order. We track the 
  number of nodes visited and return as soon as the count reaches k.

  Complexity Analysis:
  - Time Complexity: O(H + k)
    Reason: We must traverse down to the smallest element (O(H)) and then 
    visit k elements. In the best case (k=1), it is O(H). In the worst 
    case (k=N), it is O(N).
  - Space Complexity: O(H)
    Reason: Recursion stack or manual stack depth is proportional to 
    the tree height.

  Brute Force comparison:
  - Traverse the entire tree (O(N)), store values in an array, sort the 
    array (O(N log N)), and return the kth element.
  - Standard In-order Brute Force: Traverse entire tree (O(N)), store 
    in array, return result[k-1]. This is O(N) time and space.
  - Comparison: The early-exit approach is better because it avoids visiting 
    unnecessary nodes (N - k nodes) and uses O(H) instead of O(N) space.

  Follow-up Optimization:
  - If the tree is modified often, store the "size" of the left subtree in 
    each node. This allows finding the kth element in O(H) time by 
    comparing k with the left-subtree size at each step.
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
