/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Advanced Competitive Patterns — Fixed Window
 *  Level   : Hard → GM (CF 1800 → 2400+)
 * ============================================================================
 *
 *  ▶ ADVANCED PATTERNS:
 *  ────────────────────
 *  1. Count windows satisfying inequality (combine with monotonic deque)
 *  2. Contribution counting per index (how many windows contain index i?)
 *  3. Binary search on K + fixed window check (parametric search)
 *  4. Window constraint validation (does window satisfy complex property?)
 *  5. Offline query on fixed windows (sort queries by window size)
 *  6. Bitwise range contribution (each bit contributes independently)
 *
 *  PROBLEMS:
 *  LC 2444 — Count Subarrays With Fixed Bounds (min=minK, max=maxK)
 *            https://leetcode.com/problems/count-subarrays-with-fixed-bounds/
 *  LC 2762 — Continuous Subarrays (max-min ≤ 2, count with deque)
 *            https://leetcode.com/problems/continuous-subarrays/
 *  LC 992  — Subarrays with K Different Integers (exactly K = atMost(K) - atMost(K-1))
 *            https://leetcode.com/problems/subarrays-with-k-different-integers/
 *  LC 2537 — Count the Number of Good Subarrays (at least K pairs)
 *            https://leetcode.com/problems/count-the-number-of-good-subarrays/
 *  LC 1248 — Count Number of Nice Subarrays (exactly K odds)
 *            https://leetcode.com/problems/count-number-of-nice-subarrays/
 *  CF 1609D — Social Network (multiset + fixed window, 1600)
 *            https://codeforces.com/problemset/problem/1609/D
 *  CF 846C  — Four Segments (fixed window + binary search, 1800)
 *            https://codeforces.com/problemset/problem/846/C
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>
#include <algorithm>
using namespace std;
using ll = long long;

// ============================================================================
// LC 2444: Count Subarrays With Fixed Bounds — Window Constraint
// ============================================================================
/*
 * Count subarrays where min = minK and max = maxK.
 *
 * Track: lastBad (out-of-range element), lastMin (last minK occurrence),
 *        lastMax (last maxK occurrence).
 * For each right, valid subarrays end at right and start after lastBad,
 * with both lastMin and lastMax in range.
 * count += max(0, min(lastMin, lastMax) - lastBad)
 *
 * Time: O(N), Space: O(1)
 */
long long countSubarrays_fixedBounds(vector<int>& nums, int minK, int maxK) {
    ll count = 0;
    int lastBad = -1, lastMin = -1, lastMax = -1;

    for (int i = 0; i < (int)nums.size(); i++) {
        if (nums[i] < minK || nums[i] > maxK)
            lastBad = i; // Invalid element resets the window
        if (nums[i] == minK) lastMin = i;
        if (nums[i] == maxK) lastMax = i;

        int validStart = min(lastMin, lastMax);
        count += max(0, validStart - lastBad);
    }
    return count;
}

// ============================================================================
// LC 2762: Continuous Subarrays — Count with max-min ≤ 2 (Deque)
// ============================================================================
/*
 * Count subarrays where |nums[i] - nums[j]| ≤ 2 for all i,j in subarray.
 * Equivalent: max - min ≤ 2.
 * Use two deques (maxDeque + minDeque) to track max and min.
 * Variable window: shrink left until max - min ≤ 2.
 * count += (right - left + 1) for each right.
 *
 * Time: O(N), Space: O(N)
 */
long long continuousSubarrays(vector<int>& nums) {
    int n = nums.size();
    deque<int> maxDq, minDq;
    ll count = 0;
    int left = 0;

    for (int right = 0; right < n; right++) {
        while (!maxDq.empty() && nums[maxDq.back()] <= nums[right]) maxDq.pop_back();
        maxDq.push_back(right);
        while (!minDq.empty() && nums[minDq.back()] >= nums[right]) minDq.pop_back();
        minDq.push_back(right);

        while (nums[maxDq.front()] - nums[minDq.front()] > 2) {
            left++;
            if (maxDq.front() < left) maxDq.pop_front();
            if (minDq.front() < left) minDq.pop_front();
        }
        count += (right - left + 1);
    }
    return count;
}

// ============================================================================
// "Exactly K" = "At Most K" - "At Most K-1" Pattern
// ============================================================================
/*
 * This is the MOST IMPORTANT advanced counting pattern:
 * count(exactly K distinct) = count(at most K) - count(at most K-1)
 *
 * Works for: distinct elements, odd numbers, specific values, etc.
 * Each "at most K" is a variable sliding window problem.
 */

// Helper: count subarrays with at most K distinct elements
ll atMostKDistinct(vector<int>& nums, int k) {
    int n = nums.size();
    unordered_map<int, int> freq;
    ll count = 0;
    int left = 0;

    for (int right = 0; right < n; right++) {
        freq[nums[right]]++;
        while ((int)freq.size() > k) {
            freq[nums[left]]--;
            if (freq[nums[left]] == 0) freq.erase(nums[left]);
            left++;
        }
        count += (right - left + 1);
    }
    return count;
}

