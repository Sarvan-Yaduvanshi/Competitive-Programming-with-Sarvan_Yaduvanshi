/*
╔══════════════════════════════════════════════════════════════════╗
║  03 — SAME TREE, SYMMETRIC TREE & SUBTREE CHECK                ║
║  Zero to GM Level — Binary Tree Problems                         ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 1. SAME TREE (LeetCode 100) — DRY RUN
═══════════════════════════════════════════════════════════════════

 Two trees are same if:
   - Both null → same
   - One null, other not → different
   - Both non-null → same value AND left subtrees same AND right same

 Tree A:       Tree B:
     1             1
    / \           / \
   2   3         2   3

 isSame(A1, B1): val match (1==1) ✅
   isSame(A2, B2): val match (2==2) ✅
     isSame(null, null) → true ✅
     isSame(null, null) → true ✅
   isSame(A3, B3): val match (3==3) ✅
 → TRUE

═══════════════════════════════════════════════════════════════════
 2. SYMMETRIC TREE (LeetCode 101) — DRY RUN
═══════════════════════════════════════════════════════════════════

 A tree is symmetric if it's a mirror of itself.
 Check: left subtree is mirror of right subtree.

 Symmetric:           NOT Symmetric:
      1                    1
     / \                  / \
    2   2                2   2
   / \ / \                \   \
  3  4 4  3                3   3

 isMirror(left=2, right=2):
   val match (2==2) ✅
   isMirror(left.left=3, right.right=3): vals match ✅, both leaves
   isMirror(left.right=4, right.left=4): vals match ✅, both leaves
 → TRUE ✅

 Key: Mirror means left.left matches right.right AND
      left.right matches right.left (CROSS comparison!)

═══════════════════════════════════════════════════════════════════
 3. SUBTREE CHECK (LeetCode 572) — DRY RUN
═══════════════════════════════════════════════════════════════════

 Is tree B a subtree of tree A?
 For each node in A, check if the subtree rooted there equals B.

 Tree A:         Tree B:
      3              4
     / \            / \
    4   5          1   2
   / \
  1   2

 At node 3: subtree(3) ≠ B
 At node 4: subtree(4) == B?
   isSame(4, 4)=true, isSame(1,1)=true, isSame(2,2)=true → YES ✅

 Time: O(N × M) worst case, where N=|A|, M=|B|

═══════════════════════════════════════════════════════════════════
 COMPLEXITY
═══════════════════════════════════════════════════════════════════

 ┌─────────────────────┬────────────┬──────────────┐
 │ Problem             │ Time       │ Space        │
 ├─────────────────────┼────────────┼──────────────┤
 │ Same Tree           │ O(N)       │ O(H)         │
 │ Symmetric Tree      │ O(N)       │ O(H)         │
 │ Subtree Check       │ O(N·M)     │ O(H)         │
 └─────────────────────┴────────────┴──────────────┘

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
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define pb push_back
#define fi first
#define se second
#define nl '\n'

vec<int> L1, R1, V1; // Tree A
vec<int> L2, R2, V2; // Tree B

// ═══════════════════════════════════════════════════════════
// 1. SAME TREE
// ═══════════════════════════════════════════════════════════
bool isSame(int a, vec<int>& la, vec<int>& ra, vec<int>& va,
            int b, vec<int>& lb, vec<int>& rb, vec<int>& vb) {
    if (a == 0 && b == 0) return true;
    if (a == 0 || b == 0) return false;
    if (va[a] != vb[b]) return false;
    return isSame(la[a], la, ra, va, lb[b], lb, rb, vb) &&
           isSame(ra[a], la, ra, va, rb[b], lb, rb, vb);
}

// ═══════════════════════════════════════════════════════════
// 2. SYMMETRIC TREE (check if tree is mirror of itself)
// ═══════════════════════════════════════════════════════════
bool isMirror(int a, int b, vec<int>& l, vec<int>& r, vec<int>& v) {
    if (a == 0 && b == 0) return true;
    if (a == 0 || b == 0) return false;
    if (v[a] != v[b]) return false;
    // CROSS: a's left with b's right, a's right with b's left
    return isMirror(l[a], r[b], l, r, v) && isMirror(r[a], l[b], l, r, v);
}

bool isSymmetric(int root, vec<int>& l, vec<int>& r, vec<int>& v) {
    if (root == 0) return true;
    return isMirror(l[root], r[root], l, r, v);
}

// ═══════════════════════════════════════════════════════════
// 3. SUBTREE CHECK
// ═══════════════════════════════════════════════════════════
bool isSubtree(int a, int bRoot) {
    if (a == 0) return bRoot == 0;
    if (isSame(a, L1, R1, V1, bRoot, L2, R2, V2)) return true;
    return isSubtree(L1[a], bRoot) || isSubtree(R1[a], bRoot);
}

void solve() {
    int n1;
    cin >> n1;
    V1.assign(n1 + 1, 0); L1.assign(n1 + 1, 0); R1.assign(n1 + 1, 0);
    for (int i = 1; i <= n1; i++) cin >> V1[i];
    for (int i = 1; i <= n1; i++) cin >> L1[i] >> R1[i];

    // Symmetric check
    cout << "Tree A is symmetric: " << (isSymmetric(1, L1, R1, V1) ? "YES" : "NO") << nl;

    int n2;
    cin >> n2;
    V2.assign(n2 + 1, 0); L2.assign(n2 + 1, 0); R2.assign(n2 + 1, 0);
    for (int i = 1; i <= n2; i++) cin >> V2[i];
    for (int i = 1; i <= n2; i++) cin >> L2[i] >> R2[i];

    // Same tree check (both trees)
    cout << "Same tree: " << (isSame(1, L1, R1, V1, 1, L2, R2, V2) ? "YES" : "NO") << nl;

    // Subtree check
    cout << "B is subtree of A: " << (isSubtree(1, 1) ? "YES" : "NO") << nl;
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

Input:
1
5
1 2 2 3 3
2 3
4 5
0 0
0 0
0 0
3
2 3 3
2 3
0 0
0 0

Output:
Tree A is symmetric: YES
Same tree: NO
B is subtree of A: YES

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Same tree: both null→true, compare val then recurse
 ✅ Symmetric: mirror check → CROSS compare (left.left ↔ right.right)
 ✅ Subtree: try isSame at every node of main tree → O(N·M)
 ✅ For O(N) subtree check: use tree hashing (Chapter 16)
═══════════════════════════════════════════════════════════════════
*/

