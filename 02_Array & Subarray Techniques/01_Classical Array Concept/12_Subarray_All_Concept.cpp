/*
Author: Sarvan.DP.GrandMaster
Created : 2026-01-07 15:17:08
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <climits>
#include <random>
#include <chrono>
#include <cassert>
#include <unordered_map>
#include <deque>

using namespace std;

// --- Type Definitions ---
using i64 = long long;
using u64 = unsigned long long;
using ld  = long double;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int, int>;
using pll = pair<i64, i64>;

// --- Constants ---
constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD   = 1'000'000'007LL;
constexpr i64 MOD9  = 998'244'353LL;
constexpr ld PI     = 3.14159265358979323846;

// --- Random Number Generator ---
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// --- Macros ---
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

// Input helper
template<class T>
void read(vec<T> &v) {
    for (auto &x : v) cin >> x;
}
#define nl '\n'
#define YES cout << "YES" << nl
#define NO cout << "NO" << nl

inline i64 gcd(i64 a, i64 b) { return std::gcd(a, b); }
inline i64 lcm(i64 a, i64 b) { return (a / std::gcd(a, b)) * b; }

inline i64 modpow(i64 base, i64 exp, i64 mod = MOD) {
    i64 res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

// -------------------------------------------------------------
// SUBARRAY ALGORITHMS (Basic to GM)
// -------------------------------------------------------------

// 1. DEBUG TOOL: Print All Subarrays
// Useful for small N to visualize the problem.
void printAllSubarrays(const vec<int>& arr) {
    int n = sz(arr);
    cout << "--- All Subarrays ---" << nl;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            cout << "[";
            for (int k = i; k <= j; k++) {
                cout << arr[k] << (k < j ? ", " : "");
            }
            cout << "] ";
        }
        cout << nl;
    }
    cout << "---------------------" << nl;
}

// 2. BRUTE FORCE (Level 0)
// Complexity: O(N^3)
// Status: TLE for N > 500
void maxSubArraySumBruteForce(const vec<int>& arr) {
    int n = sz(arr);
    i64 maxSum = -INF64; // GM Tip: Always use i64 for sums

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            i64 currSum = 0;
            for (int k = i; k <= j; k++) {
                currSum += arr[k];
            }
            maxSum = max(maxSum, currSum);
        }
    }
    cout << "Brute Force (O(N^3)): " << maxSum << nl;
}

// 3. OPTIMIZED BRUTE FORCE (Level 1)
// Complexity: O(N^2)
// Status: Accepted for N <= 5000
void maxSubArraySum(const vec<int>& arr) {
    int n = sz(arr);
    i64 maxSum = -INF64;

    for (int i = 0; i < n; i++) {
        i64 currSum = 0;
        for (int j = i; j < n; j++) {
            currSum += arr[j]; // Just add the new element
            maxSum = max(maxSum, currSum);
        }
    }
    cout << "Optimized Brute (O(N^2)): " << maxSum << nl;
}

// 4. PREFIX SUM APPROACH (Level 1.5)
// Complexity: O(N^2) Time | O(N) Space
// Status: Useful conceptual step towards O(N)
void maxSubarraySum_Prefix(const vec<int>& arr) {
    int n = sz(arr);

    // GM Tip: Prefix array is size N+1 to handle 0-index cleanly
    // GM Tip: Always use i64 for prefix sums
    vec<i64> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + arr[i];
    }

    i64 maxSum = -INF64;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            // Sum(i, j) = Prefix[j+1] - Prefix[i]
            i64 currSum = prefix[j + 1] - prefix[i];
            maxSum = max(maxSum, currSum);
        }
    }
    cout << "Prefix Sum (O(N^2)): " << maxSum << nl;
}

// 5. KADANE'S ALGORITHM (Level GM)
// Complexity: O(N) Time | O(1) Space
// Status: Optimal
void Kadanes_Algorithm(const vec<int>& arr) {
    int n = sz(arr);
    if (n == 0) return;

    i64 maxSum = -INF64; // Initialize to -Infinity to handle negative arrays
    i64 currSum = 0;

    for (int val : arr) {
        currSum += val;

        // GM Logic: Update Max BEFORE resetting.
        // This handles cases like [-5, -2, -9] correctly.
        // Iteration 2: currSum = -2. maxSum becomes -2. Then reset currSum.
        maxSum = max(maxSum, currSum);

        if (currSum < 0) {
            currSum = 0;
        }
    }
    cout << "Kadane's (O(N)): " << maxSum << nl;
}

// Kadane's Algorithm with Subarray Indices:
struct SubarrayResult {
    i64 maxSum;
    int strt;
    int end;
};
SubarrayResult kadaneWithIndices(const vec<int>& arr) {
    int n = sz(arr);
    i64 maxSum = -INF64;
    i64 currSum = 0;

    int start = 0;
    int end = 0;
    int tempStart = 0;

    for (int i = 0; i < n; i++) {
        currSum += arr[i];

        // Found a new maximum sum, update indices
        if (currSum > maxSum) {
            maxSum = currSum;
            start = tempStart;
            end = i;
        }

        // If sum becomes negative, reset and move tempStart
        if (currSum < 0) {
            currSum = 0;
            tempStart = i + 1;
        }
    }

    return {maxSum, start, end};
}

// Minimum Subarray Sum
void Kadanes_AlgorithmMinSubarraySum(const vec<int>& arr) {
    int n = sz(arr);
    if (n == 0) return;

    i64 minSum = INF64;
    i64 currSum = 0;

    for (int val : arr) {
        currSum += val;
        minSum = min(minSum, currSum);

        // If current sum becomes positive, reset to 0
        if (currSum > 0) currSum = 0;
    }
    cout << "Minimum Subarray sum : " << minSum << nl;
}

// Maximum Product Subarray
// largest positive × negative → large negative
// largest negative × negative → large positive
void maxProductSubarray(const vec<int>& arr){
    int n = sz(arr);

    i64 maxProduct = arr[0];
    i64 currMin = arr[0];
    i64 currMax = arr[0]; // Track minimum (for negative numbers)

    for (int i = 1; i < n; i++){
        // When multiplied by negative, max becomes min and vice versa
        if (arr[i] < 0){
            swap(currMax, currMin);
        }

        currMax = max((i64)arr[i], currMax * arr[i]);
        currMin = min((i64)arr[i], currMin * arr[i]);

        maxProduct = max(maxProduct, currMax);
    }

    cout << "Maximum Product Subarray : " << maxProduct << nl;
}

// =============================================================================
//  ADVANCED KADANE'S & SUBARRAY CONCEPTS (GM Level)
// =============================================================================

// -------------------------------------------------------------
// 6. KADANE'S — MAXIMUM CIRCULAR SUBARRAY SUM (LC 918)
// -------------------------------------------------------------
// Array is circular: after last element, it wraps to first.
// Two cases:
//   Case 1: Max subarray is in the middle (normal Kadane's)
//   Case 2: Max subarray wraps around (totalSum - minSubarraySum)
//
// Answer = max(Case 1, Case 2)
//
// EDGE CASE: If ALL elements are negative, Case 2 gives 0 (empty subarray).
//            But empty is not allowed → return Case 1 (max single element).
//
// Time: O(N), Space: O(1)

i64 maxCircularSubarraySum(const vec<int>& arr) {
    int n = sz(arr);
    if (n == 0) return 0;

    // Normal Kadane's for max subarray
    i64 maxSum = -INF64, currMax = 0;
    // Kadane's for min subarray
    i64 minSum = INF64, currMin = 0;
    i64 totalSum = 0;

    for (int val : arr) {
        totalSum += val;

        currMax += val;
        maxSum = max(maxSum, currMax);
        if (currMax < 0) currMax = 0;

        currMin += val;
        minSum = min(minSum, currMin);
        if (currMin > 0) currMin = 0;
    }

    // Edge case: all elements negative
    // totalSum - minSum == 0 means empty subarray (not allowed)
    if (maxSum < 0) return maxSum; // All negative → return max element

    return max(maxSum, totalSum - minSum);
}

// GM Proof of circular case:
// The "wrap-around" subarray = everything EXCEPT some middle subarray.
// To MAXIMIZE wrap-around = totalSum - (MINIMUM middle subarray).
// So we run Kadane's for min, and the answer is totalSum - minSubarray.

// -------------------------------------------------------------
// 7. KADANE'S — DP FORMULATION (Formal Version)
// -------------------------------------------------------------
// dp[i] = maximum subarray sum ending at index i
// dp[i] = max(arr[i], dp[i-1] + arr[i])
// Answer = max(dp[0], dp[1], ..., dp[n-1])
//
// Space-optimized: dp[i] only depends on dp[i-1] → use single variable.

i64 kadane_dp(const vec<int>& arr) {
    int n = sz(arr);
    if (n == 0) return 0;

    // Full DP array (for understanding)
    vec<i64> dp(n);
    dp[0] = arr[0];
    i64 ans = dp[0];

    for (int i = 1; i < n; i++) {
        dp[i] = max((i64)arr[i], dp[i - 1] + arr[i]);
        ans = max(ans, dp[i]);
    }

    cout << "Kadane DP array: ";
    for (int i = 0; i < n; i++) cout << dp[i] << " ";
    cout << nl;
    cout << "Kadane DP answer: " << ans << nl;

    return ans;
}

// -------------------------------------------------------------
// 8. DIVIDE AND CONQUER — Maximum Subarray (O(N log N))
// -------------------------------------------------------------
// Educational purpose. Slower than Kadane's but important concept.
// Split array in half. Max subarray is either:
//   (a) Entirely in left half
//   (b) Entirely in right half
//   (c) Crossing the midpoint
// For (c): expand left from mid, expand right from mid+1.

i64 maxCrossingSum(const vec<int>& arr, int lo, int mid, int hi) {
    // Expand LEFT from mid
    i64 leftMax = -INF64, sum = 0;
    for (int i = mid; i >= lo; i--) {
        sum += arr[i];
        leftMax = max(leftMax, sum);
    }

    // Expand RIGHT from mid+1
    i64 rightMax = -INF64;
    sum = 0;
    for (int i = mid + 1; i <= hi; i++) {
        sum += arr[i];
        rightMax = max(rightMax, sum);
    }

    return leftMax + rightMax;
}

i64 maxSubarrayDivideConquer(const vec<int>& arr, int lo, int hi) {
    if (lo == hi) return arr[lo]; // Base case: single element

    int mid = lo + (hi - lo) / 2;

    i64 leftMax = maxSubarrayDivideConquer(arr, lo, mid);
    i64 rightMax = maxSubarrayDivideConquer(arr, mid + 1, hi);
    i64 crossMax = maxCrossingSum(arr, lo, mid, hi);

    return max({leftMax, rightMax, crossMax});
}

// -------------------------------------------------------------
// 9. COUNT SUBARRAYS WITH SUM EQUAL TO K (LC 560)
// -------------------------------------------------------------
// Use prefix sum + HashMap.
// If prefix[j] - prefix[i] = K, then subarray [i+1..j] has sum K.
// Equivalently: for each j, count how many previous prefix[i] == prefix[j] - K.
//
// Time: O(N), Space: O(N)
// GM Note: THIS IS THE #1 MOST IMPORTANT SUBARRAY PATTERN.

int countSubarraysWithSumK(const vec<int>& arr, int k) {
    unordered_map<i64, int> prefixCount;
    prefixCount[0] = 1; // Empty prefix has sum 0

    i64 prefixSum = 0;
    int count = 0;

    for (int x : arr) {
        prefixSum += x;

        // How many previous prefixes equal (prefixSum - K)?
        i64 target = prefixSum - k;
        if (prefixCount.count(target)) {
            count += prefixCount[target];
        }

        prefixCount[prefixSum]++;
    }
    return count;
}

// GM Dry Run: arr = [1, 2, 3], K = 3
// prefix:   0  1  3  6
// At i=0: prefixSum=1, target=1-3=-2, not found. Store {0:1, 1:1}
// At i=1: prefixSum=3, target=3-3=0, found 1! count=1. Store {0:1, 1:1, 3:1}
// At i=2: prefixSum=6, target=6-3=3, found 1! count=2.
// Subarrays: [1,2] and [3]. Correct!

// -------------------------------------------------------------
// 10. COUNT SUBARRAYS WITH SUM DIVISIBLE BY K (LC 974)
// -------------------------------------------------------------
// Use prefix sum mod K. If prefix[i] % K == prefix[j] % K, then
// subarray [i+1..j] has sum divisible by K.
// Count using remainder frequency.
//
// GM Warning: Handle negative remainders! In C++, -3 % 5 = -3 (not 2).
//             Fix: ((prefixSum % k) + k) % k

int countSubarraysDivisibleByK(const vec<int>& arr, int k) {
    unordered_map<int, int> remCount;
    remCount[0] = 1;

    i64 prefixSum = 0;
    int count = 0;

    for (int x : arr) {
        prefixSum += x;
        int rem = ((prefixSum % k) + k) % k; // Safe modulo

        count += remCount[rem];
        remCount[rem]++;
    }
    return count;
}

// -------------------------------------------------------------
// 11. LONGEST SUBARRAY WITH SUM = K
// -------------------------------------------------------------
// Use prefix sum + HashMap storing FIRST occurrence of each prefix sum.
// If prefix[j] - prefix[i] = K and i is earliest → longest subarray.
// Time: O(N), Space: O(N)

int longestSubarrayWithSumK(const vec<int>& arr, i64 k) {
    unordered_map<i64, int> firstOccurrence;
    firstOccurrence[0] = -1; // Empty prefix at index -1

    i64 prefixSum = 0;
    int maxLen = 0;

    for (int i = 0; i < sz(arr); i++) {
        prefixSum += arr[i];

        if (firstOccurrence.count(prefixSum - k)) {
            maxLen = max(maxLen, i - firstOccurrence[prefixSum - k]);
        }

        // Only store FIRST occurrence (to maximize length)
        if (!firstOccurrence.count(prefixSum)) {
            firstOccurrence[prefixSum] = i;
        }
    }
    return maxLen;
}

// Variant: Shortest subarray with sum = K
int shortestSubarrayWithSumK(const vec<int>& arr, i64 k) {
    unordered_map<i64, int> lastOccurrence;
    lastOccurrence[0] = -1;

    i64 prefixSum = 0;
    int minLen = INT_MAX;

    for (int i = 0; i < sz(arr); i++) {
        prefixSum += arr[i];

        if (lastOccurrence.count(prefixSum - k)) {
            minLen = min(minLen, i - lastOccurrence[prefixSum - k]);
        }

        // Store LAST occurrence (to minimize length)
        lastOccurrence[prefixSum] = i;
    }
    return (minLen == INT_MAX) ? -1 : minLen;
}

// -------------------------------------------------------------
// 12. LARGEST SUBARRAY WITH EQUAL 0s AND 1s
// -------------------------------------------------------------
// Convert 0 → -1. Now problem becomes: longest subarray with sum 0.
// Time: O(N), Space: O(N)
// GM Note: This transformation trick is VERY powerful.

int longestSubarrayEqual01(const vec<int>& arr) {
    // Transform: 0 → -1
    vec<int> transformed(sz(arr));
    for (int i = 0; i < sz(arr); i++) {
        transformed[i] = (arr[i] == 0) ? -1 : 1;
    }

    // Now find longest subarray with sum = 0
    return longestSubarrayWithSumK(transformed, 0);
}

// -------------------------------------------------------------
// 13. SUBARRAY WITH GIVEN XOR (Important for Interviews)
// -------------------------------------------------------------
// Count subarrays where XOR of all elements = K.
// Uses prefix XOR + HashMap (same pattern as sum!).
// Property: prefixXOR[j] ^ prefixXOR[i] = XOR(i+1..j)
//           If this equals K, then prefixXOR[i] = prefixXOR[j] ^ K

int countSubarraysWithXOR(const vec<int>& arr, int k) {
    unordered_map<int, int> prefixXORCount;
    prefixXORCount[0] = 1;

    int prefixXOR = 0;
    int count = 0;

    for (int x : arr) {
        prefixXOR ^= x;
        int target = prefixXOR ^ k;

        if (prefixXORCount.count(target)) {
            count += prefixXORCount[target];
        }
        prefixXORCount[prefixXOR]++;
    }
    return count;
}

// -------------------------------------------------------------
// 14. MINIMUM SIZE SUBARRAY SUM (LC 209) — Sliding Window
// -------------------------------------------------------------
// Find shortest subarray with sum >= target.
// Sliding Window (expand right, shrink left).
// Time: O(N), Space: O(1)
// PREREQUISITE: All elements must be POSITIVE for this approach.

int minSizeSubarraySum(const vec<int>& arr, int target) {
    int n = sz(arr);
    int minLen = INT_MAX;
    i64 windowSum = 0;
    int left = 0;

    for (int right = 0; right < n; right++) {
        windowSum += arr[right];

        // Shrink window while sum >= target
        while (windowSum >= target) {
            minLen = min(minLen, right - left + 1);
            windowSum -= arr[left];
            left++;
        }
    }
    return (minLen == INT_MAX) ? 0 : minLen;
}

// -------------------------------------------------------------
// 15. MAXIMUM SUM SUBARRAY OF SIZE K (Fixed Window)
// -------------------------------------------------------------
// Sliding window of fixed size K.
// Time: O(N), Space: O(1)

i64 maxSumSubarrayOfSizeK(const vec<int>& arr, int k) {
    int n = sz(arr);
    if (k > n) return -1;

    i64 windowSum = 0;
    for (int i = 0; i < k; i++) windowSum += arr[i];

    i64 maxSum = windowSum;

    for (int i = k; i < n; i++) {
        windowSum += arr[i] - arr[i - k]; // Slide: add right, remove left
        maxSum = max(maxSum, windowSum);
    }
    return maxSum;
}

// -------------------------------------------------------------
// 16. MAXIMUM SUM SUBARRAY WITH LENGTH IN RANGE [minL, maxL]
// -------------------------------------------------------------
// Combine prefix sum with sliding window / deque.
// For each j, find i in [j-maxL, j-minL] that minimizes prefix[i].
// Use a deque to maintain minimum prefix in the window.
// Time: O(N), Space: O(N)

i64 maxSumSubarrayLengthRange(const vec<int>& arr, int minL, int maxL) {
    int n = sz(arr);
    vec<i64> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + arr[i];

    deque<int> dq; // Stores indices of prefix array
    i64 ans = -INF64;

    for (int j = minL; j <= n; j++) {
        // Add prefix[j - minL] to deque (candidate for subtraction)
        int newIdx = j - minL;
        while (!dq.empty() && prefix[dq.back()] >= prefix[newIdx]) {
            dq.pop_back();
        }
        dq.push_back(newIdx);

        // Remove indices outside the valid range [j - maxL, j - minL]
        while (!dq.empty() && dq.front() < j - maxL) {
            dq.pop_front();
        }

        // prefix[j] - prefix[dq.front()] is the max sum ending at j
        if (!dq.empty()) {
            ans = max(ans, prefix[j] - prefix[dq.front()]);
        }
    }
    return ans;
}

// -------------------------------------------------------------
// 17. KADANE'S FOR MAXIMUM SUM WITH NO TWO ADJACENT ELEMENTS
// -------------------------------------------------------------
// Not exactly subarray but a famous Kadane variant.
// dp[i] = max(dp[i-1], dp[i-2] + arr[i])
// LC 198: House Robber
// Time: O(N), Space: O(1)

i64 maxSumNoAdjacent(const vec<int>& arr) {
    int n = sz(arr);
    if (n == 0) return 0;
    if (n == 1) return arr[0];

    i64 prev2 = 0;        // dp[i-2]
    i64 prev1 = arr[0];   // dp[i-1]

    for (int i = 1; i < n; i++) {
        i64 curr = max(prev1, prev2 + arr[i]);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

// -------------------------------------------------------------
// 18. KADANE'S ON 2D — MAXIMUM SUM RECTANGLE IN MATRIX
// -------------------------------------------------------------
// Fix left and right columns. Compress each row into 1D array.
// Apply Kadane's on the compressed array.
// Time: O(N² × M) or O(N × M²), Space: O(N)
// LC 363 variant (with constraint)

struct Rect {
    i64 sum;
    int top, bottom, left, right;
};

Rect maxSumRectangle(const vvec<int>& matrix) {
    int rows = sz(matrix), cols = sz(matrix[0]);
    Rect best = {-INF64, 0, 0, 0, 0};

    for (int left = 0; left < cols; left++) {
        vec<i64> rowSum(rows, 0); // Compressed column sums

        for (int right = left; right < cols; right++) {
            // Add column 'right' to the running row sums
            for (int r = 0; r < rows; r++) {
                rowSum[r] += matrix[r][right];
            }

            // Apply Kadane's on rowSum to find best top-bottom
            i64 currSum = 0;
            i64 maxSum = -INF64;
            int tempTop = 0, bestTop = 0, bestBottom = 0;

            for (int r = 0; r < rows; r++) {
                currSum += rowSum[r];
                if (currSum > maxSum) {
                    maxSum = currSum;
                    bestTop = tempTop;
                    bestBottom = r;
                }
                if (currSum < 0) {
                    currSum = 0;
                    tempTop = r + 1;
                }
            }

            if (maxSum > best.sum) {
                best = {maxSum, bestTop, bestBottom, left, right};
            }
        }
    }
    return best;
}

// -------------------------------------------------------------
// 19. PRINT ALL SUBARRAYS (with Sum for each)
// -------------------------------------------------------------
// Enhanced debug version with sum tracking.

void printAllSubarraysWithSum(const vec<int>& arr) {
    int n = sz(arr);
    if (n > 15) {
        cout << "Skipping print (N too large). Total subarrays: "
             << 1LL * n * (n + 1) / 2 << nl;
        return;
    }

    cout << "--- All Subarrays with Sum ---" << nl;
    for (int i = 0; i < n; i++) {
        i64 sum = 0;
        for (int j = i; j < n; j++) {
            sum += arr[j];
            cout << "[";
            for (int k = i; k <= j; k++) {
                cout << arr[k] << (k < j ? "," : "");
            }
            cout << "] sum=" << sum << "  ";
        }
        cout << nl;
    }
}

// -------------------------------------------------------------
// 20. COUNT TOTAL SUBARRAYS (Formulas)
// -------------------------------------------------------------
/*
 * SUBARRAY COUNTING FORMULAS (GM Must-Know):
 *
 * Total subarrays of array size N:
 *   N(N+1)/2
 *
 * Total subarrays containing index i:
 *   (i + 1) × (N - i)
 *   Because: i+1 choices for start (0..i), N-i choices for end (i..N-1)
 *
 * Contribution of arr[i] to sum of all subarrays:
 *   arr[i] × (i + 1) × (N - i)
 *
 * Sum of all subarray sums:
 *   Σ arr[i] × (i + 1) × (N - i)  for i = 0 to N-1
 *
 * Total subarrays of length exactly K:
 *   N - K + 1
 *
 * Total subarrays of length at least K:
 *   (N - K + 1) × (N - K + 2) / 2
 *
 * Total subarrays of length at most K:
 *   K×N - K×(K-1)/2    (when K ≤ N)
 */

