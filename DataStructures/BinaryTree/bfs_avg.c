#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/*
  Problem: Average of Levels in Binary Tree (LeetCode 637)

  Problem Description:
  Given the root of a binary tree, return the average value of the nodes 
  on each level in the form of an array. Answers within 10^-5 of the 
  actual answer will be accepted.

  Algorithm: Breadth-First Search (BFS) / Level Order Traversal
  We use a queue to process nodes level by level. For each level, we calculate
  the sum of all node values and divide by the number of nodes in that level.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: Every node in the binary tree is enqueued and dequeued exactly once.
    Calculating the sum and count for each level happens as we visit each node.
  - Space Complexity: O(W) or O(N)
    Reason: In the worst case (a perfect binary tree), the queue will hold the 
    maximum width (W) of the tree at once. For a perfect tree, W = N/2, so 
    it is O(N).

  Alternative Approaches:
  - Depth-First Search (DFS):
    - You can use DFS to maintain two arrays: one for the sum of values at
      each level and one for the count of nodes at each level.
    - Time: O(N) - visits every node once.
    - Space: O(H) - where H is the height of the tree for recursion stack.
    - Comparison: BFS is generally more intuitive for "level-based" problems
      as it naturally processes nodes level by level.

  Brute Force Approach:
  - For every level L (from 0 to H), perform a full DFS to find all nodes at 
    depth L, sum them, and count them.
  - Time Complexity: O(H * N), which can be O(N^2) for skewed trees.
  - Comparison: This is highly inefficient as it re-traverses the same nodes 
    multiple times for each level. The O(N) BFS/DFS is far superior.
*/

typedef struct node_ node_t;
struct node_ {
    int key;
    struct node_ *left, *right;
};

node_t *create_node (int key) {
    node_t *n = calloc(1, sizeof *n);
    if (!n) return NULL;
    n->key = key;
    return n;
}

// 1 based
int get_tree_height (node_t *root) {
    if (!root) return 0;
    int left_height = get_tree_height(root->left);
    int right_height = get_tree_height(root->right);
    int max = left_height >  right_height ? left_height : right_height;
    return max + 1;
}

//////////// queue implementation ////////
typedef struct qnode_ qnode_t;
struct qnode_ {
    void *data;
    struct qnode_ *next;
};

qnode_t *create_qnode (void *data) {
    qnode_t *qn = calloc(1, sizeof *qn);
    if (qn) qn->data = data;
    return qn;    
}

void enqueue (qnode_t **head, void *data) {
    if (!head || !data) return;
    qnode_t *start = *head;

    qnode_t *qn = create_qnode(data);
    if (!start) {
        *head = qn;
        return;
    }
    qn->next = start;
    *head = qn;
    return;
}

void *dequeue (qnode_t **head) {
    if (!head) return NULL;

    qnode_t *start = *head;
    if (!start) return  NULL;
    *head = start->next;
    void *data = start->data;
    free(start);
    return data;
}

bool empty (qnode_t *head) {
    if (head && head->data) return false;
    return true;
}

//////////// end of queue implementation ////////////////

void bfs_avg (node_t *root, double *arr, int *arr_size) {
    if (!root) return;
    int i = 0;

    qnode_t *sum_queue = NULL;
    enqueue(&sum_queue, root);
    while (!empty(sum_queue)) {
        int count, sum;
        count = sum = 0;
        qnode_t *level_queue = NULL;
        while (!empty(sum_queue)) {
            node_t *n = dequeue(&sum_queue);
            if (n->left) enqueue(&level_queue, n->left);
            if (n->right) enqueue(&level_queue, n->right);
            sum += n->key;
            count += 1;
        }
        arr[i++] = sum * 1.0 / count;
        sum_queue = level_queue;
    }
    *arr_size = i;
    return;
    /* pseudo code
    queue_init(sum_queue);
    enqueue(sum_queue, root);
    while (!empty(sum_queue)) {
        int count, sum;
        count = sum = 0;
        queue_init(level_queue);
        while (!empty(sum_queue)) { 
            node = dequeue(sum_queue)
            if (node->left) enqueue(level_queue, node->left);
            if (node->right) enqueue(level_queue, node->right);
            sum += node->key;
            count += 1;
        }
        arr[i++] = sum * 1.0 / count;
        sum_queue = level_queue;
    }

    return arr

*/
}

double *get_avg_level (node_t *root, int *num_nodes) {
    int height = get_tree_height(root);
    printf("height:%d\n", height);
    double *arr = calloc(height,  sizeof *arr);
    bfs_avg(root, arr, num_nodes);
    printf("num_levels:%d\n", *num_nodes);
    return arr;
}

int main (void) {
    node_t *root = create_node(50);
    root->left = create_node(10);
    root->right = create_node(40);
    root->left->right = create_node(20);
    root->left->left = create_node(80);
    root->right->left = create_node(50);
    

    int num_levels = 0;

    double *avg = get_avg_level(root, &num_levels);
    for (int i = 0; i < num_levels; i++) {
        printf("level:%d avg:%f\n", i, avg[i]);
    }
    return 0;
}
