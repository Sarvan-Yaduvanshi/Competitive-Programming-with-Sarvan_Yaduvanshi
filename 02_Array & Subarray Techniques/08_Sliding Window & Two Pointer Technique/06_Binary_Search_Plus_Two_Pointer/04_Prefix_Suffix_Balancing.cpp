/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Prefix–Suffix Two Pointer Balancing Problems
 *  Level   : Medium → Hard
 * ============================================================================
 *
 *  ▶ WHAT IS PREFIX-SUFFIX TWO POINTER BALANCING?
 *  ──────────────────────────────────────────────
 *  Instead of standard converging pointers, we maintain two "running"
 *  quantities — a prefix sum/product from the left and a suffix sum/product
 *  from the right — and balance them or find optimal split points.
 *
 *  KEY PATTERNS:
 *  ─────────────
 *  1. Prefix-Suffix Split: Find split point where prefix[left] ≈ suffix[right]
 *  2. Equal Partition: Split array into K parts with equal sums
 *  3. Left-Right DP + Two Pointer: Compute best from left and right independently,
 *     then combine using two pointer or binary search
 *  4. Product of Array Except Self: Prefix * Suffix (O(1) space trick)
 *
 *  PROBLEMS:
 *  LC 238  — Product of Array Except Self (prefix-suffix product)
 *            https://leetcode.com/problems/product-of-array-except-self/
 *  LC 2270 — Number of Ways to Split Array (prefix split)
 *            https://leetcode.com/problems/number-of-ways-to-split-array/
 *  LC 1524 — Number of Sub-arrays With Odd Sum (prefix parity)
 *            https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/
 *  LC 1525 — Number of Good Ways to Split a String (distinct prefix/suffix)
 *            https://leetcode.com/problems/number-of-good-ways-to-split-a-string/
 *  LC 2256 — Minimum Average Difference (prefix-suffix avg)
 *            https://leetcode.com/problems/minimum-average-difference/
 *  LC 334  — Increasing Triplet Subsequence (prefix min, suffix max)
 *            https://leetcode.com/problems/increasing-triplet-subsequence/
 *  LC 42   — Trapping Rain Water (prefix max + suffix max — already covered)
 *  LC 1658 — Min Operations to Reduce X (reverse: middle subarray — already covered)
 *  CF 1409E — Two Platforms (left-right DP + two pointer, 1800)
 *            https://codeforces.com/problemset/problem/1409/E
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <unordered_set>
#include <numeric>
using namespace std;
using ll = long long;

// ============================================================================
// LC 238: Product of Array Except Self — Prefix * Suffix (O(1) space)
// ============================================================================
/*
 * result[i] = product of all elements except nums[i].
 * No division allowed!
 *
 * TRICK: Two passes.
 * Pass 1 (left→right): result[i] = prefix product from [0..i-1]
 * Pass 2 (right→left): multiply result[i] by suffix product from [i+1..N-1]
 *
 * Time: O(N), Space: O(1) extra (result array doesn't count)
 */
vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, 1);

    // Pass 1: prefix product (left to right)
    int prefix = 1;
    for (int i = 0; i < n; i++) {
        result[i] = prefix;
        prefix *= nums[i];
    }

    // Pass 2: suffix product (right to left)
    int suffix = 1;
    for (int i = n - 1; i >= 0; i--) {
        result[i] *= suffix;
        suffix *= nums[i];
    }

    return result;
}

// ============================================================================
// LC 2270: Number of Ways to Split Array
// ============================================================================
/*
 * Split at index i: left = nums[0..i], right = nums[i+1..N-1]
 * Count splits where leftSum >= rightSum.
 *
 * TECHNIQUE: Compute totalSum. Maintain running prefixSum.
 * For each i: leftSum = prefixSum, rightSum = totalSum - prefixSum.
 *
 * Time: O(N), Space: O(1)
 */
int waysToSplitArray(vector<int>& nums) {
    int n = nums.size();
    ll total = 0;
    for (int x : nums) total += x;

    int count = 0;
    ll prefix = 0;
    for (int i = 0; i < n - 1; i++) { // Can't split after last element
        prefix += nums[i];
        ll suffix = total - prefix;
        if (prefix >= suffix) count++;
    }
    return count;
}

// ============================================================================
// LC 1525: Number of Good Ways to Split a String
// ============================================================================
/*
 * Split string into left and right parts. "Good" if both parts have
 * same number of DISTINCT characters.
 *
 * TECHNIQUE: Prefix distinct count (left→right) + Suffix distinct count (right→left)
 * Then check where prefixDistinct[i] == suffixDistinct[i+1].
 *
 * Time: O(N), Space: O(N) for arrays or O(26) = O(1) for frequency
 */
int numSplits(string s) {
    int n = s.size();
    vector<int> prefixDistinct(n), suffixDistinct(n);

    // Compute prefix distinct counts
    int freq[26] = {};
    int distinct = 0;
    for (int i = 0; i < n; i++) {
        if (freq[s[i] - 'a']++ == 0) distinct++;
        prefixDistinct[i] = distinct;
    }

    // Compute suffix distinct counts
    fill(freq, freq + 26, 0);
    distinct = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (freq[s[i] - 'a']++ == 0) distinct++;
        suffixDistinct[i] = distinct;
    }

    // Count good splits
    int count = 0;
    for (int i = 0; i < n - 1; i++)
        if (prefixDistinct[i] == suffixDistinct[i + 1])
            count++;
    return count;
}

