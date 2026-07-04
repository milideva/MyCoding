#include <stdio.h>
#include <stdbool.h>

/*
  Problem: Lucky Numbers

  Problem Description:
  Lucky numbers are a subset of integers. To arrive at lucky numbers:
  1. Take the set of integers starting from 1.
  2. In the first step, delete every 2nd number.
  3. In the second step, delete every 3rd number from the remaining set.
  4. Continue this process, deleting every k-th number where k 
     increments in each step.
  Any number that never gets deleted is called a Lucky Number.

  Algorithm: Recursive Deletion Simulation
  1. Recursive function `isLucky(n, counter)`.
  2. In each step, if `counter > n`, then `n` will never be deleted. 
     Return true.
  3. If `n % counter == 0`, `n` is deleted in this step. Return false.
  4. Recurse for the new position of `n` in the reduced set: 
     `n = n - (n / counter)`.
  5. Increment `counter` for the next step.

  Complexity Analysis:
  - Time Complexity: O(sqrt(N))
    Reason: The number of steps is approximately the value of the 
    largest `counter` which is around sqrt(N).
  - Space Complexity: O(sqrt(N)) for recursion stack.
*/

bool isLucky(int n, int counter) {
    if (counter > n) return true;
    if (n % counter == 0) return false;

    // Calculate new position
    int next_n = n - (n / counter);
    return isLucky(next_n, counter + 1);
}

void test(int n) {
    printf("Number: %d -> Lucky: %s\n", n, isLucky(n, 2) ? "Yes" : "No");
}

int main() {
    test(1);  // Yes
    test(3);  // Yes
    test(7);  // Yes
    test(13); // Yes
    test(19); // Yes
    test(5);  // No
    return 0;
}
