/*
Author: Sarvan Yaduvanshi
Created : 2026-11-15 17:45:57
*/

/*
 * ============================================================================
 *  106. Construct Binary Tree from Inorder and Postorder Traversal
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 106
 *  Difficulty : Medium
 *  Topics     : Array, Hash Table, Divide and Conquer, Tree, Binary Tree
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Uber
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given two integer arrays inorder and postorder where inorder is the
 *  inorder traversal of a binary tree and postorder is the postorder
 *  traversal of the same tree, construct and return the binary tree.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      inorder   : [9, 3, 15, 20, 7]
 *      postorder : [9, 15, 7, 20, 3]
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
 *          postorder LAST item = 3 is the ROOT.
 *          In inorder, 3 sits at index 1.
 *              Left of it  : [9]         -> left subtree (1 node)
 *              Right of it : [15, 20, 7] -> right subtree (3 nodes)
 *
 *  Input  : inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
 *  Output : [3,9,20,null,null,15,7]
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      inorder   : [-1]
 *      postorder : [-1]
 *
 *      Built tree:
 *
 *          -1
 *
 *  Input  : inorder = [-1], postorder = [-1]
 *  Output : [-1]
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - 1 <= inorder.length <= 3000
 *      - postorder.length == inorder.length
 *      - -3000 <= inorder[i], postorder[i] <= 3000
 *      - inorder and postorder consist of unique values.
 *      - Each value of postorder also appears in inorder.
 *      - inorder is guaranteed to be the inorder traversal of the tree.
 *      - postorder is guaranteed to be the postorder traversal of the tree.
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
	static TreeNode* buildTree(const vector<int>& inorder, const vector<int>& postorder){
		const int n = inorder.size();
		unordered_map<int, int> in_position;
		in_position.reserve(n);
		for (int i = 0; i < n; i++)
			in_position[inorder[i]] = i;

		int position_index = n - 1;

		auto dfs = [&](auto&& self, int inStart, int inEnd) -> TreeNode* {
			if (inStart > inEnd)
				return nullptr;

			const int rootVal = postorder[position_index--];
			TreeNode* root = new TreeNode(rootVal);
			const int inRoot = in_position[rootVal];

			root->right = self(self, inRoot + 1, inEnd);
			root->left = self(self, inStart, inRoot - 1);

			return root;
		};

		return dfs(dfs, 0, n - 1);
	}

};

static void solve(){
	int n, m;

	cout << "Enter number of nodes in inorder tree: ";
	cin >> n;
	vector<int> inorder(n);
	cout << "Enter the values of the nodes (space-separated): ";
	for (int& val : inorder)
		cin >> val;

	cout << "Enter number of nodes in postorder tree: ";
	cin >> m;
	vector<int> postorder(m);
	cout << "Enter the values of the nodes (space-separated): ";
	for (int& val : postorder)
		cin >> val;

	// Build Binary Tree from Preorder and Inorder Traversal
	TreeNode* root_combined = Solution::buildTree(inorder, postorder);
	cout << "Constructed Binary Tree from Inorder and Postorder Traversal:" << endl;
	TreeVisualization::printTree(root_combined);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}