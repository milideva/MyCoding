/* 
  LeetCode 102: Binary Tree Level Order Traversal

  Algorithm: Breadth-First Search (BFS)
  BFS visits nodes level by level, starting from the root. It uses a queue 
  to keep track of the children of the current level's nodes.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: Each node is enqueued and dequeued exactly once.
  - Space Complexity: O(W) or O(N)
    Reason: The queue holds at most the maximum width (W) of the tree. 
    For a complete binary tree, the last level has N/2 nodes, making it O(N).

  Alternative Approaches:
  - Recursive DFS: Pass the current level as an argument. Use the level 
    as an index to add the node's value to the corresponding level-list.
    - Time: O(N)
    - Space: O(H) for recursion stack + O(N) for the result.
  
  Comparison:
  - BFS is the standard iterative approach and avoids stack depth issues.
  - DFS is more concise but slightly less intuitive for "breadth-first" logic.

  Brute Force Approach:
  - For every level i from 0 to height H:
  -   Traverse the tree to print nodes at level i.
  - Time Complexity: O(H * N) which is O(N^2) in the worst case.
  - Comparison: BFS is O(N) and much more efficient.
*/

#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct node_ node;
struct node_ {
    int data;
    struct node_ *left, *right;
};

#define MAX 50

typedef struct queue_ queue;

struct queue_ {
    int head; // points to first occupied element
    int tail; // points to next free element
    int max;
    node *q[MAX];
};

queue *create_q (int max) {
    queue *qh;
    if (!max || (max > MAX)) 
        return NULL;
    size_t sz =  sizeof(*qh) + max * sizeof(node *);
    qh = calloc(1, sz);
    if (!qh) 
        return NULL;
    qh->max =  max;
    return qh;
}

bool enqueue (queue *qh, node *n) {
    if (!qh || !n || qh->tail >= qh->max) return false;
    qh->q[qh->tail++] = n;
    return true;
}

node *dequeue (queue *qh) {
    if (!qh || !qh->tail || qh->tail >= qh->max) return false;
    if (qh->head == qh->tail) return false;

    node *n = qh->q[qh->head];
    qh->q[qh->head] =  NULL;
    qh->head++;
    return n;
}

node *createNode (int data) {
    node *n = calloc(1, sizeof(node));
    if (!n) return NULL;
    n->data = data;
    return n;
}

void process (node *n) {
    printf("%d ", n->data);
}

/* 
              100
           50      150
       30    60   111   170
     10 40  55  75
*/

node *create_tree () {
    node *node = createNode(100);
    node->left = createNode(50);
    node->right = createNode(150);

    node->left->left = createNode(30);
    node->left->right = createNode(60);

    node->right->left = createNode(111);
    node->right->right = createNode(170);

    node->left->left->left =  createNode(10);
    node->left->left->right = createNode(40);
 
    node->left->right->left =  createNode(55);
    node->left->right->right = createNode(75);

    return node;
}

void level_order_traversal (node *node) {
    printf("%s : ", __FUNCTION__);

    queue *qh = create_q(MAX);
    while (node) {
        if (node->left) enqueue(qh, node->left);
        if (node->right) enqueue(qh, node->right);
        process(node);
        node = dequeue(qh);
    }

    printf("\n");
}


int main (void) {
    node *root = create_tree();
    level_order_traversal(root);
}
