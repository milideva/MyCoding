#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/* 
  LeetCode 1167: Minimum Cost to Connect Sticks

  Problem Description:
  You have some number of sticks with positive integer lengths. These 
  lengths are given as an array sticks, where sticks[i] is the length 
  of the ith stick.

  You can connect any two sticks of lengths x and y into one stick by 
  paying a cost of x + y. You must connect all the sticks until there 
  is only one stick remaining.

  Return the minimum cost of connecting all the given sticks into one 
  stick in this way.

  Algorithm: Greedy with Min-Heap
  1. To minimize the total cost, we should always pick the two shortest 
     sticks available.
  2. Use a Min-Heap to store all stick lengths.
  3. While more than one stick remains:
     - Pop the two smallest sticks (s1, s2).
     - The cost to connect them is `s1 + s2`.
     - Add this to the total cost.
     - Push the combined stick (`s1 + s2`) back into the Min-Heap.
  4. Repeat until only one stick remains.

  Complexity Analysis:
  - Time Complexity: O(N log N)
    Reason: Building the heap takes O(N). We then perform N-1 connections, 
    each involving heap pops and a push, taking O(log N).
  - Space Complexity: O(N) to store the sticks in the heap.

  Alternative Approaches:
  - Sorting: If we sort the array once, we still need to keep the 
    combined sticks sorted. Re-sorting after every connection would 
    be O(N^2 log N), which is inefficient.

  Brute Force comparison:
  - Try all possible pairs of sticks to connect. This is a permutation 
    problem with exponential complexity. The greedy approach using a 
    Min-Heap provides the optimal solution in polynomial time.
*/

class Solution {
public:
    int connectSticks(vector<int>& sticks) {
        priority_queue<int, vector<int>, greater<int>> pq(begin(sticks), end(sticks));
        int totalCost = 0;
        
        while (pq.size() > 1) {
            int s1 = pq.top(); pq.pop();
            int s2 = pq.top(); pq.pop();
            int currentCost = s1 + s2;
            totalCost += currentCost;
            pq.push(currentCost);
        }
        return totalCost;
    }
};

void test(const string& label, vector<int> sticks, int expected) {
    cout << "Testing: " << label << endl;
    Solution sol;
    int result = sol.connectSticks(sticks);
    cout << "  Result: " << result << " (Expected: " << expected << ")" << endl;
}

int main() {
    test("Example 1", {1, 8, 3, 5}, 30);
    test("Example 2", {2, 4, 3}, 14);
    test("Single Stick", {5}, 0);
    return 0;
}
