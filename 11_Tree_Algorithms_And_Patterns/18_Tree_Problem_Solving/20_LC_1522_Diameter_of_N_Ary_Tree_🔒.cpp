/*
Author: Sarvan Yaduvanshi
Created : 2026-11-11 18:44:31
*/

/*
 * ============================================================================
 *  1522. Diameter of N-Ary Tree  (LeetCode Premium)
 * ============================================================================
 *  Platform   : LeetCode
 *  Problem No : 1522
 *  Difficulty : Medium
 *  Topics     : Depth-First Search, Tree, Tree DP
 *  Companies  : Amazon, Microsoft, Google, Meta, Apple, Bloomberg, Uber
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given a root of an N-ary tree, you need to compute the length of the
 *  diameter of the tree.
 *
 *  The diameter of an N-ary tree is the length of the longest path between
 *  any two nodes in the tree. This path may or may not pass through the
 *  root.
 *
 *  (Nary-Tree input serialization is represented in their level order
 *  traversal, each group of children is separated by the null value.)
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *                  1
 *                / | \
 *               3  2  4
 *              / \
 *             5   6
 *
 *      Longest path : 5 -> 3 -> 1 -> 2   (3 edges)
 *      Other paths  : 5 -> 3 -> 1 -> 4, 6 -> 3 -> 1 -> 2, 6 -> 3 -> 1 -> 4
 *
 *  Input  : root = [1,null,3,2,4,null,5,6]
 *  Output : 3
 *  Explanation: Diameter is shown in red color.
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *                  1
 *                  |
 *                  2
 *                 / \
 *                3   4
 *                |   |
 *                5   6
 *
 *      Longest path : 5 -> 3 -> 2 -> 4 -> 6   (4 edges)
 *      The path does NOT pass through the root 1.
 *
 *  Input  : root = [1,null,2,null,3,4,null,5,null,6]
 *  Output : 4
 *
 * ----------------------------------------------------------------------------
 *  Example 3:
 *
 *                       1
 *                 /   /   \   \
 *                2   3     4   5
 *                   / \    |   / \
 *                  6   7   8   9  10
 *                      |   |   |
 *                     11  12  13
 *                      |
 *                     14
 *
 *      Longest path : 14 -> 11 -> 7 -> 3 -> 1 -> 4 -> 8 -> 12   (7 edges)
 *      Also 7 edges : 14 -> 11 -> 7 -> 3 -> 1 -> 5 -> 9 -> 13
 *
 *  Input  : root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,
 *                   null,11,null,12,null,13,null,null,14]
 *  Output : 7
 *
 * ----------------------------------------------------------------------------
 *  How to read the serialization (Example 2):
 *
 *      [1, null, 2, null, 3, 4, null, 5, null, 6]
 *      Group of 1 : 2
 *      Group of 2 : 3, 4
 *      Group of 3 : 5
 *      Group of 4 : 6
 *      Each group is closed by null, groups come in level order.
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - The depth of the n-ary tree is less than or equal to 1000.
 *      - The total number of nodes is between [1, 10^4].
 * ============================================================================
 */

#include "../00_Tree_Utilities/03_NaryTree.h"
#include "../00_Tree_Utilities/04_PrintNaryTree.h"
/*
 * Definition for a Node.
 * class Node {
 * public:
 *     int val;
 *     vector<Node*> children;
 *
 *     Node() {}
 *
 *     Node(int _val) {
 *         val = _val;
 *     }
 *
 *     Node(int _val, vector<Node*> _children) {
 *         val = _val;
 *         children = _children;
 *     }
 * };
 */

class Solution{
public:
	static int diameterOfBinaryTree(Node* root){
		// ans hold the maximum diameter found so far
		int ans = 0;

		// Lambda function to calculate the height of a node and update the diameter
		auto height = [&](auto&& self, Node* node) -> int {
			// Base case: If the node is null, return height as 0
			if (node == nullptr)
				return 0;

			// Store the heights of all children
			vector<int> child_heights;
			for (Node* child : node->children)
				child_heights.push_back(self(self, child));

			// Sort the heights in descending order to find the two largest heights
			ranges::sort(child_heights, std::greater<int>());

			// If there are at least two children, update the diameter
			if (child_heights.size() >= 2)
				ans = max(ans, child_heights[0] + child_heights[1]);
			else if (child_heights.size() == 1)
				ans = max(ans, child_heights[0]); // Update diameter if there's only one child

			return child_heights.empty() ? 1 : child_heights[0] + 1; // Return the height of the current node
		};

		height(height, root);
		return ans; // Return the maximum diameter found
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

	Node* root = buildNaryTree(values);
	N_ary_TreeVisualization::printNAryTree<Node>(root, "N-ary Tree visualization");

	// Approach 1: Calculate diameter using DFS + Outside lambda + [&]: Shared variable across recursive calls.
	const int diameterBruteForce = Solution::diameterOfBinaryTree(root);
	cout << "Diameter of N-ary Tree (DFS + Outside lambda + [&]): " << diameterBruteForce << "\n";

}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}