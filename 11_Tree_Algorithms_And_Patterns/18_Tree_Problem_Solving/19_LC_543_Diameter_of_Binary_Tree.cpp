/*
Author: Sarvan Yaduvanshi
Created : 2026-11-11 18:43:06
*/

/*
 * ============================================================================
 *  543. Diameter of Binary Tree
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 543
 *  Difficulty : Easy
 *  Topics     : Tree, Depth-First Search, Binary Tree
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given the root of a binary tree, return the length of the diameter of
 *  the tree.
 *
 *  The diameter of a binary tree is the length of the longest path between
 *  any two nodes in a tree. This path may or may not pass through the root.
 *
 *  The length of a path between two nodes is represented by the number of
 *  edges between them.
 *
 * ----------------------------------------------------------------------------
 *  Important Tree Concepts:
 *
 *  - Height of a node:
 *      The number of nodes on the longest downward path from that node to a
 *      leaf. Therefore, height(nullptr) = 0 and height(leaf) = 1.
 *
 *  - Height of a tree:
 *      The height of its root. For example, a single-node tree has height 1.
 *
 *  - Depth of a node:
 *      The number of edges from the root to that node. The root has depth 0.
 *
 *  - Path:
 *      A sequence of connected nodes. In a tree, there is exactly one simple
 *      path between any two nodes.
 *
 *  - Diameter:
 *      The maximum number of edges on a path between any two nodes. It is also
 *      called the longest path or tree width in some problem statements.
 *      The diameter can pass through the root, but it does not have to.
 *
 *  - Height versus diameter:
 *      Height describes the longest path going downward from one chosen node
 *      (usually the root) to a leaf. Diameter describes the longest path
 *      between any two nodes and may combine two different subtrees.
 *      Height is measured from one starting node; diameter has two endpoints.
 *
 *  - Nodes versus edges:
 *      This problem asks for diameter in edges. If a path contains k nodes,
 *      its length is k - 1 edges. With the height convention above, a path
 *      through node x has left_height + right_height edges.
 *
 *  - Local diameter:
 *      For a node x, left_height + right_height is the longest path whose
 *      highest (turning) node is x. The global diameter is the maximum local
 *      diameter over every node.
 *
 *  - Diameter endpoints and center:
 *      The two endpoints are usually leaves (unless the tree has one node).
 *      A diameter may have one center node or one center edge; this is useful
 *      for reasoning about tree centers, but is not needed by this solution.
 *
 *  - Edge cases:
 *      An empty tree has diameter 0, a single-node tree has diameter 0, and a
 *      completely skewed tree with n nodes has diameter n - 1.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *                1
 *               / \
 *              2   3
 *             / \
 *            4   5
 *
 *      Longest path : 4 -> 2 -> 1 -> 3   (3 edges)
 *      Other path   : 5 -> 2 -> 1 -> 3   (3 edges)
 *
 *  Input  : root = [1,2,3,4,5]
 *  Output : 3
 *  Explanation: 3 is the length of the path [4,2,1,3] or [5,2,1,3].
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      1
 *     /
 *    2
 *
 *      Longest path : 1 -> 2   (1 edge)
 *
 *  Input  : root = [1,2]
 *  Output : 1
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of nodes in the tree is in the range [1, 10^4].
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

class Solution{
public:
	/*
	 * Approach 1 (detailed): Postorder DFS with a shared answer.
	 *
	 * The recursive function returns the height of the current subtree. Before
	 * returning, it has already computed both child heights, so it can treat the
	 * current node as the turning point of a possible diameter:
	 *
	 *     left_height + right_height
	 *
	 * The answer is updated at every node because the actual diameter may be
	 * completely inside the left or right subtree, rather than passing through
	 * the root. The lambda captures `ans` by reference, allowing every
	 * recursive call to update the same maximum.
	 *
	 * The returned height uses nodes, while the candidate diameter uses edges:
	 *     height(node) = max(left_height, right_height) + 1
	 *     local_diameter = left_height + right_height
	 *
	 * This is postorder dynamic programming: solve both children, use their
	 * results at the current node, then return the result needed by its parent.
	 * Each node is visited once, so time complexity is O(n) and recursion space
	 * is O(h), where h is the tree height.
	 */
	static int diameterOfBinaryTree(TreeNode* root){
		// ans hold the maximum diameter found so far
		int ans = 0;

		// Lambda function to calculate the height of a node and update the diameter
		auto height = [&](auto&& self, TreeNode* node) -> int {
			// Base case: If the node is null, return height as 0
			if (node == nullptr)
				return 0;

			const int left_height = self(self, node->left);  // left subtree height
			const int right_height = self(self, node->right); // right subtree height

			// Update the maximum diameter found so far
			ans = max(ans, left_height + right_height);

			// Return the height of the current node
			return max(left_height, right_height) + 1;
		};

		height(height, root);
		return ans;
	}

	/*
	 * Approach 2 (overview): Postorder DFS returning {height, diameter}.
	 *
	 * This uses the same recurrence and the same O(n) time / O(h) space
	 * complexity as Approach 1, but returns both values from each recursive
	 * call instead of storing the answer in a shared variable. At each node,
	 * it takes the maximum of the two child diameters and the local candidate
	 * left_height + right_height.
	 */
	static int diameterOfBinaryTreeUsePair(TreeNode* root){
		// Lambda function to calculate the height and diameter of a node
		auto heightAndDiameter = [&](auto&& self, TreeNode* node) -> pair<int, int> {
			// Base case: If the node is null, return height and diameter as 0
			if (node == nullptr)
				return {0, 0};

			const auto [left_height, left_diameter] = self(self, node->left);   // left subtree height and diameter
			const auto [right_height, right_diameter] = self(self, node->right); // right subtree height and diameter

			// Calculate the current node's height and diameter
			const int current_height = max(left_height, right_height) + 1;
			const int current_diameter = max({left_diameter, right_diameter, left_height + right_height});

			return {current_height, current_diameter};
		};

		return heightAndDiameter(heightAndDiameter, root).second; // Return the diameter
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

	// Approach 1: Calculate diameter using DFS + Outside lambda + [&]: Shared variable across recursive calls.
	const int diameter = Solution::diameterOfBinaryTree(root);
	cout << "Diameter of Binary Tree : " << diameter << "\n";

	// Approach 2: Calculate diameter using DFS + use pair<int, int> to return both height and diameter from the recursive function.
	const int diameterPair = Solution::diameterOfBinaryTreeUsePair(root);
	cout << "Diameter of Binary Tree : " << diameterPair << "\n";
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}