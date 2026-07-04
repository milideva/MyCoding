#include <stdio.h>
#include <stdlib.h>

/*
  LeetCode 1721: Swapping Nodes in a Linked List

  Problem Description:
  You are given the head of a linked list, and an integer k. 
  Return the head of the linked list after swapping the values of 
  the kth node from the beginning and the kth node from the end 
  (the list is 1-indexed).

  Note: The problem can be solved by swapping node VALUES or by 
  swapping the NODES themselves. This implementation focuses on 
  the more challenging task of swapping the NODES.

  Algorithm: Three-Pointer Technique
  1. Find the `k`-th node from the start (`first`).
  2. Use a "slow and fast" pointer approach to find the `k`-th node 
     from the end (`second`):
     - Start `fast` at `first`.
     - Move `slow` and `fast` until `fast` reaches the end. 
     - `slow` is now at the `k`-th node from the end.
  3. Perform the pointer adjustments to swap `first` and `second`. 
     Care must be taken for special cases:
     - The nodes are the same.
     - The nodes are adjacent.
     - One of the nodes is the head.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We traverse the list once.
  - Space Complexity: O(1) auxiliary space.

  Brute Force comparison:
  - Collect all nodes in an array, swap them in the array, and 
    re-link them.
  - Time: O(N), Space: O(N).
  - The in-place pointer manipulation is more space-efficient.
*/

struct node {
    int data;
    struct node *next;
};

void push(struct node **head, int new_data) {
    struct node *new_node = calloc(1, sizeof(*new_node));
    new_node->data = new_data;
    new_node->next = *head;
    *head = new_node;
}

void printList(struct node *node) {
    while (node) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int getListSize(struct node *head) {
    int i = 0;
    while (head) {
        head = head->next;
        i++;
    }
    return i;
}

void swapKth(struct node **head, int k) {
    if (k <= 0) return;
    if (!head || !*head) return;

    int n = getListSize(*head);
    if (k > n) return;

    // kth from beginning and kth from end are the same
    if (2 * k - 1 == n) return;

    struct node *p1 = *head, *p1_prev = NULL;
    for (int i = 1; i < k; i++) {
        p1_prev = p1;
        p1 = p1->next;
    }

    struct node *p2 = *head, *p2_prev = NULL;
    for (int i = 1; i < n - k + 1; i++) {
        p2_prev = p2;
        p2 = p2->next;
    }

    // Adjust prev pointers
    if (p1_prev) p1_prev->next = p2;
    if (p2_prev) p2_prev->next = p1;

    // Adjust next pointers
    struct node *temp = p1->next;
    p1->next = p2->next;
    p2->next = temp;

    // Handle head update
    if (k == 1) *head = p2;
    if (k == n) *head = p1;
}

void test(int k) {
    struct node *head = NULL;
    for (int i = 8; i >= 1; i--) push(&head, i);

    printf("Original: "); printList(head);
    swapKth(&head, k);
    printf("Swap k=%d: ", k); printList(head);

    // Cleanup
    while (head) {
        struct node *temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    test(1);
    test(2);
    test(4); // Middle elements for n=8
    test(5);
    return 0;
}
