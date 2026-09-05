/**
 * Problem: Find Duplicate Subtrees
 * Given the root of a binary tree, return all duplicate subtrees.
 * 
 * Strategy: DFS + Serialization + Hash Map
 * 1. For each node, serialize its subtree (LeftChild, RootVal, RightChild).
 * 2. Store the serialization string in a hash map and count its frequency.
 * 3. If frequency is exactly 2, add the root node of this subtree to the result.
 * 
 * -------------------------------------------------------------------------
 * WHY NULL MARKERS (like '#') ARE MANDATORY:
 * -------------------------------------------------------------------------
 * Standard traversals (Pre-order, In-order, or Post-order) without null markers 
 * are highly ambiguous. Without null markers to designate empty positions:
 * 
 * 1. Multiple distinct tree structures can produce the exact same sequence.
 *    For example, a tree with root 1 and left-child 2:
 *         1
 *        /
 *       2
 *    has Pre-order: [1, 2], In-order: [2, 1], Post-order: [2, 1].
 *    
 *    A tree with root 1 and right-child 2:
 *         1
 *          \
 *           2
 *    has Pre-order: [1, 2], In-order: [1, 2], Post-order: [2, 1].
 * 
 *    As seen, Pre-order alone ([1, 2]) or Post-order alone ([2, 1]) cannot distinguish 
 *    between a left-child and a right-child. 
 * 
 * 2. In-order alone is also ambiguous. For example, a tree with root 2 and left-child 1 
 *    vs. a tree with root 1 and right-child 2 both produce In-order: [1, 2].
 * 
 * By including null markers (e.g., "#" or "null") to explicitly mark empty nodes, 
 * we guarantee that a single traversal sequence (like Pre-order or Post-order) 
 * uniquely represents one and only one unique binary tree structure.
 * 
 * -------------------------------------------------------------------------
 * WHY TIME & SPACE COMPLEXITY IS O(N^2):
 * -------------------------------------------------------------------------
 * - Time Complexity:
 *   - Balanced Tree: O(N log N)
 *   - Skewed Tree (Worst-case): O(N^2)
 *   Reason: C++ string concatenation `s = "(" + left + val + right + ")"` is not 
 *   an O(1) operation. It takes time proportional to the length of the strings 
 *   being concatenated. In a completely skewed tree of size N, the lengths of 
 *   concatenated strings from leaf to root are 1, 2, 3, ..., N. Summing this 
 *   gives O(1 + 2 + ... + N) = O(N^2) operations.
 * - Space Complexity:
 *   - Balanced Tree: O(N log N)
 *   - Skewed Tree (Worst-case): O(N^2)
 *   Reason: We store the serialization string of every node in our hash map. 
 *   The sum of string lengths in the map matches the string concatenation costs, 
 *   requiring O(N^2) total memory in the worst case.
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    unordered_map<string, int> counts;
    vector<TreeNode*> result;

    /**
     * Serializes a subtree into a unique string.
     */
    string serialize(TreeNode* node) {
        if (!node) return "#";

        string s = "(" + serialize(node->left) + to_string(node->val) + serialize(node->right) + ")";
        
        counts[s]++;
        // This check prevents adding duplicate subtrees to the output list multiple times 
        // when a subtree pattern appears three or more times in the tree (only add when frequency is exactly 2).
        if (counts[s] == 2) {
            result.push_back(node);
        }
        return s;
    }

public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        counts.clear();
        result.clear();
        serialize(root);
        return result;
    }
};

/**
 * Utility to print in-order traversal.
 */
void printInOrder(TreeNode* root) {
    if (!root) return;
    printInOrder(root->left);
    cout << root->val << " ";
    printInOrder(root->right);
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->right->left = new TreeNode(2);
    root->right->right = new TreeNode(4);
    root->right->left->left = new TreeNode(4);

    Solution sol;
    vector<TreeNode*> duplicates = sol.findDuplicateSubtrees(root);

    cout << "Duplicate subtrees (In-order):" << endl;
    for (TreeNode* n : duplicates) {
        printInOrder(n);
        cout << endl;
    }

    return 0;
}
