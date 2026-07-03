/*
  LeetCode 652: Find Duplicate Subtrees

  Problem Description:
  Given the root of a binary tree, return all duplicate subtrees. 
  For each kind of duplicate subtrees, you only need to return the 
  root node of any one of them. Two trees are duplicate if they 
  have the same structure with the same node values.

  Algorithm: DFS + Serialization + HashMap
  We traverse the tree in a post-order fashion. For each node, we generate a 
  unique string representation (serialization) of its subtree. We store these 
  strings in a hash map to count occurrences.

  Complexity Analysis:
  - Time Complexity: O(N^2)
    Reason: We visit every node (N). However, at each node, we create a 
    serialization string. In the worst case (a skewed tree), the length of 
    these strings can be O(N). String concatenation and hashing an O(N) 
    string takes O(N) time. Thus, N nodes * O(N) per node = O(N^2).
  - Space Complexity: O(N^2)
    Reason: We store the serialization string for every node in the hash map. 
    Following the same logic as time complexity, the total space for all 
    strings can reach O(N^2).

  Optimized Approach:
  - Instead of full string serialization, use a unique "triplet" ID for each 
    subtree: (node->val, left_subtree_id, right_subtree_id). 
  - Map each unique triplet to a new integer ID.
  - Time: O(N) - hashing a triplet of 3 integers is O(1).
  - Space: O(N) - storing integer IDs instead of long strings.

  Comparison:
  - Brute Force: Comparing every possible pair of subtrees would take O(N^3).
  - The current string serialization is O(N^2), which is acceptable for 
    moderate N (like LeetCode's N=5000 constraint).
*/

#include <unordered_map>
#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

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
  unordered_map < string, vector <TreeNode *>> str2node;

  string serialize (TreeNode *node) {
    if (node == nullptr)
      return "#";
    string subtree;

    subtree += "(" + serialize(node->left) + to_string(node->val) + serialize(node->right) + ")";
    str2node[subtree].push_back(node);
    return subtree;
  }

public:
  vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
    str2node.clear();
    vector<TreeNode*> res;
    serialize(root);

    for (auto const& [str, nodes] : str2node) {
      if (nodes.size() > 1) {
        res.push_back(nodes[0]);
      }
    }

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

int main () {
  Solution sol;

  // Example 1: root = [1,2,3,4,null,2,4,null,null,4]
  vector<int> nodes1 = {1, 2, 3, 4, MARKER, 2, 4, MARKER, MARKER, 4};
  TreeNode *root1 = createTreeFromLevelOrder(nodes1);

  vector <TreeNode *> res = sol.findDuplicateSubtrees(root1);
  cout << "Example 1 duplicates:" << endl;
  for (auto n : res) {
      print_inorder(n);
  }

  destroyTree(root1);
  return 0;
}
