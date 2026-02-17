/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-17 18:19:33
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

/* Problem: Valid Anagram (LeetCode 242)
 * Given two strings s and t, return true if t is an anagram of s, and false otherwise.
 * Two strings are anagrams if:
 * They contain the same characters.
 * The frequency of each character is the same.
 * order of characters can be different.
 *
 * Example 1:
 * Input: s = "anagram", t = "nagaram"   Output: true
 * Example 2:
 * Input: s = "rat", t = "car"  Output: false

Constraints:
- 1 <= s.length, t.length <= 5 * 10^4
- s and t consist of lowercase English letters.
*/

// Approach 1: Sort both strings and compare
// Time Complexity: O(n log n) due to sorting
// Space Complexity: O(1) if we sort in place, O(n) if we create new sorted strings
bool areAnagrams(string& s1, string& s2) {
    // Quick check: If lengths differ, they can't be anagrams
    if (s1.length() != s2.length()) return false;

    // Step 1: Sort
    sort(all(s1));
    sort(all(s2));

    return s1 == s2;
}

// Approach 2: Frequency counting using array (since only lowercase letters)
// Time Complexity: O(n) where n is the length of the strings
// Space Complexity: O(1) since we use a fixed-size array of 26
bool areAnagramsFreq(string& s1, string& s2){
    // Quick check: If lengths differ, they can't be anagrams
    if (s1.length() != s2.length()) return false;

    // Step 1: Create frequency array
    array<int, 26> freq = {0};

    // Step 2: Count frequencies from s1 and subtract frequencies from s2
    for (int i = 0; i < sz(s1); i++){
        freq[s1[i] - 'a']++;
        freq[s2[i] - 'a']--;
    }

    // Step 3: If all frequencies are 0, strings are anagrams
    for (int i = 0; i < 26; i++){
        if (freq[i] != 0) return false;
    }
    return true;
}

/* Follow-up: What if the inputs contain Unicode characters?
 * How would you adapt your solution to such a case?
 * Answer:- If inputs contain Unicode characters, I would replace the fixed-size frequency array with an unordered_map to dynamically count character frequencies, since Unicode is not limited to 26 letters.
 */
bool areAnagramsUnicode(string& s1, string& s2) {
    if (s1.length() != s2.length()) return false;

    unordered_map<char, int> freq;

    for (int i = 0; i < sz(s1); i++) {
        freq[s1[i]]++;
        freq[s2[i]]--;
    }

    for (auto& [key, count] : freq) {
        if (count != 0) return false;
    }
    return true;
}

void solve() {
    string s1, s2;
    cin >> s1 >> s2;

    cout << (areAnagrams(s1, s2) ? "YES" : "NO") << nl;
    cout << (areAnagramsFreq(s1, s2) ? "YES" : "NO") << nl;
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

