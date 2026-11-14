/*
Author: Sarvan Yaduvanshi
Created : 2026-11-14 12:32:23
*/

/*
 * ============================================================================
 *  515. Find Largest Value in Each Tree Row
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 515
 *  Difficulty : Medium
 *  Topics     : Tree, Depth-First Search, Breadth-First Search,
 *               Binary Tree
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given the root of a binary tree, return an array of the largest value in
 *  each row of the tree (0-indexed).
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *                1                Row 0 : max = 1
 *              /   \
 *             3     2             Row 1 : max = 3
 *            / \     \
 *           5   3     9           Row 2 : max = 9
 *
 *  Input  : root = [1,3,2,5,3,null,9]
 *  Output : [1,3,9]
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *                1                Row 0 : max = 1
 *               / \
 *              2   3              Row 1 : max = 3
 *
 *  Input  : root = [1,2,3]
 *  Output : [1,3]
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of nodes in the tree will be in the range [0, 10^4].
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
	// Approach 1: Breadth-First Search (BFS)
	// Idea: Traverse the tree level by level and find the maximum value in each level.
	// Time Complexity: O(n), where n is the number of nodes in the tree.
	// Space Complexity: O(m), where m is the maximum number of nodes at any level in the tree.
	static vector<int> largestValues(TreeNode* root) {
		vector<int> ans;

		// empty tree case
		if (root == nullptr)
			return ans;

		queue<TreeNode*> q;
		q.push(root);

		while (!q.empty()) {
			const size_t level_size = q.size();
			int maxVal = INT_MIN; // Track the maximum value in the current level
			for (size_t i = 0; i < level_size; i++) {
				const TreeNode* node = q.front();
				q.pop();

				// Update the maximum value for the current level
				maxVal = max(maxVal, node->val);

				if (node->left != nullptr)
					q.push(node->left);

				if (node->right != nullptr)
					q.push(node->right);
			}

			// Update the answer with the maximum value found in the current level
			ans.emplace_back(maxVal);
		}

		return ans;
	}

	// Approach 2: Depth-First Search (DFS)
	// Idea: Traverse the tree using DFS and keep track of the maximum value at each depth.
	//		1) First time we reach a depth, we add the value to the answer.
    //		2) If we reach the same depth again, we update the maximum value
	// Time Complexity: O(n), where n is the number of nodes in the tree.
    // Space Complexity: O(h), where h is the height of the tree (due to
	static vector<int> largestValuesUseDFS(const TreeNode* root) {
		vector<int> ans;

		// empty tree case
		if (root == nullptr)
			return {};

		// Lambda function for DFS traversal
		auto dfs = [&](auto&& self, const TreeNode* node,
									const int depth) -> void {

			// Base case: If the node is null, return
			if (node == nullptr)
				return;

			// Case 1: If we reach a new depth, add the value to the answer
			if (depth == ans.size())
				ans.emplace_back(node->val);
			// Case 2: If we have already seen this depth, update the maximum value
			else
				ans[depth] = max(ans[depth], node->val);

			self(self, node->left, depth + 1); // left subtree
			self(self, node->right, depth + 1); // right subtree
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
	TreeVisualization::printTree(root);

	// Approach 1: BFS
	const vector<int> largestValuesBFS = Solution::largestValues(root);
    cout << "Largest values in each tree row (BFS): ";
	printOutput(largestValuesBFS);

	// Approach 2: DFS
	const vector<int> largestValuesDFS = Solution::largestValuesUseDFS(root);
	cout << "Largest values in each tree row (DFS): ";
	printOutput(largestValuesDFS);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}