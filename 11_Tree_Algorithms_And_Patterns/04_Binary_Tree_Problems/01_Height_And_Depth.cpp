/*
╔══════════════════════════════════════════════════════════════════╗
║       01 — HEIGHT, DEPTH & BALANCED TREE CHECK                  ║
║       Zero to GM Level — Binary Tree Problems                    ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 PROBLEMS COVERED
═══════════════════════════════════════════════════════════════════

 1. Maximum Depth (LeetCode 104)
 2. Minimum Depth (LeetCode 111)
 3. Check Balanced Tree (LeetCode 110)

═══════════════════════════════════════════════════════════════════
 1. MAXIMUM DEPTH — DRY RUN
═══════════════════════════════════════════════════════════════════

 Tree:
         1
        / \
       2   3
      / \
     4   5
    /
   6

 maxDepth(1):
   maxDepth(2):
     maxDepth(4):
       maxDepth(6):
         maxDepth(null)=0, maxDepth(null)=0 → return 1
       maxDepth(null)=0 → return max(1,0)+1 = 2
     maxDepth(5):
       return 1 (leaf)
     return max(2,1)+1 = 3
   maxDepth(3):
     return 1 (leaf)
   return max(3,1)+1 = 4

 maxDepth = 4 ✅ (path: 1→2→4→6, 3 edges but we count nodes=4
                   or edges=3 depending on convention)

═══════════════════════════════════════════════════════════════════
 2. MINIMUM DEPTH — DRY RUN
═══════════════════════════════════════════════════════════════════

 ⚠️ TRICKY: minDepth is the shortest path to a LEAF.
    A node with only one child is NOT a leaf!

 Tree:
         1
        /
       2
      /
     3

 WRONG answer: minDepth(1) = 1 (right subtree is null, depth=0)
 CORRECT: minDepth = 3 (path 1→2→3, the only leaf is 3)

 Rule: If one child is null, take depth of the other child + 1.

═══════════════════════════════════════════════════════════════════
 3. BALANCED TREE CHECK — DRY RUN
═══════════════════════════════════════════════════════════════════

 Balanced ⟺ for EVERY node, |height(left) - height(right)| ≤ 1

 Tree:
         1
        / \
       2   3
      / \
     4   5
    /
   6

 height(6) = 0
 height(4) = 1, height(5) = 0
 At node 2: |height(left=4)=1 - height(right=5)=0| = 1 ≤ 1 ✅
 At node 1: |height(left=2)=2 - height(right=3)=0| = 2 > 1 ❌
 NOT balanced!

 Efficient approach: single DFS, return -1 if unbalanced.

═══════════════════════════════════════════════════════════════════
 COMPLEXITY
═══════════════════════════════════════════════════════════════════

 ┌────────────────────────────┬────────────┬──────────────┐
 │ Problem                    │ Time       │ Space        │
 ├────────────────────────────┼────────────┼──────────────┤
 │ Max Depth                  │ O(N)       │ O(H)         │
 │ Min Depth                  │ O(N)       │ O(H)         │
 │ Balanced Check (optimized) │ O(N)       │ O(H)         │
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
void read(vec<T> &v) {
    for (auto &x : v) cin >> x;
}
#define nl '\n'
#define YES cout << "YES" << nl
#define NO cout << "NO" << nl

vec<int> L, R; // left[i], right[i] children (0 = null)

// ═══════════════════════════════════════════════════════════
// MAXIMUM DEPTH
// ═══════════════════════════════════════════════════════════
int maxDepth(int v) {
    if (v == 0) return 0;
    return 1 + max(maxDepth(L[v]), maxDepth(R[v]));
}

// ═══════════════════════════════════════════════════════════
// MINIMUM DEPTH (careful: path must end at LEAF!)
// ═══════════════════════════════════════════════════════════
int minDepth(int v) {
    if (v == 0) return 0;
    int left = minDepth(L[v]);
    int right = minDepth(R[v]);

    // If one child is missing, take the other side
    if (L[v] == 0) return 1 + right;
    if (R[v] == 0) return 1 + left;

    return 1 + min(left, right);
}

// ═══════════════════════════════════════════════════════════
// BALANCED CHECK (O(N) — return -1 if unbalanced)
// ═══════════════════════════════════════════════════════════
int checkBalanced(int v) {
    if (v == 0) return 0;

    int leftH = checkBalanced(L[v]);
    if (leftH == -1) return -1;  // left subtree already unbalanced

    int rightH = checkBalanced(R[v]);
    if (rightH == -1) return -1;

    if (abs(leftH - rightH) > 1) return -1;  // current node unbalanced

    return 1 + max(leftH, rightH);
}

void solve() {
    int n;
    cin >> n;
    L.assign(n + 1, 0);
    R.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> L[i] >> R[i];
    }

    cout << "Max Depth: " << maxDepth(1) << nl;
    cout << "Min Depth: " << minDepth(1) << nl;
    cout << "Balanced: " << (checkBalanced(1) != -1 ? "YES" : "NO") << nl;
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
7
2 3
4 5
6 7
0 0
0 0
0 0
0 0

Tree:     1
        /   \
       2     3
      / \   / \
     4   5 6   7

Output:
Max Depth: 3
Min Depth: 3
Balanced: YES
═══════════════════════════════════════════════════════════════════
*/

