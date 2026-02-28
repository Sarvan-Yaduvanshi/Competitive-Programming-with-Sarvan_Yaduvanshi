/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Fixed Window + GCD / LCM
 *  Level   : Medium → Hard (CF 1600 → 2000)
 * ============================================================================
 *
 *  ▶ KEY CHALLENGE:
 *  ────────────────
 *  GCD and LCM are NOT easily "removable" from a window.
 *  - GCD: gcd(a,b) is associative, but you can't un-gcd easily.
 *  - LCM: lcm(a,b) is associative, but you can't un-lcm easily.
 *
 *  ▶ SOLUTIONS:
 *  ────────────
 *  1. Sparse Table: Precompute GCD/LCM for all ranges in O(N log N),
 *     then query any window in O(1). Best for static arrays.
 *  2. Segment Tree: Build in O(N), query in O(log N). Supports updates.
 *  3. Two-Stack Trick: Use two stacks to simulate a deque-like structure
 *     that supports GCD/LCM queries in amortized O(1).
 *  4. Suffix GCD Array: For each starting point, GCD can only decrease/stay.
 *     Number of distinct GCD values from any starting point is O(log max).
 *
 *  PROBLEMS:
 *  LC 1862 — Sum of Floored Pairs (related to GCD concepts)
 *            https://leetcode.com/problems/sum-of-floored-pairs/
 *  CF 475D — CGCDSSQ (count subarrays with GCD = X, 1800)
 *            https://codeforces.com/problemset/problem/475/D
 *  CF 1548B — Integers Have Friends (GCD of differences + sliding window, 2000)
 *            https://codeforces.com/problemset/problem/1548/B
 *  GFG     — GCD of all subarrays of size K
 *            https://practice.geeksforgeeks.org/problems/gcd-of-all-subarrays-of-size-k/
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stack>
#include <cmath>
using namespace std;
using ll = long long;

// ============================================================================
// APPROACH 1: Sparse Table for GCD — O(N log N) build, O(1) query
// ============================================================================
/*
 * sp[j][i] = GCD of arr[i .. i + 2^j - 1]
 * Base: sp[0][i] = arr[i]
 * Transition: sp[j][i] = gcd(sp[j-1][i], sp[j-1][i + 2^(j-1)])
 * Query [l, r]: k = log2(r-l+1), gcd(sp[k][l], sp[k][r - 2^k + 1])
 */
struct SparseTableGCD {
    vector<vector<int>> sp;
    vector<int> logTable;
    int n;

    void build(vector<int>& arr) {
        n = arr.size();
        int LOG = __lg(n) + 1;
        sp.assign(LOG, vector<int>(n));
        logTable.resize(n + 1);

        for (int i = 2; i <= n; i++) logTable[i] = logTable[i / 2] + 1;
        for (int i = 0; i < n; i++) sp[0][i] = arr[i];

        for (int j = 1; j < LOG; j++)
            for (int i = 0; i + (1 << j) - 1 < n; i++)
                sp[j][i] = __gcd(sp[j - 1][i], sp[j - 1][i + (1 << (j - 1))]);
    }

    int query(int l, int r) {
        int k = logTable[r - l + 1];
        return __gcd(sp[k][l], sp[k][r - (1 << k) + 1]);
    }
};

// GCD of every window of size K using Sparse Table
vector<int> gcdEveryWindowSparse(vector<int>& arr, int k) {
    SparseTableGCD st;
    st.build(arr);
    vector<int> result;
    for (int i = 0; i + k - 1 < (int)arr.size(); i++)
        result.push_back(st.query(i, i + k - 1));
    return result;
}

// ============================================================================
// APPROACH 2: Two-Stack Trick for Sliding Window GCD — Amortized O(1)
// ============================================================================
/*
 * Simulate a queue using two stacks. Each stack element stores (value, prefix_gcd).
 * Push to back stack. Pop from front stack (refill from back if empty).
 * Current GCD = gcd(front_stack.top().gcd, back_stack.top().gcd)
 *
 * Amortized O(1) per operation. Total O(N).
 */
struct SlidingGCD {
    stack<pair<int,int>> front, back; // (value, cumulative_gcd)

