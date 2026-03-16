/*
 * ============================================================
 *  Topic   : Monovariants — Proving Termination & Bounding Steps
 *  Pattern : A quantity that strictly increases/decreases → process terminates
 *
 *  Covers:
 *    1. Monovariant concept and examples
 *    2. Bounding the number of operations
 *    3. Constructive problems using monovariants
 *
 *  Example Problem: Codeforces — reduce array elements until stable
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

/*
 * ============================================================
 *  MONOVARIANTS
 * ============================================================
 *
 *  A MONOVARIANT is a function f(state) that:
 *    - Strictly increases (or strictly decreases) with each operation
 *    - Is bounded (above or below)
 *    ⟹ The process MUST terminate
 *
 *  USE CASES:
 *  1. Prove a process terminates
 *  2. Bound the number of steps (f changes by ≥1 each step,
 *     bounded by B → at most B steps)
 *  3. Guide greedy algorithms
 *
 *  EXAMPLE 1: GCD Reduction
 *  ─────────────────────────
 *  Euclidean algorithm: gcd(a,b) → gcd(b, a%b)
 *  Monovariant: max(a,b) strictly decreases (and is bounded below by 0)
 *  → Algorithm terminates
 *  → At most O(log(min(a,b))) steps (Fibonacci worst case)
 *
 *  EXAMPLE 2: Replace max with difference
 *  ──────────────────────────────────────
 *  Array operation: replace a[i] with |a[i] - a[j]|
 *  Monovariant: sum of array strictly decreases
 *  Bounded below by 0 → terminates
 *  Max steps ≤ initial sum
 *
 *  EXAMPLE 3: Sorting by swaps
 *  ───────────────────────────
 *  Monovariant: number of inversions
 *  Each adjacent swap reduces inversions by exactly 1
 *  Bounded below by 0 → terminates after exactly (# inversions) swaps
 * ============================================================
 */

// Count inversions — a monovariant for sorting
i64 countInversions(vec<int>& a) {
    int n = sz(a);
    i64 inv = 0;
    // Simple O(n^2) count (use merge sort for O(n log n))
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] > a[j]) inv++;
    return inv;
}

/*
 *  APPLICATION: Simulation with bounded steps
 *  ──────────────────────────────────────────
 *  Problem: Given array, repeatedly replace a[i] with a[i] mod a[j]
 *  (for some j where a[j] < a[i]). Count operations until no more possible.
 *
 *  Monovariant: sum of all elements strictly decreases each step
 *  Bound: at most O(sum) steps naively, but actually O(n log(max)) because
 *  each element halves when you take it mod something ≤ half its value.
 */

int simulateModReduction(vec<int> a) {
    int n = sz(a);
    int ops = 0;
    bool changed = true;
    while (changed) {
        changed = false;
        int mn = *min_element(all(a));
        if (mn == 0) break;
        for (int i = 0; i < n; i++) {
            if (a[i] > mn) {
                a[i] %= mn;
                ops++;
                changed = true;
            }
        }
    }
    return ops;
}

void solve() {
    int n;
    cin >> n;
    vec<int> a(n);
    read(a);

    cout << "Inversions (monovariant for sorting): " << countInversions(a) << nl;
    cout << "Mod reduction operations: " << simulateModReduction(a) << nl;
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

