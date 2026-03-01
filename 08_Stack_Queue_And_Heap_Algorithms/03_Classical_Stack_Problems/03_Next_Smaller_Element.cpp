/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           03 — NEXT SMALLER ELEMENT (NSE)                                    ║
║           From Zero to Grandmaster — Classical Stack Problems               ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM:
────────
  For each element, find the NEXT SMALLER element to its right.
  If none exists, answer is -1.

  Input:  [4, 8, 5, 2, 25]
  Output: [2, 5, 2, -1, -1]

APPROACH:
────────
  Same as NGE but stack maintains INCREASING order (bottom to top).
  Process right to left. Pop elements ≥ current.

  DRY RUN: [4, 8, 5, 2, 25]
  ┌─────┬──────────┬──────────────────┬──────────┐
  │  i  │ arr[i]   │ Stack (values)   │ NSE[i]   │
  ├─────┼──────────┼──────────────────┼──────────┤
  │  4  │ 25       │ [] → [25]        │ -1       │
  │  3  │ 2        │ pop 25 → [2]     │ -1       │
  │  2  │ 5        │ [2] → [2,5]      │ 2        │
  │  1  │ 8        │ pop 5 → [2,8]    │ 5? NO..  │
  │     │          │ wait—pop ≥ 8?    │          │
  └─────┴──────────┴──────────────────┴──────────┘

  Let me redo carefully:
  i=4: arr=25, stack=[]        → NSE=-1,  push 25  stack=[25]
  i=3: arr=2,  stack=[25]      → pop 25(≥2), stack=[] → NSE=-1, push 2  stack=[2]
  i=2: arr=5,  stack=[2]       → 2<5 → NSE=2, push 5  stack=[2,5]
  i=1: arr=8,  stack=[2,5]     → pop 5(≥8?), 5<8 so 5 is NOT ≥ 8. STOP!
       wait: we pop elements ≥ current. 5 < 8, so don't pop.
       NSE[1] = 5, push 8     stack=[2,5,8]
  i=0: arr=4,  stack=[2,5,8]   → 8≥4? Yes, pop 8. 5≥4? Yes, pop 5.
       2≥4? No → NSE[0]=2, push 4  stack=[2,4]

  Result: [2, 5, 2, -1, -1] ✅

TIME: O(n)  SPACE: O(n)
*/

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// NEXT SMALLER ELEMENT — RIGHT TO LEFT
// ═══════════════════════════════════════════════════════════════

vector<int> nextSmallerElement(vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n);
    stack<int> st;  // Increasing stack (bottom to top)

    for (int i = n - 1; i >= 0; i--) {
        // Pop elements >= current (they can't be "next smaller")
        while (!st.empty() && st.top() >= arr[i]) {
            st.pop();
        }
        result[i] = st.empty() ? -1 : st.top();
        st.push(arr[i]);
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════
// NEXT SMALLER ELEMENT — LEFT TO RIGHT (Index-based)
// ═══════════════════════════════════════════════════════════════

vector<int> nextSmallerLTR(vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n, -1);
    stack<int> st;  // Stores indices, decreasing values

    for (int i = 0; i < n; i++) {
        while (!st.empty() && arr[st.top()] > arr[i]) {
            result[st.top()] = arr[i];
            st.pop();
        }
        st.push(i);
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════
// DEMONSTRATION
// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  NEXT SMALLER ELEMENT (NSE) — MONOTONIC STACK           ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    vector<int> arr = {4, 8, 5, 2, 25};

    cout << "Array:     ";
    for (int x : arr) cout << x << " ";
    cout << "\n";

    auto r1 = nextSmallerElement(arr);
    cout << "NSE (R→L): ";
    for (int x : r1) cout << x << " ";
    cout << "\n";

    auto r2 = nextSmallerLTR(arr);
    cout << "NSE (L→R): ";
    for (int x : r2) cout << x << " ";
    cout << "\n";

    // More test
    vector<int> arr2 = {1, 3, 2, 4, 1, 5};
    cout << "\nArray:     ";
    for (int x : arr2) cout << x << " ";
    cout << "\n";
    auto r3 = nextSmallerElement(arr2);
    cout << "NSE:       ";
    for (int x : r3) cout << x << " ";
    cout << "\n";

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "NGE vs NSE COMPARISON:\n";
    cout << "──────────────────────\n";
    cout << "  NGE: Stack maintains DECREASING order. Pop ≤ current.\n";
    cout << "  NSE: Stack maintains INCREASING order. Pop ≥ current.\n\n";
    cout << "  ┌─────────┬──────────────────┬──────────────────┐\n";
    cout << "  │ Type    │ Stack Order      │ Pop Condition    │\n";
    cout << "  ├─────────┼──────────────────┼──────────────────┤\n";
    cout << "  │ NGE     │ Decreasing ↓     │ Pop if ≤ current │\n";
    cout << "  │ NSE     │ Increasing ↑     │ Pop if ≥ current │\n";
    cout << "  │ PGE     │ Decreasing ↓     │ Pop if ≤ current │\n";
    cout << "  │ PSE     │ Increasing ↑     │ Pop if ≥ current │\n";
    cout << "  └─────────┴──────────────────┴──────────────────┘\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

