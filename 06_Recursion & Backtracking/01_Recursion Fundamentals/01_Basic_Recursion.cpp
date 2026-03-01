/*
╔══════════════════════════════════════════════════════════════╗
║  01. BASIC RECURSION: Factorial, Fibonacci, Sum of Digits    ║
║  Level 1 — Recursion Fundamentals                            ║
╚══════════════════════════════════════════════════════════════╝

🎯 Problems:
   1. Factorial of N
   2. Fibonacci (Nth number)
   3. Sum of Digits of N
   4. Count Digits of N
   5. Print 1 to N (Head recursion vs Tail recursion)
   6. Print N to 1
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
void read(vec<T> &v) {
    for (auto &x : v) cin >> x;
}
#define nl '\n'

// ═══════════════════════════════════════════════════════════
// 1️⃣ FACTORIAL
// ═══════════════════════════════════════════════════════════
/*
   factorial(n) = n * (n-1) * (n-2) * ... * 1

   Recurrence: fact(n) = n * fact(n-1)
   Base case:  fact(0) = 1, fact(1) = 1

   Time:  O(n)
   Space: O(n) — call stack depth

   Recursion Tree for fact(4):
       fact(4)
       └── 4 * fact(3)
               └── 3 * fact(2)
                       └── 2 * fact(1)
                               └── return 1  ← BASE CASE
*/
i64 factorial(int n) {
    // Base case
    if (n <= 1) return 1;
    // Recursive case
    return (i64)n * factorial(n - 1);
}

// Factorial with MOD (for competitive programming)
i64 factorialMod(int n, i64 mod = MOD) {
    if (n <= 1) return 1;
    return ((i64)n % mod * factorialMod(n - 1, mod)) % mod;
}


// ═══════════════════════════════════════════════════════════
// 2️⃣ FIBONACCI
// ═══════════════════════════════════════════════════════════
/*
   fib(0) = 0, fib(1) = 1
   fib(n) = fib(n-1) + fib(n-2)

   Sequence: 0, 1, 1, 2, 3, 5, 8, 13, 21, ...

   ⚠️ NAIVE: Time O(2^n) — VERY SLOW

   Recursion Tree for fib(5):
                        fib(5)
                       /      \
                  fib(4)      fib(3)
                 /    \       /    \
            fib(3)  fib(2) fib(2) fib(1)
            /  \    /  \    /  \
        fib(2) fib(1) ... ...  ...

   Notice: fib(3) is computed TWICE! → leads to exponential time
   Solution: Memoization (Level 5) or iterative approach
*/

// Naive (DON'T use for n > 40)
i64 fibNaive(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return fibNaive(n - 1) + fibNaive(n - 2);
}

// Memoized (GOOD — O(n) time, O(n) space)
map<int, i64> fibMemo;
i64 fibFast(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    if (fibMemo.count(n)) return fibMemo[n];
    return fibMemo[n] = fibFast(n - 1) + fibFast(n - 2);
}


// ═══════════════════════════════════════════════════════════
// 3️⃣ SUM OF DIGITS
// ═══════════════════════════════════════════════════════════
/*
   sumDigits(1234) = 1 + 2 + 3 + 4 = 10

   Recurrence: sumDigits(n) = (n % 10) + sumDigits(n / 10)
   Base case:  sumDigits(0) = 0

   Time:  O(d) where d = number of digits = O(log10(n))
   Space: O(d)
*/
int sumDigits(int n) {
    if (n == 0) return 0;
    return (n % 10) + sumDigits(n / 10);
}


// ═══════════════════════════════════════════════════════════
// 4️⃣ COUNT DIGITS
// ═══════════════════════════════════════════════════════════
/*
   countDigits(1234) = 4

   Recurrence: countDigits(n) = 1 + countDigits(n / 10)
   Base case:  countDigits(0) = 0  (or n < 10 → return 1)
*/
int countDigits(int n) {
    if (n < 10) return 1;
    return 1 + countDigits(n / 10);
}


// ═══════════════════════════════════════════════════════════
// 5️⃣ PRINT 1 to N (Tail Recursion — print BEFORE recursive call)
// ═══════════════════════════════════════════════════════════
/*
   print1toN(5):
   Output: 1 2 3 4 5

   Approach: print current, then recurse for next
*/
void print1toN(int i, int n) {
    if (i > n) return;      // Base case
    cout << i << " ";        // Work at current level
    print1toN(i + 1, n);    // Recursive call
}


// ═══════════════════════════════════════════════════════════
// 6️⃣ PRINT N to 1 (Head Recursion — print AFTER recursive call)
// ═══════════════════════════════════════════════════════════
/*
   printNto1(5):
   Output: 5 4 3 2 1

   Two approaches:
   A) Decrement approach: print n, recurse n-1
   B) Head recursion: recurse first, print after
*/

// Approach A: Simple decrement
void printNto1_A(int n) {
    if (n == 0) return;
    cout << n << " ";
    printNto1_A(n - 1);
}

// Approach B: Print 1 to N but using HEAD recursion (print N to 1)
// 🧠 Trick: recurse FIRST, then print → prints in reverse!
void printNto1_B(int i, int n) {
    if (i > n) return;
    printNto1_B(i + 1, n);  // Recurse first
    cout << i << " ";        // Print after returning (reverse order!)
}


// ═══════════════════════════════════════════════════════════
// 🧪 TEST ALL FUNCTIONS
// ═══════════════════════════════════════════════════════════

void solve() {
    cout << "=== FACTORIAL ===" << nl;
    for (int i = 0; i <= 10; i++) {
        cout << "fact(" << i << ") = " << factorial(i) << nl;
    }

    cout << nl << "=== FIBONACCI ===" << nl;
    for (int i = 0; i <= 15; i++) {
        cout << "fib(" << i << ") = " << fibFast(i) << nl;
    }

    cout << nl << "=== SUM OF DIGITS ===" << nl;
    cout << "sumDigits(1234) = " << sumDigits(1234) << nl;
    cout << "sumDigits(9999) = " << sumDigits(9999) << nl;

    cout << nl << "=== COUNT DIGITS ===" << nl;
    cout << "countDigits(1234) = " << countDigits(1234) << nl;
    cout << "countDigits(100000) = " << countDigits(100000) << nl;

    cout << nl << "=== PRINT 1 to 10 ===" << nl;
    print1toN(1, 10);
    cout << nl;

    cout << nl << "=== PRINT 10 to 1 (Approach A) ===" << nl;
    printNto1_A(10);
    cout << nl;

    cout << nl << "=== PRINT 10 to 1 (Approach B — Head Recursion) ===" << nl;
    printNto1_B(1, 10);
    cout << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    int TC = 1;
    // cin >> TC;
    while (TC--) solve();

    return 0;
}

