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
    node_t *n = calloc(1, sizeof(*n));
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

static bool pop (node_t **head, int *data) {
    if (!head || !data || !*head)
        return false;

    node_t *n = *head;
    *head = n->next;
    *data = n->value;
    free(n);
    return true;
}

bool is_palindrome (node_t *head) {
    if (!head) return false;
    if (!head->next) return true;
    
    node_t *slow = head, *fast = head;
    node_t *stack = NULL;

    while (fast && fast->next) {
        push(&stack, slow->value);
        slow = slow->next;
        fast = fast->next->next;
    }
    if (fast) {
        /* Has odd #elements, skip the middle node */
        slow = slow->next;
    }
    
    bool palindrome = true;
    while (slow) {
        int top = 0;
        if (!pop(&stack, &top) || top != slow->value) {
            palindrome = false;
            break;
        }
        slow = slow->next;
    }
    free_list(&stack);
    return palindrome;
}

static void recursive_reverse (node_t **head) {
    if (!head || !*head || !(*head)->next) return;

    node_t *first = *head;
    node_t *rest = first->next;

    recursive_reverse(&rest);
    first->next->next = first;
    first->next = NULL;
    *head = rest;
}

node_t *find_loop_start (node_t *head) {
    node_t *slow = head, *fast = head;
    bool loop_flag = false;

    while (slow && fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            loop_flag = true;
            break;
        }
    }

    if (!loop_flag) return NULL;

    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

static bool compare_two_lists (node_t *n1, node_t *n2) {
    if (!n1 && !n2) return true;
    if (!n1 || !n2) return false;
    if (n1->value != n2->value) return false;
    return compare_two_lists(n1->next, n2->next);
}

node_t *random_clone (node_t *head) {
    if (!head) return NULL;
    
    node_t *curr = head;
    // Step 1: Create duplicate nodes and insert them after the original nodes
    while (curr) {
        node_t *copy = create_node(curr->value);
        if (!copy) {
            // Clean up copies and revert
            curr = head;
            while (curr) {
                node_t *next_orig = curr->next;
                if (next_orig) {
                    node_t *next_next = next_orig->next;
                    free(next_orig);
                    curr->next = next_next;
                }
                curr = curr->next;
            }
            return NULL;
        }
        copy->next = curr->next;
        curr->next = copy;
        curr = copy->next;
    }

    // Step 2: Copy the random pointers for the duplicated nodes
    curr = head;
    while (curr) {
        node_t *copy = curr->next;
        if (curr->random) {
            copy->random = curr->random->next;
        } else {
            copy->random = NULL;
        }
        curr = copy->next;
    }

    // Step 3: Separate the original and the cloned list
    curr = head;
    node_t *copy_head = head->next;
    while (curr) {
        node_t *copy = curr->next;
        curr->next = copy->next;
        curr = curr->next;
        if (curr) {
            copy->next = curr->next;
        } else {
            copy->next = NULL;
        }
    }
    return copy_head;
}

static void copy_linked_list (node_t *src, node_t **dest) {
    if (!dest) return;
    if (!src) {
        *dest = NULL;
        return;
    }
    *dest = create_node(src->value);
    if (*dest) {
        copy_linked_list(src->next, &((*dest)->next));
    }
}

node_t* mergeTwoLists(node_t* list1, node_t* list2) {
    if (!list1 || !list2)
        return list1 ? list1 : list2;
    if (list1->value > list2->value) {
        node_t *temp = list1;
        list1 = list2;
        list2 = temp;
    }
    list1->next = mergeTwoLists(list1->next, list2);
    return list1;
}

node_t* merge (node_t *head1, node_t *head2) {
    if (!head1) return head2;
    if (!head2) return head1;

    node_t *it1, *it2, *head;
    head = (head1->value <= head2->value) ? head1 : head2;

    if (head == head1) {
        it1 = head1;
        it2 = head2;
    } else {
        it1 = head2;
        it2 = head1;
    }

    while (it1->next && it2) {
        if (it1->next->value > it2->value) {
            node_t *temp = it1->next;
            it1->next = it2;
            it2 = temp;
        } else {
            it1 = it1->next;
        }
    }

    if (it2) {
        it1->next = it2;
    }
    return head;
}

