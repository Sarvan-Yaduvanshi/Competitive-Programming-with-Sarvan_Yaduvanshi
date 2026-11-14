/*
Author: Sarvan Yaduvanshi
Created : 2026-11-14 10:28:06
*/

/*
 * ============================================================================
 *  Top View of Binary Tree
 * ============================================================================
 *  Platform   : GeeksforGeeks
 *  Problem No : N/A (GFG has no number)
 *  Difficulty : Medium
 *  Topics     : Tree, Binary Tree, Data Structures
 *  Companies  : Amazon, Microsoft, Flipkart, Adobe
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given a binary tree, task is to return its top view. The top view of a
 *  binary tree is the set of nodes visible when the tree is viewed from the
 *  top.
 *
 *      - Return the nodes from the leftmost node to the rightmost node.
 *      - If multiple nodes overlap at the same horizontal position, only
 *        the topmost (closest to the root) node is included in the view.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *                1                column  0
 *              /   \
 *             2     3             2 -> column -1,  3 -> column +1
 *
 *      Column :   -1     0     +1
 *      Top    :   [2]   [1]    [3]
 *
 *  Input  : root = [1, 2, 3]
 *  Output : [2, 1, 3]
 *  Explanation: The Green colored nodes represents the top view in the
 *               below Binary tree.
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *                   10                    column  0   (row 0)
 *                 /    \
 *               20      30                20 -> -1,  30 -> +1   (row 1)
 *              /  \    /  \
 *            40   60  90   100            40 -> -2,  60 -> 0,
 *                                         90 -> 0,   100 -> +2  (row 2)
 *
 *      Column :   -2     -1      0       +1     +2
 *      Nodes  :  [40]   [20]  [10,60,90] [30]  [100]
 *      Top    :   40     20     10        30    100
 *                              (10 is the highest in column 0,
 *                               60 and 90 are hidden under it)
 *
 *  Input  : root = [10, 20, 30, 40, 60, 90, 100]
 *  Output : [40, 20, 10, 30, 100]
 *  Explanation: The Green colored nodes represents the top view in the
 *               below Binary tree.
 *
 * ----------------------------------------------------------------------------
 *  How to read the column number (same as Vertical Order):
 *      root is column 0.
 *      left child  = parent column - 1
 *      right child = parent column + 1
 *      Top view = the FIRST node (closest to the root) of every column,
 *                 printed from the smallest column to the largest.
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
	 * Nodes with the same HD lie in the same vertical column.
	 *
	 * BFS visits nodes level by level, so the first node encountered for a
	 * horizontal distance is the node closest to the root. Store that value
	 * only if the HD has not been seen before. This prevents deeper nodes
	 * from replacing the visible topmost node.
	 *
	 * The ordered map keeps horizontal distances sorted. Iterating over the
	 * map therefore returns the selected nodes from the leftmost column to
	 * the rightmost column.
	 *
	 * Complexity:
	 *   Time  : O(N log W), where N is the number of nodes and W is the
	 *           number of distinct horizontal distances.
	 *   Space : O(N) for the queue and map.
	 */
	static vector<int> topView(TreeNode *root) {
	    vector<int> ans;

		if (root == nullptr)
            return ans;

		// Map to store the first node at each horizontal distance
        map<int, int> topNodeMap;
		queue<pair<TreeNode*, int>> q; // Pair of node and its horizontal distance
        q.push({root, 0});

		while (!q.empty()) {
			// bfs insures that we are visiting nodes level by level,
			// so the first node we encounter at each horizontal distance is the topmost node for that distance.
			// hd -> horizontal distance of the current node from the root
			auto [node, hd] = q.front();
            q.pop();

            // If this horizontal distance is not already in the map, add it
            if (topNodeMap.find(hd) == topNodeMap.end())
                topNodeMap[hd] = node->val;


            // Add left and right children to the queue with updated horizontal distances
            if (node->left != nullptr)
                q.push({node->left, hd - 1});

            if (node->right)
                q.push({node->right, hd + 1});
        }

		// Extract the values from the map in order of their horizontal distances
		for (const auto& [hd, val] : topNodeMap)
			ans.push_back(val);

		return ans;
	}

	/*
	 * Approach 2: Breadth-First Search (BFS) with a hash map
	 *
	 * Idea:
	 * Apply the same BFS rule as Approach 1, but store columns in an
	 * unordered_map. For each horizontal distance, insert only the first
	 * node encountered. Since BFS is level-order, that first node is the
	 * closest node to the root and is exactly the node required in the top
	 * view.
	 *
	 * Because an unordered_map has no ordering, maintain minCol and maxCol
	 * while assigning horizontal distances. Horizontal distances between
	 * these bounds are contiguous, so iterating from minCol through maxCol
	 * produces the result in left-to-right order.
	 *
	 * Complexity:
	 *   Time  : O(N) average, including traversal and output.
	 *   Space : O(N) for the queue and hash map.
	 */
	static vector<int> topView2(TreeNode *root) {
	    vector<int> ans;

		if (root == nullptr)
			return ans;

		// Map to store the first node at each horizontal distance
		unordered_map<int, int> topNodeMap;
		int minCol = 0; // Minimum horizontal distance encountered
		int maxCol = 0; // Maximum horizontal distance encountered

		queue<pair<TreeNode*, int>> q; // Pair of node and its horizontal distance
		q.push({root, 0});

		while (!q.empty()){
			auto [node, hd] = q.front();
			q.pop();

			// If this horizontal distance is not already in the map, add it
			if (!topNodeMap.contains(hd))
				topNodeMap[hd] = node->val;

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
			ans.push_back(topNodeMap[i]);

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
	const vector<int> topViewResult = Solution::topView(root);
	cout << "Top view of the binary tree (Approach 1): ";
	printOutput(topViewResult);

	// Approach 2: Using BFS + unordered_map + min-max horizontal distance
	const vector<int> topViewResult2 = Solution::topView2(root);
	cout << "Top view of the binary tree (Approach 2): ";
	printOutput(topViewResult2);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}