/*
 * ============================================================
 *  Topic   : Classic Nim Game
 *  Pattern : XOR of pile sizes determines winner
 *
 *  Problem : CSES 1730 — Game of Nim
 *  Input   : T test cases. Each: k piles, then pile sizes.
 *  Output  : "first" or "second" for each test case.
 *
 *  Complexity: O(k) per test case
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
 *  CLASSIC NIM — Bouton's Theorem
 * ============================================================
 *
 *  THEOREM: In a Nim game with piles n1, n2, ..., nk:
 *    First player wins ⟺ n1 ⊕ n2 ⊕ ... ⊕ nk ≠ 0
 *
 *  WINNING STRATEGY (when XOR ≠ 0):
 *    1. Let X = n1 ⊕ n2 ⊕ ... ⊕ nk
 *    2. Find any pile ni such that ni ⊕ X < ni
 *       (at least one such pile exists — the one containing
 *        the highest set bit of X)
 *    3. Replace ni with ni ⊕ X
 *    4. Now XOR = 0 → opponent is in losing position
 *
 *  PROOF OUTLINE:
 *    - XOR = 0 is the terminal losing condition (all piles empty)
 *    - From XOR = 0, any move changes exactly one pile,
 *      so XOR becomes non-zero
 *    - From XOR ≠ 0, the winning move described above
 *      always exists and leads to XOR = 0
 * ============================================================
 */

void solve() {
    int k;
    cin >> k;

    vec<int> piles(k);
    read(piles);

    int xorSum = 0;
    for (int x : piles) xorSum ^= x;

    if (xorSum != 0) {
        cout << "first" << nl;
    } else {
        cout << "second" << nl;
    }
}

/*
 *  FINDING THE WINNING MOVE (for interactive problems)
 *  Returns {pile_index, new_pile_size} or {-1, -1} if losing
 */
pii findWinningMove(vec<int>& piles) {
    int xorSum = 0;
    for (int x : piles) xorSum ^= x;

    if (xorSum == 0) return {-1, -1};  // losing position

    for (int i = 0; i < sz(piles); i++) {
        int newSize = piles[i] ^ xorSum;
        if (newSize < piles[i]) {
            return {i, newSize};  // reduce pile i to newSize
        }
    }

    return {-1, -1};  // should never reach here if xorSum != 0
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

