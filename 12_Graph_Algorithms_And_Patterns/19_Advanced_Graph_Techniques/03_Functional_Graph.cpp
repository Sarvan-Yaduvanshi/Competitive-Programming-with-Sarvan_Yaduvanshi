/*
╔══════════════════════════════════════════════════════════════════╗
║         FUNCTIONAL GRAPH / SUCCESSOR GRAPH                      ║
║         Every vertex has exactly one outgoing edge              ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

A FUNCTIONAL GRAPH (successor graph) has exactly one outgoing edge
from every vertex: f(x) = next vertex after x.

Structure: Each connected component has EXACTLY ONE CYCLE
with trees hanging off cycle vertices (rho-shaped ρ).

KEY OPERATIONS:
  1. Find k-th successor of x: f^k(x) → Binary Lifting O(log k)
  2. Find cycle: Floyd's tortoise & hare O(n)
  3. Find cycle length, tail length

═══════════════════════════════════════════════════════════════════
FLOYD'S CYCLE DETECTION (Tortoise and Hare)
═══════════════════════════════════════════════════════════════════

  slow = f(slow)        — moves 1 step
  fast = f(f(fast))     — moves 2 steps
  They meet inside cycle after O(λ + μ) steps
  (μ = tail length, λ = cycle length)

  To find cycle start: reset slow to start, move both 1 step
  To find cycle length: from meeting point, count steps around

═══════════════════════════════════════════════════════════════════
BINARY LIFTING for k-th successor
═══════════════════════════════════════════════════════════════════

  up[v][0] = f(v)                  — 1st successor
  up[v][j] = up[up[v][j-1]][j-1]  — 2^j-th successor

  f^k(v) = jump through set bits of k

  Precompute: O(n log k)    Query: O(log k)

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
#define nl '\n'

const int LOG = 30;

void solve() {
    int n; i64 q;
    cin >> n >> q;

    vec<int> succ(n);
    for (int i = 0; i < n; i++) { cin >> succ[i]; succ[i]--; }

    // Binary lifting table
    vvec<int> up(LOG, vec<int>(n));
    for (int i = 0; i < n; i++) up[0][i] = succ[i];
    for (int j = 1; j < LOG; j++) {
        for (int i = 0; i < n; i++) {
            up[j][i] = up[j-1][up[j-1][i]];
        }
    }

    // Answer queries: k-th successor of vertex v
    while (q--) {
        int v; i64 k;
        cin >> v >> k; v--;

        for (int j = 0; j < LOG; j++) {
            if (k & (1LL << j)) v = up[j][v];
        }

        cout << v + 1 << nl;
    }
}

// Floyd's cycle detection on functional graph
pair<int,int> findCycle(vec<int>& succ, int start) {
    int slow = start, fast = start;

    // Phase 1: Find meeting point
    do {
        slow = succ[slow];
        fast = succ[succ[fast]];
    } while (slow != fast);

    // Phase 2: Find cycle start (tail length μ)
    int mu = 0;
    slow = start;
    while (slow != fast) {
        slow = succ[slow];
        fast = succ[fast];
        mu++;
    }

    // Phase 3: Find cycle length λ
    int lam = 1;
    fast = succ[slow];
    while (slow != fast) {
        fast = succ[fast];
        lam++;
    }

    return {mu, lam}; // tail length, cycle length
}

/*
Input: 1\n5 3\n2 3 4 5 3\n1 1\n1 4\n3 100
(successor: 1→2, 2→3, 3→4, 4→5, 5→3, cycle: 3→4→5→3)
Queries: f^1(1)=2, f^4(1)=5, f^100(3)=?
*/

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC; while (TC--) solve();
}

