/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║        LEVEL 11 — SEGMENT TREE ON TREES (Euler Tour + HLD)                     ║
║        Subtree Queries, Path Queries, Heavy-Light Decomposition                ║
║        Author: Sarvan Yaduvanshi                                               ║
╚══════════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Euler Tour Technique — Flatten Tree to Array
 2. Subtree Queries (Sum/Min/Max on Subtree)
 3. Path Queries on Trees
 4. Heavy-Light Decomposition (HLD) — The Master Technique
 5. HLD + Segment Tree — Path Queries with Updates
 6. LCA with Sparse Table / Binary Lifting
 7. Complete Dry Runs

═══════════════════════════════════════════════════════════════
SECTION 1: EULER TOUR TECHNIQUE
═══════════════════════════════════════════════════════════════

The Euler Tour "flattens" a tree into an array such that
every SUBTREE becomes a CONTIGUOUS RANGE.

ALGORITHM: Do DFS, record entry time (tin) and exit time (tout).
  Subtree of node u = indices [tin[u], tout[u]]

EXAMPLE TREE:
          1
        / | \
       2  3  4
      / \    |
     5   6   7

DFS order: 1 → 2 → 5 → 6 → 3 → 4 → 7

  Node:  1  2  5  6  3  4  7
  tin:   0  1  2  3  4  5  6
  tout:  6  3  2  3  4  6  6

  Euler tour array (by tin order):
  Index: 0  1  2  3  4  5  6
  Node:  1  2  5  6  3  4  7
  Value: v1 v2 v5 v6 v3 v4 v7

  Subtree(1) = [0, 6] = entire array ✓
  Subtree(2) = [1, 3] = {2, 5, 6} ✓
  Subtree(4) = [5, 6] = {4, 7} ✓
  Subtree(5) = [2, 2] = {5} ✓ (leaf)

Now we can use ANY range query structure on the Euler tour array!
  Sum of subtree(2) = range_sum(1, 3) on flat array.

═══════════════════════════════════════════════════════════════
SECTION 4: HEAVY-LIGHT DECOMPOSITION (HLD)
═══════════════════════════════════════════════════════════════

HLD decomposes a tree into CHAINS such that any root-to-leaf
path crosses at most O(log n) chains.

DEFINITIONS:
  • Heavy child of u = child with largest subtree
  • Heavy edge = edge to heavy child
  • Light edge = edge to non-heavy children
  • Heavy chain = maximal path of heavy edges

PROPERTY: Any path from root to leaf crosses ≤ O(log n) chains.
PROOF: Each light edge at least halves the subtree size.

EXAMPLE TREE (with subtree sizes):
          1 (7)
        / | \
       2  3  4
      (3) (1)(3)
      / \    |
     5   6   7
    (1) (1)  (1)

  Heavy children: 1→2 or 4 (tie, pick 2), 2→5 or 6 (tie, pick 5), 4→7
  Heavy chains: [1, 2, 5], [4, 7], [3], [6]

  Flatten using HLD ordering:
  Chain 1: 1, 2, 5
  Chain 2: 6
  Chain 3: 3
  Chain 4: 4, 7

  Flat array position:
  Node: 1  2  5  6  3  4  7
  Pos:  0  1  2  3  4  5  6

  Each chain is a contiguous range → use segment tree on flat array!

PATH QUERY (u → v):
  1. Find LCA of u and v.
  2. Decompose path into O(log n) chain segments.
  3. For each segment, do range query on segment tree.

VISUALIZATION of path query (5 → 7):
  Path: 5 → 2 → 1 → 4 → 7

  Chains used:
    Chain [1,2,5]: segment [2→0] (reversed, from 5 up to 1)
    Chain [4,7]: segment [5→6] (from 4 down to 7)

  ST queries: query(0, 2) and query(5, 6)
  Combine results = answer for path!

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

// --- Macros ---
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define nl '\n'

// ═══════════════════════════════════════════════════════════════
// IMPLEMENTATION 1: Euler Tour + BIT for Subtree Queries
// ═══════════════════════════════════════════════════════════════

class EulerTourTree {
    int n, timer;
    vector<vector<int>> adj;
    vector<int> tin, tout, euler; // entry/exit times, euler tour order
    vector<long long> bit;       // BIT on euler tour

    void dfs(int u, int parent) {
        tin[u] = timer;
        euler[timer++] = u;
        for (int v : adj[u]) {
            if (v != parent) dfs(v, u);
        }
        tout[u] = timer - 1;
    }