static void remove_duplicates_unsorted (node_t *head) {
    if (!head) return;
    node_t *n1 = head;
    while (n1 && n1->next) {
        node_t *n2 = n1;
        while (n2->next) {
            if (n1->value == n2->next->value) {
                node_t *dup = n2->next;
                n2->next = n2->next->next;
                free(dup);
            } else {
                n2 = n2->next;
            }
        }
        n1 = n1->next;
    }
}

static bool rotate_list (node_t **head, unsigned int k) {
    if (!head || !*head || !(*head)->next || k == 0) return true;
    
    node_t *curr = *head;
    unsigned int len = 1;
    while (curr->next) {
        curr = curr->next;
        len++;
    }
    
    k = k % len;
    if (k == 0) return true;
    
    node_t *new_tail = *head;
    for (unsigned int i = 0; i < len - k - 1; i++) {
        new_tail = new_tail->next;
    }
    
    curr->next = *head;
    *head = new_tail->next;
    new_tail->next = NULL;
    return true;
}

node_t *kth_from_last (node_t *head, unsigned int k) {
    if (!head || k == 0) return NULL;
    node_t *slow = head, *fast = head;
    for (unsigned int i = 0; i < k; i++) {
        if (!fast) return NULL;
        fast = fast->next;
    }
    while (fast) {
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}

static node_t *remove_middle (node_t *head) {
    if (!head) return NULL;
    if (!head->next) return head; // only one node, return it

    node_t *slow = head, *fast = head, *prev = NULL;
    while (fast && fast->next) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    if (prev) {
        prev->next = slow->next;
    }
    return slow;
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

void test_restored_ops() {
    printf("\n--- Testing Restored Singly Linked List Ops ---\n");

    // 1. Test is_palindrome
    {
        printf("1. Palindrome Check:\n");
        node_t *p_list = NULL;
        push(&p_list, 1);
        push(&p_list, 2);
        push(&p_list, 3);
        push(&p_list, 2);
        push(&p_list, 1);
        print_list(p_list);
        printf("   Is palindrome? %s (Expected: Yes)\n", is_palindrome(p_list) ? "Yes" : "No");
        free_list(&p_list);

        node_t *np_list = NULL;
        push(&np_list, 1);
        push(&np_list, 2);
        push(&np_list, 3);
        push(&np_list, 4);
        print_list(np_list);
        printf("   Is palindrome? %s (Expected: No)\n", is_palindrome(np_list) ? "Yes" : "No");
        free_list(&np_list);
    }

    // 2. Test recursive_reverse
    {
        printf("2. Recursive Reverse:\n");
        node_t *list = NULL;
        push(&list, 3);
        push(&list, 2);
        push(&list, 1);
        printf("   Before: "); print_list(list);
        recursive_reverse(&list);
        printf("   After:  "); print_list(list);
        free_list(&list);
    }

    // 3. Test find_loop_start
    {
        printf("3. Find Loop Start:\n");
        node_t *list = NULL;
        push(&list, 5);
        push(&list, 4);
        push(&list, 3);
        push(&list, 2);
        push(&list, 1);
        // Connect tail (5) to node 3 to create a loop
        node_t *tail = list;
        while (tail->next) tail = tail->next;
        node_t *loop_node = list->next->next; // value 3
        tail->next = loop_node;

        printf("   Loop present? %s (Expected: Yes)\n", find_loop(list) ? "Yes" : "No");
        node_t *start = find_loop_start(list);
        if (start) {
            printf("   Loop start node value: %d (Expected: 3)\n", start->value);
        } else {
            printf("   No loop start detected!\n");
        }
        
        // Break the loop before freeing
        tail->next = NULL;
        free_list(&list);
    }

    // 4. Test compare_two_lists
    {
        printf("4. Compare Two Lists:\n");
        node_t *l1 = NULL, *l2 = NULL, *l3 = NULL;
        push(&l1, 3); push(&l1, 2); push(&l1, 1);
        push(&l2, 3); push(&l2, 2); push(&l2, 1);
        push(&l3, 4); push(&l3, 2); push(&l3, 1);
        printf("   l1: "); print_list(l1);
        printf("   l2: "); print_list(l2);
        printf("   l3: "); print_list(l3);
        printf("   l1 == l2? %s (Expected: Yes)\n", compare_two_lists(l1, l2) ? "Yes" : "No");
        printf("   l1 == l3? %s (Expected: No)\n", compare_two_lists(l1, l3) ? "Yes" : "No");
        free_list(&l1);
        free_list(&l2);
        free_list(&l3);
    }

    // 5. Test random_clone
    {
        printf("5. Random Clone:\n");
        node_t *l1 = create_node(1);
        node_t *l2 = create_node(2);
        node_t *l3 = create_node(3);
        l1->next = l2;
        l2->next = l3;
        l1->random = l3; // 1's random is 3
        l2->random = l1; // 2's random is 1
        l3->random = l2; // 3's random is 2

        printf("   Original: \n");
        node_t *curr = l1;
        while (curr) {
            printf("     Node %d (Random: %d)\n", curr->value, curr->random ? curr->random->value : -1);
            curr = curr->next;
        }

        node_t *clone = random_clone(l1);
        printf("   Clone: \n");
        curr = clone;
        while (curr) {
            printf("     Node %d (Random: %d)\n", curr->value, curr->random ? curr->random->value : -1);
            curr = curr->next;
        }
        
        free_list(&l1);
        free_list(&clone);
    }

    // 6. Test copy_linked_list
    {
        printf("6. Copy Linked List:\n");
        node_t *orig = NULL, *copy = NULL;
        push(&orig, 3); push(&orig, 2); push(&orig, 1);
        printf("   Original: "); print_list(orig);
        copy_linked_list(orig, &copy);
        printf("   Copy:     "); print_list(copy);
        printf("   Is copy equal? %s (Expected: Yes)\n", compare_two_lists(orig, copy) ? "Yes" : "No");
        free_list(&orig);
        free_list(&copy);
    }

    // 7. Test mergeTwoLists and merge
    {
        printf("7. Merge Sorted Lists:\n");
        node_t *l1 = NULL, *l2 = NULL;
        push(&l1, 5); push(&l1, 3); push(&l1, 1);
        push(&l2, 6); push(&l2, 4); push(&l2, 2);
        printf("   l1: "); print_list(l1);
        printf("   l2: "); print_list(l2);
        
        node_t *merged_rec = mergeTwoLists(l1, l2);
        printf("   Merged (Recursive): "); print_list(merged_rec);
        free_list(&merged_rec);

        l1 = NULL; l2 = NULL;
        push(&l1, 5); push(&l1, 3); push(&l1, 1);
        push(&l2, 6); push(&l2, 4); push(&l2, 2);
        node_t *merged_iter = merge(l1, l2);
        printf("   Merged (Iterative): "); print_list(merged_iter);
        free_list(&merged_iter);
    }

    // 8. Test remove_duplicates_unsorted
    {
        printf("8. Remove Duplicates Unsorted:\n");
        node_t *list = NULL;
        push(&list, 2);
        push(&list, 3);
        push(&list, 2);
        push(&list, 1);
        push(&list, 3);
        printf("   Before: "); print_list(list);
        remove_duplicates_unsorted(list);
        printf("   After:  "); print_list(list);
        free_list(&list);
    }

    // 9. Test rotate_list
    {
        printf("9. Rotate List:\n");
        node_t *list = NULL;
        push(&list, 5); push(&list, 4); push(&list, 3); push(&list, 2); push(&list, 1);
        printf("   Before rotate by 2: "); print_list(list);
        rotate_list(&list, 2);
        printf("   After:              "); print_list(list);
        free_list(&list);
    }

    // 10. Test kth_from_last
    {
        printf("10. K-th From Last:\n");
        node_t *list = NULL;
        push(&list, 5); push(&list, 4); push(&list, 3); push(&list, 2); push(&list, 1);
        print_list(list);
        node_t *node = kth_from_last(list, 2);
        printf("   2nd from last: %d (Expected: 4)\n", node ? node->value : -1);
        free_list(&list);
    }

    // 11. Test remove_middle
    {
        printf("11. Remove Middle:\n");
        node_t *list = NULL;
        push(&list, 5); push(&list, 4); push(&list, 3); push(&list, 2); push(&list, 1);
        printf("   Before: "); print_list(list);
        node_t *mid = remove_middle(list);
        printf("   Removed middle node: %d (Expected: 3)\n", mid ? mid->value : -1);
        printf("   After:  "); print_list(list);
        free(mid);
        free_list(&list);
    }
}

int main () {
    test_basic_ops();
    test_restored_ops();
    return 0;
}