// ============================================================================
// LC 2256: Minimum Average Difference
// ============================================================================
/*
 * For each index i: avg_left = floor(sum(0..i) / (i+1))
 *                    avg_right = floor(sum(i+1..N-1) / (N-i-1))   (0 if empty)
 * Return index with minimum |avg_left - avg_right|.
 *
 * Time: O(N), Space: O(1)
 */
int minimumAverageDifference(vector<int>& nums) {
    int n = nums.size();
    ll total = 0;
    for (int x : nums) total += x;

    ll prefix = 0;
    ll minDiff = LLONG_MAX;
    int bestIdx = 0;

    for (int i = 0; i < n; i++) {
        prefix += nums[i];
        ll avgLeft = prefix / (i + 1);
        ll avgRight = (i == n - 1) ? 0 : (total - prefix) / (n - i - 1);
        ll diff = abs(avgLeft - avgRight);

        if (diff < minDiff) {
            minDiff = diff;
            bestIdx = i;
        }
    }
    return bestIdx;
}

// ============================================================================
// LC 334: Increasing Triplet Subsequence — Prefix Min + Suffix Max
// ============================================================================
/*
 * Return true if there exists i < j < k with nums[i] < nums[j] < nums[k].
 *
 * APPROACH 1: Prefix min from left, suffix max from right.
 *   For each j, check if prefixMin[j] < nums[j] < suffixMax[j].
 *
 * APPROACH 2 (O(1) space): Track smallest and second smallest seen so far.
 *   If any element > second_smallest, return true.
 *
 * Time: O(N), Space: O(1)
 */
bool increasingTriplet(vector<int>& nums) {
    int first = INT_MAX, second = INT_MAX;
    for (int x : nums) {
        if (x <= first) first = x;          // Smallest so far
        else if (x <= second) second = x;   // Second smallest
        else return true;                    // Found third → triplet exists
    }
    return false;
}

// ============================================================================
// CF 1409E: Two Platforms — Left-Right DP + Two Pointer
// ============================================================================
/*
 * N points fall. Two platforms of width K. Maximize caught points.
 *
 * TECHNIQUE:
 * 1. Sort by x-coordinate.
 * 2. For each position, use two pointer to find how many points a platform
 *    starting here catches.
 * 3. Compute prefix max from left: best[i] = max points a single platform
 *    catches considering only points 0..i.
 * 4. For each right platform position, combine with best left result.
 *
 * This is a classic "left-right DP with two pointer sweep" pattern.
 * Time: O(N log N), Space: O(N)
 */
void solve_CF1409E() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> x(n), y(n);
        for (auto& xi : x) cin >> xi;
        for (auto& yi : y) cin >> yi;

        sort(x.begin(), x.end()); // Only x matters

        // catch[i] = number of points caught if platform starts at x[i]
        // A platform at x[i] covers [x[i], x[i]+k]
        vector<int> catchCount(n);
        int right = 0;
        for (int left = 0; left < n; left++) {
            while (right < n && x[right] - x[left] <= k) right++;
            catchCount[left] = right - left;
        }

        // prefixBest[i] = max(catchCount[0..i])
        vector<int> prefixBest(n);
        prefixBest[0] = catchCount[0];
        for (int i = 1; i < n; i++)
            prefixBest[i] = max(prefixBest[i - 1], catchCount[i]);

        // For each right platform starting at i, the left platform uses best from [0..j-1]
        // where j is the first point not covered by a platform ending before x[i]
        int best = 0;
        int j = 0;
        for (int i = 0; i < n; i++) {
            // Right platform starts at x[i], covers [x[i], x[i]+k]
            // Left platform must end before x[i] starts → use prefixBest[i-1]
            int rightCatch = catchCount[i];
            int leftCatch = (i > 0) ? prefixBest[i - 1] : 0;
            best = max(best, leftCatch + rightCatch);
        }
        cout << best << "\n";
    }
}

int main() {
    // LC 238: Product Except Self
    vector<int> nums1 = {1, 2, 3, 4};
    auto prod = productExceptSelf(nums1);
    cout << "Product Except Self: ";
    for (int x : prod) cout << x << " ";
    cout << "\n"; // 24 12 8 6

    // LC 2270: Ways to Split Array
    vector<int> nums2 = {10, 4, -8, 7};
    cout << "Ways to split: " << waysToSplitArray(nums2) << "\n"; // 2

    // LC 1525: Good String Splits
    cout << "Good splits (aacaba): " << numSplits("aacaba") << "\n"; // 2

    // LC 334: Increasing Triplet
    vector<int> nums3 = {2, 1, 5, 0, 4, 6};
    cout << "Increasing triplet: " << increasingTriplet(nums3) << "\n"; // 1

    return 0;
}

