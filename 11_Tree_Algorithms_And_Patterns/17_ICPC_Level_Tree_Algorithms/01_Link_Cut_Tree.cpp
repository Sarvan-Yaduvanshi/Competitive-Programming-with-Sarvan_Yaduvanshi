/*
╔══════════════════════════════════════════════════════════════════╗
║  01 — LINK-CUT TREE (Dynamic Trees)                            ║
║  Zero to GM Level — ICPC Level Tree Algorithms                   ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 WHAT IS A LINK-CUT TREE?
═══════════════════════════════════════════════════════════════════

 A data structure for maintaining a DYNAMIC forest:
   link(u, v):  Add edge between u and v  → O(log N) amortized
   cut(u, v):   Remove edge between u and v → O(log N) amortized
   findRoot(v): Find root of tree containing v → O(log N)
   pathQuery(u,v): Query/update path from u to v → O(log N)

 This is the most advanced tree data structure in competitive
 programming. Used in World Finals and Div1 E/F problems.

═══════════════════════════════════════════════════════════════════
 HOW IT WORKS (HIGH LEVEL)
═══════════════════════════════════════════════════════════════════

 The tree is decomposed into "preferred paths" (like HLD chains).
 Each preferred path is stored in a SPLAY TREE.

 The key operation is ACCESS(v): make the path from v to root
 all "preferred," restructuring the splay trees.

 After access(v), the path root→v is one splay tree, and
 we can do operations on it efficiently.

═══════════════════════════════════════════════════════════════════
 SPLAY TREE BASICS
═══════════════════════════════════════════════════════════════════

 Splay tree: self-adjusting BST. After accessing a node,
 "splay" it to the root using rotations.

 Three cases:
   Zig: single rotation (parent is root)
   Zig-Zig: same direction rotations
   Zig-Zag: opposite direction rotations

═══════════════════════════════════════════════════════════════════
 COMPLETE LINK-CUT TREE IMPLEMENTATION
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

struct LinkCutTree {
    struct Node {
        int ch[2] = {0, 0}, p = 0;
        bool rev = false;
        int val = 0, pathVal = 0; // for path aggregates
        // Add more aggregate fields as needed
    };

    vec<Node> t;

    LinkCutTree(int n) : t(n + 1) {}

    void push(int x) {
        if (x && t[x].rev) {
            swap(t[x].ch[0], t[x].ch[1]);
            if (t[x].ch[0]) t[t[x].ch[0]].rev ^= 1;
            if (t[x].ch[1]) t[t[x].ch[1]].rev ^= 1;
            t[x].rev = false;
        }
    }

    void pull(int x) {
        t[x].pathVal = t[x].val;
        if (t[x].ch[0]) t[x].pathVal = max(t[x].pathVal, t[t[x].ch[0]].pathVal);
        if (t[x].ch[1]) t[x].pathVal = max(t[x].pathVal, t[t[x].ch[1]].pathVal);
    }

    bool isRoot(int x) {
        return t[t[x].p].ch[0] != x && t[t[x].p].ch[1] != x;
    }

    void rotate(int x) {
        int y = t[x].p, z = t[y].p;
        int d = (t[y].ch[1] == x), e = (t[z].ch[1] == y);
        if (!isRoot(y)) t[z].ch[e] = x;
        t[x].p = z;
        t[y].ch[d] = t[x].ch[d ^ 1];
        if (t[x].ch[d ^ 1]) t[t[x].ch[d ^ 1]].p = y;
        t[x].ch[d ^ 1] = y;
        t[y].p = x;
        pull(y);
        pull(x);
    }

    void splay(int x) {
        // Push down from root of splay tree to x
        static int stk[200005];
        int top = 0;
        stk[top++] = x;
        for (int i = x; !isRoot(i); i = t[i].p) stk[top++] = t[i].p;
        while (top) push(stk[--top]);

        while (!isRoot(x)) {
            int y = t[x].p, z = t[y].p;
            if (!isRoot(y)) {
                if ((t[z].ch[0] == y) == (t[y].ch[0] == x))
                    rotate(y); // zig-zig
                else
                    rotate(x); // zig-zag
            }
            rotate(x); // zig
        }
    }

    // Make path from x to root "preferred"
    void access(int x) {
        int last = 0;
        for (int y = x; y; y = t[y].p) {
            splay(y);
            t[y].ch[1] = last;
            pull(y);
            last = y;
        }
        splay(x);
    }

    void makeRoot(int x) {
        access(x);
        t[x].rev ^= 1;
        push(x);
    }

    int findRoot(int x) {
        access(x);
        while (t[x].ch[0]) {
            push(x);
            x = t[x].ch[0];
        }
        splay(x);
        return x;
    }

    void link(int x, int y) {
        makeRoot(x);
        if (findRoot(y) == x) return; // already connected
        t[x].p = y;
    }

    void cut(int x, int y) {
        makeRoot(x);
        access(y);
        if (t[y].ch[0] == x && !t[x].ch[1]) {
            t[y].ch[0] = t[x].p = 0;
            pull(y);
        }
    }

    bool connected(int x, int y) {
        return findRoot(x) == findRoot(y);
    }

    // Path query (max on path x→y)
    int pathMax(int x, int y) {
        makeRoot(x);
        access(y);
        return t[y].pathVal;
    }

    void setVal(int x, int v) {
        access(x);
        t[x].val = v;
        pull(x);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;

    LinkCutTree lct(n);
    for (int i = 1; i <= n; i++) {
        cin >> lct.t[i].val;
        lct.t[i].pathVal = lct.t[i].val;
    }

    while (q--) {
        string op; int u, v;
        cin >> op >> u >> v;

        if (op == "link") {
            lct.link(u, v);
            cout << "Linked " << u << " and " << v << nl;
        } else if (op == "cut") {
            lct.cut(u, v);
            cout << "Cut " << u << " and " << v << nl;
        } else if (op == "connected") {
            cout << u << " and " << v << ": "
                 << (lct.connected(u, v) ? "CONNECTED" : "DISCONNECTED") << nl;
        } else if (op == "max") {
            if (lct.connected(u, v)) {
                cout << "Max on path(" << u << "," << v << ") = "
                     << lct.pathMax(u, v) << nl;
            } else {
                cout << "Not connected" << nl;
            }
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
5 6
3 1 4 1 5
link 1 2
link 2 3
connected 1 3
max 1 3
cut 1 2
connected 1 3

Output:
Linked 1 and 2
Linked 2 and 3
1 and 3: CONNECTED
Max on path(1,3) = 4
Cut 1 and 2
1 and 3: DISCONNECTED

═══════════════════════════════════════════════════════════════════
 COMPLEXITY
═══════════════════════════════════════════════════════════════════

 All operations: O(log N) AMORTIZED (splay tree guarantee)

 ┌────────────────────────┬──────────────────┐
 │ Operation              │ Time (amortized) │
 ├────────────────────────┼──────────────────┤
 │ access(v)              │ O(log N)         │
 │ link(u, v)             │ O(log N)         │
 │ cut(u, v)              │ O(log N)         │
 │ findRoot(v)            │ O(log N)         │
 │ connected(u, v)        │ O(log N)         │
 │ pathQuery(u, v)        │ O(log N)         │
 └────────────────────────┴──────────────────┘

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Link-Cut Tree: dynamic forest with link/cut/path operations
 ✅ Based on splay trees maintaining preferred paths
 ✅ access(x) = key operation, makes root-to-x path preferred
 ✅ makeRoot(x) + access(y) → path x-to-y as one splay tree
 ✅ O(log N) amortized per operation
 ✅ Used in: dynamic connectivity, max flow, online LCA
═══════════════════════════════════════════════════════════════════
*/

