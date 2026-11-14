/*
Author: Sarvan Yaduvanshi
Created : 2026-11-14 12:09:32
*/

/*
 * ============================================================================
 *  513. Find Bottom Left Tree Value
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 513
 *  Difficulty : Medium
 *  Topics     : Tree, Depth-First Search, Breadth-First Search,
 *               Binary Tree
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  You are given the root of a binary tree.
 *
 *  Return the leftmost value in the last row of the tree.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *                2                Row 0
 *               / \
 *              1   3              Row 1  (last row)  <== leftmost is 1
 *
 *  Input  : root = [2,1,3]
 *  Output : 1
 *  Explanation: The last row is [1,3], so the leftmost value is 1.
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *                  1              Row 0
 *                /   \
 *               2     3           Row 1
 *              /     / \
 *             4     5   6         Row 2
 *                  /
 *                 7               Row 3  (last row)  <== only node 7
 *
 *  Input  : root = [1,2,3,4,null,5,6,null,null,7]
 *  Output : 7
 *  Explanation: The last row contains only the node 7.
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of nodes in the tree is in the range [1, 10^4].
 *      - -2^31 <= Node.val <= 2^31 - 1
 * ============================================================================
 */

#include "../00_Tree_Utilities/01_BinaryTree.h"
#include "../00_Tree_Utilities/02_Print_BinaryTree.h"

/*
 * Definition for a binary tree node.
 * struct TreeNode {
 *   int val;
 *   TreeNode *left;
 *   TreeNode *right;
 *   TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *   TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *   TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution {
public:
    // Approach 1: BFS (every level, keep track of the first node)
	// computing i = 0 for the first node in each level, and updating leftMostNode
	// Time Complexity: O(n), Space Complexity: O(n)
	static int findBottomLeftValueUseBFS(TreeNode* root){
		// Track the leftmost node value in the last row of the tree
		int leftMostNode = 0;
		queue<TreeNode*> q;
		q.push(root);

		while (!q.empty()){
			const size_t level_size = q.size();
			for (size_t i = 0; i < level_size; i++){
				const TreeNode* node = q.front();
				q.pop();

				// If this is the first node in the current level, update leftMostNode
				if (i == 0)
					leftMostNode = node->val;

				if (node->left != nullptr)
					q.push(node->left);

				if (node->right != nullptr)
					q.push(node->right);
			}
		}

		return leftMostNode;
	}

	// Approach 2: DFS (keep track of the depth and update leftMostNode when a new max depth is found)
	// Time Complexity: O(n), Space Complexity: O(h) where h is the height of the tree (due to recursion stack)
	static int findBottomLeftValueUseDFS(TreeNode* root){
		// Track the leftmost node value in the last row of the tree
		int leftMostNode = 0;
		int maxDepth = -1; // Initialize maxDepth to -1 so that the root node at depth 0 will be considered

		// Use a lambda function for DFS traversal
		auto dfs = [&](auto&& self, const TreeNode* node, const int depth) -> void{
			// If the node is null, return
			if (node == nullptr)
				return;

			// If we reach a new maximum depth, update leftMostNode and maxDepth
			if (depth > maxDepth){
				leftMostNode = node->val;
				maxDepth = depth;
			}

			self(self, node->left, depth + 1); // left subtree
			self(self, node->right, depth + 1); // right subtree
		};

		dfs(dfs, root, 0);
		return leftMostNode;
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

	TreeNode* root = buildTree(values);
	TreeVisualization::printTree(root);

	// Approach 1: BFS
	const int leftMostValueBFS = Solution::findBottomLeftValueUseBFS(root);
	cout << "Leftmost value in the last row (BFS): " << leftMostValueBFS << endl;

	// Approach 2: DFS
	const int leftMostValueDFS = Solution::findBottomLeftValueUseDFS(root);
	cout << "Leftmost value in the last row (DFS): " << leftMostValueDFS << endl;
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}