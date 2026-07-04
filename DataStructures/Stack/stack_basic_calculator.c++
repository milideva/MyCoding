#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <cctype>

using namespace std;

/*
  LeetCode 224/227: Basic Calculator (with Parentheses)

  Problem Description:
  Given a string expression containing non-negative integers, '+', 
  '-', '*', '/', '(', and ')', evaluate the expression.

  Algorithm: Shunting-Yard Algorithm / Two Stacks
  1. Use two stacks: `values` for numbers and `ops` for operators.
  2. Define precedence: `*`, `/` > `+`, `-`.
  3. Iterate through the string:
     - If digit: Parse the full number and push to `values`.
     - If '(': Push to `ops`.
     - If ')': While top of `ops` is not '(', evaluate the top 
       operator with two values. Pop '('.
     - If operator: 
       - While top of `ops` has higher or equal precedence, 
         evaluate it.
       - Push current operator to `ops`.
  4. After the loop, evaluate remaining operators in `ops`.

  Complexity Analysis:
  - Time Complexity: O(N)
    Reason: Each character is processed once, and each value/operator 
    is pushed/popped at most once.
  - Space Complexity: O(N) for the stacks.
*/

class BasicCalculator {
    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }

    int applyOp(int a, int b, char op) {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return a / b;
        }
        return 0;
    }

public:
    int evaluate(string expression) {
        stack<int> values;
        stack<char> ops;

        for (int i = 0; i < expression.length(); i++) {
            if (isspace(expression[i])) continue;

            if (isdigit(expression[i])) {
                int val = 0;
                while (i < expression.length() && isdigit(expression[i])) {
                    val = (val * 10) + (expression[i] - '0');
                    i++;
                }
                values.push(val);
                i--;
            } else if (expression[i] == '(') {
                ops.push('(');
            } else if (expression[i] == ')') {
                while (!ops.empty() && ops.top() != '(') {
                    int val2 = values.top(); values.pop();
                    int val1 = values.top(); values.pop();
                    char op = ops.top(); ops.pop();
                    values.push(applyOp(val1, val2, op));
                }
                if (!ops.empty()) ops.pop();
            } else {
                while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i])) {
                    int val2 = values.top(); values.pop();
                    int val1 = values.top(); values.pop();
                    char op = ops.top(); ops.pop();
                    values.push(applyOp(val1, val2, op));
                }
                ops.push(expression[i]);
            }
        }

        while (!ops.empty()) {
            int val2 = values.top(); values.pop();
            int val1 = values.top(); values.pop();
            char op = ops.top(); ops.pop();
            values.push(applyOp(val1, val2, op));
        }

        return values.top();
    }
};

void test(string expression, int expected) {
    BasicCalculator calc;
    int result = calc.evaluate(expression);
    cout << "Expr: \"" << expression << "\" -> Result: " << result;
    if (result == expected) cout << " [PASS]";
    else cout << " [FAIL] Expected: " << expected;
    cout << endl;
}

int main() {
    test("1 + 1", 2);
    test(" 2-1 + 2 ", 3);
    test("(1+(4+5+2)-3)+(6+8)", 23);
    test("10 + 2 * 6", 22);
    test("100 * (2 + 12) / 14", 100);
    return 0;
}
