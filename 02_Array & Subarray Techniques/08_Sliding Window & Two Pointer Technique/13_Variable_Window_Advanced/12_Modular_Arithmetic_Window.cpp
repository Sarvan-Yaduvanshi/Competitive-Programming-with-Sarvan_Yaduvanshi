/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Sliding Window + Modular Arithmetic
 *  Level   : Medium → Hard (CF 1500 → 2000)
 * ============================================================================
 *
 *  ▶ KEY INSIGHT:
 *  ──────────────
 *  Sum(l..r) mod K = 0  ↔  prefix[r+1] mod K == prefix[l] mod K
 *
 *  This converts "subarray sum divisible by K" into a prefix remainder problem.
 *  Use hashmap/array to count/track remainders.
 *
 *  ▶ TECHNIQUES:
 *  ─────────────
 *  1. Count subarrays with sum % K == 0: Count remainder pairs
 *  2. Longest subarray with sum % K == 0: Track first occurrence of remainder
 *  3. Shortest subarray with sum % K == target: Track last occurrence
 *  4. Window with mod constraint: Sliding window + remainder tracking
 *  5. Remainder frequency window: Track how many elements have r % K == j
 *
 *  PROBLEMS:
 *  LC 974  — Subarray Sums Divisible by K (count pairs of equal remainders)
 *            https://leetcode.com/problems/subarray-sums-divisible-by-k/
 *  LC 523  — Continuous Subarray Sum (sum = multiple of K, length ≥ 2)
 *            https://leetcode.com/problems/continuous-subarray-sum/
 *  LC 1590 — Make Sum Divisible by P (remove shortest subarray)
 *            https://leetcode.com/problems/make-sum-divisible-by-p/
 *  LC 1497 — Check If Array Pairs Are Divisible by K (pair remainders)
 *            https://leetcode.com/problems/check-if-array-pairs-are-divisible-by-k/
 *  CSES 1662 — Subarray Divisibility (subarray sum % N == 0)
 *             https://cses.fi/problemset/task/1662
 *  CF 1676E — Eating Queries (prefix + sort, 1100)
 *            https://codeforces.com/problemset/problem/1676/E
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
// LC 974: Subarray Sums Divisible by K — Count Remainder Pairs
// ============================================================================
/*
 * prefix[r] - prefix[l] ≡ 0 (mod K)  ↔  prefix[r] ≡ prefix[l] (mod K)
 * Count pairs of prefix sums with same remainder.
 * If remainder r appears c times: c*(c-1)/2 pairs. Plus pairs with prefix[0]=0.
 *
 * CAREFUL with negative remainders: ((prefix % K) + K) % K to ensure non-negative.
 *
 * Time: O(N), Space: O(K)
 */
int subarraysDivByK(vector<int>& nums, int k) {
    unordered_map<int, int> remCount;
    remCount[0] = 1; // Empty prefix has remainder 0
    int prefix = 0, count = 0;

    for (int x : nums) {
        prefix += x;
        int rem = ((prefix % k) + k) % k; // Handle negatives
        count += remCount[rem];
        remCount[rem]++;
    }
    return count;
}

// ============================================================================
// LC 523: Continuous Subarray Sum — Multiple of K, length ≥ 2
// ============================================================================
/*
 * Find if there exists subarray of length ≥ 2 with sum = multiple of K.
 * prefix[j] ≡ prefix[i] (mod K) and j - i ≥ 2.
 * Store first occurrence of each remainder. If same remainder seen ≥ 2 apart → true.
 *
 * Time: O(N), Space: O(K)
 */
bool checkSubarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> firstOcc;
    firstOcc[0] = -1; // prefix[0] has remainder 0 at index -1
    int prefix = 0;

    for (int i = 0; i < (int)nums.size(); i++) {
        prefix += nums[i];
        int rem = k == 0 ? prefix : ((prefix % k) + k) % k;

        if (firstOcc.count(rem)) {
            if (i - firstOcc[rem] >= 2) return true;
        } else {
            firstOcc[rem] = i;
        }
    }
    return false;
}

// ============================================================================
// LC 1590: Make Sum Divisible by P — Remove Shortest Subarray
// ============================================================================
/*
 * Remove shortest subarray so remaining sum is divisible by P.
 * totalSum % P = target. If target == 0 → return 0.
 * Find shortest subarray with sum ≡ target (mod P).
 * prefix[r] - prefix[l] ≡ target (mod P)
 * → prefix[l] ≡ (prefix[r] - target + P) % P
 *
 * Track most recent occurrence of each remainder for shortest length.
 *
 * Time: O(N), Space: O(N)
 */
