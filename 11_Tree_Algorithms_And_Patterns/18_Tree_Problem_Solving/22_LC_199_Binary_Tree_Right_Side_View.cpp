/*
Author: Sarvan Yaduvanshi
Created : 2026-11-13 23:39:38
*/

/*
 * ============================================================================
 *  199. Binary Tree Right Side View
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 199
 *  Difficulty : Medium
 *  Topics     : Tree, Depth-First Search, Breadth-First Search,
 *               Binary Tree
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Uber
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given the root of a binary tree, imagine yourself standing on the right
 *  side of it, return the values of the nodes you can see ordered from top
 *  to bottom.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *                1                Level 0 : see 1
 *              /   \
 *             2     3             Level 1 : see 3
 *              \     \
 *               5     4           Level 2 : see 4
 *
 *      You stand on the right. At each level the RIGHTMOST node is visible.
 *
 *  Input  : root = [1,2,3,null,5,null,4]
 *  Output : [1,3,4]
 *  Explanation: Level 0 shows 1, level 1 shows 3 (it hides 2), level 2
 *               shows 4 (it hides 5).
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *                1                Level 0 : see 1
 *              /   \
 *             2     3             Level 1 : see 3
 *            /
 *           4                     Level 2 : see 4  (3 has no children)
 *          /
 *         5                       Level 3 : see 5
 *
 *  Input  : root = [1,2,3,4,null,null,null,5]
 *  Output : [1,3,4,5]
 *  Explanation: Node 3 is a leaf, so the view below it comes from the LEFT
 *               side. Level 2 shows 4 and level 3 shows 5, because nothing
 *               on the right hides them.
 *
 * ----------------------------------------------------------------------------
 *  Example 3:
 *
 *      1                          Level 0 : see 1
 *       \
 *        3                        Level 1 : see 3
 *
 *  Input  : root = [1,null,3]
 *  Output : [1,3]
 *
 * ----------------------------------------------------------------------------
 *  Example 4:
 *
 *      (empty tree)
 *
 *  Input  : root = []
 *  Output : []
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of nodes in the tree is in the range [0, 100].
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
	// Approach 1: Calculate right side view using BFS
	// Riight View of Binary Tree is the last node of each level in the tree.
	// Compute using i == level_size - 1 condition in BFS traversal.
	// Time Complexity  : O(n) || Space Complexity : O(n)
	static vector<int> rightSideViewBFS(TreeNode* root){
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

				// If this is the last node of the current level, add it to the answer
				if (i == level_size - 1)
					ans.emplace_back(node->val);

				if (node->left != nullptr)
					q.push(node->left);

				if (node->right != nullptr)
					q.push(node->right);
			}
		}

		return ans;
	}

	// Approach 2: Calculate right side view using DFS
    // Right View of Binary Tree is the last node of each level in the tree.
	// Compute using depth-first search (DFS) traversal, prioritizing the right child first.
	// Time Complexity  : O(n) || Space Complexity : O(h) where h is the height of the tree
	static vector<int> rightSideViewDFS(const TreeNode* root){
		vector<int> ans;
		auto dfs = [&](auto&& self, const TreeNode* node, const int depth) -> void{
			// Base case: if the node is null, return
			if (node == nullptr)
				return;

			// If this is the first time we are visiting this depth, add the node's value to the answer
			if (depth == ans.size())
				ans.emplace_back(node->val);

			self(self, node->right, depth + 1); // right child first priority
			self(self, node->left, depth + 1); // left child second priority
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
    const vector<int> rightSideViewBFS = Solution::rightSideViewBFS(root);
	cout << "Right Side View of Binary Tree (BFS): ";
	printOutput(rightSideViewBFS);

	// Approach 2: Calculate right side view using DFS
    const vector<int> rightSideViewDFS = Solution::rightSideViewDFS(root);
    cout << "Right Side View of Binary Tree (DFS): ";
	printOutput(rightSideViewDFS);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}