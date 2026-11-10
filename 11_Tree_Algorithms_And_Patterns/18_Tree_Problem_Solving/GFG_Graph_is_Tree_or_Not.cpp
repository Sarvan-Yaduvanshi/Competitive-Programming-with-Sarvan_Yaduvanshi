/*
Author: Sarvan Yaduvanshi
Created : 2026-11-09 21:11:01
*/

/*
 * ============================================================================
 *  Graph is Tree or Not
 * ============================================================================
 *  Platform   : GeeksforGeeks
 *  Problem No : N/A (GFG has no number)
 *  Difficulty : Medium
 *  Topics     : Graph, Depth First Search, Breadth First Search,
 *               Union Find, Data Structures
 *  Companies  : Amazon, Microsoft, Flipkart, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given an undirected graph which consists of n nodes (numbered from 0 to
 *  n-1) and m edges. Return true if the graph is a tree, else return false.
 *
 *  Note: The input graph can have self-loops and multiple edges.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *            0
 *           / \
 *          1---2
 *               \
 *                3
 *
 *      Edges : 0-1, 0-2, 1-2, 2-3     (0-1-2 forms a triangle)
 *
 *  Input  : n = 4, m = 4, edges = [[0, 1], [0, 2], [1, 2], [2, 3]]
 *  Output : false
 *  Explanation: The graph contains a cycle, therefore it is not a tree.
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      0 --- 1 --- 2 --- 3
 *
 *      Edges : 0-1, 1-2, 2-3
 *
 *  Input  : n = 4, m = 3, edges = [[0, 1], [1, 2], [2, 3]]
 *  Output : true
 *  Explanation: Every node is connected and the graph has no cycles, so it
 *               is a tree.
 *
 * ----------------------------------------------------------------------------
 *  Tree Rule (a graph is a tree when BOTH are true):
 *      1. It is CONNECTED (all n nodes reachable from one node).
 *      2. It has NO CYCLE.
 *
 *      Shortcut: connected AND m == n - 1  ==>  tree.
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - 1 <= n <= 2 * 10^5
 *      - 0 <= m <= 2 * 10^5
 *      - edges.size() = m
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

// Function to check if a given undirected graph is a tree
static bool isTree(const int vertices, const int edges, const vector<pair<int, int>>& edgeList){
	// Case 1: Tree must have exactly N-1 edges
	if (edges != vertices - 1)
		return false;

	// Convert edge list to adjacency list
	vector<vector<int>> adj(vertices);
	for (const auto& edge : edgeList){
		auto [u, v] = edge;
		// Convert 1 -based indexing to 0-based indexing for internal representation
		u--; v--;
		// Avoid self-loops
		if (u == v)
			return false;

		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	// Case 2: Check if the graph is connected using BFS
	vector<bool> visited(vertices, false); // Track visited nodes
	queue<int> q;
	q.push(0);

	// Mark the first node as visited
	visited[0] = true;
	int edgeCount = 1; // Count the number of visited nodes

	while (!q.empty()){
		const int node = q.front();
		q.pop();

		// Visit all neighbors of the current node
		for (const int neighbor : adj[node]){
			// If the neighbor hasn't been visited, mark it and add to the queue
			if (!visited[neighbor]){
				visited[neighbor] = true;
				edgeCount++;
				q.push(neighbor);
			}
		}
	}

	// if edgeCount == vertices, then the graph is connected and has no cycles, hence it's a tree
	return edgeCount == vertices;
}
static void solve(){
	int vectices, edges;
	cin >> vectices >> edges;

	vector<pair<int, int>> edgeList;
	for (int i = 0; i < edges; i++){
		int u, v;
		cin >> u >> v;
		edgeList.emplace_back(u, v);
	}

	const bool ans = isTree(vectices, edges, edgeList);
	if (ans)
        cout << "Graph is a tree" << "\n";
    else
        cout << "Graph is NOT a tree" << "\n";
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}