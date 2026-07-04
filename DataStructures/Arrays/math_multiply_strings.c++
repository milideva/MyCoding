#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

/*
  LeetCode 43: Multiply Strings

  Problem Description:
  Given two non-negative integers `num1` and `num2` represented as 
  strings, return the product of `num1` and `num2`, also represented 
  as a string.

  Note: You must not use any built-in BigInteger library or convert 
  the inputs to integer directly.

  Algorithm: Elementary School Multiplication Simulation
  1. If either number is "0", return "0".
  2. Initialize a result vector `pos` of size `num1.size() + num2.size()`.
  3. Iterate through `num1` from right to left (index `i`).
  4. Iterate through `num2` from right to left (index `j`).
  5. Multiply digits: `mul = (num1[i]-'0') * (num2[j]-'0')`.
  6. The product `mul` contributes to indices `p1 = i + j` and 
     `p2 = i + j + 1` in the `pos` vector.
  7. Add `mul` to `pos[p2]`, then update `pos[p1]` with the carry.
  8. Convert the `pos` vector to a string, skipping leading zeros.

  Complexity Analysis:
  - Time Complexity: O(M * N)
    Reason: We perform nested loops over the lengths of the two strings.
  - Space Complexity: O(M + N)
    Reason: To store the result of the multiplication.

  Brute Force comparison:
  - Converting to `unsigned long long` is not a viable brute force 
    because it will overflow for large inputs (strings up to 200 chars).
  - Simulating multiplication digit-by-digit is the standard optimal 
    approach.
*/

class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") return "0";

        int n1 = num1.size(), n2 = num2.size();
        vector<int> pos(n1 + n2, 0);

        for (int i = n1 - 1; i >= 0; i--) {
            for (int j = n2 - 1; j >= 0; j--) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                int p1 = i + j, p2 = i + j + 1;
                int sum = mul + pos[p2];

                pos[p1] += sum / 10;
                pos[p2] = sum % 10;
            }
        }

        string res = "";
        for (int p : pos) {
            if (!(res.empty() && p == 0)) res += to_string(p);
        }
        return res.empty() ? "0" : res;
    }
};

void test(const string& label, string num1, string num2, string expected) {
    cout << "Testing: " << label << endl;
    Solution sol;
    string result = sol.multiply(num1, num2);
    if (result == expected) {
        cout << "  [PASS] Result: " << result << endl;
    } else {
        cout << "  [FAIL] Result: " << result << " (Expected: " << expected << ")" << endl;
    }
}

int main() {
    test("Example 1", "2", "3", "6");
    test("Example 2", "123", "456", "56088");
    test("Overflow Test", "498828660196", "840477629533", "419254329864656431168468");
    test("Multiplication by Zero", "123", "0", "0");
    return 0;
}
