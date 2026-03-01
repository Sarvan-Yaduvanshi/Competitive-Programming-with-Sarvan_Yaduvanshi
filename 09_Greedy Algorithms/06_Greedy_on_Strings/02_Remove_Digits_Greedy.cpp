/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Remove Digits Greedy — Monotone Stack
 *  Level   : Advanced
 * ============================================================================
 *
 *  PROBLEM (LC 402): Given a string num of digits and integer k,
 *  remove k digits to make the smallest possible number.
 *
 *  GREEDY: Use a monotone increasing stack.
 *  Whenever the current digit is smaller than the stack top, pop the top
 *  (this effectively "removes" a larger digit from a more significant position).
 *
 *  WHY IT WORKS:
 *  A larger digit in a more significant position contributes more to the value.
 *  By removing it, we get a smaller number.
 *
 *  TIME: O(N), SPACE: O(N)
 *
 * ============================================================================
 */

#include <iostream>
#include <string>
using namespace std;

// LC 402: Remove K Digits
string removeKdigits(string num, int k) {
    string stack_str; // Monotone increasing stack

    for (char c : num) {
        // Remove larger digits from the left (more significant positions)
        while (k > 0 && !stack_str.empty() && stack_str.back() > c) {
            stack_str.pop_back();
            k--;
        }
        stack_str.push_back(c);
    }

    // If k still > 0, remove from the end (largest remaining)
    while (k > 0) {
        stack_str.pop_back();
        k--;
    }

    // Remove leading zeros
    int start = 0;
    while (start < (int)stack_str.size() && stack_str[start] == '0') start++;

    string result = stack_str.substr(start);
    return result.empty() ? "0" : result;
}

// Related: Create Maximum Number from digits of two arrays
// Uses same monotone stack technique

int main() {
    cout << "Remove 3 from '1432219': " << removeKdigits("1432219", 3) << endl; // "1219"
    cout << "Remove 1 from '10200':   " << removeKdigits("10200", 1) << endl;   // "200"
    cout << "Remove 2 from '10':      " << removeKdigits("10", 2) << endl;       // "0"
    cout << "Remove 1 from '112':     " << removeKdigits("112", 1) << endl;      // "11"

    return 0;
}

