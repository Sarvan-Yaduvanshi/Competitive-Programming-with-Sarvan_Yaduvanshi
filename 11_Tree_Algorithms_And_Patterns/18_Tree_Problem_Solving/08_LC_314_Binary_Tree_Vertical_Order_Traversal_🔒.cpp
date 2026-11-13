/*
Author: Sarvan Yaduvanshi
Created : 2026-11-07 00:56:23
*/

/*
 * ============================================================================
 *  314. Binary Tree Vertical Order Traversal  (LeetCode Premium)
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 314
 *  Difficulty : Medium
 *  Topics     : Binary Tree, Breadth-First Search, Depth-First Search,
 *               Hash Table, Sorting, Tree
 *  Companies  : Meta, Amazon, Google, Microsoft, Bloomberg, Uber, Apple
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given the root of a binary tree, return the vertical order traversal of
 *  its nodes' values. (i.e., from top to bottom, column by column).
 *
 *  If two nodes are in the same row and column, the order should be from
 *  left to right.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *                3                 column 0
 *               / \
 *              9   20              9 -> col -1,  20 -> col +1
 *                 /  \
 *                15   7            15 -> col 0,  7 -> col +2
 *
 *      Column :   -1     0      +1     +2
 *      Nodes  :  [9]   [3,15]  [20]   [7]
 *
 *  Input  : root = [3,9,20,null,null,15,7]
 *  Output : [[9],[3,15],[20],[7]]
 *  Explanation: Node 3 and node 15 both sit in column 0, and 3 is higher,
 *               so 3 comes first.
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *                  3                column 0
 *                /   \
 *               9     8             9 -> col -1,  8 -> col +1
 *              / \   / \
 *             4   0 1   7           4 -> -2, 0 -> 0, 1 -> 0, 7 -> +2
 *
 *      Column :   -2     -1      0         +1     +2
 *      Nodes  :  [4]    [9]   [3,0,1]     [8]    [7]
 *
 *  Input  : root = [3,9,8,4,0,1,7]
 *  Output : [[4],[9],[3,0,1],[8],[7]]
 *  Explanation: Column 0 holds 3 (row 0), then 0 and 1 (both row 2).
 *               0 and 1 are in the same row and column, so left to right:
 *               0 first, then 1.
 *
 * ----------------------------------------------------------------------------
 *  Example 3:
 *
 *                    1                  column 0
 *                  /   \
 *                 2     3               2 -> -1,  3 -> +1
 *                / \   / \
 *               4  10 9   11            4 -> -2, 10 -> 0, 9 -> 0, 11 -> +2
 *                \
 *                 5                     5 -> -1  (right child of 4)
 *                  \
 *                   6                   6 -> 0   (right child of 5)
 *
 *      Column :   -2      -1        0          +1     +2
 *      Nodes  :  [4]    [2,5]   [1,10,9,6]     [3]   [11]
 *
 *  Input  : root = [1,2,3,4,10,9,11,null,5,null,null,null,null,null,null,
 *                   null,6]
 *  Output : [[4],[2,5],[1,10,9,6],[3],[11]]
 *  Explanation: Column 0 reads top to bottom: 1 (row 0), then 10 and 9
 *               (row 2, left to right), then 6 (row 4).
 *
 * ----------------------------------------------------------------------------
 *  How to read the column number:
 *      root is column 0.
 *      left child  = parent column - 1
 *      right child = parent column + 1
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The number of nodes in the tree is in the range [0, 100].
 *      - -100 <= Node.val <= 100
 * ============================================================================
 *  APPROACH 1: BFS + Ordered Map
 * ============================================================================
 *
 *  Core idea:
 *      Assign every node a horizontal column number.
 *
 *          root                 -> column 0
 *          left child            -> parent column - 1
 *          right child           -> parent column + 1
 *
 *      Then use:
 *          map<int, vector<int>>
 *              column -> values belonging to that column
 *
 *  Why BFS is important here:
 *      BFS visits nodes level by level. Therefore, a node that is higher in
 *      the tree is inserted into its column before a lower node. When two
 *      nodes have the same row and column, the left child is enqueued before
 *      the right child, so their left-to-right order is also preserved.
 *
 *  Step-by-step:
 *      1. Return immediately for an empty tree.
 *      2. Put (root, 0) in the queue.
 *      3. Remove one (node, column) pair from the queue.
 *      4. Append node->val to map[column].
 *      5. Enqueue the left child at column - 1.
 *      6. Enqueue the right child at column + 1.
 *      7. Iterate through map from the smallest column to the largest column.
 *
 *  Why use map instead of unordered_map?
 *      map keeps columns sorted automatically. Thus the final traversal
 *      already produces the required left-to-right column order without a
 *      separate sorting step.
 *
 *  DRY RUN:
 *
 *                3
 *               / \
 *              9   20
 *                 /  \
 *                15   7
 *
 *      Queue / map changes:
 *
 *      Start: queue = [(3,0)], map = {}
 *      Visit 3: map[0] = [3]
 *              enqueue (9,-1), (20,1)
 *      Visit 9: map[-1] = [9]
 *      Visit 20: map[1] = [20]
 *               enqueue (15,0), (7,2)
 *      Visit 15: map[0] = [3,15]
 *      Visit 7: map[2] = [7]
 *
 *      Sorted map order:
 *          -1 -> [9], 0 -> [3,15], 1 -> [20], 2 -> [7]
 *
 *      Answer = [[9], [3,15], [20], [7]]
 *
 *  Complexity:
 *      Let N be the number of nodes and K be the number of columns.
 *      - Time : O(N log K), commonly written O(N log N), because each node
 *               performs an ordered-map lookup/insertion.
 *      - Space: O(N) for the queue, map, and answer.
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
	// Approach 1: BFS + Map
	static vector<vector<int>> verticalOrder(TreeNode* root){
		// Edge case: empty tree
		if (root == nullptr)
			return {};

		// Use map to store nodes in vertical order (column -> list of node values)
		map<int, vector<int>> map;

		// Use queue pair to perform BFS (node, column index)
		queue<pair<TreeNode*, int>> q;
		q.emplace(root, 0); // Start with root at column 0

		while (!q.empty()){
			// Get the front node and its column index
			auto [node, col] = q.front();
			q.pop();

			// Store the node's value in the corresponding column in the map
			map[col].emplace_back(node->val);

			// If the left child exists, enqueue it with column index - 1
			if (node->left != nullptr)
				q.emplace(node->left, col - 1);

			// If the right child exists, enqueue it with column index + 1
			if (node->right != nullptr)
				q.emplace(node->right, col + 1);
		}

		vector<vector<int>> ans;
		ans.reserve(map.size()); // avoid reallocation
		for (auto& [col, node] : map)
			ans.emplace_back(std::move(node));

		return ans;
	}

	/*
	 * ============================================================================
	 *  APPROACH 2: BFS + Unordered Map + Column Range
	 * ============================================================================
	 *
	 *  Core idea:
	 *      Keep the same BFS traversal and the same column assignment as Approach
	 *      1, but replace the ordered map with an unordered_map.
	 *
	 *      Because an unordered_map does not sort its keys, maintain:
	 *          minCol = smallest column seen so far
	 *          maxCol = largest column seen so far
	 *
	 *      After BFS, iterate from minCol to maxCol to rebuild the answer from
	 *      leftmost column to rightmost column.
	 *
	 *  Why the node order is still correct:
	 *      Changing map type does not change BFS. Values are appended to each
	 *      column's vector in the same top-to-bottom, left-to-right order.
	 *
	 *  Step-by-step:
	 *      1. Return immediately for an empty tree.
	 *      2. Put (root, 0) in the queue and initialize minCol/maxCol to 0.
	 *      3. For every visited node, append its value to map[column].
	 *      4. Enqueue children with column - 1 and column + 1.
	 *      5. Update minCol/maxCol whenever a child column is created.
	 *      6. Read buckets from minCol through maxCol.
	 *
	 *  DRY RUN:
	 *      For the same tree:
	 *
	 *          map[-1] = [9]
	 *          map[0]  = [3,15]
	 *          map[1]  = [20]
	 *          map[2]  = [7]
	 *          minCol = -1, maxCol = 2
	 *
	 *      The final loop reads -1, 0, 1, 2 and returns:
	 *          [[9], [3,15], [20], [7]]
	 *
	 *  Complexity:
	 *      - Time : O(N) average for unordered_map operations, plus O(W) for the
	 *               final column-range loop, where W = maxCol - minCol + 1.
	 *               Since W can be O(N), this is O(N) average overall.
	 *      - Space: O(N) for the queue, unordered_map, and answer.
	 *
	 *  Important correctness note about this exact implementation:
	 *      The loop from minCol to maxCol assumes every integer column in that
	 *      range exists. A sparse tree can have a missing column, and map[col]
	 *      will then create an empty vector; that would add an empty column to
	 *      the output. For completely general input, Approach 1 is safer, or
	 *      this approach should store the seen columns and sort only those keys.
	 * ============================================================================
	 */
	static vector<vector<int>> verticalOrderOptimal(TreeNode* root){
		// Edge case: empty tree
		if (root == nullptr)
			return {};

		// Use unordered_map to store nodes in vertical order (column -> list of node values)
		unordered_map<int, vector<int>> map;
		int minCol = 0; // Track minimum column index
		int maxCol = 0; // Track maximum column index

		// Use queue pair to perform BFS (node, column index)
		queue<pair<TreeNode*, int>> q;
		q.emplace(root, 0); // Start with root at column 0

		while (!q.empty()){
			// Get the front node and its column index
			auto [node, col] = q.front();
			q.pop();

			// Store the node's value in the corresponding column in the unordered_map
			map[col].emplace_back(node->val);

			// Explore left child (column index - 1)
			if (node->left != nullptr){
				minCol = min(minCol, col - 1); // Update minimum column index
				q.emplace(node->left, col - 1); // Enqueue left child with column index - 1
			}

			// Explore right child (column index + 1)
			if (node->right != nullptr){
				maxCol = max(maxCol, col + 1); // Update maximum column index
				q.emplace(node->right, col + 1); // Enqueue right child with column index + 1
			}
		}

		// Prepare the result vector based on the range of column indices
		vector<vector<int>> ans;
		ans.reserve(map.size()); // avoid reallocation

		// Traverse from minCol to maxCol and collect the node values for each column
		for (int col = minCol; col <= maxCol; col++)
			ans.emplace_back(std::move(map[col]));

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

	// Approach 1: BFS + Map
	const vector<vector<int>> result1 = Solution::verticalOrder(root);
	cout << "Vertical Order Traversal (BFS + Map):\n";
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


	// Approach 2: BFS + Unordered Map
	const vector<vector<int>> result2 = Solution::verticalOrderOptimal(root);
	cout << "Vertical Order Traversal (BFS + Unordered Map):\n";
	cout << "[";
	for (size_t i = 0; i < result2.size(); ++i){
		cout << "[";
        for (size_t j = 0; j < result2[i].size(); ++j){
            cout << result2[i][j];
            if (j < result2[i].size() - 1)
                cout << " ";
        }
        cout << "]";
        if (i < result2.size() - 1)
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