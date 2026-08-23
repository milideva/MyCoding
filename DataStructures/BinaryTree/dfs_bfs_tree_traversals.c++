/**
 * =========================================================================
 * BINARY TREE TRAVERSALS: WHEN TO USE & PRACTICAL APPLICATIONS
 * =========================================================================
 * 
 * This file contains implementations of fundamental binary tree traversals
 * (Pre-order, In-order, Post-order, and Level-order) alongside real-world,
 * practical applications demonstrating when and why each is used.
 * 
 * -------------------------------------------------------------------------
 * 1. PRE-ORDER TRAVERSAL (Root -> Left -> Right)
 * -------------------------------------------------------------------------
 * - **When is it used?**
 *   When you need to process the parent node BEFORE processing its children.
 *   Useful when the state of child nodes depends on the parent node's state
 *   or when you want to traverse/generate structurally identical copies.
 * 
 * - **Practical Applications:**
 *   1. **Tree Copying/Cloning**: You must allocate the parent node before you 
 *      can assign its left and right children.
 *   2. **Serialization (DFS)**: Pre-order is standard for serialization 
 *      because deserializing from left-to-right matches pre-order structure.
 *   3. **Directory Listing**: Printing folders before their contents.
 * 
 * -------------------------------------------------------------------------
 * 2. IN-ORDER TRAVERSAL (Left -> Root -> Right)
 * -------------------------------------------------------------------------
 * - **When is it used?**
 *   When you want to process nodes in a relative sorted or sequential order,
 *   which is particularly useful in Binary Search Trees (BSTs).
 * 
 * - **Practical Applications:**
 *   1. **Sorted Node Retrieval in BST**: Visiting nodes in-order on a BST 
 *      yields values in ascending order.
 *   2. **BST Validation**: Proving whether a binary tree is a valid BST 
 *      by verifying if the in-order traversal yields a strictly increasing sequence.
 * 
 * -------------------------------------------------------------------------
 * 3. POST-ORDER TRAVERSAL (Left -> Right -> Root)
 * -------------------------------------------------------------------------
 * - **When is it used?**
 *   When you need to make decisions or compute results for child subtrees
 *   BEFORE you can compute the result for the parent node (bottom-up aggregation).
 * 
 * - **Practical Applications:**
 *   1. **Safe Memory Deallocation (Deletion)**: You must delete the left 
 *      and right children before deleting the parent node to prevent memory leaks.
 *   2. **Tree Metrics (Height, Diameter, Size)**: The height of a node is 
 *      `1 + max(left_height, right_height)`. Thus, children heights must be known first.
 *   3. **Expression Tree Evaluation**: Evaluating operators (parent) requires
 *      evaluating left and right operands (children) first.
 * 
 * -------------------------------------------------------------------------
 * 4. LEVEL-ORDER TRAVERSAL / BFS (Top -> Bottom, Level by Level)
 * -------------------------------------------------------------------------
 * - **When is it used?**
 *   When you need to explore nodes level-by-level, processing nodes closest
 *   to the root first. Excellent for shortest path searches.
 * 
 * - **Practical Applications:**
 *   1. **Level Statistics (Averages, Maxima)**: Computing stats per level.
 *   2. **Right Side View / Profile**: Printing the last node of each level.
 *   3. **Shortest Distance in Unweighted Trees**: BFS guarantees that the
 *      first time a node is reached, it is via the shortest path.
 * 
 * =========================================================================
 * COMPLEXITY SUMMARY
 * =========================================================================
 * - Time Complexity: O(N) for all traversals, as we must visit every node.
 * - Space Complexity:
 *   - DFS (Pre/In/Post-order): O(H) recursion stack space (where H is tree height).
 *     H = log(N) for a balanced tree; H = N for a skewed (degenerate) tree.
 *   - BFS (Level-order): O(W) queue space (where W is maximum tree width).
 *     W = N/2 for a full level at the bottom.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

// Standard Binary Tree Node Definition
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// =========================================================================
// 1. BASIC TRAVERSAL IMPLEMENTATIONS
// =========================================================================

/**
 * Standard Pre-order Traversal (Root -> Left -> Right)
 */
void preOrder(TreeNode* root) {
    if (!root) return;
    cout << root->val << " ";
    preOrder(root->left);
    preOrder(root->right);
}

