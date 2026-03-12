/*
 * ============================================================================
 *         KNAPSACK TRICKS — LARGE WEIGHT, MEET-IN-MIDDLE, VALUE-INDEXED
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Knapsack DP — Advanced Tricks for ICPC
 * Level   : ⭐⭐⭐⭐ Expert / ICPC
 * ============================================================================
 *
 * ICPC KNAPSACK TRICKS:
 * 1. Standard: O(N × W) — works when W ≤ 10^6
 * 2. VALUE-INDEXED: When W is huge but sum of values is small
 *    dp[v] = min weight to achieve value v → O(N × V_sum)
 *    This is AtCoder DP E (Knapsack 2)
 * 3. MEET-IN-MIDDLE KNAPSACK: When N ≤ 40
 *    Split into two halves, enumerate all subsets → O(2^(N/2) × N)
 * 4. MULTIPLE KNAPSACK with Binary Decomposition: O(N × W × log count)
 * 5. BITSET KNAPSACK: O(N × W / 64) using bitset
 * 6. CIRCULAR KNAPSACK: Items arranged in circle, can't take adjacent
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

/*
 * 1. VALUE-INDEXED KNAPSACK (AtCoder DP E)
 *    N items with huge weights (up to 10^9) but small values (v_i ≤ 1000, N ≤ 100)
 *    Standard dp on weight is impossible.
 *    Instead: dp[v] = minimum weight to achieve total value exactly v
 *    Answer: max v such that dp[v] ≤ W
 */
long long valueIndexedKnapsack(vector<int>& wt, vector<int>& val, long long W) {
    int n = wt.size();
    int maxV = 0;
    for (int v : val) maxV += v;

    vector<long long> dp(maxV + 1, LLONG_MAX);
    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        for (int v = maxV; v >= val[i]; v--) {  // 0/1 knapsack, backward
            if (dp[v - val[i]] != LLONG_MAX) {
                dp[v] = min(dp[v], dp[v - val[i]] + wt[i]);
            }
        }
    }

    long long ans = 0;
    for (int v = 0; v <= maxV; v++)
        if (dp[v] <= W) ans = v;
    return ans;
}

/*
 * 2. MEET-IN-MIDDLE KNAPSACK (N ≤ 40)
 *    Split items into two halves.
 *    Generate all 2^(N/2) subsets for each half.
 *    For each left subset: binary search best complement in right.
 *    Time: O(2^(N/2) × N)
 */
long long meetInMiddleKnapsack(vector<int>& wt, vector<int>& val, long long W) {
    int n = wt.size();
    int half = n / 2;

    // Generate all subsets of first half
    int n1 = half, n2 = n - half;
    vector<pair<long long, long long>> left;  // {weight, value}
    for (int mask = 0; mask < (1 << n1); mask++) {
        long long w = 0, v = 0;
        for (int i = 0; i < n1; i++) {
            if (mask & (1 << i)) { w += wt[i]; v += val[i]; }
        }
        if (w <= W) left.push_back({w, v});
    }

    // Generate all subsets of second half
    vector<pair<long long, long long>> right;
    for (int mask = 0; mask < (1 << n2); mask++) {
        long long w = 0, v = 0;
        for (int i = 0; i < n2; i++) {
            if (mask & (1 << i)) { w += wt[half + i]; v += val[half + i]; }
        }
        if (w <= W) right.push_back({w, v});
    }

    // Sort right by weight, maintain max value prefix
    sort(right.begin(), right.end());

    // Remove dominated entries: if right[i].w ≤ right[j].w and right[i].v ≥ right[j].v, keep i
    vector<pair<long long, long long>> filtered;
    long long maxVal = -1;
    for (auto& [w, v] : right) {
        if (v > maxVal) {
            filtered.push_back({w, v});
            maxVal = v;
        }
    }

    // For each left subset, binary search best right complement
    long long ans = 0;
    for (auto& [lw, lv] : left) {
        long long remaining = W - lw;
        // Find largest weight in filtered that ≤ remaining
        int lo = 0, hi = (int)filtered.size() - 1, best = -1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (filtered[mid].first <= remaining) {
                best = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        if (best >= 0)
            ans = max(ans, lv + filtered[best].second);
    }
    return ans;
}

/*
 * 3. BITSET-OPTIMIZED KNAPSACK — O(N × W / 64)
 *    Use bitset to represent which sums are achievable.
 *    Much faster constant factor.
 */
long long bitsetKnapsack(vector<int>& wt, vector<int>& val, int W) {
    // For subset sum (no values, just feasibility):
    bitset<1000001> possible;
    possible[0] = 1;

    for (int w : wt) {
        possible |= (possible << w);  // O(W/64) per item
    }

    // Find max achievable ≤ W
    for (int w = W; w >= 0; w--)
        if (possible[w]) return w;
    return 0;
}

// For actual knapsack with values — need different approach
// Use bitset for each value level (more complex)

/*
 * 4. MULTIPLE KNAPSACK — Binary Decomposition
 *    Item i available count[i] times.
 *    Decompose count[i] into powers of 2: 1, 2, 4, ..., remainder
 *    Each "virtual item" treated as 0/1 knapsack item.
 *    Time: O(N × W × log(max_count))
 */
long long multipleKnapsack(vector<int>& wt, vector<int>& val, vector<int>& cnt, int W) {
    int n = wt.size();
    vector<long long> dp(W + 1, 0);

    for (int i = 0; i < n; i++) {
        int remaining = cnt[i];
        for (int k = 1; remaining > 0; k *= 2) {
            int take = min(k, remaining);
            remaining -= take;
            int item_w = wt[i] * take;
            int item_v = val[i] * take;

            for (int w = W; w >= item_w; w--)
                dp[w] = max(dp[w], dp[w - item_w] + item_v);
        }
    }
    return dp[W];
}

/*
 * 5. FRACTIONAL KNAPSACK vs 0/1 (Comparison)
 *    Fractional: greedy by value/weight ratio — O(n log n)
 *    0/1: DP — O(nW) or harder
 */
double fractionalKnapsack(vector<int>& wt, vector<int>& val, int W) {
    int n = wt.size();
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int a, int b) {
        return (double)val[a] / wt[a] > (double)val[b] / wt[b];
    });

    double totalValue = 0;
    int remaining = W;
    for (int i : idx) {
        if (remaining >= wt[i]) {
            totalValue += val[i];
            remaining -= wt[i];
        } else {
            totalValue += (double)val[i] * remaining / wt[i];
            break;
        }
    }
    return totalValue;
}

