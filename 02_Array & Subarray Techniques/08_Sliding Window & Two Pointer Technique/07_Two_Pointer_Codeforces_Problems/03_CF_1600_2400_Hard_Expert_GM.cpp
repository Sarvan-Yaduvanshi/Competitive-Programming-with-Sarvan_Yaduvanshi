/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Codeforces Two Pointer — Hard (1600-2000)
 *  Level   : Hard
 * ============================================================================
 *
 *  CF 1849D — Array Painting (1700)
 *             https://codeforces.com/problemset/problem/1849/D
 *             Greedy + Two Pointer segment analysis
 *
 *  CF 1695C — Zero Path (1700)
 *             https://codeforces.com/problemset/problem/1695/C
 *             DP + range check
 *
 *  CF 1537D — Deleting Divisors (1700)
 *             https://codeforces.com/problemset/problem/1537/D
 *
 * ============================================================================
 *
 *  CF 2000-2400+ (Expert/GM):
 *
 *  CF 1548B — Integers Have Friends (2000) — GCD + Sliding Window
 *             https://codeforces.com/problemset/problem/1548/B
 *             Longest subarray where consecutive diffs share GCD > 1
 *
 *  CF 1608D — Dominoes (2100)
 *             https://codeforces.com/problemset/problem/1608/D
 *
 *  CF 1523D — Love-Hate (2400)
 *             https://codeforces.com/problemset/problem/1523/D
 *             Randomization + bitmask + two pointer
 *
 *  CF 1809E — Two Tanks (2200)
 *             https://codeforces.com/problemset/problem/1809/E
 *             Simulation with two pointer optimization
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
using ll = long long;

// ============================================================================
// CF 1548B: Integers Have Friends (2000) — GCD + Sliding Window
// Find longest subarray where all consecutive differences share GCD > 1
// ============================================================================
/*
 * IDEA:
 * 1. Compute diff[i] = |a[i] - a[i-1]| for i ≥ 1
 * 2. Find longest subarray in diff[] where GCD of all elements > 1
 * 3. Use sparse table for range GCD + two pointer / binary search
 *
 * Answer = longest such subarray length + 1 (original array length)
 */

// Sparse Table for range GCD
struct SparseTable {
    vector<vector<ll>> table;
    vector<int> lg;
    int n;

    void build(vector<ll>& a) {
        n = a.size();
        int LOG = 1;
        while ((1 << LOG) <= n) LOG++;
        table.assign(LOG, vector<ll>(n));
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;

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

        int best = 1;
        int left = 0;
        for (int right = 0; right < n - 1; right++) {
            while (left <= right && st.query(left, right) == 1)
                left++;
            best = max(best, right - left + 2); // +2 for original array
        }
        cout << best << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // solve_1548B();

    return 0;
}

