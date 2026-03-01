/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           05 — PREVIOUS SMALLER ELEMENT (PSE)                                ║
║           From Zero to Grandmaster — Classical Stack Problems               ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM:
────────
  For each element, find the nearest SMALLER element to its LEFT.

  Input:  [4, 10, 5, 8, 20, 15, 3, 12]
  Output: [-1, 4, 4, 5, 8, 8, -1, 3]

APPROACH:
────────
  Process LEFT to RIGHT. Stack maintains INCREASING order.
  Pop elements ≥ current. Top (if exists) is PSE.

  DRY RUN: [4, 10, 5, 8, 20, 15, 3, 12]

  i=0: arr=4,  stack=[]        → PSE=-1, push 4   stack=[4]
  i=1: arr=10, stack=[4]       → 4<10 → PSE=4     stack=[4,10]
  i=2: arr=5,  stack=[4,10]    → pop 10(≥5), 4<5 → PSE=4  stack=[4,5]
  i=3: arr=8,  stack=[4,5]     → 5<8 → PSE=5      stack=[4,5,8]
  i=4: arr=20, stack=[4,5,8]   → 8<20 → PSE=8     stack=[4,5,8,20]
  i=5: arr=15, stack=[4,5,8,20]→ pop 20(≥15), 8<15 → PSE=8 stack=[4,5,8,15]
  i=6: arr=3,  stack=[4,5,8,15]→ pop all(≥3) → PSE=-1     stack=[3]
  i=7: arr=12, stack=[3]       → 3<12 → PSE=3     stack=[3,12]

  Result: [-1, 4, 4, 5, 8, 8, -1, 3] ✅

  This is used in:
    - Stock Span Problem (PSE variant)
    - Largest Rectangle in Histogram
    - Sum of Subarray Minimums

TIME: O(n)  SPACE: O(n)
*/

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// Previous Smaller Element (values)
vector<int> previousSmallerElement(vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n);
    stack<int> st;  // Increasing stack

    for (int i = 0; i < n; i++) {
        while (!st.empty() && st.top() >= arr[i]) {
            st.pop();
        }
        result[i] = st.empty() ? -1 : st.top();
        st.push(arr[i]);
    }
    return result;
}

// Previous Smaller Element (indices) — useful for histogram, etc.
vector<int> previousSmallerIndex(vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n);
    stack<int> st;  // Stores indices

    for (int i = 0; i < n; i++) {
        while (!st.empty() && arr[st.top()] >= arr[i]) {
            st.pop();
        }
        result[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════
// CSES 1645 — NEAREST SMALLER VALUES (LEFT)
// ═══════════════════════════════════════════════════════════════
/*
  For each position, print the position of nearest smaller element to the left.
  If none, print 0. (1-indexed)
*/

void solveCSES() {
    cout << "═══ CSES 1645: NEAREST SMALLER VALUES ═══\n\n";

    vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6};
    int n = arr.size();
    stack<int> st;  // Stores 0-indexed positions

    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n";
    cout << "PSE positions (1-indexed): ";

    for (int i = 0; i < n; i++) {
        while (!st.empty() && arr[st.top()] >= arr[i]) {
            st.pop();
        }
        cout << (st.empty() ? 0 : st.top() + 1) << " ";
        st.push(i);
    }
    cout << "\n\n";
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  PREVIOUS SMALLER ELEMENT (PSE)                         ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    vector<int> arr = {4, 10, 5, 8, 20, 15, 3, 12};

    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n";

    auto r = previousSmallerElement(arr);
    cout << "PSE:   ";
    for (int x : r) cout << x << " ";
    cout << "\n";

    auto ri = previousSmallerIndex(arr);
    cout << "PSE idx: ";
    for (int x : ri) cout << x << " ";
    cout << "\n\n";

    solveCSES();

    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE: CSES 1645 — Nearest Smaller Values\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

