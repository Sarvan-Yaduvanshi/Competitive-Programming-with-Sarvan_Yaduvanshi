/*
╔══════════════════════════════════════════════════════════════════════╗
║              🏆 MASTER RECURSION TEMPLATES — CHEAT SHEET 🏆         ║
║              All Patterns in One File (Quick Reference)              ║
║              By Sarvan Yaduvanshi                                    ║
╚══════════════════════════════════════════════════════════════════════╝

Copy-paste these templates during contests!
All templates use your competitive programming template as base.
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
#include <functional>

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

inline i64 gcd(i64 a, i64 b) { return std::gcd(a, b); }
inline i64 lcm(i64 a, i64 b) { return (a / std::gcd(a, b)) * b; }

inline i64 modpow(i64 base, i64 exp, i64 mod = MOD) {
    i64 res = 1; base %= mod;
    while (exp > 0) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}


/*
═══════════════════════════════════════════════════════════════════
🔷 TEMPLATE 1: TAKE / NOT-TAKE (Subsequences, Subsets)
═══════════════════════════════════════════════════════════════════
USE WHEN: Generate/count all subsets or subsequences
TIME: O(2^n)
*/
// Print all subsequences
void takeNotTake(vec<int>& arr, int idx, vec<int>& cur, vec<vec<int>>& result) {
    if (idx == sz(arr)) {
        result.pb(cur);  // Process current subset `cur`
        return;
    }
    // TAKE
    cur.pb(arr[idx]);
    takeNotTake(arr, idx + 1, cur, result);
    cur.pop_back();  // Backtrack
    // NOT TAKE
    takeNotTake(arr, idx + 1, cur, result);
}

// Count subsequences with property
int countSubseq(vec<int>& arr, int idx, int state, int target) {
    if (idx == sz(arr)) return (state == target) ? 1 : 0;
    int take = countSubseq(arr, idx + 1, state + arr[idx], target);
    int notTake = countSubseq(arr, idx + 1, state, target);
    return take + notTake;
}


/*
═══════════════════════════════════════════════════════════════════
🔷 TEMPLATE 2: COMBINATION SUM (with/without reuse, with/without dups)
═══════════════════════════════════════════════════════════════════
USE WHEN: Find combinations that sum to target
*/
// With reuse (stay at same index)
void combSum(vec<int>& arr, int idx, int target, vec<int>& cur, vec<vec<int>>& res) {
    if (target == 0) { res.pb(cur); return; }
    if (idx == sz(arr) || target < 0) return;

    cur.pb(arr[idx]);
    combSum(arr, idx, target - arr[idx], cur, res);  // Stay (reuse)
    cur.pop_back();
    combSum(arr, idx + 1, target, cur, res);          // Skip
}

// Without reuse, with duplicate handling (SORT FIRST!)
void combSum2(vec<int>& arr, int start, int target, vec<int>& cur, vec<vec<int>>& res) {
    if (target == 0) { res.pb(cur); return; }
    for (int i = start; i < sz(arr); i++) {
        if (i > start && arr[i] == arr[i-1]) continue;  // Skip dups
        if (arr[i] > target) break;                       // Prune
        cur.pb(arr[i]);
        combSum2(arr, i + 1, target - arr[i], cur, res);
        cur.pop_back();
    }
}


/*
═══════════════════════════════════════════════════════════════════
🔷 TEMPLATE 3: PERMUTATIONS (with/without duplicates)
═══════════════════════════════════════════════════════════════════
USE WHEN: Generate all orderings
TIME: O(n!)
*/
// Swap-based permutation (distinct elements)
void permute(vec<int>& arr, int idx, vec<vec<int>>& res) {
    if (idx == sz(arr)) { res.pb(arr); return; }
    for (int i = idx; i < sz(arr); i++) {
        swap(arr[idx], arr[i]);
        permute(arr, idx + 1, res);
        swap(arr[idx], arr[i]);
    }
}

// With duplicates (SORT + visited array)
void permuteUniq(vec<int>& arr, vec<bool>& vis, vec<int>& cur, vec<vec<int>>& res) {
    if (sz(cur) == sz(arr)) { res.pb(cur); return; }
    for (int i = 0; i < sz(arr); i++) {
        if (vis[i]) continue;
        if (i > 0 && arr[i] == arr[i-1] && !vis[i-1]) continue;
        vis[i] = true; cur.pb(arr[i]);
        permuteUniq(arr, vis, cur, res);
        cur.pop_back(); vis[i] = false;
    }
}


