/*
╔══════════════════════════════════════════════════════════════════╗
║              05 — COURSE SCHEDULE PROBLEMS                      ║
║              Classic topological sort application               ║
╚══════════════════════════════════════════════════════════════════╝

Problem: n courses with prerequisites. Can you finish all courses?
         If yes, give a valid order.

This is topological sort on the prerequisite DAG.
If cycle → impossible to finish all courses.

Time: O(V+E)    Space: O(V+E)
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

void solve() {
    int n, m;  // n courses, m prerequisites
    cin >> n >> m;

    vvec<int> adj(n);
    vec<int> inDeg(n, 0);

    for (int i = 0; i < m; i++) {
        int a, b;  // b is prerequisite for a (b → a)
        cin >> a >> b; a--; b--;
        adj[b].pb(a);
        inDeg[a]++;
    }

    // Kahn's with priority_queue for lexicographically smallest order
    priority_queue<int, vec<int>, greater<int>> pq;
    for (int i = 0; i < n; i++) if (inDeg[i]==0) pq.push(i);

    vec<int> order;
    while (!pq.empty()) {
        int u = pq.top(); pq.pop();
        order.pb(u);
        for (int v : adj[u]) {
            if (--inDeg[v]==0) pq.push(v);
        }
    }

    if (sz(order) != n) {
        cout << "IMPOSSIBLE (circular dependency)" << nl;
    } else {
        cout << "Course order: ";
        for (int i = 0; i < n; i++) {
            if (i) cout << " → ";
            cout << order[i]+1;
        }
        cout << nl;
    }
}

/*
Input: 1\n4 4\n2 1\n3 1\n4 2\n4 3
(Course 2 needs 1, Course 3 needs 1, Course 4 needs 2 and 3)
Output: Course order: 1 → 2 → 3 → 4
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin >> TC;
    while (TC--) solve();
}

