/*
╔══════════════════════════════════════════════════════════════════╗
║  02 — BST VALIDATION & PROPERTIES                               ║
║  Zero to GM Level — Binary Search Tree                           ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 VALIDATE BST — DRY RUN
═══════════════════════════════════════════════════════════════════

 Method: Pass valid range [lo, hi] to each node.
 Root must be in (-∞, +∞).
 Left child must be in (lo, root.val).
 Right child must be in (root.val, hi).

 Tree:         BST?
      5
     / \
    3   7
   / \ / \
  1  4 6  8

 validate(5, -∞, +∞): 5 in range ✅
   validate(3, -∞, 5): 3 in range ✅
     validate(1, -∞, 3): 1 in range ✅ (leaf)
     validate(4, 3, 5): 4 in range ✅ (leaf)
   validate(7, 5, +∞): 7 in range ✅
     validate(6, 5, 7): 6 in range ✅ (leaf)
     validate(8, 7, +∞): 8 in range ✅ (leaf)
 → VALID BST ✅

 Invalid example:
      5
     / \
    3   7
   / \
  1   6    ← 6 > 5 but in left subtree!

 validate(3, -∞, 5):
   validate(6, 3, 5): 6 > 5 ❌ NOT IN RANGE!
 → INVALID BST ❌

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
constexpr i64 MOD = 1'000'000'007LL;
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

vec<int> L, R, V;

// ═══════════════════════════════════════════════════════════
// METHOD 1: Range-based validation O(N)
// ═══════════════════════════════════════════════════════════
bool isValidBST(int v, i64 lo, i64 hi) {
    if (v == 0) return true;
    if (V[v] <= lo || V[v] >= hi) return false;
    return isValidBST(L[v], lo, (i64)V[v]) &&
           isValidBST(R[v], (i64)V[v], hi);
}

// ═══════════════════════════════════════════════════════════
// METHOD 2: Inorder check — must be strictly increasing
// ═══════════════════════════════════════════════════════════
i64 prevVal;
bool isValidInorder(int v) {
    if (v == 0) return true;
    if (!isValidInorder(L[v])) return false;
    if (V[v] <= prevVal) return false;
    prevVal = V[v];
    return isValidInorder(R[v]);
}

void solve() {
    int n;
    cin >> n;
    V.assign(n + 1, 0); L.assign(n + 1, 0); R.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> V[i];
    for (int i = 1; i <= n; i++) cin >> L[i] >> R[i];

    bool valid1 = isValidBST(1, LLONG_MIN, LLONG_MAX);
    prevVal = LLONG_MIN;
    bool valid2 = isValidInorder(1);

    cout << "Range method:   " << (valid1 ? "VALID BST" : "INVALID") << nl;
    cout << "Inorder method: " << (valid2 ? "VALID BST" : "INVALID") << nl;
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
 SAMPLE I/O
═══════════════════════════════════════════════════════════════════

Input (valid BST):
1
5
5 3 7 1 4
2 3
4 5
0 0
0 0
0 0

Output:
Range method:   VALID BST
Inorder method: VALID BST

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Range method: pass [lo, hi] bounds down the tree
 ✅ Inorder method: check that values are strictly increasing
 ✅ Use LLONG_MIN/LLONG_MAX for initial bounds (handle INT_MIN/MAX values)
 ✅ Both methods are O(N) time, O(H) space
═══════════════════════════════════════════════════════════════════
*/

