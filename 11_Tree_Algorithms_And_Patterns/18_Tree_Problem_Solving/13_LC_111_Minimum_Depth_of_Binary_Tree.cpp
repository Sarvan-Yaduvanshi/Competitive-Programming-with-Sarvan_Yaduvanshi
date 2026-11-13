/*
Author: Sarvan Yaduvanshi
Created : 2026-11-08 04:13:35
*/

/*
 * ============================================================================
 *  111. Minimum Depth of Binary Tree
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 111
 *  Difficulty : Easy
 *  Topics     : Tree, Depth-First Search, Breadth-First Search,
 *               Binary Tree
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Uber
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given a binary tree, find its minimum depth.
 *
 *  The minimum depth is the number of nodes along the shortest path from
 *  the root node down to the nearest leaf node.
 *
 *  Note: A leaf is a node with no children.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *                3                Level 1 (depth 1)
 *               / \
 *              9   20             Level 2 (depth 2)  <== 9 is a leaf
 *                 /  \
 *                15   7           Level 3 (depth 3)
 *
 *      Shortest path : 3 -> 9     (2 nodes)
 *
 *  Input  : root = [3,9,20,null,null,15,7]
 *  Output : 2
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      2                          depth 1
 *       \
 *        3                        depth 2
 *         \
 *          4                      depth 3
 *           \
 *            5                    depth 4
 *             \
 *              6                  depth 5  <== only leaf
 *
 *      Shortest path : 2 -> 3 -> 4 -> 5 -> 6     (5 nodes)
 *
 *  Input  : root = [2,null,3,null,4,null,5,null,6]
 *  Output : 5
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of nodes in the tree is in the range [0, 10^5].
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

class Solution {
public:
	// Approach 1: Recursive DFS
	// Time Complexity: O(N) - where N is the number of nodes in the tree
	// Space Complexity: O(H) - where H is the height of the tree (due to recursion stack)
	static int minDepthUseDFS(const TreeNode* root){
		// Base case: if the current node is null, return 0
		if (root == nullptr)
			return 0;

		// Step 1: calculate the left and right subtree depths recursively
		const int leftDepth = minDepthUseDFS(root->left);
		const int rightDepth = minDepthUseDFS(root->right);

		// Step 2: if either left or right subtree is missing, so return max(leftDepth, rightDepth) + 1
		if (root->left == nullptr || root->right == nullptr)
			return max(leftDepth, rightDepth) + 1;

		// Step 3: if both left and right subtrees are present, return min(leftDepth, rightDepth) + 1
		return min(leftDepth, rightDepth) + 1;
	}

	// Approach 2: Iterative BFS
	// Time Complexity: O(N) - where N is the number of nodes in the tree
	// Space Complexity: O(W) - where W is the maximum width of the tree (due to the queue)
	static int minDepthUseBFS(TreeNode* root){
		// Base case: if the tree is empty, return 0
		if (root == nullptr)
			return 0;

		queue<TreeNode*> q;
		q.emplace(root);
		int depth = 1; // Start with depth 1 for the root node

		while (!q.empty()){
			const size_t levelSize = q.size(); // Number of nodes at the current level
			for (size_t i = 0; i < levelSize; ++i){
				const TreeNode* current = q.front();
				q.pop();

				// If we reach a leaf node, return the current depth
				if (current->left == nullptr && current->right == nullptr)
					return depth;

				// Add the left child to the queue if it exists
				if (current->left != nullptr)
					q.push(current->left);

				// Add the right child to the queue if it exists
				if (current->right != nullptr)
					q.push(current->right);
			}
			++depth; // Increment depth after processing the current level
		}

		return depth; // This line is theoretically unreachable due to the return in the loop
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

	// Approach 1: Using DFS
	const int minDepthDFS = Solution::minDepthUseDFS(root);
	cout << "Minimum Depth (DFS): " << minDepthDFS << "\n";

	// Approach 2: Using BFS
	const int minDepthBFS = Solution::minDepthUseBFS(root);
	cout << "Minimum Depth (BFS): " << minDepthBFS << "\n";
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}