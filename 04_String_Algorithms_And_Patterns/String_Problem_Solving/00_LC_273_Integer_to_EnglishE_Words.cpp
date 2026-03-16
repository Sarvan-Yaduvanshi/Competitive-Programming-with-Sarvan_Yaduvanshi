/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-13 19:32:02
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

/* Problem: LeetCode 273 - Integer to English Words
 * Description: Convert a non-negative integer to its English words representation.
 *
 * Example: Input: 123, Output: "One Hundred Twenty Three"
 * Example: Input: 12345, Output: "Twelve Thousand Three Hundred Forty Five"
 * Example: Input: 1234567, Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
 *
 * Constraints: 0 <= num <= 2^31 - 1
 */
class Solution{
private:
    const vec<string> belowTwenty = {
        "", "One", "Two", "Three", "Four", "Five",
        "Six", "Seven", "Eight", "Nine", "Ten",
        "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen",
        "Sixteen", "Seventeen", "Eighteen", "Nineteen"
    };

    const vec<string> tens  = {
        "", "", "Twenty", "Thirty", "Forty", "Fifty", ""
                         "Sixty", "Seventy", "Eighty", "Ninety"
    };

    const vec<string> thousands = {
        "", "Thousand", "Million", "Billion"
    };

    // Helper to process chunks of up to 3 digits (0 to 999)
    string helper(const int num){
        if (num == 0) return "";
        else if (num < 20) return belowTwenty[num] + " ";
        else if (num < 100) return tens[num / 10] + " " + helper(num % 10);
        else return belowTwenty[num / 100] + " Hundred " + helper(num % 100);
    }

public:
    string numberToWords(int num){
        // Handle the zero edge case immediately
        if (num == 0) return "Zero";

        string ans = "";
        int i = 0; // Index to track our suffix (thousands array)

        while (num > 0){
            // Only add to result if the chunk is not all zeroes (e.g., 1,000,000)
            if (num % 1000 != 0)
                // Process the 3-digit chunk, add the suffix, and prepend it to our result
                ans = helper(num % 1000) + thousands[i] + " " + ans;

            num /= 1000; // Move to the next chunk of 3
            i++; // Move to the next suffix
        }

        // Clean up any trailing spaces
        while (!ans.empty() && ans.back() == ' ')
            ans.pop_back();

        return ans;
    }
};
void solve() {
    int num; cin >> num;

    Solution sol;
    cout << sol.numberToWords(num) << nl;
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

