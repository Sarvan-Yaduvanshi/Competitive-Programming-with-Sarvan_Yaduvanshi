/*
 * ============================================================
 *  Topic   : Palindrome Numbers
 *  Pattern : Check, generate, find next palindrome
 *
 *  Problems:
 *    - Palindrome Number (LeetCode 9)
 *    - Find the Closest Palindrome (LeetCode 564)
 *
 *  Complexity: O(log n) for check, O(d) for generation (d = digits)
 * ============================================================
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

using i64 = long long;
using u64 = unsigned long long;
using ld  = long double;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int, int>;
using pll = pair<i64, i64>;

constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD   = 1'000'000'007LL;
constexpr i64 MOD9  = 998'244'353LL;
constexpr ld PI     = 3.14159265358979323846;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

template<class T>
void read(vec<T> &v) { for (auto &x : v) cin >> x; }
#define nl '\n'
#define YES cout << "YES" << nl
#define NO cout << "NO" << nl

// ────────────────────────────────────────────
// METHOD 1: Check palindrome without string conversion
// Reverse only the second half
// ────────────────────────────────────────────
bool isPalindromeNumber(int n) {
    if (n < 0 || (n % 10 == 0 && n != 0)) return false;
    int rev = 0;
    while (n > rev) {
        rev = rev * 10 + n % 10;
        n /= 10;
    }
    // Even digits: n == rev
    // Odd digits:  n == rev / 10 (middle digit in rev)
    return n == rev || n == rev / 10;
}

// ────────────────────────────────────────────
// METHOD 2: String-based palindrome check
// ────────────────────────────────────────────
bool isPalindromeStr(i64 n) {
    string s = to_string(n);
    int l = 0, r = sz(s) - 1;
    while (l < r) {
        if (s[l] != s[r]) return false;
        l++; r--;
    }
    return true;
}

// ────────────────────────────────────────────
// Generate all d-digit palindromes
// Only need first ceil(d/2) digits
// ────────────────────────────────────────────
vec<i64> generatePalindromes(int d) {
    vec<i64> result;
    int half = (d + 1) / 2;
    i64 lo = 1;
    for (int i = 1; i < half; i++) lo *= 10;
    i64 hi = lo * 10;

    for (i64 prefix = lo; prefix < hi; prefix++) {
        string s = to_string(prefix);
        string rev = s;
        reverse(all(rev));

        string pal;
        if (d % 2 == 0) {
            pal = s + rev;
        } else {
            pal = s + rev.substr(1);  // skip duplicate middle
        }
        result.pb(stoll(pal));
    }
    return result;
}

// ────────────────────────────────────────────
// Next Palindrome ≥ n
// Strategy: Mirror left half to right. If result < n, increment middle.
// ────────────────────────────────────────────
i64 nextPalindrome(i64 n) {
    string s = to_string(n);
    int len = sz(s);

    // Try mirroring left half
    string mirrored = s;
    for (int i = 0; i < len / 2; i++) {
        mirrored[len - 1 - i] = mirrored[i];
    }

    if (stoll(mirrored) >= n) return stoll(mirrored);

    // Increment the middle part and re-mirror
    int mid = (len - 1) / 2;
    int carry = 1;
    for (int i = mid; i >= 0 && carry; i--) {
        int d = (mirrored[i] - '0') + carry;
        mirrored[i] = '0' + d % 10;
        carry = d / 10;
    }

    if (carry) {
        // Overflow: e.g., 999 → 1001
        string res(len + 1, '0');
        res[0] = res[len] = '1';
        return stoll(res);
    }

    // Re-mirror
    for (int i = 0; i < len / 2; i++) {
        mirrored[len - 1 - i] = mirrored[i];
    }

    return stoll(mirrored);
}

void solve() {
    i64 n;
    cin >> n;

    cout << "Is palindrome: " << (isPalindromeStr(n) ? "Yes" : "No") << nl;
    cout << "Next palindrome >= " << n << ": " << nextPalindrome(n) << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    int TC = 1;
    cin >> TC;
    while (TC--) solve();

    return 0;
}

