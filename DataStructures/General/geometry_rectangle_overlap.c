/**
 * Problem: Rectangle Overlap
 * Given two axis-aligned rectangles, check if they overlap.
 * Rectangles are defined by their top-left (L) and bottom-right (R) coordinates.
 * 
 * Strategy: Check for non-overlap conditions
 * Assuming screen coordinates where Y increases downwards (L.y < R.y).
 * Two rectangles do NOT overlap if:
 * 1. One rectangle is completely to the left of the other.
 * 2. One rectangle is completely to the right of the other.
 * 3. One rectangle is completely above the other.
 * 4. One rectangle is completely below the other.
 * 
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int x, y;
} Point;

/**
 * Checks if two rectangles overlap.
 * L1: Top-Left of first rectangle
 * R1: Bottom-Right of first rectangle
 * L2: Top-Left of second rectangle
 * R2: Bottom-Right of second rectangle
 */
bool doOverlap(Point L1, Point R1, Point L2, Point R2) {
    // If one rectangle is to the left of the other
    if (L1.x >= R2.x || L2.x >= R1.x) {
        return false;
    }

    // If one rectangle is above the other (Y increases downwards)
    if (L1.y >= R2.y || L2.y >= R1.y) {
        return false;
    }

    return true;
}

int main() {
    // Case 1: Overlapping
    Point l1 = {0, 0}, r1 = {10, 10};
    Point l2 = {5, 5}, r2 = {15, 15};

    printf("Rectangles (0,0)-(10,10) and (5,5)-(15,15): %s\n", 
           doOverlap(l1, r1, l2, r2) ? "Overlap" : "Don't Overlap");

    // Case 2: Not Overlapping (separate)
    Point l3 = {0, 0}, r3 = {10, 10};
    Point l4 = {11, 11}, r4 = {20, 20};

    printf("Rectangles (0,0)-(10,10) and (11,11)-(20,20): %s\n", 
           doOverlap(l3, r3, l4, r4) ? "Overlap" : "Don't Overlap");

    // Case 3: Just touching (should return false based on >=)
    Point l5 = {0, 0}, r5 = {10, 10};
    Point l6 = {10, 10}, r6 = {20, 20};

    printf("Rectangles (0,0)-(10,10) and (10,10)-(20,20): %s\n", 
           doOverlap(l5, r5, l6, r6) ? "Overlap" : "Don't Overlap");

    return 0;
}
