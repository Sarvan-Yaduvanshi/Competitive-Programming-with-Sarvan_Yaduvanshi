/*
╔══════════════════════════════════════════════════════════════════╗
║  02 — DIAMETER, PATH SUM & MAXIMUM PATH SUM                    ║
║  Zero to GM Level — Binary Tree Problems                         ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 PROBLEMS COVERED
═══════════════════════════════════════════════════════════════════
 1. Diameter of Binary Tree (LeetCode 543)
 2. Path Sum (LeetCode 112) — root-to-leaf exact sum
 3. Maximum Path Sum (LeetCode 124) — hardest, ICPC-level pattern

═══════════════════════════════════════════════════════════════════
 1. DIAMETER — DRY RUN
═══════════════════════════════════════════════════════════════════

 Diameter = longest path between ANY two nodes (in edges).
 Key idea: for each node, path through it = leftHeight + rightHeight.

 Tree:
           1
          / \
         2   3
        / \
       4   5

 dfs(4): return height=0 (leaf)
 dfs(5): return height=0
 dfs(2): left=0+1=1, right=0+1=1
         candidate diameter through 2 = 1+1 = 2
         return height = max(1,1) = 1
 dfs(3): return height=0
 dfs(1): left=1+1=2, right=0+1=1
         candidate diameter through 1 = 2+1 = 3 ✅ (longest!)
         return height = 2

 Diameter = 3 (path: 4→2→1→3)

═══════════════════════════════════════════════════════════════════
 2. PATH SUM — DRY RUN  (Does root-to-leaf path sum = target?)
═══════════════════════════════════════════════════════════════════

 Tree (values shown):
           5
          / \
         4   8
        /   / \
       11  13  4
      / \       \
     7   2       1

 Target = 22

 Path: 5 → 4 → 11 → 2 = 5+4+11+2 = 22 ✅ Found!

 DFS approach: subtract val at each node, check if leaf with sum=0.

 hasPathSum(5, 22):
   hasPathSum(4, 22-5=17):
     hasPathSum(11, 17-4=13):
       hasPathSum(7, 13-11=2):
         leaf, 2≠0 → false
       hasPathSum(2, 13-11=2):
         leaf, 2-2=0 → TRUE ✅
     return true
   return true

═══════════════════════════════════════════════════════════════════
 3. MAXIMUM PATH SUM — DRY RUN (LeetCode 124)
═══════════════════════════════════════════════════════════════════

 ⚠️ This is one of the HARDEST tree problems. Path can start and
    end at ANY node (not just root-to-leaf).

 Key insight: For each node v, the path through v uses:
   - v's value
   - optionally the best path going down-left
   - optionally the best path going down-right

 maxGain(v) = max path sum starting at v going DOWN (one direction)
            = v.val + max(0, max(maxGain(left), maxGain(right)))

 At each node: update global answer with:
   v.val + max(0, maxGain(left)) + max(0, maxGain(right))

 Tree:
          -10
          / \
         9   20
            / \
           15  7

 maxGain(9) = 9 (leaf)
 maxGain(15) = 15 (leaf)
 maxGain(7) = 7 (leaf)
 maxGain(20) = 20 + max(15, 7) = 35
   candidate at 20: 20 + 15 + 7 = 42 ✅
 maxGain(-10) = -10 + max(0, max(9, 35)) = -10 + 35 = 25
   candidate at -10: -10 + max(0,9) + max(0,35) = -10+9+35 = 34

 Answer = max(42, 34, 9, 15, 7, 20) = 42 ✅
 Path: 15 → 20 → 7

═══════════════════════════════════════════════════════════════════
 COMPLEXITY
═══════════════════════════════════════════════════════════════════

 ┌────────────────────────────┬────────────┬──────────────┐
 │ Problem                    │ Time       │ Space        │
 ├────────────────────────────┼────────────┼──────────────┤
 │ Diameter                   │ O(N)       │ O(H)         │
 │ Path Sum                   │ O(N)       │ O(H)         │
 │ Max Path Sum               │ O(N)       │ O(H)         │
 └────────────────────────────┴────────────┴──────────────┘

═══════════════════════════════════════════════════════════════════
 CODE
═══════════════════════════════════════════════════════════════════
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

vec<int> L, R, val;
int n;

// ═══════════════════════════════════════════════════════════
// 1. DIAMETER
// ═══════════════════════════════════════════════════════════
int diameterAns;

int heightForDiameter(int v) {
    if (v == 0) return 0;
    int lh = heightForDiameter(L[v]);
    int rh = heightForDiameter(R[v]);
    diameterAns = max(diameterAns, lh + rh); // path through v
    return 1 + max(lh, rh);
}

// ═══════════════════════════════════════════════════════════
// 2. PATH SUM (root-to-leaf)
// ═══════════════════════════════════════════════════════════
bool hasPathSum(int v, i64 target) {
    if (v == 0) return false;
    target -= val[v];
    // Check if leaf
    if (L[v] == 0 && R[v] == 0) return target == 0;
    return hasPathSum(L[v], target) || hasPathSum(R[v], target);
}

// ═══════════════════════════════════════════════════════════
// 3. MAXIMUM PATH SUM (any node to any node)
// ═══════════════════════════════════════════════════════════
i64 maxPathAns;

// Returns max sum path going DOWN from v (single direction)
i64 maxGain(int v) {
    if (v == 0) return 0;

    i64 leftGain = max(0LL, maxGain(L[v]));
    i64 rightGain = max(0LL, maxGain(R[v]));

    // Path through v (potentially using both sides)
    i64 pathThroughV = val[v] + leftGain + rightGain;
    maxPathAns = max(maxPathAns, pathThroughV);

    // Return best single-direction path from v
    return val[v] + max(leftGain, rightGain);
}

void solve() {
    cin >> n;
    L.assign(n + 1, 0);
    R.assign(n + 1, 0);
    val.assign(n + 1, 0);

    for (int i = 1; i <= n; i++) cin >> val[i];
    for (int i = 1; i <= n; i++) cin >> L[i] >> R[i];

    // 1. Diameter
    diameterAns = 0;
    heightForDiameter(1);
    cout << "Diameter (edges): " << diameterAns << nl;

    // 2. Path Sum
    i64 target;
    cin >> target;
    cout << "Has path sum " << target << ": "
         << (hasPathSum(1, target) ? "YES" : "NO") << nl;

    // 3. Max Path Sum
    maxPathAns = LLONG_MIN;
    maxGain(1);
    cout << "Max Path Sum: " << maxPathAns << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1;
    cin >> TC;
    while (TC--) solve();
    return 0;
}

/*
═══════════════════════════════════════════════════════════════════
 SAMPLE INPUT / OUTPUT
═══════════════════════════════════════════════════════════════════

Input:
1
5
1 2 3 4 5
2 3
4 5
0 0
0 0
0 0
7

Tree:     1
        /   \
       2     3
      / \
     4   5

val = [_, 1, 2, 3, 4, 5]

Output:
Diameter (edges): 3
Has path sum 7: YES
Max Path Sum: 11

(Max path: 4→2→5 = 4+2+5=11, or 4→2→1→3 = 4+2+1+3=10)

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Diameter: for each node, candidate = leftH + rightH
 ✅ Path Sum: DFS subtracting values, check leaf with sum=0
 ✅ Max Path Sum: maxGain returns best single-direction path
    Global answer considers path through node (both directions)
 ✅ max(0, gain) — if a subtree has negative sum, don't use it
 ✅ All O(N) time, O(H) space — single DFS pass each
═══════════════════════════════════════════════════════════════════
*/

