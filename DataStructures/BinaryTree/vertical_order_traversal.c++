/*

Given a binary tree, return the vertical order traversal of its nodes values.

For each node at position (X, Y), its left and right children respectively will
be at positions (X-1, Y-1) and (X+1, Y-1).

Running a vertical line from X = -infinity to X = +infinity, whenever the
vertical line touches some nodes, we report the values of the nodes in order
from top to bottom (decreasing Y coordinates).

If two nodes have the same position, then the value of the node that is reported
first is the value that is smaller.

Return an list of non-empty reports in order of X coordinate. Every report will
have a list of values of nodes.

Example 1:

Input: [3,9,20,null,null,15,7]
Output: [[9],[3,15],[20],[7]]
Explanation:
Without loss of generality, we can assume the root node is at position (0, 0):
Then, the node with value 9 occurs at position (-1, -1);
The nodes with values 3 and 15 occur at positions (0, 0) and (0, -2);
The node with value 20 occurs at position (1, -1);
The node with value 7 occurs at position (2, -2).

Example 2:

Input: [1,2,3,4,5,6,7]
Output: [[4],[2],[1,5,6],[3],[7]]
Explanation:
The node with value 5 and the node with value 6 have the same position according to the given scheme.
However, in the report "[1,5,6]", the node value of 5 comes first since 5 is smaller than 6.

Note:

    The tree will have between 1 and 1000 nodes.
    Each node's value will be between 0 and 1000.

*/

#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

/*
  LeetCode 987: Vertical Order Traversal of a Binary Tree

  Problem: Similar to LC 314, but with strict sorting rules:
  - Sort by Column (X) first.
  - If same X, sort by Row (Y) top-to-bottom.
  - If same X and Y, sort by Value (Val).

  Algorithm: DFS + Sorted Nested Maps/Sets
  We use `map<int, set<pair<int, int>>>` where:
  - Key 1 (int): Column index (X).
  - Value 1 (set): Contains pairs of (Row Index Y, Node Value).
  By using `std::set<pair<int, int>>`, C++ automatically sorts by Y 
  coordinate first, and then by the node value if Y is identical.

  Complexity Analysis:
  - Time Complexity: O(N log N)
    Reason: Every node is inserted into a map and a set. The set sorting 
    overhead for N elements results in O(N log N).
  - Space Complexity: O(N)
    Reason: We store all nodes in the map structure.

  Comparison with LC 314:
  - LC 314 only requires top-to-bottom order for the same column,
    making BFS ideal.
  - LC 987 requires sorting values if coordinates are identical,
    making a coordinate-based DFS + Sort approach more appropriate.

  Brute Force Approach:
  - Collect all nodes into a list of triplets: (X, Y, Value).
  - Sort the entire list using a custom comparator.
  - Time: O(N log N).
  - The nested Map/Set approach is also O(N log N) but organizes the data 
    as it's collected, which can be more memory efficient than a large flat list.
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
  // sort based on <row, col, val>
  map <int, set <pair<int,int>> > mp; // x --> { y, value } lower x first, lower y first, lower val first

  // why map ? Because map is an ordered data structure. The order is according
  // to the key, which here is tree level. lower key first.

  // why set ? Because set is an ordered data structure. If two nodes have the
  // same position, then the value of the node that is reported first is the
  // value that is smaller.
  // set <pair <a, b>> // orders on lower a first, if a is same, then orders on lower b first.

  // vertical order is row wise ordering, row = level
  void pre ( TreeNode *root, int x, int y ){
    if(!root)
      return ;
    mp[x].insert( {y, root->val} );
    pre(root->left, x-1, y+1);
    pre(root->right, x+1, y+1);
  }

public:
  vector<vector<int>> verticalTraversal(TreeNode* root) {
    mp.clear();
    pre(root, 0, 0 );
    vector <vector<int>> v;
    for (auto const& [x, s] : mp ) {
      vector<int> c;

      for (auto const& [y, val] : s )
        c.push_back(val);

      v.push_back(c);
    }
    return v;
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

static void inorder (TreeNode *root)  {
    if (root) {
        inorder(root->left);
        printf("%d ", root->val);
        inorder(root->right);
    }
}

void print_inorder (TreeNode *n) {
    printf("print_inorder: ");
    inorder(n);
    printf("\n");
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
  vector <vector <int>> res1 = sol.verticalTraversal(root1);
  print_vec_vec(res1, "Example 1 Vertical Order");
  // Expected: [[9],[3,15],[20],[7]]

  // Example 2: [1,2,3,4,5,6,7]
  vector<int> nodes2 = {1, 2, 3, 4, 5, 6, 7};
  TreeNode *root2 = createTreeFromLevelOrder(nodes2);
  vector <vector <int>> res2 = sol.verticalTraversal(root2);
  print_vec_vec(res2, "Example 2 Vertical Order");
  // Expected: [[4],[2],[1,5,6],[3],[7]]

  destroyTree(root1);
  destroyTree(root2);

  return 0;
}
