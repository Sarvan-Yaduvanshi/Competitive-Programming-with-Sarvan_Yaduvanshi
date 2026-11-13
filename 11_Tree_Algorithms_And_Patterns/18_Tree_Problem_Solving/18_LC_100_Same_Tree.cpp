/*
Author: Sarvan Yaduvanshi
Created : 2026-11-11 17:45:24
*/

/*
 * ============================================================================
 *  100. Same Tree
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 100
 *  Difficulty : Easy
 *  Topics     : Tree, Depth-First Search, Breadth-First Search,
 *               Binary Tree
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given the roots of two binary trees p and q, write a function to check
 *  if they are the same or not.
 *
 *  Two binary trees are considered the same if they are structurally
 *  identical, and the nodes have the same value.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      p:      1             q:      1
 *             / \                   / \
 *            2   3                 2   3
 *
 *      Same shape, same values.
 *
 *  Input  : p = [1,2,3], q = [1,2,3]
 *  Output : true
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      p:      1             q:      1
 *             /                       \
 *            2                         2
 *
 *      Node 2 is a LEFT child in p, but a RIGHT child in q.
 *
 *  Input  : p = [1,2], q = [1,null,2]
 *  Output : false
 *
 * ----------------------------------------------------------------------------
 *  Example 3:
 *
 *      p:      1             q:      1
 *             / \                   / \
 *            2   1                 1   2
 *
 *      Same shape, but the values on the left and right are swapped.
 *
 *  Input  : p = [1,2,1], q = [1,1,2]
 *  Output : false
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of nodes in both trees is in the range [0, 100].
 *      - -10^4 <= Node.val <= 10^4
 * ============================================================================
 */

#include "../00_Tree_Utilities/01_BinaryTree.h"
#include "../00_Tree_Utilities/02_Print_BinaryTree.h"

/*
 * Definition for a binary tree node.
 * struct TreeNode{
 *     int val;
 *     TreeNode* left;
 *     TreeNode* right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
 * };
 */
class Solution{
public:
	// Approach 1: Breadth-First Search (BFS) to check if two binary trees are the same
	static bool isSameTreeUseBFS(TreeNode* root1, TreeNode* root2){
		// check if both trees are empty or if one of them is empty
		if (root1 == nullptr || root2 == nullptr)
			return root1 == root2;

		// Use a queue to perform level-order traversal, storing pairs of nodes from both trees
		queue<pair<TreeNode*, TreeNode*>> q;
		q.emplace(root1, root2); // Add the root nodes of both trees to the queue

		while (!q.empty()){
			// Get the front pair of nodes from the queue
			auto [node1, node2] = q.front();
			q.pop();

			// Case 1: If the values of the nodes are different, the trees are not the same
			if (node1->val != node2->val)
				return false;

			// Case 2: If one of the left children is null and the other is not, the trees are not the same
			if ((node1->left == nullptr) != (node2->left == nullptr))
				return false;

			// Case 3: If one of the right children is null and the other is not, the trees are not the same
			if ((node1->right == nullptr) != (node2->right == nullptr))
				return false;

			// If both left children are not null, add them to the queue for further comparison
			if (node1->left != nullptr)
				q.emplace(node1->left, node2->left);

			// If both right children are not null, add them to the queue for further comparison
			if (node1->right != nullptr)
				q.emplace(node1->right, node2->right);
		}
		return true;
	}

	// Approach 2: Recursive Depth-First Search (DFS) to check if two binary trees are the same
	static bool isSameTreeUseDFS(TreeNode* root1, TreeNode* root2){
		// Base case: if both nodes are null, they are the same
		if (root1 == nullptr && root2 == nullptr)
			return true;

		// If one of the nodes is null and the other is not, they are not the same
		if (root1 == nullptr || root2 == nullptr)
			return false;

		// If the values of the nodes are different, they are not the same
		if (root1->val != root2->val)
			return false;

		// Recursively check the left and right subtrees
		return isSameTreeUseDFS(root1->left, root2->left) &&
			   isSameTreeUseDFS(root1->right, root2->right);
	}

	// Approach 3: Iterative Depth-First Search (DFS) using a stack to check if two binary trees are the same
	static bool isSameTreeUseIterativeDFS(TreeNode* root1, TreeNode* root2){
		// Use a stack to perform iterative DFS, storing pairs of nodes from both trees
		stack<pair<TreeNode*, TreeNode*>> s;
		s.emplace(root1, root2); // Add the root nodes of both trees to the stack

		while (!s.empty()){
			// Get the top pair of nodes from the stack
			auto [node1, node2] = s.top();
			s.pop();

			// Case 1: If both nodes are null, continue to the next iteration
			if (node1 == nullptr && node2 == nullptr)
				continue;

			// Case 2: If one of the nodes is null and the other is not, they are not the same
			if (node1 == nullptr || node2 == nullptr)
				return false;

			// Case 3: If the values of the nodes are different, they are not the same
			if (node1->val != node2->val)
				return false;

			// Add the right children so follow the order of left children first
			s.emplace(node1->right, node2->right);

			// Add the left children to the stack for further comparison
			s.emplace(node1->left, node2->left);
		}

		return true;
	}
};

static void solve(){
	int n;
	cout << "Enter number of nodes in the tree: ";
	cin >> n;

	vector<int> values1(n);
	cout << "Enter the values of the first tree's nodes (space-separated, use -1 for null): ";
	for (int& val : values1)
		cin >> val;

	vector<int> values2(n);
	cout << "Enter the values of the second tree's nodes (space-separated, use -1 for null): ";
    for (int& val : values2)
    	cin >> val;

	// Build the binary tree from the input values
	TreeNode* root = buildTree(values1);
	TreeNode* root2 = buildTree(values2);

	// Print the tree structure for visualization
    TreeVisualization::printTree(root);
	TreeVisualization::printTree(root2);

	// Approach 1: Check if the two trees are the same using BFS
	bool sameBFS = Solution::isSameTreeUseBFS(root, root2);
    cout << "Are the two trees the same (BFS)? " << (sameBFS ? "Yes" : "No") << "\n";

	// Approach 2: Check if the two trees are the same using DFS
	bool sameDFS = Solution::isSameTreeUseDFS(root, root2);
    cout << "Are the two trees the same (DFS)? " << (sameDFS ? "Yes" : "No") << "\n";

	// Approach 3: Check if the two trees are the same using Iterative DFS
    bool sameIterativeDFS = Solution::isSameTreeUseIterativeDFS(root, root2);
    cout << "Are the two trees the same (Iterative DFS)? " << (sameIterativeDFS ? "Yes" : "No") << "\n";
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}