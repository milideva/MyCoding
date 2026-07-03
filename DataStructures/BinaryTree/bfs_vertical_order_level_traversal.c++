#include <map>
#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

/*
  LeetCode 314: Binary Tree Vertical Order Traversal

  Problem Description:
  Given the root of a binary tree, return the vertical order 
  traversal of its nodes' values. (i.e., from top to bottom, 
  column by column).

  If two nodes are in the same row and column, the order should 
  be from left to right.

  Algorithm: BFS with Map
  1. Use a map `map<int, vector<int>>` where the key is the column index 
     (root is 0).
  2. Use a queue for BFS, storing pairs of `(Node*, column_index)`.
  3. BFS ensures that nodes are visited from top to bottom and left to 
     right for the same column.
  4. Collect all vectors from the map (which is sorted by key) into the 
     final 2D result.

  Complexity Analysis:
  - Time Complexity: O(N log W)
    Reason: We visit every node (N). Inserting into the map takes 
    O(log W) where W is the width of the tree.
  - Space Complexity: O(N)
    Reason: To store all node values in the map.

  Comparison:
  - BFS vs DFS: BFS is better here because the problem asks for nodes 
    in the same row/column to be ordered from left to right. Standard BFS 
    handles this naturally, while DFS would require storing the row 
    index and sorting.
  - The map keeps columns in the correct left-to-right order.

  Brute Force comparison:
  - Calculate the width boundaries first (min_col, max_col), then for 
    each col in [min_col, max_col], run a full traversal.
  - Time: O(W * N). 
  - Using a map and single BFS is more efficient.
*/

Input: [3,9,8,4,0,1,7,null,null,null,2,5] (0's right child is 2 and 1's left child is 5)

     3
    /\
   /  \
   9   8
  /\  /\
 /  \/  \
 4  01   7
    /\
   /  \
   5   2

Output:

[
  [4],
  [9,5],
  [3,0,1],
  [8,2],
  [7]
]

*/

/*
  LeetCode 314: Binary Tree Vertical Order Traversal

  Problem: Return vertical order traversal (top to bottom, column by column).

  Algorithm: Breadth-First Search (BFS) + Map
  1. Use a queue to store pairs of (TreeNode*, column_index).
  2. The root is at column 0. Left children at col-1, right at col+1.
  3. Use a Map (TreeMap) to store nodes grouped by their column index. 
     Since Map is sorted by keys, we get columns in order.
  4. BFS ensures that within each column, nodes are processed top-to-bottom.

  Complexity Analysis:
  - Time Complexity: O(N log W)
    Reason: We visit every node (N). For each node, we perform an insertion 
    into a map. The map size is proportional to the width (W) of the tree.
  - Space Complexity: O(N)
    Reason: We store all node values in the map and the queue.

  Comparison:
  - DFS Approach: If you use DFS, you must also track the row (level) to
    ensure nodes in the same column are sorted correctly (top to bottom).
    BFS is naturally suited for this without extra level sorting.
  - Hash Map + Range Tracking: Instead of a sorted `std::map`, use
    `std::unordered_map` and keep track of min/max column indices to
    achieve O(N) time.

  Brute Force Approach:
  - 1. Calculate the column index for every node and store as (node, col).
  - 2. Sort all nodes by column index O(N log N).
  - 3. For nodes with the same column, sort by level O(N log N).
  - Time: O(N log N).
  - The map + BFS approach is O(N log W), which is typically better as W << N.
*/

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
    map <int, vector <int>> mp;

public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        mp.clear();
        vector<vector<int>> res;
        if(!root) return res;

        queue <pair<TreeNode *, int>> q;
        q.push({root, 0});

        while (!q.empty()) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                auto [n, y] = q.front(); q.pop();
                mp[y].push_back(n->val);
                if (n->left)
                    q.push({n->left, y -1});
                if (n->right)
                    q.push({n->right, y + 1});
            }
        }
        for (auto const& [col, values] : mp)
            res.push_back(values);

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

void destroyTree(TreeNode* node) {
    if (!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

void print_vec_vec (vector <vector <int>> &res, string label) {
  cout << label << " : " << endl;
  for (auto v: res) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
      cout << v[i] << (i == v.size() - 1 ? "" : ", ");
    }
    cout << "] ";
  }
  cout << endl;
}

int main () {
  Solution sol;

  // Example 1: [3,9,20,null,null,15,7]
  vector<int> nodes1 = {3, 9, 20, MARKER, MARKER, 15, 7};
  TreeNode *root1 = createTreeFromLevelOrder(nodes1);
  vector <vector <int>> res1 = sol.verticalOrder(root1);
  print_vec_vec(res1, "Example 1 Vertical Order");
  // Expected: [[9],[3,15],[20],[7]]

  // Example 2: [3,9,8,4,0,1,7]
  vector<int> nodes2 = {3, 9, 8, 4, 0, 1, 7};
  TreeNode *root2 = createTreeFromLevelOrder(nodes2);
  vector <vector <int>> res2 = sol.verticalOrder(root2);
  print_vec_vec(res2, "Example 2 Vertical Order");
  // Expected: [[4],[9],[3,0,1],[8],[7]]

  destroyTree(root1);
  destroyTree(root2);

  return 0;
}
