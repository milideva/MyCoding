#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

/*
  LeetCode 692: Top K Frequent Words

  Problem Description:
  Given an array of strings `words` and an integer `k`, return the 
  `k` most frequent strings.
  Return the answer sorted by frequency from highest to lowest. 
  Words with the same frequency should be sorted by their 
  lexicographical order (ascending).

  Algorithm: Hash Map + Min-Heap
  1. Count frequencies using an `unordered_map<string, int>`.
  2. Use a Min-Heap of size `k` to keep track of the top `k` elements.
  3. Custom Comparator for Min-Heap:
     - If frequencies are different, the smaller frequency has 
       higher priority (to be popped).
     - If frequencies are equal, the lexicographically larger 
       word has higher priority (to be popped).
  4. After processing all words, the heap contains the `k` most 
     frequent words.
  5. Pop elements and reverse the result.

  Complexity Analysis:
  - Time Complexity: O(N log K)
    Reason: We iterate through N words to count, then perform N 
    heap operations of size K.
  - Space Complexity: O(N) to store word frequencies in the map.
*/

struct Comp {
    bool operator()(const pair<int, string>& a, const pair<int, string>& b) {
        if (a.first != b.first) {
            return a.first > b.first; // Min-heap by frequency
        }
        return a.second < b.second; // Max-heap by string (lexicographically)
        // Why? In a min-heap of size K, we want to pop the "worst" 
        // among the top K. The worst is the lowest frequency or 
        // lexicographically largest string among equals.
    }
};

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> freq;
        for (const string& w : words) freq[w]++;

        // Min-heap to keep top K
        // pair is {count, word}
        priority_queue<pair<int, string>, vector<pair<int, string>>, Comp> pq;

        for (auto const& [word, count] : freq) {
            pq.push({count, word});
            if (pq.size() > k) {
                pq.pop();
            }
        }

        vector<string> result;
        while (!pq.empty()) {
            result.push_back(pq.top().second);
            pq.pop();
        }
        reverse(result.begin(), result.end());
        return result;
    }
};

void test(vector<string> words, int k) {
    cout << "Testing Top K Frequent Words (k=" << k << ")" << endl;
    Solution sol;
    vector<string> result = sol.topKFrequent(words, k);
    cout << "  Result: [ ";
    for (const string& s : result) cout << "\"" << s << "\" ";
    cout << "]" << endl;
}

int main() {
    test({"i", "love", "leetcode", "i", "love", "coding"}, 2);
    test({"the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"}, 4);
    return 0;
}
