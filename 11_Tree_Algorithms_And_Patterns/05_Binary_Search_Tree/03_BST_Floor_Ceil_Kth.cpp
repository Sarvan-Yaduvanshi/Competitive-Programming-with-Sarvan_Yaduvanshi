/*
╔══════════════════════════════════════════════════════════════════╗
║  03 — BST FLOOR, CEIL & KTH SMALLEST                           ║
║  Zero to GM Level — Binary Search Tree                           ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 FLOOR & CEIL — DRY RUN
═══════════════════════════════════════════════════════════════════

 FLOOR(x) = largest value ≤ x in BST
 CEIL(x)  = smallest value ≥ x in BST

 BST:
          8
        /   \
       3     10
      / \      \
     1   6     14

 Floor(7):
   At 8: 7 < 8, go left
   At 3: 7 > 3, candidate=3, go right
   At 6: 7 > 6, candidate=6, go right → null
   Floor = 6 ✅

 Ceil(5):
   At 8: 5 < 8, candidate=8, go left
   At 3: 5 > 3, go right
   At 6: 5 < 6, candidate=6, go left → null
   Ceil = 6 ✅

═══════════════════════════════════════════════════════════════════
 KTH SMALLEST — DRY RUN
═══════════════════════════════════════════════════════════════════

 BST inorder = sorted → Kth smallest = Kth element in inorder.

 BST: 1, 3, 6, 8, 10, 14  (inorder)
 K=3 → answer = 6

 Efficient: inorder traversal with counter, stop at K.

═══════════════════════════════════════════════════════════════════
 CODE (using adj-list tree, not pointer BST — CP style)
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

vec<int> L, R, V;

// ═══════════════════════════════════════════════════════════
// FLOOR — largest value ≤ key
// ═══════════════════════════════════════════════════════════
int bstFloor(int root, int key) {
    int ans = -1; // -1 means no floor exists
    int cur = root;
    while (cur != 0) {
        if (V[cur] == key) return V[cur];
        if (V[cur] < key) {
            ans = V[cur]; // candidate
            cur = R[cur]; // try to find larger
        } else {
            cur = L[cur]; // too big
        }
    }
    return ans;
}

// ═══════════════════════════════════════════════════════════
// CEIL — smallest value ≥ key
// ═══════════════════════════════════════════════════════════
int bstCeil(int root, int key) {
    int ans = -1;
    int cur = root;
    while (cur != 0) {
        if (V[cur] == key) return V[cur];
        if (V[cur] > key) {
            ans = V[cur]; // candidate
            cur = L[cur]; // try to find smaller
        } else {
            cur = R[cur]; // too small
        }
    }
    return ans;
}

// ═══════════════════════════════════════════════════════════
// KTH SMALLEST — inorder traversal with counter
// ═══════════════════════════════════════════════════════════
int kthResult, kthCount;

void kthSmallest(int root, int k) {
    if (root == 0 || kthCount >= k) return;
    kthSmallest(L[root], k);
    kthCount++;
    if (kthCount == k) { kthResult = V[root]; return; }
    kthSmallest(R[root], k);
}

void solve() {
    int n;
    cin >> n;
    V.assign(n + 1, 0); L.assign(n + 1, 0); R.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> V[i];
    for (int i = 1; i <= n; i++) cin >> L[i] >> R[i];

    int q;
    cin >> q;
    while (q--) {
        char op;
        int x;
        cin >> op >> x;
        if (op == 'F') {
            int f = bstFloor(1, x);
            cout << "Floor(" << x << ") = " << (f == -1 ? "NONE" : to_string(f)) << nl;
        } else if (op == 'C') {
            int c = bstCeil(1, x);
            cout << "Ceil(" << x << ") = " << (c == -1 ? "NONE" : to_string(c)) << nl;
        } else if (op == 'K') {
            kthCount = 0; kthResult = -1;
            kthSmallest(1, x);
            cout << "Kth smallest (K=" << x << ") = " << kthResult << nl;
        }
    }
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
6
8 3 10 1 6 14
2 3
4 5
0 6
0 0
0 0
0 0
5
F 7
F 2
C 5
C 15
K 3

Output:
Floor(7) = 6
Floor(2) = 1
Ceil(5) = 6
Ceil(15) = NONE
Kth smallest (K=3) = 6

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Floor: go right when < key (update candidate), left when > key
 ✅ Ceil: go left when > key (update candidate), right when < key
 ✅ Kth smallest: inorder traversal, count to K
 ✅ All O(H) time → O(log N) for balanced BST
 ✅ In CP: std::set::lower_bound = ceil, prev(lower_bound) = floor
═══════════════════════════════════════════════════════════════════
*/

