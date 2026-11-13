/*
Author: Sarvan Yaduvanshi
Created : 2026-11-07 04:47:24
*/

/*
 * ============================================================================
 *  987. Vertical Order Traversal of a Binary Tree
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 987
 *  Difficulty : Hard
 *  Topics     : Hash Table, Tree, Depth-First Search, Breadth-First Search,
 *               Sorting, Binary Tree
 *  Companies  : Meta, Amazon, Google, Microsoft, Bloomberg, Uber, Apple
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given the root of a binary tree, calculate the vertical order traversal
 *  of the binary tree.
 *
 *  For each node at position (row, col), its left and right children will be
 *  at positions (row + 1, col - 1) and (row + 1, col + 1) respectively. The
 *  root of the tree is at (0, 0).
 *
 *  The vertical order traversal of a binary tree is a list of top-to-bottom
 *  orderings for each column index starting from the leftmost column and
 *  ending on the rightmost column. There may be multiple nodes in the same
 *  row and same column. In such a case, sort these nodes by their values.
 *
 *  Return the vertical order traversal of the binary tree.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *                3              (row 0, col  0)
 *               / \
 *              9   20           9  -> (1, -1),  20 -> (1, +1)
 *                 /  \
 *                15   7         15 -> (2,  0),  7  -> (2, +2)
 *
 *      Column :   -1     0      +1     +2
 *      Nodes  :  [9]   [3,15]  [20]   [7]
 *
 *  Input  : root = [3,9,20,null,null,15,7]
 *  Output : [[9],[3,15],[20],[7]]
 *  Explanation:
 *      Column -1: Only node 9 is in this column.
 *      Column 0: Nodes 3 and 15 are in this column in that order from top
 *                to bottom.
 *      Column 1: Only node 20 is in this column.
 *      Column 2: Only node 7 is in this column.
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *                1              (0,  0)
 *              /   \
 *             2     3           2 -> (1, -1),  3 -> (1, +1)
 *            / \   / \
 *           4   5 6   7         4 -> (2, -2),  5 -> (2, 0),
 *                               6 -> (2,  0),  7 -> (2, +2)
 *
 *      Column :   -2     -1      0         +1     +2
 *      Nodes  :  [4]    [2]   [1,5,6]     [3]    [7]
 *
 *  Input  : root = [1,2,3,4,5,6,7]
 *  Output : [[4],[2],[1,5,6],[3],[7]]
 *  Explanation:
 *      Column -2: Only node 4 is in this column.
 *      Column -1: Only node 2 is in this column.
 *      Column 0: Nodes 1, 5, and 6 are in this column.
 *                1 is at the top, so it comes first.
 *                5 and 6 are at the same position (2, 0), so we order them
 *                by their value, 5 before 6.
 *      Column 1: Only node 3 is in this column.
 *      Column 2: Only node 7 is in this column.
 *
 * ----------------------------------------------------------------------------
 *  Example 3:
 *
 *                1              (0,  0)
 *              /   \
 *             2     3           2 -> (1, -1),  3 -> (1, +1)
 *            / \   / \
 *           4   6 5   7         4 -> (2, -2),  6 -> (2, 0),
 *                               5 -> (2,  0),  7 -> (2, +2)
 *
 *      Column :   -2     -1      0         +1     +2
 *      Nodes  :  [4]    [2]   [1,5,6]     [3]    [7]
 *
 *  Input  : root = [1,2,3,4,6,5,7]
 *  Output : [[4],[2],[1,5,6],[3],[7]]
 *  Explanation:
 *      This case is the exact same as example 2, but with nodes 5 and 6
 *      swapped.
 *      Note that the solution remains the same since 5 and 6 are in the
 *      same location and should be ordered by their values.
 *
 * ----------------------------------------------------------------------------
 *  How to read the position:
 *      root        = (row 0, col 0)
 *      left child  = (parent row + 1, parent col - 1)
 *      right child = (parent row + 1, parent col + 1)
 *
 *  Sort rule inside one column:
 *      1. smaller row first (top to bottom)
 *      2. same row -> smaller value first
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of nodes in the tree is in the range [1, 1000].
 *      - 0 <= Node.val <= 1000
 * ============================================================================
 *
 *  APPROACH 1: BFS + Unordered Map + Pair Sorting
 * ============================================================================
 *
 *  Important difference from LeetCode 314:
 *
 *      In problem 314, nodes in one column only need top-to-bottom order.
 *      BFS naturally provides that order.
 *
 *      In problem 987, two nodes can have the same row and column. Those
 *      nodes must be ordered by their values, so BFS alone is not sufficient.
 *      We must save the row and sort each column by:
 *
 *          1. smaller row first  (top to bottom)
 *          2. same row -> smaller value first
 *
 *  Position rule:
 *
 *          root                 -> (row 0, column 0)
 *          left child            -> (row + 1, column - 1)
 *          right child           -> (row + 1, column + 1)
 *
 *  Data structure used by this code:
 *
 *          unordered_map<int, vector<pair<int, int>>>
 *
 *      Meaning:
 *          column -> [(row, node value), (row, node value), ...]
 *
 *      For example:
 *          map[0] = [(0, 1), (2, 5), (2, 6)]
 *
 *      The `pair<int, int>` is intentionally `(row, value)`. C++ pair sorting
 *      is lexicographic, so `ranges::sort(node)` automatically sorts first by
 *      row and then by value, exactly matching the problem requirement.
 *
 *  Why BFS?
 *      BFS visits the tree level by level and gives every node its correct
 *      row/column coordinates while traversing. However, the final pair sort
 *      is still necessary because nodes at the same row and column must be
 *      ordered by value rather than by discovery order.
 *
 *  Step-by-step flow:
 *
 *      1. If root is null, return an empty answer.
 *      2. Put `(root, 0, 0)` into the queue.
 *      3. Remove `(node, row, col)` from the queue.
 *      4. Store `(row, node->val)` in `map[col]`.
 *      5. Put the left child into `(row + 1, col - 1)`.
 *      6. Put the right child into `(row + 1, col + 1)`.
 *      7. Track `minCol` and `maxCol` so columns can be read from left to
 *         right after using the unordered map.
 *      8. For each column, sort its pairs by `(row, value)`.
 *      9. Remove the row information and append only values to the answer.
 *
 *  ONE BEST DRY RUN:
 *
 *                1
 *              /   \
 *             2     3
 *            / \   / \
 *           4   6 5   7
 *
 *      Coordinates:
 *          1 -> (0,  0)
 *          2 -> (1, -1), 3 -> (1, 1)
 *          4 -> (2, -2), 6 -> (2, 0)
 *          5 -> (2,  0),  7 -> (2, 2)
 *
 *      After BFS:
 *          map[-2] = [(2,4)]
 *          map[-1] = [(1,2)]
 *          map[ 0] = [(0,1), (2,6), (2,5)]
 *          map[ 1] = [(1,3)]
 *          map[ 2] = [(2,7)]
 *
 *      Sort every column:
 *          column -2 -> [(2,4)]       -> [4]
 *          column -1 -> [(1,2)]       -> [2]
 *          column  0 -> [(0,1),(2,5),(2,6)] -> [1,5,6]
 *          column  1 -> [(1,3)]       -> [3]
 *          column  2 -> [(2,7)]       -> [7]
 *
 *      Final answer:
 *          [[4], [2], [1,5,6], [3], [7]]
 *
 *  Why are `minCol` and `maxCol` maintained?
 *      `unordered_map` does not keep keys sorted. Tracking the column range
 *      lets the final loop read columns from the leftmost to rightmost.
 *
 *  Complexity:
 *      Let N be the number of nodes and let S_c be the number of nodes in
 *      column c.
 *
 *      - BFS and hashmap work: O(N) average.
 *      - Sorting column c: O(S_c log S_c).
 *      - Total time: O(N + sum(S_c log S_c)), worst case O(N log N).
 *      - Space: O(N) for the queue, hashmap, stored pairs, and answer.
 *
 *  Note about this exact implementation:
 *      The final loop visits every integer column from `minCol` to `maxCol`.
 *      For valid binary-tree coordinates, a column gap can exist in a sparse
 *      tree. In that case `map[col]` creates an empty vector and the output
 *      contains an empty column. If arbitrary sparse trees must be supported,
 *      store the seen columns separately and sort only those column keys.
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
	static vector<vector<int>> verticalTraversal(TreeNode* root){
		// Edge case: if the root is null, return an empty vector
		if (root == nullptr)
			return {};

		// Use an unordered_map to store three things: {column -> vector of pairs (row, value)}
		unordered_map<int, vector<pair<int, int>>> map;
		int minCol = 0; // Track the minimum column index
		int maxCol = 0; // Track the maximum column index

		// Use a queue to perform BFS, storing tuples of (node, row, column)
		queue<tuple<TreeNode*, int, int>> q;
		q.emplace(root, 0, 0); // Start with the root node at row 0, column 0

		while (!q.empty()){
			// Dequeue the front element of the queue
			auto [node, row, col] = q.front();
			q.pop();

			// Store the current node's value along with its row in the map for the corresponding column
			map[col].emplace_back(row, node->val);

			// Left child: if it exists, enqueue it with updated row and column values
			if (node->left != nullptr){
				minCol = min(minCol, col - 1);
				q.emplace(node->left, row + 1, col - 1);
			}

			// Right child: if it exists, enqueue it with updated row and column values
			if (node->right != nullptr){
				maxCol = max(maxCol, col + 1);
				q.emplace(node->right, row + 1, col + 1);
			}
		}

		// Prepare the final answer by iterating through the columns from minCol to maxCol
		vector<vector<int>> ans;
		for (int col = minCol; col <= maxCol; col++){
			// Sort the vector of pairs (row, value) for the current column
			auto& node = map[col];
			// c++ pair sorts lexicographically, so it will sort by row first, then by value if rows are equal
			ranges::sort(node);

			// Extract the values from the sorted pairs and add them to the answer
			vector<int> curr;
			for (auto& [row, val] : node)
				curr.emplace_back(val);

			// Add the current column's values to the final answer
			ans.emplace_back(std::move(curr));
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

	TreeNode* root = buildTree(values);
	TreeVisualization::printTree(root); // Visualize the binary tree structure::

	// Approach 1: BFS + Unordered Map
	const auto result1 = Solution::verticalTraversal(root);
	cout << "Vertical Order Traversal (BFS + unordered_map):\n";
	cout << "[";
	for (size_t i = 0; i < result1.size(); ++i){
		cout << "[";
        for (size_t j = 0; j < result1[i].size(); ++j){
            cout << result1[i][j];
            if (j < result1[i].size() - 1)
                cout << " ";
        }
        cout << "]";
        if (i < result1.size() - 1)
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