/*
 * ============================================================================
 *      DP OPTIMIZATION — DIVIDE & CONQUER + KNUTH OPTIMIZATION
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : DP Optimization — D&C DP, Knuth's Optimization
 * Level   : ⭐⭐⭐⭐ Expert / GM
 * ============================================================================
 *
 * DIVIDE & CONQUER OPTIMIZATION:
 * ===============================
 * When: dp[i][j] = min over k { dp[i-1][k] + cost(k+1, j) }
 * Condition: opt[i][j] ≤ opt[i][j+1]  (optimal split point is monotone)
 *            i.e., cost function satisfies "quadrangle inequality"
 *
 * Instead of O(n²) per row → O(n log n) per row using D&C.
 * Total: O(k * n * log n) instead of O(k * n²)
 *
 * KNUTH'S OPTIMIZATION:
 * ======================
 * When: dp[i][j] = min over k in [i,j) { dp[i][k] + dp[k+1][j] + cost(i,j) }
 * Condition: opt[i][j-1] ≤ opt[i][j] ≤ opt[i+1][j]
 *            (quadrangle inequality on cost)
 *
 * Reduces O(n³) → O(n²) by constraining the search range for k.
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

/*
 * ============================================================
 * DIVIDE & CONQUER DP OPTIMIZATION
 * ============================================================
 *
 * Problem: Split array into k groups to minimize total cost.
 * dp[g][j] = min cost using g groups for first j elements
 * dp[g][j] = min over p { dp[g-1][p] + cost(p+1, j) }
 *
 * If opt(g, j) ≤ opt(g, j+1), use D&C.
 */
long long prefix[100005];
int arr_dc[100005];
int n_dc;

// cost(l, r) = sum of (r - l + 1 - freq) for each element
// For simplicity, use sum-of-squares cost as example
long long cost(int l, int r) {
    long long sum = prefix[r] - prefix[l - 1];
    return sum * sum;  // Example cost function
}

long long dp_dc[25][100005];  // dp[group][position]

void solve_dc(int g, int lo, int hi, int optLo, int optHi) {
    if (lo > hi) return;
    int mid = (lo + hi) / 2;

    long long best = LLONG_MAX;
    int opt = optLo;

    for (int k = optLo; k <= min(mid - 1, optHi); k++) {
        long long val = dp_dc[g - 1][k] + cost(k + 1, mid);
        if (val < best) {
            best = val;
            opt = k;
        }
    }

    dp_dc[g][mid] = best;

    // Recurse: left half has opt in [optLo, opt], right has [opt, optHi]
    solve_dc(g, lo, mid - 1, optLo, opt);
    solve_dc(g, mid + 1, hi, opt, optHi);
}

long long divideConquerDP(int n, int k) {
    // Base: g=1, dp[1][j] = cost(1, j)
    for (int j = 1; j <= n; j++)
        dp_dc[1][j] = cost(1, j);

    for (int g = 2; g <= k; g++) {
        solve_dc(g, g, n, g - 1, n);
    }
    return dp_dc[k][n];
}

/*
 * ============================================================
 * KNUTH'S OPTIMIZATION
 * ============================================================
 *
 * Interval DP: dp[i][j] = min(dp[i][k] + dp[k+1][j]) + w(i,j)
 * If w satisfies quadrangle inequality and monotonicity:
 *   opt[i][j-1] ≤ opt[i][j] ≤ opt[i+1][j]
 *
 * Example: Optimal BST / Stone merging
 */
int knuthOptDP(vector<int>& freq) {
    int n = freq.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    vector<vector<int>> opt(n, vector<int>(n, 0));
    vector<int> pre(n + 1, 0);

    for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + freq[i];

    auto w = [&](int i, int j) { return pre[j + 1] - pre[i]; };

    // Base: single elements
    for (int i = 0; i < n; i++) {
        dp[i][i] = freq[i];
        opt[i][i] = i;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;

            // Knuth's optimization: search only in [opt[i][j-1], opt[i+1][j]]
            int lo = opt[i][j - 1];
            int hi = (j + 1 < n) ? opt[i + 1][j] : j;

            for (int k = lo; k <= hi; k++) {
                int left = (k > i) ? dp[i][k - 1] : 0;
                int right = (k < j) ? dp[k + 1][j] : 0;
                int val = left + right + w(i, j);

                if (val < dp[i][j]) {
                    dp[i][j] = val;
                    opt[i][j] = k;
                }
            }
        }
    }
    return dp[0][n - 1];
}

/*
 * ============================================================
 * MONOTONIC QUEUE / DEQUE OPTIMIZATION
 * ============================================================
 *
 * When: dp[i] = min/max(dp[j] + cost(j, i)) where j ∈ [i-w, i-1]
 * (sliding window on j)
 *
 * Use monotonic deque to maintain candidates.
 * Time: O(n) instead of O(n*w)
 */
