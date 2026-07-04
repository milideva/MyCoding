/**
 * Problem: Two Sum
 * Given an array of integers and a target sum, find if there are two numbers 
 * such that they add up to the target.
 * 
 * Strategy: Sorting + Two Pointers
 * 1. Sort the array.
 * 2. Use two pointers (left and right).
 * 3. If sum is target, found.
 * 4. If sum < target, increment left.
 * 5. If sum > target, decrement right.
 * 
 * Time Complexity: O(N log N) for sorting, O(N) for search. Total O(N log N).
 * Space Complexity: O(1) or O(N) depending on the sorting algorithm used.
 * 
 * Note: A real hash map would give O(N) time and O(N) space.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Comparator for qsort.
 */
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

/**
 * Checks if two numbers in the array sum up to the target.
 */
bool hasTwoSum(int arr[], int size, int target) {
    // Sort the array first
    qsort(arr, size, sizeof(int), compare);

    int left = 0;
    int right = size - 1;

    while (left < right) {
        int currentSum = arr[left] + arr[right];
        if (currentSum == target) {
            printf("Found: %d + %d = %d\n", arr[left], arr[right], target);
            return true;
        } else if (currentSum < target) {
            left++;
        } else {
            right--;
        }
    }

    return false;
}

int main() {
    int nums[] = {4, 3, 34, 5, 14, 1, 13, 7};
    int size = sizeof(nums) / sizeof(nums[0]);
    int target = 18;

    printf("Array: ");
    for (int i = 0; i < size; i++) printf("%d ", nums[i]);
    printf("\nTarget: %d\n", target);

    if (hasTwoSum(nums, size, target)) {
        printf("Two Sum exists.\n");
    } else {
        printf("Two Sum does not exist.\n");
    }

    return 0;
}
