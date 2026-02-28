/*
Author: Sarvan.DP.GrandMaster
Created : 2025-12-31 15:03:48
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

#define v1(v, n) vec<i64> v(n)
#define take(v) for(auto &x : v) cin >> x
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

// ==========================================
//          LINEAR SEARCH VARIATIONS
// ==========================================

/**
 * Method 1: Iterative Linear Search
 * Best for: General purpose, simple debugging.
 * Time: O(N) | Space: O(1)
 */
int linearSearch(const vector<int>& arr, int target) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

/**
 * Method 2: Sentinel Linear Search
 * Logic: Places 'target' at the end to eliminate the 'i < n' check in the loop.
 * Note: We pass 'arr' by Value (copy) here to avoid modifying the original
 * array in main(). In production, this copying makes it slower than Method 1.
 * Best for: Teaching optimization concepts, not for actual CP contests.
 */
int sentinelSearch(vector<int> arr, int target) {
    int n = arr.size();
    if (n == 0) return -1;

    int last = arr[n - 1]; // Backup last element
    arr[n - 1] = target;   // Place Sentinel

    int i = 0;
    while (arr[i] != target) i++; // Unchecked loop

    arr[n - 1] = last; // Restore array

    // If i < n-1, we found it naturally.
    // If arr[n-1] == target, the target was actually the last element.
    if (i < n - 1 || arr[n - 1] == target) return i;
    return -1;
}

/**
 * Method 4: Conditional Search (Predicate)
 * Logic: Finds the first element divisible by 'k'.
 * Concept: Demonstrates C++ Lambdas and Captures [k].
 */
int searchCondition(const vector<int>& arr, int k) {
    auto it = find_if(arr.begin(), arr.end(), [k](int num) {
        return num % k == 0; // The Condition
    });

    return (it != arr.end() ? distance(arr.begin(), it) : -1);
}

void solve() {
    int n;
    cout << "Enter array size: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter elements: ";
    for(int &x : arr) cin >> x;

    int target;
    cout << "Enter target value: ";
    cin >> target;

    // --- Execution & Output ---

    // 1. Basic Loop
    cout << "Method 1 (Basic): " << linearSearch(arr, target) << "\n";

    // 2. Sentinel (Pass by value happens here)
    cout << "Method 2 (Sentinel): " << sentinelSearch(arr, target) << "\n";

    // 3. STL Find (The "Pro" Way)
    // Most preferred in actual contests for unsorted arrays.
    auto it = find(arr.begin(), arr.end(), target);
    int idx_stl = (it != arr.end() ? (it - arr.begin()) : -1);
    cout << "Method 3 (STL): " << idx_stl << "\n";

    // 4. Conditional (e.g., first multiple of target)
    // Note: If target is 0, modulo will crash, so we handle that edge case.
    if (target != 0) {
        cout << "Method 4 (Divisible by " << target << "): "
             << searchCondition(arr, target) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << fixed << setprecision(10);

    // int TC = 1;
    // cin >> TC;
    // while (TC--) solve();
    
    solve();
    return 0;
}

