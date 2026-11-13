/*
Author: Sarvan Yaduvanshi
Created : 2026-11-03 22:59:41
*/

/*
 * ============================================================================
 *  94. Binary Tree Inorder Traversal
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 94
 *  Difficulty : Easy
 *  Topics     : Stack, Tree, Depth-First Search, Binary Tree
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given the root of a binary tree, return the inorder traversal of its
 *  nodes' values.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *      1
 *       \
 *        2
 *       /
 *      3
 *
 *  Input  : root = [1,null,2,3]
 *  Output : [1,3,2]
 *  Explanation: 1 has no left child, so visit 1 first. Go right to 2. 2 has
 *               left child 3, so visit 3, then 2. Order: Left -> Root -> Right.
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *              1
 *             / \
 *            2   3
 *           / \   \
 *          4   5   8
 *             / \  /
 *            6   7 9
 *
 *  Input  : root = [1,2,3,4,5,null,8,null,null,6,7,9]
 *  Output : [4,2,6,5,7,1,3,9,8]
 *  Explanation: Go deepest left first: 4. Then 2. Then 5's left 6, then 5,
 *               then 7. Left side of root done, visit 1. Go right: 3 has no
 *               left child, visit 3. Then 8's left child 9, then 8.
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
 *  Example 4:
 *
 *      1
 *
 *  Input  : root = [1]
 *  Output : [1]
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of nodes in the tree is in the range [0, 100].
 *      - -100 <= Node.val <= 100
 *
 * ----------------------------------------------------------------------------
 *  Follow up: Recursive solution is trivial, could you do it iteratively?
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
	// Approach 1: Recursive Inorder Traversal
	// Time Complexity: O(n), where n is the number of nodes in the tree. Each node is visited once.
	// Space Complexity: O(h), where h is the height of the tree. This space is
	static vector<int> inorderTraversal(const TreeNode* root){
		vector<int> ans;

		// Edge case: if the root is null, return an empty vector
		if (root == nullptr)
			return ans;

		// Recursive lambda function for inorder traversal
		auto inorder = [&](auto&& self, const TreeNode* node) -> void{
			// Base case: if the current node is null, return
			if (node == nullptr)
				return;
			// inorder traversal: visit left subtree, current node, then right subtree

			// Recursive call to the left child
			self(self, node->left);

			// Visit the current node and add its value to the answer vector
			ans.push_back(node->val);

			// Recursive call to the right child
			self(self, node->right);
		};

		inorder(inorder, root);
		return ans;
	}

	// Approach 2: Iterative Inorder Traversal using a stack
	// Time Complexity: O(n), where n is the number of nodes in the tree. Each node is visited once.
	// Space Complexity: O(h), where h is the height of the tree. In the worst
	static vector<int> inorderTraversalIterative(TreeNode* root){
		vector<int> ans;

		// Edge case: if the root is null, return an empty vector
		if (root == nullptr)
			return ans;

		// Stack to keep track of nodes and a pointer to the current node
		stack<TreeNode*> st;
		TreeNode* curr = root; // Start with the root node

		// Continue traversing until all nodes are processed
		while (!st.empty() || curr != nullptr){
			// Traverse to the leftmost node of the current subtree
			while (curr != nullptr){
				st.push(curr); // Push the current node onto the stack
				curr = curr->left; // Move to the left child
			}

			curr = st.top(); // save the top node from the stack (the last leftmost node)
			st.pop(); // remove the top node from the stack since we are visiting it now

			// Visit the current node and add its value to the answer vector
			ans.push_back(curr->val);

			// Move to the right child of the current node to continue the traversal
			curr = curr->right;
		}

		return ans;
	}

	// Approach 3: Morris Inorder Traversal (Threaded Binary Tree)
	// Time Complexity: O(n), where n is the number of nodes in the tree. Each node is visited once.
	// Space Complexity: O(1), as it uses no additional space for recursion or a stack
	static vector<int> inorderTraversalMorrisAlgo(TreeNode* root){
		vector<int> ans;

		// Edge case: if the root is null, return an empty vector
		if (root == nullptr)
			return ans;

		// Initialize the current node to the root of the tree
		TreeNode* curr = root;

		// Continue traversing until all nodes are processed
		while (curr != nullptr){
			// Case 1: if the current node has no left child
			if (curr->left == nullptr){
				ans.push_back(curr->val); // store the curr value in the answer vector
				curr = curr->right; // move to the right child of the current node

				// Case 2: if the current node has a left child
			} else{
				// Find the inorder predecessor of the current node (the rightmost node in the left subtree)
				TreeNode* predecessor = curr->left;
				while (predecessor->right != nullptr && predecessor->right != curr)
					predecessor = predecessor->right; // move to the right child until find the rightmost node

				// Case 2a: if the right child of the predecessor is null, create a temporary link to the current node
				if (predecessor->right == nullptr){
					predecessor->right = curr; // create a temporary link to the current node
					curr = curr->left; // move to the left child of the current node

					// Case 2b: if the right child of the predecessor is already
				} else{
					predecessor->right = nullptr; // remove the temporary link to restore the original tree structure
					ans.push_back(curr->val); // store the curr value in the answer vector
					curr = curr->right; // move to the right child of the current node
				}
			}
		}

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

	TreeNode* root = buildTree(values); // Build the binary tree from the input values
	TreeVisualization::printTree(root); // Print the tree structure for visualization

	// Approach 1: Recursive Inorder Traversal
	vector<int> inorderRecursive = Solution::inorderTraversal(root);
	cout << "Inorder Traversal (Recursive): ";
	printOutput(inorderRecursive);

	// Approach 2: Iterative Inorder Traversal
	vector<int> inorderIterative = Solution::inorderTraversalIterative(root);
	cout << "Inorder Traversal (Iterative): ";
	printOutput(inorderIterative);

	// Approach 3: Morris Inorder Traversal
	vector<int> inorderMorris = Solution::inorderTraversalMorrisAlgo(root);
	cout << "Inorder Traversal (Morris): ";
	printOutput(inorderMorris);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}