    void bitUpdate(int i, long long delta) {
        for (i++; i <= n; i += i & (-i)) bit[i] += delta;
    }

    long long bitQuery(int i) {
        long long sum = 0;
        for (i++; i > 0; i -= i & (-i)) sum += bit[i];
        return sum;
    }

public:
    EulerTourTree(int n) : n(n), timer(0), adj(n), tin(n), tout(n), euler(n), bit(n + 1, 0) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void build(int root, const vector<long long>& values) {
        dfs(root, -1);
        for (int i = 0; i < n; i++) {
            bitUpdate(tin[i], values[i]);
        }
    }

    // Update value of node u
    void updateNode(int u, long long oldVal, long long newVal) {
        bitUpdate(tin[u], newVal - oldVal);
    }

    // Sum of values in subtree of u
    long long subtreeSum(int u) {
        return bitQuery(tout[u]) - (tin[u] > 0 ? bitQuery(tin[u] - 1) : 0);
    }

    void printEulerTour() {
        cout << "  Euler tour order: ";
        for (int i = 0; i < n; i++) cout << euler[i] << " ";
        cout << "\n";
        cout << "  tin:  ";
        for (int i = 0; i < n; i++) cout << i << "→" << tin[i] << " ";
        cout << "\n";
        cout << "  tout: ";
        for (int i = 0; i < n; i++) cout << i << "→" << tout[i] << " ";
        cout << "\n";
    }
};

void demoEulerTour() {
    cout << "═══ EULER TOUR + BIT FOR SUBTREE QUERIES ═══\n\n";

    /*
       Tree (0-indexed):
            0
          / | \
         1  2  3
        / \    |
       4   5   6
    */
    int n = 7;
    EulerTourTree ett(n);
    ett.addEdge(0, 1); ett.addEdge(0, 2); ett.addEdge(0, 3);
    ett.addEdge(1, 4); ett.addEdge(1, 5);
    ett.addEdge(3, 6);

    vector<long long> values = {10, 20, 30, 40, 50, 60, 70};
    cout << "Tree structure:\n";
    cout << "        0 (10)\n";
    cout << "      / | \\\n";
    cout << "   1(20) 2(30) 3(40)\n";
    cout << "   / \\         |\n";
    cout << " 4(50) 5(60)  6(70)\n\n";

    ett.build(0, values);
    ett.printEulerTour();
    cout << "\n";

    cout << "Subtree sum queries:\n";
    cout << "  subtree(0) = " << ett.subtreeSum(0) << " (all nodes: 10+20+30+40+50+60+70 = 280)\n";
    cout << "  subtree(1) = " << ett.subtreeSum(1) << " (nodes 1,4,5: 20+50+60 = 130)\n";
    cout << "  subtree(3) = " << ett.subtreeSum(3) << " (nodes 3,6: 40+70 = 110)\n";
    cout << "  subtree(2) = " << ett.subtreeSum(2) << " (node 2: 30)\n";
    cout << "  subtree(4) = " << ett.subtreeSum(4) << " (node 4: 50)\n\n";

    cout << "Update: node 4 value 50 → 100\n";
    ett.updateNode(4, 50, 100);
    cout << "  subtree(0) = " << ett.subtreeSum(0) << " (was 280, now 330)\n";
    cout << "  subtree(1) = " << ett.subtreeSum(1) << " (was 130, now 180)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// IMPLEMENTATION 2: HLD + Segment Tree for Path Queries
// ═══════════════════════════════════════════════════════════════

class HLD {
    int n, timer;
    vector<vector<int>> adj;
    vector<int> parent, depth, heavy, head, pos, sub_sz;
    vector<long long> tree; // segment tree

    int dfs(int u) {
        sub_sz[u] = 1;
        int maxSz = 0;
        heavy[u] = -1;
        for (int v : adj[u]) {
            if (v != parent[u]) {
                parent[v] = u;
                depth[v] = depth[u] + 1;
                int cSz = dfs(v);
                sub_sz[u] += cSz;
                if (cSz > maxSz) {
                    maxSz = cSz;
                    heavy[u] = v;
                }
            }
        }
        return sub_sz[u];
    }

    void decompose(int u, int h) {
        head[u] = h;
        pos[u] = timer++;
        if (heavy[u] != -1)
            decompose(heavy[u], h); // Continue same chain
        for (int v : adj[u]) {
            if (v != parent[u] && v != heavy[u])
                decompose(v, v); // Start new chain
        }
    }

    void stUpdate(int node, int s, int e, int idx, long long val) {
        if (s == e) { tree[node] = val; return; }
        int mid = (s + e) / 2;
        if (idx <= mid) stUpdate(2*node, s, mid, idx, val);
        else stUpdate(2*node+1, mid+1, e, idx, val);
        tree[node] = max(tree[2*node], tree[2*node+1]);
    }

    long long stQuery(int node, int s, int e, int l, int r) {
        if (r < s || e < l) return LLONG_MIN;
        if (l <= s && e <= r) return tree[node];
        int mid = (s + e) / 2;
        return max(stQuery(2*node, s, mid, l, r), stQuery(2*node+1, mid+1, e, l, r));
    }

public:
    HLD(int n) : n(n), timer(0), adj(n), parent(n, -1), depth(n, 0),
                 heavy(n, -1), head(n), pos(n), sub_sz(n), tree(4*n, LLONG_MIN) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void build(int root, const vector<long long>& values) {
        dfs(root);
        decompose(root, root);
        for (int i = 0; i < n; i++)
            stUpdate(1, 0, n-1, pos[i], values[i]);
    }

    void updateNode(int u, long long val) {
        stUpdate(1, 0, n-1, pos[u], val);
    }

    // Path max query from u to v
    long long pathMax(int u, int v) {
        long long res = LLONG_MIN;
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) swap(u, v);
            // u's chain head is deeper
            res = max(res, stQuery(1, 0, n-1, pos[head[u]], pos[u]));
            u = parent[head[u]]; // Jump to parent of chain head
        }
        // Now u and v are on the same chain
        if (depth[u] > depth[v]) swap(u, v);
        res = max(res, stQuery(1, 0, n-1, pos[u], pos[v]));
        return res;
    }
};