i64 sumOfAllSubarraySums(const vec<int>& arr) {
    int n = sz(arr);
    i64 total = 0;
    for (int i = 0; i < n; i++) {
        // arr[i] appears in (i+1) × (n-i) subarrays
        total += (i64)arr[i] * (i + 1) * (n - i);
    }
    return total;
}

// -------------------------------------------------------------
// KADANE'S COMPLETE VARIANT CHEAT SHEET
// -------------------------------------------------------------
/*
 * ┌───────────────────────────────────────┬────────────┬───────────┐
 * │ Kadane's Variant                      │ Time       │ Space     │
 * ├───────────────────────────────────────┼────────────┼───────────┤
 * │ Max Subarray Sum                      │ O(N)       │ O(1)      │
 * │ Max Subarray Sum with Indices         │ O(N)       │ O(1)      │
 * │ Min Subarray Sum                      │ O(N)       │ O(1)      │
 * │ Max Product Subarray                  │ O(N)       │ O(1)      │
 * │ Max Circular Subarray Sum             │ O(N)       │ O(1)      │
 * │ Kadane DP Array Version               │ O(N)       │ O(N)      │
 * │ Divide & Conquer Max Subarray         │ O(N log N) │ O(log N)  │
 * │ Count Subarrays with Sum = K          │ O(N)       │ O(N)      │
 * │ Count Subarrays Sum Div by K          │ O(N)       │ O(N)      │
 * │ Longest Subarray with Sum = K         │ O(N)       │ O(N)      │
 * │ Shortest Subarray with Sum = K        │ O(N)       │ O(N)      │
 * │ Largest Subarray Equal 0s and 1s      │ O(N)       │ O(N)      │
 * │ Subarray with Given XOR               │ O(N)       │ O(N)      │
 * │ Min Size Subarray Sum >= Target       │ O(N)       │ O(1)      │
 * │ Max Sum Fixed Window Size K           │ O(N)       │ O(1)      │
 * │ Max Sum Length in [minL, maxL]        │ O(N)       │ O(N)      │
 * │ Max Sum No Adjacent (House Robber)    │ O(N)       │ O(1)      │
 * │ Max Sum Rectangle in 2D Matrix       │ O(N²M)     │ O(N)      │
 * │ Sum of All Subarray Sums             │ O(N)       │ O(1)      │
 * └───────────────────────────────────────┴────────────┴───────────┘
 *
 * PATTERN RECOGNITION:
 *   "Max/Min subarray sum"         → Kadane's
 *   "Count subarrays with sum=K"   → Prefix Sum + HashMap
 *   "Longest subarray with sum=K"  → Prefix Sum + First Occurrence Map
 *   "Shortest subarray sum >= K"   → Sliding Window (positive) or Deque
 *   "Subarray with XOR = K"        → Prefix XOR + HashMap
 *   "Fixed window size K"          → Sliding Window
 *   "Length in range [L, R]"       → Prefix Sum + Deque
 */

