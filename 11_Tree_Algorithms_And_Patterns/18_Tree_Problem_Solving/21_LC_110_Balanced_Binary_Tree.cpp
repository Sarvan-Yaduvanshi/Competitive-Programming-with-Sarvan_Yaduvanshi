/*
Author: Sarvan Yaduvanshi
Created : 2026-11-11 18:59:09
*/

/*
 * ============================================================================
 *  110. Balanced Binary Tree
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 110
 *  Difficulty : Easy
 *  Topics     : Tree, Depth-First Search, Binary Tree
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given a binary tree, determine if it is height-balanced.
 *
 *  (A height-balanced binary tree is a binary tree in which the depth of
 *  the two subtrees of EVERY node never differs by more than one.)
 *
 * ----------------------------------------------------------------------------
 *  Core idea shared by both approaches:
 *
 *  A node is balanced only when:
 *      1. Its left subtree is balanced.
 *      2. Its right subtree is balanced.
 *      3. abs(left subtree height - right subtree height) <= 1.
 *
 *  Therefore, each DFS call must calculate the height of its subtree while
 *  also carrying enough information to decide whether that subtree is balanced.
 *  This is a bottom-up (postorder) solution: solve the children first, then
 *  check the current node.
 *
 * ----------------------------------------------------------------------------
 *  Dry run for both approaches:
 *
 *                  3
 *                 / \
 *                9   20
 *                   /  \
 *                  15   7
 *
 *  Visit 9:
 *      left height = 0, right height = 0
 *      height = 1, balanced = true
 *
 *  Visit 15 and 7:
 *      each has height = 1, balanced = true
 *
 *  Visit 20:
 *      left height = 1, right height = 1
 *      height = 2, balanced = true because |1 - 1| = 0
 *
 *  Visit 3:
 *      left height = 1, right height = 2
 *      height = 3, balanced = true because |1 - 2| = 1
 *
 *  Final result: true.
 *
 *  Approach 1 stores the results as {height, isBalanced} at every return.
 *  Approach 2 stores only one integer: a valid height when balanced, or -1
 *  as a special signal when the subtree is unbalanced. Both approaches make
 *  the same decisions during the same postorder traversal.
 *
 * ----------------------------------------------------------------------------
 *  Complexity for both approaches:
 *
 *      Time  : O(n), because every node is visited once.
 *      Space : O(h) recursion stack, where h is the tree height.
 *              Best case (balanced tree): O(log n)
 *              Worst case (skewed tree): O(n)
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *                3                height 3
 *               / \
 *              9   20             9: h=1 | 20: h=2
 *                 /  \
 *                15   7           15: h=1, 7: h=1
 *
 *      Node 3  : left h=1, right h=2  -> diff 1  OK
 *      Node 20 : left h=1, right h=1  -> diff 0  OK
 *
 *  Input  : root = [3,9,20,null,null,15,7]
 *  Output : true
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *                  1
 *                /   \
 *               2     2
 *              / \
 *             3   3
 *            / \
 *           4   4
 *
 *      Node 1 : left h=4 (2 -> 3 -> 4), right h=1  -> diff 3  BAD
 *      Node 2 (left one) : left h=3, right h=1     -> diff 2  BAD
 *
 *  Input  : root = [1,2,2,3,3,null,null,4,4]
 *  Output : false
 *
 * ----------------------------------------------------------------------------
 *  Example 3:
 *
 *      (empty tree)
 *
 *  Input  : root = []
 *  Output : true
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of nodes in the tree is in the range [0, 5000].
 *      - -10^4 <= Node.val <= 10^4
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
	/*
	 * Approach 1: Return {height, balance status}.
	 *
	 * How to implement this approach from scratch:
	 * 1. Define DFS(node) to return two values:
	 *       - the height of node's subtree
	 *       - whether node's subtree is balanced
	 * 2. For nullptr, return {0, true}; an empty subtree has height zero and is
	 *    balanced.
	 * 3. Recursively obtain the pair from the left and right children.
	 * 4. Compute the current height:
	 *       max(left height, right height) + 1
	 * 5. The current subtree is balanced only if both child flags are true and
	 *    the height difference is at most one.
	 * 6. Return the pair for the current node. The answer is the flag at root.
	 *
	 * This approach is direct and easy to read because the returned data says
	 * exactly what it represents.
	 */
    static bool isBalanced(const TreeNode* root) {
    	// Lambda function to perform DFS and return height and balance status
    	auto dfs = [&](auto&& self, const TreeNode* node) -> pair<int, bool>{
    		// Base case: If the node is null, return height 0 and balanced true
    		if (node == nullptr)
    			return {0, true};

    		// Recursively get the height and balance status of the left and right subtrees
    		const auto [leftHeight, leftSubtreeBalance] = self(self, node->left);
    		const auto [rightHeight, rightSubtreeBalance] = self(self, node->right);

    		// Calculate the height of the current node and check if it is balanced
    		const int height = max(leftHeight, rightHeight) + 1;
    		const bool isBalance = leftSubtreeBalance && rightSubtreeBalance &&
    								abs(leftHeight - rightHeight) <= 1;

    		// Return the height and balance status as a pair
    		return {height, isBalance};
    	};

    	// Call the DFS function starting from the root and return the balance status
    	return dfs(dfs, root).second;
    }

	/*
	 * Approach 2: Return height, or -1 as an unbalanced signal.
	 *
	 * How to implement this approach from scratch:
	 * 1. Define DFS(node) to return an integer.
	 * 2. For nullptr, return height 0.
	 * 3. Get the left height. If it is -1, immediately return -1.
	 * 4. Get the right height. If it is -1, immediately return -1.
	 * 5. If the current height difference is greater than one, return -1.
	 * 6. Otherwise return max(left height, right height) + 1.
	 * 7. The tree is balanced when DFS(root) does not return -1.
	 *
	 * The special value -1 avoids carrying a separate boolean. It also lets an
	 * unbalanced result travel upward immediately, so ancestors do not need to
	 * calculate heights for an already-invalid subtree.
	 */
	static bool isBalanceApporach2(const TreeNode* root){
    	// Lambda function to perform DFS and return height or -1 if unbalanced
	    auto dfs = [&](auto&& self, const TreeNode* node) -> int{
	    	// Base case: If the node is null, return height 0
		    if (node == nullptr)
		    	return 0;

	    	// Recursively get the height of the left subtree
	    	const int leftHeight = self(self, node->left);
	    	// Case 1: If the left subtree is unbalanced, return -1
	    	if (leftHeight == -1)
	    		return -1;

	    	// Recursively get the height of the right subtree
	    	const int rightHeight = self(self, node->right);
	    	// Case 2: If the right subtree is unbalanced, return -1
	    	if (rightHeight == -1)
	    		return -1;

	    	// Case 3: If the current node is unbalanced, return -1
	    	if (abs(leftHeight - rightHeight) > 1)
	    		return -1;

	    	// Case 4: If the current node is balanced, return its height
	    	return max(leftHeight, rightHeight) + 1;
	    };

    	// Call the DFS function starting from the root and check if the result is not -1 (indicating balanced)
    	return dfs(dfs, root) != -1;
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

	// Approach 1: Check if the tree is balanced using DFS
	const bool isBalanced1 = Solution::isBalanced(root);
	cout << "Is the binary tree balanced (Approach 1)? " << (isBalanced1 ? "Yes" : "No") << "\n";

	// Approach 2: Check if the tree is balanced using optimized DFS
	const bool isBalanced2 = Solution::isBalanceApporach2(root);
	cout << "Is the binary tree balanced (Approach 2)? " << (isBalanced2 ? "Yes" : "No") << "\n";
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}