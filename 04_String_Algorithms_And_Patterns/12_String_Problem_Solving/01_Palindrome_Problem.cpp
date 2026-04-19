/*
Author: Sarvan.DP.GrandMaster
Created : 2026-04-13 09:14:16
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

// <================ Cover all types of string Palindrome problems here =================>

/* Problem 1: Leetcode 125. Valid Palindrome
 * A phrase is a palindrome if, after converting all uppercase letters into lowercase letters and
 * removing all non-alphanumeric characters, it reads the same forward and backward.
 * Alphanumeric characters include letters and numbers.
 * Given a string s, return true if it is a palindrome, or false otherwise.
 *
 * Example 1: Input: s = "A man, a plan, a canal: Panama"  Output: true
 * Explanation: "amanaplanacanalpanama" is a palindrome.
 *
 * Example 2: Input: s = "race a car"  Output: false
 * Explanation: "raceacar" is not a palindrome.
 *
 * Constraints:
 * • 1 <= s.length <= 2 * 10^5
 * • s consists only of printable ASCII characters.
 */

// Approach 1: Use Two Pointers Technique
// Key Idea: Use two pointers left point to start and right point to end the string.
// Remove all non-alphanumeric characters and convert to lowercase before comparing characters at left and right.
// Time Complexity: O(n) where n is the length of the string.
// Space Complexity: O(1)

bool isPalindrome(string str){
    // check string are empty so empty string are always palindrome
    if (str.empty()) return true;

    int left = 0;
    int right = (int)str.size() - 1;

    while (left < right){
        // 1. Skip non-alphanumeric (left) side
        while (left < right && !isalnum(str[left]))
            left++;

        // 2. Skip non-alphanumeric (right) side
        while (left < right && !isalnum(str[right]))
            right--;

        // 3. Case-insensitive comparison
        if (tolower(str[left]) != tolower(str[right]))
            return false;

        // 4. shrink window
        left++;
        right--;
    }

    return true;
}

// Approach 2: Steel use Two Pointers Technique but
// remove all non-alphanumeric characters not use C++ STL like(isAlnum()) implementation own function
// Key Idea: 1. Check it is a character or not
//           2. Check it is a digit or not
//           3. Check it is a alphanumeric or not
//           4. Convert uppercase to lowercase using bit manipulation (c | ' ')
// Time Complexity: O(n) where n is the length of the string.
// Space Complexity: O(1)

// step 1: // Fast inline check: is c a characters?
inline bool isAlpha(char ch){
    return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'));
}

// Step 2: // Fast inline check: is a ch digit?
inline bool isDigit(char ch){
    return (ch >= '1' && ch <= '9');
}

// Step 3: Fast inline check: is c alphanumeric?
inline bool isAlNum(char ch){
    return (isAlpha(ch) || isdigit(ch));
}

// Step 4: Fast inline: convert to lowercase using bitwise OR
inline char Tolower(char ch){
    if (isalpha(ch)) return ch | 32;
    return ch; // digits and others unchanged
}

bool validPalindrome(string str){
    if (str.empty()) return true;

    int left = 0;
    int right = (int)str.size() - 1;

    while (left < right){
        while (left < right && !isAlNum(str[left]))
            left++;
        while (left < right && !isAlNum(str[right]))
            right--;

        if (Tolower(str[left]) != Tolower(str[right]))
            return false;

        left++;
        right--;
    }
    return true;
}

/* Problem 2: Leetcode 680. Valid Palindrome II
 *  Given a string s, return true if the s can be palindrome after deleting at most one character from it.
 *
 *  Example 1: Input: s = "aba"  Output: true
 *  Explanation: The string is already a palindrome.
 *  Example 2: Input: s = "abca"  Output: true
 *  Explanation: You could delete the character 'c'.
 *  Example 3: Input: s = "abc"  Output: false
 *  Explanation: It is impossible to make it a palindrome by deleting one character.
 *
 *  Constraints:
 *  • 1 <= s.length <= 10^5
 *  • s consists of lowercase English letters.
 */

// Approach 1: Two Pointers + Helper Function
// Key Idea: Use two pointers to check palindrome. If mismatch occurs,
//         : try skipping left or right character and check if either results in a palindrome.
// Time Complexity: O(n) where n is the length of the string.
// Space Complexity: O(1)

bool validPalindromeII(string& str){
    // Lambda helper fun to check it is palindrome or not
    auto validPal = [&](int left, int right) -> bool{
        while (left < right){
            if (str[left] != str[right])
                return false;

            // shrink window
            left++;
            right--;
        }
        return true;
    };

    int left = 0;
    int right = (int)str.size() - 1;

    while (left < right){
        // skip if already left == right
        if (str[left] == str[right]){
            left++; right--;
        }else
            // skip left part at most one character or right part
            return validPal(left + 1, right) || validPal(left, right - 1);
    }

    return true;
}

// 




void solve() {
    // int n; cin >> n;
    // cin.ignore(); // avoid "\n" error

    string str;
    getline(cin, str);

    // Call function Problem 1
    // cout << (validPalindrome(str) ? "true" : "false") << nl;

    // Call function Problem 2
    cout << (validPalindromeII(str) ? "true" : "false") << nl;
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

