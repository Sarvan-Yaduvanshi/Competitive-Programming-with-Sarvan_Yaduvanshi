/*
╔══════════════════════════════════════════════════════════════════╗
║  03 — FENWICK TREE (BIT) AS TREE STRUCTURE                      ║
║  Zero to GM Level — Special Trees                                ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 CONCEPT: Fenwick Tree is a tree-shaped data structure
═══════════════════════════════════════════════════════════════════

 A Fenwick tree (Binary Indexed Tree, BIT) is actually a tree!
 Each index i is responsible for a RANGE of elements determined
 by the lowest set bit of i.

 i is responsible for range [i - lowbit(i) + 1, i]
 where lowbit(i) = i & (-i)

═══════════════════════════════════════════════════════════════════
 TREE STRUCTURE VISUALIZATION (N=8)
═══════════════════════════════════════════════════════════════════

 Index:  1    2    3    4    5    6    7    8
 Binary: 001  010  011  100  101  110  111  1000

 Parent of i = i + lowbit(i)  (for update traversal)
 i = i - lowbit(i) (for query traversal)

 Tree structure (parent relationship via update):
            8
          / | \
         4  6  7
        /|  |
       2 3  5
       |
       1

 BIT[1] covers a[1]
 BIT[2] covers a[1..2]
 BIT[3] covers a[3]
 BIT[4] covers a[1..4]
 BIT[5] covers a[5]
 BIT[6] covers a[5..6]
 BIT[7] covers a[7]
 BIT[8] covers a[1..8]

═══════════════════════════════════════════════════════════════════
 DRY RUN — Point Update + Prefix Query
═══════════════════════════════════════════════════════════════════

 Array: a = [_, 3, 1, 4, 1, 5, 9, 2, 6]
                1  2  3  4  5  6  7  8

 Initial BIT:
   BIT[1]=3, BIT[2]=3+1=4, BIT[3]=4, BIT[4]=3+1+4+1=9
   BIT[5]=5, BIT[6]=5+9=14, BIT[7]=2, BIT[8]=3+1+4+1+5+9+2+6=31

 Query prefix_sum(5):
   i=5: ans += BIT[5]=5,  i=5-lowbit(5)=5-1=4
   i=4: ans += BIT[4]=9,  i=4-lowbit(4)=4-4=0
   Answer = 5+9 = 14
   Verify: 3+1+4+1+5 = 14 ✅

 Update a[3] += 10:
   i=3: BIT[3]+=10, i=3+lowbit(3)=3+1=4
   i=4: BIT[4]+=10, i=4+lowbit(4)=4+4=8
   i=8: BIT[8]+=10, done.
   Updated: BIT[3]=14, BIT[4]=19, BIT[8]=41

═══════════════════════════════════════════════════════════════════
 OPERATIONS & COMPLEXITY
═══════════════════════════════════════════════════════════════════

 ┌──────────────────────────┬────────────────┬──────────────┐
 │ Operation                │ Time           │ Space        │
 ├──────────────────────────┼────────────────┼──────────────┤
 │ Point update             │ O(log N)       │ O(N)         │
 │ Prefix sum query         │ O(log N)       │ —            │
 │ Range sum [l, r]         │ O(log N)       │ —            │
 │ Build from array         │ O(N)           │ O(N)         │
 └──────────────────────────┴────────────────┴──────────────┘

 Why Fenwick over Segment Tree?
   ✅ Half the memory (N vs 4N)
   ✅ Smaller constant factor (faster in practice)
   ✅ Simpler code
   ❌ Less flexible (no lazy propagation, harder for non-invertible ops)

═══════════════════════════════════════════════════════════════════
 CODE — Complete Fenwick Tree
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
template<class T> using vec = vector<T>;
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

struct FenwickTree {
    int n;
    vec<i64> tree;

    FenwickTree(int n) : n(n), tree(n + 1, 0) {}

    // Build from array in O(N)
    FenwickTree(vec<i64>& a) : n(sz(a) - 1), tree(sz(a), 0) {
        for (int i = 1; i <= n; i++) {
            tree[i] += a[i];
            int j = i + (i & (-i));
            if (j <= n) tree[j] += tree[i];
        }
    }

    // Point update: a[i] += delta
    void update(int i, i64 delta) {
        for (; i <= n; i += i & (-i))
            tree[i] += delta;
    }

    // Prefix sum: a[1] + a[2] + ... + a[i]
    i64 query(int i) {
        i64 s = 0;
        for (; i > 0; i -= i & (-i))
            s += tree[i];
        return s;
    }

    // Range sum: a[l] + a[l+1] + ... + a[r]
    i64 query(int l, int r) {
        return query(r) - query(l - 1);
    }

    // Find smallest index with prefix sum >= target (binary search on BIT)
    // Works only if all values are non-negative
    int find(i64 target) {
        int pos = 0;
        int logn = 0;
        while ((1 << (logn + 1)) <= n) logn++;
        for (int pw = 1 << logn; pw > 0; pw >>= 1) {
            if (pos + pw <= n && tree[pos + pw] < target) {
                pos += pw;
                target -= tree[pos];
            }
        }
        return pos + 1;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;

    vec<i64> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    FenwickTree bit(a);

    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int i; i64 delta; cin >> i >> delta;
            bit.update(i, delta);
        } else {
            int l, r; cin >> l >> r;
            cout << bit.query(l, r) << nl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1; cin >> TC;
    while (TC--) solve();
    return 0;
}

/*
═══════════════════════════════════════════════════════════════════
 SAMPLE I/O
═══════════════════════════════════════════════════════════════════

Input:
1
8 4
3 1 4 1 5 9 2 6
2 1 5
1 3 10
2 1 5
2 3 7

Output:
14
24
30

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ BIT is actually a tree: parent of i = i + lowbit(i)
 ✅ O(log N) update and query, O(N) space
 ✅ Lighter than segment tree: less memory, faster constant
 ✅ Used extensively with Euler tour for subtree queries
 ✅ Binary search on BIT: find(target) in O(log N)
═══════════════════════════════════════════════════════════════════
*/

