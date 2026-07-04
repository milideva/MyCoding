#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

/*
  Problem: Range Sum Query with Square Root Decomposition

  Problem Description:
  Given an array of integers, implement a data structure that supports 
  two operations:
  - `update(index, val)`: Update the element at the given index.
  - `query(left, right)`: Return the sum of elements in the range [left, right].

  Algorithm: Square Root Decomposition
  1. Divide the array into blocks of size approximately `sqrt(N)`.
  2. Maintain an auxiliary array `blocks` where `blocks[i]` stores the 
     sum of the i-th block.
  3. Preprocessing: Iterate through the array once to populate `blocks`. 
     Takes O(N).
  4. Update (O(1)):
     - Calculate the block index.
     - Update the block sum by adding the difference: 
       `blocks[b_idx] += (new_val - old_val)`.
  5. Query (O(sqrt N)):
     - For the range [L, R]:
       - Sum individual elements in the starting partial block.
       - Sum entire blocks in the middle.
       - Sum individual elements in the ending partial block.
  
  Complexity Analysis:
  - Preprocessing: O(N)
  - Update: O(1)
  - Query: O(sqrt N)
  - Space Complexity: O(N) for array + O(sqrt N) for blocks.

  Brute Force comparison:
  - Query: O(N), Update: O(1).
  - Square root decomposition balances these costs, making it efficient 
    for scenarios with frequent queries.
*/

class SqrtDecomposition {
    vector<int> arr;
    vector<long long> blocks;
    int blockSize;

public:
    SqrtDecomposition(const vector<int>& input) {
        int n = input.size();
        arr = input;
        blockSize = ceil(sqrt(n));
        blocks.resize(blockSize, 0);

        for (int i = 0; i < n; ++i) {
            blocks[i / blockSize] += arr[i];
        }
    }

    void update(int idx, int val) {
        int b_idx = idx / blockSize;
        blocks[b_idx] += (val - arr[idx]);
        arr[idx] = val;
    }

    long long query(int l, int r) {
        long long sum = 0;
        int startBlock = l / blockSize;
        int endBlock = r / blockSize;

        if (startBlock == endBlock) {
            for (int i = l; i <= r; ++i) sum += arr[i];
        } else {
            // Partial start block
            for (int i = l; i < (startBlock + 1) * blockSize; ++i) sum += arr[i];
            // Full middle blocks
            for (int i = startBlock + 1; i < endBlock; ++i) sum += blocks[i];
            // Partial end block
            for (int i = endBlock * blockSize; i <= r; ++i) sum += arr[i];
        }
        return sum;
    }
};

void test() {
    cout << "Testing: Square Root Decomposition" << endl;
    vector<int> input = {1, 5, 2, 4, 6, 1, 3, 5, 7, 10};
    SqrtDecomposition sd(input);

    cout << "  Query(3, 8): " << sd.query(3, 8) << " (Expected: 26)" << endl;
    sd.update(8, 0);
    cout << "  After update(8, 0), Query(3, 8): " << sd.query(3, 8) << " (Expected: 19)" << endl;
}

int main() {
    test();
    return 0;
}
