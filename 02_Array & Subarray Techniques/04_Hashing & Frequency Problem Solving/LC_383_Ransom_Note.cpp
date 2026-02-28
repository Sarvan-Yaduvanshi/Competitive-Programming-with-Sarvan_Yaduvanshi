/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-17 23:59:16
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

/* Problem: Leetcode-383-Ransom Note
   Given two strings ransomNote and magazine, return true if ransomNote can be constructed by using the letters from magazine and false otherwise.
   Each letter in magazine can only be used once in ransomNote.

   Example 1:
   Input: ransomNote = "a", magazine = "b"
   Output: false

   Example 2:
   Input: ransomNote = "aa", magazine = "ab"
   Output: false

   Example 3:
   Input: ransomNote = "aa", magazine = "aab"
   Output: true

   Constraints:
   - 1 <= ransomNote.length, magazine.length <= 10^5
   - ransomNote and magazine consist of lowercase English letters.
*/

// Approach: Frequency Count using Array (since only lowercase letters are involved)
// Time: O(n + m), Space: O(1) since we only use a fixed size array of 26
bool canConstruct(const string& ransomNote, const string& magazine) {
    array<int, 26> freq = {0};

    // Count frequencies in magazine
    for (char c : magazine) {
        freq[c - 'a']++;
    }

    // Check if ransomNote can be constructed
    for (char c : ransomNote) {
        if (freq[c - 'a'] == 0) {
            return false; // Not enough characters in magazine
        }
        freq[c - 'a']--; // Use one character
    }

    return true; // All characters in ransomNote are available in magazine
}

void solve() {
    string ransomNote, magazine;
    cin >> ransomNote >> magazine;

    cout << (canConstruct(ransomNote, magazine) ? "true" : "false") << nl;
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

