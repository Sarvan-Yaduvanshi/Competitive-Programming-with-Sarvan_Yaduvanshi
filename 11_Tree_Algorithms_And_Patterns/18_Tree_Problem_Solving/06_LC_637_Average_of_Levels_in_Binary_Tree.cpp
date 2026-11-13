/*
Author: Sarvan Yaduvanshi
Created : 2026-11-04 01:44:03
*/

/*
 * ============================================================================
 *  637. Average of Levels in Binary Tree
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 637
 *  Difficulty : Easy
 *  Topics     : Tree, Depth-First Search, Breadth-First Search, Binary Tree
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given the root of a binary tree, return the average value of the nodes on
 *  each level in the form of an array. Answers within 10^-5 of the actual
 *  answer will be accepted.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *          3
 *         / \
 *        9   20
 *           /  \
 *          15   7
 *
 *  Input  : root = [3,9,20,null,null,15,7]
 *  Output : [3.00000,14.50000,11.00000]
 *  Explanation: The average value of nodes on level 0 is 3, on level 1 is
 *               14.5, and on level 2 is 11. Hence return [3, 14.5, 11].
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *          3
 *         / \
 *        9   20
 *       /  \
 *      15   7
 *
 *  Input  : root = [3,9,20,15,7]
 *  Output : [3.00000,14.50000,11.00000]
 *  Explanation: Level 0 = [3] avg 3. Level 1 = [9,20] avg 14.5.
 *               Level 2 = [15,7] avg 11.
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of nodes in the tree is in the range [1, 10^4].
 *      - -2^31 <= Node.val <= 2^31 - 1
 *
 * ----------------------------------------------------------------------------
 *  APPROACH 1: Breadth-First Search (BFS / Level Order Traversal)
 *
 *  Key idea:
 *      Nodes at the same depth are stored together in the queue. At the
 *      beginning of each iteration, q.size() gives the exact number of nodes
 *      in the current level.
 *
 *  Algorithm:
 *      1. If root is null, return an empty answer.
 *      2. Push root into a queue.
 *      3. While the queue is not empty:
 *           a. Store the current queue size as level_size.
 *           b. Remove exactly level_size nodes from the queue.
 *           c. Add each removed node's value to sum.
 *           d. Push its non-null children for the next level.
 *           e. Append sum / level_size to the answer.
 *      4. Return the averages of all levels.
 *
 *  Why does level_size matter?
 *      Children are added to the same queue while the current level is being
 *      processed. Saving q.size() before the loop prevents those new children
 *      from being mixed with the current level.
 *
 * ----------------------------------------------------------------------------
 *  DETAILED DRY RUN:
 *
 *      Tree:
 *
 *              3
 *             / \
 *            9   20
 *               /  \
 *              15   7
 *
 *      Initial queue: [3]
 *
 *      Level 0:
 *        level_size = 1, nodes = [3]
 *        sum = 3
 *        average = 3 / 1 = 3.00000
 *        push 9 and 20
 *        answer = [3.00000]
 *        queue = [9, 20]
 *
 *      Level 1:
 *        level_size = 2, nodes = [9, 20]
 *        sum = 9 + 20 = 29
 *        average = 29 / 2 = 14.50000
 *        9 has no children; push 15 and 7 from node 20
 *        answer = [3.00000, 14.50000]
 *        queue = [15, 7]
 *
 *      Level 2:
 *        level_size = 2, nodes = [15, 7]
 *        sum = 15 + 7 = 22
 *        average = 22 / 2 = 11.00000
 *        no children are added
 *        answer = [3.00000, 14.50000, 11.00000]
 *        queue = []
 *
 *      Final output: [3.00000, 14.50000, 11.00000]
 *
 * ----------------------------------------------------------------------------
 *  COMPLEXITY:
 *      Time Complexity  : O(N)
 *          Every node enters and leaves the queue exactly once.
 *
 *      Space Complexity : O(W) auxiliary space
 *          W is the maximum width of the tree. In the worst case W = N / 2.
 *          The returned answer vector is excluded from auxiliary space.
 *
 * ----------------------------------------------------------------------------
 *  EDGE CASES:
 *      - root = nullptr -> return []
 *      - One node [7] -> [7.00000]
 *      - Negative values are handled because sum uses long long.
 * ============================================================================
 */

