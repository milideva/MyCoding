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
  - Space Complexity: O(N)

  What are "Catalan Numbers" and why are they relevant here?
  ---------------------------------------------------------
  1. What is the question we are asking?
     To find the running time of an algorithm that generates all valid combinations, we must 
     know: "How many valid configurations are we printing for N pairs of parentheses?"
     Let's manually count the output size for different N:
     - N = 1 pair:  1 valid string:  ()
     - N = 2 pairs: 2 valid strings: (()), ()()
     - N = 3 pairs: 5 valid strings: ((())), (()()), (())(), ()(()), ()()()
     - N = 4 pairs: 14 valid strings.
     - N = 5 pairs: 42 valid strings.
     This sequence of counts is: 1, 2, 5, 14, 42, 132, 429, ...

  2. The Catalan Sequence:
     In mathematics, this exact sequence is called the "Catalan Numbers" (denoted as C_N). 
     By definition, the N-th Catalan Number is the exact number of valid parentheses sequences 
     you can form with N pairs of brackets.

  3. How does this define our Time Complexity?
     Since our backtracking algorithm generates every single valid combination, the number of 
     leaf nodes in our recursion tree is exactly C_N.
     For each of these C_N combinations, we spend O(N) work to build/append the string.
     Therefore: Total Time = O(N * C_N).

  4. Where does the "4" in O(4^N / sqrt(N)) come from?
     Mathematically, the Catalan numbers can be calculated using the combination formula:
         C_N = (1 / (N + 1)) * (2N choose N)

     The central binomial coefficient (2N choose N) represents the single largest element in 
     row 2N of Pascal's Triangle. Summing all elements in row 2N of Pascal's Triangle gives:
         Sum = 2^(2N) = (2^2)^N = 4^N
     Since (2N choose N) is the dominant term, it is bounded by this total sum 4^N.

     Using Stirling's Approximation (n! ≈ sqrt(2 * pi * n) * (n/e)^n), mathematicians 
     proved that the asymptotic growth rate of C_N is:
         C_N ≈ 4^N / (N * sqrt(pi * N)) = Θ(4^N / N^(3/2))

     Plugging this growth rate back into our Time Complexity:
         Time Complexity = O(N * C_N) = O(N * (4^N / N^(3/2))) = O(4^N / sqrt(N))

  Space Complexity Explanation:
  - Space Complexity: O(N)
    Reason: The maximum depth of the recursion stack is 2 * N, requiring O(N) call frames. 
    In the explicit backtracking implementation, we reuse a single string of size O(N), 
    while the implicit version creates string copies at each recursion frame of size up to O(N) 
    (the peak auxiliary memory remains O(N)).
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
