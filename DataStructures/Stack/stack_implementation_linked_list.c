#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
  Problem: Stack Implementation using Linked List

  Description:
  Implement a LIFO (Last-In, First-Out) stack data structure using 
  a singly linked list in C.

  Algorithm:
  - Push: Insert a new node at the head of the list (top of stack).
  - Pop: Remove the node from the head of the list.
  - Peek: Return the value at the head of the list.

  Complexity Analysis:
  - Push: O(1)
  - Pop: O(1)
  - Peek: O(1)
  - Space Complexity: O(N) where N is the number of elements.
*/

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
} Stack;

Stack* createStack() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}

bool isEmpty(Stack* s) {
    return s->top == NULL;
}

void push(Stack* s, int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = val;
    newNode->next = s->top;
    s->top = newNode;
}

int pop(Stack* s) {
    if (isEmpty(s)) return -1;
    Node* temp = s->top;
    int val = temp->data;
    s->top = temp->next;
    free(temp);
    return val;
}

void freeStack(Stack* s) {
    while (!isEmpty(s)) pop(s);
    free(s);
}

int main() {
    Stack* s = createStack();
    printf("Pushing: 10, 20, 30\n");
    push(s, 10);
    push(s, 20);
    push(s, 30);

    printf("Popped: %d\n", pop(s));
    printf("Popped: %d\n", pop(s));
    
    freeStack(s);
    return 0;
}
