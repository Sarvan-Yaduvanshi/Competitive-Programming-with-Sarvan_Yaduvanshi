/*
Author: Sarvan Yaduvanshi
Created : 2026-11-03 12:12:28
*/

/*
 * ============================================================================
 *  TREE TRAVERSAL PATTERN 2: INORDER TRAVERSAL (Left -> Root -> Right)
 *  Time: O(N)  |  Space: O(H) recursive/stack, O(1) Morris  (H = height)
 * ============================================================================
 *
 *  What is Inorder?
 *
 *    Rule (LNR):   1. Traverse LEFT subtree
 *                  2. Visit ROOT (Node)
 *                  3. Traverse RIGHT subtree
 *
 *    Name trick : IN = root comes IN BETWEEN its children.
 *    Easy line  : "Print the node when you come BACK UP from the left."
 *
 *    Same rule is applied to EVERY subtree, not only the main root.
 *
 *  Golden Fact (VERY IMPORTANT):
 *    Inorder of a BST (Binary Search Tree) gives values in SORTED order.
 *    This is the reason inorder is the most asked traversal in interviews.
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
 *    Inorder Output : [4, 2, 5, 1, 3, 6]
 *
 * ----------------------------------------------------------------------------
 *  EXAMPLE 2: Uneven Tree (this is also a BST)
 *
 *                 10
 *                /  \
 *               5    15
 *              /    /  \
 *             3    12   20
 *              \
 *               4
 *
 *    Inorder Output : [3, 4, 5, 10, 12, 15, 20]   <== SORTED (BST)
 *
 * ----------------------------------------------------------------------------
 *  EXAMPLE 3: Edge Cases
 *
 *      Empty tree  (root = null)   ->  []       (early return in all 3)
 *      Single node [7]             ->  [7]
 *
 *      Right skewed :  1 -> 2 -> 3             Inorder : [1, 2, 3]
 *      Left skewed  :      3                   Inorder : [1, 2, 3]
 *                         /                    (height H = N, worst case)
 *                        2
 *                       /
 *                      1
 *
 * ============================================================================
 *  APPROACH 1: RECURSIVE (lambda with self, your Approach 1)
 * ============================================================================
 *
 *    - Edge case : root == nullptr -> return empty vector.
 *    - Lambda takes (self, node). "self" lets a lambda call itself.
 *    - Base case : node == nullptr -> return.
 *    - Order of the 3 lines is the whole traversal:
 *          self(node->left)        <- go left FIRST
 *          ans.push_back(node->val)<- VISIT in the middle
 *          self(node->right)       <- go right LAST
 *    - "ans" is captured by reference [&], so one shared vector is used.
 *    - Time O(N), Space O(H) call stack.
 *
 *    Dry Run, Example 1 (indent = depth, VISIT happens AFTER left returns):
 *
 *      inorder(1)
 *        inorder(2)
 *          inorder(4)
 *            inorder(null) -> return
 *            VISIT 4
 *            inorder(null) -> return
 *          VISIT 2
 *          inorder(5)
 *            inorder(null) -> return
 *            VISIT 5
 *            inorder(null) -> return
 *        VISIT 1
 *        inorder(3)
 *          inorder(null) -> return          (3 has no left child)
 *          VISIT 3
 *          inorder(6)
 *            inorder(null) -> return
 *            VISIT 6
 *            inorder(null) -> return
 *
 *      Result: 4, 2, 5, 1, 3, 6
 *
 *    Dry Run, Example 2:
 *
 *      inorder(10)
 *        inorder(5)
 *          inorder(3)
 *            inorder(null) -> return
 *            VISIT 3
 *            inorder(4)
 *              inorder(null) -> return
 *              VISIT 4
 *              inorder(null) -> return
 *          VISIT 5
 *          inorder(null) -> return          (5 has no right child)
 *        VISIT 10
 *        inorder(15)
 *          inorder(12)
 *            inorder(null) -> return
 *            VISIT 12
 *            inorder(null) -> return
 *          VISIT 15
 *          inorder(20)
 *            inorder(null) -> return
 *            VISIT 20
 *            inorder(null) -> return
 *
 *      Result: 3, 4, 5, 10, 12, 15, 20
 *
 *    Dry Run, Example 3 (edge):
 *      Single [7] : inorder(7) -> null, VISIT 7, null          -> [7]
 *      Empty      : early return                               -> []
 *
 * ============================================================================
 *  APPROACH 2: ITERATIVE WITH STACK (your Approach 2)
 * ============================================================================
 *
 *    - Use stack<TreeNode*> st and pointer curr = root.
 *    - Outer loop : while (!st.empty() || curr != nullptr)
 *        (stack empty AND curr null = everything done)
 *    - Step A (GO LEFT)  : while curr != null -> push curr, curr = curr->left.
 *    - Step B (POP)      : curr = st.top(); st.pop();
 *    - Step C (VISIT)    : ans.push_back(curr->val);
 *    - Step D (GO RIGHT) : curr = curr->right;
 *    - Idea: stack remembers "nodes whose left side is being explored".
 *      Pop = left side finished -> time to visit that node.
 *    - Time O(N), Space O(H) (O(N) for left skewed tree).
 *
 *    Dry Run, Example 1 (stack: bottom -> top, top at the right):
 *
 *      Step A : push 1, push 2, push 4, curr = null    stack = [1, 2, 4]
 *      Step B-D: pop 4, VISIT 4, curr = 4.right = null stack = [1, 2]
 *      Loop   : stack not empty, skip Step A
 *               pop 2, VISIT 2, curr = 2.right = 5     stack = [1]
 *      Step A : push 5, curr = 5.left = null           stack = [1, 5]
 *               pop 5, VISIT 5, curr = null            stack = [1]
 *               pop 1, VISIT 1, curr = 1.right = 3     stack = []
 *      Step A : push 3, curr = 3.left = null           stack = [3]
 *               pop 3, VISIT 3, curr = 3.right = 6     stack = []
 *      Step A : push 6, curr = null                    stack = [6]
 *               pop 6, VISIT 6, curr = null            stack = []
 *      End    : stack empty AND curr null -> STOP
 *
 *      Output: 4, 2, 5, 1, 3, 6
 *
 *    Dry Run, Example 2:
 *
 *      Step A : push 10, push 5, push 3, curr = null   stack = [10, 5, 3]
 *               pop 3, VISIT 3, curr = 3.right = 4     stack = [10, 5]
 *      Step A : push 4, curr = null                    stack = [10, 5, 4]
 *               pop 4, VISIT 4, curr = null            stack = [10, 5]
 *               pop 5, VISIT 5, curr = 5.right = null  stack = [10]
 *               pop 10, VISIT 10, curr = 10.right = 15 stack = []
 *      Step A : push 15, push 12, curr = null          stack = [15, 12]
 *               pop 12, VISIT 12, curr = null          stack = [15]
 *               pop 15, VISIT 15, curr = 15.right = 20 stack = []
 *      Step A : push 20, curr = null                   stack = [20]
 *               pop 20, VISIT 20, curr = null          stack = []
 *      End    : STOP
 *
 *      Output: 3, 4, 5, 10, 12, 15, 20
 *
 *    Dry Run, Example 3 (left skewed 3 -> 2 -> 1, worst case stack):
 *
 *      Step A : push 3, push 2, push 1, curr = null    stack = [3, 2, 1]
 *               pop 1, VISIT 1, curr = null            stack = [3, 2]
 *               pop 2, VISIT 2, curr = null            stack = [3]
 *               pop 3, VISIT 3, curr = null            stack = []
 *      Output: 1, 2, 3     (stack grew to size N = 3)
 *
 * ============================================================================
 *  APPROACH 3: MORRIS TRAVERSAL (your Approach 3, O(1) space)
 * ============================================================================
 *
 *    - No recursion, no stack. Uses TEMPORARY thread links.
 *    - Thread = right pointer of the INORDER PREDECESSOR points back to curr.
 *    - Inorder Predecessor of curr = rightmost node in curr's left subtree.
 *
 *    Loop while curr != nullptr:
 *
 *      Case 1: curr->left == nullptr
 *          VISIT curr, then curr = curr->right.
 *          (right may be a real child OR a thread going back up)
 *
 *      Case 2: curr->left exists
 *          Find predecessor: start at curr->left, keep going right while
 *          (pred->right != null AND pred->right != curr).
 *
 *          Case 2a: pred->right == nullptr   (FIRST time here)
 *              Make thread: pred->right = curr.
 *              Go left: curr = curr->left.      (NO visit yet)
 *
 *          Case 2b: pred->right == curr      (SECOND time, came back)
 *              Remove thread: pred->right = nullptr.   (tree restored)
 *              VISIT curr.
 *              Go right: curr = curr->right.
 *
 *    - Why visit in 2b and not 2a? In 2b the left subtree is fully done.
 *      Left done -> visit node = INORDER rule.
 *    - (Preorder Morris visits in 2a instead. Only that one line moves.)
 *    - Every edge is walked at most 2-3 times, so Time O(N). Space O(1).
 *
 *    Dry Run, Example 1:
 *
 *      curr=1 : left=2. pred: 2 -> 5 (5.right null). 2a: thread 5->1.
 *               curr = 2
 *      curr=2 : left=4. pred=4 (4.right null). 2a: thread 4->2.
 *               curr = 4
 *      curr=4 : left null. Case 1: VISIT 4. curr = 4.right = 2 (thread)
 *      curr=2 : left=4. pred=4, 4.right == 2 == curr. 2b: remove thread.
 *               VISIT 2. curr = 2.right = 5
 *      curr=5 : left null. Case 1: VISIT 5. curr = 5.right = 1 (thread)
 *      curr=1 : left=2. pred: 2 -> 5, 5.right == 1 == curr. 2b: remove
 *               thread. VISIT 1. curr = 1.right = 3
 *      curr=3 : left null. Case 1: VISIT 3. curr = 6
 *      curr=6 : left null. Case 1: VISIT 6. curr = null
 *      End    : STOP, all threads removed, tree is same as before.
 *
 *      Output: 4, 2, 5, 1, 3, 6
 *
 *    Dry Run, Example 2:
 *
 *      curr=10: left=5. pred=5 (5.right null). 2a: thread 5->10.
 *               curr = 5
 *      curr=5 : left=3. pred: 3 -> 4 (4.right null). 2a: thread 4->5.
 *               curr = 3
 *      curr=3 : left null. Case 1: VISIT 3. curr = 3.right = 4
 *      curr=4 : left null. Case 1: VISIT 4. curr = 4.right = 5 (thread)
 *      curr=5 : left=3. pred: 3 -> 4, 4.right == 5 == curr. 2b: remove
 *               thread. VISIT 5. curr = 5.right = 10 (thread)
 *      curr=10: left=5. pred=5, 5.right == 10 == curr. 2b: remove thread.
 *               VISIT 10. curr = 10.right = 15
 *      curr=15: left=12. pred=12 (12.right null). 2a: thread 12->15.
 *               curr = 12
 *      curr=12: left null. Case 1: VISIT 12. curr = 12.right = 15 (thread)
 *      curr=15: left=12. pred=12, 12.right == 15 == curr. 2b: remove
 *               thread. VISIT 15. curr = 15.right = 20
 *      curr=20: left null. Case 1: VISIT 20. curr = null
 *      End    : STOP
 *
 *      Output: 3, 4, 5, 10, 12, 15, 20
 *
 *    Dry Run, Example 3 (left skewed 3 -> 2 -> 1):
 *
 *      curr=3 : left=2. pred=2 (2.right null). 2a: thread 2->3. curr = 2
 *      curr=2 : left=1. pred=1 (1.right null). 2a: thread 1->2. curr = 1
 *      curr=1 : left null. VISIT 1. curr = 1.right = 2 (thread)
 *      curr=2 : pred=1, 1.right == 2. 2b: remove, VISIT 2. curr = 3
 *      curr=3 : pred=2, 2.right == 3. 2b: remove, VISIT 3. curr = null
 *      Output: 1, 2, 3     (no stack used)
 *
 *      Single [7] : left null, VISIT 7, curr = null          -> [7]
 *
 * ----------------------------------------------------------------------------
 *  Compare all 3 approaches:
 *
 *      Approach     | Time | Space      | Modifies tree? | Difficulty
 *      -------------+------+------------+----------------+-----------
 *      Recursive    | O(N) | O(H)       | No             | Easy
 *      Iterative    | O(N) | O(H)       | No             | Medium
 *      Morris       | O(N) | O(1)       | Temporarily    | Hard
 *
 * ----------------------------------------------------------------------------
 *  Compare with other traversals (Example 1 tree):
 *
 *      Preorder   (N L R) : 1 2 4 5 3 6
 *      Inorder    (L N R) : 4 2 5 1 3 6      <== this one
 *      Postorder  (L R N) : 4 5 2 6 3 1
 *      Level Order (BFS)  : 1 2 3 4 5 6
 *
 * ----------------------------------------------------------------------------
 *  When to use Inorder?
 *    - BST: get sorted values.
 *    - Validate BST (inorder must be strictly increasing).
 *    - Kth smallest / largest element in BST.
 *    - Find inorder successor / predecessor.
 *    - Recover a BST where 2 nodes are swapped.
 *    - Convert BST to sorted list / sorted array.
 *
 * ----------------------------------------------------------------------------
 *  Complexity:
 *    Time  : O(N) - every node visited exactly once.
 *    Space : Recursive / Iterative O(H). Morris O(1).
 *            Balanced tree : H = log N
 *            Skewed tree   : H = N  (worst case)
 *
 * ----------------------------------------------------------------------------
 *  Common Mistakes:
 *    1. Iterative: forgetting "curr = curr->right" after VISIT -> infinite
 *       loop or missing right subtree.
 *    2. Iterative: outer loop uses only !st.empty() -> last right subtree
 *       skipped. Need "|| curr != nullptr".
 *    3. Morris: forgetting "pred->right != curr" in the while -> infinite
 *       loop on the thread.
 *    4. Morris: forgetting to remove the thread -> tree stays broken.
 *    5. Morris: visiting in Case 2a (that is preorder, not inorder).
 *    6. Recursive: forgetting the base case (node == nullptr) -> crash.
 *
 * ----------------------------------------------------------------------------
 *  Practice Problems (in order):
 *    94.  Binary Tree Inorder Traversal           (Easy)   <- start here
 *    530. Minimum Absolute Difference in BST      (Easy)
 *    98.  Validate Binary Search Tree             (Medium)
 *    230. Kth Smallest Element in a BST           (Medium)
 *    173. Binary Search Tree Iterator             (Medium)
 *    285. Inorder Successor in BST                (Medium, Premium)
 *    99.  Recover Binary Search Tree              (Medium)
 *    897. Increasing Order Search Tree            (Easy)
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
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

// Approach 1: Recursive Inorder Traversal
static vector<int> inorderTraversal(const TreeNode* root){
	vector<int> ans;

	// Edge case: if the root is null, return an empty vector
	if (root == nullptr)
		return ans;

	// Recursive lambda function for inorder traversal
	auto inorder = [&](auto&& self, const TreeNode* node) -> void{
		// Base case: if the current node is null, return
		if (node == nullptr)
			return;
		// inorder traversal: visit left subtree, current node, then right subtree

		// Recursive call to the left child
		self(self, node->left);

		// Visit the current node and add its value to the answer vector
		ans.push_back(node->val);

		// Recursive call to the right child
		self(self, node->right);
	};

	inorder(inorder, root);
	return ans;
}

// Approach 2: Iterative Inorder Traversal using a stack
static vector<int> inorderTraversalIterative(TreeNode* root){
	vector<int> ans;

	// Edge case: if the root is null, return an empty vector
	if (root == nullptr)
		return ans;

	// Stack to keep track of nodes and a pointer to the current node
	stack<TreeNode*> st;
	TreeNode* curr = root; // Start with the root node

	// Continue traversing until all nodes are processed
	while (!st.empty() || curr != nullptr){
		// Traverse to the leftmost node of the current subtree
		while (curr != nullptr){
			st.push(curr); // Push the current node onto the stack
			curr = curr->left; // Move to the left child
		}

		curr = st.top(); // save the top node from the stack (the last leftmost node)
		st.pop(); // remove the top node from the stack since we are visiting it now

		// Visit the current node and add its value to the answer vector
		ans.push_back(curr->val);

		// Move to the right child of the current node to continue the traversal
		curr = curr->right;
	}

	return ans;
}

// Approach 3: Morris Inorder Traversal (Threaded Binary Tree)
static vector<int> inorderTraversalMorrisAlgo(TreeNode* root){
	vector<int> ans;

	// Edge case: if the root is null, return an empty vector
	if (root == nullptr)
		return ans;

	// Initialize the current node to the root of the tree
	TreeNode* curr = root;

	// Continue traversing until all nodes are processed
	while (curr != nullptr){
		// Case 1: if the current node has no left child
		if (curr->left == nullptr){
			ans.push_back(curr->val); // store the curr value in the answer vector
			curr = curr->right; // move to the right child of the current node

		// Case 2: if the current node has a left child
		} else{
			// Find the inorder predecessor of the current node (the rightmost node in the left subtree)
			TreeNode* predecessor = curr->left;
			while (predecessor->right != nullptr && predecessor->right != curr)
				predecessor = predecessor->right; // move to the right child until find the rightmost node

			// Case 2a: if the right child of the predecessor is null, create a temporary link to the current node
			if (predecessor->right == nullptr){
				predecessor->right = curr; // create a temporary link to the current node
				curr = curr->left; // move to the left child of the current node

				// Case 2b: if the right child of the predecessor is already
			} else{
				predecessor->right = nullptr; // remove the temporary link to restore the original tree structure
				ans.push_back(curr->val); // store the curr value in the answer vector
				curr = curr->right; // move to the right child of the current node
			}
		}
	}

	return ans;
}

// Function to build a binary tree from a vector of values (for testing purposes)
TreeNode* buildTree(const vector<int>& values){
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
	cout << "Output: [";
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

	// Approach 1: Recursive Inorder Traversal
	vector<int> recursiveResult = inorderTraversal(root);
	cout << "Recursive Inorder Traversal ";
	printTraversal(recursiveResult);

	// Approach 2: Iterative Inorder Traversal
	vector<int> iterativeResult = inorderTraversalIterative(root);
	cout << "Iterative Inorder Traversal ";
	printTraversal(iterativeResult);

	// Approach 3: Morris Inorder Traversal
	vector<int> morrisResult = inorderTraversalMorrisAlgo(root);
	cout << "Morris Inorder Traversal ";
	printTraversal(morrisResult);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}