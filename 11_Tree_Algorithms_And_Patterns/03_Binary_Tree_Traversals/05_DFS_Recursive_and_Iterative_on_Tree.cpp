/*
╔══════════════════════════════════════════════════════════════════╗
║       01 — DFS ON TREES (Recursive & Iterative)                  ║
║       Zero to GM Level — Tree Traversals                         ║
╚══════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS
─────────────────
 1. DFS on Trees vs Graphs
 2. Recursive DFS (The Standard)
 3. Iterative DFS with Stack
 4. DFS Preorder & Postorder on General Trees
 5. Detailed Dry Run
 6. Complexity Analysis
 7. Code

═══════════════════════════════════════════════════════════════════
 1. DFS ON TREES vs GRAPHS
═══════════════════════════════════════════════════════════════════

 On GRAPHS: Need visited[] array to avoid infinite loops
 On TREES:  Just track PARENT — no visited[] needed!

 Why? Trees have no cycles. The only way to "go back" is
 through the parent edge. So just skip the parent.

 Pattern:
   void dfs(int v, int parent) {
       for (int u : adj[v]) {
           if (u == parent) continue;  // skip parent
           dfs(u, v);
       }
   }

 This is the #1 most important pattern in tree problems!

═══════════════════════════════════════════════════════════════════
 2. RECURSIVE DFS — THE STANDARD
═══════════════════════════════════════════════════════════════════

 Template:
   void dfs(int v, int par) {
       // PREORDER: process v BEFORE children
       cout << v << " ";

       for (int u : adj[v]) {
           if (u == par) continue;
           dfs(u, v);
       }

       // POSTORDER: process v AFTER children
   }

 Call: dfs(root, -1);

═══════════════════════════════════════════════════════════════════
 3. ITERATIVE DFS WITH STACK
═══════════════════════════════════════════════════════════════════

 When recursion depth might overflow (N > 10^5 or 10^6):

   stack<pair<int,int>> stk;  // (node, parent)
   stk.push({root, -1});
   while (!stk.empty()) {
       auto [v, par] = stk.top(); stk.pop();
       // process v
       for (int u : adj[v]) {
           if (u == par) continue;
           stk.push({u, v});
       }
   }

 ⚠️ NOTE: Iterative DFS visits nodes in REVERSE order compared
    to recursive DFS (because stack is LIFO). If order matters,
    reverse the neighbor list or use a different approach.

═══════════════════════════════════════════════════════════════════
 4. PREORDER vs POSTORDER ON GENERAL TREES
═══════════════════════════════════════════════════════════════════

 Tree:
            1
          / | \
         2  3  4
        / \
       5   6

 PREORDER (process node FIRST, then children):
   Visit 1 → Visit 2 → Visit 5 → Visit 6 → Visit 3 → Visit 4
   Output: 1 2 5 6 3 4

   Dry run:
     dfs(1, -1):
       print 1
       dfs(2, 1):
         print 2
         dfs(5, 2): print 5, no children
         dfs(6, 2): print 6, no children
       dfs(3, 1): print 3, no children
       dfs(4, 1): print 4, no children

 POSTORDER (process children FIRST, then node):
   Visit 5 → Visit 6 → Visit 2 → Visit 3 → Visit 4 → Visit 1
   Output: 5 6 2 3 4 1

   Dry run:
     dfs(1, -1):
       dfs(2, 1):
         dfs(5, 2): no children, print 5
         dfs(6, 2): no children, print 6
         print 2
       dfs(3, 1): no children, print 3
       dfs(4, 1): no children, print 4
       print 1

 🔑 KEY INSIGHT:
   Preorder: Node → Left subtree → Right subtree → ...
   Postorder: Left subtree → Right subtree → ... → Node
   Preorder is good for "top-down" processing (root first)
   Postorder is good for "bottom-up" processing (leaves first)

═══════════════════════════════════════════════════════════════════
 5. DETAILED DRY RUN
═══════════════════════════════════════════════════════════════════

 Tree:
              1
            /   \
           2     3
          / \   / \
         4   5 6   7

 adj[1]=[2,3], adj[2]=[1,4,5], adj[3]=[1,6,7]
 adj[4]=[2], adj[5]=[2], adj[6]=[3], adj[7]=[3]

 Recursive DFS from root=1, parent=-1:

 Call Stack Trace:
 ┌────────────────────────────────────────────────────────────┐
 │ dfs(1, -1)                                                 │
 │   Process 1 (preorder)                                     │
 │   Neighbors of 1: [2, 3]                                   │
 │     2 ≠ -1 → dfs(2, 1)                                     │
 │   ┌──────────────────────────────────────────────────────┐ │
 │   │ dfs(2, 1)                                            │ │
 │   │   Process 2 (preorder)                               │ │
 │   │   Neighbors of 2: [1, 4, 5]                          │ │
 │   │     1 == parent(1) → SKIP                            │ │
 │   │     4 ≠ 1 → dfs(4, 2)                                │ │
 │   │   ┌────────────────────────────────────────────────┐ │ │
 │   │   │ dfs(4, 2)                                      │ │ │
 │   │   │   Process 4 (preorder)                         │ │ │
 │   │   │   Neighbors of 4: [2]                          │ │ │
 │   │   │     2 == parent(2) → SKIP                      │ │ │
 │   │   │   Process 4 (postorder)                        │ │ │
 │   │   └────────────────────────────────────────────────┘ │ │
 │   │     5 ≠ 1 → dfs(5, 2)                                │ │
 │   │   ┌────────────────────────────────────────────────┐ │ │
 │   │   │ dfs(5, 2)                                      │ │ │
 │   │   │   Process 5 (preorder)                         │ │ │
 │   │   │   Neighbors of 5: [2]                          │ │ │
 │   │   │     2 == parent(2) → SKIP                      │ │ │
 │   │   │   Process 5 (postorder)                        │ │ │
 │   │   └────────────────────────────────────────────────┘ │ │
 │   │   Process 2 (postorder)                              │ │
 │   └──────────────────────────────────────────────────────┘ │
 │     3 ≠ -1 → dfs(3, 1)                                     │
 │   ┌──────────────────────────────────────────────────────┐ │
 │   │ dfs(3, 1)                                            │ │
 │   │   Process 3 (preorder)                               │ │
 │   │   Neighbors of 3: [1, 6, 7]                          │ │
 │   │     1 == parent(1) → SKIP                            │ │
 │   │     6 → dfs(6, 3): Process 6                         │ │
 │   │     7 → dfs(7, 3): Process 7                         │ │
 │   │   Process 3 (postorder)                              │ │
 │   └──────────────────────────────────────────────────────┘ │
 │   Process 1 (postorder)                                    │
 └────────────────────────────────────────────────────────────┘

 PREORDER:  1 2 4 5 3 6 7
 POSTORDER: 4 5 2 6 7 3 1

═══════════════════════════════════════════════════════════════════
 6. COMPLEXITY
═══════════════════════════════════════════════════════════════════

 ┌──────────────────────────┬────────────┬─────────────────────┐
 │ Operation                │ Time       │ Space               │
 ├──────────────────────────┼────────────┼─────────────────────┤
 │ Recursive DFS            │ O(N)       │ O(H) call stack     │
 │ Iterative DFS            │ O(N)       │ O(N) explicit stack │
 │ DFS on tree              │ O(N)       │ O(N) adj list       │
 └──────────────────────────┴────────────┴─────────────────────┘

 H = height of tree
 Best case H = O(log N) (balanced tree)
 Worst case H = O(N) (degenerate/skewed tree)

 ⚠️ If N > 10^5 or tree might be skewed → use ITERATIVE DFS!
    (Recursive DFS might cause stack overflow)

═══════════════════════════════════════════════════════════════════
 7. CODE
═══════════════════════════════════════════════════════════════════
*/


