/*
Author: Sarvan Yaduvanshi
Created : 2026-11-03 23:03:27
*/

/*
 * ============================================================================
 *  102. Binary Tree Level Order Traversal
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 102
 *  Difficulty : Medium
 *  Topics     : Tree, Breadth-First Search, Binary Tree
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given the root of a binary tree, return the level order traversal of its
 *  nodes' values. (i.e., from left to right, level by level).
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *          3
 *         / \
 *        9   20
 *           /  \
 *          15   7
 *
 *  Input  : root = [3,9,20,null,null,15,7]
 *  Output : [[3],[9,20],[15,7]]
 *  Explanation: Level 0 has 3. Level 1 has 9 and 20, left to right.
 *               Level 2 has 15 and 7.
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      1
 *
 *  Input  : root = [1]
 *  Output : [[1]]
 *
 * ----------------------------------------------------------------------------
 *  Example 3:
 *
 *      (empty tree)
 *
 *  Input  : root = []
 *  Output : []
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of nodes in the tree is in the range [0, 2000].
 *      - -1000 <= Node.val <= 1000
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

class Solution{
public:
	// 1. Standard Level-by-Level BFS (Returns 2D vector grouped by levels)
	// Time Complexity: O(n) - Each node is processed once.
	// Space Complexity: O(n) - The queue can hold up to n/2 nodes in the worst case (for a complete binary tree).
	static vector<vector<int>> levelOrderOrBFS(TreeNode* root) {
		vector<vector<int>> ans;

		// Edge case: empty tree
		if (root == nullptr)
			return ans;

		// Use queue for BFS traversal(queue properties: FIFO, first in first out)
		queue<TreeNode*> q;
		q.push(root); // Step 1: Push Level 0 (Root) into the FIFO queue

		// Step 2: Process each level until the queue is empty
		while (!q.empty()){
			// Step 2: Take a snapshot of how many nodes are in the current level
			size_t level_size = q.size();
			vector<int> current_level;
			current_level.reserve(level_size);

			// Step 3: Process ONLY the nodes belonging to the current level
			for (int i = 0; i < level_size; i++){
				TreeNode* current_node = q.front(); // Get the front node in the queue (FIFO)
				q.pop(); // Remove the front node from the queue after processing

				// Step 4: Add the current node's value to the current level's result
				current_level.emplace_back(current_node->val);

				// Step 5: Push left children to the BACK of the queue for the next level
				if (current_node->left != nullptr)
					q.push(current_node->left);

				// Step 6: Push right children to the BACK of the queue for the next level
				if (current_node->right != nullptr)
					q.push(current_node->right);
			}

			// Step 7: Current level is completely finished; store it!
			ans.emplace_back(current_level);
		}

		return ans;
	}

	// Alternative approach: DFS with depth tracking (not implemented here)
	static vector<vector<int>> levelOrderOrDFS(TreeNode* root) {
		vector<vector<int>> ans;

		if (root == nullptr)
			return ans;

		// Lambda function for DFS traversal
		auto dfs = [&](auto&& self, TreeNode* node, int depth) -> void {
			// Base case: if the node is null, return
			if (node == nullptr)
				return;

			// If this is the first time visiting this depth, create a new level
			if (depth == ans.size())
				ans.emplace_back();

			// Add the current node's value to the corresponding depth level
			ans[depth].emplace_back(node->val);

			// Recursively visit left and right children
			if (node->left != nullptr)
				self(self, node->left, depth + 1);
			if (node->right != nullptr)
				self(self, node->right, depth + 1);
		};

		dfs(dfs, root, 0);
		return ans;
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
	TreeVisualization::printTree(root); // Visualize the binary tree structure

	// Perform BFS Level Order Traversal
	vector<vector<int>> bfs_result = Solution::levelOrderOrBFS(root);
	cout << "BFS Level Order Traversal (grouped by levels):\n[";
	for (size_t i = 0; i < bfs_result.size(); ++i){
		cout << "[";
		for (size_t j = 0; j < bfs_result[i].size(); ++j){
			cout << bfs_result[i][j];
			if (j < bfs_result[i].size() - 1)
				cout << " ";
		}
		cout << "]";
		if (i < bfs_result.size() - 1)
			cout << ", ";
	}
	cout << "]\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

	solve();

    return 0;
}
