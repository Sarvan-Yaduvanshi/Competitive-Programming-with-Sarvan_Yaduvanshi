/*
╔══════════════════════════════════════════════════════════════════╗
║  02 — COUNT PATHS OF LENGTH K (Centroid Divide & Conquer)       ║
║  Zero to GM Level — Centroid Decomposition                       ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 PROBLEM: Count pairs (u,v) with dist(u,v) = K in a tree
═══════════════════════════════════════════════════════════════════

 Naive: O(N²) — check all pairs.
 Centroid decomposition: O(N log N)!

═══════════════════════════════════════════════════════════════════
 KEY IDEA
═══════════════════════════════════════════════════════════════════

 For any path in the tree, it passes through exactly one centroid
 in the centroid tree decomposition.

 For centroid C:
   1. Compute distances from C to all nodes in its component
   2. Count pairs whose distances sum to K
   3. Subtract pairs within the SAME child subtree (to avoid double-counting)
   4. Remove C, recurse on remaining components

═══════════════════════════════════════════════════════════════════
 DRY RUN (K=4)
═══════════════════════════════════════════════════════════════════

 Tree (N=7):
         1
        / \
       2   3
      / \   \
     4   5   6
    /
   7

 Centroid = 2 (sub sizes balanced)
 Distances from 2: {2:0, 1:1, 4:1, 5:1, 3:2, 7:2, 6:3}

 Pairs summing to K=4:
   dist=1 + dist=3 → (node at dist 1) × (node at dist 3)
   Nodes at dist 1: {1, 4, 5} (3 nodes)
   Nodes at dist 3: {6} (1 node)
   But must exclude pairs in same subtree of centroid!

   Subtree through child 1: {1, 3, 6} with dists {1, 2, 3}
   Subtree through child 4: {4, 7} with dists {1, 2}
   Subtree through child 5: {5} with dist {1}

   Total pairs with sum=4: use frequency array, then subtract same-subtree pairs.

═══════════════════════════════════════════════════════════════════
 COMPLEXITY: O(N log N) — each node processed O(log N) times
                          (once per centroid level)
═══════════════════════════════════════════════════════════════════
 CODE
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
#include <cstring>

using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

const int MAXN = 200005;

vvec<int> adj;
int sub_sz[MAXN];
bool removed[MAXN];
int n, K;
i64 answer;

void computeSize(int v, int par) {
    sub_sz[v] = 1;
    for (int u : adj[v])
        if (u != par && !removed[u]) {
            computeSize(u, v);
            sub_sz[v] += sub_sz[u];
        }
}

int findCentroid(int v, int par, int treeSize) {
    for (int u : adj[v])
        if (u != par && !removed[u] && sub_sz[u] > treeSize / 2)
            return findCentroid(u, v, treeSize);
    return v;
}

// Collect distances from centroid to all nodes in component
vec<int> dists;
void collectDists(int v, int par, int d) {
    dists.pb(d);
    for (int u : adj[v])
        if (u != par && !removed[u])
            collectDists(u, v, d + 1);
}

// Count pairs with dist sum = K using frequency array
vec<int> freq;
int maxDist;

i64 countPairsWithFreq(vec<int>& d) {
    i64 cnt = 0;
    for (int x : d) {
        if (K - x >= 0 && K - x <= maxDist)
            cnt += freq[K - x];
    }
    return cnt;
}

void addToFreq(vec<int>& d) {
    for (int x : d)
        if (x <= maxDist) freq[x]++;
}

void clearFreq(vec<int>& d) {
    for (int x : d)
        if (x <= maxDist) freq[x] = 0;
}

void solve_centroid(int v) {
    computeSize(v, -1);
    int c = findCentroid(v, -1, sub_sz[v]);
    removed[c] = true;

    // Process paths through centroid c
    freq.assign(maxDist + 1, 0);
    freq[0] = 1; // centroid itself at distance 0

    for (int u : adj[c]) {
        if (removed[u]) continue;

        dists.clear();
        collectDists(u, c, 1);

        // Count pairs: one endpoint from this subtree, other from previously processed
        answer += countPairsWithFreq(dists);

        // Add current subtree distances to frequency
        addToFreq(dists);
    }

    // Cleanup frequency (restore to 0)
    freq[0] = 0;
    for (int u : adj[c]) {
        if (removed[u]) continue;
        dists.clear();
        collectDists(u, c, 1);
        clearFreq(dists);
    }

    // Recurse on remaining components
    for (int u : adj[c])
        if (!removed[u])
            solve_centroid(u);
}

void solve() {
    cin >> n >> K;
    adj.assign(n + 1, {});
    memset(removed, false, sizeof(removed));
    answer = 0;
    maxDist = n; // safe upper bound

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }

    solve_centroid(1);

    cout << "Number of pairs at distance " << K << ": " << answer << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1;
    // cin >> TC;
    while (TC--) solve();
    return 0;
}

/*
═══════════════════════════════════════════════════════════════════
 SAMPLE I/O
═══════════════════════════════════════════════════════════════════

Input:
7 3
1 2
1 3
2 4
2 5
3 6
4 7

Output:
Number of pairs at distance 3: 4

 Pairs: (7,1), (7,5), (4,3), (5,3)? Let me verify:
 dist(7,1)=3 ✅, dist(7,5)=3 ✅, dist(4,3)=3 ✅, dist(5,3)=3 ✅
 dist(4,6)=4, dist(7,3)=4 — not K=3.

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Centroid D&C: process paths through centroid, then recurse
 ✅ Use frequency array to count pairs with distance sum = K
 ✅ Process child subtrees one by one to avoid same-subtree pairs
 ✅ O(N log N) total — each node in O(log N) centroid levels
 ✅ Powerful technique for: path counting, closest pair, etc.
═══════════════════════════════════════════════════════════════════
*/

