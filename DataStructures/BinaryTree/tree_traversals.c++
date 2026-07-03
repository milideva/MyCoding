#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>

using namespace std;

// MARKER is a sentinel value used to represent a null/empty node in the level-order input vector.
const int MARKER = -1;

/*
  Problem: Common Binary Tree Operations (Traversals, Symmetry, Path Sum)

  Problem Description:
  Implement and demonstrate various binary tree traversals and 
  common operations:
  - Pre-order (Recursive & Iterative): Root -> Left -> Right
  - Level-order (BFS): Level-by-level from left to right.
  - Symmetry: Check if a tree is a mirror of itself.
  - Path Sum: Determine if the tree has a root-to-leaf path such that 
    adding up all the values along the path equals the given target sum.

  Algorithms & Complexity:

  1. Pre-order Traversal (Recursive & Iterative):
     - Time: O(N) - visits each node once.
     - Space: O(H) - stack usage.

  2. Level-order Traversal (BFS):
     - Time: O(N) - visits each node once.
     - Space: O(W) or O(N) - queue usage for the maximum width.

  3. Symmetric Tree (LeetCode 101):
     - Algorithm: Recursive DFS comparing mirrors (left->left vs right->right).
     - Time: O(N).
     - Space: O(H).

  4. Path Sum (LeetCode 112):
     - Algorithm: Pre-order DFS carrying target remainder.
     - Time: O(N).
     - Space: O(H).

  Comparison:
  - Recursive vs Iterative DFS: Recursive is more readable; iterative (using
    manual stack) avoids potential stack overflow on extremely deep trees.
  - BFS is necessary when processing level-by-level (e.g., finding the average
    of each level or the right-side view).

  Brute Force comparison:
  - Navigating the tree without a stack or queue (e.g., using "find-parent" 
    repeatedly for each node) would take O(N^2) or O(N * H). 
  - The standard DFS/BFS traversals are O(N) and are the most fundamental 
    building blocks for tree algorithms.
*/

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {

  void preOrderTraversalHelper(TreeNode* root, vector<int> &vec) {
    if (!root)
      return;
    vec.push_back(root->val);
    preOrderTraversalHelper(root->left, vec);
    preOrderTraversalHelper(root->right, vec);
  }

  bool isSymmetricHelper(TreeNode* l, TreeNode* r) {
        if (!l && !r) return true;
        if (!l && r) return false;
        if (l && !r) return false;
        if (l->val != r->val) return false;
        return isSymmetricHelper(l->left, r->right) && isSymmetricHelper(l->right, r->left);
    }

  bool pathSumDfs (TreeNode *root, int targetSum, int &pathSum) {
    if (!root)
      return false;
    pathSum += root->val;
    if (!root->left && !root->right) {
      if (targetSum == pathSum)
	        return true;
      pathSum -= root->val;
      return false;
    }
    if (pathSumDfs(root->left, targetSum, pathSum)) {
      return true;
    }

    if (pathSumDfs(root->right, targetSum, pathSum)){
      return true;
    }
    pathSum -= root->val;
    return false;
  }
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
      if (!root) return false;
      int pathSum = 0;
      return pathSumDfs(root, targetSum, pathSum);
    }

  vector<int> preOrderTraversal(TreeNode* root) {
    vector <int> vec;
    if (!root) return vec;
    preOrderTraversalHelper(root, vec);
    return vec;
  }

  vector <int> preOrderIterative (TreeNode* root) {
    vector <int> ans;
    if (!root)
      return ans;
    stack <TreeNode *> stk;
    stk.push(root);
    while (!stk.empty()) {
      auto rt = stk.top();
      stk.pop();
      ans.push_back(rt->val);
      if (rt->right) {
	      stk.push(rt->right);
      }
      if (rt->left) {
	      stk.push(rt->left);
      }
    }
    return ans;
  }

  vector<vector<int>> levelOrder(TreeNode* root) {
        vector <vector <int>> answer;
        if (!root)
            return answer;
        queue <TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            int size = q.size();
            vector <int> levelVec;

            while (size--) {
                TreeNode* node = q.front();
                q.pop();
                levelVec.push_back(node->val);
                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }

            answer.push_back(levelVec);

        }
        return answer;
    }

    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        return isSymmetricHelper(root->left, root->right);
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
    printf("print_inorder: \n");
    inorder(n);
    printf("\n");
}

void destroyTree(TreeNode* node) {
    if (!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

void print_vec_vec (vector <vector <int>> &res, string str) {
  cout << endl << str << endl;
  for (auto v: res) {
    for (auto e : v) {
      cout << e << " ";
    }
    cout << endl;
  }
}

void print_vec (vector <int> &res, string str) {
  cout << endl << str << endl;
  for (auto v:res) {
    cout << v << " ";
  }
  cout << endl;
}

int main () {
  Solution sol;

  // Test Case 1: Standard Tree
  vector<int> nodes1 = {1, 2, 3, 4, 5, 6, 7};
  TreeNode *root1 = createTreeFromLevelOrder(nodes1);
  print_inorder(root1);

  vector <int> res = sol.preOrderTraversal(root1);
  print_vec(res, "preOrder");
  res = sol.preOrderIterative(root1);
  print_vec(res, "preOrderIterative");

  vector <vector<int>> ans = sol.levelOrder(root1);
  print_vec_vec(ans, "levelOrder");

  // Test Case 2: Symmetric check (False)
  vector<int> nodes2 = {1, 2, 2, MARKER, 3, MARKER, 3};
  TreeNode *root2 = createTreeFromLevelOrder(nodes2);
  bool isMirror = sol.isSymmetric(root2);
  cout << endl << "Tree 2 " << (isMirror ? "symmetric" : "not symmetric") << endl;

  // Test Case 3: Symmetric check (True)
  vector<int> nodes3 = {1, 2, 2, 3, 4, 4, 3};
  TreeNode *root3 = createTreeFromLevelOrder(nodes3);
  isMirror = sol.isSymmetric(root3);
  cout << endl << "Tree 3 " << (isMirror ? "symmetric" : "not symmetric") << endl;

  // Test Case 4: Path Sum
  int sum = 7;
  bool hasPathSum = sol.hasPathSum(root3, sum);
  cout << endl << "hasPathSum: " << hasPathSum << " for pathSum:" << sum << endl;

  sum = 10;
  hasPathSum = sol.hasPathSum(root3, sum);
  cout << endl << "hasPathSum: " << hasPathSum << " for pathSum:" << sum << endl;

  destroyTree(root1);
  destroyTree(root2);
  destroyTree(root3);

  return 0;
}
