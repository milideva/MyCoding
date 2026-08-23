/**
 * =========================================================================
 * PATH SUM I, II & III: DFS APPLICATIONS ON BINARY TREES
 * =========================================================================
 * 
 * This file contains optimal implementations and test cases for:
 * 1. LeetCode 112: Path Sum (Boolean existence check)
 * 2. LeetCode 113: Path Sum II (Retrieving all matching paths)
 * 3. LeetCode 437: Path Sum III (Counting downward paths)
 * 
 * These problems use Depth-First Search (DFS) to traverse paths and compare 
 * path sums against a target.
 * 
 * -------------------------------------------------------------------------
 * 1. PATH SUM I (LeetCode 112)
 * -------------------------------------------------------------------------
 * - **Problem Description:**
 *   Given the root of a binary tree and an integer targetSum, return true if 
 *   the tree has a root-to-leaf path such that adding up all the values along 
 *   the path equals targetSum.
 * 
 * - **Strategy:**
 *   - Base Case: If the node is null, return false (no path).
 *   - If the current node is a leaf (no left and right children) and its value 
 *     equals the remaining targetSum, we found a valid path -> return true.
 *   - Otherwise, recursively check the left and right subtrees with the 
 *     reduced targetSum: `targetSum - root->val`.
 * 
 * - **Complexity:**
 *   - Time Complexity: O(N) since we may need to visit all nodes in the worst case.
 *   - Space Complexity: O(H) where H is the height of the tree (recursion stack).
 * 
 * -------------------------------------------------------------------------
 * 2. PATH SUM II (LeetCode 113)
 * -------------------------------------------------------------------------
 * - **Problem Description:**
 *   Given the root of a binary tree and an integer targetSum, return all 
 *   root-to-leaf paths where the sum of the node values in the path equals targetSum.
 * 
 * - **Strategy (DFS with Backtracking):**
 *   - Traverse the tree from root to leaf using DFS, keeping track of the 
 *     `currentPath` vector and accumulating the sum.
 *   - At each node, push its value to `currentPath`.
 *   - If we reach a leaf node and the path sum matches targetSum, save a copy 
 *     of `currentPath` to our global list of results.
 *   - Backtrack: Pop the current node from `currentPath` before returning 
 *     to the parent node, allowing other branches to use the vector.
 * 
 * - **Complexity:**
 *   - Time Complexity: O(N * H) where N is the number of nodes and H is the height.
 *     In the worst case (skewed tree), copying paths can take up to O(N) for 
 *     each matching path.
 *   - Space Complexity: O(H) recursion stack space and current path storage.
 * 
 * -------------------------------------------------------------------------
 * 3. PATH SUM III (LeetCode 437)
 * -------------------------------------------------------------------------
 * - **Problem Description:**
 *   Given the root of a binary tree and an integer targetSum, return the 
 *   number of paths where the sum of the values along the path equals targetSum.
 *   The path does not need to start or end at the root or a leaf, but it must 
 *   go downwards (i.e., traveling only from parent nodes to child nodes).
 * 
 * - **Strategy (Double DFS):**
 *   - For every node, run a helper DFS `countPathsFromNode` to count all downward 
 *     paths starting from that node that sum to `targetSum`.
 *   - Recurse on the left and right children with the same `targetSum` to 
 *     consider them as starting points for other downward paths.
 * 
 * - **Complexity:**
 *   - Time Complexity: O(N log N) for balanced trees, O(N^2) in the worst case (skewed tree).
 *   - Space Complexity: O(H) recursion stack space.
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    void findPaths(TreeNode* node, int targetSum, vector<int>& currentPath, vector<vector<int>>& result) {
        if (!node) return;

        // Add current node's value to the path
        currentPath.push_back(node->val);

        // If it's a leaf node and the value matches the remaining target sum, save the path
        if (!node->left && !node->right && node->val == targetSum) {
            result.push_back(currentPath);
        } else {
            // Otherwise, recurse on left and right children with updated target sum
            findPaths(node->left, targetSum - node->val, currentPath, result);
            findPaths(node->right, targetSum - node->val, currentPath, result);
        }

        // Backtrack: remove the current node's value before returning
        currentPath.pop_back();
    }

public:
    // Path Sum I (Boolean Existence)
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root) return false;

        // Check if we reached a leaf node
        if (!root->left && !root->right) {
            return root->val == targetSum;
        }

        // Recurse on subtrees with reduced targetSum
        return hasPathSum(root->left, targetSum - root->val) || 
               hasPathSum(root->right, targetSum - root->val);
    }

    // Path Sum II (All Paths Retrieval)
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> result;
        vector<int> currentPath;
        findPaths(root, targetSum, currentPath, result);
        return result;
    }

private:
    unordered_map <TreeNode *, int> top2NodeSum;
    int cnt = 0;

    void countPathsFromNode (TreeNode* node, long long currSum, int targetSum)  {
        if (!node) return;

        currSum += node->val;
        //top2NodeSum[node] = currSum;

        if (currSum == targetSum) {
            cnt++;
        }
        countPathsFromNode(node->left, currSum, targetSum);
        countPathsFromNode(node->right, currSum, targetSum);
    }

    void traverseAndCount(TreeNode* node, int targetSum) {
        if (!node) return;
        countPathsFromNode(node, 0, targetSum);
        traverseAndCount(node->left, targetSum);
        traverseAndCount(node->right, targetSum);
    }

public:
    // Path Sum III (Downward paths count, does not need to start at root/end at leaf)
    int pathSumIII(TreeNode* root, int targetSum) {
        cnt = 0; // Reset count for each test case run to be reentrant
        traverseAndCount(root, targetSum);
        return cnt;
    }
};

// =========================================================================
// TESTING HARNESS
// =========================================================================

void printPath(const vector<int>& path) {
    cout << "[ ";
    for (int val : path) {
        cout << val << " ";
    }
    cout << "]";
}

void printPaths(const vector<vector<int>>& paths) {
    cout << "{ ";
    for (const auto& path : paths) {
        printPath(path);
        cout << " ";
    }
    cout << "}";
}

void runTest(const string& label, TreeNode* root, int targetSum, bool expectedHasPath, const vector<vector<int>>& expectedPaths, int expectedPathsIII) {
    cout << "Testing: " << label << " (Target Sum = " << targetSum << ")" << endl;
    Solution sol;
    
    // Test Path Sum I
    bool hasPathResult = sol.hasPathSum(root, targetSum);
    cout << "  Path Sum I (Existence): " << (hasPathResult ? "True" : "False")
         << " (Expected: " << (expectedHasPath ? "True" : "False") << ") ";
    if (hasPathResult == expectedHasPath) {
        cout << "[PASS]" << endl;
    } else {
        cout << "[FAIL]" << endl;
    }

    // Test Path Sum II
    vector<vector<int>> pathsResult = sol.pathSum(root, targetSum);
    cout << "  Path Sum II (Paths):     "; printPaths(pathsResult);
    cout << " (Expected: "; printPaths(expectedPaths); cout << ") ";
    if (pathsResult == expectedPaths) {
        cout << "[PASS]" << endl;
    } else {
        cout << "[FAIL]" << endl;
    }

    // Test Path Sum III
    int pathsIIIResult = sol.pathSumIII(root, targetSum);
    cout << "  Path Sum III (Count):   " << pathsIIIResult
         << " (Expected: " << expectedPathsIII << ") ";
    if (pathsIIIResult == expectedPathsIII) {
        cout << "[PASS]" << endl;
    } else {
        cout << "[FAIL]" << endl;
    }
    cout << endl;
}

int main() {
    cout << "=========================================================" << endl;
    cout << "           RUNNING PATH SUM I, II & III TESTS            " << endl;
    cout << "=========================================================" << endl;

    /*
     * Build the following Binary Tree:
     *               5
     *              / \
     *             4   8
     *            /   / \
     *           11  13  4
     *          /  \    / \
     *         7    2  5   1
     */
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(4);
    root->right = new TreeNode(8);
    
    root->left->left = new TreeNode(11);
    root->left->left->left = new TreeNode(7);
    root->left->left->right = new TreeNode(2);

    root->right->left = new TreeNode(13);
    root->right->right = new TreeNode(4);
    root->right->right->left = new TreeNode(5);
    root->right->right->right = new TreeNode(1);

    // Test 1: Target sum 22 should exist (paths [5, 4, 11, 2] and [5, 8, 4, 5])
    runTest("Example Tree - Target 22", root, 22, true, {{5, 4, 11, 2}, {5, 8, 4, 5}}, 3);

    // Test 2: Target sum 26 should exist (path [5, 8, 13])
    runTest("Example Tree - Target 26", root, 26, true, {{5, 8, 13}}, 1);

    // Test 3: Target sum 18 should exist (path [5, 8, 5] is not leaf, [5, 8, 4, 1] is leaf sum 18)
    runTest("Example Tree - Target 18", root, 18, true, {{5, 8, 4, 1}}, 2);

    // Test 4: Target sum 5 should not exist (5 is not a leaf node)
    runTest("Example Tree - Target 5", root, 5, false, {}, 3);

    // Test 5: Empty Tree
    runTest("Empty Tree - Target 0", nullptr, 0, false, {}, 0);

    // Clean up memory
    // Since we're doing local verification we'll do manual deletion
    delete root->left->left->left;
    delete root->left->left->right;
    delete root->left->left;
    delete root->left;
    delete root->right->left;
    delete root->right->right->left;
    delete root->right->right->right;
    delete root->right->right;
    delete root->right;
    delete root;

    cout << "=========================================================" << endl;
    return 0;
}