int minSubarray(vector<int>& nums, int p) {
    int n = nums.size();
    ll totalSum = 0;
    for (int x : nums) totalSum += x;
    int target = totalSum % p;
    if (target == 0) return 0;

    unordered_map<int, int> lastOcc;
    lastOcc[0] = -1;
    int prefix = 0, best = n;

    for (int i = 0; i < n; i++) {
        prefix = ((prefix + nums[i]) % p + p) % p;
        int need = ((prefix - target) % p + p) % p;
        if (lastOcc.count(need))
            best = min(best, i - lastOcc[need]);
        lastOcc[prefix] = i;
    }
    return best == n ? -1 : best;
}

// ============================================================================
// CSES 1662: Subarray Divisibility — Sum divisible by N (not K)
// ============================================================================
/*
 * Exactly like LC 974 but K = N (array size).
 * Count subarrays with sum % N == 0.
 * By pigeonhole: among N+1 prefix sums, two must have same remainder mod N.
 * So answer is always ≥ 1 for N ≥ 1.
 */
void solve_CSES1662() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;

    vector<ll> remCount(n, 0);
    remCount[0] = 1;
    ll prefix = 0, count = 0;

    for (int i = 0; i < n; i++) {
        prefix += a[i];
        int rem = ((prefix % n) + n) % n;
        count += remCount[rem];
        remCount[rem]++;
    }
    cout << count << "\n";
}

// ============================================================================
// LC 1497: Check If Array Pairs Are Divisible by K — Remainder Pairing
// ============================================================================
/*
 * Can we pair all elements such that each pair sum is divisible by K?
 * Element with remainder r must pair with element having remainder (K - r) % K.
 * Count remainders. For r=0: count must be even. For r and K-r: counts must match.
 * For r = K/2 (if K even): count must be even.
 *
 * Time: O(N), Space: O(K)
 */
bool canArrange(vector<int>& arr, int k) {
    vector<int> remCount(k, 0);
    for (int x : arr)
        remCount[((x % k) + k) % k]++;

    if (remCount[0] % 2 != 0) return false;
    for (int r = 1; r <= k / 2; r++) {
        if (r == k - r) {
            if (remCount[r] % 2 != 0) return false;
        } else {
            if (remCount[r] != remCount[k - r]) return false;
        }
    }
    return true;
}

// ============================================================================
// Longest Subarray with Sum % K == target — First Occurrence of Remainder
// ============================================================================
int longestSubarraySumModK(vector<int>& arr, int k, int target) {
    unordered_map<int, int> firstOcc;
    firstOcc[0] = -1;
    int prefix = 0, best = 0;

    for (int i = 0; i < (int)arr.size(); i++) {
        prefix = ((prefix + arr[i]) % k + k) % k;
        int need = ((prefix - target) % k + k) % k;
        if (firstOcc.count(need))
            best = max(best, i - firstOcc[need]);
        if (!firstOcc.count(prefix))
            firstOcc[prefix] = i;
    }
    return best;
}

// ============================================================================
// Remainder Frequency Window — Count elements with arr[i] % K == j
// ============================================================================
/*
 * Maintain freq[0..K-1] for current window.
 * Add element: freq[arr[i] % K]++
 * Remove element: freq[arr[i] % K]--
 * Query: freq[target_remainder]
 *
 * Useful for: "window with at least M elements divisible by K" etc.
 */

int main() {
    // Subarrays divisible by K
    vector<int> a1 = {4, 5, 0, -2, -3, 1};
    cout << "Subarrays div by 5: " << subarraysDivByK(a1, 5) << "\n"; // 7

    // Continuous subarray sum (multiple of K, len ≥ 2)
    vector<int> a2 = {23, 2, 4, 6, 7};
    cout << "Has subarray sum %6==0: " << checkSubarraySum(a2, 6) << "\n"; // 1

    // Min subarray to remove for divisibility
    vector<int> a3 = {3, 1, 4, 2};
    cout << "Min remove for %6: " << minSubarray(a3, 6) << "\n"; // 1

    // Pair divisible by K
    vector<int> a4 = {1, 2, 3, 4, 5, 10, 6, 7, 8, 9};
    cout << "Can pair %5: " << canArrange(a4, 5) << "\n"; // 1

    // Longest subarray sum % 3 == 1
    vector<int> a5 = {1, 2, 3, 4, 5};
    cout << "Longest sum%3==1: " << longestSubarraySumModK(a5, 3, 1) << "\n"; // 4

    return 0;
}