void demoHLD() {
    cout << "═══ HLD + SEGMENT TREE FOR PATH QUERIES ═══\n\n";

    /*
       Tree:
            0
          / | \
         1  2  3
        / \    |
       4   5   6
    */
    int n = 7;
    HLD hld(n);
    hld.addEdge(0, 1); hld.addEdge(0, 2); hld.addEdge(0, 3);
    hld.addEdge(1, 4); hld.addEdge(1, 5);
    hld.addEdge(3, 6);

    vector<long long> values = {10, 20, 30, 40, 50, 60, 70};
    hld.build(0, values);

    cout << "Tree with values:\n";
    cout << "        0(10)\n";
    cout << "      / | \\\n";
    cout << "  1(20) 2(30) 3(40)\n";
    cout << "  / \\          |\n";
    cout << "4(50) 5(60)   6(70)\n\n";

    cout << "Path MAX queries:\n";
    cout << "  pathMax(4, 6) = " << hld.pathMax(4, 6)
         << " (path: 4→1→0→3→6, max(50,20,10,40,70) = 70)\n";
    cout << "  pathMax(4, 5) = " << hld.pathMax(4, 5)
         << " (path: 4→1→5, max(50,20,60) = 60)\n";
    cout << "  pathMax(2, 6) = " << hld.pathMax(2, 6)
         << " (path: 2→0→3→6, max(30,10,40,70) = 70)\n";
    cout << "  pathMax(0, 0) = " << hld.pathMax(0, 0) << " (single node: 10)\n\n";

    cout << "Update: node 0 value → 100\n";
    hld.updateNode(0, 100);
    cout << "  pathMax(4, 6) = " << hld.pathMax(4, 6) << " (now 100)\n\n";

    cout << "HLD Complexity:\n";
    cout << "  • Path query: O(log²n) — O(log n) chains × O(log n) per ST query\n";
    cout << "  • With optimized HLD: O(log n) per query (single chain walk)\n";
    cout << "  • Update: O(log n)\n";
    cout << "  • Build: O(n)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║   LEVEL 11: SEGMENT TREE ON TREES (EULER TOUR + HLD)       ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n\n";

    demoEulerTour();
    demoHLD();

    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "  KEY TAKEAWAYS:\n";
    cout << "  1. Euler Tour: subtree → contiguous range in array\n";
    cout << "  2. Subtree queries: range query on [tin[u], tout[u]]\n";
    cout << "  3. HLD: decompose tree into O(log n) chains\n";
    cout << "  4. Path query = query each chain segment separately\n";
    cout << "  5. HLD + ST: O(log²n) path queries, O(log n) updates\n";
    cout << "  6. Essential for CSES Path Queries II, SPOJ QTREE\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

