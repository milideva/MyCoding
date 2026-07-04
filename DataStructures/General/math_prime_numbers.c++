#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

/*
  LeetCode 204: Count Primes

  Problem Description:
  Given an integer `n`, return the number of prime numbers that are 
  strictly less than `n`.

  Algorithm: Sieve of Eratosthenes
  1. Create a boolean array `isPrime` of size `n`, initialized to true.
  2. Mark `isPrime[0]` and `isPrime[1]` as false.
  3. For `p` from 2 up to `sqrt(n)`:
     - If `isPrime[p]` is true:
       - Mark all multiples of `p` starting from `p*p` as false.
  4. Count the number of true values in the array.

  Complexity Analysis:
  - Time Complexity: O(N log log N)
  - Space Complexity: O(N).
*/

class Solution {
public:
    int countPrimes(int n) {
        if (n <= 2) return 0;
        vector<bool> isPrime(n, true);
        isPrime[0] = isPrime[1] = false;

        for (int p = 2; p * p < n; p++) {
            if (isPrime[p]) {
                for (int i = p * p; i < n; i += p) {
                    isPrime[i] = false;
                }
            }
        }

        int count = 0;
        for (int i = 2; i < n; i++) {
            if (isPrime[i]) count++;
        }
        return count;
    }
    
    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }
};

void test(int n) {
    Solution sol;
    cout << "Primes strictly less than " << n << ": " << sol.countPrimes(n) << endl;
}

int main() {
    test(10);  // 4 (2, 3, 5, 7)
    test(0);   // 0
    test(1);   // 0
    test(100); // 25
    return 0;
}