/**
 * Standard In-order Traversal (Left -> Root -> Right)
 */
void inOrder(TreeNode* root) {
    if (!root) return;
    inOrder(root->left);
    cout << root->val << " ";
    inOrder(root->right);
}

/**
 * Standard Post-order Traversal (Left -> Right -> Root)
 */
void postOrder(TreeNode* root) {
    if (!root) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->val << " ";
}

/**
 * Standard Level-order Traversal (Top -> Bottom, Left -> Right)
 */
void levelOrder(TreeNode* root) {
    if (!root) return;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();
        cout << curr->val << " ";
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
}

// =========================================================================
// 2. PRACTICAL APPLICATIONS WITH DETAILED CODE EXAMPLES
// =========================================================================

/**
 * APPLICATION 1 (Pre-order): Cloning/Deep-Copying a Binary Tree
 * 
 * Why Pre-order? 
 * We must instantiate the parent node first (`new TreeNode`) before we can 
 * recursively clone and assign its left and right subtrees.
 */
TreeNode* cloneTree(TreeNode* root) {
    if (!root) return nullptr;

    // Step 1: Process root (create copy node)
    TreeNode* copyNode = new TreeNode(root->val);

    // Step 2 & 3: Process children (recursively clone left and right subtrees)
    copyNode->left = cloneTree(root->left);
    copyNode->right = cloneTree(root->right);

    return copyNode;
}

/**
 * APPLICATION 2 (BST Validation): Proving if a Binary Tree is a valid BST
 * 
 * We can validate a BST using two main tree traversal strategies:
 * 
 * 1. PRE-ORDER APPROACH (Top-Down Range Validation):
 *    - Process root first: The current node's value must lie strictly within 
 *      the bounds [minVal, maxVal] inherited from ancestors.
 *    - Recurse left with upper bound root->val, and recurse right with lower bound root->val.
 *    - Why Pre-order? We make bounds checking decisions on the parent node before recursing on children.
 */
bool isValidBSTPreOrder(TreeNode* root, long long minVal = LLONG_MIN, long long maxVal = LLONG_MAX) {
    if (!root) return true;

    if (root->val <= minVal || root->val >= maxVal) {
        return false;
    }

    return isValidBSTPreOrder(root->left, minVal, root->val) && 
           isValidBSTPreOrder(root->right, root->val, maxVal);
}

/**
 * 2. IN-ORDER APPROACH (Left-to-Right Sorted Validation):
 *    - Perform a standard in-order traversal (Left -> Root -> Right).
 *    - Track the previously visited node. Every visited node's value must be 
 *      strictly greater than the previous node's value.
 *    - Why In-order? An in-order traversal of a valid BST must visit nodes 
 *      in strictly ascending order.
 */
bool isValidBSTInOrder(TreeNode* root, TreeNode*& prev) {
    if (!root) return true;

    // Recurse left
    if (!isValidBSTInOrder(root->left, prev)) return false;

    // Process root
    if (prev && root->val <= prev->val) {
        return false;
    }
    prev = root;

    // Recurse right
    return isValidBSTInOrder(root->right, prev);
}

// Wrapper for BST validation (defaults to the true in-order approach)
bool isValidBST(TreeNode* root) {
    TreeNode* prev = nullptr;
    return isValidBSTInOrder(root, prev);
}

/**
 * APPLICATION 3 (Post-order): Calculating Tree Height (Bottom-Up)
 * 
 * Why Post-order?
 * A parent node cannot determine its own height until both of its children
 * have computed their heights.
 */
int calculateHeight(TreeNode* root) {
    if (!root) return 0;

    // Step 1 & 2: Get heights of left and right subtrees
    int leftHeight = calculateHeight(root->left);
    int rightHeight = calculateHeight(root->right);

    // Step 3: Process root (return 1 + max child height)
    return 1 + max(leftHeight, rightHeight);
}

/**
 * APPLICATION 4 (Post-order): Safe Tree Deallocation (Memory Cleanup)
 * 
 * Why Post-order?
 * We must free the children nodes first. If we freed the parent node first, 
 * we would lose the pointers to its children (`parent->left` and `parent->right`), 
 * resulting in memory leaks or dangling pointers.
 */
