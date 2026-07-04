#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
  LeetCode 273: Integer to English Words

  Problem Description:
  Convert a non-negative integer `num` to its English words 
  representation.

  Example 1:
  Input: num = 123
  Output: "One Hundred Twenty Three"

  Algorithm: Recursive Segment Processing
  1. Define mappings for numbers under 20 and tens.
  2. Handle 0 separately as "Zero".
  3. Divide the number into segments of three digits: Billions, 
     Millions, Thousands, and the remainder.
  4. Recursive function `helper(n)`:
     - If `n >= 100`, process hundreds: `helper(n/100) + " Hundred " + helper(n%100)`.
     - If `n >= 20`, process tens: `tens[n/10] + " " + helper(n%10)`.
     - If `n > 0`, process units: `under20[n]`.
  5. Trim trailing spaces.

  Complexity Analysis:
  - Time Complexity: O(log N)
    Reason: The number of digits in N is log10(N). We process fixed 
    segments.
  - Space Complexity: O(log N) for the recursion stack and result string.
*/

class Solution {
    vector<string> lessThan20 = {
        "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
        "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"
    };
    vector<string> tens = {
        "", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"
    };
    vector<string> thousands = {"", "Thousand", "Million", "Billion"};

    string helper(int n) {
        if (n == 0) return "";
        if (n < 20) return lessThan20[n] + " ";
        if (n < 100) return tens[n / 10] + " " + helper(n % 10);
        return lessThan20[n / 100] + " Hundred " + helper(n % 100);
    }

public:
    string numberToWords(int num) {
        if (num == 0) return "Zero";

        string res = "";
        int i = 0;
        while (num > 0) {
            if (num % 1000 != 0) {
                res = helper(num % 1000) + thousands[i] + " " + res;
            }
            num /= 1000;
            i++;
        }

        // Trim trailing space
        while (!res.empty() && res.back() == ' ') res.pop_back();
        return res;
    }
};

void test(int num) {
    Solution sol;
    cout << "Number: " << num << " -> \"" << sol.numberToWords(num) << "\"" << endl;
}

int main() {
    test(123);
    test(12345);
    test(1234567);
    test(1000010);
    test(0);
    return 0;
}
