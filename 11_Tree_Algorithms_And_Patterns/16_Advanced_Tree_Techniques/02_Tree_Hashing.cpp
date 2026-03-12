/*
╔══════════════════════════════════════════════════════════════════╗
║  02 — TREE HASHING & ISOMORPHISM                               ║
║  Zero to GM Level — Advanced Tree Techniques                     ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 CONCEPT
═══════════════════════════════════════════════════════════════════

 Two rooted trees are ISOMORPHIC if they have the same structure
 (ignoring node labels).

 Tree hashing: assign a hash to each subtree such that
 isomorphic subtrees get the SAME hash.

 Method: Sort children hashes → combine into parent hash.
   hash[leaf] = base_hash
   hash[v] = H(sorted(hash[child1], hash[child2], ...))

═══════════════════════════════════════════════════════════════════
 DRY RUN
═══════════════════════════════════════════════════════════════════

 Tree A:        Tree B:
     1              1
    / \            / \
   2   3          2   3
  /     \          \   /
 4       5          4 5

 Tree A hashes:
   h[4]=H(leaf)=1, h[5]=H(leaf)=1
   h[2]=H(sorted{1})=H({1}), h[3]=H(sorted{1})=H({1})
   h[1]=H(sorted{H({1}), H({1})})

 Tree B hashes:
   h[4]=1, h[5]=1
   h[2]=H(sorted{1})=H({1}), h[3]=H(sorted{1})=H({1})
   h[1]=H(sorted{H({1}), H({1})})

 Same root hash → ISOMORPHIC ✅

═══════════════════════════════════════════════════════════════════
 IMPLEMENTATION: Map subtree structure to integers
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
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

// Map from sorted children hash vector → unique ID
map<vec<int>, int> hashMap;
int nextId = 0;

int getHash(vec<int>& childHashes) {
    sort(childHashes.begin(), childHashes.end());
    if (hashMap.find(childHashes) == hashMap.end()) {
        hashMap[childHashes] = nextId++;
    }
    return hashMap[childHashes];
}

vvec<int> adj;
vec<int> treeHash;

void computeHash(int v, int par) {
    vec<int> childHashes;
    for (int u : adj[v]) {
        if (u == par) continue;
        computeHash(u, v);
        childHashes.pb(treeHash[u]);
    }
    treeHash[v] = getHash(childHashes);
}

void solve() {
    // Read two trees, check if isomorphic (rooted)
    int n1; cin >> n1;
    adj.assign(n1 + 1, {});
    treeHash.assign(n1 + 1, 0);
    hashMap.clear(); nextId = 0;

    for (int i = 0; i < n1 - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }
    computeHash(1, -1);
    int hash1 = treeHash[1];

    int n2; cin >> n2;
    adj.assign(n2 + 1, {});
    treeHash.assign(n2 + 1, 0);

    for (int i = 0; i < n2 - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }
    computeHash(1, -1);
    int hash2 = treeHash[1];

    cout << "Tree 1 root hash: " << hash1 << nl;
    cout << "Tree 2 root hash: " << hash2 << nl;
    cout << "Isomorphic (rooted at 1): " << (hash1 == hash2 ? "YES" : "NO") << nl;
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
5
1 2
1 3
2 4
3 5
5
1 2
1 3
3 4
2 5

Output:
Tree 1 root hash: (same)
Tree 2 root hash: (same)
Isomorphic (rooted at 1): YES

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Tree hash: sort children hashes, map to unique ID
 ✅ Isomorphic subtrees get same hash
 ✅ For UNROOTED isomorphism: root at centroid(s) and compare
 ✅ Time: O(N log N) per tree
 ✅ Used in: symmetry detection, duplicate subtree removal
═══════════════════════════════════════════════════════════════════
*/

