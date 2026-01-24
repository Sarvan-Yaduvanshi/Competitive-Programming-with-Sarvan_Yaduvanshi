/*
Author: Sarvan.DP.GrandMaster
Created : 2026-01-08 17:13:02
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
// Tier 1: The Basics (O(N^2))
// Understand the logic, but never use these in a contest unless N <= 100.

/**
 * Algorithms 1 : Bubble Sort
 * Logic: Moves the largest element to the end in each pass.
 * Optimization: Stops early if no swaps occur in a pass (Array is already sorted).
 * * Time Complexity:
 * - Best Case: O(N) [Already sorted]
 * - Average/Worst: O(N^2) [Reverse sorted or random]
 * * Space Complexity: O(1) [In-place]
 * * Max Constraints: N <= 2000 (Because N^2 is slow. 10^4 might TLE)
 */
void bubbleSort(vec<int>& arr) {
    int n = sz(arr);

    for (int i = 0; i < n - 1; i++) {
        bool swapped = false; // Reset flag for every pass

        // Last i elements are already in place
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // GM Optimization: If no swaps occurred, array is fully sorted. Break.
        if (!swapped) break;
    }
}

/**
 * Algorithms 2 : Selection Sort
 * Logic: Finds the minimum element in the unsorted region and swaps it to the front.
 * * * Time Complexity:
 * - Best Case: O(N^2) [It scans everything regardless]
 * - Average/Worst: O(N^2)
 * * Space Complexity: O(1) [In-place]
 * * Max Constraints: N <= 2000 (Because N^2 is slow)
 */
void selectionSort(vec<int>& arr) {
    int n = sz(arr);

    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        // Find the smallest element in the remaining unsorted array
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // GM Optimization: Only swap if the minimum is not already in the correct spot
        // This saves a tiny bit of time on unnecessary operations.
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

/**
 * Algorithms 3 : Insertion Sort
 * Logic: Takes an element and shifts greater elements right to find the correct spot.
 * * Time Complexity:
 * - Best Case: O(N) [Already sorted] -> This makes it very special!
 * - Average/Worst: O(N^2)
 * * Space Complexity: O(1) [In-place]
 */

void insertionSort(vector<int>& arr) {
    int n = sz(arr);

    // Start from i = 1 because element at i = 0 is trivially "sorted"
    for (int i = 1; i < n; i++) {
        int curr = arr[i];
        int prev = i - 1;

        // Shift elements of arr[0..i-1] that are greater than curr
        // to one position ahead of their current position
        while (prev >= 0 && arr[prev] > curr) {
            arr[prev + 1] = arr[prev]; // Shift right
            prev--;
        }

        // Place curr at its correct position
        // We use (prev + 1) because prev was decremented one extra time in the loop
        arr[prev + 1] = curr;
    }
}

void solve() {
    int n;
    cin >> n;
    vec<int> arr(n); read(arr);

    bubbleSort(arr);
    // selectionSort(arr);
    // insertionSort(arr);


    for (int i = 0; i < n; i++) {
        cout << arr[i] << (i == n - 1 ? "" : " ");
    }
    cout << nl;
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