#include <iomanip>
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
	// Approach 1: Breadth-First Search (BFS / Level Order Traversal)
	static vector<double> averageOfLevels(TreeNode* root){
		vector<double> ans;

		// Handle empty tree case
		if (root == nullptr)
			return ans;

		// Use a queue for level order traversal
		queue<TreeNode*> q;
		q.push(root); // Start with the root node

		// Process each level of the tree
		while (!q.empty()){
			// Get the number of nodes at the current level
			size_t level_size = q.size();
			long long sum = 0; // Use long long to avoid overflow for large sums

			// Process all nodes at the current level
			for (size_t i = 0; i < level_size; i++){
				// Get the front node from the queue
				TreeNode* curr_node = q.front();
				q.pop(); // Remove the node from the queue

				sum += curr_node->val; // Add the node's value to the sum for this level

				// Add the left and right children of the current node to the queue for the next level
				if (curr_node->left != nullptr)
					q.push(curr_node->left); // left child

				if (curr_node->right != nullptr)
					q.push(curr_node->right); // right child
			}

			// Calculate the average for the current level and add it to the result vector
			ans.emplace_back(static_cast<double>(sum) / level_size);
		}

		return ans;
	}

	// Approach 2: Using Depth-First Search (DFS) with Recursion
	// Time Complexity: O(n) - Each node is visited once
	// Space Complexity: O(h) - The recursion stack can hold up to n nodes in the worst case (for a skewed tree), where h is the height of the tree
	static vector<double> averageOfLevelsUseDFS(TreeNode* root){
		// Used two vectors to store the sum of values and count of nodes at each level
		vector<long long> sum;
		vector<int> level_count;

		// Lambda function for DFS traversal
		auto dfs = [&](auto&& self, const TreeNode* node, const int depth) -> void{
			// Base case: if the current node is null, return
			if (node == nullptr)
				return;

			// If we reach a new depth level, add a new entry for that level
			if (depth == sum.size()){
				sum.emplace_back(0);
				level_count.emplace_back(0);
			}

			sum[depth] += node->val; // Add the current node's value to the sum for this level
			level_count[depth]++; // Increment the count of nodes at this level

			// Recursively call DFS for the left and right children, increasing the depth by 1
			self(self, node->left, depth + 1); // left child
			self(self, node->right, depth + 1); // right child
		};

		// Start DFS traversal from the root at depth 0
		dfs(dfs, root, 0);

		vector<double> ans;

		// Handle empty tree case
		if (root == nullptr)
			return ans;

		// Calculate the average for each level and store it in the result vector
		for (size_t i = 0; i < sum.size(); i++)
			ans.emplace_back(static_cast<double>(sum[i]) / level_count[i]);

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

	TreeNode* root = buildTree(values);
	TreeVisualization::printTree(root);

	// Approach 1: Using BFS to calculate the average of levels in the binary tree
	cout << "Approach 1: Using BFS to calculate the average of levels in the binary tree\n";
	const vector<double> averages_bfs = Solution::averageOfLevels(root);
	cout << "Output: [";
	for (size_t i = 0; i < averages_bfs.size(); ++i){
		cout << fixed << setprecision(5) << averages_bfs[i];
		if (i < averages_bfs.size() - 1)
			cout << ", ";
	}
	cout << "]\n";

	// Approach 2: Using DFS to calculate the average of levels in the binary tree
	cout << "Approach 2: Using DFS to calculate the average of levels in the binary tree\n";
	const vector<double> averages_dfs = Solution::averageOfLevelsUseDFS(root);
	cout << "Output: [";
	for (size_t i = 0; i < averages_dfs.size(); ++i){
		cout << fixed << setprecision(5) << averages_dfs[i];
		if (i < averages_dfs.size() - 1)
			cout << ", ";
	}
	cout << "]\n";
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}