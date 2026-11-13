/*
Author: Sarvan Yaduvanshi
Created : 2026-11-07 19:36:11
*/

/*
 * ============================================================================
 *  Sum of Binary Tree
 * ============================================================================
 *  Platform   : GeeksforGeeks
 *  Problem No : N/A (GFG has no number)
 *  Difficulty : Basic
 *  Topics     : Tree, Binary Tree, Data Structures
 *  Companies  : Amazon, Microsoft, Adobe, Flipkart
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given a binary tree, find the sum of values of all the nodes.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *                15               Level 0
 *              /    \
 *            10      20           Level 1
 *           /  \    /  \
 *          8   12  16   25        Level 2
 *
 *  Input  : root = [15, 10, 20, 8, 12, 16, 25]
 *  Output : 106
 *  Explanation: The sum of all the nodes is
 *               15 + 10 + 20 + 8 + 12 + 16 + 25 = 106.
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *              1                Level 0
 *             / \
 *            3   2              Level 1
 *
 *  Input  : root = [1, 3, 2]
 *  Output : 6
 *  Explanation: The sum of all the nodes is 1 + 2 + 3 = 6.
 *
 * ----------------------------------------------------------------------------
 *  Example 3:
 *
 *              1                Level 0
 *             /
 *            2                  Level 1
 *           /
 *          4                    Level 2
 *
 *  Input  : root = [1, 2, N, 4, N]
 *  Output : 7
 *  Explanation: The sum of all the nodes is 1 + 2 + 4 = 7.
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - 1 <= number of nodes <= 10^4
 *      - -10^5 <= Node data <= 10^5
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
	// Approach 1: Use DFS to calculate the sum of all nodes in the binary tree
	static int sumOfBinaryTreeDFS(const TreeNode* root){
		if (root == nullptr)
			return 0;

		// Recursively calculate the sum of left and right subtrees
		const int leftSum = sumOfBinaryTreeDFS(root->left);
		const int rightSum = sumOfBinaryTreeDFS(root->right);

		// Return the total sum including the current node's value
		return root->val + leftSum + rightSum;
	}

	// Approach 2: Use BFS to calculate the sum of all nodes in the binary tree
	static int sumOfBinaryTreeBFS(const TreeNode* root){
		if (root == nullptr)
			return 0;

		int totalSum = 0;
		queue<const TreeNode*> q;
		q.push(root);

		while (!q.empty()){
			const TreeNode* current = q.front();
			q.pop();

			// Add the current node's value to the total sum
			totalSum += current->val;

			// Enqueue left and right children if they exist
			if (current->left != nullptr)
				q.push(current->left);
			if (current->right != nullptr)
				q.push(current->right);
		}

		return totalSum;
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

	// Approach 1: Calculate the sum of the binary tree using DFS
	const int sumDFS = Solution::sumOfBinaryTreeDFS(root);
	cout << "Sum of Binary Tree (DFS): " << sumDFS << "\n";

	// Approach 2: Calculate the sum of the binary tree using BFS
	const int sumBFS = Solution::sumOfBinaryTreeBFS(root);
	cout << "Sum of Binary Tree (BFS): " << sumBFS << "\n";
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}