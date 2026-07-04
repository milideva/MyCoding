#include <iostream>

using namespace std;

/*
  LeetCode 278: First Bad Version

  Problem Description:
  Suppose you have `n` versions `[1, 2, ..., n]` and you want to 
  find out the first bad one. You are given an API 
  `bool isBadVersion(version)` which returns whether a version 
  is bad. All versions after a bad version are also bad. 
  Minimize the number of calls to the API.

  Algorithm: Binary Search
  1. Initialize `left = 1` and `right = n`.
  2. While `left < right`:
     - Calculate `mid = left + (right - left) / 2`.
     - If `isBadVersion(mid)` is true:
       - The first bad version could be `mid` or before it. 
       - Set `right = mid`.
     - Else:
       - The first bad version must be after `mid`.
       - Set `left = mid + 1`.
  3. Return `left`.

  Complexity Analysis:
  - Time Complexity: O(log N)
    Reason: We halve the search space at each step.
  - Space Complexity: O(1) auxiliary space.
*/

class Solution {
    int firstBadVer;

public:
    Solution(int bad) : firstBadVer(bad) {}

    bool isBadVersion(int version) {
        return version >= firstBadVer;
    }

    int findFirstBadVersion(int n) {
        int left = 1, right = n;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (isBadVersion(mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
};

void test(int n, int bad) {
    cout << "Testing: Total Versions=" << n << ", First Bad=" << bad << endl;
    Solution sol(bad);
    int result = sol.findFirstBadVersion(n);
    if (result == bad) {
        cout << "  [PASS] Found: " << result << endl;
    } else {
        cout << "  [FAIL] Result: " << result << " (Expected: " << bad << ")" << endl;
    }
}

int main() {
    test(5, 4);
    test(1, 1);
    test(100, 37);
    return 0;
}
