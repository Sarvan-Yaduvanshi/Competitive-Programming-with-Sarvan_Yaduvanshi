/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           04 — PREVIOUS GREATER ELEMENT (PGE)                                ║
║           From Zero to Grandmaster — Classical Stack Problems               ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM:
────────
  For each element, find the nearest GREATER element to its LEFT.
  If none, answer is -1.

  Input:  [10, 4, 2, 20, 40, 12, 30]
  Output: [-1, 10, 4, -1, -1, 40, 40]

APPROACH:
────────
  Process LEFT to RIGHT. Stack maintains DECREASING order.
  For each element, pop all ≤ current. Top (if exists) is PGE.

  DRY RUN: [10, 4, 2, 20, 40, 12, 30]

  i=0: arr=10, stack=[]           → PGE=-1, push 10      stack=[10]
  i=1: arr=4,  stack=[10]         → 10>4 → PGE=10, push 4 stack=[10,4]
  i=2: arr=2,  stack=[10,4]       → 4>2 → PGE=4, push 2   stack=[10,4,2]
  i=3: arr=20, stack=[10,4,2]     → pop 2,4,10(≤20)        stack=[]
                                   → PGE=-1, push 20       stack=[20]
  i=4: arr=40, stack=[20]         → pop 20(≤40)            stack=[]
                                   → PGE=-1, push 40       stack=[40]
  i=5: arr=12, stack=[40]         → 40>12 → PGE=40         stack=[40,12]
  i=6: arr=30, stack=[40,12]      → pop 12(≤30), 40>30
                                   → PGE=40, push 30       stack=[40,30]

  Result: [-1, 10, 4, -1, -1, 40, 40] ✅

TIME: O(n)  SPACE: O(n)
*/

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

vector<int> previousGreaterElement(vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n);
    stack<int> st;  // Decreasing stack

    for (int i = 0; i < n; i++) {
        while (!st.empty() && st.top() <= arr[i]) {
            st.pop();
        }
        result[i] = st.empty() ? -1 : st.top();
        st.push(arr[i]);
    }
    return result;
}

// Return indices instead of values
vector<int> previousGreaterIndex(vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n);
    stack<int> st;  // Stores indices

    for (int i = 0; i < n; i++) {
        while (!st.empty() && arr[st.top()] <= arr[i]) {
            st.pop();
        }
        result[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    return result;
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  PREVIOUS GREATER ELEMENT (PGE)                         ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    vector<int> arr = {10, 4, 2, 20, 40, 12, 30};

    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n";

    auto r1 = previousGreaterElement(arr);
    cout << "PGE:   ";
    for (int x : r1) cout << x << " ";
    cout << "\n";

    auto r2 = previousGreaterIndex(arr);
    cout << "PGE idx: ";
    for (int x : r2) cout << x << " ";
    cout << "\n";

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "ALL 4 PATTERNS SUMMARY:\n";
    cout << "───────────────────────\n";
    cout << "  ┌────────┬───────────┬──────────────┬───────────────┐\n";
    cout << "  │ Type   │ Direction │ Stack Order  │ Pop Condition │\n";
    cout << "  ├────────┼───────────┼──────────────┼───────────────┤\n";
    cout << "  │ NGE    │ R → L     │ Decreasing ↓ │ Pop ≤ curr   │\n";
    cout << "  │ NSE    │ R → L     │ Increasing ↑ │ Pop ≥ curr   │\n";
    cout << "  │ PGE    │ L → R     │ Decreasing ↓ │ Pop ≤ curr   │\n";
    cout << "  │ PSE    │ L → R     │ Increasing ↑ │ Pop ≥ curr   │\n";
    cout << "  └────────┴───────────┴──────────────┴───────────────┘\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

