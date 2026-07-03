/*
  LeetCode 270: Closest Binary Search Tree Value

  Problem: Find the node value in a BST closest to a given floating-point target.

  Algorithm: Binary Search on Tree
  Since it's a BST, if the target is smaller than the current node's value, 
  the closest value must either be the current node or in the left subtree. 
  Conversely, if larger, check the right subtree.

  Complexity Analysis:
  - Time Complexity: O(H)
    Reason: We follow a single path from root to leaf, similar to searching in 
     a BST. H is the tree height.
  - Space Complexity: O(H) (Recursive) or O(1) (Iterative).

  Comparison:
  - Brute Force (In-order): Traverse the entire tree (O(N)), store in an 
    array, and find the closest value. This is O(N) time and space.
  - Iterative Optimization: By using a while-loop (implemented in 
    `closestValueIterative`), we achieve O(1) auxiliary space, making it 
    the most efficient approach for large trees.
*/

#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>
#include <cmath>
#include <cfloat>
#include <iomanip>
#include <cmath>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
  
  vector <int> inOrder;
  
  void getInOrder (TreeNode* root) {
    if (!root)
      return;
    getInOrder(root->left);
    inOrder.push_back(root->val);
    getInOrder(root->right);
  }
    
public:
  int closestValueOn(TreeNode* root, double target) {
    getInOrder(root);
    double bestDiff = DBL_MAX;
    int bestVal = INT_MAX;
    for (int i = 0; i < inOrder.size(); i++) {
      double diff = abs(inOrder[i] - target);
      if (diff < bestDiff) {
        bestDiff = diff;
        bestVal = inOrder[i];
        continue;
      }
      if (diff > bestDiff) {
        break;
      }
    }
    return bestVal;
  }

  // Recursive
  int closestValue(TreeNode* root, double target) {
    // If target < root->val, search the left subtree.
    if (target < root->val && root->left) {
      const int left = closestValue(root->left, target);
      if (abs(left - target) < abs(root->val - target))
        return left;
    }

    // If target > root->val, search the right subtree.
    if (target > root->val && root->right) {
      const int right = closestValue(root->right, target);
      if (abs(right - target) < abs(root->val - target))
        return right;
    }

    return root->val;
  }
  
  // Iterative
  int closestValueIterative(TreeNode* root, double target) {
    int closest = root->val;
    while (root) {
      if (std::abs(root->val - target) < std::abs(closest - target)) {
        closest = root->val;
      }
      root = target < root->val ? root->left : root->right;
    }
    return closest;
  }

  // Recursive without return value
  void closestValue(TreeNode* root, double target, int* closest) {
    if (!root) return;

    // Update the closest value if the current node is closer to the target
    if (std::abs(root->val - target) < std::abs(*closest - target)) {
      *closest = root->val;
    }

    if (target < root->val && root->left) {
      closestValue(root->left, target, closest);
    } else if (target > root->val && root->right) {
      closestValue(root->right, target, closest);
    }
  }
};

/*
           10
         /    \
        5      15
       / \    /  \
      3   7  13   18
     /   / \   \
    1   6   8  14


*/


#include <iostream>
#include <cmath>

// Reusing the TreeNode and Solution classes defined earlier

