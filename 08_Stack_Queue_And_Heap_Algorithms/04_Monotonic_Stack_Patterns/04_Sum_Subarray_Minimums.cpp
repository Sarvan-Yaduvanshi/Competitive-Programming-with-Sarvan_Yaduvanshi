/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           04 — SUM OF SUBARRAY MINIMUMS (LC 907)                             ║
║           From Zero to Grandmaster — Monotonic Stack Patterns               ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: Find sum of min(subarray) for all subarrays. Return mod 10^9+7.
  Input: [3, 1, 2, 4]  Answer: 17
  Subarrays and their mins:
    [3]=3, [1]=1, [2]=2, [4]=4
    [3,1]=1, [1,2]=1, [2,4]=2
    [3,1,2]=1, [1,2,4]=1
    [3,1,2,4]=1
  Sum = 3+1+2+4+1+1+2+1+1+1 = 17

CONTRIBUTION TECHNIQUE:
──────────────────────
  For each element arr[i], count how many subarrays have arr[i] as minimum.

  Let left[i]  = distance to Previous Smaller or Equal Element (or left boundary)
  Let right[i] = distance to Next Strictly Smaller Element (or right boundary)

  Contribution of arr[i] = arr[i] × left[i] × right[i]

  Why different strictness? To avoid double counting!
    PSE: use strictly smaller (<) — left boundary is EXCLUSIVE
    NSE: use smaller or equal (<=) for left, strictly smaller (<) for right
    (Or flip: one side strict, one side non-strict)

DRY RUN: [3, 1, 2, 4]
  PSE indices (strictly <):   [-1, -1, 1, 2]
  NSE indices (strictly <):   [1, 4, 4, 4]

  i=0: left=0-(-1)=1, right=1-0=1, contrib=3×1×1=3
  i=1: left=1-(-1)=2, right=4-1=3, contrib=1×2×3=6
  i=2: left=2-1=1,    right=4-2=2, contrib=2×1×2=4
  i=3: left=3-2=1,    right=4-3=1, contrib=4×1×1=4

  Total = 3+6+4+4 = 17 ✅

TIME: O(n)  SPACE: O(n)
*/

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;

long long sumSubarrayMins(vector<int>& arr) {
    int n = arr.size();
    vector<int> pse(n), nse(n);
    stack<int> st;

    // PSE: Previous Smaller Element (strictly smaller)
    for (int i = 0; i < n; i++) {
        while (!st.empty() && arr[st.top()] >= arr[i]) st.pop();
        pse[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }

    while (!st.empty()) st.pop();

    // NSE: Next Smaller Element (strictly smaller)
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && arr[st.top()] > arr[i]) st.pop();  // strictly >
        nse[i] = st.empty() ? n : st.top();
        st.push(i);
    }

    long long total = 0;
    for (int i = 0; i < n; i++) {
        long long left = i - pse[i];
        long long right = nse[i] - i;
        total = (total + (long long)arr[i] % MOD * left % MOD * right % MOD) % MOD;
    }
    return total;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: SUM OF SUBARRAY MAXIMUMS (Mirror problem)
// ═══════════════════════════════════════════════════════════════

long long sumSubarrayMaxs(vector<int>& arr) {
    int n = arr.size();
    vector<int> pge(n), nge(n);
    stack<int> st;

    // PGE: Previous Greater Element (strictly greater)
    for (int i = 0; i < n; i++) {
        while (!st.empty() && arr[st.top()] <= arr[i]) st.pop();
        pge[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    while (!st.empty()) st.pop();

    // NGE: Next Greater Element (strictly greater)
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && arr[st.top()] < arr[i]) st.pop();
        nge[i] = st.empty() ? n : st.top();
        st.push(i);
    }

    long long total = 0;
    for (int i = 0; i < n; i++) {
        long long left = i - pge[i];
        long long right = nge[i] - i;
        total = (total + (long long)arr[i] % MOD * left % MOD * right % MOD) % MOD;
    }
    return total;
}

// Sum of (max - min) of all subarrays = sumMax - sumMin
long long sumSubarrayRanges(vector<int>& arr) {
    return sumSubarrayMaxs(arr) - sumSubarrayMins(arr);
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  SUM OF SUBARRAY MINIMUMS & MAXIMUMS                     ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    vector<int> arr = {3, 1, 2, 4};
    cout << "Array: [3, 1, 2, 4]\n";
    cout << "Sum of subarray minimums: " << sumSubarrayMins(arr) << "\n";
    cout << "Sum of subarray maximums: " << sumSubarrayMaxs(arr) << "\n";
    cout << "Sum of subarray ranges:   " << sumSubarrayRanges(arr) << "\n\n";

    vector<int> arr2 = {11, 81, 94, 43, 3};
    cout << "Array: [11, 81, 94, 43, 3]\n";
    cout << "Sum of subarray minimums: " << sumSubarrayMins(arr2) << "\n";

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE:\n";
    cout << "  LC 907  — Sum of Subarray Minimums\n";
    cout << "  LC 2104 — Sum of Subarray Ranges\n";
    cout << "  LC 2281 — Sum of Total Strength of Wizards (HARD)\n";
    cout << "═══════════════════════════════════════════════════════════\n";
    return 0;
}