void destroyTree(TreeNode* &root) {
    if (!root) return;

    // Step 1 & 2: Free children subtrees
    destroyTree(root->left);
    destroyTree(root->right);

    // Step 3: Delete parent
    delete root;
    root = nullptr;
}

/**
 * APPLICATION 5 (Level-order / BFS): Grouping Node Values Level-by-Level
 * 
 * Why Level-order?
 * Requires processing nodes tier-by-tier. We use a nested loop with a 
 * size-snapshot of the queue to isolate each level's nodes.
 */
vector<vector<int>> groupByLevels(TreeNode* root) {
    vector<vector<int>> levels;
    if (!root) return levels;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size(); // Snapshot of nodes at the current level
        vector<int> currentLevel;

        for (int i = 0; i < levelSize; i++) {
            TreeNode* curr = q.front();
            q.pop();

            currentLevel.push_back(curr->val);

            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        levels.push_back(currentLevel);
    }
    return levels;
}

// =========================================================================
// 3. TESTING HARNESS
// =========================================================================

int main() {
    cout << "=========================================================" << endl;
    cout << "  RUNNING BINARY TREE TRAVERSALS & APPLICATIONS TESTS    " << endl;
    cout << "=========================================================" << endl;

    /*
     * Build the following standard Binary Tree:
     *          1
     *         / \
     *        2   3
     *       / \
     *      4   5
     */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    // 1. Basic Traversals
    cout << "\n--- 1. BASIC TRAVERSALS ---" << endl;
    cout << "Pre-order (Root->Left->Right):   "; preOrder(root); cout << endl;
    cout << "In-order (Left->Root->Right):    "; inOrder(root);  cout << endl;
    cout << "Post-order (Left->Right->Root):  "; postOrder(root); cout << endl;
    cout << "Level-order (BFS, tier-by-tier): "; levelOrder(root); cout << endl;

    // 2. Pre-order Application: Cloning/Deep-Copying
    cout << "\n--- 2. PRE-ORDER APPLICATION (Cloning) ---" << endl;
    TreeNode* clonedRoot = cloneTree(root);
    cout << "Cloned Tree Level-order:         "; levelOrder(clonedRoot); cout << endl;

    // 3. In-order Application: BST Validation
    cout << "\n--- 3. IN-ORDER APPLICATION (BST Validation) ---" << endl;
    cout << "Is standard tree a valid BST?    " << (isValidBST(root) ? "Yes" : "No") << " (Expected: No)" << endl;

    /*
     * Build a valid Binary Search Tree (BST):
     *          4
     *         / \
     *        2   5
     *       / \
     *      1   3
     */
    TreeNode* bstRoot = new TreeNode(4);
    bstRoot->left = new TreeNode(2);
    bstRoot->right = new TreeNode(5);
    bstRoot->left->left = new TreeNode(1);
    bstRoot->left->right = new TreeNode(3);

    cout << "In-order traversal of BST:       "; inOrder(bstRoot); cout << endl;
    cout << "Is BST tree a valid BST?         " << (isValidBST(bstRoot) ? "Yes" : "No") << " (Expected: Yes)" << endl;

    // 4. Post-order Application: Height Calculation
    cout << "\n--- 4. POST-ORDER APPLICATION (Height) ---" << endl;
    cout << "Height of standard tree:         " << calculateHeight(root) << " (Expected: 3)" << endl;
    cout << "Height of BST tree:              " << calculateHeight(bstRoot) << " (Expected: 3)" << endl;

    // 5. Level-order Application: Level Grouping
    cout << "\n--- 5. LEVEL-ORDER APPLICATION (Level Grouping) ---" << endl;
    vector<vector<int>> levels = groupByLevels(root);
    for (size_t i = 0; i < levels.size(); i++) {
        cout << "  Level " << i << ": ";
        for (int v : levels[i]) {
            cout << v << " ";
        }
        cout << endl;
    }

    // 6. Post-order Application: Memory Cleanup
    cout << "\n--- 6. POST-ORDER APPLICATION (Safe Deallocation) ---" << endl;
    destroyTree(root);
    destroyTree(clonedRoot);
    destroyTree(bstRoot);
    cout << "Memory safely freed for all trees." << endl;
    cout << "=========================================================" << endl;

    return 0;
}
