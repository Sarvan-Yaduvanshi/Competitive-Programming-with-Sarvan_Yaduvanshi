/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Advanced Pair Counting in Range [L, R] — Two Pointer Tricks
 *  Level   : Medium → Hard (Codeforces 1400 → 2000)
 * ============================================================================
 *
 *  ▶ THE RANGE PAIR COUNTING TECHNIQUE
 *  ────────────────────────────────────
 *  Problem: Count pairs (i, j), i < j, such that L ≤ f(a[i], a[j]) ≤ R.
 *
 *  KEY TRICK:
 *  ──────────
 *  countInRange(L, R) = countAtMost(R) - countAtMost(L - 1)
 *
 *  This converts a "range" problem into TWO "at most" problems.
 *  Each "at most" problem can be solved with sorted array + two pointer.
 *
 *  COMMON VARIANTS:
 *  ────────────────
 *  1. Count pairs with sum in [L, R]
 *  2. Count pairs with difference in [L, R]
 *  3. Count pairs with product in [L, R]
 *  4. Count pairs with XOR in [L, R] (trie-based — harder)
 *  5. Count pairs with GCD = K (Euler's totient or inclusion-exclusion)
 *
 *  PROBLEMS:
 *  LC 1538C (CF) — Number of Pairs (sort + 2ptr for sum in [L,R])
 *            https://codeforces.com/problemset/problem/1538/C
 *  LC 1577 — Number of Ways Where Square of Number = Product of Two Numbers
 *            https://leetcode.com/problems/number-of-ways-where-square-of-number-is-equal-to-product-of-two-numbers/
 *  LC 1814 — Count Nice Pairs in an Array (sum of reversed digits trick)
 *            https://leetcode.com/problems/count-nice-pairs-in-an-array/
 *  LC 1782 — Count Pairs of Nodes (degree counting, hard)
 *            https://leetcode.com/problems/count-pairs-of-nodes/
 *  LC 2563 — Count the Number of Fair Pairs (sort + 2ptr range)
 *            https://leetcode.com/problems/count-the-number-of-fair-pairs/
 *  LC 327  — Count of Range Sum (merge sort + prefix, hard)
 *            https://leetcode.com/problems/count-of-range-sum/
 *  CF 1538C — Number of Pairs (1300)
 *            https://codeforces.com/problemset/problem/1538/C
 *  CF 1324D — Pair of Topics (1400)
 *            https://codeforces.com/problemset/problem/1324/D
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

// ============================================================================
// CORE TECHNIQUE: countPairsWithSumAtMost(arr, target)
// ============================================================================
/*
 * Given sorted array, count pairs (i,j) i<j with a[i]+a[j] <= target.
 * Two pointer: if sum <= target, ALL pairs (left, left+1..right-1, right) work.
 *   count += (right - left), then left++.
 * Else right--.
 *
 * Time: O(N) (after sorting), Space: O(1)
 */
ll countPairsSumAtMost(vector<ll>& a, ll target) {
    int left = 0, right = (int)a.size() - 1;
    ll count = 0;
    while (left < right) {
        if (a[left] + a[right] <= target) {
            count += (right - left);
            left++;
        } else {
            right--;
        }
    }
    return count;
}

// ============================================================================
// LC 2563: Count the Number of Fair Pairs — L ≤ a[i]+a[j] ≤ R
// ============================================================================
/*
 * Count pairs (i,j) where lower ≤ nums[i]+nums[j] ≤ upper.
 * countInRange = countAtMost(upper) - countAtMost(lower - 1)
 *
 * Time: O(N log N), Space: O(1)
 */
long long countFairPairs(vector<int>& nums, int lower, int upper) {
    vector<ll> a(nums.begin(), nums.end());
    sort(a.begin(), a.end());
    return countPairsSumAtMost(a, (ll)upper) - countPairsSumAtMost(a, (ll)lower - 1);
}

// ============================================================================
// CF 1538C: Number of Pairs — L ≤ a[i]+a[j] ≤ R
// ============================================================================
/*
 * Exactly the same technique as LC 2563.
 * sort + countAtMost(R) - countAtMost(L-1)
 */
void solve_CF1538C() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        ll l, r;
        cin >> n >> l >> r;
        vector<ll> a(n);
        for (auto& x : a) cin >> x;
        sort(a.begin(), a.end());

        ll ans = countPairsSumAtMost(a, r) - countPairsSumAtMost(a, l - 1);
        cout << ans << "\n";
    }
}

