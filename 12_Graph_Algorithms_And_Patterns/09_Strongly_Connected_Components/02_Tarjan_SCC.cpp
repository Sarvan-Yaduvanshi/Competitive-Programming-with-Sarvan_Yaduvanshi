/*
╔══════════════════════════════════════════════════════════════════╗
║              02 — TARJAN'S SCC ALGORITHM                        ║
║              Single-pass DFS with low-link values               ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
ALGORITHM
═══════════════════════════════════════════════════════════════════

Uses DFS discovery time (disc[]) and lowest reachable discovery
time (low[]).

  disc[u] = when u was discovered
  low[u]  = minimum disc reachable from u's subtree via back edges

A vertex u is a ROOT of an SCC if: disc[u] == low[u]

When we find a root, pop all vertices from stack until u → one SCC.

Time: O(V+E)    Space: O(V+E)
═══════════════════════════════════════════════════════════════════

DRY RUN:
  Graph: 1→2, 2→3, 3→1, 3→4, 4→5, 5→4

  DFS from 1:
    disc[1]=0, low[1]=0, push 1
    → disc[2]=1, low[2]=1, push 2
      → disc[3]=2, low[3]=2, push 3
        → 1: on stack, low[3]=min(2,0)=0
        → disc[4]=3, low[4]=3, push 4
          → disc[5]=4, low[5]=4, push 5
            → 4: on stack, low[5]=min(4,3)=3
            low[5]=3 ≠ disc[5]=4, not root
          low[4]=min(3,3)=3, disc[4]=3=low[4] → ROOT!
          Pop: {5,4} → SCC #1
        low[3]=min(0,3)=0, not root
      low[2]=min(1,0)=0, not root
    low[1]=min(0,0)=0, disc[1]=0=low[1] → ROOT!
    Pop: {3,2,1} → SCC #2

═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

int n, m;
vvec<int> adj;
vec<int> disc, low, comp;
vec<bool> onStack;
stack<int> st;
int timer_val, numSCC;
vvec<int> sccs;

void tarjan(int u) {
    disc[u] = low[u] = timer_val++;
    st.push(u);
    onStack[u] = true;

    for (int v : adj[u]) {
        if (disc[v] == -1) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (onStack[v]) {
            low[u] = min(low[u], disc[v]);
        }
    }

    // u is root of an SCC
    if (disc[u] == low[u]) {
        vec<int> scc;
        while (true) {
            int v = st.top(); st.pop();
            onStack[v] = false;
            comp[v] = numSCC;
            scc.pb(v);
            if (v == u) break;
        }
        sccs.pb(scc);
        numSCC++;
    }
}

void solve() {
    cin >> n >> m;
    adj.assign(n, {});
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v; u--; v--;
        adj[u].pb(v);
    }

    disc.assign(n, -1);
    low.assign(n, 0);
    comp.assign(n, -1);
    onStack.assign(n, false);
    timer_val = numSCC = 0;
    sccs.clear();

    for (int i = 0; i < n; i++) {
        if (disc[i] == -1) tarjan(i);
    }

    cout << "Number of SCCs: " << numSCC << nl;
    for (int i = 0; i < numSCC; i++) {
        cout << "SCC " << i+1 << ": {";
        for (int j = 0; j < sz(sccs[i]); j++) {
            if (j) cout << ", ";
            cout << sccs[i][j]+1;
        }
        cout << "}" << nl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin >> TC;
    while (TC--) solve();
}

