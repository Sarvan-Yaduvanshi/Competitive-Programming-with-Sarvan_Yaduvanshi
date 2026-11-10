/*
Author: Sarvan Yaduvanshi
Created : 2026-11-02 22:57:00
*/

/*
 * ============================================================================
 *  TREE TRAVERSAL PATTERN 1: PREORDER TRAVERSAL (Root -> Left -> Right)
 *  Time: O(N)  |  Space: O(H)   (H = height of tree)
 * ============================================================================
 *
 *  What is Tree Traversal?
 *    Visiting every node of a tree exactly once, in some fixed order.
 *    A tree has no single "next" like an array, so we need a rule for order.
 *
 *    Two big families:
 *      DFS (go deep first) : Preorder, Inorder, Postorder
 *      BFS (go level wise) : Level Order
 *
 * ----------------------------------------------------------------------------
 *  What is Preorder?
 *
 *    Rule (NLR):   1. Visit ROOT (Node)
 *                  2. Traverse LEFT subtree
 *                  3. Traverse RIGHT subtree
 *
 *    Name trick:  PRE = root comes BEFORE its children.
 *    Easy line :  "Print the node the FIRST time you arrive at it."
 *
 *    Same rule is applied to EVERY subtree, not only the main root.
 *    That is why recursion fits this problem so well.
 *
 * ----------------------------------------------------------------------------
 *  EXAMPLE 1: Full Binary Tree
 *
 *              1
 *             / \
 *            2   3
 *           / \   \
 *          4   5   6
 *
 *    Preorder Output : [1, 2, 4, 5, 3, 6]
 *
 *    Recursion Dry Run (call stack view, indent = depth):
 *
 *      preorder(1)  -> VISIT 1
 *        preorder(2)  -> VISIT 2
 *          preorder(4)  -> VISIT 4
 *            preorder(null) -> return
 *            preorder(null) -> return
 *          preorder(5)  -> VISIT 5
 *            preorder(null) -> return
 *            preorder(null) -> return
 *        preorder(3)  -> VISIT 3
 *          preorder(null) -> return        (3 has no left child)
 *          preorder(6)  -> VISIT 6
 *            preorder(null) -> return
 *            preorder(null) -> return
 *
 *    Result: 1, 2, 4, 5, 3, 6
 *
 * ----------------------------------------------------------------------------
 *  EXAMPLE 2: Uneven Tree (left child has only a right child)
 *
 *                 10
 *                /  \
 *               5    15
 *              /    /  \
 *             3    12   20
 *              \
 *               4
 *
 *    Preorder Output : [10, 5, 3, 4, 15, 12, 20]
 *
 *    Step by step:
 *      Visit 10                  -> go left
 *      Visit 5                   -> go left
 *      Visit 3                   -> left is null, go right
 *      Visit 4                   -> no children, go back up to 10
 *      Right of 10: Visit 15     -> go left
 *      Visit 12                  -> no children, back to 15
 *      Right of 15: Visit 20     -> done
 *
 *    Result: 10, 5, 3, 4, 15, 12, 20
 *
 *    Lesson: the whole LEFT subtree of a node finishes before its RIGHT
 *    subtree starts. Node 4 (deep inside left) comes before 15.
 *
 * ----------------------------------------------------------------------------
 *  EXAMPLE 3: Edge Cases
 *
 *      Empty tree   (root = null)  ->  []
 *      Single node  [7]            ->  [7]
 *
 *      Skewed (only right children):   1 -> 2 -> 3
 *      Preorder : [1, 2, 3]   (height H = N, worst case stack)
 *
 * ----------------------------------------------------------------------------
 *  HOW TO CODE IT: 3 Approaches (concept only)
 *
 *  Approach 1: Recursive (simplest)
 *    - Base case : node == nullptr -> return.
 *    - Visit node (store its value).
 *    - Recurse left.
 *    - Recurse right.
 *    - Order of these 3 lines IS the traversal. Move the "visit" line and
 *      you get inorder or postorder.
 *    - Time O(N), Space O(H) call stack.
 *
 *  Approach 2: Iterative with Stack (interview favourite)
 *    - Push root on stack.
 *    - While stack not empty:
 *        pop node, VISIT it,
 *        push RIGHT child first (if exists),
 *        push LEFT child second (if exists).
 *    - Why right first? Stack is LIFO. Left is pushed last, so left
 *      is popped first. That gives Root -> Left -> Right.
 *    - Time O(N), Space O(H) for balanced, O(N) for skewed.
 *
 *    Dry run on Example 1 (stack top is at the right):
 *
 *      Start        : stack = [1]
 *      pop 1, visit : push 3, push 2     stack = [3, 2]
 *      pop 2, visit : push 5, push 4     stack = [3, 5, 4]
 *      pop 4, visit : no children        stack = [3, 5]
 *      pop 5, visit : no children        stack = [3]
 *      pop 3, visit : push 6             stack = [6]
 *      pop 6, visit : no children        stack = []
 *
 *      Output: 1, 2, 4, 5, 3, 6   (same as recursion)
 *
 *    Dry run on Example 2:
 *
 *      Start         : stack = [10]
 *      pop 10, visit : push 15, push 5       stack = [15, 5]
 *      pop 5,  visit : push 3 (right null)   stack = [15, 3]
 *      pop 3,  visit : push 4                stack = [15, 4]
 *      pop 4,  visit : no children           stack = [15]
 *      pop 15, visit : push 20, push 12      stack = [20, 12]
 *      pop 12, visit : no children           stack = [20]
 *      pop 20, visit : no children           stack = []
 *
 *      Output: 10, 5, 3, 4, 15, 12, 20
 *
 *  Approach 3: Morris Traversal (advanced, O(1) space)
 *    - No recursion, no stack. Uses temporary "thread" links from the
 *      rightmost node of the left subtree back to the current node.
 *    - Threads are removed again, so tree is restored.
 *    - Time O(N), Space O(1). Learn this LAST.
 *
 * ----------------------------------------------------------------------------
 *  Compare with other traversals (Example 1 tree):
 *
 *      Preorder   (N L R) : 1 2 4 5 3 6
 *      Inorder    (L N R) : 4 2 5 1 3 6
 *      Postorder  (L R N) : 4 5 2 6 3 1
 *      Level Order (BFS)  : 1 2 3 4 5 6
 *
 *    Only the position of "visit" changes in DFS:
 *      before children = preorder, between = inorder, after = postorder.
 *
 * ----------------------------------------------------------------------------
 *  When to use Preorder?
 *    - Copy / clone a tree (create parent first, then children).
 *    - Serialize a tree (save root first, so rebuilding is easy).
 *    - Prefix expression from an expression tree.
 *    - Any task where parent must be processed BEFORE its children.
 *    - Printing folder structure (folder name first, then its contents).
 *
 * ----------------------------------------------------------------------------
 *  Complexity:
 *    Time  : O(N) - every node visited exactly once.
 *    Space : O(H) - recursion stack or explicit stack.
 *            Balanced tree : H = log N
 *            Skewed tree   : H = N  (worst case)
 *
 * ----------------------------------------------------------------------------
 *  Common Mistakes:
 *    1. Forgetting the base case (node == nullptr) -> crash.
 *    2. Iterative: pushing LEFT before RIGHT -> output becomes Root,
 *       Right, Left (wrong).
 *    3. Pushing nullptr into the stack, then reading ->val on it.
 *    4. Returning vector by value inside every recursive call. Use one
 *       shared vector passed by reference.
 *    5. Mixing up preorder with level order. Preorder goes DEEP first.
 *
 * ----------------------------------------------------------------------------
 *  Practice Problems (in order):
 *    144. Binary Tree Preorder Traversal         (Easy)   <- start here
 *    589. N-ary Tree Preorder Traversal          (Easy)
 *    100. Same Tree                              (Easy)
 *    572. Subtree of Another Tree                (Easy)
 *    105. Construct Binary Tree from Preorder
 *         and Inorder Traversal                  (Medium)
 *    114. Flatten Binary Tree to Linked List     (Medium)
 *    297. Serialize and Deserialize Binary Tree  (Hard)
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <climits>
#include <random>
#include <chrono>
#include <cassert>
using namespace std;

// --- Type Definitions ---
struct TreeNode{
	int val;
	TreeNode* left;
	TreeNode* right;

	// Constructor initializes the node with a value and sets left and right children to nullptr
	explicit TreeNode(const int v) : val(v), left(nullptr), right(nullptr) {}
};

// Approach 1: Recursive Preorder Traversal
// Time Complexity: O(N) - each node is visited once
// Space Complexity: O(H) - recursion stack, where H is the height of the tree
static vector<int> preorderTraversal(const TreeNode* root){
	vector<int> ans;

	// Lambda function for recursive preorder traversal
	auto preorder = [&](auto&& self, const TreeNode* node) -> void {
		// Base case: if the current node is null, return
		if (node == nullptr)
			return;

		// preorder ans: root -> left -> right

		// Visit the current node (root) and add its value to the answer vector
		ans.push_back(node->val);

		// Recursively traverse the left subtree
		self(self, node->left);

		// Recursively traverse the right subtree
		self(self, node->right);
	};

	preorder(preorder, root);
	return ans;
}

// Approach 2: Iterative Preorder Traversal using Stack
// Time Complexity: O(N) - each node is visited once
// Space Complexity: O(H) - stack space, where H is the height of the tree
static vector<int> preorderTraversalApproach2(TreeNode* root){
	vector<int> ans;

	// Edge case: if the root is null, return an empty vector
	if (root == nullptr)
		return ans;

	// Use a stack to simulate the recursive call stack for preorder traversal
	stack<TreeNode*> st;
	st.push(root); // Push the root node onto the stack to start the traversal

	// Continue the traversal until the stack is empty
	while (!st.empty()){
		// Pop the top node from the stack and visit it
		TreeNode* curr = st.top();
		st.pop();

		// Add the value of the current node to the answer vector
		ans.push_back(curr->val);

		// Push the right child first so that the left child is processed next (LIFO order)
		if (curr->right != nullptr)
			st.push(curr->right);

		// Push the left child onto the stack to be processed after the right child
		if (curr->left != nullptr)
			st.push(curr->left);
	}

	return ans;
}


// Approach 3: Morris Preorder Traversal
//
// Morris traversal avoids both recursion and an auxiliary stack by temporarily
// connecting the rightmost node of the current node's left subtree back to the
// current node. This temporary connection is called a thread.
//
// For preorder (Root -> Left -> Right):
//   1. If the current node has no left child, visit it and move right.
//   2. Otherwise, find its inorder predecessor (the rightmost node in the
//      left subtree).
//   3. If the predecessor has no thread, create one, visit the current node,
//      and move left.
//   4. If the predecessor already points to the current node, remove the
//      thread and move right.
//
// The second encounter of a node with a left child is only used to remove its
// thread; the node is not visited again. Therefore, the tree is restored before
// the function returns.
//
// Dry run using this tree:
//
//              1
//             / \
//            2   3
//           / \   \
//          4   5   6
//
//   curr = 1: predecessor = 5, create 5 -> 1, visit 1, move to 2
//   curr = 2: predecessor = 4, create 4 -> 2, visit 2, move to 4
//   curr = 4: no left child, visit 4, follow thread to 2
//   curr = 2: thread 4 -> 2 exists, remove it, move to 5
//   curr = 5: no left child, visit 5, follow thread to 1
//   curr = 1: thread 5 -> 1 exists, remove it, move to 3
//   curr = 3: no left child, visit 3, move to 6
//   curr = 6: no left child, visit 6, move to nullptr
//
// Output: [1, 2, 4, 5, 3, 6]
//
// Time Complexity: O(N) - each temporary thread is created and removed once.
// Space Complexity: O(1) auxiliary space (the returned answer is not counted).
static vector<int> preorderTraversalUseMorrisAlgo(TreeNode* root){
	vector<int> ans;

	// Edge case: if the root is null, return an empty vector
	if (root == nullptr)
		return ans;

	// Start with the current node as the root
	TreeNode* curr = root;

	// Continue the traversal until there are no more nodes to process
	while (curr != nullptr) {
		// Case 1: If the current node has no left child
		if (curr->left == nullptr) {
			ans.push_back(curr->val); // visit the current node(store its value to the answer vector)
			curr = curr->right; // move to the right child

		// Case 2: If the current node has a left child, find its inorder predecessor
        } else {
        	// Find the rightmost node in the left subtree (inorder predecessor)
            TreeNode* predecessor = curr->left;
            while (predecessor->right != nullptr && predecessor->right != curr)
            	// Move to the right child until we find the left subtree's rightmost node
                predecessor = predecessor->right;

            // Case 2a: If the predecessor's right child is null, create a temporary thread
            if (predecessor->right == nullptr){
                predecessor->right = curr; // create a temporary thread
                ans.push_back(curr->val); // visit the current node(store its value to the answer vector)
                curr = curr->left; // move to the left child

            // Case 2b: If the predecessor's right child already points to the current node, remove the thread
            } else{
	            predecessor->right = nullptr; // remove the temporary thread
            	curr = curr->right; // move to the right child
            }
		}
	}

	return ans;
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
	cout << "Preorder Traversal Output: [";
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

	// Approach 1: Recursive Preorder Traversal
	vector<int> preorderResult = preorderTraversal(root);
	printTraversal(preorderResult);

	// Approach 2: Iterative Preorder Traversal
	vector<int> iterativePreorderResult = preorderTraversalApproach2(root);
	printTraversal(iterativePreorderResult);

	// Approach 3: Morris Preorder Traversal
	vector<int> morrisPreorderResult = preorderTraversalUseMorrisAlgo(root);
	printTraversal(morrisPreorderResult);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}
