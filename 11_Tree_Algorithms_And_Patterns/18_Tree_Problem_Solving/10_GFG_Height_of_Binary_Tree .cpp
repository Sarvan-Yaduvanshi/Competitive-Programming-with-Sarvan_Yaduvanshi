/*
Author: Sarvan Yaduvanshi
Created : 2026-11-07 06:25:39
*/

/*
 * ============================================================================
 *  Height of Binary Tree
 * ============================================================================
 *  Platform   : GeeksforGeeks
 *  Problem No : N/A (GFG has no number)
 *  Difficulty : Easy
 *  Topics     : Tree
 *  Companies  : VMWare, Zoho, Amazon, Microsoft, Snapdeal, D-E-Shaw,
 *               FactSet, MakeMyTrip, Teradata, Synopsys, CouponDunia,
 *               Cadence India, Monotype Solutions, FreeCharge
 * ----------------------------------------------------------------------------
 *
 *  Problem Statement:
 *  Given the root of a binary tree, find the maximum depth of the tree.
 *
 *  Note: The maximum depth or height of the tree is the number of edges in
 *  the tree from the root to the deepest node.
 *
 * ----------------------------------------------------------------------------
 *  Example 1:
 *
 *              12               Level 0
 *             /  \
 *            8    18            Level 1
 *           / \
 *          5   11               Level 2
 *
 *  Input  : root = [12, 8, 18, 5, 11]
 *  Output : 2
 *  Explanation: One of the longest path from the root (node 12) goes
 *               through node 8 to node 5, which has 2 edges.
 *
 * ----------------------------------------------------------------------------
 *  Example 2:
 *
 *              1                Level 0
 *             / \
 *            2   3              Level 1
 *           /   / \
 *          4   10  5            Level 2
 *                 / \
 *                6   7          Level 3
 *
 *  Input  : root = [1, 2, 3, 4, N, 10, 5, N, N, N, N, 6, 7]
 *  Output : 3
 *  Explanation: The longest path from the root (node 1) to a leaf node 6
 *               with 3 edges.
 *
 * ----------------------------------------------------------------------------
 *  Constraints:
 *      - 1 <= size of binary tree <= 3 * 10^4
 *      - 0 <= Node.data <= 10^5
 *
 * ----------------------------------------------------------------------------
 *  Expected Complexities:
 *      Time Complexity   : O(n)
 *      Auxiliary Space   : O(h)
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <iomanip>
#include <random>
#include <chrono>
using namespace std;

// --- Type Definitions ---
struct TreeNode{
	int val;
	TreeNode* left;
	TreeNode* right;

	// Constructor initializes the node with a value and sets left and right children to nullptr
	explicit TreeNode(const int v) : val(v), left(nullptr), right(nullptr) {}
};

// Approach: Recursive Depth-First Search (DFS) to calculate the height of the binary tree
// Time Complexity: O(n), where n is the number of nodes in the tree
// Space Complexity: O(h), where h is the height of the tree (due to recursion stack)
static int heightOfBinaryTree(const TreeNode* root){
    if (root == nullptr)
        return -1; // Return -1 for null nodes to count edges

    // Recursively calculate the height of left and right subtrees
    const int leftHeight = heightOfBinaryTree(root->left);
    const int rightHeight = heightOfBinaryTree(root->right);

    // Return the maximum height between left and right subtrees, plus 1 for the current edge
    return max(leftHeight, rightHeight) + 1;
}

// Approach: Iterative Breadth-First Search (BFS) to calculate the height of the binary tree
// Time Complexity: O(n), where n is the number of nodes in the tree
// Space Complexity: O(w), where w is the maximum width of the tree (due to the queue)
static int heightOfBinaryTreeIterative(TreeNode* root){
	// Edge case: if the tree is empty, return -1
	if (root == nullptr)
		return -1;

	// Initialize a queue for level-order traversal
	queue<TreeNode*> q;
    q.push(root);

	int levels = 0; // Initialize the level counter

	while (!q.empty()){
        const int size = q.size(); // Get the number of nodes at the current level

        // Process all nodes at the current level
        for (int i = 0; i < size; ++i){
            const TreeNode* node = q.front();
            q.pop();

            // Enqueue left child if it exists
            if (node->left != nullptr)
                q.push(node->left);

            // Enqueue right child if it exists
            if (node->right != nullptr)
                q.push(node->right);
        }

		// Increment the level counter after processing the current level
        levels++;
    }

	return levels - 1; // Return the number of edges, which is levels - 1
}

// Function to build a binary tree from a vector of values (for testing purposes)
static TreeNode* buildTree(const vector<int>& values){
	int n = values.size();

	// Edge case: empty tree or root is null
	if (n == 0 || values[0] == -1)
		return nullptr;

	TreeNode* root = new TreeNode(values[0]);

	queue<TreeNode*> q;
	q.push(root);

	int idx = 1;
	while (!q.empty() && idx < n){
		TreeNode* current = q.front();
		q.pop();

		// Left child
		if (idx < n && values[idx] != -1){
			current->left = new TreeNode(values[idx]);
            q.push(current->left);
		}

		// Move to the next index for the right child
		idx++;

		// Right child
		if (idx < n && values[idx] != -1){
			current->right = new TreeNode(values[idx]);
			q.push(current->right);
		}

		idx++;
	}

	return root;
}

// Function to print traversal result
static void printTraversal(const vector<int>& traversal){
	cout << "Output: \n[";
	for (size_t i = 0; i < traversal.size(); ++i){
		cout << traversal[i];
        if (i < traversal.size() - 1)
            cout << " ";
	}
	cout << "]\n";
}

static void solve(){
	int n;
	cout << "Enter number of nodes in the tree: ";
	cin >> n;

	vector<int> values(n);
	cout << "Enter the values of the nodes (space-separated): ";
	for (int& val : values)
		cin >> val;

	// Print original tree values
	cout << "Original tree values: [";
	for (size_t i = 0; i < values.size(); ++i){
		cout << values[i];
        if (i < values.size() - 1)
            cout << " ";
	}
	cout << "]\n";

	// Build the binary tree from the input values
	TreeNode* root = buildTree(values);

	// Approach 1: Use DFS
	const int height = heightOfBinaryTree(root);
    cout << "Height of the binary tree: " << height << "\n";

	// Approach 2: Use BFS
	const int heightIterative = heightOfBinaryTreeIterative(root);
	    cout << "Height of the binary tree (iterative): " << heightIterative << "\n";
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}