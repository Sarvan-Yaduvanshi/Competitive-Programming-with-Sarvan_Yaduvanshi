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

        currMax = max(arr[i],currMax * arr[i]);
        currMin = min(arr[i], currMin * arr[i]);

        maxProduct = max(maxProduct, currMax);
    }

    cout << "Maximum Product Subarray : " << nl;
}

void solve() {
    int n;
    cin >> n;
    vec<int> arr(n);
    read(arr);

    // Uncomment for debugging small arrays
    // printAllSubarrays(arr);

    maxSubArraySumBruteForce(arr);
    maxSubArraySum(arr);
    maxSubarraySum_Prefix(arr);
    Kadanes_Algorithm(arr);
    Kadanes_AlgorithmMinSubarraySum(arr);

    SubarrayResult res = kadaneWithIndices(arr);
    // Print Result
    cout << "Maximum Sum: " << res.maxSum << nl;
    cout << "Start Index: " << res.strt << nl;
    cout << "End Index:   " << res.end << nl;

    // Optional: Print the actual subarray
    cout << "Subarray: [";
    for(int i = res.strt; i <= res.end; i++) {
        cout << arr[i] << (i < res.end ? ", " : "");
    }
    cout << "]" << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    // Standard CP Main Structure
    solve();

    return 0;
}
