/*
Author: Sarvan Yaduvanshi
Created : 2026-11-07 19:29:53
*/

/*
 * ============================================================================
 *  222. Count Complete Tree Nodes
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 222
 *  Difficulty : Easy
 *  Topics     : Binary Search, Bit Manipulation, Tree, Binary Tree
 *  Companies  : Amazon, Google, Microsoft, Meta, Apple, Bloomberg, Uber
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given the root of a complete binary tree, return the number of the nodes
 *  in the tree.
 *
 *  According to Wikipedia, every level, except possibly the last, is
 *  completely filled in a complete binary tree, and all nodes in the last
 *  level are as far left as possible. It can have between 1 and 2^h nodes
 *  inclusive at the last level h.
 *
 *  Design an algorithm that runs in less than O(n) time complexity.
 *
 * ----------------------------------------------------------------------------
 *  Approach 3: Count Nodes Using Complete Binary Tree Properties
 *
 *  This approach is valid because the problem guarantees that the input is a
 *  complete binary tree. At every recursive call:
 *
 *  1. Traverse only the leftmost path to calculate the left height.
 *  2. Traverse only the rightmost path to calculate the right height.
 *  3. If both heights are equal, the subtree is a perfect binary tree.
 *     A perfect binary tree with height h contains exactly:
 *
 *                         2^h - 1 nodes
 *
 *     Therefore, return the result directly without visiting every node.
 *  4. If the heights are different, the subtree is not perfect. Count its
 *     nodes recursively as:
 *
 *                         1 + nodes(left) + nodes(right)
 *
 *  The height checks take O(log n) time for a complete tree. The implementation
 *  uses the existing recursive DFS function for the unequal-height case, so
 *  that fallback is linear in the nodes of those subtrees. Consequently, this
 *  exact implementation takes O(log n) for a perfect tree and can take O(n)
 *  for a non-perfect complete tree. A fully optimized complete-tree solution
 *  would recursively apply the height check to both subtrees to achieve
 *  O(log^2 n).
 *
 *  Important distinction:
 *  - A perfect binary tree is completely filled at every level.
 *  - A complete binary tree may have an incomplete last level, but its nodes
 *    must be placed from left to right.
 *  - If the input is not guaranteed to be a complete tree, this mathematical
 *    shortcut must not be used. Use Approach 1 (DFS) or Approach 2 (BFS),
 *    which work for any ordinary binary tree in O(n) time.
 *
 * ----------------------------------------------------------------------------
 *  Dry Run 1: Perfect Binary Tree
 *
 *              1
 *            /   \
 *           2     3
 *          / \   / \
 *         4   5 6   7
 *
 *  left_height  = 3  (1 -> 2 -> 4)
 *  right_height = 3  (1 -> 3 -> 7)
 *  Since both heights are equal, the tree is perfect.
 *  Node count = 2^3 - 1 = 7.
 *
 * ----------------------------------------------------------------------------
 *  Dry Run 2: Complete but Not Perfect Binary Tree
 *
 *              1
 *            /   \
 *           2     3
 *          / \   /
 *         4   5 6
 *
 *  At the root:
 *  left_height  = 3  (1 -> 2 -> 4)
 *  right_height = 2  (1 -> 3)
 *  Heights are different, so the root subtree is not perfect.
 *  The implementation uses DFS fallback:
 *
 *      count(1) = 1 + count(2) + count(3)
 *      count(2) = 1 + count(4) + count(5) = 3
 *      count(3) = 1 + count(6) + count(null) = 2
 *      Total    = 1 + 3 + 2 = 6
 *
 *  This tree is still complete, but it is not perfect. For an arbitrary
 *  non-complete binary tree, use DFS or BFS directly instead of this shortcut.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *              1                Level 0
 *            /   \
 *           2     3             Level 1
 *          / \   /
 *         4   5 6               Level 2  (last level, filled from the left)
 *
 *  Input  : root = [1,2,3,4,5,6]
 *  Output : 6
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      (empty tree)
 *
 *  Input  : root = []
 *  Output : 0
 *
 * ----------------------------------------------------------------------------
 *  Example 3:
 *
 *      1
 *
 *  Input  : root = [1]
 *  Output : 1
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of nodes in the tree is in the range [0, 5 * 10^4].
 *      - 0 <= Node.val <= 5 * 10^4
 *      - The tree is guaranteed to be complete.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <iomanip>
#include <random>
#include <chrono>
using namespace std;

// --- Type Definitions ---
struct TreeNode{
	int val;
	TreeNode* left;
	TreeNode* right;

	// Constructor initializes the node with a value and sets left and right children to nullptr
	explicit TreeNode(const int v) : val(v), left(nullptr), right(nullptr) {}
};

// Approach 1: Recursive DFS (Cal left and right subtrees, count nodes)
// Time Complexity: O(n) where n is the number of nodes in the tree
// Space Complexity: O(h) where h is the height of the tree (due to recursion stack)
static int countNodes(const TreeNode* root){
	// empty tree case
	if (root == nullptr)
		return 0;

	const int leftCount = countNodes(root->left);   // Count nodes in left subtree
	const int rightCount = countNodes(root->right); // Count nodes in right subtree

	return 1 + leftCount + rightCount; // (1(count parent node) + left child + right right child)
}

// Approach 2: Use BFS (Level Order Traversal) to count nodes
// Time Complexity: O(n) where n is the number of nodes in the tree
// Space Complexity: O(w) where w is the maximum width of the tree (due to queue)
static int countNodesBFS(const TreeNode* root){
	// empty tree case
	if (root == nullptr)
		return 0;

	queue<const TreeNode*> q;
	q.push(root);
	int count_num_of_nodes = 0;

	while (!q.empty()){
		const TreeNode* current = q.front();
		q.pop();
		count_num_of_nodes++; // Increment count for the current node

		// Enqueue left child if it exists
		if (current->left != nullptr)
			q.push(current->left);

		// Enqueue right child if it exists
		if (current->right != nullptr)
			q.push(current->right);
	}
	return count_num_of_nodes; // Return the total count of nodes
}

// Approach 3: Use complete-tree properties to count nodes
// Time Complexity: O(log(n)) for a perfect tree; O(n) in this implementation's
//             unequal-height fallback case
// Space Complexity: O(1) (constant space)
static int countNodesMath(const TreeNode* root){
	// empty tree case
	if (root == nullptr)
		return 0;

	// Helper function to count the height of the leftmost path
	// Time Complexity: O(log(n)) where n is the number of nodes in the tree
	auto count_left_height = [&](const TreeNode* node) -> int{
		int height = 0;
		while (node != nullptr){
			height++;
			node = node->left;
		}

		return height;
	};

	// Helper function to count the height of the rightmost path
	// Time Complexity: O(log(n)) where n is the number of nodes in the tree
	auto count_right_height = [&](const TreeNode* node) -> int{
		int height = 0;
		while (node != nullptr){
			height++;
			node = node->right;
		}

		return height;
	};

	// Calculate the heights of the leftmost and rightmost paths
	const int left_height = count_left_height(root);
	const int right_height = count_right_height(root);

	// Case 1: If the left and right heights are equal, the tree is a perfect binary tree
	// The number of nodes in a perfect binary tree is given by the formula: 2^height - 1
	if (left_height == right_height)
		return (1 << left_height) - 1;

	// Case 2: If the heights are not equal, recursively count the nodes in the left and right subtrees
	return 1 + countNodes(root->left) + countNodes(root->right);
}



// Function to build a binary tree from a vector of values (for testing purposes)
static TreeNode* buildTree(const vector<int>& values){
	int n = values.size();

	// Edge case: empty tree or root is null
	if (n == 0 || values[0] == -1)
		return nullptr;

	TreeNode* root = new TreeNode(values[0]);

	queue<TreeNode*> q;
	q.push(root);

	int idx = 1;
	while (!q.empty() && idx < n){
		TreeNode* current = q.front();
		q.pop();

		// Left child
		if (idx < n && values[idx] != -1){
			current->left = new TreeNode(values[idx]);
            q.push(current->left);
		}

		// Move to the next index for the right child
		idx++;

		// Right child
		if (idx < n && values[idx] != -1){
			current->right = new TreeNode(values[idx]);
			q.push(current->right);
		}

		idx++;
	}

	return root;
}

// Function to print traversal result
static void printTraversal(const vector<int>& traversal){
	cout << "Output: \n[";
	for (size_t i = 0; i < traversal.size(); ++i){
		cout << traversal[i];
        if (i < traversal.size() - 1)
            cout << " ";
	}
	cout << "]\n";
}

static void solve(){
	int n;
	cout << "Enter number of nodes in the tree: ";
	cin >> n;

	vector<int> values(n);
	cout << "Enter the values of the nodes (space-separated): ";
	for (int& val : values)
		cin >> val;

	// Print original tree values
	cout << "Original tree values: [";
	for (size_t i = 0; i < values.size(); ++i){
		cout << values[i];
        if (i < values.size() - 1)
            cout << " ";
	}
	cout << "]\n";

	// Build the binary tree from the input values
	TreeNode* root = buildTree(values);


	// Approach 1: Count nodes using recursive DFS
	const int count_dfs = countNodes(root);
	cout << "Count of nodes (DFS): " << count_dfs << "\n";

	// Approach 2: Count nodes using BFS
	const int count_bfs = countNodesBFS(root);
	cout << "Count of nodes (BFS): " << count_bfs << "\n";

	// Approach 3: Count nodes using complete-tree properties
	const int count_math = countNodesMath(root);
	cout << "Count of nodes (Math): " << count_math << "\n";
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}