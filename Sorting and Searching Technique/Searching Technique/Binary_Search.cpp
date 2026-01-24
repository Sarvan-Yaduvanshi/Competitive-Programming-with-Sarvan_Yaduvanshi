/*
Author: Sarvan.DP.GrandMaster
Created : 2026-01-11 17:01:33
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

/*
 * Algorithm 1: Binary Search (Beginner Level Implementation)
 * Time Complexity -> O(logN)
 * Space Complexity -> 0(1)
 */
int binarySearch(const vec<int>& arr, const int k){
    int lo = 0;
    int hi = sz(arr) - 1;

    while (lo <= hi){
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == k) return mid; // target found immediately return mid
        else if (arr[mid] > k) hi = mid - 1;
        else lo = mid + 1;
    }

    // if target not found
    return -1;
}

/*
 * Algorithm 2: Binary Search (Recursive Engine)
 * --------------------------------------------
 * Time Complexity  : O(log N)
 * Space Complexity : O(log N) [Due to Stack Depth]
 * * Note: While iterative is O(1) space, this recursive version
 * is cleaner for understanding Divide & Conquer.
 */
int binarySearchEngine(const vec<int>& arr, int lo, int hi, int k){
    // Base Case: Search space is exhausted
    if (lo > hi) return -1;

    // GM Optimization: Prevents (low + high) overflow for large arrays
    int mid = lo + (hi - lo) / 2;

    if (arr[mid] == k) return mid; // Target found
    else if (arr[mid] < k)
        // Target is in the right half
        return binarySearchEngine(arr, mid + 1, hi, k);
    else
        // Target is in the left half
        return binarySearchEngine(arr, lo, mid - 1, k);
}
/*
 * Wrapper Function
 * ----------------
 * Provides a clean interface so the caller doesn't need
 * to worry about indices (0, n-1).
 */
int recursiveBinarySearch(const vec<int>& arr, int k) {
    if (arr.empty()) return -1; // Edge case safety
    return binarySearchEngine(arr, 0, arr.size() - 1, k);
}

/*
 * Algorithm 3: Binary Search (First Occurrence / Lower Bound style)
 * -----------------------------------------------------------------
 * Purpose: Finds the FIRST index where arr[i] == k.
 * Time Complexity  : O(log N)
 * Space Complexity : O(1)
 */
int binarySearchGMLevel(const vec<int>& arr, int k) {
    int lo = 0;
    int hi = sz(arr) - 1;
    int ans = -1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        if (arr[mid] == k) {
            ans = mid;     // Candidate found
            hi = mid - 1;  // Try to find a better (earlier) index on the left
        }
        else if (arr[mid] < k) {
            lo = mid + 1;  // Target is to the right
        }
        else {
            hi = mid - 1;  // Target is to the left
        }
    }
    return ans;
}

/*
 * Algorithm: Binary Search (Rightmost / Last Occurrence Variant)
 * --------------------------------------------------------------
 * Purpose: Finds the LAST index 'i' such that arr[i] == target.
 * Logic  : Uses a "Right-Biased" search. We try to push 'L' as far right as possible
 * while maintaining the condition (arr[L] <= target).
 *
 * Time Complexity  : O(log N)
 * Space Complexity : O(1)
 */
int binarySearch2(const vec<int>& arr, int target) {
    int L = 0;
    int R = sz(arr) - 1;

    // Invariant: The answer lies within the range [L, R]
    // Loop terminates when L == R (Search space reduced to 1 element)
    while (L < R) {

        // GM NOTE: Ceiling Division (L + R + 1) / 2
        // We MUST round up because we use 'L = mid' below.
        // If we rounded down (standard division) and L = R-1, mid would be L.
        // If the 'else' branch hits, L = mid (which is L), causing an Infinite Loop.
        int mid = (L + R + 1) / 2;

        if (arr[mid] <= target) {
            // arr[mid] is a candidate (equal) or smaller.
            // Since we want the LAST occurrence, we don't discard mid.
            // We set L = mid to preserve this candidate and search the right half.
            L = mid;
        } else {
            // arr[mid] > target.
            // mid cannot be the answer. The answer must be to the left.
            R = mid - 1;
        }
    }

    // Post-processing:
    // The loop breaks when L == R. 'L' is now the "Rightmost element <= target".
    // We must check if this element is actually equal to the target.
    return (arr[L] == target ? L : -1);
}

/*
 * Algorithm 4: Binary Search (Half-Open Interval / STL Style)
 * -----------------------------------------------------------
 * Style    : [L, R)  -> L is inclusive, R is exclusive.
 * Purpose  : Finds the FIRST index 'i' such that arr[i] >= target.
 * (Equivalent to std::lower_bound)
 * * Returns  :
 * - The index of the first element >= target.
 * - If all elements < target, returns 'sz(arr)' (End of array).
 * * Time Complexity  : O(log N)
 * Space Complexity : O(1)
 */
int lowerBoundSTL(const vec<int>& arr, int target) {
    int L = 0;
    int R = sz(arr); // GM Note: R is size, NOT size-1. Range is [0, N)

    while (L < R) {
        int mid = L + (R - L) / 2;

        if (arr[mid] >= target) {
            // Target might be at 'mid' or to the left.
            // Since R is exclusive, we set R = mid (not mid - 1).
            // range becomes [L, mid)
            R = mid;
        } else {
            // arr[mid] < target. The answer must be strictly to the right.
            // range becomes [mid + 1, R)
            L = mid + 1;
        }
    }

    // L and R have converged. L is the answer.
    // If you need strictly "Equal" check:
    // if (L < sz(arr) && arr[L] == target) return L; else return -1;
    return L;
}

void solve() {
    int n; cin >> n;
    vec<int> arr(n); read(arr);

    int target; cin >> target;
    cout << binarySearch(arr, target) << nl;
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

