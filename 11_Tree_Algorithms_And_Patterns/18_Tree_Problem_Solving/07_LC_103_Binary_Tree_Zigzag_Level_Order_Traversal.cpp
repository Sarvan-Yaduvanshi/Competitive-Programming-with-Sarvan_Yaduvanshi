/*
Author: Sarvan Yaduvanshi
Created : 2026-11-04 07:44:14
*/

/*
 * ============================================================================
 *  103. Binary Tree Zigzag Level Order Traversal
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 103
 *  Difficulty : Medium
 *  Topics     : Tree, Breadth-First Search, Binary Tree
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Uber
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given the root of a binary tree, return the zigzag level order traversal
 *  of its nodes' values. (i.e., from left to right, then right to left for
 *  the next level and alternate between).
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *                3                Level 0  : left -> right  : [3]
 *               / \
 *              9   20             Level 1  : right -> left  : [20, 9]
 *                 /  \
 *                15   7           Level 2  : left -> right  : [15, 7]
 *
 *  Input  : root = [3,9,20,null,null,15,7]
 *  Output : [[3],[20,9],[15,7]]
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      1                         Level 0  : left -> right  : [1]
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
 *      - -100 <= Node.val <= 100
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
	// Approach 1: Level-order traversal(BFS) with directional alternation using a queue
	static vector<vector<int>> zigzagLevelOrder(TreeNode* root){
		vector<vector<int>> ans;

		// Handle empty tree case
		if (root == nullptr)
			return {};

		queue<TreeNode*> q;
		q.emplace(root);

		// Level 0 starts Left -> Right
		bool left_to_right = true;

		while (!q.empty()){
			const size_t level_size = q.size();
			// Pre-allocate exact size so we can place elements at `idx` directly
			vector<int> current_level(level_size);

			// Process all nodes at the current level
			for (size_t i = 0; i < level_size; i++){
				TreeNode* current_node = q.front();
				q.pop();

				// Direct index calculation: front-to-back or back-to-front
				const size_t idx = left_to_right ? i : (level_size - i - 1);
				current_level[idx] = current_node->val;

				// Explore the left child for the next level
				if (current_node->left != nullptr)
					q.emplace(current_node->left);

				// Explore the right child for the next level
				if (current_node->right != nullptr)
					q.emplace(current_node->right);
			}

			// Add the current level's values to the final answer
			ans.emplace_back(std::move(current_level));
			left_to_right = !left_to_right; // Flip direction for the next level!
		}

		return ans;
	}

	// Approach 2: Depth-first search (DFS) with reversal
	static vector<vector<int>> zigzagLevelOrderUseDFS(TreeNode* root){
		vector<vector<int>> ans;

		if (root == nullptr)
			return {};

		// Lambda function for DFS traversal
		auto dfs = [&](auto&& self, TreeNode* node, const int depth) -> void{
			// Base case: if the current node is null, return
			if (node == nullptr)
				return;

			// If we are at a new depth level, add a new vector to hold values for this level
			if (depth == ans.size())
				ans.emplace_back();

			// Add the current node's value to the corresponding depth level
			ans[depth].emplace_back(node->val);

			// Recursively traverse the left and right children, increasing the depth
			self(self, node->left, depth + 1);
			self(self, node->right, depth + 1);
		};

		// Start DFS traversal from the root at depth 0
		dfs(dfs, root, 0);

		// Reverse odd-depth levels
		for (int i = 1; i < ans.size(); i += 2)
			ranges::reverse(ans[i]);

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

	// Approach 1: Level Order Traversal (BFS) with Reversal
	const vector<vector<int>> bfs_result = Solution::zigzagLevelOrder(root);
	cout << "BFS Zigzag Level Order Traversal (grouped by levels):\n[";
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
	const vector<vector<int>> resultDFS = Solution::zigzagLevelOrderUseDFS(root);
	cout << "DFS Zigzag Level Order Traversal (grouped by levels):\n[";
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