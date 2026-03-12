/*
╔══════════════════════════════════════════════════════════════════╗
║              02 — HIERHOLZER'S ALGORITHM                        ║
║              Find Euler path/circuit in O(E)                    ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
ALGORITHM
═══════════════════════════════════════════════════════════════════

1. Start at appropriate vertex (odd degree for path, any for circuit)
2. Follow edges greedily, removing used edges
3. When stuck (no more edges from current vertex),
   add vertex to FRONT of result
4. Backtrack and continue from previous vertex

Uses a stack + tracking current edge index for efficiency.

═══════════════════════════════════════════════════════════════════
DRY RUN (Directed graph)
═══════════════════════════════════════════════════════════════════

Graph: 1→2, 2→3, 3→1, 1→4, 4→3
All vertices: in = out, so Euler circuit exists.

Stack: [1]
  1→2: Stack [1,2]
  2→3: Stack [1,2,3]
  3→1: Stack [1,2,3,1]
  1→4: Stack [1,2,3,1,4]
  4→3: Stack [1,2,3,1,4,3]
  3: no more edges → pop to result: [3]
  4: no more edges → pop: [4,3]
  1: no more edges → pop: [1,4,3]
  3: no more edges → pop: [3,1,4,3]
  2: no more edges → pop: [2,3,1,4,3]
  1: no more edges → pop: [1,2,3,1,4,3]

Euler circuit: 1→2→3→1→4→3→1

Time: O(E)    Space: O(V+E)
═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
#endif
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
#define sz(x) ((int)(x).size())
#define nl '\n'

// DIRECTED Euler circuit/path using Hierholzer
void solve() {
    int n, m; cin >> n >> m;

    vvec<int> adj(n);
    vec<int> inD(n,0), outD(n,0);

    for(int i=0;i<m;i++){
        int u,v; cin>>u>>v; u--;v--;
        adj[u].push_back(v);
        outD[u]++; inD[v]++;
    }

    // Determine start vertex
    int start = 0;
    int startNodes=0, endNodes=0;
    bool valid = true;

    for(int i=0;i<n;i++){
        int diff = outD[i]-inD[i];
        if(diff==1) { start=i; startNodes++; }
        else if(diff==-1) { endNodes++; }
        else if(diff!=0) { valid=false; }
    }

    if(!valid || (startNodes!=0 && !(startNodes==1&&endNodes==1))){
        cout << "No Euler path/circuit" << nl;
        return;
    }

    // Hierholzer's Algorithm
    vec<int> curEdge(n, 0);  // next edge to use from each vertex
    stack<int> st;
    vec<int> result;

    st.push(start);
    while(!st.empty()){
        int u = st.top();
        if(curEdge[u] < sz(adj[u])){
            int v = adj[u][curEdge[u]++];
            st.push(v);
        } else {
            result.push_back(u);
            st.pop();
        }
    }

    reverse(result.begin(), result.end());

    if(sz(result) != m+1){
        cout << "Graph not connected enough for Euler path" << nl;
        return;
    }

    cout << "Euler " << (startNodes==0 ? "circuit" : "path") << ":" << nl;
    for(int i=0;i<sz(result);i++){
        if(i) cout << " → ";
        cout << result[i]+1;
    }
    cout << nl;
}

/*
Input: 1\n4 6\n1 2\n2 3\n3 1\n1 4\n4 3\n3 1
Output: Euler circuit: 1 → 2 → 3 → 1 → 4 → 3 → 1
*/

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin>>TC; while(TC--) solve();
}

