/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Sliding Window + Contribution Counting (Variable Window)
 *  Level   : Medium → Hard
 * ============================================================================
 *
 *  ▶ THE "COUNT ALL VALID SUBARRAYS" TECHNIQUE:
 *  ─────────────────────────────────────────────
 *  When the problem asks "count subarrays satisfying property P":
 *
 *  If P is SHRINKABLE (once valid, all smaller windows also valid):
 *    For each right, find the LEFTMOST valid left.
 *    count += (right - left + 1)  ← ALL subarrays [l..right] for l in [left, right]
 *
 *  If P is EXPANDABLE (once invalid, all larger windows also invalid):
 *    For each left, find the RIGHTMOST valid right.
 *    count += (right - left + 1)
 *
 *  ▶ "EXACTLY K" = "AT MOST K" - "AT MOST K-1"
 *  This is the most important counting trick in CP. Works for:
 *  - Exactly K distinct elements
 *  - Exactly K odd numbers
 *  - Exactly K zeros
 *  - Sum = K (when all elements ≥ 0)
 *
 *  PROBLEMS:
 *  LC 713  — Subarray Product Less Than K (count, variable window)
 *            https://leetcode.com/problems/subarray-product-less-than-k/
 *  LC 992  — Subarrays with K Different Integers (exactly K = atMost trick)
 *            https://leetcode.com/problems/subarrays-with-k-different-integers/
 *  LC 1248 — Count Nice Subarrays (exactly K odds)
 *            https://leetcode.com/problems/count-number-of-nice-subarrays/
 *  LC 2302 — Count Subarrays With Score Less Than K
 *            https://leetcode.com/problems/count-subarrays-with-score-less-than-k/
 *  LC 2537 — Count the Number of Good Subarrays (at least K pairs)
 *            https://leetcode.com/problems/count-the-number-of-good-subarrays/
 *  LC 2444 — Count Subarrays with Fixed Bounds
 *            https://leetcode.com/problems/count-subarrays-with-fixed-bounds/
 *  LC 930  — Binary Subarrays with Sum (exactly K 1s)
 *            https://leetcode.com/problems/binary-subarrays-with-sum/
 *  LC 1358 — Number of Substrings Containing All Three Characters
 *            https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
using ll = long long;

// ============================================================================
// TEMPLATE: Count subarrays with PROPERTY ≤ K (shrinkable)
// ============================================================================
/*
 * For each right, find leftmost left where property ≤ K.
 * count += (right - left + 1).
 * Total subarrays = sum of window sizes.
 *
 * WHY (right - left + 1)?
 * Window [left, right] is valid. All subarrays ending at right:
 * [left, right], [left+1, right], ..., [right, right] → (right - left + 1) subarrays.
 */

// Count subarrays with sum ≤ K (all positive elements)
ll countSubarraysSumLeK(vector<int>& nums, ll k) {
    int n = nums.size();
    ll sum = 0, count = 0;
    int left = 0;

    for (int right = 0; right < n; right++) {
        sum += nums[right];
        while (sum > k && left <= right) sum -= nums[left++];
        count += (right - left + 1);
    }
    return count;
}

// ============================================================================
// LC 713: Subarray Product Less Than K
// ============================================================================
/*
 * Count subarrays where product of all elements < K.
 * Product is monotone increasing (all positive). Shrink when product ≥ K.
 * count += (right - left + 1) for each right.
 */
int numSubarrayProductLessThanK(vector<int>& nums, int k) {
    if (k <= 1) return 0;
    int left = 0, count = 0;
    ll product = 1;

    for (int right = 0; right < (int)nums.size(); right++) {
        product *= nums[right];
        while (product >= k) product /= nums[left++];
        count += (right - left + 1);
    }
    return count;
}

// ============================================================================
// TEMPLATE: "Exactly K" = "At Most K" - "At Most K-1"
// ============================================================================
ll atMostKDistinct(vector<int>& nums, int k) {
    int n = nums.size();
    unordered_map<int, int> freq;
    ll count = 0;
    int left = 0;

    for (int right = 0; right < n; right++) {
        freq[nums[right]]++;
        while ((int)freq.size() > k) {
            if (--freq[nums[left]] == 0) freq.erase(nums[left]);
            left++;
        }
        count += (right - left + 1);
    }
    return count;
}

// LC 992: Exactly K different integers
int subarraysWithKDistinct(vector<int>& nums, int k) {
    return (int)(atMostKDistinct(nums, k) - atMostKDistinct(nums, k - 1));
}

// ============================================================================
// LC 2302: Count Subarrays With Score Less Than K
// ============================================================================
/*
 * Score of subarray = sum * length. Count subarrays with score < K.
 * sum * length < K → shrinkable. For each right, shrink left while score ≥ K.
 * count += (right - left + 1).
 */
