/*
╔══════════════════════════════════════════════════════════════════╗
║         03 — BLOSSOM ALGORITHM (General Matching Concept)       ║
║         Maximum matching in non-bipartite graphs                ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

In GENERAL (non-bipartite) graphs, Kuhn's algorithm fails because
odd cycles create "blossoms" that confuse augmenting path search.

BLOSSOM: An odd-length alternating cycle in the graph.

EDMONDS' BLOSSOM ALGORITHM:
  1. Search for augmenting paths like Kuhn
  2. When an odd cycle (blossom) is found, CONTRACT it to a single
     super-vertex and continue searching
  3. When augmenting path found through contracted graph,
     EXPAND blossoms and augment

═══════════════════════════════════════════════════════════════════
EXAMPLE
═══════════════════════════════════════════════════════════════════

Pentagon graph (5-cycle):
    1 — 2
    |       |
    5   3
    |   |
    4 ——┘

This is not bipartite (odd cycle), Kuhn fails.
Blossom algorithm contracts the 5-cycle, finds matching of size 2.
Maximum matching = 2 (e.g., 1-2, 3-4, vertex 5 unmatched)

═══════════════════════════════════════════════════════════════════
COMPLEXITY
  Edmonds' algorithm: O(V³) or O(V² × E)
  Micali-Vazirani: O(√V × E) — fastest known

IMPLEMENTATION NOTE:
  Full blossom implementation is 100+ lines. Below is a simplified
  O(V³) version suitable for ICPC (n ≤ 500).
═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
#define sz(x) ((int)(x).size())
#define nl '\n'

// Edmonds' Blossom Algorithm O(V³)
struct Blossom {
    int n;
    vvec<int> adj;
    vec<int> match, parent, base;
    vec<bool> blossom, vis;

    Blossom(int n) : n(n), adj(n), match(n, -1), parent(n), base(n), blossom(n), vis(n) {}

    void addEdge(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); }

    int lca(int a, int b) {
        vec<bool> used(n, false);
        while (true) {
            a = base[a];
            used[a] = true;
            if (match[a] == -1) break;
            a = parent[match[a]];
        }
        while (true) {
            b = base[b];
            if (used[b]) return b;
            b = parent[match[b]];
        }
    }

    void markPath(int v, int b, int child) {
        while (base[v] != b) {
            blossom[base[v]] = true;
            blossom[base[match[v]]] = true;
            parent[v] = child;
            child = match[v];
            v = parent[match[v]];
        }
    }

    int findAugPath(int root) {
        fill(vis.begin(), vis.end(), false);
        fill(parent.begin(), parent.end(), -1);
        for (int i = 0; i < n; i++) base[i] = i;

        vis[root] = true;
        queue<int> q;
        q.push(root);

        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int to : adj[v]) {
                if (base[v] == base[to] || match[v] == to) continue;
                if (to == root || (match[to] != -1 && parent[match[to]] != -1)) {
                    // Found blossom — contract
                    int curBase = lca(v, to);
                    fill(blossom.begin(), blossom.end(), false);
                    markPath(v, curBase, to);
                    markPath(to, curBase, v);
                    for (int i = 0; i < n; i++) {
                        if (blossom[base[i]]) {
                            base[i] = curBase;
                            if (!vis[i]) { vis[i] = true; q.push(i); }
                        }
                    }
                } else if (parent[to] == -1) {
                    parent[to] = v;
                    if (match[to] == -1) return to; // augmenting path found
                    to = match[to];
                    vis[to] = true;
                    q.push(to);
                }
            }
        }
        return -1;
    }

    int maxMatching() {
        int result = 0;
        for (int v = 0; v < n; v++) {
            if (match[v] == -1) {
                int u = findAugPath(v);
                if (u != -1) {
                    result++;
                    while (u != -1) {
                        int pv = parent[u], ppv = match[pv];
                        match[u] = pv; match[pv] = u;
                        u = ppv;
                    }
                }
            }
        }
        return result;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    Blossom blossom(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v; u--; v--;
        blossom.addEdge(u, v);
    }

    int matching = blossom.maxMatching();
    cout << "Maximum matching (general graph): " << matching << nl;
    for (int i = 0; i < n; i++) {
        if (blossom.match[i] > i) {
            cout << "  " << i+1 << " — " << blossom.match[i]+1 << nl;
        }
    }
}

/*
Input: 1\n5 5\n1 2\n2 3\n3 4\n4 5\n5 1
(Pentagon — odd cycle, not bipartite)
Output:
Maximum matching (general graph): 2
  1 — 2
  3 — 4
*/

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC; while (TC--) solve();
}

