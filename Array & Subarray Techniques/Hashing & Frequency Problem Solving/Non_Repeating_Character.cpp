/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-18 00:06:26
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

/* Problem: Given a string s consisting of lowercase English Letters.
 * return the first non-repeating character in s. If there is no non-repeating character, return '$'.
 * Example 1:
 * Input: s = "leetcode"
 * Output: 'l'
 * Explanation: 'l' is the first non-repeating character in "leetcode".
 * Example 2:
 * Input: s = "loveleetcode"
 * Output: 'v'
 * Explanation: 'v' is the first non-repeating character in "loveleetcode".
 */

// Approach: Use a frequency array of size 26 to count occurrences of each character.
// Then iterate through the string again to find the first character with frequency 1.
// Time Complexity: O(n), Space Complexity: O(1) since the frequency array is of fixed size 26.
char isNonRepeating(const string& s, char c) {
    // Use C++ STL in one line simple return
    // return count(all(s), c) == 1;

    // Manual counting method (more efficient than count for large strings)
    // Step 1: Create frequency array
    array<int, 26> freq = {0};

    // Step 2: Count frequencies
    for (char ch : s){
        freq[ch - 'a']++;
    }

    // Step 3: Check if character c is non-repeating
    for (char ch : s){
        if (freq[ch - 'a'] == 1)
            return ch; // Return the first non-repeating character
    }

    return '$'; // If no non-repeating character found
}

void solve() {
    
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