/*
═══════════════════════════════════════════════════════════════════
🔷 TEMPLATE 4: GRID BACKTRACKING (Rat in Maze, Word Search)
═══════════════════════════════════════════════════════════════════
USE WHEN: Find paths in 2D grid
*/
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void gridDFS(vvec<int>& grid, int r, int c, int rows, int cols,
             vvec<bool>& visited) {
    if (r == rows - 1 && c == cols - 1) { /* found path */ return; }

    for (int d = 0; d < 4; d++) {
        int nr = r + dx[d], nc = c + dy[d];
        if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
        if (grid[nr][nc] == 0 || visited[nr][nc]) continue;

        visited[nr][nc] = true;
        gridDFS(grid, nr, nc, rows, cols, visited);
        visited[nr][nc] = false;  // Backtrack
    }
}


/*
═══════════════════════════════════════════════════════════════════
🔷 TEMPLATE 5: N-QUEENS (Constraint satisfaction)
═══════════════════════════════════════════════════════════════════
*/
void nQueens(int n, int row, vec<bool>& col, vec<bool>& d1, vec<bool>& d2,
             vec<string>& board, vec<vec<string>>& res) {
    if (row == n) { res.pb(board); return; }
    for (int c = 0; c < n; c++) {
        if (col[c] || d1[row-c+n-1] || d2[row+c]) continue;
        board[row][c] = 'Q';
        col[c] = d1[row-c+n-1] = d2[row+c] = true;
        nQueens(n, row + 1, col, d1, d2, board, res);
        board[row][c] = '.';
        col[c] = d1[row-c+n-1] = d2[row+c] = false;
    }
}


/*
═══════════════════════════════════════════════════════════════════
🔷 TEMPLATE 6: MEMOIZATION (Top-Down DP)
═══════════════════════════════════════════════════════════════════
USE WHEN: Overlapping subproblems
Converts O(2^n) → O(n * states)
*/
// Using lambda + function<> (modern C++ style)
// Example: Knapsack
i64 knapsackTemplate(vec<int>& wt, vec<int>& val, int W) {
    int n = sz(wt);
    vvec<i64> dp(n + 1, vec<i64>(W + 1, -1));

    function<i64(int, int)> solve = [&](int i, int w) -> i64 {
        if (i == n || w == 0) return 0;
        if (dp[i][w] != -1) return dp[i][w];

        i64 skip = solve(i + 1, w);
        i64 take = (wt[i] <= w) ? val[i] + solve(i + 1, w - wt[i]) : 0;

        return dp[i][w] = max(take, skip);
    };

    return solve(0, W);
}


/*
═══════════════════════════════════════════════════════════════════
🔷 TEMPLATE 7: BITMASK DP
═══════════════════════════════════════════════════════════════════
USE WHEN: n ≤ 20, need to track subset state
TIME: O(n * 2^n) or O(n^2 * 2^n)
*/
// TSP template
i64 bitmaskDP(vvec<int>& cost, int n) {
    vvec<i64> dp(1 << n, vec<i64>(n, -1));

    function<i64(int, int)> solve = [&](int mask, int u) -> i64 {
        if (mask == (1 << n) - 1) return cost[u][0];  // Return to start
        if (dp[mask][u] != -1) return dp[mask][u];

        i64 res = INF64;
        for (int v = 0; v < n; v++) {
            if ((mask >> v) & 1) continue;
            res = min(res, cost[u][v] + solve(mask | (1 << v), v));
        }
        return dp[mask][u] = res;
    };

    return solve(1, 0);
}


/*
═══════════════════════════════════════════════════════════════════
🔷 TEMPLATE 8: DIGIT DP
═══════════════════════════════════════════════════════════════════
USE WHEN: Count numbers in [L, R] with digit property
*/
i64 digitDP(string& num, int targetState) {
    int len = sz(num);
    // dp[pos][tight][state]
    map<tuple<int,bool,int>, i64> dp;

    function<i64(int, bool, int)> solve = [&](int pos, bool tight, int state) -> i64 {
        if (pos == len) return (state == targetState) ? 1 : 0;

        auto key = make_tuple(pos, tight, state);
        if (dp.count(key)) return dp[key];

        int limit = tight ? (num[pos] - '0') : 9;
        i64 res = 0;
        for (int d = 0; d <= limit; d++) {
            res += solve(pos + 1, tight && (d == limit), state + d);
        }
        return dp[key] = res;
    };

    return solve(0, true, 0);
}


