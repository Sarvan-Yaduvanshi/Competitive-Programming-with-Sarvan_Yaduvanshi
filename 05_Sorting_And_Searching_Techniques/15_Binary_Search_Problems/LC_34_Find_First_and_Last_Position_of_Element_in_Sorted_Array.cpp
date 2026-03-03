/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-03 20:43:06
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

/* Problem: LC 34. Find First and Last Position of Element in Sorted Array
   Difficulty: Medium
   Given a sorted array of integers, find the starting and ending position of a given target value.
   If the target is not found in the array, return [-1, -1].
   You must write an algorithm with O(log n) runtime complexity.

   Example 1:
   Input: nums = [5,7,7,8,8,10], target = 8
   Output: [3,4]

    Example 2:
    Input: nums = [5,7,7,8,8,10], target = 6
    Output: [-1,-1]

   Approach:
   - Use binary search to find the leftmost (first) occurrence of target.
   - Use binary search to find the rightmost (last) occurrence of target.
   - Return the indices as a pair.
*/

// Step 1: Find first occurrence (leftmost index)
int findFirstOccurrence(const vector<int>& nums, int target) {
    int lo = 0, hi = (int)nums.size() - 1;
    int first = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) {
            first = mid; // Potential first occurrence
            hi = mid - 1; // Search left half
        } else if (nums[mid] < target) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return first;
}

// Step 2: Find last occurrence (rightmost index)
int findLastOccurrence(const vector<int>& nums, int target) {
    int lo = 0, hi = (int)nums.size() - 1;
    int last = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) {
            last = mid; // Potential last occurrence
            lo = mid + 1; // Search right half
        } else if (nums[mid] < target) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return last;
}

vec<int> searchRange(const vector<int>& nums, int target) {
    int first = findFirstOccurrence(nums, target);
    int last = findLastOccurrence(nums, target);
    return {first, last};

    // Alternative using STL:
    // auto [lo_it, hi_it] = equal_range(nums.begin(), nums.end(), target);
    // if (lo_it == hi_it) return {-1, -1}; // Target not found
    // return {int(lo_it - nums.begin()), int(hi_it - nums.begin() - 1)};
}

void solve() {
    int n, target;
    cin >> n >> target;
    vector<int> nums(n);
    read(nums);

    vector<int> result = searchRange(nums, target);
    cout << "[" << result[0] << "," << result[1] << "]" << nl;
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

