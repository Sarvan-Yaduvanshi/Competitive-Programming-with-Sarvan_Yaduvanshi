/*
Author: Sarvan Yaduvanshi
Created : 2026-11-08 05:29:56
*/

/*
 * ============================================================================
 *  559. Maximum Depth of N-ary Tree
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 559
 *  Difficulty : Easy
 *  Topics     : Tree, Depth-First Search, Breadth-First Search
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Uber
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given a n-ary tree, find its maximum depth.
 *
 *  The maximum depth is the number of nodes along the longest path from the
 *  root node down to the farthest leaf node.
 *
 *  Nary-Tree input serialization is represented in their level order
 *  traversal, each group of children is separated by the null value
 *  (See examples).
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *                  1                Level 1 (depth 1)
 *                / | \
 *               3  2  4             Level 2 (depth 2)
 *              / \
 *             5   6                 Level 3 (depth 3)
 *
 *      Longest path : 1 -> 3 -> 5   (3 nodes)
 *
 *  Input  : root = [1,null,3,2,4,null,5,6]
 *  Output : 3
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *                       1                      depth 1
 *                 /   /   \   \
 *                2   3     4   5               depth 2
 *                   / \    |   / \
 *                  6   7   8   9  10           depth 3
 *                      |   |   |
 *                     11  12  13               depth 4
 *                      |
 *                     14                       depth 5
 *
 *      Longest path : 1 -> 3 -> 7 -> 11 -> 14   (5 nodes)
 *
 *  Input  : root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,
 *                   null,11,null,12,null,13,null,null,14]
 *  Output : 5
 *
 * ----------------------------------------------------------------------------
 *  How to read the serialization (Example 1):
 *
 *      [1, null, 3, 2, 4, null, 5, 6]
 *       ^   ^    ^------^   ^    ^--^
 *       |   |    children   |    children of 3
 *       |   |    of 1       |
 *       |   |               end of the group of 1
 *       |   end of root (root has no siblings)
 *       root
 *
 *      Rule: after the root, each group of children is closed by null.
 *            Groups come in level order: group of 1, then group of 3,
 *            then group of 2, then group of 4, ...
 *            A node with no children gives an empty group (just null).
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The total number of nodes is in the range [0, 10^4].
 *      - The depth of the n-ary tree is less than or equal to 1000.
 * ============================================================================
 */

#include "../00_Tree_Utilities/03_NaryTree.h"
#include "../00_Tree_Utilities/04_PrintNaryTree.h"
/*
 * Definition for a Node.
 * class Node {
 * public:
 *     int val;
 *     vector<Node*> children;
 *
 *     Node() {}
 *
 *     Node(int _val) {
 *         val = _val;
 *     }
 *
 *     Node(int _val, vector<Node*> _children) {
 *         val = _val;
 *         children = _children;
 *     }
 * };
 */

class Solution {
public:
	// Approach 1: Use DFS to find the maximum depth of the N-ary tree
	static int maxDepthDFS(Node* root){
		// Base case: if the node is null, return depth 0
		if (root == nullptr)
			return 0;

		// Initialize maximum depth
		int max_depth = 0;

		// Recursively find the maximum depth among all children
		for (Node* child : root->children)
			max_depth = max(max_depth, maxDepthDFS(child));

		return max_depth + 1; // Add 1 for the current node
	}

	// Approach 2: Use BFS to find the maximum depth of the N-ary tree
	static int maxDepthBFS(Node* root){
		// Base case: if the node is null, return depth 0
		if (root == nullptr)
			return 0;

		queue<Node*> q;
		q.push(root);
		int depth = 0;

		// Perform level-order traversal
		while (!q.empty()){
			int size = q.size();
			for (int i = 0; i < size; ++i){
				Node* current = q.front();
				q.pop();

				// Add all children of the current node to the queue
				for (Node* child : current->children){
					if (child != nullptr)
						q.push(child);
				}
			}
			depth++; // Increment depth after processing each level
		}

		return depth;
	}

};

static void solve(){
	int n;
	cout << "Enter number of nodes in the tree: ";
	cin >> n;

	vector<int> values(n);
	cout << "Enter the values of the nodes (space-separated): ";
	for (int& val : values)
		cin >> val;

	// Build the N-ary tree from the level-order values and -1 separators
	Node* root = buildNaryTree(values);
	N_ary_TreeVisualization::printNAryTree<Node>(
		root,
		"N-ary Tree Visualization"
	);


	// Approach 1: Preorder Traversal using Recursion
	int depthDFS = Solution::maxDepthDFS(root);
	cout << "Maximum Depth (DFS): " << depthDFS << "\n";

	// Approach 2: Level Order Traversal using Queue
	const int depthBFS = Solution::maxDepthBFS(root);
	cout << "Maximum Depth (BFS): " << depthBFS << "\n";
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}