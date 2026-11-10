/*
Author: Sarvan Yaduvanshi
Created : 2026-11-11 00:58:14
*/

/*
 * ============================================================================
 *  TREE TRAVERSAL PATTERN 5: N-ARY TREE PREORDER TRAVERSAL (Root -> Children)
 *  Time: O(N)  |  Space: O(H)   (H = height of tree)
 * ============================================================================
 *
 *  What is an N-ary Tree?
 *
 *    A tree where each node can have ANY number of children (0, 1, 2, 3...).
 *    A binary tree has at most 2 (left, right). N-ary has no such limit.
 *
 *    Node shape:
 *        struct Node {
 *            int val;
 *            vector<Node*> children;    <== list of children, no left/right
 *        };
 *
 * ----------------------------------------------------------------------------
 *  What is Preorder (N-ary)?
 *
 *    Rule:   1. Visit ROOT (Node)
 *            2. Traverse each CHILD subtree, from LEFT to RIGHT
 *               (child[0] first, then child[1], then child[2] ...)
 *
 *    Name trick : PRE = parent comes BEFORE all its children.
 *    Easy line  : "Print the node the FIRST time you arrive at it."
 *
 *    Same rule is applied to EVERY subtree, not only the main root.
 *
 *    Binary vs N-ary:
 *      Binary preorder : Root -> Left -> Right      (2 fixed children)
 *      N-ary preorder  : Root -> child0 -> child1 -> ... -> childK
 *                        (a LOOP over children replaces left/right)
 *
 *    Note: Inorder does NOT exist for N-ary trees (no clear "middle").
 *    Only Preorder, Postorder, and Level Order are used.
 *
 * ----------------------------------------------------------------------------
 *  EXAMPLE 1: Small N-ary Tree
 *
 *                  1
 *                / | \
 *               3  2  4
 *              / \
 *             5   6
 *
 *    Preorder Output : [1, 3, 5, 6, 2, 4]
 *
 * ----------------------------------------------------------------------------
 *  EXAMPLE 2: Bigger N-ary Tree (uneven, 4 levels)
 *
 *                       1
 *                 /   /   \   \
 *                2   3     4   5
 *                   / \    |   / \
 *                  6   7   8   9  10
 *                      |
 *                      11
 *
 *    Preorder Output : [1, 2, 3, 6, 7, 11, 4, 8, 5, 9, 10]
 *
 * ----------------------------------------------------------------------------
 *  EXAMPLE 3: Edge Cases
 *
 *      Empty tree  (root = null)   ->  []       (early return in both)
 *      Single node [7]             ->  [7]      (children list is empty)
 *
 *      Skewed chain  1 -> 2 -> 3   ->  [1, 2, 3]
 *      (height H = N, worst case stack)
 *
 *      Wide tree (root with 4 leaf children 2,3,4,5):
 *                    1
 *                 / | | \
 *                2  3 4  5          ->  [1, 2, 3, 4, 5]
 *
 * ============================================================================
 *  APPROACH 1: RECURSIVE (lambda with self, your Approach 1)
 * ============================================================================
 *
 *    - Edge case : root == nullptr -> return empty vector.
 *    - Lambda takes (self, node). "self" lets a lambda call itself.
 *    - Base case : node == nullptr -> return.
 *    - Order of the lines is the whole traversal:
 *          ans.emplace_back(node->val)          <- VISIT FIRST
 *          for (child : node->children)         <- then every child,
 *              self(self, child)                   left to right
 *    - "ans" is captured by reference [&], so one shared vector is used.
 *    - Loop order = children order, so child[0] is fully done before
 *      child[1] starts.
 *    - Time O(N), Space O(H) call stack.
 *
 *    Dry Run, Example 1 (indent = depth, VISIT happens BEFORE children):
 *
 *      dfs(1) -> VISIT 1
 *        dfs(3) -> VISIT 3
 *          dfs(5) -> VISIT 5        (no children, loop does nothing)
 *          dfs(6) -> VISIT 6        (no children)
 *        dfs(2) -> VISIT 2          (no children)
 *        dfs(4) -> VISIT 4          (no children)
 *
 *      Result: 1, 3, 5, 6, 2, 4
 *
 *    Dry Run, Example 2:
 *
 *      dfs(1) -> VISIT 1
 *        dfs(2) -> VISIT 2          (leaf)
 *        dfs(3) -> VISIT 3
 *          dfs(6) -> VISIT 6        (leaf)
 *          dfs(7) -> VISIT 7
 *            dfs(11) -> VISIT 11    (leaf)
 *        dfs(4) -> VISIT 4
 *          dfs(8) -> VISIT 8        (leaf)
 *        dfs(5) -> VISIT 5
 *          dfs(9)  -> VISIT 9       (leaf)
 *          dfs(10) -> VISIT 10      (leaf)
 *
 *      Result: 1, 2, 3, 6, 7, 11, 4, 8, 5, 9, 10
 *
 *    Dry Run, Example 3 (edge):
 *      Single [7] : dfs(7) -> VISIT 7, children empty       -> [7]
 *      Empty      : early return                            -> []
 *
 * ============================================================================
 *  APPROACH 2: ITERATIVE WITH STACK (your Approach 2)
 * ============================================================================
 *
 *    - Use stack<const Node*> st. It replaces the recursion call stack.
 *    - Push root.
 *    - While stack not empty:
 *        Step A : node = st.top(); st.pop();
 *        Step B : VISIT node (ans.emplace_back(node->val)).
 *        Step C : push children in REVERSE order (last child first,
 *                 first child last), skip null children.
 *    - Why reverse? Stack is LIFO. The LAST pushed is popped FIRST.
 *      Pushing child[n-1] ... child[0] means child[0] is on top, so it is
 *      processed first. That keeps the left to right order.
 *    - Binary tree version pushes RIGHT then LEFT (2 children).
 *      N-ary version does the same with a reverse loop over n children.
 *    - Time O(N), Space O(H) for narrow trees.
 *      Worst case O(N) for a wide tree (root with N-1 children are all
 *      pushed at once).
 *
 *    Dry Run, Example 1 (stack: bottom -> top, top at the right):
 *
 *      Start        : stack = [1]
 *      pop 1, VISIT : push children reverse: 4, 2, 3
 *                                            stack = [4, 2, 3]
 *      pop 3, VISIT : push children reverse: 6, 5
 *                                            stack = [4, 2, 6, 5]
 *      pop 5, VISIT : no children            stack = [4, 2, 6]
 *      pop 6, VISIT : no children            stack = [4, 2]
 *      pop 2, VISIT : no children            stack = [4]
 *      pop 4, VISIT : no children            stack = []
 *
 *      Output: 1, 3, 5, 6, 2, 4   (same as recursion)
 *
 *    Dry Run, Example 2:
 *
 *      Start         : stack = [1]
 *      pop 1,  VISIT : push 5, 4, 3, 2         stack = [5, 4, 3, 2]
 *      pop 2,  VISIT : no children             stack = [5, 4, 3]
 *      pop 3,  VISIT : push 7, 6               stack = [5, 4, 7, 6]
 *      pop 6,  VISIT : no children             stack = [5, 4, 7]
 *      pop 7,  VISIT : push 11                 stack = [5, 4, 11]
 *      pop 11, VISIT : no children             stack = [5, 4]
 *      pop 4,  VISIT : push 8                  stack = [5, 8]
 *      pop 8,  VISIT : no children             stack = [5]
 *      pop 5,  VISIT : push 10, 9              stack = [10, 9]
 *      pop 9,  VISIT : no children             stack = [10]
 *      pop 10, VISIT : no children             stack = []
 *
 *      Output: 1, 2, 3, 6, 7, 11, 4, 8, 5, 9, 10
 *
 *    Dry Run, Example 3 (wide tree, root 1 with children 2,3,4,5):
 *
 *      Start         : stack = [1]
 *      pop 1, VISIT  : push 5, 4, 3, 2         stack = [5, 4, 3, 2]
 *      pop 2, VISIT  : stack = [5, 4, 3]
 *      pop 3, VISIT  : stack = [5, 4]
 *      pop 4, VISIT  : stack = [5]
 *      pop 5, VISIT  : stack = []
 *
 *      Output: 1, 2, 3, 4, 5   (stack grew to size 4 = all children)
 *
 *      Single [7] : push 7, pop, VISIT 7, no children       -> [7]
 *
 * ----------------------------------------------------------------------------
 *  Compare the 2 approaches:
 *
 *      Approach     | Time | Space      | Difficulty
 *      -------------+------+------------+-----------
 *      Recursive    | O(N) | O(H)       | Easy
 *      Iterative    | O(N) | O(H)..O(N) | Medium
 *
 *    Approach 3 (Morris) does NOT exist for N-ary trees. Morris needs
 *    exactly one "left" and one "right" pointer to build threads.
 *
 * ----------------------------------------------------------------------------
 *  Compare with other traversals (Example 1 tree):
 *
 *      Preorder   (Root, children L to R)  : 1 3 5 6 2 4     <== this one
 *      Postorder  (children L to R, Root)  : 5 6 3 2 4 1
 *      Level Order (BFS)                   : 1 3 2 4 5 6
 *                                            (grouped: [[1],[3,2,4],[5,6]])
 *
 *    Only the position of "visit" changes in DFS:
 *      before children = preorder, after children = postorder.
 *
 * ----------------------------------------------------------------------------
 *  When to use N-ary Preorder?
 *    - Copy / clone an N-ary tree (create parent first).
 *    - Serialize an N-ary tree (save the root first).
 *    - Print a folder structure (folder name, then its contents).
 *    - File system / org chart / HTML DOM walk (parent before children).
 *    - Any task where parent must be processed BEFORE its children.
 *
 * ----------------------------------------------------------------------------
 *  Complexity:
 *    Time  : O(N) - every node visited exactly once.
 *    Space : O(H) - recursion stack or explicit stack.
 *            Balanced tree : H = log N
 *            Skewed tree   : H = N   (worst case)
 *            Iterative, very wide tree : up to O(N) (all children pushed)
 *
 * ----------------------------------------------------------------------------
 *  Common Mistakes:
 *    1. Iterative: pushing children in NORMAL order -> output visits the
 *       LAST child first (right to left, wrong).
 *    2. Forgetting the base case (node == nullptr) -> crash.
 *    3. Using node->left / node->right. N-ary has only node->children.
 *    4. Iterative: using unsigned size with "i >= 0" loop. If n is
 *       size_t, "i--" below 0 wraps to a huge number. Your code uses
 *       const int n, which is correct.
 *    5. Iterative: pushing nullptr then reading ->val. (Your null check
 *       in the loop prevents this.)
 *    6. Mixing preorder with level order. Preorder goes DEEP first.
 *
 * ----------------------------------------------------------------------------
 *  Practice Problems (in order):
 *    589. N-ary Tree Preorder Traversal           (Easy)   <- start here
 *    590. N-ary Tree Postorder Traversal          (Easy)
 *
 *    429. N-ary Tree Level Order Traversal        (Medium)
 *    559. Maximum Depth of N-ary Tree             (Easy)
 *    558. Logical OR of Two Binary Grids (skip) / 428. Serialize and
 *         Deserialize N-ary Tree                  (Hard, Premium)
 *    1522. Diameter of N-Ary Tree                 (Medium, Premium)
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
using namespace std;

// N-ary tree node definition
struct Node{
	int val; // Value of the node
    vector<Node*> children; // Vector to store pointers to child nodes

    // Constructor initializes the node with a value and an empty children vector
    explicit Node(const int v) : val(v), children() {}
};

// Approach 1: Use Recursion to perform Preorder Traversal of an N-ary tree
static vector<int> preorder(const Node* root){
	vector<int> ans;

	if (root == nullptr)
		return ans;

	auto dfs = [&](auto&& self, const Node* node) -> void{
		// Base Case
		if (node == nullptr)
			return;

		// Add current value to answer
		ans.emplace_back(node->val);

		// Recursively visit all children of the current node
		for (const Node* child : node->children)
			self(self, child);
	};

	dfs(dfs, root);
	return ans;
}

// Approach 2: Use Iteration to perform Preorder Traversal of an N-ary tree
static vector<int> preorderIterative(const Node* root){
	vector<int> ans;

	if (root == nullptr)
		return ans;

	// Use a stack to simulate the recursive call stack
	stack<const Node*> st;
	st.push(root);

	while (!st.empty()){
		const Node* node = st.top();
		st.pop();

		// Add current value to answer
		ans.emplace_back(node->val);

		// Push children onto the stack in reverse order to maintain preorder traversal
		const int n = node->children.size();
        for (int i = n - 1; i >= 0; i--){
	        if (node->children[i] != nullptr)
                st.push(node->children[i]);
        }
	}

	return ans;
}

// Function to build an N-ary tree from a vector of parent indices (for testing purposes)
static Node* buildTree(const vector<int>& values){
	size_t n = values.size();

	// Inadequate input check: if the tree is empty or the root is null
	if (n == 0 || values[0] == -1)
		return nullptr;

	Node* root = new Node(values[0]);
	queue<Node*> q;
	q.push(root);

	size_t idx = 2; // skip root and first separator
	while (!q.empty() && idx < n){
		Node* current = q.front();
        q.pop();

        // Add children for the current node
        while (idx < n && values[idx] != -1){
            Node* child = new Node(values[idx]);
            current->children.push_back(child);
            q.push(child);
            idx++;
        }

        // Move to the next index for the next node
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

	// Build the N-ary tree from the level-order values and -1 separators
	Node* root = buildTree(values);

	// Approach 1: Preorder Traversal using Recursion
	vector<int> recursiveResult = preorder(root);
	cout << "Preorder Traversal (Recursive): ";
	printTraversal(recursiveResult);

	// Approach 2: Preorder Traversal using Iteration
	vector<int> iterativeResult = preorderIterative(root);
	cout << "Preorder Traversal (Iterative): ";
	printTraversal(iterativeResult);

}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}