/*
Author: Sarvan Yaduvanshi
Created : 2026-11-08 04:13:35
*/

/*
 * ============================================================================
 *  104. Maximum Depth of Binary Tree
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 104
 *  Difficulty : Easy
 *  Topics     : Tree, Depth-First Search, Breadth-First Search,
 *               Binary Tree
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Uber
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given the root of a binary tree, return its maximum depth.
 *
 *  A binary tree's maximum depth is the number of nodes along the longest
 *  path from the root node down to the farthest leaf node.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *                3                Level 1 (depth 1)
 *               / \
 *              9   20             Level 2 (depth 2)
 *                 /  \
 *                15   7           Level 3 (depth 3)
 *
 *      Longest path : 3 -> 20 -> 15   (3 nodes)
 *
 *  Input  : root = [3,9,20,null,null,15,7]
 *  Output : 3
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      1                          depth 1
 *       \
 *        2                        depth 2
 *
 *      Longest path : 1 -> 2   (2 nodes)
 *
 *  Input  : root = [1,null,2]
 *  Output : 2
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of nodes in the tree is in the range [0, 10^4].
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

class Solution {
public:
	// Approach 1: Recursive DFS
	// Time Complexity: O(N) - where N is the number of nodes in the tree
	// Space Complexity: O(H) - where H is the height of the tree (due to recursion stack)
	static int maxDepthUseDFS(const TreeNode* root){
		// Base case: if the current node is null, return 0
		if (root == nullptr)
			return 0;

		// Step 1: calculate the left and right subtree depths recursively
		const int leftDepth = maxDepthUseDFS(root->left);
		const int rightDepth = maxDepthUseDFS(root->right);

		// Step 2: if either left or right subtree is missing, so return max(leftDepth, rightDepth) + 1
		return 1 + max(leftDepth, rightDepth);
	}

	// Approach 2: Iterative BFS
	// Time Complexity: O(N) - where N is the number of nodes in the tree
	// Space Complexity: O(W) - where W is the maximum width of the tree (due to the queue)
	static int maxDepthUseBFS(TreeNode* root){
		// Base case: if the tree is empty, return 0
		if (root == nullptr)
			return 0;

		queue<TreeNode*> q;
		q.emplace(root);
		int maxDepth = 0; // Start with depth 0 for the root node

		while (!q.empty()){
			const size_t levelSize = q.size(); // Number of nodes at the current level
			for (size_t i = 0; i < levelSize; ++i){
				const TreeNode* current = q.front();
				q.pop();

				// Add the left child to the queue if it exists
				if (current->left != nullptr)
					q.push(current->left);

				// Add the right child to the queue if it exists
				if (current->right != nullptr)
					q.push(current->right);
			}
			maxDepth++; // Increment depth after processing the current level
		}

		return maxDepth; // This line is theoretically unreachable due to the return in the loop
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

	// Approach 1: Using DFS
	const int maxDepthDFS = Solution::maxDepthUseDFS(root);
	cout << "Maximum Depth (DFS): " << maxDepthDFS << "\n";

	// Approach 2: Using BFS
	const int maxDepthBFS = Solution::maxDepthUseBFS(root);
	cout << "Maximum Depth (BFS): " << maxDepthBFS << "\n";
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}