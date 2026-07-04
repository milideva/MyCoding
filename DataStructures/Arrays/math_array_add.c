#include <stdio.h>
#include <stdlib.h>

/*
  Problem: Add Two Numbers Represented by Arrays

  Problem Description:
  Given two arrays representing two non-negative integers, add them 
  and return the result as a new array. Most significant digit is 
  at index 0.

  Example:
  arr1 = [3, 4, 5], arr2 = [1, 2, 3, 4, 5]
  Result: [1, 2, 6, 9, 0] (345 + 12345 = 12690)

  Algorithm: Digit-by-Digit Addition
  1. Determine the sizes of the two arrays.
  2. Iterate from the last index (least significant digit) of both 
     arrays.
  3. Perform addition with carry propagation.
  4. Store results in a new array.
  5. Handle cases where the result has more digits than both 
     inputs (e.g., 99 + 1 = 100).

  Complexity Analysis:
  - Time Complexity: O(max(N, M))
    Reason: We traverse both arrays once.
  - Space Complexity: O(max(N, M)) to store the result.
*/

int* addArrays(int arr1[], int n1, int arr2[], int n2, int* resSize) {
    int maxSz = (n1 > n2) ? n1 : n2;
    int* res = (int*)malloc((maxSz + 1) * sizeof(int));
    int carry = 0;
    int i = n1 - 1, j = n2 - 1, k = maxSz;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry + (i >= 0 ? arr1[i--] : 0) + (j >= 0 ? arr2[j--] : 0);
        res[k--] = sum % 10;
        carry = sum / 10;
    }

    // k points to the index before the first digit of the result
    int start = k + 1;
    *resSize = maxSz + 1 - start;
    
    // Shift elements to the front if necessary
    if (start > 0) {
        for (int m = 0; m < *resSize; m++) {
            res[m] = res[start + m];
        }
    }
    return res;
}

void test(const char* label, int a1[], int n1, int a2[], int n2) {
    printf("Testing: %s\n", label);
    int resSize;
    int* res = addArrays(a1, n1, a2, n2, &resSize);
    printf("  Result: ");
    for (int i = 0; i < resSize; i++) printf("%d ", res[i]);
    printf("\n");
    free(res);
}

int main() {
    int a1[] = {3, 4, 5};
    int a2[] = {1, 2, 3, 4, 5};
    test("Example 1", a1, 3, a2, 5);

    int a3[] = {9, 9, 9};
    int a4[] = {1};
    test("Carry Overflow", a3, 3, a4, 1);

    return 0;
}
