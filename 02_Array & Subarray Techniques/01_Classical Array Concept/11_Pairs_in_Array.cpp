/*
Author: Sarvan.DP.GrandMaster
Created : 2026-01-05 19:36:37
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
#include <unordered_set>

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

// Method 1: Cartesian Product (All Ordered Pairs)
// Logic: A x A. Includes (i, i) and distinguishes (i, j) from (j, i).
// Complexity: O(N^2)
void printCartesian(const vec<int>& arr) {
    int n = sz(arr);

    // GM Safety: Don't print if N is huge (saves your terminal)
    if (n > 1000) {
        cout << "Skipping print (Size too large). Total: " << 1LL * n * n << nl;
        return;
    }

    cout << "--- Cartesian Product ---" << nl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "(" << arr[i] << "," << arr[j] << ") ";
        }
        cout << nl;
    }
    cout << "Total Pairs: " << 1LL * n * n << nl << nl;
}

// Method 2: Distinct Pairs / Combinations (Strictly Upper Triangular)
// Logic: Order doesn't matter ( (1,2) is same as (2,1) ), no (i, i).
// Complexity: O(N^2) but constant factor 1/2
void printCombinations(const vec<int>& arr) {
    int n = sz(arr);

    // GM Safety
    if (n > 2000) {
        cout << "Skipping print. Total: " << 1LL * n * (n - 1) / 2 << nl;
        return;
    }

    cout << "--- Combinations (i < j) ---" << nl;
    for (int i = 0; i < n; i++) {
        // Optimization: Start j from i + 1 immediately
        for (int j = i + 1; j < n; j++) {
            cout << "(" << arr[i] << "," << arr[j] << ") ";
        }
        // Only print newline if we actually printed pairs for this row
        if (i < n - 1) cout << nl;
    }
    cout << "Total Pairs: " << 1LL * n * (n - 1) / 2 << nl;
}

// Method 3: Permutations (Ordered Distinct Pairs)
// Use Case: When order matters but same elements not allowed.
// Formula: Total pairs = n(n-1)
// Permutations: All ordered pairs where i ≠ j
// Distinguishes (i,j) from (j,i), excludes (i,i)
void printPermutations(const vec<int>& arr) {
    int n = sz(arr);

    if (n > 1500) {
        cout << "Skipping print. Total: "
             << 1LL * n * (n - 1) << nl;
        return;
    }

    cout << "--- Permutations (i ≠ j) ---" << nl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                cout << "(" << arr[i] << "," << arr[j] << ") ";
            }
        }
        cout << nl;
    }
    cout << "Total Pairs: " << 1LL * n * (n - 1) << nl;
}

// Method 4: Count Pairs with Given Sum
// Problem: Find number of pairs where arr[i] + arr[j] = targetSum.
// Approach 1 : Using HashMap Time Complexity --> O(N)  Space Complexity --> O(N)
int countPairsWithSum(const vec<int>& arr,int n, int targetSum){
    // Map stores: <Number, How many times we've seen it so far>
    unordered_map<int, int> freq;
    int count = 0;

    for (int i = 0; i < n; i++) {
        // 1. Calculate what number we need to find to make the sum
        int complement = targetSum - arr[i];

        // 2. Look "Backwards": Did we see the complement earlier?
        if (freq.find(complement) != freq.end()) {
            // If yes, this current number (arr[i]) makes a pair
            // with EVERY instance of the complement we've seen.
            count += freq[complement];
        }

        // 3. Store "History": Add the current number to the map
        // so future numbers can pair with it.
        freq[arr[i]]++;
    }

    return count;
}

// Using Two Pointers (Sorted Array) - O(n log n)
int countPairsWithSumSorted(const vec<int>& arr, int n, int targetSum){
    int left = 0;
    int right = n - 1;
    int count = 0;

    while (left < right){
        int currSum = arr[left] + arr[right];

        if (currSum == targetSum){
            int leftCount = 1, rightCount = 1;

            // 1. Count how many times the number at 'left' repeats
            while (left + 1 < right && arr[left] == arr[left + 1]){
                leftCount++;
                left++;
            }

            // 2. Count how many times the number at 'right' repeats
            while (right - 1 > left && arr[right] == arr[right - 1]){
                rightCount++;
                right++;
            }

            // 3. CHECK: Are the left numbers and right numbers actually the SAME number?
            // Example: [3, 3, 3, 3] with target 6
            if (arr[left] == arr[right]){
                // Special Formula for combinations: n*(n+1)/2
                // (Note: here leftCount is essentially n-1)
                count += (leftCount * (leftCount - 1)) / 2;
            }
            // 4. NORMAL CASE: Different numbers
            // Example: [2, 2] and [4, 4, 4] with target 6
            else{
                count += (leftCount * rightCount); // 2 * 3 = 6 pairs
            }

            // Move pointers inward to escape the processed duplicates
            left++;
            right--;
        }
    }

    return count;
}

// =============================================================================
//  ADVANCED PAIR CONCEPTS (GM Level)
// =============================================================================

// -------------------------------------------------------------
// Method 5: Count Pairs with Given DIFFERENCE (|arr[i] - arr[j]| = K)
// -------------------------------------------------------------
// Approach 1: HashMap — O(N) Time, O(N) Space
// For each element, check if (element + K) or (element - K) exists.
// GM Tip: Be careful with K=0 (count duplicates using nC2).

int countPairsWithDiff(const vec<int>& arr, int k) {
    int n = sz(arr);
    unordered_map<int, int> freq;
    for (int x : arr) freq[x]++;

    int count = 0;
    if (k == 0) {
        // K=0 means same elements. Count nC2 for each group.
        for (auto& [val, cnt] : freq) {
            count += cnt * (cnt - 1) / 2;
        }
    } else {
        // For each unique value, check if (val + k) exists
        for (auto& [val, cnt] : freq) {
            if (freq.count(val + k)) {
                count += cnt * freq[val + k];
            }
        }
    }
    return count;
}

// Approach 2: Sorted + Two Pointer — O(N log N) Time, O(1) Space
// Works on sorted array. Move left/right based on current difference.
int countPairsWithDiff_sorted(vec<int> arr, int k) {
    sort(all(arr));
    int n = sz(arr);
    int i = 0, j = 1;
    int count = 0;

    while (j < n) {
        int diff = arr[j] - arr[i];

        if (diff == k) {
            count++;
            i++;
            j++;
            // Skip duplicates for distinct pairs
            while (j < n && arr[j] == arr[j - 1]) j++;
            while (i < j && arr[i] == arr[i - 1]) i++;
        }
        else if (diff < k) {
            j++;
        }
        else {
            i++;
            if (i == j) j++; // Ensure i < j always
        }
    }
    return count;
}

// -------------------------------------------------------------
// Method 6: Find Pair Closest to Given Sum
// -------------------------------------------------------------
// Given sorted array, find pair whose sum is closest to target.
// Two Pointer approach. O(N log N) if unsorted, O(N) if sorted.
// LC 2sum variant

pii closestPairSum(vec<int> arr, int target) {
    sort(all(arr));
    int n = sz(arr);
    int lo = 0, hi = n - 1;
    int bestDiff = INT_MAX;
    pii bestPair = {0, 0};

    while (lo < hi) {
        int currSum = arr[lo] + arr[hi];
        int diff = abs(currSum - target);

        if (diff < bestDiff) {
            bestDiff = diff;
            bestPair = {arr[lo], arr[hi]};
        }

        if (currSum < target) lo++;
        else if (currSum > target) hi--;
        else break; // Exact match
    }
    return bestPair;
}

// -------------------------------------------------------------
// Method 7: Maximum / Minimum Pair Sum
// -------------------------------------------------------------
// MAX pair sum: Just find two largest → O(N)
// MIN pair sum: Just find two smallest → O(N)
// LC 1877: Minimize Maximum Pair Sum in Array
//          Sort, pair smallest with largest → O(N log N)

i64 maxPairSum(const vec<int>& arr) {
    // Find two largest elements
    i64 first = -INF64, second = -INF64;
    for (int x : arr) {
        if (x > first) { second = first; first = x; }
        else if (x > second) second = x;
    }
    return first + second;
}

i64 minPairSum(const vec<int>& arr) {
    // Find two smallest elements
    i64 first = INF64, second = INF64;
    for (int x : arr) {
        if (x < first) { second = first; first = x; }
        else if (x < second) second = x;
    }
    return first + second;
}

// LC 1877: Minimize the Maximum Pair Sum
// Sort array, pair arr[0] with arr[n-1], arr[1] with arr[n-2], etc.
// The answer is the maximum of all such pair sums.
// Greedy Proof: Pairing smallest with largest minimizes the worst case.
int minMaxPairSum(vec<int> arr) {
    sort(all(arr));
    int n = sz(arr);
    int result = 0;
    for (int i = 0; i < n / 2; i++) {
        result = max(result, arr[i] + arr[n - 1 - i]);
    }
    return result;
}

// -------------------------------------------------------------
// Method 8: Pair with Maximum Product
// -------------------------------------------------------------
// Two cases: (largest × second largest) OR (smallest × second smallest)
// Because two negatives multiply to positive!
// Time: O(N)

i64 maxProductPair(const vec<int>& arr) {
    int n = sz(arr);
    if (n < 2) return 0;

    // Find max1, max2 (two largest) and min1, min2 (two smallest)
    i64 max1 = -INF64, max2 = -INF64;
    i64 min1 = INF64, min2 = INF64;

    for (int x : arr) {
        if (x > max1) { max2 = max1; max1 = x; }
        else if (x > max2) max2 = x;

        if (x < min1) { min2 = min1; min1 = x; }
        else if (x < min2) min2 = x;
    }

    return max(max1 * max2, min1 * min2);
}

// Pair with Minimum Product (trickier — could involve one pos, one neg)
i64 minProductPair(const vec<int>& arr) {
    int n = sz(arr);
    if (n < 2) return 0;

    i64 max1 = -INF64, min1 = INF64;
    i64 max2 = -INF64, min2 = INF64;

    for (int x : arr) {
        if (x > max1) { max2 = max1; max1 = x; }
        else if (x > max2) max2 = x;
        if (x < min1) { min2 = min1; min1 = x; }
        else if (x < min2) min2 = x;
    }

    // Min product can be: two smallest positives, OR largest × smallest (cross sign)
    return min({max1 * max2, min1 * min2, max1 * min1});
}

// -------------------------------------------------------------
// Method 9: Count Pairs with XOR Equal to K
// -------------------------------------------------------------
// Property: If a ^ b = K, then b = a ^ K
// So for each element, check if (element ^ K) was seen before.
// Time: O(N), Space: O(N)

int countPairsWithXOR(const vec<int>& arr, int k) {
    unordered_map<int, int> freq;
    int count = 0;

    for (int x : arr) {
        int complement = x ^ k;
        if (freq.count(complement)) {
            count += freq[complement];
        }
        freq[x]++;
    }
    return count;
}

// -------------------------------------------------------------
// Method 10: TWO SUM — Return Indices (LC 1)
// -------------------------------------------------------------
// The most famous pair problem. Return indices of two numbers that sum to target.
// HashMap approach: O(N) Time, O(N) Space

pii twoSum(const vec<int>& arr, int target) {
    unordered_map<int, int> seen; // value → index

    for (int i = 0; i < sz(arr); i++) {
        int complement = target - arr[i];
        if (seen.count(complement)) {
            return {seen[complement], i};
        }
        seen[arr[i]] = i;
    }
    return {-1, -1}; // Not found
}

// -------------------------------------------------------------
// Method 11: THREE SUM (LC 15)
// -------------------------------------------------------------
// Find all unique triplets that sum to zero.
// Sort + Fix one + Two Pointer for remaining two.
// Time: O(N²), Space: O(1) extra

vvec<int> threeSum(vec<int> arr) {
    sort(all(arr));
    int n = sz(arr);
    vvec<int> result;

    for (int i = 0; i < n - 2; i++) {
        // Skip duplicate for first element
        if (i > 0 && arr[i] == arr[i - 1]) continue;

        int target = -arr[i];
        int lo = i + 1, hi = n - 1;

        while (lo < hi) {
            int sum = arr[lo] + arr[hi];

            if (sum == target) {
                result.push_back({arr[i], arr[lo], arr[hi]});

                // Skip duplicates
                while (lo < hi && arr[lo] == arr[lo + 1]) lo++;
                while (lo < hi && arr[hi] == arr[hi - 1]) hi--;
                lo++;
                hi--;
            }
            else if (sum < target) lo++;
            else hi--;
        }
    }
    return result;
}

// GM Note on 3Sum complexity:
// Outer loop: O(N), Inner two-pointer: O(N) → Total: O(N²)
// Cannot do better than O(N²) for 3Sum (proven lower bound for comparison-based)

// -------------------------------------------------------------
// Method 12: FOUR SUM (LC 18)
// -------------------------------------------------------------
// Find all unique quadruplets that sum to target.
// Sort + Fix two + Two Pointer for remaining two.
// Time: O(N³), Space: O(1) extra

vvec<int> fourSum(vec<int> arr, int target) {
    sort(all(arr));
    int n = sz(arr);
    vvec<int> result;

    for (int i = 0; i < n - 3; i++) {
        if (i > 0 && arr[i] == arr[i - 1]) continue;

        for (int j = i + 1; j < n - 2; j++) {
            if (j > i + 1 && arr[j] == arr[j - 1]) continue;

            i64 remain = (i64)target - arr[i] - arr[j];
            int lo = j + 1, hi = n - 1;

            while (lo < hi) {
                i64 sum = (i64)arr[lo] + arr[hi];

                if (sum == remain) {
                    result.push_back({arr[i], arr[j], arr[lo], arr[hi]});
                    while (lo < hi && arr[lo] == arr[lo + 1]) lo++;
                    while (lo < hi && arr[hi] == arr[hi - 1]) hi--;
                    lo++;
                    hi--;
                }
                else if (sum < remain) lo++;
                else hi--;
            }
        }
    }
    return result;
}

// -------------------------------------------------------------
// Method 13: Count ALL Pairs Sum Divisible by K
// -------------------------------------------------------------
// For each element, compute arr[i] % K.
// Pair (i,j) has sum divisible by K if (arr[i]%K + arr[j]%K) % K == 0.
// Use remainder frequency array.
// Time: O(N + K), Space: O(K)

i64 countPairsDivisibleByK(const vec<int>& arr, int k) {
    vec<int> remFreq(k, 0);
    for (int x : arr) {
        remFreq[((x % k) + k) % k]++; // Handle negatives
    }

    i64 count = 0;

    // Remainder 0 pairs with remainder 0
    count += 1LL * remFreq[0] * (remFreq[0] - 1) / 2;

    // Remainder r pairs with remainder (k - r)
    for (int r = 1; r <= k / 2; r++) {
        if (r == k - r) {
            // Special case: r = k/2 (only when k is even)
            count += 1LL * remFreq[r] * (remFreq[r] - 1) / 2;
        } else {
            count += 1LL * remFreq[r] * remFreq[k - r];
        }
    }
    return count;
}

// -------------------------------------------------------------
// Method 14: Pair Sort — Sort by First, Then by Second
// -------------------------------------------------------------
// Critical for many CP problems: custom comparators on pairs.

void demo_pair_sorting() {
    cout << nl << "--- Pair Sorting Techniques ---" << nl;

    vec<pii> pairs = {{3,1}, {1,4}, {2,2}, {1,3}, {3,2}};

    // Default: Sort by first, then by second (ascending both)
    vec<pii> p1 = pairs;
    sort(all(p1));
    cout << "Default (asc,asc): ";
    for (auto [a,b] : p1) cout << "(" << a << "," << b << ") ";
    cout << nl;

    // Sort by first ascending, second descending
    vec<pii> p2 = pairs;
    sort(all(p2), [](const pii& a, const pii& b) {
        if (a.fi != b.fi) return a.fi < b.fi;
        return a.se > b.se; // Descending second
    });
    cout << "Sort (asc,desc):   ";
    for (auto [a,b] : p2) cout << "(" << a << "," << b << ") ";
    cout << nl;

    // Sort by second element only
    vec<pii> p3 = pairs;
    sort(all(p3), [](const pii& a, const pii& b) {
        return a.se < b.se;
    });
    cout << "Sort by second:    ";
    for (auto [a,b] : p3) cout << "(" << a << "," << b << ") ";
    cout << nl;

    // Sort by sum of pair
    vec<pii> p4 = pairs;
    sort(all(p4), [](const pii& a, const pii& b) {
        return (a.fi + a.se) < (b.fi + b.se);
    });
    cout << "Sort by sum:       ";
    for (auto [a,b] : p4) cout << "(" << a << "," << b << ") ";
    cout << nl;
}

// -------------------------------------------------------------
// Method 15: Count Inversions (Pair Concept)
// -------------------------------------------------------------
// An inversion is a pair (i, j) where i < j but arr[i] > arr[j].
// Brute Force: O(N²). Merge Sort: O(N log N) — see Module 10.
// Here: Brute force for understanding.

i64 countInversions_brute(const vec<int>& arr) {
    int n = sz(arr);
    i64 inversions = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) inversions++;
        }
    }
    return inversions;
}

// -------------------------------------------------------------
// PAIRS CHEAT SHEET
// -------------------------------------------------------------
/*
 * ┌──────────────────────────────────────┬────────────┬───────────┐
 * │ Pair Problem                         │ Time       │ Technique │
 * ├──────────────────────────────────────┼────────────┼───────────┤
 * │ All Ordered Pairs (Cartesian)        │ O(N²)      │ 2 loops   │
 * │ All Unordered Pairs (Combinations)   │ O(N²)      │ i<j loop  │
 * │ Count Pairs with Sum = K             │ O(N)       │ HashMap   │
 * │ Count Pairs with Diff = K            │ O(N)       │ HashMap   │
 * │ Closest Pair to Target Sum           │ O(N log N) │ 2-Pointer │
 * │ Max/Min Pair Sum                     │ O(N)       │ Track top2│
 * │ Max/Min Pair Product                 │ O(N)       │ Track ext │
 * │ Count Pairs with XOR = K             │ O(N)       │ HashMap   │
 * │ Two Sum (return indices)             │ O(N)       │ HashMap   │
 * │ Three Sum                            │ O(N²)      │ Sort+2Ptr │
 * │ Four Sum                             │ O(N³)      │ Sort+2Ptr │
 * │ Pairs Divisible by K                 │ O(N+K)     │ Remainder │
 * │ Count Inversions                     │ O(N log N) │ MergeSort │
 * │ Minimize Max Pair Sum (LC 1877)      │ O(N log N) │ Sort+Pair │
 * └──────────────────────────────────────┴────────────┴───────────┘
 *
 * KEY FORMULAS:
 *   Total ordered pairs:       N²
 *   Total unordered pairs:     N(N-1)/2
 *   Total permutation pairs:   N(N-1)
 *   Pairs with sum divisible:  Use remainder frequency array
 */

