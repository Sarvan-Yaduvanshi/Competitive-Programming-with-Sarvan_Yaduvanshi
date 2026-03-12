/*
╔══════════════════════════════════════════════════════════════════╗
║  01 — ROOT TO NODE PATH & ALL ROOT-TO-LEAF PATHS               ║
║  Zero to GM Level — Tree Path Problems                           ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 FIND PATH FROM ROOT TO A TARGET NODE — DRY RUN
═══════════════════════════════════════════════════════════════════

 Tree:
           1
          / \
         2   3
        / \   \
       4   5   6

 Find path from root(1) to node(5):

 DFS(1, target=5, path=[]):
   path = [1]
   DFS(2, target=5, path=[1]):
     path = [1, 2]
     DFS(4, target=5, path=[1,2]):
       path = [1, 2, 4]
       4 ≠ 5, no children match → pop 4, path=[1,2]
     DFS(5, target=5, path=[1,2]):
       path = [1, 2, 5]
       5 == target → FOUND! Return [1, 2, 5] ✅

═══════════════════════════════════════════════════════════════════
 ALL ROOT-TO-LEAF PATHS — DRY RUN
═══════════════════════════════════════════════════════════════════

 Same tree:
   Path 1: 1→2→4
   Path 2: 1→2→5
   Path 3: 1→3→6

 DFS with backtracking:
   DFS(1): path=[1]
     DFS(2): path=[1,2]
       DFS(4): path=[1,2,4] → LEAF → save path
       DFS(5): path=[1,2,5] → LEAF → save path
     DFS(3): path=[1,3]
       DFS(6): path=[1,3,6] → LEAF → save path

═══════════════════════════════════════════════════════════════════
 COMPLEXITY: O(N) time, O(H) space for recursion | O(N·H) for paths
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

using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

vvec<int> adj;

// ═══════════════════════════════════════════════════════════
// Find path from root to target
// ═══════════════════════════════════════════════════════════
bool findPath(int v, int par, int target, vec<int>& path) {
    path.pb(v);
    if (v == target) return true;
    for (int u : adj[v]) {
        if (u == par) continue;
        if (findPath(u, v, target, path)) return true;
    }
    path.pop_back(); // backtrack
    return false;
}

// ═══════════════════════════════════════════════════════════
// All root-to-leaf paths
// ═══════════════════════════════════════════════════════════
vvec<int> allPaths;

void findAllPaths(int v, int par, vec<int>& path) {
    path.pb(v);

    bool isLeaf = true;
    for (int u : adj[v]) {
        if (u == par) continue;
        isLeaf = false;
        findAllPaths(u, v, path);
    }

    if (isLeaf) allPaths.pb(path);
    path.pop_back();
}

void solve() {
    int n;
    cin >> n;
    adj.assign(n + 1, {});
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }

    // Path from root to target
    int target;
    cin >> target;
    vec<int> path;
    if (findPath(1, -1, target, path)) {
        cout << "Path from 1 to " << target << ": ";
        for (int i = 0; i < sz(path); i++) {
            if (i) cout << " → ";
            cout << path[i];
        }
        cout << nl;
    }

    // All root-to-leaf paths
    allPaths.clear();
    path.clear();
    findAllPaths(1, -1, path);

    cout << "All root-to-leaf paths:" << nl;
    for (auto& p : allPaths) {
        cout << "  ";
        for (int i = 0; i < sz(p); i++) {
            if (i) cout << " → ";
            cout << p[i];
        }
        cout << nl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1;
    cin >> TC;
    while (TC--) solve();
    return 0;
}

/*
 Input: 1\n6\n1 2\n1 3\n2 4\n2 5\n3 6\n5
 Output:
 Path from 1 to 5: 1 → 2 → 5
 All root-to-leaf paths:
   1 → 2 → 4
   1 → 2 → 5
   1 → 3 → 6
*/