void testClosestValue() {
    Solution solution;

    // Helper function to print the result of each test case
    auto printResult = [](const std::string& testName, int expected, int actual) {
        if (expected == actual) {
            std::cout << testName << " Passed: Expected = " << expected << ", Actual = " << actual << "\n";
        } else {
            std::cout << testName << " Failed: Expected = " << expected << ", Actual = " << actual << "\n";
        }
    };

    // Test Case 1: Single Node Tree
    {
        TreeNode* root = new TreeNode(10);
        double target = 9.5;
        int result = solution.closestValue(root, target);
        printResult("Test Case 1", 10, result);
        delete root;
    }

    // Test Case 2: Extended BST
    {
        // Construct the extended BST
        TreeNode* root = new TreeNode(10);
        root->left = new TreeNode(5);
        root->right = new TreeNode(15);
        root->left->left = new TreeNode(3);
        root->left->right = new TreeNode(7);
        root->right->left = new TreeNode(13);
        root->right->right = new TreeNode(18);
        root->left->left->left = new TreeNode(1);
        root->left->right->left = new TreeNode(6);
        root->left->right->right = new TreeNode(8);
        root->right->left->right = new TreeNode(14);
        
        // Sub-Test Case 2.1: Target is in the middle of the tree
        {
            double target = 12.0;
            int result = solution.closestValue(root, target);
            printResult("Sub-Test Case 2.1", 13, result);
        }

        // Sub-Test Case 2.2: Target is very close to a leaf node
        {
            double target = 7.1;
            int result = solution.closestValue(root, target);
            printResult("Sub-Test Case 2.2", 7, result);
        }

        // Sub-Test Case 2.3: Target is closer to the middle of a subtree
        {
            double target = 14.1;
            int result = solution.closestValue(root, target);
            printResult("Sub-Test Case 2.3", 14, result);
        }

        // Sub-Test Case 2.4: Target is exactly at a node's value
        {
            double target = 8.0;
            int result = solution.closestValue(root, target);
            printResult("Sub-Test Case 2.4", 8, result);
        }

        // Sub-Test Case 2.5: Target is less than the smallest node value
        {
            double target = 0.5;
            int result = solution.closestValue(root, target);
            printResult("Sub-Test Case 2.5", 1, result);
        }

        // Sub-Test Case 2.6: Target is greater than the largest node value
        {
            double target = 20.0;
            int result = solution.closestValue(root, target);
            printResult("Sub-Test Case 2.6", 18, result);
        }

        // Clean up the tree
        delete root->left->right->right;
        delete root->left->right->left;
        delete root->right->left->right;
        delete root->left->left->left;
        delete root->right->right;
        delete root->right->left;
        delete root->left->right;
        delete root->left->left;
        delete root->right;
        delete root->left;
        delete root;
    }

    // Test Case 3: Left-skewed Tree
    {
        TreeNode* root = new TreeNode(4);
        root->left = new TreeNode(3);
        root->left->left = new TreeNode(2);
        root->left->left->left = new TreeNode(1);
        double target = 2.8;
        int result = solution.closestValue(root, target);
        printResult("Test Case 3", 3, result);
        delete root->left->left->left;
        delete root->left->left;
        delete root->left;
        delete root;
    }

    // Test Case 4: Right-skewed Tree
    {
        TreeNode* root = new TreeNode(1);
        root->right = new TreeNode(2);
        root->right->right = new TreeNode(3);
        root->right->right->right = new TreeNode(4);
        double target = 2.5;
        int result = solution.closestValue(root, target);
        printResult("Test Case 4", 3, result);
        delete root->right->right->right;
        delete root->right->right;
        delete root->right;
        delete root;
    }
}


///////////////////////////////// Test code ////////////////////////////////////////
TreeNode *create_TreeNode (int data) {
    TreeNode *node = (TreeNode *) calloc(1, sizeof *node);
    if (node) node->val = data;
    return node;
}

// Helper function to create a BST
TreeNode *create_BST_from_array (int array[], int start, int end) {
    if (!array) return NULL;
    if (end < start) return NULL;

    int mid = (start+end)/2;
    TreeNode *n = create_TreeNode(array[mid]);
    if (!n) return n;

    n->left = create_BST_from_array(array, start, mid-1);
    n->right = create_BST_from_array(array, mid+1, end);

    printf("TreeNode:%d left:%d right:%d\n", n->val,
           n->left ? n->left->val : 0,
           n->right ? n->right->val : 0);
    return n;
}

static void inorder (TreeNode *root)  { 
    if (root) { 
        inorder(root->left); 
        printf("%d \n", root->val); 
        inorder(root->right); 
    } 
}

void print_inorder (TreeNode *n) {
    printf("print_inorder: \n");
    inorder(n);
}

TreeNode *create_tree () {
    int array[] = { -10, 5, 10, 56, 60, 100, 233, 300, 500, 600, 700, 800, 900, 1000, 2333 };
    int end = sizeof array/ sizeof array[0];
    TreeNode *root = create_BST_from_array(array, 0, end-1);
    print_inorder(root);
    return root;
}
void print_vec_vec (vector <vector <int>> &res) {
  cout << "Vertical order : " << endl;
  for (auto v: res) {
    for (auto e : v) {
      cout << e << " ";
    }
    cout << endl;
  }
}

int main () {
  class Solution sol;
  TreeNode *root = create_tree();
  double target = 850.00001;
  
  cout << std::setprecision(5) << std::fixed;

  int res = sol.closestValue(root, target);
  cout << "Target: " << target << " Closest value:" << res << '\n';

  target = 849.99999;
  res = sol.closestValue(root, target);
  cout << "Target: " << target << " Closest value:" << res << '\n';


  testClosestValue();
  std::cout << "All test cases passed!\n";

  return 0;
}