// LC 992: Subarrays with Exactly K Different Integers
int subarraysWithKDistinct(vector<int>& nums, int k) {
    return (int)(atMostKDistinct(nums, k) - atMostKDistinct(nums, k - 1));
}

// LC 1248: Count Nice Subarrays (exactly K odd numbers)
int numberOfSubarrays(vector<int>& nums, int k) {
    // Transform: odd → 1, even → 0. Count subarrays with sum = K.
    // = atMost(K) - atMost(K-1)
    auto atMost = [&](int target) -> ll {
        ll count = 0;
        int left = 0, oddCount = 0;
        for (int right = 0; right < (int)nums.size(); right++) {
            oddCount += (nums[right] % 2);
            while (oddCount > target) {
                oddCount -= (nums[left] % 2);
                left++;
            }
            count += (right - left + 1);
        }
        return count;
    };
    return (int)(atMost(k) - atMost(k - 1));
}

// ============================================================================
// Contribution Counting Per Index — How many K-windows contain index i?
// ============================================================================
/*
 * For fixed window size K in array of size N:
 * Index i is in windows starting from max(0, i-K+1) to min(i, N-K).
 * Count = min(i, N-K) - max(0, i-K+1) + 1
 *       = min(i+1, K, N-i, N-K+1)
 *
 * This lets you compute total contribution of all elements across all windows.
 */
ll totalContribution(vector<int>& arr, int k) {
    int n = arr.size();
    ll total = 0;
    for (int i = 0; i < n; i++) {
        int windows = min({i + 1, k, n - i, n - k + 1});
        total += (ll)arr[i] * windows;
    }
    return total;
}

// ============================================================================
// Binary Search on K + Fixed Window Check
// ============================================================================
/*
 * Pattern: "Find minimum K such that some fixed-window property holds."
 * Binary search on K. For each K, run fixed window check.
 * Example: "Find smallest K where max window sum ≥ threshold"
 */
int minKForSumThreshold(vector<int>& arr, int threshold) {
    int n = arr.size();
    int lo = 1, hi = n, ans = -1;

    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        // Check if any window of size mid has sum ≥ threshold
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
// Bitwise Range Contribution — Each bit independent
// ============================================================================
/*
 * For bitwise OR/AND/XOR of all windows: process each bit independently.
 * For bit b: count how many windows have that bit set (OR) / all set (AND).
 * Then reconstruct the answer bit by bit.
 *
 * This is the standard approach for bitwise window problems in competitive.
 */
ll sumOfORAllKWindows(vector<int>& arr, int k) {
    int n = arr.size();
    ll totalOR = 0;

    for (int b = 0; b < 30; b++) {
        // Count windows where bit b is set in OR (= at least one element has bit b)
        // = totalWindows - windows where NO element has bit b
        int zeroRun = 0; // Consecutive elements without bit b
        ll windowsWithoutBit = 0;

        for (int i = 0; i < n; i++) {
            if (arr[i] & (1 << b)) zeroRun = 0;
            else zeroRun++;

            if (i >= k - 1) {
                if (zeroRun >= k) windowsWithoutBit++;
                // Adjust when leaving window
                // (simplified: if zeroRun tracks consecutive zeros)
            }
        }
        ll totalWindows = n - k + 1;
        ll windowsWithBit = totalWindows - windowsWithoutBit;
        totalOR += windowsWithBit * (1LL << b);
    }
    return totalOR;
}

int main() {
    // Fixed bounds
    vector<int> nums1 = {1, 3, 5, 2, 7, 5};
    cout << "Fixed bounds [1,5]: " << countSubarrays_fixedBounds(nums1, 1, 5) << "\n"; // 2

    // Continuous subarrays (|diff| ≤ 2)
    vector<int> nums2 = {5, 4, 2, 4};
    cout << "Continuous: " << continuousSubarrays(nums2) << "\n"; // 8

    // Exactly K distinct
    vector<int> nums3 = {1, 2, 1, 2, 3};
    cout << "Exactly 2 distinct: " << subarraysWithKDistinct(nums3, 2) << "\n"; // 7

    // Nice subarrays (exactly K odds)
    vector<int> nums4 = {1, 1, 2, 1, 1};
    cout << "Nice (k=3): " << numberOfSubarrays(nums4, 3) << "\n"; // 2

    // Contribution
    vector<int> arr = {1, 2, 3, 4, 5};
    cout << "Total contribution (k=3): " << totalContribution(arr, 3) << "\n"; // 28

    // Binary search on K
    cout << "Min K for sum≥10: " << minKForSumThreshold(arr, 10) << "\n"; // 3

    return 0;
}

