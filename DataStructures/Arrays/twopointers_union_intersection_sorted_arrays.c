#include <stdio.h>
#include <stdlib.h>

/*
  Problem: Union and Intersection of Two Sorted Arrays

  Problem Description:
  Given two sorted arrays, find their union and intersection.
  - Union: Elements present in either of the arrays.
  - Intersection: Elements present in both arrays.
  Input arrays are distinct. Output can be in any order.

  Example:
  arr1 = [1, 3, 4, 5, 7], arr2 = [2, 3, 5, 6]
  Union: [1, 2, 3, 4, 5, 6, 7]
  Intersection: [3, 5]

  Algorithm: Two Pointers (Linear Merge)
  1. Initialize two pointers `i = 0` and `j = 0`.
  2. Intersection:
     - If `arr1[i] == arr2[j]`, add to result, `i++`, `j++`.
     - Else if `arr1[i] < arr2[j]`, `i++`.
     - Else, `j++`.
  3. Union:
     - If `arr1[i] < arr2[j]`, add `arr1[i]`, `i++`.
     - Else if `arr1[i] > arr2[j]`, add `arr2[j]`, `j++`.
     - Else (`arr1[i] == arr2[j]`), add one of them, `i++`, `j++`.
     - After the loop, add remaining elements from either array.

  Complexity Analysis:
  - Time Complexity: O(N + M)
    Reason: We traverse both arrays exactly once.
  - Space Complexity: O(1) auxiliary space (excluding results).

  Brute Force comparison:
  - Use a hash set for union and intersection.
  - Time: O(N + M), Space: O(N + M).
  - The two-pointer approach is more space-efficient as it leverages 
    the sorted property.
*/

void printIntersection(int arr1[], int n1, int arr2[], int n2) {
    int i = 0, j = 0;
    printf("Intersection: [ ");
    while (i < n1 && j < n2) {
        if (arr1[i] < arr2[j]) i++;
        else if (arr2[j] < arr1[i]) j++;
        else {
            printf("%d ", arr1[i++]);
            j++;
        }
    }
    printf("]\n");
}

void printUnion(int arr1[], int n1, int arr2[], int n2) {
    int i = 0, j = 0;
    printf("Union: [ ");
    while (i < n1 && j < n2) {
        if (arr1[i] < arr2[j]) printf("%d ", arr1[i++]);
        else if (arr2[j] < arr1[i]) printf("%d ", arr2[j++]);
        else {
            printf("%d ", arr1[i++]);
            j++;
        }
    }
    while (i < n1) printf("%d ", arr1[i++]);
    while (j < n2) printf("%d ", arr2[j++]);
    printf("]\n");
}

int main() {
    int arr1[] = {10, 20, 30, 40, 50};
    int arr2[] = {5, 15, 20, 40, 60, 80};
    int n1 = 5, n2 = 6;

    printf("Array 1: "); for(int i=0; i<n1; i++) printf("%d ", arr1[i]); printf("\n");
    printf("Array 2: "); for(int i=0; i<n2; i++) printf("%d ", arr2[i]); printf("\n");

    printIntersection(arr1, n1, arr2, n2);
    printUnion(arr1, n1, arr2, n2);

    return 0;
}
