/*
  LeetCode 426: Convert Binary Search Tree to Sorted Doubly Linked List

  Problem Description:
  Convert a Binary Search Tree to a sorted Circular Doubly-Linked List 
  in place.

  You can think of the left and right pointers as synonymous to the 
  predecessor and successor pointers in a doubly-linked list. For a 
  circular doubly linked list, the predecessor of the first element 
  is the last element, and the successor of the last element is the 
  first element.

  We want to do the transformation in place. After the transformation, 
  the left pointer of the tree node should point to its predecessor, 
  and the right pointer should point to its successor. You should 
  return the pointer to the smallest element of the linked list.

  Algorithm: In-order DFS (In-place)
  We perform a standard in-order traversal (Left, Root, Right). We maintain 
  two pointers, 'first' and 'last'. As we visit each node, we link 'last->right' 
  to the current node and 'current->left' to 'last'. Finally, we close 
  the circle by linking the first and last nodes.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We visit each of the N nodes exactly once during the traversal.
  - Space Complexity: O(H)
    Reason: Recursion stack depth is proportional to the tree height (H).

  Comparison:
  - Copy Approach (Brute Force): Traverse the tree, store all node values 
    in a sorted array or list, then create N new Doubly Linked List nodes.
    - Time: O(N), Space: O(N).
  - In-place Approach (Current): By reusing existing TreeNode pointers (left/right 
    becoming prev/next), we achieve O(H) space on the stack without 
    extra heap allocation.

  Comparison of Traversal:
  - Standard in-order produces the sorted sequence directly. Any other 
    traversal (Pre/Post) would require sorting the result, taking O(N log N).
*/

#include <iostream>
#include <vector>

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
    TreeNode *first = nullptr;
    TreeNode *last = nullptr;
    void inOrder (TreeNode *root) {
        if (!root) return;
        inOrder(root->left);
        if (last == nullptr) {
            first = root;
        } else {
            last->right = root;
            root->left = last;
        }
        last = root;
        inOrder(root->right);
    }
    
public:
    TreeNode* treeToDoublyList(TreeNode* root) {
        if (root == nullptr) return root;
        inOrder(root);
        last->right = first;
        first->left = last;
        
        return first;
    }
};

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
  
  TreeNode *head = sol.treeToDoublyList(root);

  cout << "Head: " << head->val << endl;
  cout << "Tail: " << head->left->val << endl;

  return 0;
}
