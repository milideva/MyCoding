#include <iostream>
#include <stack>


using namespace std;

/*
  Problem: Iterative In-order Traversal & BST Validation (LeetCode 94, 98)

  Algorithm 1: Iterative In-order (print_inorder_without_recursion)
  We use an explicit stack to simulate the recursion of an in-order traversal 
  (Left, Root, Right). We push all left children to the stack, pop the top, 
  process it, and then move to the right child.

  Complexity Analysis (Iterative In-order):
  - Time Complexity: O(N)
    Reason: We visit every node in the tree exactly once.
  - Space Complexity: O(H)
    Reason: The stack stores nodes along the current path from root to leaf. 
    In the worst case (skewed tree), H = N.

  Algorithm 2: BST Validation (isBST_inorder)
  An in-order traversal of a BST must yield node values in strictly 
  increasing order. We use a global pointer 'gprev' to track the 
  previously visited node.

  Complexity Analysis (BST Validation):
  - Time Complexity: O(N)
  - Space Complexity: O(H)

  Brute Force comparison:
  - A brute force way to perform in-order traversal without a stack or 
    recursion would involve finding the minimum element, then for each 
    element, finding its successor (using the successor algorithm). 
    Successor takes O(H). Total time: O(N * H), which is O(N^2) for 
    skewed trees. The stack-based approach is much faster (O(N)).

  Comparison:
  - Recursive vs Iterative: Recursive is simpler to write but can cause 
    stack overflow on deep trees. Iterative is more robust.
*/

struct node_ {
    int key;
    struct node_ *left;
    struct node_ *right;
};

typedef struct node_ node;


node *createNode (int key) {
    node *node = new node_;

    if (node) node->key = key;

    return node;
}

/* 
              100
           50      150
       30    60       170
     10 40  55  75
*/

void print_inorder_without_recursion (node *root) {
    stack <node *> stk;
    if (!root) return;
    node *curr = root;

    while (curr || stk.empty() == false) {
        while (curr) {
            stk.push(curr);
            curr = curr->left;
        }
        curr = stk.top();
        stk.pop();
        cout << curr->key << " ";
        curr = curr->right;
    }
    cout << endl;
}

struct node_ *gprev; // beware - global var, must be reset to NULL every time this function is called
bool isBST_inorder (node *node) {
    if (!node) return true;

    if (!isBST_inorder(node->left)) 
       return false;
    if (gprev && node->key < gprev->key) {
        // printf("Fails node:%d prev:%d \n",node->key, gprev->key); 
        return false;
    }
    gprev = node;
    return isBST_inorder(node->right);
}

/* 
              100
           50      150
       30    60   111   170
     10 40  55  75
*/
int main () {
    node *node = createNode(100);
    node->left = createNode(50);
    node->right = createNode(150);

    node->left->left = createNode(30);
    node->left->right = createNode(60);

    node->right->left = createNode(111);
    node->right->right = createNode(170);

    node->left->left->left =  createNode(10);
    node->left->left->right = createNode(140); // 40 made to 140 should fail
    
    node->left->right->left =  createNode(55);
    node->left->right->right = createNode(75);

    cout << "isBST_inorder " << isBST_inorder(node) << endl;

    node->left->left->right = createNode(40); // back to 40 should pass.

    gprev = NULL;
    cout << "isBST_inorder " << isBST_inorder(node) << endl;

    node->left->right->left =  createNode(45); // 55 made to 45 should fail

    gprev = NULL;
    cout << "isBST_inorder " << isBST_inorder(node) << endl;

    print_inorder_without_recursion(node);

    return 0;

}
