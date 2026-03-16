/*
 * ============================================================
 *  Topic   : Subtraction Game & Wythoff's Game
 *  Pattern : Periodic Grundy for subtraction, golden ratio for Wythoff
 *
 *  Problems:
 *    - Subtraction Game (generic)
 *    - SPOJ MWYTHON — Wythoff's Game
 *
 *  Complexity: O(n × |S|) for subtraction Grundy, O(1) for Wythoff
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
 *  SUBTRACTION GAME
 * ============================================================
 *
 *  One pile of n stones. Subtraction set S = {s1, s2, ..., sk}.
 *  Each turn: take exactly si stones (for some si in S).
 *  Last to move wins.
 *
 *  GRUNDY: G(n) = mex({ G(n - s) : s in S, s <= n })
 *
 *  KEY PROPERTY: Grundy values are EVENTUALLY PERIODIC.
 *  Compute for small n, find the period, extend to large n.
 *
 *  EXAMPLE: S = {1, 3, 4}
 *  G(0)=0, G(1)=1, G(2)=0, G(3)=2, G(4)=3, G(5)=1, G(6)=0, G(7)=2, ...
 *  Period = 5 after some transient
 * ============================================================
 */

int mex(set<int>& S) {
    int m = 0;
    while (S.count(m)) m++;
    return m;
}

vec<int> subtractionGameGrundy(int maxN, vec<int>& moves) {
    vec<int> G(maxN + 1, 0);
    for (int n = 1; n <= maxN; n++) {
        set<int> reachable;
        for (int s : moves) {
            if (n >= s) reachable.insert(G[n - s]);
        }
        G[n] = mex(reachable);
    }
    return G;
}

// Find period of Grundy values (look for repeating block)
int findPeriod(vec<int>& G, int minPeriod = 1) {
    int n = sz(G);
    for (int p = minPeriod; p <= n / 3; p++) {
        bool ok = true;
        // Check if last 2*p values match
        for (int i = n - 1; i >= n - 2 * p && i >= p; i--) {
            if (G[i] != G[i - p]) { ok = false; break; }
        }
        if (ok) return p;
    }
    return -1;  // no period found in range
}

/*
 * ============================================================
 *  WYTHOFF'S GAME
 * ============================================================
 *
 *  Two piles (a, b). Each turn:
 *    - Remove any positive number from ONE pile, OR
 *    - Remove the SAME positive number from BOTH piles
 *  Last to move wins.
 *
 *  LOSING POSITIONS (cold positions):
 *    (ak, bk) where:
 *      ak = floor(k * φ)
 *      bk = floor(k * φ²) = ak + k
 *    and φ = (1 + √5) / 2 ≈ 1.618
 *
 *  CHECK: given (a, b) with a <= b:
 *    k = b - a
 *    Losing iff a == floor(k * φ)
 *
 *  TIME: O(1) per query (just compute floor(k * φ))
 *
 *  CAUTION: For large values, floating point can be imprecise.
 *  Use careful rounding or Fibonacci-based methods.
 * ============================================================
 */

bool isWythoffLosing(i64 a, i64 b) {
    if (a > b) swap(a, b);
    i64 k = b - a;
    // φ = (1 + √5) / 2
    ld phi = (1.0L + sqrtl(5.0L)) / 2.0L;
    i64 expected_a = (i64)(k * phi);

    // Check nearby values due to floating point issues
    return a == expected_a;
}

// Generate first n cold positions of Wythoff's game
vec<pll> wythoffColdPositions(int n) {
    ld phi = (1.0L + sqrtl(5.0L)) / 2.0L;
    vec<pll> cold;
    for (int k = 0; k < n; k++) {
        i64 a = (i64)(k * phi);
        i64 b = a + k;
        cold.pb({a, b});
    }
    return cold;
}

/*
 * ============================================================
 *  MOORE'S NIM (k-NIM)
 * ============================================================
 *
 *  Standard Nim but can take from AT MOST k piles per turn.
 *
 *  THEOREM: Second wins ⟺ for every bit position,
 *           the sum of that bit across all piles ≡ 0 (mod k+1)
 *
 *  k = 1: Standard Nim (XOR = sum mod 2)
 *  k = 2: Sum each bit mod 3 = all zeros → second wins
 * ============================================================
 */

bool mooresNimFirstWins(vec<int>& piles, int k) {
    for (int bit = 0; bit < 30; bit++) {
        int sum = 0;
        for (int p : piles) {
            sum += (p >> bit) & 1;
        }
        if (sum % (k + 1) != 0) return true;  // first wins
    }
    return false;  // second wins
}

void solve() {
    i64 a, b;
    cin >> a >> b;

    // Wythoff's game: determine winner
    if (isWythoffLosing(a, b)) {
        cout << "second" << nl;
    } else {
        cout << "first" << nl;
    }
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

