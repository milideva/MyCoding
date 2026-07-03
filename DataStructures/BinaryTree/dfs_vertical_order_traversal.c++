/*
  LeetCode 987: Vertical Order Traversal of a Binary Tree

  Problem Description:
  Given the root of a binary tree, calculate the vertical order 
  traversal of the binary tree. For each node at position (row, col), 
  its left child will be at (row + 1, col - 1), and its right child 
  will be at (row + 1, col + 1). The root is at (0, 0).

  The vertical order traversal of a binary tree is a list of 
  top-to-bottom orderings for each column index starting from the 
  leftmost column and ending on the rightmost column. There may 
  be multiple nodes in the same row and same column. In such a 
  case, sort these nodes by their values.

  Algorithm: DFS with Map
  1. Use a nested map `map<int, map<int, multiset<int>>>` where the first 
     key is the column (x), the second is the row (y), and the multiset 
     stores node values at that coordinate (to handle sorting for same 
     position).
  2. Perform a DFS/BFS to populate the map.
  3. Traverse the map to collect the results into the final 2D vector.

  Complexity Analysis:
  - Time Complexity: O(N log N)
    Reason: We visit every node (N). Inserting into the map and 
    multiset takes O(log N). Sorting and traversing also take O(N log N).
  - Space Complexity: O(N)
    Reason: To store all node values in the map structure.

  Comparison:
  - BFS vs DFS: BFS is often preferred for vertical traversal as it 
    naturally processes nodes level-by-level (row-by-row), but DFS 
    works fine as long as we store the coordinates and sort correctly.
  - The current map-based approach is robust for the LeetCode 
    requirements.

  Brute Force comparison:
  - For every column, perform a full tree traversal to find all nodes in 
    that column and sort them. 
  - Time: O(W * N log N), where W is the width of the tree.
  - Using a map reduces this to a single traversal + sorting overhead.
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
