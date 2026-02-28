/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Sliding Window + Prefix / Binary Search Hybrid
 *  Level   : Hard → Expert (CF 1800+)
 * ============================================================================
 *
 *  ▶ WHEN NORMAL SLIDING WINDOW FAILS:
 *  ────────────────────────────────────
 *  Standard sliding window requires MONOTONICITY (e.g., all positive).
 *  When array has NEGATIVE numbers, expanding the window can DECREASE the sum!
 *  → The "shrink when too big" logic breaks.
 *
 *  ▶ SOLUTIONS:
 *  ────────────
 *  1. Prefix Sum + Monotonic Deque (LC 862): O(N)
 *     - Build prefix sum. Want shortest [l,r] with prefix[r] - prefix[l] ≥ K.
 *     - Maintain increasing deque of prefix indices.
 *     - Pop from front while prefix[right] - prefix[front] ≥ K (record answer).
 *     - Pop from back while prefix[back] ≥ prefix[right] (dominated).
 *
 *  2. Binary Search on Answer + Window Validation:
 *     - "Find minimum window size where property holds"
 *     - Binary search on size, validate with fixed window check.
 *
 *  3. Parametric Search + Sliding Window:
 *     - "Is there a subarray of length ≥ L with avg ≥ K?"
 *     - Subtract K from each element, check if max subarray ≥ 0.
 *
 *  PROBLEMS:
 *  LC 862  — Shortest Subarray with Sum ≥ K (positive + NEGATIVE!)
 *            https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/
 *  LC 1793 — Maximum Score of a Good Subarray (expand from k, two pointer)
 *            https://leetcode.com/problems/maximum-score-of-a-good-subarray/
 *  LC 644  — Maximum Average Subarray II (binary search on answer)
 *            https://leetcode.com/problems/maximum-average-subarray-ii/
 *  LC 2106 — Maximum Fruits Harvested After at Most K Steps
 *            https://leetcode.com/problems/maximum-fruits-harvested-after-at-most-k-steps/
 *  CF 1849D — Array Painting (prefix + greedy, 1700)
 *            https://codeforces.com/problemset/problem/1849/D
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <climits>
using namespace std;
using ll = long long;

// ============================================================================
// LC 862: Shortest Subarray with Sum ≥ K — PREFIX + MONOTONIC DEQUE
// ============================================================================
/*
 * ▶ THIS IS THE MOST IMPORTANT PROBLEM IN THIS FILE!
 *
 * Array may have NEGATIVE numbers. Find shortest subarray with sum ≥ K.
 * Normal sliding window FAILS because sum isn't monotone.
 *
 * APPROACH: Prefix sums + monotonic deque.
 *
 * prefix[i] = sum of arr[0..i-1]. prefix[0] = 0.
 * We want: shortest (j - i) where prefix[j] - prefix[i] ≥ K and i < j.
 *
 * DEQUE INVARIANT (increasing prefix values):
 * 1. Pop FRONT while prefix[right] - prefix[front] ≥ K.
 *    → These give valid answers. Record min length.
 *    → Pop because no future right can give a shorter answer with this front.
 * 2. Pop BACK while prefix[back] ≥ prefix[right].
 *    → Back is dominated: same position or later, but larger prefix.
 *    → Any future query would prefer right over back.
 *
 * Time: O(N), Space: O(N)
 *
 * VISUAL:
 * prefix: [0, 2, -1, 5, 3, 8, ...]
 * deque stores indices with increasing prefix values.
 * When prefix[right] - prefix[front] ≥ K, that's our candidate.
 */
int shortestSubarray(vector<int>& nums, int k) {
    int n = nums.size();
    vector<ll> prefix(n + 1, 0);
    for (int i = 0; i < n; i++)
        prefix[i + 1] = prefix[i] + nums[i];

    deque<int> dq; // Indices into prefix, with increasing prefix values
    int best = n + 1;

    for (int right = 0; right <= n; right++) {
        // Pop front: valid answers (prefix[right] - prefix[front] ≥ K)
        while (!dq.empty() && prefix[right] - prefix[dq.front()] >= k) {
            best = min(best, right - dq.front());
            dq.pop_front();
        }
        // Pop back: dominated (prefix[back] ≥ prefix[right])
        while (!dq.empty() && prefix[dq.back()] >= prefix[right])
            dq.pop_back();
        dq.push_back(right);
    }
    return best == n + 1 ? -1 : best;
}