    void pushBack(int val) {
        int g = back.empty() ? val : __gcd(back.top().second, val);
        back.push({val, g});
    }

    void popFront() {
        if (front.empty()) {
            // Transfer all from back to front
            while (!back.empty()) {
                int val = back.top().first; back.pop();
                int g = front.empty() ? val : __gcd(front.top().second, val);
                front.push({val, g});
            }
        }
        front.pop();
    }

    int getGCD() {
        if (front.empty() && back.empty()) return 0;
        if (front.empty()) return back.top().second;
        if (back.empty()) return front.top().second;
        return __gcd(front.top().second, back.top().second);
    }
};

vector<int> gcdEveryWindowTwoStack(vector<int>& arr, int k) {
    int n = arr.size();
    SlidingGCD sg;
    vector<int> result;

    for (int i = 0; i < n; i++) {
        sg.pushBack(arr[i]);
        if (i >= k) sg.popFront();
        if (i >= k - 1) result.push_back(sg.getGCD());
    }
    return result;
}

// ============================================================================
// LCM of Every Window of Size K — Using Two-Stack (same idea)
// ============================================================================
/*
 * WARNING: LCM can overflow for large values! Use __int128 or check.
 * Same two-stack structure but replace gcd with lcm.
 */
ll safeLCM(ll a, ll b) {
    if (a == 0 || b == 0) return 0;
    return a / __gcd(a, b) * b;
}

struct SlidingLCM {
    stack<pair<ll, ll>> front, back;

    void pushBack(ll val) {
        ll l = back.empty() ? val : safeLCM(back.top().second, val);
        back.push({val, l});
    }

    void popFront() {
        if (front.empty()) {
            while (!back.empty()) {
                ll val = back.top().first; back.pop();
                ll l = front.empty() ? val : safeLCM(front.top().second, val);
                front.push({val, l});
            }
        }
        front.pop();
    }

    ll getLCM() {
        if (front.empty() && back.empty()) return 1;
        if (front.empty()) return back.top().second;
        if (back.empty()) return front.top().second;
        return safeLCM(front.top().second, back.top().second);
    }
};

// ============================================================================
// CF 1548B: Integers Have Friends — GCD of diff array + sliding window
// ============================================================================
/*
 * Find longest subarray where all elements have same remainder mod some m > 1.
 * Equivalent: all |a[i+1] - a[i]| share a GCD > 1 in that subarray.
 *
 * Build diff array: d[i] = |a[i+1] - a[i]|.
 * Find longest subarray of d with GCD > 1.
 * Use sparse table or two-stack GCD + two pointer.
 *
 * Answer for original array = longest window in diff + 1.
 */
void solve_CF1548B() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<ll> a(n);
        for (auto& x : a) cin >> x;

        if (n == 1) { cout << 1 << "\n"; continue; }

        vector<int> d(n - 1);
        for (int i = 0; i < n - 1; i++)
            d[i] = (int)abs(a[i + 1] - a[i]);

        // Find longest subarray of d with GCD > 1 using two-stack
        SlidingGCD sg;
        int best = 1, left = 0;
        for (int right = 0; right < (int)d.size(); right++) {
            sg.pushBack(d[right]);
            while (sg.getGCD() <= 1 && left <= right) {
                sg.popFront();
                left++;
            }
            best = max(best, right - left + 2); // +2 because diff array is n-1
        }
        cout << best << "\n";
    }
}

int main() {
    // GCD of every window using Sparse Table
    vector<int> arr = {12, 8, 18, 6, 24};
    auto g1 = gcdEveryWindowSparse(arr, 3);
    cout << "GCD windows (sparse, k=3): ";
    for (int x : g1) cout << x << " ";
    cout << "\n"; // gcd(12,8,18)=2, gcd(8,18,6)=2, gcd(18,6,24)=6

    // GCD of every window using Two-Stack
    auto g2 = gcdEveryWindowTwoStack(arr, 3);
    cout << "GCD windows (2stack, k=3): ";
    for (int x : g2) cout << x << " ";
    cout << "\n"; // Same: 2 2 6

    return 0;
}

