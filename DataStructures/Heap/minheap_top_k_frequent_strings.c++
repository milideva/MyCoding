#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

/*
  LeetCode 692: Top K Frequent Words

  Problem Description:
  Given an array of strings `words` and an integer `k`, return the `k` 
  most frequent strings.

  Return the answer sorted by the frequency from highest to lowest. 
  Sort the words with the same frequency by their lexicographical 
  order.

  Example 1:
  Input: ["i", "love", "leetcode", "i", "love", "coding"], k = 2
  Output: ["i", "love"]

  Example 2:
  Input: ["the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"], k = 4
  Output: ["the", "is", "sunny", "day"]

  Algorithm: Min-Heap of size K
  1. Count the frequency of each word using a hash map.
  2. Use a Min-Heap to store pairs of `(frequency, word)`.
  3. Custom Comparator for Min-Heap:
     - If frequencies are different, prioritize the smaller frequency 
       (to pop it out).
     - If frequencies are the same, prioritize the lexicographically 
       larger word (to pop it out).
  4. Iterate through the hash map, keeping only the top `k` elements 
     in the heap.
  5. Collect result and reverse it (since it's a min-heap).

  Complexity Analysis:
  - Time Complexity: O(N log K)
    Reason: Counting frequencies takes O(N). Heap operations for unique 
    words (up to N) take O(N log K).
  - Space Complexity: O(N)
    Reason: Hash map stores all unique words.

  Comparison:
  - Sorting: Sort all unique words by frequency and then lexicographically.
    - Time Complexity: O(U log U) where U is unique words.
    - Comparison: Min-Heap is more efficient when K << U.
*/

struct WordCompare {
    bool operator()(const pair<int, string>& a, const pair<int, string>& b) {
        if (a.first != b.second.size()) { // Wait, error in logic below
            // Correction:
        }
        // If frequency is same, larger string stays at top to be popped (min-heap logic for alphabetical order)
        if (a.first == b.first) {
            return a.second < b.second;
        }
        // Smaller frequency stays at top to be popped
        return a.first > b.first;
    }
};

class Solution {
    struct Comp {
        bool operator()(const pair<int, string>& a, const pair<int, string>& b) {
            if (a.first == b.first) return a.second < b.second;
            return a.first > b.first;
        }
    };

public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> counts;
        for (const string& w : words) counts[w]++;

        priority_queue<pair<int, string>, vector<pair<int, string>>, Comp> minHeap;

        for (auto const& [word, freq] : counts) {
            minHeap.push({freq, word});
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }

        vector<string> result;
        while (!minHeap.empty()) {
            result.push_back(minHeap.top().second);
            minHeap.pop();
        }
        reverse(result.begin(), result.end());
        return result;
    }
};

void test(const string& label, vector<string> words, int k, vector<string> expected) {
    cout << "Testing: " << label << endl;
    Solution sol;
    vector<string> result = sol.topKFrequent(words, k);
    
    if (result == expected) {
        cout << "  [PASS]" << endl;
    } else {
        cout << "  [FAIL] Result: ";
        for (const string& s : result) cout << s << " ";
        cout << endl;
    }
}

int main() {
    test("Example 1", {"i", "love", "leetcode", "i", "love", "coding"}, 2, {"i", "love"});
    test("Example 2", {"the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"}, 4, {"the", "is", "sunny", "day"});
    return 0;
}
