#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*
  LeetCode 155: Min Stack

  Problem Description:
  Design a stack that supports push, pop, top, and retrieving the 
  minimum element in constant time.
  - `MinStack()`: Initialize the stack.
  - `void push(int val)`: Push element onto stack.
  - `void pop()`: Remove the element on top of the stack.
  - `int top()`: Get the top element.
  - `int getMin()`: Retrieve the minimum element in the stack.

  Algorithm: Two Arrays (Value Stack and Min Stack)
  1. Maintain two arrays (or linked lists): `dataStack` and `minStack`.
  2. `push(val)`:
     - Push `val` to `dataStack`.
     - Push `min(val, current_min)` to `minStack`.
  3. `pop()`: Pop from both stacks.
  4. `getMin()`: Return the top of `minStack`.

  Complexity Analysis:
  - Time Complexity: O(1) for all operations.
  - Space Complexity: O(N) to store values and minimums.
*/

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int min[MAX_SIZE];
    int topIdx;
} MinStack;

MinStack* createMinStack() {
    MinStack* s = (MinStack*)malloc(sizeof(MinStack));
    s->topIdx = -1;
    return s;
}

void push(MinStack* s, int val) {
    if (s->topIdx >= MAX_SIZE - 1) return;
    
    s->topIdx++;
    s->data[s->topIdx] = val;
    
    if (s->topIdx == 0) {
        s->min[s->topIdx] = val;
    } else {
        int currentMin = s->min[s->topIdx - 1];
        s->min[s->topIdx] = (val < currentMin) ? val : currentMin;
    }
}

void pop(MinStack* s) {
    if (s->topIdx >= 0) {
        s->topIdx--;
    }
}

int top(MinStack* s) {
    if (s->topIdx >= 0) return s->data[s->topIdx];
    return -1;
}

int getMin(MinStack* s) {
    if (s->topIdx >= 0) return s->min[s->topIdx];
    return INT_MAX;
}

int main() {
    MinStack* s = createMinStack();
    printf("Pushing: -2, 0, -3\n");
    push(s, -2);
    push(s, 0);
    push(s, -3);

    printf("  getMin(): %d (Expected: -3)\n", getMin(s));
    pop(s);
    printf("  top():    %d (Expected: 0)\n", top(s));
    printf("  getMin(): %d (Expected: -2)\n", getMin(s));

    free(s);
    return 0;
}
