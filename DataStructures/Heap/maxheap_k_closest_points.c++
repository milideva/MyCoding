#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

/*
  LeetCode 973: K Closest Points to Origin

  Problem Description:
  Given an array of points where points[i] = [xi, yi] represents a point 
  on the X-Y plane and an integer k, return the k closest points to the 
  origin (0, 0).

  The distance between two points on the X-Y plane is the Euclidean 
  distance (i.e., √(x1 - x2)^2 + (y1 - y2)^2).

  You may return the answer in any order. The answer is guaranteed to 
  be unique (except for the order that it is in).

  Algorithm: Max-Heap of size K
  1. We want the K points with the SMALLEST distances.
  2. Use a Max-Heap to store the current closest K points. 
  3. For each point:
     - Calculate its squared distance to the origin.
     - Push to the max-heap.
     - If heap size exceeds K, pop the largest distance.
  4. At the end, the heap contains the K closest points.

  Complexity Analysis:
  - Time Complexity: O(N log K)
    Reason: We iterate through N points, and each heap push/pop takes O(log K).
  - Space Complexity: O(K)
    Reason: To store K points in the max-heap.

  Comparison:
  - QuickSelect (Hoare's Selection Algorithm):
    - Average Time: O(N), Worst Case: O(N^2).
    - Best for very large N where O(N log K) might be slightly slower.
  - Sorting:
    - Time: O(N log N).
    - Comparison: The Max-Heap approach is better when K is significantly 
      smaller than N.
*/

struct Point {
    int x, y;
    long dist;
    Point(int _x, int _y) : x(_x), y(_y), dist(1L * _x * _x + 1L * _y * _y) {}

    // Max-Heap needs 'less' to return true if p1 is 'smaller' than p2.
    // We want the point with the LARGEST distance at the top.
    bool operator<(const Point& other) const {
        return dist < other.dist;
    }
};

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        priority_queue<Point> maxHeap;

        for (const auto& p : points) {
            maxHeap.emplace(p[0], p[1]);
            if (maxHeap.size() > k) {
                maxHeap.pop();
            }
        }

        vector<vector<int>> result;
        while (!maxHeap.empty()) {
            Point p = maxHeap.top();
            maxHeap.pop();
            result.push_back({p.x, p.y});
        }
        return result;
    }
};

void test(const string& label, vector<vector<int>> points, int k, const vector<vector<int>>& expected) {
    cout << "Testing: " << label << endl;
    Solution sol;
    vector<vector<int>> result = sol.kClosest(points, k);
    
    // Sort results and expected for comparison (since order doesn't matter)
    auto cmp = [](const vector<int>& a, const vector<int>& b) {
        return (a[0]*a[0] + a[1]*a[1]) < (b[0]*b[0] + b[1]*b[1]);
    };
    sort(result.begin(), result.end(), cmp);
    
    cout << "  Result: ";
    for (const auto& p : result) cout << "[" << p[0] << "," << p[1] << "] ";
    cout << endl;
}

int main() {
    test("Example 1", {{1,3}, {-2,2}}, 1, {{-2,2}});
    test("Example 2", {{3,3}, {5,-1}, {-2,4}}, 2, {{3,3}, {-2,4}});
    return 0;
}
