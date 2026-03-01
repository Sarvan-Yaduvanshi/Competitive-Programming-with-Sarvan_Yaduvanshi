/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — VALID PARENTHESES (BALANCED BRACKETS)                         ║
║           From Zero to Grandmaster — Classical Stack Problems               ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Problem Definition
 2. Stack-Based Solution
 3. Multiple Bracket Types
 4. Detailed Dry Run
 5. Edge Cases
 6. Variations

PROBLEM:
────────
  Given a string containing brackets, check if they are balanced.
  Types: (), {}, []

  Valid:   "()", "(())", "{[()]}", "()[]{}"
  Invalid: "(]", "([)]", "(", "(()"

INTUITION:
─────────
  Every opening bracket MUST have a matching closing bracket,
  and they must be properly nested.

  Stack is perfect because:
    • Push opening bracket
    • On closing bracket, check if top matches
    • If stack empty at end → balanced!

  ┌───────────────────────────────────────────┐
  │ String: "{[()]}"                          │
  │                                           │
  │ i=0: '{' → push          stack: [{]      │
  │ i=1: '[' → push          stack: [{, []   │
  │ i=2: '(' → push          stack: [{, [, (]│
  │ i=3: ')' → matches '('   stack: [{, []   │
  │ i=4: ']' → matches '['   stack: [{]      │
  │ i=5: '}' → matches '{'   stack: []       │
  │                                           │
  │ Stack empty → ✅ BALANCED                  │
  └───────────────────────────────────────────┘

  ┌───────────────────────────────────────────┐
  │ String: "([)]"                            │
  │                                           │
  │ i=0: '(' → push          stack: [(]      │
  │ i=1: '[' → push          stack: [(, []   │
  │ i=2: ')' → top='[' ≠ '(' → ❌ INVALID    │
  │                                           │
  │ Mismatch! Not balanced.                   │
  └───────────────────────────────────────────┘

TIME: O(n)  SPACE: O(n)
*/

#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: BASIC VALID PARENTHESES — LC 20
// ═══════════════════════════════════════════════════════════════

bool isValid(string s) {
    stack<char> st;

    for (char c : s) {
        if (c == '(' || c == '{' || c == '[') {
            st.push(c);
        } else {
            if (st.empty()) return false;
            char top = st.top();
            if ((c == ')' && top == '(') ||
                (c == '}' && top == '{') ||
                (c == ']' && top == '[')) {
                st.pop();
            } else {
                return false;
            }
        }
    }
    return st.empty();
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: MINIMUM REMOVALS TO MAKE VALID — LC 1249
// ═══════════════════════════════════════════════════════════════
/*
  Given string with '(' and ')', remove minimum brackets to make valid.

  Strategy:
    Pass 1 (left to right): Remove unmatched ')'
    Pass 2 (right to left): Remove unmatched '('

  Or use stack to track indices of unmatched brackets.

  DRY RUN: "lee(t(c)o)de)"

  Stack stores indices of unmatched '('

  i=0:  'l' → skip
  i=3:  '(' → push 3     stack=[3]
  i=5:  '(' → push 5     stack=[3,5]
  i=7:  ')' → pop 5      stack=[3]
  i=9:  ')' → pop 3      stack=[]
  i=12: ')' → no match!  mark index 12 for removal

  Result: "lee(t(c)o)de"  (removed last ')')
*/

string minRemoveToMakeValid(string s) {
    stack<int> st;
    vector<bool> toRemove(s.size(), false);

    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '(') {
            st.push(i);
        } else if (s[i] == ')') {
            if (!st.empty()) {
                st.pop();
            } else {
                toRemove[i] = true;
            }
        }
    }

    // Remaining in stack are unmatched '('
    while (!st.empty()) {
        toRemove[st.top()] = true;
        st.pop();
    }

    string result;
    for (int i = 0; i < (int)s.size(); i++) {
        if (!toRemove[i]) result += s[i];
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: LONGEST VALID PARENTHESES — LC 32
// ═══════════════════════════════════════════════════════════════
/*
  Find length of longest valid parentheses substring.

  Stack stores INDICES. Initialize with -1 as base.

  DRY RUN: ")()())"

  stack = [-1]
  i=0: ')' → pop -1, stack empty → push 0     stack=[0]
  i=1: '(' → push 1                            stack=[0,1]
  i=2: ')' → pop 1, len=2-0=2, maxLen=2        stack=[0]
  i=3: '(' → push 3                            stack=[0,3]
  i=4: ')' → pop 3, len=4-0=4, maxLen=4        stack=[0]
  i=5: ')' → pop 0, stack empty → push 5       stack=[5]

  Answer: 4  (substring "()()")
*/

int longestValidParentheses(string s) {
    stack<int> st;
    st.push(-1);  // Base index
    int maxLen = 0;

    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '(') {
            st.push(i);
        } else {
            st.pop();
            if (st.empty()) {
                st.push(i);  // New base
            } else {
                maxLen = max(maxLen, i - st.top());
            }
        }
    }
    return maxLen;
}

// ═══════════════════════════════════════════════════════════════
// DEMONSTRATION
// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  VALID PARENTHESES — BALANCED BRACKETS                   ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Section 1: Basic validation
    cout << "═══ SECTION 1: VALID PARENTHESES ═══\n\n";
    vector<string> tests = {"()", "(())", "{[()]}", "()[]{}", "(]", "([)]", "(", "(()", ""};
    for (auto& s : tests) {
        cout << "  \"" << s << "\" → " << (isValid(s) ? "✅ Valid" : "❌ Invalid") << "\n";
    }

    // Section 2: Min removals
    cout << "\n═══ SECTION 2: MIN REMOVALS ═══\n\n";
    vector<string> tests2 = {"lee(t(c)o)de)", "a)b(c)d", "))(("};
    for (auto& s : tests2) {
        cout << "  \"" << s << "\" → \"" << minRemoveToMakeValid(s) << "\"\n";
    }

    // Section 3: Longest valid
    cout << "\n═══ SECTION 3: LONGEST VALID PARENTHESES ═══\n\n";
    vector<string> tests3 = {"(()", ")()())", "()(())", "(()()"};
    for (auto& s : tests3) {
        cout << "  \"" << s << "\" → " << longestValidParentheses(s) << "\n";
    }

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE PROBLEMS:\n";
    cout << "───────────────────\n";
    cout << "1. LC 20   — Valid Parentheses\n";
    cout << "2. LC 32   — Longest Valid Parentheses\n";
    cout << "3. LC 1249 — Minimum Remove to Make Valid\n";
    cout << "4. LC 921  — Minimum Add to Make Valid\n";
    cout << "5. LC 678  — Valid Parenthesis String (with *)\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