#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <iomanip>
#include <random>
#include <chrono>

using namespace std;

vector<vector<int>> adj; // declare adjacency list (2D vector)
vector<int> ans;

// METHOD 1: Recursive DFS (standard for tree problems)
void dfs(int currNode, int parent){
	// Add current node to traversal
	ans.push_back(currNode);

	// Visit all adjacent nodes
	for (int nbr : adj[currNode]){
		// Skip parent node to avoid going backward
		if (nbr == parent)
			continue;

		// DFS on child node
		dfs(nbr, currNode);
	}
}

vector<vector<int>> preorderResult, postorderResult;
void dfsRecursive(int v, int par) {
    preorderResult.pb(v);   // PREORDER: visit node first

    for (int u : adj[v]) {
        if (u == par) continue;  // skip parent (no visited[] needed!)
        dfsRecursive(u, v);
    }

    postorderResult.pb(v);  // POSTORDER: visit node after all children
}

// METHOD 2: Iterative DFS with Stack (for large trees)
vector<int> iterativeDFS(int root, int n) {
    vector<int> order;
    stack<pair<int, int>> st; // (node, parent)
    st.push({root, -1});
    vector<bool> visited(n + 1, false);

    while (!st.empty()) {
        auto [v, par] = st.top();
        st.pop();

        if (visited[v]) continue;
        visited[v] = true;
        order.pb(v);

        // Push in reverse order so first neighbor is processed first
        for (int i = adj[v].size() - 1; i >= 0; i--) {
            int u = adj[v][i];
            if (u == par || visited[u]) continue;
            st.push({u, v});
        }
    }
    return order;
}

