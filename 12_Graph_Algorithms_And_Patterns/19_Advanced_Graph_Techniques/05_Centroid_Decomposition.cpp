/*
╔══════════════════════════════════════════════════════════════════╗
║         CENTROID DECOMPOSITION                                  ║
║         Divide & conquer on trees — path queries O(n log² n)    ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

CENTROID of tree: vertex whose removal splits tree into subtrees
of size ≤ n/2.  Always exists and can be found in O(n).

CENTROID DECOMPOSITION:
  1. Find centroid c of tree
  2. Process all paths through c
  3. Remove c, recursively decompose remaining subtrees

Creates a CENTROID TREE of depth O(log n).
Every path in original tree passes through O(log n) centroids.

═══════════════════════════════════════════════════════════════════
APPLICATIONS
═══════════════════════════════════════════════════════════════════
  - Count paths with property X (length = k, weight = k, etc.)
  - Closest marked vertex to any node
  - Distance sum queries on tree

Time: O(n log n) build + O(log n) per query
Space: O(n)

═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using i64 = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

const int MAXN = 200005;
int n;
vvec<int> adj;
int subtreeSize[MAXN];
bool removed[MAXN];
int centroidParent[MAXN]; // parent in centroid tree

void calcSize(int v, int p) {
    subtreeSize[v] = 1;
    for (int u : adj[v]) {
        if (u != p && !removed[u]) {
            calcSize(u, v);
            subtreeSize[v] += subtreeSize[u];
        }
    }
}

int findCentroid(int v, int p, int treeSize) {
    for (int u : adj[v]) {
        if (u != p && !removed[u] && subtreeSize[u] > treeSize / 2)
            return findCentroid(u, v, treeSize);
    }
    return v;
}

void buildCentroidTree(int v, int p) {
    calcSize(v, -1);
    int c = findCentroid(v, -1, subtreeSize[v]);

    centroidParent[c] = p;
    removed[c] = true;

    for (int u : adj[c]) {
        if (!removed[u]) {
            buildCentroidTree(u, c);
        }
    }
}

void solve() {
    cin >> n;
    adj.assign(n, {});
    fill(removed, removed + n, false);
    fill(centroidParent, centroidParent + n, -1);

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v; u--; v--;
        adj[u].pb(v); adj[v].pb(u);
    }

    buildCentroidTree(0, -1);

    cout << "Centroid Tree:" << nl;
    for (int i = 0; i < n; i++) {
        cout << "  " << i+1 << " → parent: "
             << (centroidParent[i] == -1 ? 0 : centroidParent[i]+1) << nl;
    }

    // Example: count paths of length exactly K
    // For each centroid c:
    //   1. BFS/DFS to find distances from c to all vertices in its component
    //   2. Count pairs (d1, d2) where d1 + d2 = K
    //   3. Subtract pairs within same subtree (inclusion-exclusion)
}

/*
Input: 1\n7\n1 2\n1 3\n2 4\n2 5\n3 6\n3 7
Tree:      1
          / \
         2   3
        / \ / \
       4  5 6  7
Centroid: likely vertex 1 (size 7, max subtree 3)
*/

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC; while (TC--) solve();
}

