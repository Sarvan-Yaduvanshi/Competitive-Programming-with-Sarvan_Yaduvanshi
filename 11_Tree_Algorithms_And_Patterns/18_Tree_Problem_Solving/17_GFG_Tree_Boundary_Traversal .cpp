/*
Author: Sarvan Yaduvanshi
Created : 2026-11-11 07:36:28
*/

/*
 * ============================================================================
 *  Tree Boundary Traversal
 *  (LeetCode 545. Boundary of Binary Tree  -  Premium)
 * ============================================================================
 *  Platform   : GeeksforGeeks  +  LeetCode Premium
 *  Problem No : GFG = N/A (GFG has no number)  |  LeetCode = 545
 *  Difficulty : Medium
 *  Topics     : Tree, Binary Tree, Data Structures
 *  Companies  : Flipkart, Morgan Stanley, Accolite, Amazon, Microsoft,
 *               OYO Rooms, Samsung, Snapdeal, FactSet, Hike, Payu,
 *               Kritikal Solutions
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given a root of a Binary Tree, return its boundary traversal in the
 *  following order:
 *
 *      1. Left Boundary : Nodes from the root to the leftmost non-leaf
 *                         node, preferring the left child over the right
 *                         and excluding leaves.
 *      2. Leaf Nodes    : All leaf nodes from left to right, covering
 *                         every leaf in the tree.
 *      3. Reverse Right Boundary : Nodes from the root to the rightmost
 *                         non-leaf node, preferring the right child over
 *                         the left, excluding leaves, and added in reverse
 *                         order.
 *
 *  Note: The root is included once, leaves are added separately to avoid
 *  repetition, and the right boundary follows traversal preference, not the
 *  path from the rightmost leaf.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *                  1
 *                /   \
 *               2     3
 *              / \   / \
 *             4   5 6   7
 *                / \
 *               8   9
 *
 *      Left boundary  : 1, 2          (4 is a leaf, so it is skipped here)
 *      Leaf nodes     : 4, 8, 9, 6, 7
 *      Right boundary : 3             (7 is a leaf, so it is skipped here)
 *      Reversed right : 3
 *
 *  Input  : root = [1, 2, 3, 4, 5, 6, 7, N, N, 8, 9, N, N, N, N]
 *  Output : [1, 2, 4, 8, 9, 6, 7, 3]
 *  Explanation: Left boundary + leaf nodes + reversed right boundary
 *               = [1, 2] + [4, 8, 9, 6, 7] + [3].
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *      1
 *       \
 *        2
 *         \
 *          3
 *           \
 *            4
 *
 *  Input  : root = [1, N, 2, N, 3, N, 4, N, N]
 *  Output : [1, 4, 3, 2]
 *  Explanation:
 *      Left boundary: [1] (as there is no left subtree)
 *      Leaf nodes: [4]
 *      Right boundary: [3, 2] (in reverse order)
 *      Final traversal: [1, 4, 3, 2]
 *
 * ----------------------------------------------------------------------------
 *  Picture (3 parts of the boundary, Example 1):
 *
 *                  [1]                 <== root (taken ONCE)
 *                /     \
 *             [2]       [3]            <== LEFT side going down  | RIGHT side
 *             / \       / \                                      | (printed
 *          [4]  [5]   [6]  [7]         <== LEAVES, left to right |  bottom up)
 *               / \
 *            [8]  [9]                  <== LEAVES
 *
 *      Order printed : left boundary (top -> down)
 *                      leaves        (left -> right)
 *                      right boundary (bottom -> up)
 *
 * ----------------------------------------------------------------------------
 *  GFG Constraints:
 *      - 1 <= number of nodes <= 10^5
 *      - 1 <= node->data <= 10^5
 *
 *  GFG Expected Complexities:
 *      Time Complexity   : O(n)
 *      Auxiliary Space   : O(h)
 *
 * ----------------------------------------------------------------------------
 *  LeetCode 545 version (Premium, same idea):
 *
 *      Example A:
 *          1
 *           \
 *            2
 *           / \
 *          3   4
 *
 *      Input  : root = [1,null,2,3,4]
 *      Output : [1,3,4,2]
 *      Explanation: Left boundary is [1] (no left child). Leaves are [3,4].
 *                   Right boundary is [2], reversed [2].
 *
 *      Example B:
 *                    1
 *                  /   \
 *                 2     3
 *                / \   /
 *               4   5 6
 *                  / \ / \
 *                 7  8 9 10
 *
 *      Input  : root = [1,2,3,4,5,6,null,null,null,7,8,9,10]
 *      Output : [1,2,4,7,8,9,10,6,3]
 *
 *      LeetCode Constraints:
 *          - The number of nodes in the tree is in the range [1, 10^4].
 *          - -1000 <= Node.val <= 1000
 *
 * ----------------------------------------------------------------------------
 *  Approach: Boundary Traversal in Three Simple Parts
 *
 *  Boundary traversal is not a normal preorder, inorder, or postorder
 *  traversal. The boundary is printed in this exact order:
 *
 *      1. Root
 *      2. Left boundary from top to bottom
 *      3. All leaf nodes from left to right
 *      4. Right boundary from bottom to top
 *
 *  Step 1: Identify a leaf node
 *      A leaf has no left child and no right child. Leaves are handled
 *      separately, so they must not be added while collecting either
 *      boundary. This prevents duplicate values.
 *
 *  Step 2: Handle the root
 *      - If the tree is empty, return an empty answer.
 *      - If the root itself is a leaf, add it once and return.
 *      - Otherwise, add the root before processing the three remaining parts.
 *
 *  Step 3: Collect the left boundary
 *      Start from root->left and move downward:
 *      - Add the current node only if it is not a leaf.
 *      - Prefer the left child.
 *      - If the left child does not exist, move to the right child.
 *      This rule is important for trees where the left side has missing
 *      children.
 *
 *  Step 4: Collect all leaves
 *      Use DFS from the root:
 *      - If the current node is null, stop.
 *      - If it is a leaf, add its value.
 *      - Otherwise, recursively visit the left child and then the right child.
 *      Because DFS is left-first, leaves are added from left to right.
 *
 *  Step 5: Collect the right boundary
 *      Start from root->right and move downward:
 *      - Add only non-leaf nodes.
 *      - Prefer the right child.
 *      - If the right child does not exist, move to the left child.
 *      Store these nodes temporarily, then add them in reverse order so that
 *      the final answer travels upward from the bottom-right to the root.
 *
 *  Why are leaves excluded from the boundaries?
 *      Leaves are already collected in Step 4. If they were included in the
 *      left or right boundary as well, the answer would contain duplicates.
 *
 *  Why is the root added only once?
 *      The root is the starting point of both conceptual boundaries, but the
 *      implementation adds it explicitly once and starts boundary scans from
 *      root->left and root->right.
 *
 *  Dry Run 1: General Binary Tree
 *
 *                  1
 *                /   \
 *               2     3
 *              / \   / \
 *             4   5 6   7
 *                / \
 *               8   9
 *
 *  1. Root:
 *         ans = [1]
 *
 *  2. Left boundary, starting at 2:
 *         Add 2; 4 is a leaf, so stop adding boundary nodes.
 *         ans = [1, 2]
 *
 *  3. Leaves, using left-to-right DFS:
 *         4, 8, 9, 6, 7
 *         ans = [1, 2, 4, 8, 9, 6, 7]
 *
 *  4. Right boundary, starting at 3:
 *         Store 3; 7 is a leaf and is skipped.
 *         Reverse the stored values: [3]
 *         ans = [1, 2, 4, 8, 9, 6, 7, 3]
 *
 *  Final boundary traversal = [1, 2, 4, 8, 9, 6, 7, 3]
 *
 *  Dry Run 2: Right-Skewed Tree
 *
 *              1
 *               \
 *                2
 *                 \
 *                  3
 *                   \
 *                    4
 *
 *  1. Root:
 *         ans = [1]
 *  2. Left boundary:
 *         There is no left subtree, so nothing is added.
 *  3. Leaves:
 *         Only 4 is a leaf, so ans = [1, 4].
 *  4. Right boundary:
 *         Store [2, 3]; reverse it to [3, 2].
 *  5. Final answer:
 *         [1, 4, 3, 2]
 *
 *  Complexity:
 *      Time Complexity: O(n)
 *          - The boundary scans visit only paths.
 *          - The leaf DFS visits every node once.
 *          - Therefore, the total work is linear.
 *
 *      Auxiliary Space: O(h)
 *          - O(h) recursion stack for the leaf DFS, where h is tree height.
 *          - O(h) temporary space for the right boundary.
 *          - The returned answer is excluded from auxiliary space.
 *          - In the worst case, h = n, so auxiliary space becomes O(n).
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
	// Approach 1: Use DFS to find the boundary traversal of the binary tree
	static vector<int> boundaryTraversal(TreeNode* root){
		vector<int> ans;

		if (root == nullptr)
			return {};

		// Lambda function to check if a node is a leaf
		auto isLeaf = [&](const TreeNode* node) -> bool{
			// A node is a leaf if it is not null and has no left or right children
			return node != nullptr && node->left == nullptr && node->right == nullptr;
		};

		// Lambda function to add the left boundary nodes (excluding leaves) to the answer
		auto addLeftBoundary = [&](TreeNode* node) -> void{
			TreeNode* curr = node;
			while (curr != nullptr){
				// Add the current node's value to the answer if it is not a leaf
				if (!isLeaf(curr))
					ans.emplace_back(curr->val);

				// Case 1: If the current node has a left child, move to the left child
				if (curr->left != nullptr)
					curr = curr->left;
					// Case 2: curr node has no left child but has a right child, move to the right child
				else
					curr = curr->right;
			}
		};

		// Lambda function to add the right boundary nodes (excluding leaves) to the answer in reverse order
		auto addRightBoundary = [&](TreeNode* node) -> void{
			TreeNode* curr = node;
			// store the value tempporarily vector in reverse order
			vector<int> rev_order;
			while (curr != nullptr){
				// Add the current node's value to the temporary vector if it is not a leaf
				if (!isLeaf(curr))
					rev_order.emplace_back(curr->val);

				// Case 1: If the current node has a right child, move to the right child
				if (curr->right != nullptr)
					curr = curr->right;
					// Case 2: curr node has no right child but has a left child, move to the left child
				else
					curr = curr->left;
			}

			// Traverse the temporary vector in reverse order and add its elements to the answer
			for (int i = static_cast<int>(rev_order.size()) - 1; i >= 0; i--)
				ans.emplace_back(rev_order[i]);
		};

		// Lambda function to add all leaf nodes to the answer
		auto addLeaves = [&](auto&& self, TreeNode* node) -> void{
			// Base case: if the node is null, return
			if (node == nullptr)
				return;

			// If the node is a leaf, add its value to the answer
			if (isLeaf(node))
				ans.emplace_back(node->val);

			self(self, node->left); // Recursively visit the left child
			self(self, node->right); // Recursively visit the right child
		};

		// If the root is a leaf, add its value to the answer and return
		if (isLeaf(root)){
			ans.emplace_back(root->val);
			return ans;
		}

		ans.emplace_back(root->val); // Add the root value to the answer
		addLeftBoundary(root->left); // Add left boundary nodes (excluding leaves) to the answer
		addLeaves(addLeaves, root); // Add all leaf nodes to the answer
		addRightBoundary(root->right); // Add right boundary nodes (excluding leaves) to the answer in reverse order

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

	// Approach 1: Use DFS to find the boundary traversal of the binary tree
	const vector<int> boundary = Solution::boundaryTraversal(root);
	cout << "Boundary Traversal of Binary Tree: ";
	printOutput(boundary);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}