// ============================================================================
// BINARY SEARCH ON ANSWER + WINDOW VALIDATION
// ============================================================================
/*
 * Pattern: "Find minimum window size W such that f(window) ≥ threshold."
 * Binary search on W. For each W, run fixed-size window check.
 *
 * Example: Minimum window size where max sum ≥ threshold.
 * Time: O(N log N)
 */
int minWindowSizeForSum(vector<int>& arr, ll threshold) {
    int n = arr.size();
    int lo = 1, hi = n, ans = -1;

    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        ll sum = 0;
        bool found = false;
        for (int i = 0; i < n; i++) {
            sum += arr[i];
            if (i >= mid) sum -= arr[i - mid];
            if (i >= mid - 1 && sum >= threshold) { found = true; break; }
        }
        if (found) { ans = mid; hi = mid - 1; }
        else lo = mid + 1;
    }
    return ans;
}

// ============================================================================
// LC 644 Style: Maximum Average Subarray II — Parametric Search
// ============================================================================
/*
 * Find subarray of length ≥ minLen with maximum average.
 * Binary search on the answer (average value).
 * For each guess avg: subtract avg from all elements.
 * Check if any subarray of length ≥ minLen has sum ≥ 0.
 * Use prefix sum + min prefix tracking.
 *
 * Time: O(N * log(max-min / epsilon))
 */
double maxAverageSubarrayII(vector<int>& nums, int minLen) {
    double lo = *min_element(nums.begin(), nums.end());
    double hi = *max_element(nums.begin(), nums.end());
    int n = nums.size();

    while (hi - lo > 1e-6) {
        double mid = (lo + hi) / 2;

        // Check: is there a subarray of length ≥ minLen with avg ≥ mid?
        // Subtract mid from all, check if max subarray of len ≥ minLen has sum ≥ 0
        vector<double> diff(n);
        for (int i = 0; i < n; i++) diff[i] = nums[i] - mid;

        double prefix = 0, minPrefix = 0, prevPrefix = 0;
        bool found = false;
        for (int i = 0; i < n; i++) {
            prefix += diff[i];
            if (i >= minLen - 1) {
                // Can form subarray of length ≥ minLen
                if (i >= minLen) {
                    prevPrefix += diff[i - minLen];
                    minPrefix = min(minPrefix, prevPrefix);
                }
                if (prefix - minPrefix >= -1e-9) {
                    found = true;
                    break;
                }
            }
        }
        if (found) lo = mid;
        else hi = mid;
    }
    return lo;
}

// ============================================================================
// LC 1793: Maximum Score of a Good Subarray — Expand from Index k
// ============================================================================
/*
 * Score = min(subarray) * length(subarray). Subarray must include index k.
 * Expand outward from k using two pointers. Always expand toward larger value.
 *
 * Time: O(N), Space: O(1)
 */
int maximumScore(vector<int>& nums, int k) {
    int n = nums.size();
    int left = k, right = k;
    int minVal = nums[k], best = nums[k];

    while (left > 0 || right < n - 1) {
        // Expand toward the larger neighbor to keep min as high as possible
        int leftVal = (left > 0) ? nums[left - 1] : 0;
        int rightVal = (right < n - 1) ? nums[right + 1] : 0;

        if (leftVal >= rightVal) {
            left--;
            minVal = min(minVal, nums[left]);
        } else {
            right++;
            minVal = min(minVal, nums[right]);
        }
        best = max(best, minVal * (right - left + 1));
    }
    return best;
}

int main() {
    // LC 862: Shortest subarray sum ≥ K (with negatives!)
    vector<int> nums1 = {2, -1, 2};
    cout << "Shortest sum≥3: " << shortestSubarray(nums1, 3) << "\n"; // 3

    vector<int> nums2 = {84, -37, 32, 40, 95};
    cout << "Shortest sum≥167: " << shortestSubarray(nums2, 167) << "\n"; // 3

    // Binary search on window size
    vector<int> arr = {1, 4, 2, 5, 3};
    cout << "Min window for sum≥10: " << minWindowSizeForSum(arr, 10) << "\n"; // 3

    // Max average subarray (length ≥ 4)
    vector<int> nums3 = {1, 12, -5, -6, 50, 3};
    printf("Max avg (minLen=4): %.5f\n", maxAverageSubarrayII(nums3, 4)); // 12.75

    // Max score good subarray
    vector<int> nums4 = {1, 4, 3, 7, 4, 5};
    cout << "Max score (k=3): " << maximumScore(nums4, 3) << "\n"; // 15

    return 0;
}

