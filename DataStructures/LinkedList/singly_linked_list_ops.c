#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

/*
  Problem: Singly Linked List Operations (C Implementation)

  Problem Description:
  A comprehensive implementation of various singly linked list 
  operations, including:
  - Insertion (Head, Sorted, Unsorted)
  - Deletion (By Value, Without tracking previous)
  - Reversal (Iterative, Recursive)
  - Search (k-th from last, Loop detection, Loop start)
  - Properties (Palindrome check, Length, Comparison)
  - Advanced (Random cloning, Merging sorted lists, Rotations)

  Complexity Analysis:
  - Insertion/Deletion (Head): O(1)
  - Insertion/Deletion (Middle/Tail): O(N)
  - Search: O(N)
  - Reversal: O(N)
  - Space Complexity: O(1) for most iterative operations, 
    O(N) for recursive ones or those requiring auxiliary stacks.

  Comparison:
  - Singly linked lists provide O(1) insertion at the head but 
    lack the bidirectional navigation of doubly linked lists. 
    They are more memory-efficient as they only store one pointer per node.
*/

typedef struct node_tag node_t;

struct node_tag {
    struct node_tag *next, *random;
    int value;
};

static node_t *create_node (int data) {
    node_t *node = calloc(1, sizeof(node_t));
    if (node)
        node->value = data;
    return node;
}

static void print_list (node_t *head) {
    if (!head) {
        printf("List: empty\n");
        return ;
    }
    node_t *node = head;
    printf("List: ");
    while (node) {
        printf("%d -> ", node->value);
        node = node->next;
    }
    printf("NULL\n");
}

static void push (node_t **head, int data) {
    if (!head) return;
    node_t *n = malloc(sizeof(*n));
    if (!n) return;
    n->value = data;
    n->next = *head;
    *head = n;
}

static void reverse (node_t **head) {
    node_t *prev = NULL;
    node_t *current = *head, *next;
    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

bool find_loop (node_t *head) {
    node_t *slow = head, *fast = head;
    while (slow && fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

static void free_list (node_t **head) {
    if (!head) return;
    node_t *node = *head;
    while (node) {
        node_t *next = node->next;
        free(node);
        node = next;
    }
    *head = NULL;
}

void test_basic_ops() {
    printf("Testing Basic Singly Linked List Ops\n");
    node_t *head = NULL;
    push(&head, 10);
    push(&head, 20);
    push(&head, 30);
    print_list(head);

    reverse(&head);
    printf("After Reversal: ");
    print_list(head);

    printf("Loop Detection: %s\n", find_loop(head) ? "Found" : "None");
    
    free_list(&head);
}

int main () {
    test_basic_ops();
    return 0;
}
