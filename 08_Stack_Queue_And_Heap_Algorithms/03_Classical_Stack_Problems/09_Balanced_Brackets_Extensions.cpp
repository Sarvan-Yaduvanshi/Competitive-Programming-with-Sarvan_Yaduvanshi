/*
╔══════════════════════════════════════════════════════════════════════════════╗
║       09 — BALANCED BRACKETS + EXPRESSION TREE (COMPLETE)                    ║
║           From Zero to Grandmaster — Classical Stack Problems               ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

BALANCED BRACKETS (Extension of LC 20):
──────────────────────────────────────
  Classic: Check if brackets are balanced (multiple types).
  Extensions:
    1. Minimum swaps to make balanced
    2. Minimum removals to make valid (LC 1249)
    3. Minimum additions to make valid (LC 921)
    4. Longest valid parentheses (LC 32)

MINIMUM SWAPS TO BALANCE (LC 1963):
──────────────────────────────────
  Given string of only '[' and ']', find min swaps.

  After removing all balanced pairs, you get: "]]]...[[[..."
  If remaining unbalanced = k, answer = ceil(k/2)

  DRY RUN: "][]["
  Process: ']' → unmatched close (count=1)
           '[' → unmatched open
           ']' → matches open
           '[' → unmatched open
  Actually stack approach:
    ']' → stack empty, unmatched++
    '[' → push
    ']' → pop (matched!)
    '[' → push
  unmatched_close=1, unmatched_open=stack.size()=1
  total_unmatched = 1+1 = 2, swaps = ceil(2/2) = 1 ✅

LONGEST VALID PARENTHESES (LC 32):
─────────────────────────────────
  Find the length of the longest valid parentheses substring.

  Stack stores INDICES of unmatched brackets.

  DRY RUN: "(()"
  stack=[-1] (sentinel base)
  i=0 '(': push 0 → stack=[-1,0]
  i=1 '(': push 1 → stack=[-1,0,1]
  i=2 ')': pop 1 → stack=[-1,0], length=2-0=2
  Answer: 2 ✅

  DRY RUN: ")()())"
  stack=[-1]
  i=0 ')': pop -1 → empty! push 0 → stack=[0]
  i=1 '(': push 1 → stack=[0,1]
  i=2 ')': pop 1 → stack=[0], length=2-0=2
  i=3 '(': push 3 → stack=[0,3]
  i=4 ')': pop 3 → stack=[0], length=4-0=4
  i=5 ')': pop 0 → empty! push 5 → stack=[5]
  Answer: 4 ✅
*/

#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// 1. MINIMUM REMOVALS TO MAKE VALID (LC 1249)
// ═══════════════════════════════════════════════════════════════

