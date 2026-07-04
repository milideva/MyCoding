#include <vector>
#include <iostream>

using namespace std;

/*
  LeetCode 1395: Count Number of Teams

  Problem Description:
  There are `n` soldiers standing in a line. Each soldier is assigned 
  a unique rating value. You have to form a team of 3 soldiers 
  (i, j, k) such that their ratings are either:
  - `rating[i] < rating[j] < rating[k]` OR 
  - `rating[i] > rating[j] > rating[k]`
  where `0 <= i < j < k < n`.

  Return the number of teams you can form.

  Algorithm: Greedy/Counting with Fixed Middle Element
  1. For each soldier `j`, treat them as the middle element of the team.
  2. Count how many soldiers to their left (`i < j`) have ratings 
     smaller (`leftLess`) or larger (`leftGreater`) than `rating[j]`.
  3. Count how many soldiers to their right (`k > j`) have ratings 
     smaller (`rightLess`) or larger (`rightGreater`) than `rating[j]`.
  4. The number of increasing teams with `j` as middle is `leftLess * rightGreater`.
  5. The number of decreasing teams with `j` as middle is `leftGreater * rightLess`.
  6. Sum these products for all possible `j`.

  Complexity Analysis:
  - Time Complexity: O(N^2)
    Reason: We iterate through every element `j`, and for each `j`, 
    we perform two linear scans (left and right).
  - Space Complexity: O(1) auxiliary space.

  Alternative Approaches (Fenwick Tree / Segment Tree):
  - Logic: Use a BIT to count elements smaller/larger in O(log N).
  - Time Complexity: O(N log N).
  - Comparison: O(N^2) is acceptable for N=1000, but O(N log N) is 
    needed for larger N.

  Brute Force comparison:
  - Check all possible triplets (i, j, k).
  - Time Complexity: O(N^3).
  - The middle-element counting approach reduces this to quadratic time.
*/

class Solution {
public:
    int numTeams(vector<int>& rating) {
        int n = rating.size();
        if (n < 3) return 0;
        int totalTeams = 0;

        for (int j = 1; j < n - 1; ++j) {
            int leftLess = 0, leftGreater = 0;
            int rightLess = 0, rightGreater = 0;

            // 1. Count elements to the left
            for (int i = 0; i < j; ++i) {
                if (rating[i] < rating[j]) leftLess++;
                else leftGreater++;
            }

            // 2. Count elements to the right
            for (int k = j + 1; k < n; ++k) {
                if (rating[k] < rating[j]) rightLess++;
                else rightGreater++;
            }

            // 3. Combine counts
            totalTeams += (leftLess * rightGreater) + (leftGreater * rightLess);
        }
        return totalTeams;
    }
};

void test(const string& label, vector<int> rating, int expected) {
    cout << "Testing: " << label << endl;
    Solution sol;
    int result = sol.numTeams(rating);
    if (result == expected) {
        cout << "  [PASS] Teams: " << result << endl;
    } else {
        cout << "  [FAIL] Result: " << result << " (Expected: " << expected << ")" << endl;
    }
}

int main() {
    test("Example 1", {2, 5, 3, 4, 1}, 3);
    test("Example 2", {2, 1, 3}, 0);
    test("Example 3", {1, 2, 3, 4}, 4);
    return 0;
}