vector<int> slidingWindowDP(vector<int>& arr, int w) {
    int n = arr.size();
    vector<int> dp(n);
    deque<int> dq;  // Stores indices, maintains dp[j] in increasing order

    dp[0] = arr[0];
    dq.push_back(0);

    for (int i = 1; i < n; i++) {
        // Remove expired elements
        while (!dq.empty() && dq.front() < i - w)
            dq.pop_front();

        dp[i] = dp[dq.front()] + arr[i];

        // Maintain monotonicity
        while (!dq.empty() && dp[dq.back()] >= dp[i])
            dq.pop_back();
        dq.push_back(i);
    }
    return dp;
}

/*
 * ============================================================
 * SLOPE TRICK (Brief Introduction)
 * ============================================================
 *
 * Maintain the DP function as a piecewise-linear convex function.
 * Track using two priority queues (slopes from left and right).
 *
 * Classic: "Make array non-decreasing with min cost"
 * dp[i][v] = min cost to make a[0..i] non-decreasing, a[i] = v
 *
 * Key observation: dp function is convex and piecewise linear.
 * We only need to track the "breakpoints" (where slope changes).
 */
long long slopeTrickMinCost(vector<int>& a) {
    int n = a.size();
    long long ans = 0;
    priority_queue<long long> L;  // Max-heap: left slopes breakpoints

    for (int i = 0; i < n; i++) {
        L.push(a[i]);
        if (L.top() > a[i]) {
            ans += L.top() - a[i];
            L.pop();
            L.push(a[i]);
        }
    }
    return ans;
}

/*
 * ============================================================
 * ALIENS TRICK (Lambda/Penalty Optimization)
 * ============================================================
 *
 * Problem: Minimize f(x) subject to using exactly k items.
 * Trick: Remove the constraint by adding penalty λ per item.
 *   g(λ) = min_x { f(x) + λ*x }
 * Binary search on λ to find where optimal x = k.
 *
 * Converts O(n²) to O(n log n) or O(n log² n).
 *
 * Example: "Divide array into exactly k subarrays, minimize cost"
 * Add λ per subarray, binary search on λ.
 */

// Simplified illustration: check if with penalty lambda, we use ≤ k groups
pair<long long, int> aliensSolve(vector<int>& arr, int n, long long lambda) {
    // dp[i] = min cost for arr[0..i-1] with lambda per group
    vector<long long> dp(n + 1, LLONG_MAX);
    vector<int> groups(n + 1, 0);
    dp[0] = 0;
    groups[0] = 0;

    for (int i = 1; i <= n; i++) {
        long long sum = 0;
        for (int j = i; j >= 1; j--) {
            sum += arr[j - 1];
            long long val = dp[j - 1] + sum * sum + lambda;
            if (val < dp[i]) {
                dp[i] = val;
                groups[i] = groups[j - 1] + 1;
            }
        }
    }
    return {dp[n], groups[n]};
}

long long aliensTrick(vector<int>& arr, int n, int k) {
    long long lo = 0, hi = 1e18;
    long long ans = LLONG_MAX;

    while (lo <= hi) {
        long long mid = (lo + hi) / 2;
        auto [cost, cnt] = aliensSolve(arr, n, mid);

        if (cnt <= k) {
            ans = min(ans, cost - (long long)k * mid);
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== DP OPTIMIZATION TECHNIQUES ===" << endl;

    // D&C DP Example
    n_dc = 8;
    int arr[] = {0, 1, 3, 5, 2, 4, 6, 8, 1};  // 1-indexed
    prefix[0] = 0;
    for (int i = 1; i <= n_dc; i++) {
        arr_dc[i] = arr[i];
        prefix[i] = prefix[i-1] + arr[i];
    }
    cout << "\n--- D&C DP (3 groups) ---" << endl;
    cout << "Min cost: " << divideConquerDP(n_dc, 3) << endl;

    // Knuth's Optimization
    vector<int> freq = {34, 8, 50};
    cout << "\n--- Knuth's Optimization (Optimal BST) ---" << endl;
    cout << "Min cost: " << knuthOptDP(freq) << endl;

    // Slope Trick
    vector<int> slope_arr = {3, 1, 2, 5, 4};
    cout << "\n--- Slope Trick (Make Non-Decreasing) ---" << endl;
    cout << "Min cost: " << slopeTrickMinCost(slope_arr) << endl;

    cout << "\n============================================" << endl;
    cout << "  OPTIMIZATION CHEAT SHEET:" << endl;
    cout << "  • CHT:     dp[i] = min(dp[j] + b[j]*a[i])" << endl;
    cout << "  • D&C:     opt(i,j) ≤ opt(i,j+1)" << endl;
    cout << "  • Knuth:   opt(i,j-1) ≤ opt(i,j) ≤ opt(i+1,j)" << endl;
    cout << "  • MonoQ:   sliding window on j" << endl;
    cout << "  • Slope:   convex piecewise-linear dp" << endl;
    cout << "  • Aliens:  exact-k constraint → binary search" << endl;
    cout << "============================================" << endl;

    return 0;
}

