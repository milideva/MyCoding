#include <stdio.h>
#include <stdlib.h>

/*
  LeetCode 46: Permutations

  Problem Description:
  Given an array `nums` of distinct integers, return all the 
  possible permutations. You can return the answer in any order.

  Algorithm: Backtracking (Swap-based)
  1. Use a recursive function `permute(index)`.
  2. Base Case: If `index == n`, we have a complete permutation.
  3. Recursive Step:
     - For each `i` from `index` to `n-1`:
       - Swap `nums[index]` and `nums[i]`.
       - Recurse for `index + 1`.
       - Backtrack: Swap `nums[index]` and `nums[i]` back to 
         restore original state.

  Complexity Analysis:
  - Time Complexity: O(N * N!)
    Reason: There are N! permutations, and each takes O(N) to print 
    or store.
  - Space Complexity: O(N) for the recursion stack.

  Brute Force comparison:
  - Generate all possible sequences and filter for uniqueness: O(N^N).
  - Backtracking is the standard optimal approach for permutations.
*/

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void backtrack(int nums[], int n, int index) {
    if (index == n) {
        printf("  [ ");
        for (int i = 0; i < n; i++) printf("%d ", nums[i]);
        printf("]\n");
        return;
    }

    for (int i = index; i < n; i++) {
        swap(&nums[index], &nums[i]);
        backtrack(nums, n, index + 1);
        swap(&nums[index], &nums[i]); // Backtrack
    }
}

void test(const char* label, int nums[], int n) {
    printf("Testing %s:\n", label);
    backtrack(nums, n, 0);
}

int main() {
    int a1[] = {1, 2, 3};
    test("Example 1", a1, 3);

    int a2[] = {0, 1};
    test("Example 2", a2, 2);

    return 0;
}
