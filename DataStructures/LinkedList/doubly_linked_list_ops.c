#include <stdlib.h>
#include <stdio.h>

/*
  Problem: Doubly Linked List Operations (C Implementation)

  Problem Description:
  A comprehensive implementation of various doubly linked list 
  operations, including:
  - Insertion (Sorted)
  - Deletion (By Value)
  - Memory Management

  Complexity Analysis:
  - Insertion (Sorted): O(N)
  - Deletion (By Value): O(N)
  - Space Complexity: O(1) auxiliary space for these operations.

  Comparison:
  - Doubly linked lists allow for bidirectional traversal (next and prev), 
    making deletions at a known node O(1). However, they use more memory 
    per node than singly linked lists.
*/

typedef struct node_tag node_t;

struct node_tag {
    struct node_tag *next;
    struct node_tag *prev;
    int value;
};

static node_t *create_node (int data) {
    node_t *node = (node_t*)calloc(1, sizeof(node_t));
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
        printf("%d <-> ", node->value);
        node = node->next;
    }
    printf("NULL\n");
}

static void del_node (node_t **head, int value) {
    if (!head || !*head) return;

    node_t *curr = *head;
    while (curr) {
        if (curr->value == value) {
            node_t *to_delete = curr;
            if (curr->prev) curr->prev->next = curr->next;
            if (curr->next) curr->next->prev = curr->prev;
            if (curr == *head) *head = curr->next;
            
            curr = curr->next;
            free(to_delete);
        } else {
            curr = curr->next;
        }
    }
}

static void add_node_sorted (node_t **head, int val) {
    node_t *node = create_node(val);
    if (!head || !node) return;

    if (!*head) {
        *head = node;
        return;
    }

    node_t *curr = *head;
    while (curr->next && curr->value < val) {
        curr = curr->next;
    }

    if (curr->value >= val) {
        // Insert before curr
        node->next = curr;
        node->prev = curr->prev;
        if (curr->prev) curr->prev->next = node;
        curr->prev = node;
        if (curr == *head) *head = node;
    } else {
        // Insert after curr (tail)
        curr->next = node;
        node->prev = curr;
    }
}

void test_doubly() {
    printf("Testing Doubly Linked List\n");
    node_t *head = NULL;
    add_node_sorted(&head, 20);
    add_node_sorted(&head, 10);
    add_node_sorted(&head, 30);
    print_list(head);

    del_node(&head, 20);
    printf("After deleting 20: ");
    print_list(head);

    // Cleanup
    while (head) {
        node_t *temp = head;
        head = head->next;
        free(temp);
    }
}

int main () {
    test_doubly();
    return 0;
}