string minRemoveToMakeValid(string s) {
    stack<int> st;  // Indices of unmatched '('
    vector<bool> remove(s.size(), false);

    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '(') {
            st.push(i);
        } else if (s[i] == ')') {
            if (!st.empty()) {
                st.pop();  // Matched!
            } else {
                remove[i] = true;  // Unmatched ')'
            }
        }
    }

    // Remaining in stack = unmatched '('
    while (!st.empty()) {
        remove[st.top()] = true;
        st.pop();
    }

    string result;
    for (int i = 0; i < (int)s.size(); i++) {
        if (!remove[i]) result += s[i];
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════
// 2. MINIMUM ADDITIONS TO MAKE VALID (LC 921)
// ═══════════════════════════════════════════════════════════════

int minAddToMakeValid(string s) {
    int open = 0, close = 0;  // Unmatched counts

    for (char c : s) {
        if (c == '(') {
            open++;
        } else {
            if (open > 0) open--;  // Match with unmatched open
            else close++;          // Unmatched close
        }
    }
    return open + close;  // Need to add this many brackets
}

// ═══════════════════════════════════════════════════════════════
// 3. LONGEST VALID PARENTHESES (LC 32) ★★★
// ═══════════════════════════════════════════════════════════════

int longestValidParentheses(string s) {
    stack<int> st;
    st.push(-1);  // Sentinel base for length calculation
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

// DP approach for comparison
int longestValidParenthesesDP(string s) {
    int n = s.size();
    vector<int> dp(n, 0);
    int maxLen = 0;

    for (int i = 1; i < n; i++) {
        if (s[i] == ')') {
            if (s[i-1] == '(') {
                // Pattern: ...()
                dp[i] = (i >= 2 ? dp[i-2] : 0) + 2;
            } else if (dp[i-1] > 0 && i - dp[i-1] - 1 >= 0
                       && s[i - dp[i-1] - 1] == '(') {
                // Pattern: ...))
                dp[i] = dp[i-1] + 2;
                if (i - dp[i-1] - 2 >= 0)
                    dp[i] += dp[i - dp[i-1] - 2];
            }
            maxLen = max(maxLen, dp[i]);
        }
    }
    return maxLen;
}

// ═══════════════════════════════════════════════════════════════
// 4. MINIMUM SWAPS TO MAKE BALANCED (LC 1963)
// ═══════════════════════════════════════════════════════════════

int minSwaps(string s) {
    int unmatched = 0;  // Count of unmatched '['

    for (char c : s) {
        if (c == '[') {
            unmatched++;
        } else {
            if (unmatched > 0) unmatched--;
            // else: unmatched ']', but we only need to count half
        }
    }
    // unmatched = number of unmatched '[' = number of unmatched ']'
    // Minimum swaps = ceil(unmatched / 2)
    return (unmatched + 1) / 2;
}

// ═══════════════════════════════════════════════════════════════
// 5. SCORE OF PARENTHESES (LC 856)
// ═══════════════════════════════════════════════════════════════
/*
  () = 1
  AB = A + B
  (A) = 2 * A

  DRY RUN: "(()(()))"
  stack = [0]
  '(': push 0 → [0, 0]
  '(': push 0 → [0, 0, 0]
  ')': pop 0 → score=max(1, 2*0)=1, add to top → [0, 1]
  '(': push 0 → [0, 1, 0]
  '(': push 0 → [0, 1, 0, 0]
  ')': pop 0 → score=1, add to top → [0, 1, 1]
  ')': pop 1 → score=2, add to top → [0, 3]
  ')': pop 3 → score=6, add to top → [6]
  Answer: 6 ✅
*/

int scoreOfParentheses(string s) {
    stack<int> st;
    st.push(0);

    for (char c : s) {
        if (c == '(') {
            st.push(0);
        } else {
            int inner = st.top(); st.pop();
            int score = max(1, 2 * inner);
            st.top() += score;
        }
    }
    return st.top();
}

// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  BRACKET PROBLEMS: BALANCE, REMOVE, LENGTH, SWAP, SCORE  ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Min Remove
    cout << "═══ MIN REMOVE TO MAKE VALID (LC 1249) ═══\n";
    cout << "  \"lee(t(c)o)de)\" → \"" << minRemoveToMakeValid("lee(t(c)o)de)") << "\"\n";
    cout << "  \"a)b(c)d\" → \"" << minRemoveToMakeValid("a)b(c)d") << "\"\n";
    cout << "  \"))((\" → \"" << minRemoveToMakeValid("))((") << "\"\n\n";

    // Min Additions
    cout << "═══ MIN ADDITIONS (LC 921) ═══\n";
    cout << "  \"())\" → " << minAddToMakeValid("())") << "\n";
    cout << "  \"(((\" → " << minAddToMakeValid("(((") << "\n";
    cout << "  \"()\" → " << minAddToMakeValid("()") << "\n\n";

    // Longest Valid
    cout << "═══ LONGEST VALID PARENTHESES (LC 32) ═══\n";
    cout << "  \"(()\" → " << longestValidParentheses("(()") << "\n";
    cout << "  \")()())\" → " << longestValidParentheses(")()())") << "\n";
    cout << "  \"\" → " << longestValidParentheses("") << "\n";
    cout << "  DP approach: \")()())\" → " << longestValidParenthesesDP(")()())") << "\n\n";

    // Min Swaps
    cout << "═══ MIN SWAPS TO BALANCE (LC 1963) ═══\n";
    cout << "  \"][][\" → " << minSwaps("][][") << "\n";
    cout << "  \"]]][[[ \" → " << minSwaps("]]][[[") << "\n";
    cout << "  \"[]\" → " << minSwaps("[]") << "\n\n";

    // Score
    cout << "═══ SCORE OF PARENTHESES (LC 856) ═══\n";
    cout << "  \"()\" → " << scoreOfParentheses("()") << "\n";
    cout << "  \"(())\" → " << scoreOfParentheses("(())") << "\n";
    cout << "  \"()()\" → " << scoreOfParentheses("()()") << "\n";
    cout << "  \"(()(()))\" → " << scoreOfParentheses("(()(()))") << "\n";

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE:\n";
    cout << "  LC 20   — Valid Parentheses\n";
    cout << "  LC 32   — Longest Valid Parentheses ★★★\n";
    cout << "  LC 856  — Score of Parentheses\n";
    cout << "  LC 921  — Minimum Add to Make Valid\n";
    cout << "  LC 1249 — Minimum Remove to Make Valid\n";
    cout << "  LC 1963 — Minimum Swaps to Balance\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