/*
 * 6. KNAPSACK WITH CONFLICT GRAPH
 *    Can't take both items i and j if they conflict.
 *    If conflict graph is a tree → tree knapsack.
 *    If conflict graph is arbitrary → NP-hard in general.
 *    For small conflict sets → bitmask DP.
 */

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== KNAPSACK TRICKS ===" << endl;

    // Value-Indexed Knapsack
    vector<int> wt1 = {3, 4, 5};
    vector<int> val1 = {30, 50, 60};
    long long W1 = 8;
    cout << "\n--- Value-Indexed Knapsack ---" << endl;
    cout << "Max value: " << valueIndexedKnapsack(wt1, val1, W1) << endl;

    // Meet-in-Middle Knapsack
    vector<int> wt2 = {2, 3, 5, 7, 1, 4, 1};
    vector<int> val2 = {10, 5, 15, 7, 6, 18, 3};
    long long W2 = 15;
    cout << "\n--- Meet-in-Middle Knapsack ---" << endl;
    cout << "Max value: " << meetInMiddleKnapsack(wt2, val2, W2) << endl;

    // Multiple Knapsack
    vector<int> wt3 = {2, 3, 4};
    vector<int> val3 = {3, 4, 5};
    vector<int> cnt3 = {3, 2, 1};
    cout << "\n--- Multiple Knapsack ---" << endl;
    cout << "Max value (W=10): " << multipleKnapsack(wt3, val3, cnt3, 10) << endl;

    // Bitset Knapsack (subset sum)
    vector<int> items = {3, 7, 1, 8, 2, 5};
    cout << "\n--- Bitset Knapsack (Subset Sum) ---" << endl;
    cout << "Max sum ≤ 15: " << bitsetKnapsack(items, items, 15) << endl;

    // Fractional Knapsack
    cout << "\n--- Fractional vs 0/1 ---" << endl;
    cout << "Fractional: " << fixed << setprecision(2)
         << fractionalKnapsack(wt1, val1, 8) << endl;

    cout << "\n============================================" << endl;
    cout << "  KNAPSACK TRICK SELECTOR:" << endl;
    cout << "  • W small (≤10^6): Standard dp[w]" << endl;
    cout << "  • V_sum small:     Value-indexed dp[v]" << endl;
    cout << "  • N ≤ 40:          Meet-in-Middle" << endl;
    cout << "  • Large N, large W: Bitset O(NW/64)" << endl;
    cout << "  • Item copies:     Binary Decomposition" << endl;
    cout << "  • Fractional:      Greedy (not DP)" << endl;
    cout << "============================================" << endl;

    return 0;
}

