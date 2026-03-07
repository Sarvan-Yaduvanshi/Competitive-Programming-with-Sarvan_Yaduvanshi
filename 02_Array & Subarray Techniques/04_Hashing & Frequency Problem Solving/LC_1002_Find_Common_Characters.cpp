/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-07 22:10:50
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

/* Problem: LeetCode 1002 - Find Common Characters
 * Difficulty: Easy
 * Given an array of strings A, return a list of all characters that show up in all strings within the list (including duplicates).
 * For example, if a character occurs 3 times in all strings but not 4 times, you need to include that character three times in the final answer.
 * You may return the answer in any order.
 *
 * Example 1:
 * Input: ["bella","label","roller"]
 * Output: ["e","l","l"]
 *
 * Example 2:
 * Input: ["cool","lock","cook"]
 * Output: ["c","o"]
 *
 * Constraints:
 * 1 <= A.length <= 100
 * 1 <= A[i].length <= 100
 * A[i][j] is a lowercase letter
 */

/* Approach:
 * 1. Count frequency of each character in the first string.
 * 2. For each subsequent string, update the frequency counts to be the minimum of the current counts and the counts in that string.
 * 3. Finally, construct the result based on the minimum frequency counts.
 * Time Complexity: O(N * M) where N is the number of strings and M is the length of the longest string.
 * Space Complexity: O(1) since we only need a fixed size array for character counts (26 lowercase letters).
 */
vec<string> commonChars(vec<string>& words) {
    // Key optimization: Use a fixed-size array for character counts (26 lowercase letters)
    // Global frequency array initialized to 0
    array<int, 26> freq{};
    freq.fill(INT_MAX); // Start with max to find minimum

    for (string& w : words){
        // Local frequency array for the current word
        array<int, 26> local_freq = {0};
        for (char c : w)
            local_freq[c - 'a']++;

        // Update global frequency to be the minimum of itself and local frequency
        for (int i = 0; i < 26; i++)
            freq[i] = min(freq[i], local_freq[i]);
    }

    // Construct the result based on the minimum frequency counts
    vec<string> result;
    for (int i = 0; i < 26; i++){
        while (freq[i]--){
            result.pb(string(1, 'a' + i)); // Add the character freq[i] times
        }
    }

    return result;
}

void solve() {
    int n; cin >> n;
    vec<string> words(n);
    read(words);

    vec<string> res = commonChars(words);
    cout << "[";
    for (int i = 0; i < sz(res); i++){
        cout << res[i] << (i < sz(res) - 1 ? ", " : "");
    }
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

