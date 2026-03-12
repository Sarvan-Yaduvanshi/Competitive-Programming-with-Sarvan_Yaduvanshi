/*
╔══════════════════════════════════════════════════════════════════╗
║              04 — 2-SAT (Boolean Satisfiability via SCC)        ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

2-SAT: Given boolean variables x1..xn and clauses of form
  (a OR b) where a,b are literals (xi or ¬xi),
  determine if a satisfying assignment exists.

REDUCTION TO SCC:
  Clause (a OR b) → implications: (¬a → b) AND (¬b → a)
  Build implication graph, find SCCs.

  SATISFIABLE iff no variable and its negation are in same SCC.

  Assignment: if comp[x] > comp[¬x] → x = true, else x = false
  (Kosaraju numbers SCCs in reverse topological order)

Variable x → node 2*i
Negation ¬x → node 2*i + 1

Time: O(V+E) = O(n + clauses)    Space: O(n + clauses)
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

template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
#define pb push_back
#define nl '\n'

struct TwoSAT {
    int n;
    vvec<int> adj, radj;
    vec<bool> visited;
    vec<int> order, comp;
    vec<bool> assignment;

    TwoSAT(int n) : n(n), adj(2*n), radj(2*n) {}

    // Variable i: true literal = 2*i, false literal = 2*i+1
    // Add clause (a OR b): ¬a→b AND ¬b→a
    void addClause(int a, bool na, int b, bool nb) {
        // literal a: if na=true then ¬a, so literal = 2*a + na
        int la = 2*a + (na ? 0 : 1);  // ¬(literal of a if na)
        int lb = 2*b + (nb ? 0 : 1);
        int nota = la ^ 1;
        int notb = lb ^ 1;
        // (la OR lb) → (¬la → lb) AND (¬lb → la)
        // Actually: clause says (a_lit OR b_lit)
        // where a_lit = (na ? a : ¬a), b_lit = (nb ? b : ¬b)
        int alit = 2*a + (na ? 1 : 0); // na=true means we want variable a true = node 2*a
        // Let me simplify:
        // addImplication(¬alit, blit) and addImplication(¬blit, alit)
        int al = 2*a + (na ? 0 : 1);  // a appears positive(na=true) → 2*a, negative → 2*a+1
        int bl = 2*b + (nb ? 0 : 1);
        adj[al^1].pb(bl);
        adj[bl^1].pb(al);
        radj[bl].pb(al^1);
        radj[al].pb(bl^1);
    }

    // Simpler interface: addOr(u, v) where u,v are literal indices
    // Literal for variable i true = 2*i, false = 2*i+1
    void addOr(int u, int v) {
        adj[u^1].pb(v);
        adj[v^1].pb(u);
        radj[v].pb(u^1);
        radj[u].pb(v^1);
    }

    void dfs1(int u) { visited[u]=true; for(int v:adj[u]) if(!visited[v]) dfs1(v); order.pb(u); }
    void dfs2(int u,int c) { comp[u]=c; for(int v:radj[u]) if(comp[v]==-1) dfs2(v,c); }

    bool solve() {
        int N = 2*n;
        visited.assign(N, false);
        order.clear();
        for(int i=0;i<N;i++) if(!visited[i]) dfs1(i);
        comp.assign(N, -1);
        int numSCC = 0;
        for(int i=N-1;i>=0;i--){
            int u=order[i];
            if(comp[u]==-1) dfs2(u, numSCC++);
        }

        assignment.resize(n);
        for(int i=0;i<n;i++){
            if(comp[2*i]==comp[2*i+1]) return false; // UNSATISFIABLE
            assignment[i] = (comp[2*i] > comp[2*i+1]); // true if comp[true] > comp[false]
        }
        return true;
    }
};

void solve() {
    int n, m; cin >> n >> m; // n variables, m clauses

    TwoSAT sat(n);

    for(int i=0;i<m;i++){
        // Input: a sign_a b sign_b
        // sign=1 means positive, sign=-1 means negative
        int a, sa, b, sb;
        cin >> a >> sa >> b >> sb;
        a--; b--;
        // Literal: positive(sa==1) = 2*a, negative(sa==-1) = 2*a+1
        int la = (sa == 1) ? 2*a : 2*a+1;
        int lb = (sb == 1) ? 2*b : 2*b+1;
        sat.addOr(la, lb);
    }

    if(sat.solve()){
        cout << "SATISFIABLE" << nl;
        for(int i=0;i<n;i++){
            cout << "x" << i+1 << " = " << (sat.assignment[i] ? "true" : "false") << nl;
        }
    } else {
        cout << "UNSATISFIABLE" << nl;
    }
}

/*
Input: 1\n3 3\n1 1 2 1\n1 -1 3 1\n2 -1 3 -1
Clause 1: (x1 OR x2), Clause 2: (¬x1 OR x3), Clause 3: (¬x2 OR ¬x3)
Output: SATISFIABLE with some valid assignment
*/

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin>>TC;
    while(TC--) solve();
}