void solve() {
    int n; cin >> n;

    vec<int> arr(n); read(arr);

    // === BASIC PAIR TYPES ===
    printCartesian(arr);
    printCombinations(arr);
    printPermutations(arr);

    // === PAIR WITH SUM ===
    int target = 10;
    cout << nl << "--- Pairs with Sum = " << target << " ---" << nl;
    cout << "HashMap count: " << countPairsWithSum(arr, n, target) << nl;

    // === PAIR WITH DIFFERENCE ===
    int k = 2;
    cout << nl << "--- Pairs with Diff = " << k << " ---" << nl;
    cout << "HashMap count: " << countPairsWithDiff(arr, k) << nl;

    // === CLOSEST PAIR SUM ===
    auto [a, b] = closestPairSum(arr, target);
    cout << nl << "Closest pair to sum " << target << ": (" << a << "," << b << ")" << nl;

    // === MAX/MIN PAIR SUM & PRODUCT ===
    cout << nl << "Max pair sum: " << maxPairSum(arr) << nl;
    cout << "Min pair sum: " << minPairSum(arr) << nl;
    cout << "Max pair product: " << maxProductPair(arr) << nl;
    cout << "Min pair product: " << minProductPair(arr) << nl;

    // === XOR PAIR ===
    cout << nl << "Pairs with XOR = " << k << ": " << countPairsWithXOR(arr, k) << nl;

    // === TWO SUM ===
    auto [i1, i2] = twoSum(arr, target);
    cout << "Two Sum indices for " << target << ": [" << i1 << ", " << i2 << "]" << nl;

    // === THREE SUM ===
    cout << nl << "--- Three Sum (target 0) ---" << nl;
    vec<int> ts = {-1, 0, 1, 2, -1, -4};
    auto triplets = threeSum(ts);
    for (auto& t : triplets) {
        cout << "[" << t[0] << "," << t[1] << "," << t[2] << "] ";
    }
    cout << nl;

    // === DIVISIBILITY ===
    cout << nl << "Pairs with sum div by 3: " << countPairsDivisibleByK(arr, 3) << nl;

    // === INVERSIONS ===
    cout << "Inversions (brute): " << countInversions_brute(arr) << nl;

    // === PAIR SORTING ===
    demo_pair_sorting();
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    // Multi-test case support (commented out for this demo)
    // int TC = 1;
    // cin >> TC;
    // while (TC--) solve();

    solve();
    return 0;
}

