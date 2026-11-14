/*
Author: Sarvan Yaduvanshi
Created : 2026-11-14 10:28:06
*/

/*
 * ============================================================================
 *  Bottom View of Binary Tree
 * ============================================================================
 *  Platform   : GeeksforGeeks
 *  Problem No : N/A (GFG has no number)
 *  Difficulty : Medium
 *  Topics     : Tree, Binary Tree, Data Structures
 *  Companies  : Amazon, Microsoft, Flipkart, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given a binary tree, and your task is to return its bottom view. The
 *  bottom view of a binary tree is the set of nodes visible when the tree
 *  is viewed from the bottom.
 *
 *  Note: If there are multiple bottom-most nodes for a horizontal distance
 *  from the root, then the latter one in the level order traversal is
 *  considered.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *                1                column  0   (row 0)
 *              /   \
 *             2     3             2 -> -1,  3 -> +1   (row 1)
 *            / \     \
 *           4   5     6           4 -> -2,  5 -> 0,  6 -> +2   (row 2)
 *
 *      Column :   -2     -1      0       +1     +2
 *      Nodes  :  [4]    [2]    [1,5]    [3]    [6]
 *      Bottom :   4      2      5        3      6
 *                              (5 is lower than 1)
 *
 *  Input  : root = [1, 2, 3, 4, 5, N, 6]
 *  Output : [4, 2, 5, 3, 6]
 *  Explanation: The Green nodes represent the bottom view of below binary
 *               tree.
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *                     20                       column  0   (row 0)
 *                  /      \
 *                8          22                 8 -> -1,  22 -> +1   (row 1)
 *              /   \       /   \
 *             5     3     4     25             5 -> -2,  3 -> 0,
 *                  / \                         4 -> 0,   25 -> +2   (row 2)
 *                10   14                       (children of 3)
 *                      \
 *                  (see decode below)
 *
 *      Real tree after decoding:
 *
 *                     20
 *                  /      \
 *                8          22
 *              /   \       /   \
 *             5     3     4     25
 *                  / \         /
 *                10   14      28
 *
 *      Columns:
 *          20 -> 0
 *          8  -> -1,  22 -> +1
 *          5  -> -2,  3  -> 0,  4 -> 0,  25 -> +2
 *          10 -> -1,  14 -> +1,  28 -> +1
 *
 *      Column :   -2     -1        0          +1          +2
 *      Nodes  :  [5]   [8,10]  [20,3,4]   [22,14,28]     [25]
 *      Bottom :   5     10        4          28            25
 *
 *  Input  : root = [20, 8, 22, 5, 3, 4, 25, N, N, 10, 14, N, N, 28, N]
 *  Output : [5, 10, 4, 28, 25]
 *  Explanation: The Green nodes represent the bottom view of below binary
 *               tree.
 *
 * ----------------------------------------------------------------------------
 *  How to read the column number (same as Vertical Order):
 *      root is column 0.
 *      left child  = parent column - 1
 *      right child = parent column + 1
 *      Bottom view = the LAST node (lowest, and latest in level order on a
 *                    tie) of every column, printed from the smallest column
 *                    to the largest.
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - 1 <= size of binary tree, Node.data <= 10^5
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
	 * Approach 1: Breadth-First Search (BFS) with an ordered map
	 *
	 * Idea:
	 * Assign every node a horizontal distance (HD) from the root. The root
	 * has HD 0, the left child has HD - 1, and the right child has HD + 1.
	 * All nodes having the same HD belong to the same vertical column.
	 *
	 * BFS visits the tree level by level. Therefore, nodes in a deeper level
	 * are processed after nodes in shallower levels. Whenever a node is
	 * processed, overwrite the value stored for its HD. The final value for
	 * each HD is consequently the bottommost node. If two nodes are at the
	 * same depth and HD, BFS processes them in level-order, so the later
	 * node naturally overwrites the earlier one as required by the problem.
	 *
	 * An ordered map keeps the columns sorted automatically. Iterating over
	 * it from beginning to end produces the answer from left to right.
	 *
	 * Complexity:
	 *   Time  : O(N log W), where N is the number of nodes and W is the
	 *           number of distinct horizontal distances.
	 *   Space : O(N) for the queue and map.
	 */
	static vector<int> bottomView(TreeNode *root) {
	    vector<int> ans;

		// empty tree case
		if (root == nullptr)
            return ans;

		// Map to store the last node at each horizontal distance
        map<int, int> bottomNodeMap;
		queue<pair<TreeNode*, int>> q; // Pair of node and its horizontal distance
        q.push({root, 0});

		while (!q.empty()) {
			// bfs insures that we are visiting nodes level by level,
			// so the last node we encounter at each horizontal distance is the bottommost node for that distance.
			// hd -> horizontal distance of the current node from the root
			auto [node, hd] = q.front();
            q.pop();

			// ALWAYS overwrite! Later/deeper nodes replace earlier/shallower ones
			bottomNodeMap[hd] = node->val;


            // Add left and right children to the queue with updated horizontal distances
            if (node->left != nullptr)
                q.push({node->left, hd - 1});

            if (node->right)
                q.push({node->right, hd + 1});
        }

		// Extract the values from the map in order of their horizontal distances
		for (const auto& [hd, val] : bottomNodeMap)
			ans.push_back(val);

		return ans;
	}

	/*
	 * Approach 2: Breadth-First Search (BFS) with a hash map
	 *
	 * Idea:
	 * Use the same horizontal-distance and BFS logic as Approach 1, but use
	 * an unordered_map so that storing or overwriting a column takes O(1)
	 * average time instead of O(log W).
	 *
	 * Since an unordered_map does not keep keys sorted, track the smallest
	 * and largest horizontal distances encountered during traversal. Every
	 * horizontal distance between these two limits is guaranteed to exist:
	 * moving through the tree changes HD by exactly one. Finally, iterate
	 * from minCol to maxCol to emit the columns in left-to-right order.
	 *
	 * The value for a column is overwritten on every visit. Because BFS
	 * processes nodes level by level, the last value stored for that column
	 * is its bottom-view node, including the required level-order tie rule.
	 *
	 * Complexity:
	 *   Time  : O(N) average, including traversal and output.
	 *   Space : O(N) for the queue and hash map.
	 */
	static vector<int> bottomView2(TreeNode *root) {
	    vector<int> ans;

		// empty tree case
		if (root == nullptr)
			return ans;

		// Map to store the last node at each horizontal distance
		unordered_map<int, int> bottomNodeMap;
		int minCol = 0; // Minimum horizontal distance encountered
		int maxCol = 0; // Maximum horizontal distance encountered

		queue<pair<TreeNode*, int>> q; // Pair of node and its horizontal distance
		q.push({root, 0});

		while (!q.empty()){
			auto [node, hd] = q.front();
			q.pop();

			// ALWAYS overwrite! Later/deeper nodes replace earlier/shallower ones
			bottomNodeMap[hd] = node->val;

			// Upadate the min horizontal distance and add  left child to the queue
			if (node->left != nullptr){
				minCol = min(minCol, hd - 1);
				q.push({node->left, hd - 1});
			}

			// Update the max horizontal distance and add right child to the queue
			if (node->right != nullptr){
				maxCol = max(maxCol, hd + 1);
				q.push({node->right, hd + 1});
			}
		}

		// Extract the values from the map in order of their horizontal distances
		for (int i = minCol; i <= maxCol; ++i)
			ans.push_back(bottomNodeMap[i]);

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

	// Approach 1: Using BFS + map
	const vector<int> bottomViewResult1 = Solution::bottomView(root);
	cout << "Bottom view of the binary tree (Approach 1): ";
	printOutput(bottomViewResult1);

	// Approach 2: Using BFS + unordered_map + min-max horizontal distance
	const vector<int> bottomViewResult2 = Solution::bottomView2(root);
	cout << "Bottom view of the binary tree (Approach 2): ";
	printOutput(bottomViewResult2);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}