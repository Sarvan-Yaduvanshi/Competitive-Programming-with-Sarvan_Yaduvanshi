/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-14 16:57:06
*/

#include <unordered_set>
#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <numeric>
#include <random>
#include <chrono>

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
 * Problem: Given an array of integers and a target sum, determine if there are two numbers in the array that add up to the target sum.
 * Example: nums = [2, 7, 11, 15], target = 9
 * Output: true (because 2 + 7 = 9)
 *
 * Approach 1: Brute Force
 * Time Complexity -> O(N^2) | Space Complexity -> O(1)
 *
 * Approach 2: Using Hash map
 * Time Complexity -> O(N) | Space Complexity -> O(N)
 *
 * Approach 3: Sorting + Two Pointers
 * Time Complexity -> O(N logN) | Space Complexity -> O(1) (if we can sort in place)
 */

// Approach 1: Brute Force
// Time Complexity -> O(N^2) | Space Complexity -> O(1)
vector<int> twoSumBruteForce(vector<int>& nums, int target){
    int n = sz(nums);
    vec<int> ans;

    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            if (nums[i] + nums[j] == target) ans.pb(i);
        }
    }
    return ans;
}

// Approach 2: Using Hash map
// Time Complexity -> O(N) | Space Complexity -> O(N)
vector<int> twoSumUsingHashSet(vector<int>& nums, int target){
    int n = sz(nums);
    unordered_map<int, int> mp;

    for (int i = 0; i < n; i++){
        int need = target - nums[i];

        // Check if the needed value is already in the map
        if (mp.contains(need)){
            return {mp[need], i};
        }

        // Add the current number to the map
        mp[nums[i]] = i;
    }

    return {};
}

void solve() {
    int n; cin >> n;
    vec<int> arr(n); read(arr);
    int target; cin >> target;

    vector<int> ans = twoSumUsingHashSet(arr, target);
    cout << "[";
    for (auto x : ans) cout << x << ", ";
    cout << "]" << nl;
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

