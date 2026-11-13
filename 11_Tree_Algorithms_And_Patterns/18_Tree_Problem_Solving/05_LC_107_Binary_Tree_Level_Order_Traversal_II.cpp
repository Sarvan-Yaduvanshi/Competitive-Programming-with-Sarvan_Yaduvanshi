/*
Author: Sarvan Yaduvanshi
Created : 2026-11-03 23:22:16
*/

/*
 * ============================================================================
 *  107. Binary Tree Level Order Traversal II
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 107
 *  Difficulty : Medium
 *  Topics     : Tree, Breadth-First Search, Binary Tree
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given the root of a binary tree, return the bottom-up level order
 *  traversal of its nodes' values. (i.e., from left to right, level by level
 *  from leaf to root).
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
 *  Output : [[15,7],[9,20],[3]]
 *  Explanation: Levels top-down are [3], [9,20], [15,7]. Reverse the order
 *               of levels: deepest level first, root level last. Inside each
 *               level, still left to right.
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
	// Approach: Level Order Traversal (BFS) with Reversal
	// Time Complexity: O(n) - Each node is visited once
	// Space Complexity: O(n) - The queue can hold up to n/2 nodes in the worst case (for a complete binary tree)
	static vector<vector<int>> levelOrderBottom(TreeNode* root){
		vector<vector<int>> ans;

		// Edge case: empty tree
		if (root == nullptr)
			return ans;

		// Use a queue to perform level order traversal (BFS)
		queue<TreeNode*> q;
		q.push(root); // Add Level 0 (root) to the queue

		// Process each level of the tree
		while (!q.empty()){
			// Get the number of nodes at the current level
			const size_t level_size = q.size();
			vector<int> current_level;
			current_level.reserve(level_size); // Reserve space for efficiency

			// Process all nodes at the current level
			for (size_t i = 0; i < level_size; i++){
				TreeNode* current_node = q.front(); // Get the front node in the queue
				q.pop(); // Remove it from the queue

				// Add the current node's value to the current level's list
				current_level.emplace_back(current_node->val);

				// Add the left child to the queue if it exists
				if (current_node->left != nullptr)
					q.push(current_node->left);

				// Add the right child to the queue if it exists
				if (current_node->right != nullptr)
					q.push(current_node->right);
			}

			// Add the current level's values to the answer list
			ans.emplace_back(std::move(current_level));
		}

		// Reverse the order of levels to get bottom-up traversal
		ranges::reverse(ans);
		return ans;
	}

	// Approach 2: Using Depth-First Search (DFS) with Level Tracking
	// Time Complexity: O(n) - Each node is visited once
	// Space Complexity: O(n) - The recursion stack can hold up to n nodes in the worst case (for a skewed tree)
	static vector<vector<int>> levelOrderBottomUseDFS(TreeNode* root){
		vector<vector<int>> ans;

		// Edge case: empty tree
		if (root == nullptr)
			return ans;

		// Lambda function for DFS traversal
		auto dfs = [&](auto&& self, TreeNode* node, const int depth) -> void{
			// Base case: if the current node is null, return
			if (node == nullptr)
				return;

			// If we reach a new depth level, add a new vector for that level
			if (depth == ans.size())
				ans.emplace_back();

			// Add the current node's value to the corresponding depth level
			ans[depth].emplace_back(node->val);

			// Recursively call DFS for the left and right children, increasing the depth by 1
			self(self, node->left, depth + 1); // left child
			self(self, node->right, depth + 1); // right child
		};

		dfs(dfs, root, 0);
		ranges::reverse(ans); // Reverse the order of levels to get bottom-up traversal
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
	TreeVisualization::printTree(root);

	// Approach 1: Level Order Traversal (BFS) with Reversal
	vector<vector<int>> bfs_result = Solution::levelOrderBottom(root);
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

	// Approach 2: Using Depth-First Search (DFS) with Level Tracking
	vector<vector<int>> resultDFS = Solution::levelOrderBottomUseDFS(root);
	cout << "DFS Level Order Traversal (grouped by levels):\n[";
	for (size_t i = 0; i < resultDFS.size(); ++i){
		cout << "[";
        for (size_t j = 0; j < resultDFS[i].size(); ++j){
            cout << resultDFS[i][j];
            if (j < resultDFS[i].size() - 1)
                cout << " ";
        }
        cout << "]";
        if (i < resultDFS.size() - 1)
            cout << ", ";
	}
	cout << "]\n";
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}