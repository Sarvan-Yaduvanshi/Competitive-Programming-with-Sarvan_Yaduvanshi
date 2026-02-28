/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Meet in the Middle (Split-and-Merge with Two Pointer)
 *  Level   : Hard → Expert (Codeforces 1800 → 2200)
 * ============================================================================
 *
 *  ▶ WHAT IS MEET IN THE MIDDLE?
 *  ─────────────────────────────
 *  When brute-force is O(2^N) or O(N!), and N is moderate (e.g., N ≤ 40),
 *  split the input into TWO HALVES:
 *    Left half: generate all 2^(N/2) subsets/combinations
 *    Right half: generate all 2^(N/2) subsets/combinations
 *  Then COMBINE results using sorting + two pointer (or binary search).
 *
 *  Total: O(2^(N/2) * log(2^(N/2))) = O(2^(N/2) * N)
 *  This is MASSIVELY better than O(2^N) for N=40:
 *    2^40 = 1 trillion ❌     vs     2^20 * 20 = 20 million ✅
 *
 *  ▶ WHEN TO USE:
 *  ──────────────
 *  ✅ N ≤ 40 and need to enumerate subsets
 *  ✅ Target sum/XOR/product problems on small sets
 *  ✅ Can't afford O(2^N) but O(2^(N/2)) is fine
 *
 *  ▶ CONNECTION TO TWO POINTER:
 *  ────────────────────────────
 *  After generating left and right subsets, we SORT both.
 *  Then use TWO POINTER (or binary search) to find complementary pairs.
 *  This is literally "Two Sum on generated subsets".
 *
 *  PROBLEMS:
 *  LC 1755 — Closest Subsequence Sum (Meet in Middle + Two Pointer)
 *            https://leetcode.com/problems/closest-subsequence-sum/
 *  LC 2035 — Partition Array Into Two Arrays to Minimize Sum Difference
 *            https://leetcode.com/problems/partition-array-into-two-arrays-to-minimize-sum-difference/
 *  CF 888E — Maximum Subsequence (Meet in Middle + Sort + Two Pointer, 1800)
 *            https://codeforces.com/problemset/problem/888/E
 *  CSES 1642 — Sum of Four Values (can be solved with meet in middle)
 *            https://cses.fi/problemset/task/1642
 *  CF 1006F — Xor Paths (Meet in Middle on grid, 2100)
 *            https://codeforces.com/problemset/problem/1006/F
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
using namespace std;
using ll = long long;

// ============================================================================
// HELPER: Generate all subset sums of arr[start..end)
// ============================================================================
/*
 * For N elements, there are 2^N subsets.
 * We use bitmask enumeration: for mask in [0, 2^N):
 *   sum = sum of arr[i] where bit i of mask is set.
 *
 * Time: O(2^N), Space: O(2^N)
 */
vector<ll> generateSubsetSums(vector<int>& arr, int start, int end) {
    int n = end - start;
    vector<ll> sums(1 << n, 0);

    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i))
                sums[mask] += arr[start + i];
        }
    }
    return sums;
}

// ============================================================================
// LC 1755: Closest Subsequence Sum
// ============================================================================
/*
 * Given array of N ≤ 40 elements and target goal.
 * Find subsequence with sum closest to goal.
 *
 * MEET IN THE MIDDLE:
 * 1. Split array into two halves.
 * 2. Generate all 2^(N/2) subset sums for each half.
 * 3. Sort the right half.
 * 4. For each sum in left half, binary search for closest complement in right half.
 *
 * Time: O(2^(N/2) * N), Space: O(2^(N/2))
 */
int minAbsDifference(vector<int>& nums, int goal) {
    int n = nums.size();
    int half = n / 2;

    // Generate all subset sums for each half
    vector<ll> leftSums = generateSubsetSums(nums, 0, half);
    vector<ll> rightSums = generateSubsetSums(nums, half, n);

    // Sort right half for binary search
    sort(rightSums.begin(), rightSums.end());

    ll best = LLONG_MAX;

    for (ll lsum : leftSums) {
        ll need = goal - lsum; // We want rsum closest to 'need'

        // Binary search for closest value in rightSums
        auto it = lower_bound(rightSums.begin(), rightSums.end(), need);

        // Check the element at 'it' and the one before
        if (it != rightSums.end())
            best = min(best, abs(lsum + *it - goal));
        if (it != rightSums.begin()) {
            --it;
            best = min(best, abs(lsum + *it - goal));
        }
    }
    return (int)best;
}

