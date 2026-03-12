/*
╔══════════════════════════════════════════════════════════════════╗
║              02 — BFS: BREADTH-FIRST SEARCH                     ║
║              Level Order Traversal + Shortest Path              ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

BFS explores a graph LEVEL BY LEVEL using a QUEUE.
  - First visits all vertices at distance 0 (source)
  - Then all vertices at distance 1
  - Then all vertices at distance 2
  - ... and so on

BFS naturally finds the SHORTEST PATH in UNWEIGHTED graphs!

  Algorithm:
  1. Enqueue source, mark visited, dist[source] = 0
  2. While queue not empty:
     a. Dequeue vertex u
     b. For each unvisited neighbor v:
        - Mark visited, dist[v] = dist[u] + 1
        - Enqueue v

═══════════════════════════════════════════════════════════════════
VISUALIZATION & DRY RUN
═══════════════════════════════════════════════════════════════════

Graph:
    1 ─── 2 ─── 5
    │     │     │
    3 ─── 4     6

BFS from vertex 1:
══════════════════════════════════════════════════════════════
Step │ Queue         │ Dequeue │ Visited          │ dist[]
══════════════════════════════════════════════════════════════
  0  │ [1]           │    -    │ {1}              │ d[1]=0
  1  │ [2,3]         │    1    │ {1,2,3}          │ d[2]=1,d[3]=1
  2  │ [3,4,5]       │    2    │ {1,2,3,4,5}      │ d[4]=2,d[5]=2
  3  │ [4,5]         │    3    │ {1,2,3,4,5}      │ (4 already visited)
  4  │ [5]           │    4    │ {1,2,3,4,5}      │ (all neighbors visited)
  5  │ [6]           │    5    │ {1,2,3,4,5,6}    │ d[6]=3
  6  │ []            │    6    │ {1,2,3,4,5,6}    │ DONE
══════════════════════════════════════════════════════════════

BFS Order: 1, 2, 3, 4, 5, 6

Level Structure:
  Level 0: {1}
  Level 1: {2, 3}
  Level 2: {4, 5}
  Level 3: {6}

Shortest distances from vertex 1:
  d[1]=0, d[2]=1, d[3]=1, d[4]=2, d[5]=2, d[6]=3

═══════════════════════════════════════════════════════════════════
WHY BFS GIVES SHORTEST PATH (UNWEIGHTED)
═══════════════════════════════════════════════════════════════════

  PROOF SKETCH:
  - BFS processes vertices in order of their distance from source
  - When we first visit a vertex, we've found the shortest path to it
  - Because: we've already visited ALL closer vertices first
  - This is a "wavefront" expanding outward layer by layer

═══════════════════════════════════════════════════════════════════
TIME & SPACE COMPLEXITY
═══════════════════════════════════════════════════════════════════

  Time:  O(V + E)  — each vertex enqueued once, each edge checked once
  Space: O(V)      — queue + visited + dist arrays

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
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int, int>;

#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

template<class T>
void read(vec<T> &v) { for (auto &x : v) cin >> x; }

void solve() {
    int n, m;
    cin >> n >> m;

    vvec<int> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    int source;
    cin >> source;
    source--;

    // ========================================
    // BFS with shortest path + path reconstruction
    // ========================================
    vec<int> dist(n, -1);
    vec<int> parent(n, -1);  // to reconstruct path
    queue<int> q;

    dist[source] = 0;
    q.push(source);

    vec<int> bfsOrder;
    vvec<int> levels;  // vertices at each level

    while (!q.empty()) {
        int u = q.front(); q.pop();
        bfsOrder.pb(u);

        // Track levels
        while (sz(levels) <= dist[u]) levels.pb({});
        levels[dist[u]].pb(u);

        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    // Print BFS order
    cout << "BFS Order from " << source + 1 << ": ";
    for (int i = 0; i < sz(bfsOrder); i++) {
        if (i > 0) cout << " → ";
        cout << bfsOrder[i] + 1;
    }
    cout << nl;

    // Print levels
    cout << nl << "Level Structure:" << nl;
    for (int l = 0; l < sz(levels); l++) {
        cout << "  Level " << l << ": {";
        for (int j = 0; j < sz(levels[l]); j++) {
            if (j > 0) cout << ", ";
            cout << levels[l][j] + 1;
        }
        cout << "}" << nl;
    }

    // Print shortest distances
    cout << nl << "Shortest distances:" << nl;
    for (int i = 0; i < n; i++) {
        cout << "  d[" << i+1 << "] = ";
        if (dist[i] == -1) cout << "UNREACHABLE";
        else cout << dist[i];
        cout << nl;
    }

    // Path reconstruction: find path from source to every vertex
    cout << nl << "Shortest paths:" << nl;
    for (int i = 0; i < n; i++) {
        if (dist[i] == -1 || i == source) continue;

        vec<int> path;
        for (int v = i; v != -1; v = parent[v]) {
            path.pb(v);
        }
        reverse(all(path));

        cout << "  " << source+1 << " → " << i+1 << " (dist=" << dist[i] << "): ";
        for (int j = 0; j < sz(path); j++) {
            if (j > 0) cout << " → ";
            cout << path[j] + 1;
        }
        cout << nl;
    }
}

/*
═══════════════════════════════════════════════════════════════════
SAMPLE INPUT/OUTPUT
═══════════════════════════════════════════════════════════════════

Input:
1
6 6
1 2
1 3
2 4
2 5
3 4
5 6
1

Output:
BFS Order from 1: 1 → 2 → 3 → 4 → 5 → 6

Level Structure:
  Level 0: {1}
  Level 1: {2, 3}
  Level 2: {4, 5}
  Level 3: {6}

Shortest distances:
  d[1] = 0
  d[2] = 1
  d[3] = 1
  d[4] = 2
  d[5] = 2
  d[6] = 3

Shortest paths:
  1 → 2 (dist=1): 1 → 2
  1 → 3 (dist=1): 1 → 3
  1 → 4 (dist=2): 1 → 2 → 4
  1 → 5 (dist=2): 1 → 2 → 5
  1 → 6 (dist=3): 1 → 2 → 5 → 6

═══════════════════════════════════════════════════════════════════
KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
  ✅ BFS = shortest path for unweighted graphs (GUARANTEED!)
  ✅ O(V + E) time — optimal for graph traversal
  ✅ Use parent[] array to reconstruct the actual path
  ✅ BFS gives natural "level" structure
  ✅ For weighted shortest path, use Dijkstra instead
═══════════════════════════════════════════════════════════════════
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1;
    cin >> TC;
    while (TC--) solve();
    return 0;
}

