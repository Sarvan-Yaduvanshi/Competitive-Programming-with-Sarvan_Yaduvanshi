/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — STACK COMPLETE GUIDE                                        ║
║           From Zero to Grandmaster — LIFO Power                            ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Basic Stack Operations
 2. Valid Parentheses Problem
 3. Next Greater Element (Monotonic Stack)
 4. Largest Rectangle in Histogram
 5. Stack-based Expression Evaluation

STACK = LIFO (Last In, First Out)
  push(x) → O(1)
  pop()   → O(1)
  top()   → O(1)
  empty() → O(1)
  size()  → O(1)

  No iteration, no random access — only top!
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: BASIC OPERATIONS
// ═══════════════════════════════════════════════════════════════

void demonstrateBasics() {
    cout << "═══ STACK BASICS ═══\n\n";

    stack<int> st;
    st.push(10);
    st.push(20);
    st.push(30);

    cout << "Top: " << st.top() << "\n";
    cout << "Size: " << st.size() << "\n";

    cout << "Pop order (LIFO): ";
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: VALID PARENTHESES
// ═══════════════════════════════════════════════════════════════
/*
 DRY RUN: s = "({[]})"
   '(' → push → stack: ['(']
   '{' → push → stack: ['(', '{']
   '[' → push → stack: ['(', '{', '[']
   ']' → matches '[' → pop → stack: ['(', '{']
   '}' → matches '{' → pop → stack: ['(']
   ')' → matches '(' → pop → stack: []
   Stack empty → VALID ✓
*/

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

void validParentheses() {
    cout << "═══ VALID PARENTHESES ═══\n\n";
    vector<string> tests = {"({[]})", "(()", "{[()]}", "([)]", ""};
    for (auto& s : tests) {
        cout << "\"" << s << "\" → " << (isValid(s) ? "VALID" : "INVALID") << "\n";
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: NEXT GREATER ELEMENT (MONOTONIC STACK)
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM: For each element, find the next element that is greater.

 APPROACH: Maintain a DECREASING stack. When new element > top,
           it's the "next greater" for the top.

 DRY RUN: arr = [4, 5, 2, 25, 7, 8]
   i=0: arr[0]=4, stack empty → push 0. Stack: [0(4)]
   i=1: arr[1]=5 > 4 → NGE[0]=5, pop. Stack empty. Push 1. Stack: [1(5)]
   i=2: arr[2]=2 < 5 → push 2. Stack: [1(5), 2(2)]
   i=3: arr[3]=25 > 2 → NGE[2]=25, pop. 25 > 5 → NGE[1]=25, pop. Push 3. Stack: [3(25)]
   i=4: arr[4]=7 < 25 → push 4. Stack: [3(25), 4(7)]
   i=5: arr[5]=8 > 7 → NGE[4]=8, pop. 8 < 25. Push 5. Stack: [3(25), 5(8)]
   Remaining: NGE[3]=-1, NGE[5]=-1

   Result: [5, 25, 25, -1, 8, -1]
*/

void nextGreaterElement() {
    cout << "═══ NEXT GREATER ELEMENT (MONOTONIC STACK) ═══\n\n";

    vector<int> arr = {4, 5, 2, 25, 7, 8};
    int n = arr.size();
    vector<int> nge(n, -1);  // -1 if no greater element

    stack<int> st;  // Store INDICES
    for (int i = 0; i < n; i++) {
        while (!st.empty() && arr[st.top()] < arr[i]) {
            nge[st.top()] = arr[i];
            st.pop();
        }
        st.push(i);
    }

    cout << "Array: ";
    for (int x : arr) cout << x << "\t";
    cout << "\nNGE:   ";
    for (int x : nge) cout << x << "\t";
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: LARGEST RECTANGLE IN HISTOGRAM
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM: Given bar heights, find largest rectangle area.

 APPROACH: For each bar, find how far left and right it can extend
           (until a shorter bar is found). Use monotonic stack.

 DRY RUN: heights = [2, 1, 5, 6, 2, 3]
   For bar of height 5 (index 2):
     Left boundary: index 2 (bar at 1 stops it)
     Right boundary: index 3 (bar at 2 stops it at index 4)
     Width = 4-2 = 2, Area = 5*2 = 10
   For bar of height 6 (index 3):
     Width = 1, Area = 6

   Max area = 10 (from bars at index 2-3 with height 5)
*/

int largestRectangle(vector<int>& heights) {
    int n = heights.size();
    stack<int> st;
    int maxArea = 0;

    for (int i = 0; i <= n; i++) {
        int h = (i == n) ? 0 : heights[i];
        while (!st.empty() && heights[st.top()] > h) {
            int height = heights[st.top()];
            st.pop();
            int width = st.empty() ? i : i - st.top() - 1;
            maxArea = max(maxArea, height * width);
        }
        st.push(i);
    }
    return maxArea;
}

void histogramProblem() {
    cout << "═══ LARGEST RECTANGLE IN HISTOGRAM ═══\n\n";
    vector<int> heights = {2, 1, 5, 6, 2, 3};
    cout << "Heights: ";
    for (int h : heights) cout << h << " ";
    cout << "\nLargest rectangle area: " << largestRectangle(heights) << "\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demonstrateBasics();
    validParentheses();
    nextGreaterElement();
    histogramProblem();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. Stack = LIFO, O(1) push/pop/top\n";
    cout << "2. Parentheses matching: push open, pop on close\n";
    cout << "3. Monotonic stack: O(n) for next greater/smaller\n";
    cout << "4. Histogram: monotonic stack for left/right boundaries\n";
    cout << "5. Each element pushed/popped at most once → O(n) total\n";

    return 0;
}

/*
 PRACTICE PROBLEMS:
 ──────────────────
 1. [LC Valid Parentheses]        https://leetcode.com/problems/valid-parentheses/
 2. [LC Next Greater Element I]   https://leetcode.com/problems/next-greater-element-i/
 3. [LC Largest Rectangle]        https://leetcode.com/problems/largest-rectangle-in-histogram/
 4. [CSES Nearest Smaller Values] https://cses.fi/problemset/task/1645
*/