// ============================================================================
// CF 888E: Maximum Subsequence — sum closest to M (modulo)
// ============================================================================
/*
 * Given N ≤ 35 elements and modulo M.
 * Find subsequence whose sum mod M is maximum.
 *
 * MEET IN THE MIDDLE:
 * 1. Split, generate all subset sums mod M for each half.
 * 2. Sort right half.
 * 3. For each left sum L, we want R such that (L + R) mod M is maximized.
 *    Best R = (M - 1 - L) mod M. Find largest R ≤ that using binary search.
 *    Also check R wrapping around (R near M-1 when L is small).
 *
 * Time: O(2^(N/2) * log), Space: O(2^(N/2))
 */
void solve_CF888E() {
    int n;
    ll m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto& x : a) cin >> x;

    int half = n / 2;

    // Generate all subset sums mod M for each half
    auto genMod = [&](int start, int end) -> vector<ll> {
        int sz = end - start;
        vector<ll> sums(1 << sz, 0);
        for (int mask = 0; mask < (1 << sz); mask++) {
            for (int i = 0; i < sz; i++) {
                if (mask & (1 << i))
                    sums[mask] = (sums[mask] + a[start + i]) % m;
            }
        }
        return sums;
    };

    vector<ll> leftSums = genMod(0, half);
    vector<ll> rightSums = genMod(half, n);

    sort(rightSums.begin(), rightSums.end());
    rightSums.erase(unique(rightSums.begin(), rightSums.end()), rightSums.end());

    ll best = 0;
    for (ll L : leftSums) {
        // We want (L + R) % m maximized. Best R = (m - 1 - L) % m
        ll target = (m - 1 - L) % m;

        // Find largest R ≤ target
        auto it = upper_bound(rightSums.begin(), rightSums.end(), target);
        if (it != rightSums.begin()) {
            --it;
            best = max(best, (L + *it) % m);
        }

        // Also check the largest element in rightSums (wrapping case)
        best = max(best, (L + rightSums.back()) % m);
    }
    cout << best << "\n";
}

// ============================================================================
// TWO POINTER VERSION: When both halves are sorted, use two pointer
// ============================================================================
/*
 * Alternative to binary search: if looking for EXACT sum = target:
 * Sort leftSums ascending, rightSums descending.
 * Two pointer: if L + R == target → found.
 *              if L + R < target → left++.
 *              if L + R > target → right++.
 *
 * For CLOSEST sum: still binary search is cleaner, but two pointer works:
 * Sort both ascending. Use left pointer from start, right pointer from end.
 */
bool meetInMiddleExactSum(vector<int>& nums, int target) {
    int n = nums.size();
    int half = n / 2;

    vector<ll> leftSums = generateSubsetSums(nums, 0, half);
    vector<ll> rightSums = generateSubsetSums(nums, half, n);

    sort(leftSums.begin(), leftSums.end());
    sort(rightSums.begin(), rightSums.end());

    // Two pointer: left from start, right from end
    int i = 0, j = (int)rightSums.size() - 1;
    while (i < (int)leftSums.size() && j >= 0) {
        ll sum = leftSums[i] + rightSums[j];
        if (sum == target) return true;
        if (sum < target) i++;
        else j--;
    }
    return false;
}

int main() {
    // LC 1755: Closest Subsequence Sum
    vector<int> nums1 = {5, -7, 3, 5};
    cout << "Closest to 6: " << minAbsDifference(nums1, 6) << "\n"; // 0 (subseq {5,3,-7,5}=6)

    vector<int> nums2 = {7, -9, 15, -2};
    cout << "Closest to -5: " << minAbsDifference(nums2, -5) << "\n"; // 1

    // Meet in Middle exact sum
    vector<int> nums3 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << "Exact sum 30: " << meetInMiddleExactSum(nums3, 30) << "\n"; // 1

    return 0;
}

