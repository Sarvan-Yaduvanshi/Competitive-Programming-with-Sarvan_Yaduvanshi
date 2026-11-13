/*
Author: Sarvan Yaduvanshi
Created : 2026-11-03 23:01:02
*/

/*
 * ============================================================================
 *  145. Binary Tree Postorder Traversal
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 145
 *  Difficulty : Easy
 *  Topics     : Stack, Tree, Depth-First Search, Binary Tree
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given the root of a binary tree, return the postorder traversal of its
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
 *  Output : [3,2,1]
 *  Explanation: 1 has no left child, go right to 2. 2 has left child 3,
 *               visit 3 first. Then 2, then root 1.
 *               Order: Left -> Right -> Root.
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
 *  Output : [4,6,7,5,2,9,8,3,1]
 *  Explanation: Left subtree of 1 first: 4, then 5's children 6 and 7, then
 *               5, then 2. Right subtree next: 8's left child 9, then 8,
 *               then 3. Root 1 comes last.
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
	// Approach 1: Recursive Postorder Traversal
	// Time Complexity: O(N), Space Complexity: O(H) where H is the height of the tree (due to recursion stack)
	static vector<int> postorderTraversalRecursive(TreeNode* root){
		vector<int> ans;

		// Edge case: if the root is null, return an empty vector
		if (root == nullptr)
			return ans;

		// Recursive lambda function for postorder traversal
		auto postorder = [&](auto&& self, const TreeNode* node) -> void{
			// Base case: if the current node is null, return
			if (node == nullptr)
				return;

			// Postorder traversal: visit left subtree, right subtree, then current node
			// Recursive call to the left child
			self(self, node->left);

			// Recursive call to the right child
			self(self, node->right);

			// Visit the current node and add its value to the answer vector
			ans.push_back(node->val);
		};

		postorder(postorder, root);
		return ans;
	}

	// Approach 2: Iterative Postorder Traversal using two stacks
	// Time Complexity: O(N), Space Complexity: O(N) for the two stacks
	static vector<int> postorderTraversalIterative(TreeNode* root){
		vector<int> ans;

		// Edge case: if the root is null, return an empty vector
		if (root == nullptr)
			return ans;

		// Use two stacks to perform postorder traversal iteratively
		stack<TreeNode*> st1; // Stack to hold nodes for processing
		stack<TreeNode*> st2; // Stack to hold nodes in postorder sequence

		st1.push(root); // Start with the root node in the first stack

		// Process nodes until the first stack is empty
		while (!st1.empty()){
			// save the top node from the first stack and pop it
			TreeNode* curr = st1.top();
			st1.pop();

			// Push the current node onto the second stack to maintain postorder sequence
			st2.push(curr);

			// left child is pushed first so that right child is processed first (LIFO order)
			if (curr->left != nullptr)
				st1.push(curr->left);

			// right child is pushed after left child so that it is processed first (LIFO order)
			if (curr->right != nullptr)
				st1.push(curr->right);
		}

		// Build the final postorder traversal result from the second stack
		while (!st2.empty()){
			ans.push_back(st2.top()->val); // store the value of the node in the answer vector
			st2.pop(); // remove the node from the second stack after visiting
		}

		return ans;
	}

	// Approach 3: Morris Postorder Traversal (Threaded Binary Tree)
	// Time Complexity: O(N), Space Complexity: O(1) (no extra space used for recursion or stacks)
	static vector<int> postorderTraversalMorrisAlgo(TreeNode* root){
		vector<int> ans;

		// Edge case: if the root is null, return an empty vector
		if (root == nullptr)
			return ans;

		// Lambda function to reverse the right boundary of a subtree
		auto reverseRightBoundary = [](TreeNode* from, TreeNode* to) -> void{
			// Base case: if the from and to nodes are the same, no reversal is needed
			if (from == to)
				return;

			// Use two pointers to reverse the right boundary of the subtree
			TreeNode* prev = from; // initialize prev to the starting node of the boundary
			TreeNode* curr = from->right; // initialize curr to the right child of the starting node

			// Continue reversing the right boundary until we reach the 'to' node
			while (true){
				// Step 1: Save the next node to process (the right child of the current node)
				TreeNode* next = curr->right;

				// Step 2: Reverse the right pointer of the current node to point to the previous node
				curr->right = prev;

				// Step 3: Move the prev and curr pointers forward to continue the reversal
				prev = curr;
				curr = next;

				// Step 4: If we have reached the 'to' node, break the loop as the reversal is complete
				if (prev == to)
					break;
			}
		};

		// Lambda function to collect the values of the nodes in the reversed right boundary
		auto collectReverseRightBoundary = [&](TreeNode* from, TreeNode* to) -> void{
			// Step 1: Reverse the right boundary of the subtree from 'from' to 'to'
			reverseRightBoundary(from, to);

			// Step 2: Traverse the reversed right boundary and collect the values of the nodes
			TreeNode* curr = to;
			while (true){
				// Step 3: Add the value of the current node to the answer vector
				ans.push_back(curr->val);

				// Step 4: If we have reached the 'from' node, break the loop as we have collected all values
				if (curr == from)
					break;

				// Step 5: Move to the right child of the current node to continue collecting values
				curr = curr->right;
			}

			// Step 6: Reverse the right boundary back to its original order to restore the tree structure
			reverseRightBoundary(to, from);
		};

		TreeNode dummy(0);
		dummy.left = root;

		TreeNode* curr = &dummy;

		while (curr != nullptr){
			if (curr->left == nullptr){
				curr = curr->right;
			} else{
				TreeNode* predecessor = curr->left;
				while (predecessor->right != nullptr && predecessor->right != curr)
					predecessor = predecessor->right;

				if (predecessor->right == nullptr){
					predecessor->right = curr;
					curr = curr->left;
				} else{
					collectReverseRightBoundary(curr->left, predecessor);

					predecessor->right = nullptr;
					curr = curr->right;
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
	TreeVisualization::printTree(root); // Visualize the binary tree structure

	// Approach 1: Recursive Postorder Traversal
	vector<int> postorderRecursive = Solution::postorderTraversalRecursive(root);
	cout << "Postorder Traversal (Recursive): ";
	printOutput(postorderRecursive);

	// Approach 2: Iterative Postorder Traversal
	vector<int> postorderIterative = Solution::postorderTraversalIterative(root);
	cout << "Postorder Traversal (Iterative): ";
	printOutput(postorderIterative);

	// Approach 3: Morris Postorder Traversal
	vector<int> postorderMorris = Solution::postorderTraversalMorrisAlgo(root);
	cout << "Postorder Traversal (Morris Algorithm): ";
	printOutput(postorderMorris);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}