// ═══════════════════════════════════════════════════════════════
// METHOD 3: DFS with subtree size computation (very common!)
// ═══════════════════════════════════════════════════════════════
vector<int> subSize;
void dfsSubtreeSize(int currNode, int parent) {
    subSize[currNode] = 1;
    for (int nbr : adj[currNode]) {
        if (nbr == parent) continue;
        dfsSubtreeSize(nbr, currNode);
        subSize[currNode] += subSize[nbr];
    }
}

void solve() {
    int n; cin >> n;

    adj.assign(n + 1, {});
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Recursive DFS
    preorderResult.clear();
    postorderResult.clear();
    dfsRecursive(1, -1);

    cout << "Recursive DFS:" << nl;
    cout << "  Preorder:  ";
    for (int x : preorderResult) cout << x << " ";
    cout << nl;
    cout << "  Postorder: ";
    for (int x : postorderResult) cout << x << " ";
    cout << nl;

    // Iterative DFS
    vec<int> iterOrder = iterativeDFS(1, n);
    cout << nl << "Iterative DFS: ";
    for (int x : iterOrder) cout << x << " ";
    cout << nl;

    // Subtree sizes
    subSize.assign(n + 1, 0);
    dfsSubtreeSize(1, -1);
    cout << nl << "Subtree sizes:" << nl;
    for (int i = 1; i <= n; i++) {
        cout << "  sub[" << i << "] = " << subSize[i] << nl;
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
═══════════════════════════════════════════════════════════════════
 SAMPLE INPUT / OUTPUT
═══════════════════════════════════════════════════════════════════

Input:
1
7
1 2
1 3
2 4
2 5
3 6
3 7

Tree:
         1
        / \
       2   3
      / \ / \
     4  5 6  7

Output:
Recursive DFS:
  Preorder:  1 2 4 5 3 6 7
  Postorder: 4 5 2 6 7 3 1

Iterative DFS: 1 2 4 5 3 6 7

Subtree sizes:
  sub[1] = 7
  sub[2] = 3
  sub[3] = 3
  sub[4] = 1
  sub[5] = 1
  sub[6] = 1
  sub[7] = 1

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ DFS on tree: skip parent, no visited[] needed
 ✅ Pattern: dfs(v, par) { for u in adj[v]: if u≠par: dfs(u,v) }
 ✅ Preorder: process before children (top-down)
 ✅ Postorder: process after children (bottom-up)
 ✅ Use iterative DFS for N > 10^5 to avoid stack overflow
 ✅ Subtree size: sub[v] = 1 + Σ sub[child] (most common DFS usage)
═══════════════════════════════════════════════════════════════════
*/
