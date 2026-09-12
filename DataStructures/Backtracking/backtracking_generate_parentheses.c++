#include <vector>
#include <string>
#include <iostream>

using namespace std;

/*
  LeetCode 22: Generate Parentheses

  Problem Description:
  Given `n` pairs of parentheses, write a function to generate all 
  combinations of well-formed parentheses.

  Example 1:
  Input: n = 3
  Output: ["((()))","(()())","(())()","()(())","()()()"]

  Algorithm: Backtracking with Constraints
  1. Maintain counts of `open` and `close` parentheses used.
  2. Recursive function with constraints.
  3. Base Case: If `current_string.length() == 2 * n`, add to result.
  4. Decision Rule:
     - If `open_count < n`, we can always add an '('.
     - If `close_count < open_count`, we can add a ')'.
  5. This ensures that we never have more closing parentheses than 
     opening ones at any point, guaranteeing well-formedness.

  Complexity Analysis:
  - Time Complexity: O(4^N / sqrt(N))
    Reason: The total number of valid parentheses combinations is given by the N-th Catalan Number:
    C_N = (1 / (N + 1)) * (2N choose N).
    Using Stirling's approximation, the asymptotic behavior of the Catalan number is:
    C_N ≈ 4^N / (N * sqrt(pi * N)) = Θ(4^N / N^(3/2))
    Since each path takes O(N) operations to build and append to results, the total time complexity is:
    Time = O(N * C_N) = O(N * (4^N / N^(3/2))) = O(4^N / sqrt(N))
    This makes the analysis in the comments absolutely correct!

  - Space Complexity: O(N)
    Reason: The maximum depth of the recursion stack is 2 * N, requiring O(N) call frames. 
    In the explicit backtracking implementation, we reuse a single string of size O(N), 
    while the implicit version creates string copies at each recursion frame of size up to O(N) (peak memory remains O(N)).
*/

class Solution {
    // -------------------------------------------------------------------------
    // Method 1: Implicit Backtracking (Using Pass-by-Value)
    // -------------------------------------------------------------------------
    // - How it works: We pass the string `curr` by value.
    // - Implicit state recovery: When the function makes a recursive call with `curr + "("`, 
    //   a copy of `curr` is passed down. When that call returns, the current stack frame's 
    //   copy of `curr` remains untouched (still at its original state).
    // - Pros: Very simple to write; no manual state restoration is required.
    // - Cons: Copying strings at each recursion level creates overhead (additional O(N) string copy per step).
    // -------------------------------------------------------------------------
    void backtrackImplicit(int n, int open, int close, string curr, vector<string>& result) {
        if (curr.length() == 2 * n) {
            result.push_back(curr);
            return;
        }

        if (open < n) {
            backtrackImplicit(n, open + 1, close, curr + "(", result);
        }
        if (close < open) {
            backtrackImplicit(n, open, close + 1, curr + ")", result);
        }
    }

    // -------------------------------------------------------------------------
    // Method 2: Explicit Backtracking (Using Pass-by-Reference & Undo)
    // -------------------------------------------------------------------------
    // - How it works: We pass the string `curr` by reference (`string& curr`).
    // - Explicit state recovery: We append a character to our single shared string (`curr.push_back(...)`), 
    //   recursively explore all paths with that character, and then manually remove it (`curr.pop_back()`) 
    //   before trying the next decision.
    // - Pros: Highly memory-efficient. No redundant string copies are made during recursion.
    // - Cons: Requires careful state restoration (forgetting to pop_back() will corrupt the search).
    // -------------------------------------------------------------------------
    void backtrackExplicit(int n, int open, int close, string& curr, vector<string>& result) {
        if (curr.length() == 2 * n) {
            result.push_back(curr);
            return;
        }

        if (open < n) {
            curr.push_back('('); // Choose
            backtrackExplicit(n, open + 1, close, curr, result); // Explore
            curr.pop_back();     // Un-choose (Explicit Backtrack)
        }
        if (close < open) {
            curr.push_back(')'); // Choose
            backtrackExplicit(n, open, close + 1, curr, result); // Explore
            curr.pop_back();     // Un-choose (Explicit Backtrack)
        }
    }

public:
    // API for Method 1
    vector<string> generateParenthesisImplicit(int n) {
        vector<string> result;
        backtrackImplicit(n, 0, 0, "", result);
        return result;
    }

    // API for Method 2
    vector<string> generateParenthesisExplicit(int n) {
        vector<string> result;
        string curr = "";
        backtrackExplicit(n, 0, 0, curr, result);
        return result;
    }
};

void test(int n) {
    cout << "Testing: n=" << n << endl;
    Solution sol;
    
    vector<string> res_implicit = sol.generateParenthesisImplicit(n);
    vector<string> res_explicit = sol.generateParenthesisExplicit(n);
    
    cout << "  Implicit Result: [ ";
    for (const string& s : res_implicit) cout << "\"" << s << "\" ";
    cout << "]" << endl;

    cout << "  Explicit Result: [ ";
    for (const string& s : res_explicit) cout << "\"" << s << "\" ";
    cout << "]" << endl;

    if (res_implicit == res_explicit) {
        cout << "  Verification: Both methods match perfectly! [PASS]" << endl;
    } else {
        cout << "  Verification: Discrepancy between implicit and explicit methods! [FAIL]" << endl;
    }
    cout << endl;
}

int main() {
    test(3);
    test(1);
    return 0;
}
