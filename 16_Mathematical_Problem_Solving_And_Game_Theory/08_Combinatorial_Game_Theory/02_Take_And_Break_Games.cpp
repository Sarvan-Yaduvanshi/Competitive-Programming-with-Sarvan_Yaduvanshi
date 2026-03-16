/*
 * ============================================================
 *  Topic   : Take-and-Break Games & Turning Turtles
 *  Pattern : Games where piles split or coins flip
 *
 *  Covers:
 *    - Take-and-Break (split a pile after removing)
 *    - Turning Turtles (coin flipping game)
 *    - Lasker's Nim (take or split)
 *
 *  Complexity: O(n²) for Grundy computation via splits
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

int mex(set<int>& S) {
    int m = 0;
    while (S.count(m)) m++;
    return m;
}

/*
 * ============================================================
 *  LASKER'S NIM
 * ============================================================
 *
 *  One pile of n stones. Each turn:
 *    Option A: Take any positive number of stones from the pile
 *    Option B: Split the pile into two non-empty piles
 *  Last to move wins.
 *
 *  GRUNDY VALUES:
 *    G(0) = 0
 *    G(1) = 1 (take 1)
 *    G(2) = 2 (take 1 → G(1)=1, take 2 → G(0)=0, split(1,1) → G(1)⊕G(1)=0)
 *           mex({0,1,0}) = 2
 *    G(3) = 3, G(4) = mex({0,1,2,3, G(1)⊕G(3), G(2)⊕G(2)})
 *
 *  PATTERN: G(n) = n for n not divisible by 3 (approximately)
 *  Actually: G(0)=0, and for n ≥ 1:
 *    if n % 3 == 0: G(n) = n/3 * 4 (approximately — compute to verify)
 *
 *  For small n: brute-force compute, then check pattern.
 * ============================================================
 */

vec<int> laskerNimGrundy(int maxN) {
    vec<int> G(maxN + 1, 0);
    for (int n = 1; n <= maxN; n++) {
        set<int> reachable;
        // Option A: take k stones (1 ≤ k ≤ n)
        for (int k = 1; k <= n; k++) {
            reachable.insert(G[n - k]);
        }
        // Option B: split into (a, n-a) where 1 ≤ a ≤ n-1
        for (int a = 1; a < n; a++) {
            reachable.insert(G[a] ^ G[n - a]);
        }
        G[n] = mex(reachable);
    }
    return G;
}

/*
 * ============================================================
 *  TURNING TURTLES (Coin-Turning Game)
 * ============================================================
 *
 *  n coins in a row (positions 0..n-1), each H or T.
 *  Move: flip a Heads coin to Tails at position i, AND
 *        optionally flip any ONE coin at position j < i.
 *  Game ends when all coins are T.
 *  Last to move wins.
 *
 *  ANALYSIS:
 *  - Each H at position i behaves like a Nim pile of size i.
 *  - Flipping coin i from H→T = removing pile of size i.
 *  - Optionally flipping coin j < i:
 *    - If j was T→H: adding pile of size j (like Nim move)
 *    - If j was H→T: removing pile of size j
 *  - The combined effect is: the game is equivalent to Nim
 *    with piles at positions of all Heads.
 *
 *  GRUNDY VALUE = XOR of positions of all Heads coins.
 *  First player wins ⟺ XOR ≠ 0.
 * ============================================================
 */

bool turningTurtlesFirstWins(vec<bool>& coins) {
    // coins[i] = true means Heads at position i
    int xorVal = 0;
    for (int i = 0; i < sz(coins); i++) {
        if (coins[i]) {  // Heads
            xorVal ^= i;
        }
    }
    return xorVal != 0;
}

/*
 * ============================================================
 *  GENERIC TAKE-AND-BREAK
 * ============================================================
 *
 *  Pile of n stones. Move: take k stones (k ≥ 1), then
 *  optionally split remainder into two piles.
 *
 *  G(n) = mex({ G(n-k) : k=1..n } ∪ { G(a) ⊕ G(b) : a+b=n-k, a,b ≥ 1 for k=1..n-1 })
 *
 *  This is very general. Specific games impose constraints on k or the split.
 * ============================================================
 */

vec<int> takeAndBreakGrundy(int maxN) {
    vec<int> G(maxN + 1, 0);
    for (int n = 1; n <= maxN; n++) {
        set<int> reachable;
        for (int k = 1; k <= n; k++) {
            int rem = n - k;
            // Don't split: just one pile of size rem
            reachable.insert(G[rem]);
            // Split remainder into two non-empty piles
            for (int a = 1; a < rem; a++) {
                reachable.insert(G[a] ^ G[rem - a]);
            }
        }
        G[n] = mex(reachable);
    }
    return G;
}

void solve() {
    int n;
    cin >> n;

    // Demo: compute Lasker's Nim Grundy values
    auto G = laskerNimGrundy(min(n, 100));

    cout << "Lasker's Nim Grundy values:" << nl;
    for (int i = 0; i <= min(n, 100); i++) {
        cout << "G(" << i << ") = " << G[i] << nl;
    }
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