void solve() {
    int n;
    cin >> n;
    vec<int> arr(n);
    read(arr);

    // === BASIC: Print All Subarrays ===
    printAllSubarraysWithSum(arr);

    // === BRUTE FORCE PROGRESSION ===
    maxSubArraySumBruteForce(arr);
    maxSubArraySum(arr);
    maxSubarraySum_Prefix(arr);

    // === KADANE'S CORE ===
    Kadanes_Algorithm(arr);
    Kadanes_AlgorithmMinSubarraySum(arr);
    maxProductSubarray(arr);

    // === KADANE'S WITH INDICES ===
    SubarrayResult res = kadaneWithIndices(arr);
    cout << "Maximum Sum: " << res.maxSum << nl;
    cout << "Start Index: " << res.strt << nl;
    cout << "End Index:   " << res.end << nl;
    cout << "Subarray: [";
    for(int i = res.strt; i <= res.end; i++) {
        cout << arr[i] << (i < res.end ? ", " : "");
    }
    cout << "]" << nl;

    // === KADANE'S DP VERSION ===
    kadane_dp(arr);

    // === CIRCULAR KADANE'S ===
    cout << "Circular Max Subarray: " << maxCircularSubarraySum(arr) << nl;

    // === DIVIDE AND CONQUER ===
    cout << "Divide & Conquer: " << maxSubarrayDivideConquer(arr, 0, n - 1) << nl;

    // === COUNT SUBARRAYS ===
    int k = 0;
    cout << nl << "--- Subarray Counting ---" << nl;
    cout << "Total subarrays: " << 1LL * n * (n + 1) / 2 << nl;
    cout << "Sum of all subarray sums: " << sumOfAllSubarraySums(arr) << nl;

    cout << "Count subarrays sum=0: " << countSubarraysWithSumK(arr, 0) << nl;
    cout << "Count subarrays sum div by 3: " << countSubarraysDivisibleByK(arr, 3) << nl;

    // === LONGEST/SHORTEST ===
    cout << "Longest subarray sum=0: " << longestSubarrayWithSumK(arr, 0) << nl;
    cout << "Shortest subarray sum=0: " << shortestSubarrayWithSumK(arr, 0) << nl;

    // === FIXED WINDOW ===
    if (n >= 3) {
        cout << "Max sum subarray of size 3: " << maxSumSubarrayOfSizeK(arr, 3) << nl;
    }

    // === NO ADJACENT ===
    cout << "Max sum no adjacent: " << maxSumNoAdjacent(arr) << nl;

    // === 2D KADANE'S DEMO ===
    vvec<int> matrix = {
        {1, 2, -1, -4, -20},
        {-8, -3, 4, 2, 1},
        {3, 8, 10, 1, 3},
        {-4, -1, 1, 7, -6}
    };
    Rect rect = maxSumRectangle(matrix);
    cout << nl << "Max Sum Rectangle: sum=" << rect.sum
         << " rows[" << rect.top << ".." << rect.bottom
         << "] cols[" << rect.left << ".." << rect.right << "]" << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    // Standard CP Main Structure
    solve();

    return 0;
}

