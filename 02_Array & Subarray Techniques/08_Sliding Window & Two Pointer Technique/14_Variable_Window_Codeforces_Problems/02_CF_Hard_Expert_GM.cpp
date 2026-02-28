/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Codeforces Variable Sliding Window — Hard / Expert / GM
 *  Level   : 1600 → 2400+
 * ============================================================================
 *
 *  CF 1548B — Integers Have Friends (2000) — GCD + Sliding Window
 *             https://codeforces.com/problemset/problem/1548/B
 *             Longest subarray where consecutive diffs share GCD > 1
 *
 *  CF 1918D — Blocking Elements (2400) — Binary Search + Sliding Window DP
 *             https://codeforces.com/problemset/problem/1918/D
 *
 *  CF 1409E — Two Platforms (1800) — Sort + Prefix + Sliding Window
 *             https://codeforces.com/problemset/problem/1409/E
 *
 *  CF 1915F — Grading (1800) — Sort + Sliding Window
 *             https://codeforces.com/problemset/problem/1915/F
 *
 *  CF 1709D — Rorororobot (2000) — Sparse Table + Two Pointer
 *             https://codeforces.com/problemset/problem/1709/D
 *
 *  CF 1695D — Tree Queries (2300) — DFS + Two Pointer
 *             https://codeforces.com/problemset/problem/1695/D
 *
 *  CF 1537E2 — Erase and Extend Hard (2100) — String + SW
 *              https://codeforces.com/problemset/problem/1537/E2
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <deque>
using namespace std;
using ll = long long;

// ============================================================================
// CF 1548B: Integers Have Friends (2000)
// ============================================================================
/*
 * Find longest subarray where all elements give same remainder mod some m > 1.
 * Equivalent: consecutive diffs d[i] = |a[i+1]-a[i]| share GCD > 1.
 *
 * Use Sparse Table for range GCD, then two pointer:
 * Expand right. If range GCD becomes 1, move left.
 */

struct SparseTable {
    vector<vector<ll>> table;
    vector<int> lg;

    void build(vector<ll>& a) {
        int n = a.size();
        int LOG = 1;
        while ((1 << LOG) <= n) LOG++;
        table.assign(LOG, vector<ll>(n));
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i/2] + 1;
        for (int i = 0; i < n; i++) table[0][i] = a[i];
        for (int j = 1; j < LOG; j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                table[j][i] = __gcd(table[j-1][i], table[j-1][i + (1 << (j-1))]);
    }

    ll query(int l, int r) {
        int k = lg[r - l + 1];
        return __gcd(table[k][l], table[k][r - (1 << k) + 1]);
    }
};

void solve_1548B() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<ll> a(n);
        for (auto& x : a) cin >> x;

        if (n == 1) { cout << 1 << "\n"; continue; }

        vector<ll> diff(n - 1);
        for (int i = 0; i < n - 1; i++)
            diff[i] = abs(a[i+1] - a[i]);

        SparseTable st;
        st.build(diff);

        int best = 1, left = 0;
        for (int right = 0; right < n - 1; right++) {
            while (left <= right && st.query(left, right) == 1)
                left++;
            best = max(best, right - left + 2);
        }
        cout << best << "\n";
    }
}

// ============================================================================
// CF 1918D: Blocking Elements (2400) — BS + SW DP
// ============================================================================
/*
 * Given array a of N elements. Choose blocking indices b1 < b2 < ... < bk.
 * Cost = max(a[b1] + a[b2] + ... + a[bk], max(segment sums between blockers))
 * Minimize the cost.
 *
 * Binary search on cost C. Check: can we choose blockers such that
 * - sum of blockers ≤ C
 * - every segment between blockers has sum ≤ C
 *
 * DP + sliding window deque to check feasibility in O(N).
 *
 * dp[i] = min sum of blockers ending at position i, such that
 * all constraints are met.
 *
 * Transition: dp[i] = a[i] + min(dp[j]) for all j where prefix[i-1]-prefix[j] ≤ C
 * Use deque to maintain minimum dp[j] in the valid range.
 */
void solve_1918D() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (auto& x : a) cin >> x;

    vector<ll> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) prefix[i+1] = prefix[i] + a[i];

    auto check = [&](ll C) -> bool {
        // dp[i] = min total blocker cost to block up to index i (0-indexed into a, positions 1..n)
        // Add virtual blockers at position 0 and n+1
        // dp[-1] = 0 (virtual start), need dp[n] ≤ C (virtual end)

        vector<ll> dp(n + 2, 1e18);
        dp[0] = 0; // Virtual blocker before array

        deque<int> dq;
        dq.push_back(0);

        for (int i = 1; i <= n + 1; i++) {
            // j is valid if prefix[i-1] - prefix[j] ≤ C → prefix[j] ≥ prefix[i-1] - C
            // Remove from front if segment sum too large
            while (!dq.empty() && prefix[i-1] - prefix[dq.front()] > C)
                dq.pop_front();

            if (!dq.empty()) {
                ll cost = (i <= n) ? a[i-1] : 0; // blocker cost (0 for virtual end)
                dp[i] = dp[dq.front()] + cost;
            }

            // Maintain deque as minimum of dp values
            if (i <= n) {
                while (!dq.empty() && dp[dq.back()] >= dp[i])
                    dq.pop_back();
                dq.push_back(i);
            }
        }
        return dp[n + 1] <= C;
    };

    ll lo = 0, hi = prefix[n];
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        if (check(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Uncomment to test:
    // solve_1548B();
    // solve_1918D();

    return 0;
}

