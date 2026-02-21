/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-21 21:14:52
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

/* Problem: LC 125 — Valid Palindrome
 * Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.
 *
 * Example 1:
 * Input: s = "A man, a plan, a canal: Panama"
 * Output: true
 * Explanation: "amanaplanacanalpanama" is a palindrome.
 *
 * Example 2:
 * Input: s = "race a car"
 * Output: false
 * Explanation: "raceacar" is not a palindrome.
 *
 * Example 3:
 * Input: s = " "
 * Output: true
 * Explanation: After removing non-alphanumeric chars, s is "". Empty string is palindrome.
 *
 * Constraints:
 * - 1 <= s.length <= 2 * 10^5
 * - s consists only of printable ASCII characters.
 *
 * ─────────── KEY CONCEPTS USED ───────────
 *  1. Remove non-alphanumeric characters (whitespace, punctuation)
 *  2. Convert uppercase → lowercase (case-insensitive comparison)
 *  3. Two-pointer palindrome check
 *  4. Bitwise tricks for case conversion
 */

/*
 * ═══════════════════════════════════════════════════════════════
 *  Approach 1: BRUTE FORCE (Beginner)
 *  - Create a cleaned string (only alphanumeric, all lowercase)
 *  - Reverse it and compare
 *  Time: O(n), Space: O(n)
 * ═══════════════════════════════════════════════════════════════
 */
bool isPalindrome_BruteForce(string s) {
    // Step 1: Clean the string — remove non-alphanumeric, convert to lowercase
    string cleaned = "";
    for (char c : s) {
        if (isalnum(static_cast<unsigned char>(c))) {
            cleaned += tolower(static_cast<unsigned char>(c));
        }
    }

    // Step 2: Reverse and compare
    string reversed = cleaned;
    reverse(all(reversed));

    return cleaned == reversed;
}

/*
 * ═══════════════════════════════════════════════════════════════
 *  Approach 2: CLEAN + TWO POINTER (Intermediate)
 *  - Create a cleaned string
 *  - Use two pointers from both ends
 *  Time: O(n), Space: O(n) for cleaned string
 * ═══════════════════════════════════════════════════════════════
 */
bool isPalindrome_CleanTwoPointer(string s) {
    // Step 1: Clean string
    string cleaned;
    for (char c : s) {
        if (isalnum(static_cast<unsigned char>(c))) {
            cleaned += tolower(static_cast<unsigned char>(c));
        }
    }

    // Step 2: Two pointers
    int left = 0, right = sz(cleaned) - 1;
    while (left < right) {
        if (cleaned[left] != cleaned[right]) return false;
        left++;
        right--;
    }
    return true;
}

/*
 * ═══════════════════════════════════════════════════════════════
 *  Approach 3: IN-PLACE TWO POINTER — NO EXTRA SPACE (Expert)
 *  - Two pointers on ORIGINAL string
 *  - Skip non-alphanumeric characters
 *  - Compare with case-insensitive check
 *  Time: O(n), Space: O(1) ✅
 * ═══════════════════════════════════════════════════════════════
 */
