/*
Author: Sarvan.DP.GrandMaster
Created : 2026-01-10 00:30:49
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

/**
 * Algorithms 1 : Counting Sort
 * Logic: Count frequencies of each element and reconstruct the array.
 * * Time Complexity: O(N + Range)
 * - Very fast if Range is small.
 * * Space Complexity: O(Range)
 * - Dangerous if Range is huge (e.g. 10^9). Memory Limit Exceeded (MLE).
 * * Constraints: usually val <= 10^6.
 * - Can handle negatives only if you shift indices (offset).
 */
void countingSort(vec<int>& arr) {
    int n = sz(arr);
    if (n == 0) return;

    // 1. Find the Maximum element to determine range
    int max_val = arr[0];
    for (int x : arr) {
        max_val = max(max_val, x);
    }

    // 2. Create Frequency Array (initialized to 0)
    // Size is max_val + 1 because indices go from 0 to max_val
    vector<int> count(max_val + 1, 0);

    // 3. Count frequencies
    for (int x : arr) {
        count[x]++;
    }

    // 4. Overwrite the original array using the counts
    int index = 0;
    for (int i = 0; i <= max_val; i++) {
        while (count[i] > 0) {
            arr[index] = i;
            index++;
            count[i]--;
        }
    }
}

/**
 * Algorithms 2 : Radix Sort
 * Logic: Sorts numbers digit by digit starting from LSD (Least Significant Digit).
 * * Time Complexity: O(d * (N + b))
 * - d: Number of digits (max element length)
 * - N: Number of elements
 * - b: Base (10 in this case)
 * * Space Complexity: O(N + b)
 */
// A stable Counting Sort for a specific digit represented by exp (1, 10, 100...)
void countSort(vec<int>& arr, int exp) {
    int n = sz(arr);
    vec<int> output(n); // Output array
    int count[10] = {0};   // Frequency array for digits 0-9

    // 1. Store count of occurrences in count[]
    // (arr[i] / exp) % 10 gives the digit at current place value
    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    // 2. Change count[i] so that it contains actual position of this digit in output[]
    // This is the "Prefix Sum" step
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // 3. Build the output array
    // CRITICAL: We iterate REVERSE (n-1 to 0) to maintain STABILITY.
    // This ensures elements with same digit keep their relative order from previous pass.
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // 4. Copy the output array to arr, so that arr now contains sorted numbers according to current digit
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void radixSort(vec<int>& arr) {
    if (sz(arr) == 0) return;

    // Find the maximum number to know number of digits
    int maxVal = arr[0];
    for (int x : arr) maxVal = max(maxVal, x);

    // Do counting sort for every digit.
    // exp is 10^i where i is current digit number
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countSort(arr, exp);
    }
}

/**
 * Algorithms 3 : Bucket Sort
 * Usage: Best for uniformly distributed floats in range [0.0, 1.0).
 * * Time Complexity:
 * - Average: O(N + K) [N elements, K buckets] -> Effectively Linear O(N).
 * - Worst Case: O(N^2) [If all elements fall into ONE bucket].
 * * Space Complexity: O(N + K)
 */

void bucketSort(vec<float>& arr) {
    int n = sz(arr);
    if (n <= 0) return;

    // 1. Create N empty buckets
    // We use a vector of vectors
    vec<vec<float>> buckets(n);

    // 2. Scatter: Put array elements in different buckets
    for (int i = 0; i < n; i++) {
        // Calculate index: n * arr[i]
        // Example: 0.72 * 10 = 7.2 -> Index 7
        int idx = n * arr[i];

        // Safety Check: If value is exactly 1.0, it might give index 'n'.
        // Clamp it to the last bucket.
        if (idx >= n) idx = n - 1;

        buckets[idx].pb(arr[i]);
    }

    // 3. Sort individual buckets
    for (int i = 0; i < n; i++) {
        // Standard sort is fine here because bucket sizes are tiny (Avg size = 1)
        sort(buckets[i].begin(), buckets[i].end());
    }

    // 4. Gather: Concatenate all buckets into arr
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (float val : buckets[i]) {
            arr[index++] = val;
        }
    }
}

void solve() {
    int n; cin >> n;
    vec<float> arr(n);
    for(float &x : arr) cin >> x;

    bucketSort(arr);

    // Print
    for (int i = 0; i < n; i++) cout << arr[i] << (i == n - 1 ? "" : " ");
    cout << "\n";
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

