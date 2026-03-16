/*
 * ============================================================
 *  Topic   : Base Conversion Problems
 *  Pattern : Convert between bases, analyze base-k representations
 *
 *  Problems:
 *    - Base 7 (LeetCode 504)
 *    - Convert to Base -2 (LeetCode 1017)
 *    - Check if number is palindrome in any base
 *
 *  Complexity: O(log_k(n)) per conversion
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
// BASE-10 → BASE-k (k ≤ 36)
// ────────────────────────────────────────────
string toBase(i64 n, int k) {
    if (n == 0) return "0";
    bool neg = (n < 0);
    if (neg) n = -n;

    string res;
    while (n > 0) {
        int rem = n % k;
        if (rem < 10) res += char('0' + rem);
        else res += char('a' + rem - 10);
        n /= k;
    }
    if (neg) res += '-';
    reverse(all(res));
    return res;
}

// ────────────────────────────────────────────
// BASE-k → BASE-10
// ────────────────────────────────────────────
i64 fromBase(const string& s, int k) {
    i64 res = 0;
    for (char c : s) {
        int digit;
        if (c >= '0' && c <= '9') digit = c - '0';
        else digit = c - 'a' + 10;
        res = res * k + digit;
    }
    return res;
}

// ────────────────────────────────────────────
// NEGATIVE BASE CONVERSION (e.g., base -2)
// LeetCode 1017: Convert to Base -2
// ────────────────────────────────────────────
string toNegBase(int n, int negBase) {
    if (n == 0) return "0";
    string res;
    while (n != 0) {
        int rem = n % negBase;
        n /= negBase;
        // In C++, remainder can be negative
        if (rem < 0) {
            rem -= negBase;  // make remainder positive
            n++;             // adjust quotient
        }
        res += char('0' + rem);
    }
    reverse(all(res));
    return res;
}

// ────────────────────────────────────────────
// DIGIT SUM IN BASE-k
// ────────────────────────────────────────────
int digitSumInBase(i64 n, int k) {
    int s = 0;
    while (n > 0) {
        s += n % k;
        n /= k;
    }
    return s;
}

// ────────────────────────────────────────────
// CHECK IF PALINDROME IN BASE-k
// ────────────────────────────────────────────
bool isPalindromeInBase(i64 n, int k) {
    vec<int> digits;
    i64 tmp = n;
    while (tmp > 0) {
        digits.pb(tmp % k);
        tmp /= k;
    }
    int l = 0, r = sz(digits) - 1;
    while (l < r) {
        if (digits[l] != digits[r]) return false;
        l++; r--;
    }
    return true;
}

// ────────────────────────────────────────────
// HIGHEST POWER OF k DIVIDING n!
// (Legendre's formula)
// ────────────────────────────────────────────
i64 legendreFormula(i64 n, int p) {
    i64 count = 0;
    i64 pk = p;
    while (pk <= n) {
        count += n / pk;
        pk *= p;
    }
    return count;
}

void solve() {
    i64 n;
    int k;
    cin >> n >> k;

    cout << "Base-" << k << " representation: " << toBase(n, k) << nl;
    cout << "Digit sum in base-" << k << ": " << digitSumInBase(n, k) << nl;
    cout << "Palindrome in base-" << k << ": " << (isPalindromeInBase(n, k) ? "Yes" : "No") << nl;
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

