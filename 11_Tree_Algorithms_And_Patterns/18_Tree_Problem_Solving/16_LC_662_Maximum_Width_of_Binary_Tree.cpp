/*
Author: Sarvan Yaduvanshi
Created : 2026-11-08 04:14:25
*/

/*
 * ============================================================================
 *  662. Maximum Width of Binary Tree
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 662
 *  Difficulty : Medium
 *  Topics     : Tree, Depth-First Search, Breadth-First Search,
 *               Binary Tree
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Uber
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given the root of a binary tree, return the maximum width of the given
 *  tree.
 *
 *  The maximum width of a tree is the maximum width among all levels.
 *
 *  The width of one level is defined as the length between the end-nodes
 *  (the leftmost and rightmost non-null nodes), where the null nodes between
 *  the end-nodes that would be present in a complete binary tree extending
 *  down to that level are also counted into the length calculation.
 *
 *  It is guaranteed that the answer will in the range of a 32-bit signed
 *  integer.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *                  1                Level 0 : width 1
 *                /   \
 *               3     2             Level 1 : width 2
 *              / \     \
 *             5   3     9           Level 2 : width 4  <== MAX
 *
 *      Level 2 slots : [5] [3] [null] [9]   (null counted between 3 and 9)
 *
 *  Input  : root = [1,3,2,5,3,null,9]
 *  Output : 4
 *  Explanation: The maximum width exists in the third level with length 4
 *               (5,3,null,9).
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *                  1                Level 0 : width 1
 *                /   \
 *               3     2             Level 1 : width 2
 *              /       \
 *             5         9           Level 2 : width 4
 *            /         /
 *           6         7             Level 3 : width 7  <== MAX
 *
 *      Level 3 slots : [6] [null] [null] [null] [null] [null] [7]
 *
 *  Input  : root = [1,3,2,5,null,null,9,6,null,7]
 *  Output : 7
 *  Explanation: The maximum width exists in the fourth level with length 7
 *               (6,null,null,null,null,null,7).
 *
 * ----------------------------------------------------------------------------
 *  Example 3:
 *
 *                  1                Level 0 : width 1
 *                /   \
 *               3     2             Level 1 : width 2  <== MAX
 *              /
 *             5                     Level 2 : width 1
 *
 *  Input  : root = [1,3,2,5]
 *  Output : 2
 *  Explanation: The maximum width exists in the second level with length 2
 *               (3,2).
 *
 * ----------------------------------------------------------------------------
 *  How to count width (index trick, like a heap array):
 *      root index = 0
 *      left child  index = 2 * parent + 1
 *      right child index = 2 * parent + 2
 *      width of a level = (last index - first index) + 1
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of nodes in the tree is in the range [1, 3000].
 *      - -100 <= Node.val <= 100
 * ============================================================================
 *
 *  Revision Notes: Think Before Coding
 *
 *  Core Observation:
 *  The width is not just the number of non-null nodes at a level. Null
 *  positions between the leftmost and rightmost nodes must also be counted.
 *  Therefore, assign every node the index it would have in a complete binary
 *  tree:
 *
 *      root index = 0
 *      left child  = 2 * parent index + 1
 *      right child = 2 * parent index + 2
 *
 *  For one level:
 *
 *      width = rightmost index - leftmost index + 1
 *
 *  Approach 1: BFS / Level-Order Traversal
 *
 *  1. Put the root and its virtual complete-tree index into a queue.
 *  2. Process exactly one level at a time using the current queue size.
 *  3. Remember the first index of the level.
 *  4. Remove every node in that level and normalize its index by subtracting
 *     the first index. Normalization keeps indices small and preserves the
 *     distance between nodes.
 *  5. Add existing children with indices `2 * index + 1` and
 *     `2 * index + 2`.
 *  6. The width of the level is `last normalized index + 1`.
 *  7. Keep the largest width found across all levels.
 *
 *  BFS is usually the easiest approach because width is naturally measured
 *  level by level.
 *  Time Complexity: O(n)
 *  Space Complexity: O(w), where w is the maximum number of queued nodes.
 *
 *  Approach 2: DFS / Recursive Traversal
 *
 *  1. Traverse the tree recursively while storing the current depth and the
 *     complete-tree index of each node.
 *  2. For every depth, record the index of the first node visited. Because DFS
 *     visits the left subtree before the right subtree, this is the leftmost
 *     node of that level.
 *  3. For each node, calculate:
 *
 *         current width = current index - first index at this depth + 1
 *
 *  4. Update the global maximum width.
 *  5. Visit the left child before the right child using the same index rules.
 *
 *  DFS avoids a queue, but it needs one stored leftmost index per level and
 *  recursion stack space.
 *  Time Complexity: O(n)
 *  Space Complexity: O(h), excluding the leftmost-index array.
 *
 *  Dry Run 1: Tree with Internal Null Positions
 *
 *                  1
 *                /   \
 *               3     2
 *              / \     \
 *             5   3     9
 *
 *  Complete-tree indices:
 *      Level 0: 1(index 0)                         width = 1
 *      Level 1: 3(index 1), 2(index 2)             width = 2
 *      Level 2: 5(index 3), 3(index 4), 9(index 6)
 *               width = 6 - 3 + 1 = 4
 *
 *  The missing index 5 represents the null position between node 3 and node 9.
 *  Answer = 4.
 *
 *  BFS view:
 *      At level 2, first index = 3. Normalized indices are 0, 1, and 3.
 *      Last normalized index = 3, so width = 3 + 1 = 4.
 *
 *  DFS view:
 *      First index at depth 2 = 3. When node 9 is visited:
 *      width = 6 - 3 + 1 = 4.
 *
 *  Dry Run 2: Sparse Deep Tree
 *
 *                  1
 *                /   \
 *               3     2
 *              /       \
 *             5         9
 *            /         /
 *           6         7
 *
 *  Complete-tree indices:
 *      Level 0: 1(index 0)                         width = 1
 *      Level 1: 3(index 1), 2(index 2)             width = 2
 *      Level 2: 5(index 3), 9(index 6)             width = 6 - 3 + 1 = 4
 *      Level 3: 6(index 7), 7(index 13)           width = 13 - 7 + 1 = 7
 *
 *  Several null positions lie between nodes 6 and 7, so the maximum width is
 *  7. Answer = 7.
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
using i64 = long long;

class Solution{
public:
	// Approach 1: Use BFS to find the maximum width of the binary tree
	static int widthOfBinaryTreeUseBFS(TreeNode* root){
		if (root == nullptr)
			return 0;

		// Use a queue to perform level-order traversal, storing pairs of (node, index)
		queue<pair<TreeNode*, i64>> q;
		q.emplace(root, 0);
		i64 maximum_depth = 0;

		while (!q.empty()){
			const size_t level_size = q.size();

			// Get the index of the first node in the current level to normalize indices
			i64 first = q.front().second;
			i64 last = 0; // Initialize last index for the current level

			for (size_t i = 0; i < level_size; i++){
				auto [node, idx] = q.front();
				q.pop();

				// Normalize the index to prevent integer overflow and maintain relative positions
				idx -= first;

				// Update the last index for the current level
				last = idx;

				// Add left child and left index (2 * idx + 1) to the queue if it exists
				if (node->left != nullptr)
					q.emplace(node->left, 2 * idx + 1);

				// Add right child and right index (2 * idx + 2) to the queue if it exists
				if (node->right != nullptr)
					q.emplace(node->right, 2 * idx + 2);
			}

			// Update the maximum width found so far for the current level
			maximum_depth = max(maximum_depth, last + 1);
		}

		// convert maximum_depth to int before returning, as the problem guarantees the answer fits in a 32-bit signed integer
		return static_cast<int>(maximum_depth);
	}

	// Approach 2: Use DFS to find the maximum width of the binary tree
	static int widthOfBinaryTreeUseDFS(TreeNode* root){
		if (root == nullptr)
			return 0;

		i64 maximum_depth = 0;
		vector<i64> leftMost; // Store the leftmost index at each depth level

		// Recursive DFS function to traverse the tree and calculate width
		auto dfs = [&](auto&& self, TreeNode* node, size_t depth, i64 idx) -> void{
			// Base case: if the node is null, return
			if (node == nullptr)
				return;

			// If this is the first time visiting this depth, record the leftmost index
			if (depth == leftMost.size())
				leftMost.emplace_back(idx);

			// Update the maximum width for the current depth level
			maximum_depth = max(maximum_depth, idx - leftMost[depth] + 1);

			// Recursively visit the left and also update depth and index left child (2 * idx + 1)
			if (node->left != nullptr)
				self(self, node->left, depth + 1, 2 * idx + 1);

			// Recursively visit the right and also update depth and index right child (2 * idx + 2)
			if (node->right != nullptr)
				self(self, node->right, depth + 1, 2 * idx + 2);
		};

		dfs(dfs, root, 0, 0);
		return static_cast<int>(maximum_depth);
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

	// Approach 1: Calculate maximum width using BFS
	const int maxWidthBFS = Solution::widthOfBinaryTreeUseBFS(root);
	cout << "Maximum Width of Binary Tree (BFS): " << maxWidthBFS << "\n";

	// Approach 2: Calculate maximum width using DFS
	const int maxWidthDFS = Solution::widthOfBinaryTreeUseDFS(root);
	cout << "Maximum Width of Binary Tree (DFS): " << maxWidthDFS << "\n";
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}