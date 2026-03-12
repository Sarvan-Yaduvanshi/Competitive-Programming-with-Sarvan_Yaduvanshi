/*
╔══════════════════════════════════════════════════════════════════╗
║         06 — DYNAMIC CONNECTIVITY (Offline via DSU+D&C)         ║
║         Edge add/delete with connectivity queries               ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

DYNAMIC CONNECTIVITY: Given a graph where edges are added and
removed over time, answer "are u,v connected?" at any point.

OFFLINE SOLUTION: Divide & Conquer on time + DSU with rollback.

Each edge has a lifetime [tAdd, tRemove).
Use segment tree on time intervals.
For each time point, activate/deactivate edges.

ALGORITHM:
  1. Build segment tree on time [0, Q)
  2. For each edge with lifetime [l, r), insert into segment tree
     nodes covering [l, r)
  3. DFS through segment tree:
     - Enter node: unite all edges stored in this node
     - At leaf: answer the query for this time point
     - Leave node: rollback the unions (DSU with rollback!)

═══════════════════════════════════════════════════════════════════
COMPLEXITY
  Time:  O(Q × log²Q × α(V)) ≈ O(Q × log²Q)
  Space: O(V + E × logQ)

  ⚠️ Requires DSU WITHOUT path compression (union by rank only)
     to support rollback.
═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int,int>;
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

// DSU with rollback (no path compression!)
struct DSU_Rollback {
    vec<int> parent, rank_;
    vec<pair<int*,int>> history;

    DSU_Rollback(int n) : parent(n), rank_(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        while (parent[x] != x) x = parent[x]; // NO path compression
        return x;
    }

    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (rank_[a] < rank_[b]) swap(a, b);
        history.pb({&parent[b], parent[b]});
        history.pb({&rank_[a], rank_[a]});
        parent[b] = a;
        if (rank_[a] == rank_[b]) rank_[a]++;
        return true;
    }

    bool connected(int a, int b) { return find(a) == find(b); }
    int save() { return sz(history); }
    void rollback(int checkpoint) {
        while (sz(history) > checkpoint) {
            auto [ptr, val] = history.back();
            *ptr = val;
            history.pop_back();
        }
    }
};

// Segment tree on time — stores edge sets at each node
struct SegTree {
    int sz;
    vvec<pii> tree; // edges at each node

    SegTree(int n) : sz(n), tree(4 * n) {}

    void addEdge(int node, int lo, int hi, int l, int r, pii edge) {
        if (l >= hi || r <= lo) return;
        if (l <= lo && hi <= r) { tree[node].pb(edge); return; }
        int mid = (lo + hi) / 2;
        addEdge(2*node, lo, mid, l, r, edge);
        addEdge(2*node+1, mid, hi, l, r, edge);
    }

    void addEdge(int l, int r, pii edge) {
        if (l >= r) return;
        addEdge(1, 0, sz, l, r, edge);
    }
};

int n, q;
DSU_Rollback* dsu;
SegTree* seg;
vec<int> queryU, queryV;
vec<bool> answers;

void solve(int node, int lo, int hi) {
    int checkpoint = dsu->save();

    // Activate edges at this node
    for (auto [u, v] : seg->tree[node]) {
        dsu->unite(u, v);
    }

    if (hi - lo == 1) {
        // Leaf: answer query at time 'lo'
        if (queryU[lo] != -1) {
            answers[lo] = dsu->connected(queryU[lo], queryV[lo]);
        }
    } else {
        int mid = (lo + hi) / 2;
        solve(2*node, lo, mid);
        solve(2*node+1, mid, hi);
    }

    // Rollback
    dsu->rollback(checkpoint);
}

void run() {
    cin >> n >> q;

    DSU_Rollback dsuObj(n);
    dsu = &dsuObj;

    SegTree segObj(q);
    seg = &segObj;

    queryU.assign(q, -1);
    queryV.assign(q, -1);
    answers.assign(q, false);

    // Track edge lifetimes
    map<pii, int> edgeStart; // edge → time when added

    for (int t = 0; t < q; t++) {
        int type; cin >> type;
        if (type == 1) {
            // Add edge
            int u, v; cin >> u >> v; u--; v--;
            if (u > v) swap(u, v);
            edgeStart[{u, v}] = t;
        } else if (type == 2) {
            // Remove edge
            int u, v; cin >> u >> v; u--; v--;
            if (u > v) swap(u, v);
            int start = edgeStart[{u, v}];
            seg->addEdge(start, t, {u, v});
            edgeStart.erase({u, v});
        } else {
            // Query: connected?
            cin >> queryU[t] >> queryV[t];
            queryU[t]--; queryV[t]--;
        }
    }

    // Close remaining edges
    for (auto [edge, start] : edgeStart) {
        seg->addEdge(start, q, edge);
    }

    solve(1, 0, q);

    for (int t = 0; t < q; t++) {
        if (queryU[t] != -1) {
            cout << (answers[t] ? "YES" : "NO") << nl;
        }
    }
}

/*
Input: 1\n3 7\n1 1 2\n1 2 3\n3 1 3\n2 1 2\n3 1 3\n1 1 3\n3 1 3
Output:
YES (1-2-3 connected)
NO  (edge 1-2 removed, only 2-3 remains)
YES (edge 1-3 added)
*/

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC; while (TC--) run();
}

