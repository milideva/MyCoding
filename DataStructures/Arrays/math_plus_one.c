#include <stdio.h>
#include <stdlib.h>

/*
  LeetCode 66: Plus One

  Problem Description:
  You are given a large integer represented as an integer array 
  `digits`, where each `digits[i]` is the i-th digit of the integer. 
  The digits are ordered from most significant to least significant 
  in left-to-right order. The large integer does not contain any 
  leading 0's, except the number 0 itself.

  Increment the large integer by one and return the resulting array 
  of digits.

  Example 1:
  Input: digits = [1,2,3]
  Output: [1,2,4]

  Algorithm: Backward Carry Propagation
  1. Iterate through the array from right to left.
  2. Increment the current digit.
  3. If the digit becomes 10, set it to 0 and continue to the next digit 
     (carry).
  4. If the digit is less than 10, we are done; return the array.
  5. If the loop finishes and we still have a carry (e.g., [9,9,9]), 
     create a new array of size `n+1` with the first element set to 1.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: We traverse the array at most once.
  - Space Complexity: O(N) if we need to return a new array (for carry 
    overflow), otherwise O(1) in-place.
*/

int* plusOne(int* digits, int digitsSize, int* returnSize) {
    for (int i = digitsSize - 1; i >= 0; i--) {
        if (digits[i] < 9) {
            digits[i]++;
            *returnSize = digitsSize;
            return digits;
        }
        digits[i] = 0;
    }

    // Handle overflow (e.g., 999 -> 1000)
    *returnSize = digitsSize + 1;
    int* res = (int*)malloc((*returnSize) * sizeof(int));
    res[0] = 1;
    for (int i = 1; i < *returnSize; i++) {
        res[i] = 0;
    }
    return res;
}

void test(const char* label, int digits[], int size) {
    printf("Testing: %s\n", label);
    int returnSize;
    int* result = plusOne(digits, size, &returnSize);

    printf("  Result: ");
    for (int i = 0; i < returnSize; i++) printf("%d ", result[i]);
    printf("\n");

    if (result != digits) free(result);
}

int main() {
    int d1[] = {1, 2, 3};
    test("Example 1", d1, 3);

    int d2[] = {4, 3, 2, 1};
    test("Example 2", d2, 4);

    int d3[] = {9, 9, 9};
    test("Overflow Case", d3, 3);

    int d4[] = {0};
    test("Single Zero", d4, 1);

    return 0;
}
