/*
Author: Sarvan.DP.GrandMaster
Created : 2026-01-28 15:08:00
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

/**
 * Problem: 2D Difference Array (Range Updates + Point Query)
 * Technique: 2D Difference Array + 2D Prefix Sum
 * Time Complexity: O(Q + N*M)
 * Space Complexity: O(N*M)
 */

// METHOD 1: STATIC ARRAYS (GM Standard)
// Pros: O(1) allocation, cache-friendly, safer for recursion
// We only need one array.
// Step 1: It acts as the "Difference Array".
// Step 2: It becomes the "Final Grid" after prefix sum.
constexpr int MAXN = 1005; // Must be > N to handle r2+1 boundary safely
i64 grid[MAXN][MAXN];

void solve_static() {
    int n, m, q;
    if (!(cin >> n >> m >> q)) return;

    // Reset grid if running multiple test cases (important for global arrays!)
    // memset(grid, 0, sizeof(grid));

    // 1. Process Range Updates (O(1) per update)
    while (q--) {
        int r1, c1, r2, c2;
        i64 x;
        cin >> r1 >> c1 >> r2 >> c2 >> x;

        // Apply 2D Difference Array Formula
        grid[r1][c1]         += x; // Top-Left: Add x
        grid[r1][c2 + 1]     -= x; // Top-Right+1: Remove effect for future cols
        grid[r2 + 1][c1]     -= x; // Bottom-Left+1: Remove effect for future rows
        grid[r2 + 1][c2 + 1] += x; // Bottom-Right+1: Add back (subtracted twice)
    }

    // 2. Compute Prefix Sum In-Place (Transforms Diff Array -> Final Values)
    // Complexity: O(N * M)
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            grid[i][j] += grid[i - 1][j]
                        + grid[i][j - 1]
                        - grid[i - 1][j - 1];
        }
    }

    // 3. Print Final Grid
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << grid[i][j] << (j == m ? "" : " ");
        }
        cout << nl;
    }
}

// METHOD 2: VECTOR (Clean & Dynamic)
// Pros: No fixed size limits, isolated memory
void solve_vector() {
    int n, m, q;
    cin >> n >> m >> q;

    // Size is (n+2, m+2) to safely handle r2+1 and c2+1 indices without 'if' checks
    vector<vector<i64>> diff(n + 2, vector<i64>(m + 2, 0));

    // 1. Process Range Updates
    while (q--) {
        int r1, c1, r2, c2;
        i64 x;
        cin >> r1 >> c1 >> r2 >> c2 >> x;

        diff[r1][c1] += x;
        diff[r1][c2 + 1] -= x;
        diff[r2 + 1][c1] -= x;
        diff[r2 + 1][c2 + 1] += x;
    }

    // 2. Compute Prefix Sum (In-Place)
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            // Current cell = Difference value + Value from Top + Value from Left - Overlap
            diff[i][j] += diff[i - 1][j]
                        + diff[i][j - 1]
                        - diff[i - 1][j - 1];
        }
    }

    // 3. Print
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << diff[i][j] << (j == m ? "" : " ");
        }
        cout << nl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve_static(); // Recommended for CP
    // solve_vector();

    return 0;
}
/*
3 3 3
1 1 3 3 100                    0 50 50
1 1 1 3 -50     output -->     50 100 100
1 1 3 1 -50                    50 100 100
*/

/*
 * ==========================================
 * 2D DIFFERENCE ARRAY CHEATSHEET
 * ==========================================
 *
 * GOAL: Add value X to a subgrid (r1, c1) -> (r2, c2)
 *
 * LOGIC:
 * 1. MARKERS (Update Phase):
 * Imagine four corners.
 * (r1, c1)         -> +X  (Start adding X here)
 * (r1, c2+1)       -> -X  (Stop adding X horizontally after c2)
 * (r2+1, c1)       -> -X  (Stop adding X vertically after r2)
 * (r2+1, c2+1)     -> +X  (Correction: The -X was applied twice, so add X back)
 *
 * 2. SWEEP (Build Phase):
 * Run standard 2D Prefix Sum on the marker array.
 * The +X will "propagate" down and right until it hits a -X wall.
 *
 * FORMULA:
 * diff[i][j] += diff[i-1][j] + diff[i][j-1] - diff[i-1][j-1];
 */

