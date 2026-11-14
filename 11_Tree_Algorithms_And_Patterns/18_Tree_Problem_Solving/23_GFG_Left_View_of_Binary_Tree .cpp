/*
Author: Sarvan Yaduvanshi
Created : 2026-11-13 23:39:38
*/

/*
 * ============================================================================
 *  Left View of Binary Tree
 * ============================================================================
 *  Platform   : GeeksforGeeks
 *  Problem No : N/A (GFG has no number)
 *  Difficulty : Easy
 *  Topics     : Tree, Binary Tree, Data Structures
 *  Companies  : Amazon, Microsoft, Flipkart, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given the root of a binary tree. Return the left view of the binary tree.
 *  The left view of a binary tree is the set of nodes visible when the tree
 *  is viewed from the left side.
 *
 *  Note: If the tree is empty, return an empty list.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *                1                Level 0 : see 1
 *              /   \
 *             2     3             Level 1 : see 2
 *            / \
 *           4   5                 Level 2 : see 4
 *
 *      You stand on the left. At each level the LEFTMOST node is visible.
 *
 *  Input  : root = [1, 2, 3, 4, 5, N, N]
 *  Output : [1, 2, 4]
 *  Explanation: From the left side of the tree, only the nodes 1, 2, and 4
 *               are visible.
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *                1                Level 0 : see 1
 *              /   \
 *             2     3             Level 1 : see 2
 *                  /
 *                 4               Level 2 : see 4
 *                  \
 *                   5             Level 3 : see 5
 *
 *  Input  : root = [1, 2, 3, N, N, 4, N, N, 5, N, N]
 *  Output : [1, 2, 4, 5]
 *  Explanation: From the left side of the tree, only the nodes 1, 2, 4, and
 *               5 are visible.
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - 0 <= size of binary tree, Node.data <= 10^5
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
	// Approach 1: Calculate left side view using BFS
	// Left View of Binary Tree is the first node of each level in the tree.
	// Compute using i == 0 condition in BFS traversal.
	// Time Complexity  : O(n) || Space Complexity : O(n)
	static vector<int> leftSideViewBFS(TreeNode* root){
		vector<int> ans;

		// empty tree case
		if (root == nullptr)
			return ans;

		queue<TreeNode*> q;
		q.push(root);

		while (!q.empty()){
			const size_t level_size = q.size();
			for (size_t i = 0; i < level_size; i++){
				const TreeNode* node = q.front();
				q.pop();

				// If this is the first node of the current level, add it to the answer
				if (i == 0)
					ans.emplace_back(node->val);

				if (node->left != nullptr)
					q.push(node->left);

				if (node->right != nullptr)
					q.push(node->right);
			}
		}

		return ans;
	}

	// Approach 2: Calculate left side view using DFS
    // Left View of Binary Tree is the first node of each level in the tree.
    // Compute using depth-first search (DFS) traversal, prioritizing the left child first.
	// Time Complexity  : O(n) || Space Complexity : O(h) where h is the height of the tree
	static vector<int> leftSideViewDFS(const TreeNode* root){
		vector<int> ans;
		auto dfs = [&](auto&& self, const TreeNode* node, const int depth) -> void{
			// Base case: if the node is null, return
			if (node == nullptr)
				return;

			// If this is the first time we are visiting this depth, add the node's value to the answer
			if (depth == ans.size())
				ans.emplace_back(node->val);

			self(self, node->left, depth + 1);  // Prioritize left child first for left view
			self(self, node->right, depth + 1);  // Then visit right child
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

	// Approach 1: Calculate right side view using BFS
    const vector<int> leftSideViewBFS = Solution::leftSideViewBFS(root);
	cout << "Left Side View of Binary Tree (BFS): ";
	printOutput(leftSideViewBFS);

	// Approach 2: Calculate right side view using DFS
    const vector<int> leftSideViewDFS = Solution::leftSideViewDFS(root);
    cout << "Left Side View of Binary Tree (DFS): ";
	printOutput(leftSideViewDFS);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}