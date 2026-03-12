/*
 * ============================================================================
 *          HARDCORE DP — DP WITH SEGMENT TREE & FENWICK TREE
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Hardcore DP — DP + Segment Tree, DP + BIT
 * Level   : ⭐⭐⭐⭐⭐ Grandmaster / ICPC
 * ============================================================================
 *
 * DP WITH DATA STRUCTURES:
 *   Sometimes DP transitions require range queries:
 *     dp[i] = some_op over { dp[j] : j satisfies some range condition }
 *
 *   Use segment tree or BIT to speed up these transitions.
 *
 * EXAMPLES:
 * 1. LIS with BIT — O(n log n) counting variant
 * 2. DP with Segment Tree — AtCoder DP Q (Flowers)
 * 3. DP with Segment Tree — AtCoder DP W (Intervals)
 * 4. Number of inversions / DP with BIT
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

/*
 * ============================================================
 * FENWICK TREE (BIT) — for DP optimization
 * ============================================================
 */
class BIT {
    vector<long long> tree;
    int n;
public:
    BIT(int n) : n(n), tree(n + 1, 0) {}

    void update(int i, long long val) {
        for (; i <= n; i += i & (-i))
            tree[i] = max(tree[i], val);
    }

    long long query(int i) {
        long long res = 0;
        for (; i > 0; i -= i & (-i))
            res = max(res, tree[i]);
        return res;
    }
};

/*
 * PROBLEM 1: AtCoder DP Q — Flowers
 * N flowers with heights h[] and beauty values a[].
 * Remove some flowers so remaining heights are increasing.
 * Maximize sum of beauty values.
 *
 * This is "Maximum Weight Increasing Subsequence" = LIS variant.
 * dp[i] = max beauty ending at flower i
 * dp[i] = a[i] + max(dp[j]) for all j < i where h[j] < h[i]
 *
 * Use BIT indexed by height to query max dp in range [1, h[i]-1].
 * Time: O(n log n)
 */
long long flowersDP(vector<int>& h, vector<long long>& a) {
    int n = h.size();
    int maxH = *max_element(h.begin(), h.end());
    BIT bit(maxH);

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        long long best = bit.query(h[i] - 1);  // Max dp with height < h[i]
        long long dp_i = best + a[i];
        bit.update(h[i], dp_i);
        ans = max(ans, dp_i);
    }
    return ans;
}

/*
 * ============================================================
 * SEGMENT TREE — for DP optimization
 * ============================================================
 */
class SegTree {
    vector<long long> tree;
    int n;

    void updateHelper(int node, int lo, int hi, int pos, long long val) {
        if (lo == hi) { tree[node] = max(tree[node], val); return; }
        int mid = (lo + hi) / 2;
        if (pos <= mid) updateHelper(2*node, lo, mid, pos, val);
        else updateHelper(2*node+1, mid+1, hi, pos, val);
        tree[node] = max(tree[2*node], tree[2*node+1]);
    }

    long long queryHelper(int node, int lo, int hi, int l, int r) {
        if (r < lo || hi < l) return 0;
        if (l <= lo && hi <= r) return tree[node];
        int mid = (lo + hi) / 2;
        return max(queryHelper(2*node, lo, mid, l, r),
                   queryHelper(2*node+1, mid+1, hi, l, r));
    }

public:
    SegTree(int n) : n(n), tree(4 * n + 4, 0) {}

    void update(int pos, long long val) {
        updateHelper(1, 1, n, pos, val);
    }

    long long query(int l, int r) {
        if (l > r) return 0;
        return queryHelper(1, 1, n, l, r);
    }
};

/*
 * PROBLEM 2: AtCoder DP W — Intervals
 * N positions, M intervals [l, r] with weight w.
 * Select subset of positions (binary: each on/off).
 * Score = sum of w for intervals where ALL positions in [l,r] selected.
 * Wait — actually: score = sum of w for intervals [l,r] where
 * at least one position in [l,r] is selected?
 *
 * Actually this is a harder formulation. Simplified version here:
 * dp[i] = max score considering positions 1..i
 * For each interval [l,r,w], if we "activate" it by selecting some position in it:
 * dp[i] = max(dp[i-1], max over intervals ending at i: dp[l-1] + w)
 *
 * Use segment tree for max dp[l-1] over all intervals ending at i.
 */

// Simplified: Weighted Interval Scheduling with DP + Seg Tree
long long weightedIntervalScheduling(vector<tuple<int,int,long long>>& intervals) {
    int n = 0;
    for (auto& [l, r, w] : intervals) n = max(n, r);

    sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
        return get<1>(a) < get<1>(b);
    });

    SegTree seg(n + 1);
    seg.update(0, 0);  // dp[0] = 0 at position 0

    long long ans = 0;
    int idx = 0;

    for (int pos = 1; pos <= n; pos++) {
        // Carry forward: dp[pos] >= dp[pos-1]
        long long carry = seg.query(pos - 1, pos - 1);
        // Actually need running max... simplified approach:

        while (idx < (int)intervals.size() && get<1>(intervals[idx]) == pos) {
            auto [l, r, w] = intervals[idx];
            long long val = seg.query(0, l - 1) + w;
            ans = max(ans, val);
            seg.update(pos, val);
            idx++;
        }
        // Also option of not taking any interval ending here
        long long prev = seg.query(0, pos - 1);
        seg.update(pos, prev);
        ans = max(ans, prev);
    }
    return ans;
}