long long countSubarrays_scoreLess(vector<int>& nums, ll k) {
    int n = nums.size();
    ll sum = 0, count = 0;
    int left = 0;

    for (int right = 0; right < n; right++) {
        sum += nums[right];
        while (sum * (right - left + 1) >= k) sum -= nums[left++];
        count += (right - left + 1);
    }
    return count;
}

// ============================================================================
// LC 2537: Count Good Subarrays — At Least K Pairs of Equal Elements
// ============================================================================
/*
 * A pair = two same-valued elements in subarray.
 * Adding element x with frequency f adds f new pairs.
 * Removing element x with frequency f removes (f-1) pairs (new freq = f-1).
 *
 * "At least K pairs" → once we have ≥ K pairs, all extensions are also valid.
 * For each right, find leftmost left with ≥ K pairs.
 * All subarrays starting at [0..left] with right endpoint = right are valid.
 * count += left  (not left+1 because it's "at least", not "at most")
 *
 * Wait — reframe: if window [left, right] has ≥ K pairs,
 * then all [l, right] for l ≤ left also have ≥ K pairs (bigger window = more pairs).
 * So count += (left + 1) — wrong direction.
 *
 * Actually: shrink from left while pairs ≥ K. After shrinking,
 * window [left, right] has < K pairs, but [left-1, right] has ≥ K.
 * All starting points [0, 1, ..., left-1] give valid subarrays.
 * count += left.
 */
long long countGoodSubarrays(vector<int>& nums, int k) {
    int n = nums.size();
    unordered_map<int, int> freq;
    ll pairs = 0, count = 0;
    int left = 0;

    for (int right = 0; right < n; right++) {
        pairs += freq[nums[right]]; // Adding nums[right] creates freq[x] new pairs
        freq[nums[right]]++;

        while (pairs >= k) {
            freq[nums[left]]--;
            pairs -= freq[nums[left]]; // Removing decreases by new freq
            left++;
        }
        count += left; // All starts before left give ≥ K pairs
    }
    return count;
}

// ============================================================================
// LC 2444: Count Subarrays with Fixed Bounds (min = minK, max = maxK)
// ============================================================================
/*
 * Track lastBad, lastMin, lastMax. For each right:
 * count += max(0, min(lastMin, lastMax) - lastBad)
 */
long long countSubarrays_fixedBounds(vector<int>& nums, int minK, int maxK) {
    ll count = 0;
    int lastBad = -1, lastMin = -1, lastMax = -1;

    for (int i = 0; i < (int)nums.size(); i++) {
        if (nums[i] < minK || nums[i] > maxK) lastBad = i;
        if (nums[i] == minK) lastMin = i;
        if (nums[i] == maxK) lastMax = i;
        count += max(0, min(lastMin, lastMax) - lastBad);
    }
    return count;
}

// ============================================================================
// CONTRIBUTION COUNTING — How many subarrays contain index i?
// ============================================================================
/*
 * Index i is in subarrays [l..r] where l ≤ i ≤ r.
 * Choices: l can be 0..i (i+1 choices), r can be i..n-1 (n-i choices).
 * Total subarrays containing i = (i + 1) * (n - i).
 *
 * If each element contributes val[i], total sum of all subarrays:
 * total = sum of val[i] * (i+1) * (n-i)
 *
 * Time: O(N), Space: O(1)
 */
ll totalSumAllSubarrays(vector<int>& nums) {
    int n = nums.size();
    ll total = 0;
    for (int i = 0; i < n; i++)
        total += (ll)nums[i] * (i + 1) * (n - i);
    return total;
}

int main() {
    // Product < K
    vector<int> a1 = {10, 5, 2, 6};
    cout << "Product < 100: " << numSubarrayProductLessThanK(a1, 100) << "\n"; // 8

    // Exactly K distinct
    vector<int> a2 = {1, 2, 1, 2, 3};
    cout << "Exactly 2 distinct: " << subarraysWithKDistinct(a2, 2) << "\n"; // 7

    // Score < K
    vector<int> a3 = {2, 1, 4, 3, 5};
    cout << "Score < 10: " << countSubarrays_scoreLess(a3, 10) << "\n"; // 6

    // Good subarrays (≥ K pairs)
    vector<int> a4 = {1, 1, 1, 1, 1};
    cout << "Good (k=10): " << countGoodSubarrays(a4, 10) << "\n"; // 1

    // Fixed bounds
    vector<int> a5 = {1, 3, 5, 2, 7, 5};
    cout << "Fixed [1,5]: " << countSubarrays_fixedBounds(a5, 1, 5) << "\n"; // 2

    // Total sum all subarrays
    vector<int> a6 = {1, 2, 3};
    cout << "Total sum all subarrays: " << totalSumAllSubarrays(a6) << "\n"; // 20

    return 0;
}