// ============================================================================
// CF 1324D: Pair of Topics — count pairs a[i]-b[i] + a[j]-b[j] > 0
// ============================================================================
/*
 * Given arrays a and b. Count pairs (i,j), i<j, where
 *   a[i]+a[j] > b[i]+b[j]  ↔  (a[i]-b[i]) + (a[j]-b[j]) > 0
 *
 * Let c[i] = a[i] - b[i]. Count pairs with c[i]+c[j] > 0.
 * = Total pairs - pairs with c[i]+c[j] <= 0
 * = C(n,2) - countAtMost(0)
 *
 * Or directly: sort c, two pointer.
 * If c[left]+c[right] > 0: all pairs (left, left+1..right-1, right) work.
 *   count += (right - left), right--.
 * Else left++.
 */
void solve_CF1324D() {
    int n;
    cin >> n;
    vector<ll> a(n), b(n);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;

    vector<ll> c(n);
    for (int i = 0; i < n; i++) c[i] = a[i] - b[i];
    sort(c.begin(), c.end());

    ll count = 0;
    int left = 0, right = n - 1;
    while (left < right) {
        if (c[left] + c[right] > 0) {
            count += (right - left);
            right--;
        } else {
            left++;
        }
    }
    cout << count << "\n";
}

// ============================================================================
// LC 327: Count of Range Sum — Merge Sort on Prefix Sums (HARD)
// ============================================================================
/*
 * Count subarrays with sum in [lower, upper].
 * Let prefix[i] = sum(0..i-1). Subarray sum [i,j] = prefix[j+1] - prefix[i].
 * We need: lower ≤ prefix[j] - prefix[i] ≤ upper, for i < j.
 *
 * MERGE SORT approach: During merge step, count valid (i,j) pairs
 * between left half (as i) and right half (as j) using two pointers.
 *
 * Time: O(N log N), Space: O(N)
 */
int countRangeSum(vector<int>& nums, int lower, int upper) {
    int n = nums.size();
    vector<ll> prefix(n + 1, 0);
    for (int i = 0; i < n; i++)
        prefix[i + 1] = prefix[i] + nums[i];

    // Merge sort on prefix array, count during merge
    int count = 0;

    function<void(int, int)> mergeSort = [&](int lo, int hi) {
        if (hi - lo <= 1) return;
        int mid = lo + (hi - lo) / 2;
        mergeSort(lo, mid);
        mergeSort(mid, hi);

        // Count: for each j in [mid, hi), count i in [lo, mid) where
        // lower ≤ prefix[j] - prefix[i] ≤ upper
        // ↔ prefix[j] - upper ≤ prefix[i] ≤ prefix[j] - lower
        int lo1 = lo, hi1 = lo; // Two pointers in left half
        for (int j = mid; j < hi; j++) {
            while (lo1 < mid && prefix[lo1] < prefix[j] - upper) lo1++;
            while (hi1 < mid && prefix[hi1] <= prefix[j] - lower) hi1++;
            count += (hi1 - lo1);
        }

        // Standard merge
        inplace_merge(prefix.begin() + lo, prefix.begin() + mid, prefix.begin() + hi);
    };

    mergeSort(0, n + 1);
    return count;
}

// ============================================================================
// GENERAL FRAMEWORK: Count pairs with diff in [L, R]
// ============================================================================
/*
 * count pairs |a[i]-a[j]| in [L,R] (sorted):
 *   = countDiffAtMost(R) - countDiffAtMost(L-1)
 *
 * countDiffAtMost(d): for each right, find leftmost left where a[right]-a[left] <= d.
 *   count += (right - left)
 */
ll countPairsDiffAtMost(vector<ll>& a, ll d) {
    if (d < 0) return 0;
    int n = a.size();
    ll count = 0;
    int left = 0;
    for (int right = 1; right < n; right++) {
        while (a[right] - a[left] > d) left++;
        count += (right - left);
    }
    return count;
}

ll countPairsDiffInRange(vector<ll>& a, ll L, ll R) {
    sort(a.begin(), a.end());
    return countPairsDiffAtMost(a, R) - countPairsDiffAtMost(a, L - 1);
}

int main() {
    // LC 2563: Fair Pairs
    vector<int> nums1 = {0, 1, 7, 4, 4, 5};
    cout << "Fair pairs [3,6]: " << countFairPairs(nums1, 3, 6) << "\n"; // 6

    // LC 327: Count of Range Sum
    vector<int> nums2 = {-2, 5, -1};
    cout << "Range sum [-2,2]: " << countRangeSum(nums2, -2, 2) << "\n"; // 3

    // Count pairs diff in range
    vector<ll> a = {1, 3, 5, 7, 9};
    cout << "Pairs diff in [2,4]: " << countPairsDiffInRange(a, 2, 4) << "\n"; // 6

    return 0;
}