/*
 * PROBLEM 3: Count Inversions using BIT
 * dp[i] = number of elements before i that are greater than a[i]
 * Use BIT to query count in range [a[i]+1, max] before inserting a[i]
 */
class BIT_Sum {
    vector<int> tree;
    int n;
public:
    BIT_Sum(int n) : n(n), tree(n + 2, 0) {}
    void update(int i, int val = 1) {
        for (; i <= n; i += i & (-i)) tree[i] += val;
    }
    int query(int i) {
        int s = 0;
        for (; i > 0; i -= i & (-i)) s += tree[i];
        return s;
    }
    int query(int l, int r) { return query(r) - query(l - 1); }
};

long long countInversions(vector<int>& arr) {
    int n = arr.size();
    // Coordinate compress
    vector<int> sorted_arr = arr;
    sort(sorted_arr.begin(), sorted_arr.end());
    sorted_arr.erase(unique(sorted_arr.begin(), sorted_arr.end()), sorted_arr.end());

    map<int, int> comp;
    for (int i = 0; i < (int)sorted_arr.size(); i++)
        comp[sorted_arr[i]] = i + 1;

    int maxVal = sorted_arr.size();
    BIT_Sum bit(maxVal);
    long long inversions = 0;

    for (int i = 0; i < n; i++) {
        int val = comp[arr[i]];
        inversions += bit.query(val + 1, maxVal);  // Count elements > arr[i]
        bit.update(val);
    }
    return inversions;
}

/*
 * PROBLEM 4: LIS Count using BIT
 * For each element, query BIT for:
 *   - max LIS length ending with value < a[i]
 *   - count of subsequences achieving that length
 */
pair<int, long long> lisCountBIT(vector<int>& arr) {
    int n = arr.size();
    // Coordinate compress
    vector<int> sorted_arr = arr;
    sort(sorted_arr.begin(), sorted_arr.end());
    sorted_arr.erase(unique(sorted_arr.begin(), sorted_arr.end()), sorted_arr.end());
    map<int, int> comp;
    for (int i = 0; i < (int)sorted_arr.size(); i++)
        comp[sorted_arr[i]] = i + 1;
    int maxVal = sorted_arr.size();

    // BIT stores {max_length, count} — custom merge
    vector<pair<int, long long>> bit(maxVal + 2, {0, 1});

    auto merge = [](pair<int,long long> a, pair<int,long long> b) -> pair<int,long long> {
        if (a.first > b.first) return a;
        if (b.first > a.first) return b;
        return {a.first, a.second + b.second};
    };

    auto query = [&](int i) -> pair<int,long long> {
        pair<int,long long> res = {0, 1};
        for (; i > 0; i -= i & (-i))
            res = merge(res, bit[i]);
        return res;
    };

    auto update = [&](int i, pair<int,long long> val) {
        for (; i <= maxVal; i += i & (-i))
            bit[i] = merge(bit[i], val);
    };

    int maxLen = 0;
    long long totalCount = 0;

    for (int x : arr) {
        int v = comp[x];
        auto [len, cnt] = query(v - 1);
        len++;
        update(v, {len, cnt});

        if (len > maxLen) { maxLen = len; totalCount = cnt; }
        else if (len == maxLen) totalCount += cnt;
    }
    return {maxLen, totalCount};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== HARDCORE DP — DP + DATA STRUCTURES ===" << endl;

    // Flowers (LIS with weights)
    vector<int> h = {3, 1, 4, 1, 5, 9, 2, 6};
    vector<long long> a = {10, 20, 30, 15, 25, 35, 5, 40};
    cout << "\n--- Flowers (DP + BIT) ---" << endl;
    cout << "Heights: "; for (int x : h) cout << x << " ";
    cout << "\nBeauty:  "; for (long long x : a) cout << x << " ";
    cout << "\nMax beauty: " << flowersDP(h, a) << endl;

    // Count Inversions
    vector<int> arr = {3, 1, 2, 5, 4};
    cout << "\n--- Count Inversions (BIT) ---" << endl;
    cout << "Array: "; for (int x : arr) cout << x << " ";
    cout << "\nInversions: " << countInversions(arr) << endl;

    // LIS Count
    vector<int> arr2 = {1, 3, 5, 4, 7};
    cout << "\n--- LIS Count (BIT) ---" << endl;
    cout << "Array: "; for (int x : arr2) cout << x << " ";
    auto [len, cnt] = lisCountBIT(arr2);
    cout << "\nLIS length: " << len << ", Count: " << cnt << endl;

    // Weighted Interval Scheduling
    vector<tuple<int,int,long long>> intervals = {
        {1, 3, 5}, {2, 5, 6}, {4, 7, 8}, {6, 8, 4}
    };
    cout << "\n--- Weighted Interval Scheduling (Seg Tree) ---" << endl;
    cout << "Max weight: " << weightedIntervalScheduling(intervals) << endl;

    return 0;
}