/*
═══════════════════════════════════════════════════════════════════
🔷 TEMPLATE 9: MEET IN THE MIDDLE
═══════════════════════════════════════════════════════════════════
USE WHEN: n ≤ 40, need 2^n subsets
CONVERTS: O(2^n) → O(2^(n/2) * log)
*/
i64 meetMiddle(vec<i64>& arr, i64 target) {
    int n = sz(arr), half = n / 2;

    // Generate left half subsets
    vec<i64> left;
    for (int mask = 0; mask < (1 << half); mask++) {
        i64 sum = 0;
        for (int i = 0; i < half; i++)
            if ((mask >> i) & 1) sum += arr[i];
        left.pb(sum);
    }

    // Generate right half subsets
    vec<i64> right;
    for (int mask = 0; mask < (1 << (n - half)); mask++) {
        i64 sum = 0;
        for (int i = 0; i < n - half; i++)
            if ((mask >> i) & 1) sum += arr[half + i];
        right.pb(sum);
    }

    sort(all(right));

    i64 count = 0;
    for (i64 ls : left) {
        i64 need = target - ls;
        count += upper_bound(all(right), need) - lower_bound(all(right), need);
    }
    return count;
}


/*
═══════════════════════════════════════════════════════════════════
🔷 TEMPLATE 10: TREE DFS + REROOTING
═══════════════════════════════════════════════════════════════════
USE WHEN: Compute answer for EVERY node as root, in O(n)
*/
void treeDFS(int u, int parent, vvec<int>& adj, vec<i64>& dp) {
    dp[u] = 1;  // Base (leaf)
    for (int v : adj[u]) {
        if (v == parent) continue;
        treeDFS(v, u, adj, dp);
        dp[u] += dp[v];  // Combine child result
    }
}

void reroot(int u, int parent, vvec<int>& adj, vec<i64>& dp, vec<i64>& ans, int n) {
    for (int v : adj[u]) {
        if (v == parent) continue;
        // Transition: move root from u to v
        ans[v] = ans[u] - dp[v] + (n - dp[v]);
        reroot(v, u, adj, dp, ans, n);
    }
}


/*
═══════════════════════════════════════════════════════════════════
🔷 TEMPLATE 11: SPRAGUE-GRUNDY (Game Theory)
═══════════════════════════════════════════════════════════════════
*/
int grundyTemplate(int state, vec<int>& memo, vec<int>& moves) {
    if (state == 0) return 0;
    if (memo[state] != -1) return memo[state];

    set<int> reachable;
    for (int move : moves) {
        if (move <= state) {
            reachable.insert(grundyTemplate(state - move, memo, moves));
        }
    }

    // MEX
    int g = 0;
    while (reachable.count(g)) g++;
    return memo[state] = g;
}

// Combined game: XOR of Grundy numbers
// xorSum > 0 → First player wins


/*
═══════════════════════════════════════════════════════════════════
🔷 TEMPLATE 12: SOS DP (Sum Over Subsets)
═══════════════════════════════════════════════════════════════════
F[mask] = sum of f[sub] for all sub ⊆ mask
TIME: O(n * 2^n)
*/
vec<i64> sosDPTemplate(vec<i64>& f, int n) {
    vec<i64> dp = f;
    for (int i = 0; i < n; i++)
        for (int mask = 0; mask < (1 << n); mask++)
            if ((mask >> i) & 1)
                dp[mask] += dp[mask ^ (1 << i)];
    return dp;
}


/*
═══════════════════════════════════════════════════════════════════
🔷 TEMPLATE 13: RECURSIVE SEGMENT TREE
═══════════════════════════════════════════════════════════════════
*/
struct SegTree {
    int n;
    vec<i64> tree;

    void build(vec<int>& a, int nd, int s, int e) {
        if (s == e) { tree[nd] = a[s]; return; }
        int m = (s + e) / 2;
        build(a, 2*nd, s, m); build(a, 2*nd+1, m+1, e);
        tree[nd] = tree[2*nd] + tree[2*nd+1];
    }

    void update(int nd, int s, int e, int i, int v) {
        if (s == e) { tree[nd] = v; return; }
        int m = (s + e) / 2;
        if (i <= m) update(2*nd, s, m, i, v);
        else update(2*nd+1, m+1, e, i, v);
        tree[nd] = tree[2*nd] + tree[2*nd+1];
    }

    i64 query(int nd, int s, int e, int l, int r) {
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) return tree[nd];
        int m = (s + e) / 2;
        return query(2*nd, s, m, l, r) + query(2*nd+1, m+1, e, l, r);
    }

    void init(vec<int>& a) { n = sz(a); tree.assign(4*n, 0); build(a, 1, 0, n-1); }
    void upd(int i, int v) { update(1, 0, n-1, i, v); }
    i64 qry(int l, int r) { return query(1, 0, n-1, l, r); }
};


// ═══════════════════════════════════════════════════════════
// This file is a TEMPLATE REFERENCE — no main() test needed.
// Copy what you need into your solve() function!
// ═══════════════════════════════════════════════════════════

void solve() {
    // Your solution here using templates above
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

