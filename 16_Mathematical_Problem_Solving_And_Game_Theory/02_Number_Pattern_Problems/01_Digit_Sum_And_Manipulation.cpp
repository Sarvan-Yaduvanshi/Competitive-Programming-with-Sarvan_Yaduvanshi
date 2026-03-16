/*
 * ============================================================
 *  Topic   : Digit Sum & Digit Manipulation Techniques
 *  Pattern : Extract digits, compute digit sums, digital root
 *
 *  Problems Covered:
 *    - Add Digits / Digital Root (LeetCode 258)
 *    - Happy Number (LeetCode 202)
 *    - Sum of digit differences
 *
 *  Complexity: O(log n) per number for digit operations
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
// DIGIT EXTRACTION
// ────────────────────────────────────────────
vec<int> getDigits(i64 n) {
    if (n == 0) return {0};
    vec<int> digits;
    while (n > 0) {
        digits.pb(n % 10);
        n /= 10;
    }
    reverse(all(digits));
    return digits;
}

// ────────────────────────────────────────────
// DIGIT SUM
// ────────────────────────────────────────────
int digitSum(i64 n) {
    int s = 0;
    while (n > 0) {
        s += n % 10;
        n /= 10;
    }
    return s;
}

// ────────────────────────────────────────────
// DIGITAL ROOT (O(1) formula)
// ────────────────────────────────────────────
// Repeatedly sum digits until single digit
// Formula: digitalRoot(n) = 1 + (n-1) % 9 for n > 0
int digitalRoot(i64 n) {
    if (n == 0) return 0;
    return 1 + (n - 1) % 9;
}

// ────────────────────────────────────────────
// HAPPY NUMBER (LeetCode 202)
// ────────────────────────────────────────────
// Replace n with sum of squares of its digits.
// If reaches 1 → happy. If cycles → not happy.
// Use Floyd's cycle detection.
int sumOfSquaresOfDigits(int n) {
    int s = 0;
    while (n > 0) {
        int d = n % 10;
        s += d * d;
        n /= 10;
    }
    return s;
}

bool isHappy(int n) {
    int slow = n, fast = n;
    do {
        slow = sumOfSquaresOfDigits(slow);
        fast = sumOfSquaresOfDigits(sumOfSquaresOfDigits(fast));
    } while (slow != fast);
    return slow == 1;
}

// ────────────────────────────────────────────
// REVERSE NUMBER
// ────────────────────────────────────────────
i64 reverseNumber(i64 n) {
    i64 rev = 0;
    while (n > 0) {
        rev = rev * 10 + n % 10;
        n /= 10;
    }
    return rev;
}

// ────────────────────────────────────────────
// COUNT DIGITS
// ────────────────────────────────────────────
int countDigits(i64 n) {
    if (n == 0) return 1;
    return (int)log10(n) + 1;
}

void solve() {
    i64 n;
    cin >> n;

    cout << "Digits: ";
    for (int d : getDigits(n)) cout << d << " ";
    cout << nl;

    cout << "Digit Sum: " << digitSum(n) << nl;
    cout << "Digital Root: " << digitalRoot(n) << nl;
    cout << "Is Happy: " << (isHappy((int)n) ? "Yes" : "No") << nl;
    cout << "Reversed: " << reverseNumber(n) << nl;
    cout << "Digit Count: " << countDigits(n) << nl;
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

