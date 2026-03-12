/*
╔══════════════════════════════════════════════════════════════════╗
║  03 — DYNAMIC CONNECTIVITY (Offline with Link-Cut / ETT)        ║
║  Zero to GM Level — ICPC Level Tree Algorithms                   ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 PROBLEM: Dynamic Connectivity
═══════════════════════════════════════════════════════════════════

 Given a graph with edges being added/removed over time,
 answer "are u and v connected?" queries.

 Two approaches:
   1. ONLINE: Link-Cut Tree → O(log N) per operation
   2. OFFLINE: Divide & conquer on time + DSU with rollback

═══════════════════════════════════════════════════════════════════
 APPROACH 2: OFFLINE D&C + DSU (Most practical for ICPC)
═══════════════════════════════════════════════════════════════════

 Each edge exists during a TIME INTERVAL [add_time, remove_time).
 Build a segment tree on time. Each edge is added to O(log T) nodes.
 DFS the segment tree, maintaining DSU with rollback.

═══════════════════════════════════════════════════════════════════
 DRY RUN
═══════════════════════════════════════════════════════════════════

 Operations (T=6):
   t=0: add(1,2)
   t=1: add(2,3)
   t=2: query connected(1,3)? → YES
   t=3: remove(1,2)
   t=4: query connected(1,3)? → NO
   t=5: add(1,3)

 Edge (1,2) exists during [0, 3)
 Edge (2,3) exists during [1, 6)  (never removed)
 Edge (1,3) exists during [5, 6)

 Segment tree on time [0..5]:
   Edge (1,2) added to nodes covering [0,3)
   Edge (2,3) added to nodes covering [1,6)
   Edge (1,3) added to nodes covering [5,6)

 DFS segment tree with DSU:
   At time 2: DSU has {1-2, 2-3} → 1,2,3 connected → YES ✅
   At time 4: DSU has {2-3} only → 1 disconnected from 3 → NO ✅

═══════════════════════════════════════════════════════════════════
 DSU WITH ROLLBACK (undo operations)
═══════════════════════════════════════════════════════════════════

 Standard DSU uses path compression → can't undo.
 Union by RANK without path compression + explicit stack → rollback!

═══════════════════════════════════════════════════════════════════
 COMPLEXITY
═══════════════════════════════════════════════════════════════════

 Time: O((N + Q) · log²N)  (Q queries, each edge in O(log T) nodes,
       each DSU operation O(log N) without path compression)
 Space: O(N + Q log T)

═══════════════════════════════════════════════════════════════════
 CODE — DSU with rollback
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
using pii = pair<int, int>;
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

// ═══════════════════════════════════════════════════════════
// DSU WITH ROLLBACK (union by rank, no path compression)
// ═══════════════════════════════════════════════════════════
struct DSU_Rollback {
    vec<int> parent, rank_arr;
    vec<tuple<int,int,int,int>> history; // (u, old_par_u, v, old_rank_v)
    int components;

    DSU_Rollback(int n) : parent(n + 1), rank_arr(n + 1, 0), components(n) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        while (parent[x] != x) x = parent[x]; // NO path compression!
        return x;
    }

    bool connected(int u, int v) { return find(u) == find(v); }

    bool unite(int u, int v) {
        u = find(u); v = find(v);
        if (u == v) {
            history.pb({-1, -1, -1, -1}); // no-op marker
            return false;
        }
        if (rank_arr[u] < rank_arr[v]) swap(u, v);
        // Save state for rollback
        history.pb({v, parent[v], u, rank_arr[u]});
        parent[v] = u;
        if (rank_arr[u] == rank_arr[v]) rank_arr[u]++;
        components--;
        return true;
    }

    int save() { return sz(history); }

    void rollback(int checkpoint) {
        while (sz(history) > checkpoint) {
            auto [v, old_par, u, old_rank] = history.back();
            history.pop_back();
            if (v == -1) continue; // was a no-op
            parent[v] = old_par;
            rank_arr[u] = old_rank;
            components++;
        }
    }
};

void solve() {
    int n, q;
    cin >> n >> q;

    DSU_Rollback dsu(n);

    // Demo: link/cut/query with rollback
    vec<string> ops(q);
    vec<int> u_arr(q), v_arr(q);
    for (int i = 0; i < q; i++) {
        cin >> ops[i] >> u_arr[i] >> v_arr[i];
    }

    // Simple sequential processing (not full offline D&C)
    // For full offline D&C, use segment tree on time intervals
    vec<int> checkpoints;

    for (int i = 0; i < q; i++) {
        if (ops[i] == "link") {
            checkpoints.pb(dsu.save());
            dsu.unite(u_arr[i], v_arr[i]);
            cout << "Linked " << u_arr[i] << " " << v_arr[i]
                 << " (components: " << dsu.components << ")" << nl;
        } else if (ops[i] == "query") {
            cout << u_arr[i] << " and " << v_arr[i] << ": "
                 << (dsu.connected(u_arr[i], v_arr[i]) ? "CONNECTED" : "DISCONNECTED") << nl;
        } else if (ops[i] == "rollback") {
            // Undo last link
            if (!checkpoints.empty()) {
                dsu.rollback(checkpoints.back());
                checkpoints.pop_back();
                cout << "Rolled back last link (components: " << dsu.components << ")" << nl;
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
5 7
link 1 2
link 2 3
query 1 3
link 4 5
query 1 5
rollback 0 0
query 1 5

Output:
Linked 1 2 (components: 4)
Linked 2 3 (components: 3)
1 and 3: CONNECTED
Linked 4 5 (components: 2)
1 and 5: DISCONNECTED
Rolled back last link (components: 3)
1 and 5: DISCONNECTED

═══════════════════════════════════════════════════════════════════
 FULL OFFLINE DYNAMIC CONNECTIVITY OUTLINE
═══════════════════════════════════════════════════════════════════

 1. Each edge has existence interval [add_time, remove_time)
 2. Build segment tree on time axis [0, T)
 3. For each edge, add it to all segment tree nodes covering its interval
 4. DFS the segment tree:
    - Enter node: apply all edge unions (with save)
    - At leaf: answer query
    - Leave node: rollback DSU to saved state
 5. This gives O((N + Q) log²N) total

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ DSU with rollback: union by rank, NO path compression
 ✅ save() + rollback(checkpoint) for undoing operations
 ✅ O(log N) per find (no path compression = slower but undoable)
 ✅ Offline D&C: segment tree on time + DSU rollback
 ✅ Online: Link-Cut Tree (Ch17 file 01) for O(log N) amortized
═══════════════════════════════════════════════════════════════════
*/

