#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
  LeetCode 349: Intersection of Two Arrays

  Problem Description:
  Given two integer arrays `nums1` and `nums2`, return an array of 
  their intersection. Each element in the result must be unique and 
  you may return the result in any order.

  Example 1:
  Input: nums1 = [1,2,2,1], nums2 = [2,2]
  Output: [2]

  Algorithm: Sorting + Binary Search (Space-efficient)
  1. Sort the smaller array (`nums1`).
  2. For each element in the larger array (`nums2`):
     - Binary search for it in the sorted `nums1`.
     - If found, add it to the result array if not already present.
  3. This avoids the O(N) auxiliary space needed for a hash set.

  Complexity Analysis:
  - Time Complexity: O(N log N + M log N)
    Reason: N log N to sort, then M searches each taking log N.
  - Space Complexity: O(1) beyond sorting overhead and the result array.

  Brute Force comparison:
  - Linear scan for every element: O(N * M).
  - Using a hash set: O(N + M) time and O(N) space.
  - Sorting + Binary search is a good trade-off if space is a constraint.
*/

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

bool binarySearch(int arr[], int size, int target) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return true;
        if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return false;
}

int* intersection(int* nums1, int n1, int* nums2, int n2, int* returnSize) {
    qsort(nums1, n1, sizeof(int), compare);
    
    int* res = (int*)malloc(sizeof(int) * (n1 < n2 ? n1 : n2));
    int count = 0;

    for (int i = 0; i < n2; i++) {
        // Skip duplicates in nums2 to optimize (if nums2 was sorted)
        // Here we just check if it's in nums1 and not already in res
        if (binarySearch(nums1, n1, nums2[i])) {
            bool alreadyAdded = false;
            for (int k = 0; k < count; k++) {
                if (res[k] == nums2[i]) {
                    alreadyAdded = true;
                    break;
                }
            }
            if (!alreadyAdded) res[count++] = nums2[i];
        }
    }
    *returnSize = count;
    return res;
}

void test(const char* label, int n1[], int s1, int n2[], int s2) {
    printf("Testing: %s\n", label);
    int returnSize;
    int* res = intersection(n1, s1, n2, s2, &returnSize);
    printf("  Result: [ ");
    for (int i = 0; i < returnSize; i++) printf("%d ", res[i]);
    printf("]\n");
    free(res);
}

int main() {
    int n1[] = {1, 2, 2, 1}, n2[] = {2, 2};
    test("Example 1", n1, 4, n2, 2);

    int n3[] = {4, 9, 5}, n4[] = {9, 4, 9, 8, 4};
    test("Example 2", n3, 3, n4, 5);

    return 0;
}