bool isPalindrome_InPlace(const string &s) {
    int left = 0, right = sz(s) - 1;

    while (left < right) {
        // Skip non-alphanumeric from left
        while (left < right && !isalnum(static_cast<unsigned char>(s[left]))) left++;
        // Skip non-alphanumeric from right
        while (left < right && !isalnum(static_cast<unsigned char>(s[right]))) right--;

        // Compare (case-insensitive)
        if (tolower(static_cast<unsigned char>(s[left])) !=
            tolower(static_cast<unsigned char>(s[right]))) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

/*
 * ═══════════════════════════════════════════════════════════════
 *  Approach 4: BITWISE GM LEVEL — FASTEST
 *  - In-place, O(1) space
 *  - Use (c | 32) for case-insensitive comparison (bitwise trick)
 *  - Manual isalnum check for maximum speed
 *  Time: O(n), Space: O(1) ✅
 *
 *  BITWISE INSIGHT:
 *  - (c | 32) converts uppercase to lowercase without branching
 *  - 'A' | 32 = 'a', 'B' | 32 = 'b', ..., 'Z' | 32 = 'z'
 *  - For digits: '0'|32 = '0' (no change, since bit 5 already set for digits 48-57)
 *    BUT '0'|32 = 48|32 = 48 (bit 5 is actually 0 for '0'=48=0b110000)
 *    Wait: 48 = 0011 0000, 48|32 = 0011 0000 | 0010 0000 = 0011 0000 = 48...
 *    Actually '0'|32 still = 48? No: 48|32 = 48 since bit 5 of 48 is 1!
 *    48 = 0b00110000, bit 5 (value 32) = 1. So yes, digits are unchanged by |32.
 *
 *  ⚠️ For safety with digits, we can just use tolower() which is well-optimized.
 * ═══════════════════════════════════════════════════════════════
 */

// Fast inline check: is c a letter?
inline bool isAlpha(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

// Fast inline check: is c a digit?
inline bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

// Fast inline check: is c alphanumeric?
inline bool isAlNum(char c) {
    return isAlpha(c) || isDigit(c);
}

// Fast inline: convert to lowercase using bitwise OR
inline char toLower(char c) {
    if (isAlpha(c)) return c | 32;
    return c;  // digits and others unchanged
}

bool isPalindrome_GM(const string &s) {
    int left = 0, right = sz(s) - 1;

    while (left < right) {
        // Skip non-alphanumeric from left
        while (left < right && !isAlNum(s[left])) left++;
        // Skip non-alphanumeric from right
        while (left < right && !isAlNum(s[right])) right--;

        // Compare (case-insensitive using bitwise)
        if (toLower(s[left]) != toLower(s[right])) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

/*
 * ═══════════════════════════════════════════════════════════════
 *  COMPLEXITY COMPARISON
 * ═══════════════════════════════════════════════════════════════
 *
 *  ┌─────────────────────┬──────────┬──────────┬─────────────────┐
 *  │ Approach            │ Time     │ Space    │ Level           │
 *  ├─────────────────────┼──────────┼──────────┼─────────────────┤
 *  │ Brute Force         │ O(n)     │ O(n)     │ Beginner        │
 *  │ Clean + Two Pointer │ O(n)     │ O(n)     │ Intermediate    │
 *  │ In-Place Two Ptr    │ O(n)     │ O(1)     │ Expert          │
 *  │ Bitwise GM          │ O(n)     │ O(1)     │ Grand Master    │
 *  └─────────────────────┴──────────┴──────────┴─────────────────┘
 *
 *  All are O(n) time, but the GM approach:
 *  - Uses O(1) space (no extra string allocation)
 *  - Avoids function call overhead (inline helpers)
 *  - Uses bitwise ops instead of branches (faster on CPU)
 *  - Single pass through the string
 *
 * ═══════════════════════════════════════════════════════════════
 */

void solve() {
    // Test cases
    vector<pair<string, bool>> tests = {
        {"A man, a plan, a canal: Panama", true},
        {"race a car", false},
        {" ", true},
        {"Was it a car or a cat I saw?", true},
        {"No 'x' in Nixon", true},
        {"hello", false},
        {"abcba", true},
        {"0P", false},
    };

    cout << "═══════ LC 125: Valid Palindrome ═══════" << nl << nl;

    for (auto &[input, expected] : tests) {
        bool r1 = isPalindrome_BruteForce(input);
        bool r2 = isPalindrome_CleanTwoPointer(input);
        bool r3 = isPalindrome_InPlace(input);
        bool r4 = isPalindrome_GM(input);

        string status = (r1 == expected && r2 == expected && r3 == expected && r4 == expected)
                        ? "✅ PASS" : "❌ FAIL";

        cout << status << " | Input: \"" << input << "\"" << nl;
        cout << "       Expected: " << (expected ? "true" : "false") << nl;
        cout << "       BruteForce=" << r1 << " CleanTP=" << r2
             << " InPlace=" << r3 << " GM=" << r4 << nl << nl;
    }
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

