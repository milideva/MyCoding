/*
  LeetCode 106: Construct Binary Tree from Inorder and Postorder Traversal

  Algorithm: Recursive DFS with HashMap
  1. Postorder: LEFT -> RIGHT -> ROOT. The last element is always the root.
  2. Inorder: LEFT -> ROOT -> RIGHT. The root splits the array into left 
     and right subtrees.
  3. Pre-process Inorder array with a HashMap (Value -> Index) for O(1) 
     root lookups.
  4. Build tree recursively by processing the postorder array from back to front.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We create N nodes, and for each node, we perform a constant 
    time HashMap lookup and pointer wiring.
  - Space Complexity: O(N)
    Reason: We use O(N) space for the HashMap. Recursion stack takes 
    O(H) space, where H is the height of the tree.

  Comparison:
  - Without HashMap: Finding the root index in the Inorder array in every
    recursive call takes O(N). This results in O(N^2) total time.
  - The HashMap optimization is standard for this problem to achieve
    linear time complexity.

  Brute Force comparison:
  - The O(N^2) approach is the brute force here. Since every node must be 
    located in the inorder array to split the subtrees, the total work 
    becomes a summation of search times. Using a HashMap converts the 
    O(N) search into an O(1) lookup.
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
  unordered_map <int, int> mp;  // val to inorder index

  // Finding the root ==>
  // Postorder is LEFT RIGHT ROOT. So the last element of our
  // postorder array will always be our root, and then we will move
  // backwards in our postorder array to find the next root.

  // Finding the left and right subtree ==>
  // Inorder is LEFT ROOT RIGHT. So for any node lets say current node
  // is at index i in inorder array, if you think it as a root of its
  // subtree, then all the nodes at indices less than i will be on the
  // left subtree of the current node and all the nodes at indices
  // greater than i will be on the right subtree of the current node.

  TreeNode *makeBinaryTree (int start, int end, int &postIndex, vector <int> &inorder, vector <int> &postorder) {

    // Since Post Order traversal is like LEFT RIGHT ROOT, therefore
    // we will traverse the postorder array from backwards and will
    // construct our tree like ROOT RIGHT LEFT.

    // Take our node from postorder array, let say it is at index idx
    // (We came from postorder.size()-1 to idx) and this will be our
    // root in current recursive call, then decrement the idx for our
    // next upcoming root.

    // Now find our current node (from step 2) in our inorder array
    // (let say we found it at i), then we will have nodes in left
    // subtree of current node who are at position less than i and
    // nodes in right subtree of current node who are at position
    // greater than i.

    // So we make a recursive call to construct the right subtree
    // first, then we make a recursive call to construct the left
    // subtree of our current node. (Since we are building our Binary
    // Tree in ROOT RIGHT LEFT).

    // If range for inorder is NOT valid then return NULL
    if (start > end) return NULL;
    cout << "start:" << start << " end:" << end << endl;
    cout << "postorder[]:" << postorder[postIndex] << " postIndex:" << postIndex << endl;
    // Create a node for our root node of current subtree
    TreeNode* root = new TreeNode(postorder[postIndex]);
        
    // Find position of current root in inorder array
    int i = mp[root->val];
    cout << "i: " << i << endl;
    // Decrement our pointer to postorder array for our next upcoming root if any
    postIndex--;
		
    // Make a call to create right subtree, inorder range [i+1, end]
    root->right = makeBinaryTree(i+1, end, postIndex, inorder, postorder);
		
    // Make a call to create left subtree, inorder range [start, i-1]
    root->left = makeBinaryTree(start, i-1, postIndex, inorder, postorder);
        
    return root;
  }
  
public:
  TreeNode *buildTree(vector <int> &inorder, vector <int> &postorder) {
    int index = postorder.size()-1;
    for (int i = 0; i < inorder.size(); i++) {
      mp[inorder[i]] = i;
    }
    return makeBinaryTree(0, inorder.size()-1, index, inorder, postorder);
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

static void postorder (TreeNode *root)  {
    if (root) {
        postorder(root->left);
	postorder(root->right);
        cout << root->val << " ";
    }
}


void printTreePostorder (TreeNode *n) {
  cout << "Postorder:" << endl;
  postorder(n);
  cout << endl;
}


int main () {
  class Solution sol;
  
  vector <int> inorder { 9,3,15,20,7 };
  vector <int> postorder { 9,15,7,20,3 };
  
  TreeNode *root = sol.buildTree(inorder, postorder);
  
  printTreeInorder(root);
  printTreePostorder(root);
  return 0;
}
