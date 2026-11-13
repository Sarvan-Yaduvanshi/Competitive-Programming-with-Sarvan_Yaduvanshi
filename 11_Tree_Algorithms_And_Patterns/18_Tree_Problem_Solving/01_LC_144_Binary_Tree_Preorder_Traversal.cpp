/*
Author: Sarvan Yaduvanshi
Created : 2026-11-03 22:58:06
*/

/*
 * ============================================================================
 *  144. Binary Tree Preorder Traversal
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 144
 *  Difficulty : Easy
 *  Topics     : Stack, Tree, Depth-First Search, Binary Tree
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given the root of a binary tree, return the preorder traversal of its
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
 *  Output : [1,2,3]
 *  Explanation: Visit 1 (root), left is null, go right to 2, then 2's left
 *               child 3. Order: Root -> Left -> Right.
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
 *  Output : [1,2,4,5,6,7,3,8,9]
 *  Explanation: Go deep left first: 1 -> 2 -> 4. Then 5 with its children
 *               6 and 7. Left side of root is done, so go right: 3 -> 8 ->
 *               9.
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
	// Approach 1: Recursive Preorder Traversal
	// Time Complexity: O(N) - each node is visited once
	// Space Complexity: O(H) - recursion stack, where H is the height of the tree
	static vector<int> preorderTraversal(const TreeNode* root){
		vector<int> ans;

		// Lambda function for recursive preorder traversal
		auto preorder = [&](auto&& self, const TreeNode* node) -> void {
			// Base case: if the current node is null, return
			if (node == nullptr)
				return;

			// preorder ans: root -> left -> right

			// Visit the current node (root) and add its value to the answer vector
			ans.push_back(node->val);

			// Recursively traverse the left subtree
			self(self, node->left);

			// Recursively traverse the right subtree
			self(self, node->right);
		};

		preorder(preorder, root);
		return ans;
	}
	// Approach 2: Iterative Preorder Traversal using Stack
	// Time Complexity: O(N) - each node is visited once
	// Space Complexity: O(H) - stack space, where H is the height of the tree
	static vector<int> preorderTraversalApproach2(TreeNode* root){
		vector<int> ans;

		// Edge case: if the root is null, return an empty vector
		if (root == nullptr)
			return ans;

		// Use a stack to simulate the recursive call stack for preorder traversal
		stack<TreeNode*> st;
		st.push(root); // Push the root node onto the stack to start the traversal

		// Continue the traversal until the stack is empty
		while (!st.empty()){
			// Pop the top node from the stack and visit it
			TreeNode* curr = st.top();
			st.pop();

			// Add the value of the current node to the answer vector
			ans.push_back(curr->val);

			// Push the right child first so that the left child is processed next (LIFO order)
			if (curr->right != nullptr)
				st.push(curr->right);

			// Push the left child onto the stack to be processed after the right child
			if (curr->left != nullptr)
				st.push(curr->left);
		}

		return ans;
	}

	// Approach 3: Morris Preorder Traversal
	//
	// Morris traversal avoids both recursion and an auxiliary stack by temporarily
	// connecting the rightmost node of the current node's left subtree back to the
	// current node. This temporary connection is called a thread.
	//
	// For preorder (Root -> Left -> Right):
	//   1. If the current node has no left child, visit it and move right.
	//   2. Otherwise, find its inorder predecessor (the rightmost node in the
	//      left subtree).
	//   3. If the predecessor has no thread, create one, visit the current node,
	//      and move left.
	//   4. If the predecessor already points to the current node, remove the
	//      thread and move right.
	//
	// The second encounter of a node with a left child is only used to remove its
	// thread; the node is not visited again. Therefore, the tree is restored before
	// the function returns.
	//
	// Dry run using this tree:
	//
	//              1
	//             / \
	//            2   3
	//           / \   \
	//          4   5   6
	//
	//   curr = 1: predecessor = 5, create 5 -> 1, visit 1, move to 2
	//   curr = 2: predecessor = 4, create 4 -> 2, visit 2, move to 4
	//   curr = 4: no left child, visit 4, follow thread to 2
	//   curr = 2: thread 4 -> 2 exists, remove it, move to 5
	//   curr = 5: no left child, visit 5, follow thread to 1
	//   curr = 1: thread 5 -> 1 exists, remove it, move to 3
	//   curr = 3: no left child, visit 3, move to 6
	//   curr = 6: no left child, visit 6, move to nullptr
	//
	// Output: [1, 2, 4, 5, 3, 6]
	//
	// Time Complexity: O(N) - each temporary thread is created and removed once.
	// Space Complexity: O(1) auxiliary space (the returned answer is not counted).
	static vector<int> preorderTraversalUseMorrisAlgo(TreeNode* root){
		vector<int> ans;

		// Edge case: if the root is null, return an empty vector
		if (root == nullptr)
			return ans;

		// Start with the current node as the root
		TreeNode* curr = root;

		// Continue the traversal until there are no more nodes to process
		while (curr != nullptr) {
			// Case 1: If the current node has no left child
			if (curr->left == nullptr) {
				ans.push_back(curr->val); // visit the current node(store its value to the answer vector)
				curr = curr->right; // move to the right child

				// Case 2: If the current node has a left child, find its inorder predecessor
			} else {
				// Find the rightmost node in the left subtree (inorder predecessor)
				TreeNode* predecessor = curr->left;
				while (predecessor->right != nullptr && predecessor->right != curr)
					// Move to the right child until we find the left subtree's rightmost node
						predecessor = predecessor->right;

				// Case 2a: If the predecessor's right child is null, create a temporary thread
				if (predecessor->right == nullptr){
					predecessor->right = curr; // create a temporary thread
					ans.push_back(curr->val); // visit the current node(store its value to the answer vector)
					curr = curr->left; // move to the left child

					// Case 2b: If the predecessor's right child already points to the current node, remove the thread
				} else{
					predecessor->right = nullptr; // remove the temporary thread
					curr = curr->right; // move to the right child
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

	// Build the binary tree from the input values
	TreeNode* root = buildTree(values);

	// Visualize the tree structure for better understanding
	TreeVisualization::printTree(root);

	// Approach 1: Recursive Preorder Traversal
	vector<int> ans1 = Solution::preorderTraversal(root);
	cout << "Preorder Traversal (Recursive): ";
	printOutput(ans1);

	// Approach 2: Iterative Preorder Traversal using Stack
	vector<int> ans2 = Solution::preorderTraversalApproach2(root);
	cout << "Preorder Traversal (Iterative using Stack): ";
	printOutput(ans2);

	// Approach 3: Morris Preorder Traversal
	vector<int> ans3 = Solution::preorderTraversalUseMorrisAlgo(root);
	cout << "Preorder Traversal (Morris Traversal): ";
	printOutput(ans3);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}
