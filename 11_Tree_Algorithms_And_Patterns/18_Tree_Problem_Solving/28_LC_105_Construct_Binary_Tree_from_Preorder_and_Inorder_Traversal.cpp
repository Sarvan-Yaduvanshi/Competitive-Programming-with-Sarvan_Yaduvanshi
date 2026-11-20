/*
Author: Sarvan Yaduvanshi
Created : 2026-11-15 17:44:40
*/

/*
 * ============================================================================
 *  105. Construct Binary Tree from Preorder and Inorder Traversal
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 105
 *  Difficulty : Medium
 *  Topics     : Array, Hash Table, Divide and Conquer, Tree, Binary Tree
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Uber
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given two integer arrays preorder and inorder where preorder is the
 *  preorder traversal of a binary tree and inorder is the inorder traversal
 *  of the same tree, construct and return the binary tree.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      preorder : [3, 9, 20, 15, 7]
 *      inorder  : [9, 3, 15, 20, 7]
 *
 *      Built tree:
 *
 *                3
 *               / \
 *              9   20
 *                 /  \
 *                15   7
 *
 *      How it splits:
 *          preorder[0] = 3 is the ROOT.
 *          In inorder, 3 sits at index 1.
 *              Left of it  : [9]         -> left subtree (1 node)
 *              Right of it : [15, 20, 7] -> right subtree (3 nodes)
 *
 *  Input  : preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
 *  Output : [3,9,20,null,null,15,7]
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      preorder : [-1]
 *      inorder  : [-1]
 *
 *      Built tree:
 *
 *          -1
 *
 *  Input  : preorder = [-1], inorder = [-1]
 *  Output : [-1]
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - 1 <= preorder.length <= 3000
 *      - inorder.length == preorder.length
 *      - -3000 <= preorder[i], inorder[i] <= 3000
 *      - preorder and inorder consist of unique values.
 *      - Each value of inorder also appears in preorder.
 *      - preorder is guaranteed to be the preorder traversal of the tree.
 *      - inorder is guaranteed to be the inorder traversal of the tree.
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
	static TreeNode* buildTree(const vector<int>& preorder, const vector<int>& inorder) {
		const int n = inorder.size();
		unordered_map<int, int> in_position;
		in_position.reserve(n);
		for (int i = 0; i < n; i++)
			in_position[inorder[i]] = i;

		int posistion_index = 0;

		auto dfs = [&](auto&& self, int inStart, int inEnd) -> TreeNode* {
			if (inStart > inEnd)
				return nullptr;

			const int rootVal = preorder[posistion_index++];
			TreeNode* root = new TreeNode(rootVal);
			const int inRoot = in_position[rootVal];

			root->left = self(self, inStart, inRoot - 1);
			root->right = self(self, inRoot + 1, inEnd);

			return root;
		};

		return dfs(dfs, 0, n - 1);
	}

};

static void solve(){
	int n, m;
	cout << "Enter number of nodes in preorder tree: ";
	cin >> n;

	vector<int> preorder(n);
	cout << "Enter the values of the nodes (space-separated): ";
	for (int& val : preorder)
		cin >> val;

	cout << "Enter number of nodes in inorder tree: ";
	cin >> m;
	vector<int> inorder(m);
	cout << "Enter the values of the nodes (space-separated): ";
	for (int& val : inorder)
		cin >> val;

	// Build Binary Tree from Preorder and Inorder Traversal
	TreeNode* root_combined = Solution::buildTree(preorder, inorder);
	cout << "Constructed Binary Tree from Preorder and Inorder Traversal:" << endl;
	TreeVisualization::printTree(root_combined);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}