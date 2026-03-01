/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Greedy + Math / Number Theory
 *  Level   : Grandmaster
 * ============================================================================
 *
 *  ▶ GREEDY + GCD/LCM:
 *  ────────────────────
 *  - GCD properties: gcd(a,b) divides a-b. Greedy: reduce using GCD.
 *  - LCM constraints: greedy assignment respecting LCM bounds.
 *
 *  ▶ GREEDY + MODULAR ARITHMETIC:
 *  ──────────────────────────────
 *  - Remainders: group elements by remainder, assign greedily.
 *  - Sum divisibility: prefix sums mod K.
 *
 *  ▶ GREEDY + PRIME FACTORIZATION:
 *  ───────────────────────────────
 *  - Divide greedily by smallest prime factor.
 *  - Factor-based grouping.
 *
 *  ▶ GREEDY + BINARY REPRESENTATION:
 *  ─────────────────────────────────
 *  - Process bits from MSB to LSB (or vice versa).
 *  - XOR greedy: maximize XOR by choosing bits greedily.
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

// ============================================================================
// EXAMPLE 1: Greedy XOR Maximization
// Given N numbers, choose a subset to maximize XOR
// Greedy: Use Gaussian elimination on bits (linear basis)
// ============================================================================
long long maxXorSubset(vector<long long>& nums) {
    vector<long long> basis;

    for (long long x : nums) {
        for (long long b : basis)
            x = min(x, x ^ b);
        if (x > 0)
            basis.push_back(x);
    }

    // Greedily build max XOR
    long long result = 0;
    for (long long b : basis)
        result = max(result, result ^ b);
    return result;
}

// ============================================================================
// EXAMPLE 2: Greedy GCD Operations
// Given array, in one operation: replace a[i] with gcd(a[i], a[j])
// Find minimum number of operations to make all elements equal
// ============================================================================
/*
 * Key insight: Final value must be gcd of entire array.
 * If gcd(all) == min(all), no operations needed.
 * Otherwise, we need to propagate gcd through the array.
 *
 * This is a simplified version — many CF problems involve
 * greedy GCD propagation where you process pairs optimally.
 */

// ============================================================================
// EXAMPLE 3: Greedy Sum Partition by Divisibility
// Partition array into maximum groups where each group sum is divisible by K
// ============================================================================
int maxDivisibleGroups(vector<int>& nums, int k) {
    // Prefix sum approach: if prefix[i] ≡ prefix[j] (mod k), then sum(i..j) divisible by k
    // Greedy: cut at every point where prefix sum mod k = 0
    int groups = 0;
    long long prefixMod = 0;

    for (int x : nums) {
        prefixMod = ((prefixMod + x) % k + k) % k;
        if (prefixMod == 0) {
            groups++;
        }
    }
    return groups;
}

// ============================================================================
// EXAMPLE 4: Minimum operations to make GCD = 1
// In each operation, replace any element with gcd of two elements
// If gcd(all) != 1, impossible. Otherwise, find min operations.
// ============================================================================
int minOpsToGCDOne(vector<int>& a) {
    int n = a.size();
    int g = 0;
    for (int x : a) g = __gcd(g, x);
    if (g != 1) return -1;

    // Check if any element is already 1
    int ones = count(a.begin(), a.end(), 1);
    if (ones > 0) return n - ones;

    // Find shortest subarray with gcd = 1
    int minLen = n;
    for (int i = 0; i < n; i++) {
        int g = 0;
        for (int j = i; j < n; j++) {
            g = __gcd(g, a[j]);
            if (g == 1) {
                minLen = min(minLen, j - i);
                break;
            }
        }
    }
    // Need minLen operations to create a 1, then (n-1) to propagate
    return minLen + (n - 1);
}

int main() {
    // XOR Maximization
    vector<long long> nums = {3, 5, 7, 2};
    cout << "Max XOR subset: " << maxXorSubset(nums) << endl;

    // Divisible Groups
    vector<int> arr = {3, 6, 1, 2, 5, 1};
    cout << "Max groups div by 3: " << maxDivisibleGroups(arr, 3) << endl;

    // Min ops to GCD 1
    vector<int> arr2 = {2, 4, 3, 6};
    cout << "Min ops to GCD=1: " << minOpsToGCDOne(arr2) << endl;

    return 0;
}

