/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — MIN STACK (LC 155)                                            ║
║           From Zero to Grandmaster — Stack & Queue Design Problems          ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: Design a stack that supports push, pop, top, and getMin in O(1).

APPROACH: Two stacks — main stack + min stack
─────────────────────────────────────────────
  Main stack: stores all elements normally
  Min stack:  stores the current minimum at each level

  OR: Single stack with pairs (value, currentMin)

DRY RUN:
  push(-2): main=[-2], min=[-2]      getMin()=-2
  push(0):  main=[-2,0], min=[-2,-2] getMin()=-2
  push(-3): main=[-2,0,-3], min=[-2,-2,-3] getMin()=-3
  pop():    main=[-2,0], min=[-2,-2]  getMin()=-2
  top():    0
  getMin(): -2

  ┌──────────┬──────────┐
  │ Main     │ Min      │
  │ Stack    │ Stack    │
  ├──────────┼──────────┤
  │   -3     │   -3     │ ← top (before pop)
  │    0     │   -2     │
  │   -2     │   -2     │
  └──────────┴──────────┘

  After pop():
  ┌──────────┬──────────┐
  │    0     │   -2     │ ← top
  │   -2     │   -2     │
  └──────────┴──────────┘

ALL OPERATIONS: O(1) time, O(n) space
*/

#include <iostream>
#include <stack>
#include <climits>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// APPROACH 1: TWO STACKS
// ═══════════════════════════════════════════════════════════════

class MinStack {
    stack<int> mainSt;
    stack<int> minSt;

public:
    void push(int val) {
        mainSt.push(val);
        if (minSt.empty() || val <= minSt.top()) {
            minSt.push(val);
        } else {
            minSt.push(minSt.top());
        }
    }

    void pop() {
        mainSt.pop();
        minSt.pop();
    }

    int top() { return mainSt.top(); }
    int getMin() { return minSt.top(); }
};

// ═══════════════════════════════════════════════════════════════
// APPROACH 2: SINGLE STACK WITH PAIRS
// ═══════════════════════════════════════════════════════════════

class MinStack2 {
    stack<pair<int,int>> st;  // (value, currentMin)

public:
    void push(int val) {
        int curMin = st.empty() ? val : min(val, st.top().second);
        st.push({val, curMin});
    }

    void pop() { st.pop(); }
    int top() { return st.top().first; }
    int getMin() { return st.top().second; }
};

// ═══════════════════════════════════════════════════════════════
// APPROACH 3: O(1) SPACE (Mathematical trick)
// ═══════════════════════════════════════════════════════════════
/*
  Store encoded values: if val < currentMin, push (2*val - currentMin)
  This is a sentinel that tells us the previous min when we pop.

  push(val):
    if val >= min: push val normally, min unchanged
    if val < min:  push (2*val - min), update min = val

  pop():
    if top >= min: normal pop
    if top < min:  the real value is current min
                   previous min = 2*min - top

  ⚠️ Risk of integer overflow with large values!
*/

class MinStackO1Space {
    stack<long long> st;
    long long minVal;

public:
    void push(int val) {
        if (st.empty()) {
            st.push(val);
            minVal = val;
        } else if (val >= minVal) {
            st.push(val);
        } else {
            st.push(2LL * val - minVal);  // Encoded
            minVal = val;
        }
    }

    void pop() {
        if (st.top() < minVal) {
            minVal = 2 * minVal - st.top();  // Restore previous min
        }
        st.pop();
    }

    int top() {
        if (st.top() < minVal) return minVal;  // Encoded → real value is minVal
        return st.top();
    }

    int getMin() { return minVal; }
};

// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  MIN STACK (LC 155) — 3 APPROACHES                      ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Test all 3 approaches
    cout << "═══ APPROACH 1: TWO STACKS ═══\n";
    MinStack ms1;
    ms1.push(-2); ms1.push(0); ms1.push(-3);
    cout << "  getMin(): " << ms1.getMin() << "\n";  // -3
    ms1.pop();
    cout << "  top():    " << ms1.top() << "\n";      // 0
    cout << "  getMin(): " << ms1.getMin() << "\n";   // -2

    cout << "\n═══ APPROACH 2: SINGLE STACK PAIRS ═══\n";
    MinStack2 ms2;
    ms2.push(-2); ms2.push(0); ms2.push(-3);
    cout << "  getMin(): " << ms2.getMin() << "\n";
    ms2.pop();
    cout << "  top():    " << ms2.top() << "\n";
    cout << "  getMin(): " << ms2.getMin() << "\n";

    cout << "\n═══ APPROACH 3: O(1) SPACE (MATH TRICK) ═══\n";
    MinStackO1Space ms3;
    ms3.push(-2); ms3.push(0); ms3.push(-3);
    cout << "  getMin(): " << ms3.getMin() << "\n";
    ms3.pop();
    cout << "  top():    " << ms3.top() << "\n";
    cout << "  getMin(): " << ms3.getMin() << "\n";

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE: LC 155 — Min Stack, LC 716 — Max Stack\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

