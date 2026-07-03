/*
  LeetCode 105: Construct Binary Tree from Inorder and Preorder Traversal

  Algorithm: Recursive DFS with HashMap
  1. Preorder: ROOT -> LEFT -> RIGHT. The first element is always the root.
  2. Inorder: LEFT -> ROOT -> RIGHT. The root splits the array into left 
     and right subtrees.
  3. Pre-process Inorder array with a HashMap (Value -> Index) for O(1) 
     root lookups.
  4. Build tree recursively by processing the preorder array from front to back.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We create N nodes. For each node, the lookup for its position 
    in the Inorder array is O(1) thanks to the HashMap.
  - Space Complexity: O(N)
    Reason: O(N) space for the HashMap and O(H) for the recursion stack.

  Comparison:
  - Brute Force: Searching the inorder array for each node takes O(N) per node.
    Total time: O(N^2).
  - The current approach is optimal for this problem.

  Brute Force comparison:
  - Navigating the preorder array takes O(N). If for each node we perform a 
    linear scan of the inorder array to find its boundaries, we spend O(N) 
    per node. 
  - Time: O(N^2). 
  - Space: O(H) for recursion.
  - The HashMap optimization reduces time to O(N) with O(N) extra space.
*/

#include <unordered_map>
#include <vector>
#include <iostream>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}  
};

class Solution {
  unordered_map <int, int> umapVal2IndexInorder;

  // Finding the root ==>
  // Preorder is ROOT LEFT RIGHT. So the first element of our
  // preorder array will always be our root, and then we will move
  // forwards in our preorder array to find the next root.

  // Finding the left and right subtree ==>
  // Inorder is LEFT ROOT RIGHT. So for any node lets say current node
  // is at index i in inorder array, if you think it as a root of its
  // subtree, then all the nodes at indices less than i will be on the
  // left subtree of the current node and all the nodes at indices
  // greater than i will be on the right subtree of the current node.

  TreeNode *makeTree(int start, int end, int &index, vector<int>& inorder, vector<int>& preorder) {

    // Since Pre Order traversal is like ROOT LEFT RIGHT, therefore
    // we will traverse the preorder array from forwards and will
    // construct our tree like ROOT LEFT RIGHT.

    // Take our node from preorder array, let say it is at index idx
    // (We came from 0 to preorder.size()-1  idx) and this will be our
    // root in current recursive call, then decrement the idx for our
    // next upcoming root.

    // Now find our current node (from step 2) in our inorder array
    // (let say we found it at i), then we will have nodes in left
    // subtree of current node who are at position less than i and
    // nodes in right subtree of current node who are at position
    // greater than i.

    // So we make a recursive call to construct the left subtree
    // first, then we make a recursive call to construct the right
    // subtree of our current node. (Since we are building our Binary
    // Tree in ROOT LEFT RIGHT).

    // If range for inorder is NOT valid then return NULL
    if (start > end) return NULL;
    
    // Create a node for our root node of current subtree
    TreeNode *root = new TreeNode(preorder[index]);
      
    // Find position of current root in inorder array
    int middle = umapVal2IndexInorder[root->val];

    // Move our pointer to preorder array for our next upcoming root if any
    index++;
		
		
    // Make a call to create left subtree, inorder range [start, i-1]
    root->left = makeTree(start, middle-1, index, inorder, preorder);

    // Make a call to create right subtree, inorder range [i+1, end]
    root->right = makeTree(middle+1, end, index, inorder, preorder);        

    return root;
  }
  
public:
  TreeNode *buildTree(vector <int> &inorder, vector <int> &preorder) {
    
    for (int i = 0; i < inorder.size(); i++) {
      umapVal2IndexInorder[inorder[i]] = i;
    }
    int indexPreorder = 0;
    return makeTree(0, inorder.size()-1, indexPreorder, inorder, preorder);
  }

};

static void inorder (TreeNode *root)  {
    if (root) {
        inorder(root->left);
        cout << root->val << " ";
        inorder(root->right);
    }
}


void printTreeInorder (TreeNode *n) {
  cout << "Inorder:" << endl;
  inorder(n);
  cout << endl;
}

static void preorder (TreeNode *root)  {
    if (root) {
      cout << root->val << " ";
      preorder(root->left);
      preorder(root->right);
    }
}


void printTreePreorder (TreeNode *n) {
  cout << "Preorder:" << endl;
  preorder(n);
  cout << endl;
}


int main () {
  class Solution sol;
  
  vector <int> inorder { 9,3,15,20,7 };
  vector <int> preorder { 3,9,20,15,7}; 
  
  TreeNode *root = sol.buildTree(inorder, preorder);
  
  printTreeInorder(root);
  printTreePreorder(root);
  return 0;
}
