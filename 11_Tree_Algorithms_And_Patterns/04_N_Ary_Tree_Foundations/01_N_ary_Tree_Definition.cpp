/*
===============================================================================
                 N-ARY TREE DEFINITION AND FOUNDATIONS
                         Zero to Competitive Programming
===============================================================================

CONTENTS
--------
1. What is a tree and what is an N-ary tree?
2. Vocabulary, invariants, and formulas
3. Representations used in contests
4. Building a tree from parent input
5. DFS and BFS traversals with dry runs
6. Height, depth, subtree size, leaves, and level statistics
7. Tree DP: the general postorder pattern
8. LCA, distance, path queries, and binary lifting
9. Rerooting DP and Euler tour techniques
10. Advanced patterns: diameter, hashing, serialization, and heavy-light ideas
11. Complexity, pitfalls, and a contest checklist

-------------------------------------------------------------------------------
1) DEFINITION
-------------------------------------------------------------------------------

A tree is a connected, undirected graph with no cycle. An N-ary tree is a
rooted tree in which every node has at most N children. "N-ary" describes the
maximum number of children; it does not mean that every node must have exactly
N children. A node may have zero, one, or N children.

Example (N = 3):

                              1
                         /    |    \
                        2     3     4
                      / | \         |
                     5  6  7        8

The root is 1. Children(1) = [2, 3, 4], Children(2) = [5, 6, 7], and
Children(3) = Children(4) = empty (except that 4 has child 8).

In an unrooted tree there is no special root. Once a root is selected, every
edge is viewed as parent -> child. The same undirected tree can therefore have
different parent/child relationships for different roots.

Important distinction:
  * A general tree is usually represented with adjacency lists.
  * A rooted N-ary tree is usually represented by children lists.
  * A binary tree is the special case where each node has at most two children.

Typical node definition:

    struct Node {
        int value;
        vector<Node*> child;
    };

For competitive programming, nodes are more often indexed from 1 to n:

    vector<vector<int>> children(n + 1);
    vector<int> value(n + 1);

The indexed representation is faster to input, simpler for DP, and avoids
manual memory management. For an undirected input use:

    vector<vector<int>> graph(n + 1);
    graph[u].push_back(v);
    graph[v].push_back(u);

-------------------------------------------------------------------------------
2) VOCABULARY AND INVARIANTS
-------------------------------------------------------------------------------

* Root: the selected node at the top; its parent is absent.
* Parent(v): the node directly above v; parent(root) = 0 or -1.
* Child: a node directly below its parent.
* Sibling: nodes having the same parent.
* Leaf: a node with no children.
* Internal node: a node with at least one child.
* Ancestor of v: v itself, its parent, grandparent, and so on.
* Descendant of v: v's children and all nodes below them.
* Depth(v): number of edges from the root to v; depth(root) = 0.
* Height(v): maximum number of edges from v down to a leaf.
* Subtree(v): v and every descendant of v.
* Level d: all nodes whose depth is d.
* Degree in an undirected tree: number of incident edges.
* Children count: degree(v), except the root, whose children count is degree(root).

For n nodes:
  * Number of edges = n - 1.
  * There is exactly one simple path between any two nodes.
  * A tree is connected and acyclic.
  * Sum of undirected degrees = 2(n - 1).
  * Every non-root node has exactly one parent.
  * The sum of all children counts = n - 1.

If a rooted tree has n nodes and k leaves, then:
  * Every node except the root contributes one parent edge.
  * leafCount can be found by children[v].empty().

Height convention warning:
  * Edge-height: leaf height = 0.
  * Node-height: leaf height = 1.
Always check which convention the problem statement uses.

-------------------------------------------------------------------------------
3) REPRESENTATIONS
-------------------------------------------------------------------------------

A) Explicit node objects
------------------------
Useful when values and pointers are part of the problem API.

    struct Node {
        int val;
        vector<Node*> children;
    };

Pros: natural recursive code and direct subtree manipulation.
Cons: allocation overhead, pointer lifetime issues, and slower cache behavior.

B) Children adjacency list
--------------------------
If parent of every node is known:

    for (int v = 2; v <= n; ++v) {
        int p;
        cin >> p;
        children[p].push_back(v);
    }

The input order is not necessarily important unless the problem defines an
ordered tree. In an ordered tree, children[p] order must be preserved. In an
unordered tree, sorting children can be useful for canonical forms.

C) Undirected adjacency list
----------------------------
For edges (u, v), add both directions. Root the tree with DFS/BFS:

    parent[root] = 0;
    stack<int> st;
    st.push(root);
    while (!st.empty()) {
        int v = st.top();
        st.pop();
        for (int to : graph[v]) {
            if (to == parent[v]) continue;
            parent[to] = v;
            depth[to] = depth[v] + 1;
            st.push(to);
        }
    }

Do not use only "visited[to]" as a replacement for careful rooting when later
logic needs parent, depth, or child order. Store those arrays explicitly.

-------------------------------------------------------------------------------
4) BUILDING AND ROOTING: DRY RUN
-------------------------------------------------------------------------------

Suppose n = 8 and the undirected edges are:
  1-2, 1-3, 1-4, 2-5, 2-6, 2-7, 4-8

Root at 1. A DFS/BFS discovers:
  parent:  parent[1]=0, parent[2]=1, parent[3]=1, parent[4]=1,
           parent[5]=2, parent[6]=2, parent[7]=2, parent[8]=4
  depth:   depth[1]=0, depth[2..4]=1, depth[5..7]=2, depth[8]=2

The rooted children lists become:
  children[1] = [2, 3, 4]
  children[2] = [5, 6, 7]
  children[4] = [8]

For an input containing parent[v] for v = 2..n, the root is the only node
whose parent is absent (or 0). If arbitrary parent order is supplied, first
store parents, find the root, and then build children.

Validation in a debugging build:
  * Count exactly n - 1 edges.
  * Every non-root parent is in [1, n].
  * DFS visits n nodes.
  * No node is its own parent.
  * An undirected input must not contain a cycle.

-------------------------------------------------------------------------------
5) TRAVERSALS
-------------------------------------------------------------------------------

PREORDER: visit v before all children.
    preorder(v):
        process(v)
        for child in children[v]:
            preorder(child)

For the example tree, preorder is:
  1, 2, 5, 6, 7, 3, 4, 8

POSTORDER: visit all children before v.
    postorder(v):
        for child in children[v]:
            postorder(child)
        process(v)

Postorder is:
  5, 6, 7, 2, 3, 8, 4, 1

Postorder is the default traversal for subtree DP because every child's answer
is ready before the parent's answer is computed.

LEVEL ORDER (BFS): process nodes by nondecreasing depth.
    queue.push(root)
    while queue is not empty:
        v = queue.front(); queue.pop()
        process(v)
        for child in children[v]:
            queue.push(child)

For the example:
  level 0: [1]
  level 1: [2, 3, 4]
  level 2: [5, 6, 7, 8]

Iterative DFS is safer than recursive DFS when n can be 2e5 or more. A stack
frame can store (v, parent, nextChildIndex) to simulate recursive postorder:
  1. Push (root, 0).
  2. If nextChildIndex is not exhausted, push the next child.
  3. Otherwise process v and pop it.

Every node and edge is examined O(1) times:
  Time = O(n), recursive auxiliary space = O(height),
  iterative stack/queue space = O(n) in the worst case.

-------------------------------------------------------------------------------
6) BASIC QUERIES: RECURRENCES AND DRY RUNS
-------------------------------------------------------------------------------

SUBTREE SIZE
------------
  size(v) = 1 + sum(size(c)) for every child c of v.

Dry run:
  size(5)=size(6)=size(7)=size(3)=size(8)=1
  size(2)=1+1+1+1=4
  size(4)=1+1=2
  size(1)=1+4+1+2=8

HEIGHT (edge convention)
------------------------
  height(v) = 0                              if v is a leaf
  height(v) = 1 + max(height(c))              otherwise

Dry run:
  height(2)=1, height(4)=1, height(1)=2.

DEPTH AND MAXIMUM DEPTH
-----------------------
  depth[root] = 0
  depth[child] = depth[parent] + 1
  treeHeight = max(depth[v])

LEAF COUNT
----------
  leafCount(v) = 1 if children[v] is empty
                 sum(leafCount(c)) otherwise

SUBTREE SUM / MIN / MAX
-----------------------
Replace the size identity with the required associative operation:
  sum(v) = value[v] + sum(sum(c))
  min(v) = min(value[v], min(min(c)))
  max(v) = max(value[v], max(max(c)))

Use long long for sums unless the constraints prove int is safe.

LEVEL STATISTICS
----------------
BFS naturally computes:
  * number of nodes at each depth,
  * sum/min/max at each depth,
  * widest level,
  * distance from root.

At each BFS layer, record queue.size() before popping. That value is the
current level width. To compute the sum of values at a level, process exactly
that many nodes before starting the next level.

-------------------------------------------------------------------------------
7) THE GENERAL TREE-DP PATTERN
-------------------------------------------------------------------------------

Most rooted N-ary tree problems reduce to:

    solve(v):
        initialize answer for v
        for c in children[v]:
            childAnswer = solve(c)
            merge childAnswer into answer
        finalize answer for v
        return answer for the parent

The key question is: "What is the smallest information the parent needs from
this child?" Returning an entire subtree is usually unnecessary.

Example: maximum root-to-leaf sum
  bestDown(v) = value[v]                                  (leaf)
  bestDown(v) = value[v] + max(bestDown(c))                otherwise

Example: maximum independent set (choose no adjacent nodes)
  dp[v][1] = value[v] + sum(dp[c][0])
  dp[v][0] = sum(max(dp[c][0], dp[c][1]))

Example: minimum vertex cover
  cover[v][1] = 1 + sum(min(cover[c][0], cover[c][1]))
  cover[v][0] = sum(cover[c][1])

Example: number of colorings with K colors
  If v has color x, every child may use any color except x:
  ways[v][x] = product over c of
                (sum over y != x of ways[c][y])

Example: longest downward path satisfying a property:
  Return the best valid downward length. Reset/stop the recurrence when a
  child violates the property.

MERGING CHILD STATES
--------------------
If a node combines frequency maps, sets, or DP tables from children:
  * small-to-large merging reduces repeated work;
  * always merge the smaller container into the larger one;
  * typical complexity is O(n log n) for map/set merging (with assumptions
    about the container and operation).

For values in a bounded alphabet, vectors are often faster than maps. For
large values, coordinate compression may make vectors possible.

-------------------------------------------------------------------------------
8) LCA, DISTANCE, AND PATH QUERIES
-------------------------------------------------------------------------------

For two nodes u and v in a rooted tree:
  LCA(u, v) = their lowest common ancestor.
  distance(u, v) = depth[u] + depth[v] - 2 * depth[LCA(u, v)].

Small constraints: ancestor climbing
  while depth[u] > depth[v], move u = parent[u].
  Then move u and v upward together until u == v.
  Complexity per query: O(height).

Binary lifting (large constraints):
  up[j][v] = the 2^j-th ancestor of v.
  up[0][v] = parent[v]
  up[j][v] = up[j-1][up[j-1][v]]

Build in O(n log n). To lift v by k, inspect bits of k:
  for j = 0..LOG-1:
      if (k >> j) & 1: v = up[j][v]

LCA query:
  1. Lift the deeper node to the same depth.
  2. If nodes are equal, return it.
  3. For j from LOG-1 down to 0, if up[j][u] != up[j][v], lift both.
  4. Return parent[u].

Complexity: O(log n) per LCA/distance query and O(n log n) memory.
Choose LOG so that 2^LOG > maximum possible height.

PATH AGGREGATES WITH BINARY LIFTING
-----------------------------------
Store an aggregate along each jump as well as the ancestor:
  jumpValue[j][v] = aggregate on the path from v to up[j][v].

For sum, min, max, xor, or any associative operation, combine the selected
jumps while lifting. For non-commutative operations, preserve path direction
and store both upward and downward order if necessary.

-------------------------------------------------------------------------------
9) EULER TOUR AND SUBTREE INTERVALS
-------------------------------------------------------------------------------

Run DFS and record:
  tin[v]  = time when v is entered
  tout[v] = time after all descendants are processed

With the half-open interval [tin[v], tout[v]):
  u is in subtree(v) exactly when
      tin[v] <= tin[u] && tout[u] <= tout[v].

The subtree of v becomes one contiguous range in Euler order. Therefore:
  * subtree sum: range sum query;
  * subtree add: range add;
  * subtree minimum/maximum: range query;
  * subtree updates + point queries: Fenwick tree or segment tree.

For a node-weighted tree:
  euler[tin[v]] = value[v].

For edge weights, attach the weight of edge(parent[v], v) to tin[v]; the root
gets the identity value. Be careful not to count the LCA edge incorrectly.

An Euler tour is not the same as the full walk that writes a vertex on every
entry and exit. For subtree intervals, tin/tout entry times are sufficient.

-------------------------------------------------------------------------------
10) REROOTING DP
-------------------------------------------------------------------------------

Some questions ask for the answer for every possible root. A first DFS computes
the answer inside each subtree; a second DFS transfers the answer from parent
to child after removing the child's contribution and adding the outside part.

Classic example: sum of distances from every node to all other nodes.

First pass from arbitrary root r:
  sub[v] = subtree size
  down[v] = sum of distances from v to nodes in subtree(v)
  down[v] = sum(down[c] + sub[c])

At the root:
  answer[r] = down[r]

Transfer across edge v -> c:
  answer[c] = answer[v] + n - 2 * sub[c]

Why? Nodes in c's subtree become one edge closer (sub[c] nodes), while all
other nodes become one edge farther (n - sub[c] nodes).

Rerooting checklist:
  1. Define the answer for one root.
  2. Compute child/subtree contributions.
  3. Derive the exact transfer formula for one edge.
  4. Visit children in a second DFS.
  5. Confirm whether the state is node-weighted or edge-weighted.

-------------------------------------------------------------------------------
11) DIAMETER AND PATH DP
-------------------------------------------------------------------------------

The diameter is the maximum distance between any two nodes. At node v, a
diameter passing through v can use the two longest downward child paths:
  candidate(v) = best1 + best2
where each child path length includes the edge v -> child.

Postorder state:
  down(v) = longest downward path starting at v.
  Update a global answer with the two largest child values.

For the example:
  at node 2, child lengths are 1, 1, 1, so candidate = 2;
  at node 1, downward lengths through 2 and 4 are 2 and 2, so candidate = 4;
  one diameter is 5 -> 2 -> 1 -> 4 -> 8, length 4.

The two-sweep method also works for an unweighted tree:
  1. BFS/DFS from any node a, find a farthest node b.
  2. BFS/DFS from b; the farthest distance is the diameter.

For weighted trees with nonnegative edge weights, use weighted distances. For
general negative weights, use a DP formulation rather than assuming a sweep.

-------------------------------------------------------------------------------
12) CANONICAL FORM, ISOMORPHISM, AND HASHING
-------------------------------------------------------------------------------

Ordered N-ary trees: child order matters. Serialize recursively:
  serial(v) = "(" + value[v] + serial(c1) + ... + serial(ck) + ")"

Unordered N-ary trees: child order does not matter. Compute child signatures,
sort them, and assign an interned ID:
  signature(v) = sorted list of signature(child)
  id(v) = map[signature(v)]

Two rooted unordered trees are isomorphic exactly when their root signatures
match. Sorting child signatures costs O(sum degree(v) log degree(v)), usually
O(n log n) in the worst case.

For probabilistic hashing, combine child hashes after sorting. Use two moduli
or 64-bit mixing when collision risk matters. For a proof-level solution,
intern exact sorted vectors instead of relying only on a hash.

Serialization must include boundaries. Concatenating values without delimiters
can make different trees look identical (for example [1, 23] and [12, 3]).

-------------------------------------------------------------------------------
13) ADVANCED CONTEST PATTERNS
-------------------------------------------------------------------------------

* Centroid decomposition: repeatedly find a centroid, solve paths through it,
  and recurse on remaining components. Useful for global distance queries.
* Heavy-light decomposition: split each root-to-node path into O(log n)
  heavy segments, then answer path queries with a segment tree.
* DSU on tree (sack): answer all subtree frequency queries in about O(n log n)
  by retaining the largest child's data structure.
* Virtual tree: for a small set of marked nodes, sort by tin and add LCAs to
  build a compressed tree; useful for many queries on selected nodes.
* Tree difference arrays: mark endpoints and LCA to count how many paths pass
  through each node or edge.
* Centroid finding: move to a child with subtree size greater than n/2 until
  no such child exists.
* Constraint DP: cap dimensions when only values up to K matter; never create
  an O(n^2) state accidentally for a chain of n nodes.

The common design process is always:
  root the tree -> choose traversal order -> define a minimal state ->
  merge child states -> prove the transition -> analyze worst-case complexity.

-------------------------------------------------------------------------------
14) PITFALLS AND FINAL CHECKLIST
-------------------------------------------------------------------------------

1. In an undirected adjacency list, skip parent (or use visited); otherwise
   DFS immediately walks back and recurses forever.
2. A chain of n nodes has recursion depth n. Use iterative traversal or increase
   stack only when the platform safely permits it.
3. Distances use edges, not vertices, unless the statement says otherwise.
4. The root has no parent. Use 0 or -1 consistently and size arrays safely.
5. Do not assume input children are sorted unless order is meaningful.
6. Use long long for path sums, DP values, and weighted distances.
7. For multiple test cases, clear every adjacency and DP array.
8. In binary lifting, never dereference an invalid ancestor index.
9. For rerooting, verify the transfer formula on a three-node chain.
10. For unordered-tree isomorphism, sort child signatures before combining.
11. Check whether a query is node-based or edge-based at the LCA.
12. State time and memory complexity for the worst shape: a star and a chain.

QUICK COMPLEXITY TABLE
----------------------
  Rooting / DFS / BFS                         O(n)       O(n)
  Subtree DP                                  O(n)       O(n)
  LCA with binary lifting (preprocess)        O(n log n) O(n log n)
  One LCA query                               O(log n)   O(1)
  Euler tour + Fenwick/segment tree           O(n log n) O(n)
  Rerooting DP                                O(n)       O(n)
  Small-to-large map merging                  about O(n log n)
  Heavy-light path query                      O(log^2 n) typical

The most reusable N-ary-tree insight is not a particular traversal. It is the
ability to turn a recursive subtree answer into a compact state that can be
merged at the parent. Once that state is correct, the tree shape and branching
factor usually affect only the implementation details, not the recurrence.
===============================================================================
*/

int main(){
  return 0;
}
