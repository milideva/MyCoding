/**
 * Problem: Check if four points form a rectangle.
 * Given four points in a 2D plane, determine if they form a rectangle.
 * 
 * Strategy: Distance-based properties
 * A rectangle has:
 * 1. Two equal shorter sides.
 * 2. Two equal longer sides.
 * 3. Two equal diagonals.
 * If we calculate the distance between every pair of points (6 pairs total), 
 * we should get exactly 3 distinct values (unless it's a square, then 2).
 * 
 * Time Complexity: O(1) - Always 4 points.
 * Space Complexity: O(1).
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

struct Point {
    int x, y;
};

/**
 * Calculates the squared Euclidean distance between two points.
 * Using squared distance avoids unnecessary sqrt() and precision issues.
 */
long long distSq(Point p1, Point p2) {
    return (long long)(p1.x - p2.x) * (p1.x - p2.x) + 
           (long long)(p1.y - p2.y) * (p1.y - p2.y);
}

/**
 * Checks if four points form a rectangle.
 */
bool isRectangle(Point p1, Point p2, Point p3, Point p4) {
    set<long long> distances;
    Point pts[] = {p1, p2, p3, p4};

    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            long long d = distSq(pts[i], pts[j]);
            if (d == 0) return false; // Points are not distinct
            distances.insert(d);
        }
    }

    // For a rectangle, there are only 3 possible distances: side1, side2, and diagonal.
    // For a square, there are only 2 possible distances: side and diagonal.
    return (distances.size() == 2 || distances.size() == 3);
}

int main() {
    Point p1 = {0, 0}, p2 = {5, 0}, p3 = {0, 3}, p4 = {5, 3};
    Point p5 = {0, 0}, p6 = {5, 0}, p7 = {0, 3}, p8 = {5, 2}; // Not a rectangle

    cout << "Points {0,0}, {5,0}, {0,3}, {5,3} form a rectangle: " 
         << (isRectangle(p1, p2, p3, p4) ? "Yes" : "No") << endl;
    cout << "Points {0,0}, {5,0}, {0,3}, {5,2} form a rectangle: " 
         << (isRectangle(p5, p6, p7, p8) ? "Yes" : "No") << endl;

    return 0;
}
