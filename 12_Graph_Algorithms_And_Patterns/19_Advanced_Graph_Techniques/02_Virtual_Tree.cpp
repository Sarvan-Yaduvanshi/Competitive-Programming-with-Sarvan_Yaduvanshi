/*
╔══════════════════════════════════════════════════════════════════╗
║         02 — VIRTUAL TREE (Auxiliary Tree)                      ║
║         Build O(k) tree on k important vertices preserving LCA  ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

Given a tree of n vertices and k "important" vertices,
build a VIRTUAL TREE containing only those k vertices (+ their
pairwise LCAs) while preserving tree structure and distances.

Result: A tree of size O(k) that maintains all ancestor/descendant
relationships and LCA between important vertices.

═══════════════════════════════════════════════════════════════════
ALGORITHM
═══════════════════════════════════════════════════════════════════

1. Sort important vertices by DFS entry time (tin)
2. Add pairwise LCAs of consecutive vertices in sorted order
3. Remove duplicates, sort all by tin
4. Build virtual tree using a stack (similar to Euler tour)

═══════════════════════════════════════════════════════════════════
WHEN TO USE
═══════════════════════════════════════════════════════════════════

Many tree DP problems where queries involve subsets of vertices.
Instead of DP on full tree O(n) per query → DP on virtual tree O(k).

Example: Q queries, each with k_i vertices, sum of k_i ≤ 10^5
  Without virtual tree: Q × n (TLE)
  With virtual tree: sum of k_i (OK!)

═══════════════════════════════════════════════════════════════════
COMPLEXITY
  Building: O(k log k) per query (sorting + LCA queries)
  Space: O(k) per virtual tree
═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

const int MAXN = 200005;
const int LOG = 18;

int n;
vvec<int> adj;
int tin[MAXN], tout[MAXN], timer_val;
int up[MAXN][LOG], depth[MAXN];

void dfsLCA(int u, int p, int d) {
    tin[u] = timer_val++;
    depth[u] = d;
    up[u][0] = p;
    for (int i = 1; i < LOG; i++)
        up[u][i] = up[up[u][i-1]][i-1];
    for (int v : adj[u])
        if (v != p) dfsLCA(v, u, d+1);
    tout[u] = timer_val++;
}

bool isAncestor(int u, int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int lca(int u, int v) {
    if (isAncestor(u, v)) return u;
    if (isAncestor(v, u)) return v;
    for (int i = LOG-1; i >= 0; i--)
        if (!isAncestor(up[u][i], v))
            u = up[u][i];
    return up[u][0];
}

// Build virtual tree on given vertices
// Returns adjacency list of virtual tree and list of vertices in it
pair<vvec<int>, vec<int>> buildVirtualTree(vec<int>& nodes) {
    // Sort by DFS entry time
    sort(nodes.begin(), nodes.end(), [](int a, int b) {
        return tin[a] < tin[b];
    });

    // Add pairwise LCAs
    vec<int> all = nodes;
    for (int i = 0; i + 1 < sz(nodes); i++) {
        all.pb(lca(nodes[i], nodes[i+1]));
    }

    // Deduplicate and sort
    sort(all.begin(), all.end(), [](int a, int b) {
        return tin[a] < tin[b];
    });
    all.erase(unique(all.begin(), all.end()), all.end());

    // Build tree using stack
    int m = sz(all);
    vvec<int> vtAdj(m);

    // Map vertex to index in virtual tree
    vec<int> idx(n, -1);
    for (int i = 0; i < m; i++) idx[all[i]] = i;

    stack<int> st;
    st.push(0); // first vertex (has smallest tin)

    for (int i = 1; i < m; i++) {
        int u = all[i];
        int l = lca(u, all[st.top()]);

        if (l != all[st.top()]) {
            // Pop and connect until we find ancestor
            while (sz(st) > 1) {
                int top = st.top();
                // Check if next on stack is ancestor of l
                st.pop();
                int next = st.top();
                if (isAncestor(all[next], l) && all[next] != l) {
                    // l is between next and top
                    if (idx[l] == -1) { idx[l] = sz(all); /* shouldn't happen */ }
                    vtAdj[idx[l]].pb(idx[all[top]]);
                    vtAdj[idx[all[top]]].pb(idx[l]);
                    st.push(idx[l]); // push l
                    break;
                }
                vtAdj[idx[all[next]]].pb(idx[all[top]]);
                vtAdj[idx[all[top]]].pb(idx[all[next]]);
            }
        }
        st.push(i);
    }

    // Connect remaining stack
    while (sz(st) > 1) {
        int top = st.top(); st.pop();
        int next = st.top();
        vtAdj[next].pb(top);
        vtAdj[top].pb(next);
    }

    return {vtAdj, all};
}

void solve() {
    cin >> n;
    adj.assign(n, {});
    for (int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v; u--; v--;
        adj[u].pb(v); adj[v].pb(u);
    }

    timer_val = 0;
    dfsLCA(0, 0, 0);

    int q; cin >> q;
    while (q--) {
        int k; cin >> k;
        vec<int> nodes(k);
        for (auto& x : nodes) { cin >> x; x--; }

        auto [vtAdj, vtNodes] = buildVirtualTree(nodes);

        cout << "Virtual tree has " << sz(vtNodes) << " vertices: ";
        for (int v : vtNodes) cout << v+1 << " ";
        cout << nl;
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC; while (TC--) solve();
}

