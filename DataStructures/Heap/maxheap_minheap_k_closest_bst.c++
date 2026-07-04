#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

/*
  LeetCode 272: Closest Binary Search Tree Value II

  Problem Description:
  Given the root of a binary search tree, a target value, and an 
  integer k, return the k values in the BST that are closest to 
  the target. You may return the answer in any order.

  You are guaranteed to have only one unique set of k values in the 
  BST that are closest to the target.

  Algorithm: In-order Traversal + Max-Heap of size K
  1. Use a Max-Heap to store the current closest K values. 
  2. The heap stores pairs of `(absolute_difference, node_value)`.
  3. Perform an in-order traversal of the BST.
  4. For each node:
     - Calculate `diff = abs(node->val - target)`.
     - Push `{diff, node->val}` to the max-heap.
     - If heap size exceeds K, pop the largest difference.
  5. After traversal, the heap contains the K closest values.

  Complexity Analysis:
  - Time Complexity: O(N log K)
    Reason: We visit all N nodes once, and each heap operation takes O(log K).
  - Space Complexity: O(H + K)
    Reason: O(H) for the recursion stack and O(K) for the heap.

  Alternative Approaches (Follow-up: O(log N + K)):
  - Optimized Search: 
    1. Find the node closest to the target in O(log N).
    2. Use two stacks (predecessor and successor) to find K neighbors.
    - Comparison: The Heap approach is O(N log K), which is simpler but 
      slower than the O(log N + K) approach for large trees.
*/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    priority_queue<pair<double, int>> pq; // <diff, value>

    void inOrder(TreeNode* root, double target, int k) {
        if (!root) return;
        
        inOrder(root->left, target, k);
        
        double diff = abs(root->val - target);
        pq.push({diff, root->val});
        if (pq.size() > k) {
            pq.pop();
        }
        
        inOrder(root->right, target, k);
    }

public:
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        while (!pq.empty()) pq.pop(); // Clear pq for multiple calls
        
        inOrder(root, target, k);
        
        vector<int> result;
        while (!pq.empty()) {
            result.push_back(pq.top().second);
            pq.pop();
        }
        return result;
    }
};

//=========================================================================
// BST Construction & Test Code
//=========================================================================

TreeNode* createBST(const vector<int>& arr, int start, int end) {
    if (start > end) return nullptr;
    int mid = start + (end - start) / 2;
    TreeNode* root = new TreeNode(arr[mid]);
    root->left = createBST(arr, start, mid - 1);
    root->right = createBST(arr, mid + 1, end);
    return root;
}

void destroyTree(TreeNode* root) {
    if (!root) return;
    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
}

void test(const string& label, const vector<int>& bstArr, double target, int k) {
    cout << "Testing: " << label << " (Target: " << target << ", K: " << k << ")" << endl;
    TreeNode* root = createBST(bstArr, 0, bstArr.size() - 1);
    Solution sol;
    vector<int> result = sol.closestKValues(root, target, k);
    sort(result.begin(), result.end());

    cout << "  Result: [ ";
    for (int v : result) cout << v << " ";
    cout << "]" << endl;
    destroyTree(root);
}

int main() {
    vector<int> tree1 = {1, 2, 3, 4, 5};
    test("Example 1", tree1, 3.714286, 2);

    vector<int> tree2 = {-10, 5, 10, 56, 60, 100, 233, 300, 500, 600, 700, 800, 900, 1000, 2333};
    test("Large Tree Test 1", tree2, 350.0, 4);
    test("Large Tree Test 2", tree2, 850.0, 5);

    return 0;
}
