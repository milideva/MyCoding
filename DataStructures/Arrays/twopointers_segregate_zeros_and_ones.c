#include <stdio.h>

/*
  Problem: Segregate Zeros and Ones

  Problem Description:
  Given an array containing only 0s and 1s, segregate them such that 
  all 0s are on the left and all 1s are on the right. The task should 
  be completed in a single pass.

  Algorithm: Two Pointers (Left and Right)
  1. Initialize two pointers: `left = 0` and `right = n - 1`.
  2. While `left < right`:
     - While `arr[left] == 0` and `left < right`, increment `left`.
     - While `arr[right] == 1` and `left < right`, decrement `right`.
     - If `left < right`, swap `arr[left]` and `arr[right]`, then 
       increment `left` and decrement `right`.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: Each element is visited at most once.
  - Space Complexity: O(1) auxiliary space.

  Brute Force comparison:
  - Counting: Count 0s and 1s, then overwrite the array.
    - Time: O(N), but two passes.
  - Sorting: Standard sort.
    - Time: O(N log N).
  - The two-pointer approach is a single-pass O(N) solution.
*/

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void segregateZerosAndOnes(int arr[], int n) {
    int left = 0, right = n - 1;
    while (left < right) {
        while (arr[left] == 0 && left < right) left++;
        while (arr[right] == 1 && left < right) right--;
        
        if (left < right) {
            swap(&arr[left], &arr[right]);
            left++;
            right--;
        }
    }
}

void test(const char* label, int arr[], int n) {
    printf("Testing: %s\n", label);
    segregateZerosAndOnes(arr, n);
    printf("  Result: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr1[] = {0, 1, 0, 1, 1, 1};
    test("Example 1", arr1, 6);

    int arr2[] = {1, 1, 0, 0, 0};
    test("Example 2", arr2, 5);

    int arr3[] = {0, 0, 0};
    test("All Zeros", arr3, 3);

    return 0;
}
