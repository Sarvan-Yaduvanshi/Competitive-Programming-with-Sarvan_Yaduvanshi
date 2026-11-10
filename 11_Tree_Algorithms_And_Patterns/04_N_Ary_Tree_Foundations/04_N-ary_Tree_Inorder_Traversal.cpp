/*
Author: Sarvan Yaduvanshi
Created : 2026-11-11 02:32:21
*/

/*
 * ============================================================================
 *  TREE TRAVERSAL PATTERN 7: N-ARY TREE INORDER TRAVERSAL
 *                            (First Child -> Root -> Remaining Children)
 *  Time: O(N)  |  Space: O(H)   (H = height of tree)
 * ============================================================================
 *
 *  What is Inorder for an N-ary tree?
 *
 *    Binary inorder is clear: Left, Root, Right. Root sits IN BETWEEN its
 *    2 children. An N-ary node has many children, so "middle" is not
 *    defined. There is NO official rule and NO LeetCode problem for it.
 *
 *    Common convention (the one your code uses):
 *
 *      Rule:   1. Traverse the FIRST child (child[0]) subtree
 *              2. Visit ROOT (Node)
 *              3. Traverse the REMAINING children, left to right
 *                 (child[1], child[2], ... child[n-1])
 *
 *    Name trick : IN = root sits AFTER the first child, BEFORE the rest.
 *    Easy line  : "First child is the LEFT side. All other children are
 *                  the RIGHT side."
 *
 *    Same rule is applied to EVERY subtree, not only the main root.
 *
 *    Check with binary tree:
 *      Node with exactly 2 children (c0, c1) -> c0, Root, c1.
 *      That is exactly binary inorder (Left, Root, Right).
 *      Node with 1 child                     -> c0, Root.
 *      Leaf                                  -> Root.
 *
 *    Binary vs N-ary:
 *      Binary inorder : Left -> Root -> Right
 *      N-ary inorder  : child0 -> Root -> child1 -> ... -> childK
 *
 *    WARNING: other books may choose a different split (example: half of
 *    the children before root). Always read the problem statement. Your
 *    rule here: 1 child before root, the rest after.
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
 *    Inorder Output : [5, 3, 6, 1, 2, 4]
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
 *    Inorder Output : [2, 1, 6, 3, 11, 7, 8, 4, 9, 5, 10]
 *
 * ----------------------------------------------------------------------------
 *  EXAMPLE 3: Edge Cases
 *
 *      Empty tree  (root = null)   ->  []       (early return in both)
 *      Single node [7]             ->  [7]      (children list is empty)
 *
 *      Skewed chain  1 -> 2 -> 3   ->  [3, 2, 1]
 *      (each node has only a first child, so root comes after it)
 *
 *      Wide tree (root 1 with leaf children 2,3,4,5):
 *                    1
 *                 / | | \
 *                2  3 4  5          ->  [2, 1, 3, 4, 5]
 *      (only child 2 is before the root, 3 4 5 come after)
 *
 *      Binary-like tree (root 1 with children 2, 3):
 *                    1
 *                   / \
 *                  2   3            ->  [2, 1, 3]   (same as binary inorder)
 *
 * ============================================================================
 *  APPROACH 1: RECURSIVE (lambda with self, your Approach 1)
 * ============================================================================
 *
 *    - Edge case : root == nullptr -> return empty vector.
 *    - Lambda takes (self, node). "self" lets a lambda call itself.
 *    - Base case : node == nullptr -> return.
 *    - n = node->children.size() (number of children).
 *    - Order of the 3 steps is the whole traversal:
 *          Step 1: if (n > 0) self(children[0])       <- first child
 *          Step 2: ans.push_back(node->val)           <- VISIT in between
 *          Step 3: for i = 1 .. n-1 self(children[i]) <- remaining children
 *    - The "n > 0" check is a must. children[0] on an empty vector is
 *      undefined behavior.
 *    - Step 3 loop starts at i = 1, NOT 0, because child 0 is already done.
 *    - "ans" is captured by reference [&], so one shared vector is used.
 *    - Time O(N), Space O(H) call stack.
 *
 *    Dry Run, Example 1 (indent = depth, VISIT after the FIRST child only):
 *
 *      dfs(1)
 *        dfs(3)                     (first child of 1)
 *          dfs(5) -> VISIT 5        (first child of 3, leaf)
 *          VISIT 3
 *          dfs(6) -> VISIT 6        (remaining child of 3, leaf)
 *        VISIT 1
 *        dfs(2) -> VISIT 2          (remaining child of 1, leaf)
 *        dfs(4) -> VISIT 4          (remaining child of 1, leaf)
 *
 *      Result: 5, 3, 6, 1, 2, 4
 *
 *    Dry Run, Example 2:
 *
 *      dfs(1)
 *        dfs(2) -> VISIT 2          (first child of 1, leaf)
 *        VISIT 1
 *        dfs(3)
 *          dfs(6) -> VISIT 6        (first child of 3, leaf)
 *          VISIT 3
 *          dfs(7)
 *            dfs(11) -> VISIT 11    (first child of 7, leaf)
 *            VISIT 7
 *        dfs(4)
 *          dfs(8) -> VISIT 8        (first child of 4, leaf)
 *          VISIT 4
 *        dfs(5)
 *          dfs(9) -> VISIT 9        (first child of 5, leaf)
 *          VISIT 5
 *          dfs(10) -> VISIT 10      (remaining child of 5, leaf)
 *
 *      Result: 2, 1, 6, 3, 11, 7, 8, 4, 9, 5, 10
 *
 *    Dry Run, Example 3 (edge):
 *      Single [7]    : n = 0, skip step 1, VISIT 7, loop empty   -> [7]
 *      Chain 1->2->3 : dfs(1) -> dfs(2) -> dfs(3)
 *                      VISIT 3, VISIT 2, VISIT 1                 -> [3,2,1]
 *      Wide tree     : dfs(2) VISIT 2, VISIT 1, then 3, 4, 5    -> [2,1,3,4,5]
 *      Empty         : early return                              -> []
 *
 * ============================================================================
 *  APPROACH 2: ITERATIVE WITH STACK OF (node, childIdx) (your Approach 2)
 * ============================================================================
 *
 *    Idea: the stack holds pairs (node, childIdx). childIdx is a STATE
 *    counter for that node. It copies what recursion does by hand.
 *
 *    State table for one node (n = number of children):
 *
 *      childIdx        | What to do                         | Then
 *      ----------------+------------------------------------+-------------
 *      0               | go into first child (if n > 0)     | childIdx = 1
 *      1               | VISIT node                         | childIdx = 2
 *      2 .. n          | go into child[childIdx - 1]        | childIdx++
 *      > n  (n + 1)    | all children done                  | POP node
 *
 *    - Step "0" = Step 1 of recursion (first child).
 *    - Step "1" = Step 2 of recursion (visit).
 *    - Step "2..n" = Step 3 of recursion (remaining children).
 *    - Always do childIdx++ BEFORE pushing a child. Then the next time this
 *      node is on top, it moves forward. If you forget, the same child is
 *      pushed forever (infinite loop).
 *    - Why child[childIdx - 1]? State 2 must open child[1]. State 3 opens
 *      child[2]. So the index is childIdx - 1.
 *    - Leaf (n = 0): state 0 -> 1 (no push), state 1 -> VISIT, state 2 -> pop
 *      (because 2 <= 0 is false).
 *    - auto& [node, childIdx] = st.top() is a REFERENCE into the stack.
 *      It stays valid after st.push/emplace because std::stack uses
 *      std::deque, and deque push_back does not break references to
 *      existing elements. (With a vector as container it WOULD break.)
 *    - Time O(N), Space O(H) (stack holds one root-to-node path only).
 *
 *    Dry Run, Example 1 (stack pairs, bottom -> top, top at the right):
 *
 *      stack = [(1,0)]
 *      (1,0) idx 0 : idx -> 1, push (3,0)      [(1,1),(3,0)]
 *      (3,0) idx 0 : idx -> 1, push (5,0)      [(1,1),(3,1),(5,0)]
 *      (5,0) idx 0 : idx -> 1, n = 0 no push   [(1,1),(3,1),(5,1)]
 *      (5,1) idx 1 : VISIT 5, idx -> 2
 *      (5,2) idx 2 : 2 <= 0 false, POP         [(1,1),(3,1)]
 *      (3,1) idx 1 : VISIT 3, idx -> 2
 *      (3,2) idx 2 : child[1] = 6, idx -> 3,
 *                    push (6,0)                [(1,1),(3,3),(6,0)]
 *      (6,0) idx 0 : idx -> 1
 *      (6,1) idx 1 : VISIT 6, idx -> 2
 *      (6,2)       : POP                       [(1,1),(3,3)]
 *      (3,3) idx 3 : 3 <= 2 false, POP         [(1,1)]
 *      (1,1) idx 1 : VISIT 1, idx -> 2
 *      (1,2) idx 2 : child[1] = 2, idx -> 3,
 *                    push (2,0)                [(1,3),(2,0)]
 *      (2,0),(2,1) : VISIT 2, then POP         [(1,3)]
 *      (1,3) idx 3 : child[2] = 4, idx -> 4,
 *                    push (4,0)                [(1,4),(4,0)]
 *      (4,0),(4,1) : VISIT 4, then POP         [(1,4)]
 *      (1,4) idx 4 : 4 <= 3 false, POP         []
 *      End : stack empty
 *
 *      Output: 5, 3, 6, 1, 2, 4   (same as recursion)
 *
 *    Dry Run, Example 2 (only the important events):
 *
 *      (1,0) -> idx 1, push 2
 *      (2,0) -> idx 1 ; (2,1) VISIT 2 ; (2,2) POP
 *      (1,1) VISIT 1, idx 2
 *      (1,2) -> child[1] = 3, idx 3, push (3,0)
 *      (3,0) -> idx 1, push 6 ; VISIT 6 ; POP 6
 *      (3,1) VISIT 3, idx 2
 *      (3,2) -> child[1] = 7, idx 3, push (7,0)
 *      (7,0) -> idx 1, push 11 ; VISIT 11 ; POP 11
 *      (7,1) VISIT 7 ; (7,2) POP          (n = 1, 2 <= 1 false)
 *      (3,3) POP                          (n = 2, 3 <= 2 false)
 *      (1,3) -> child[2] = 4, idx 4, push (4,0)
 *      (4,0) -> idx 1, push 8 ; VISIT 8 ; POP 8
 *      (4,1) VISIT 4 ; (4,2) POP
 *      (1,4) -> child[3] = 5, idx 5, push (5,0)
 *      (5,0) -> idx 1, push 9 ; VISIT 9 ; POP 9
 *      (5,1) VISIT 5, idx 2
 *      (5,2) -> child[1] = 10, idx 3, push (10,0)
 *      (10,..) VISIT 10 ; POP 10
 *      (5,3) POP                          (n = 2, 3 <= 2 false)
 *      (1,5) POP                          (n = 4, 5 <= 4 false)
 *      End : stack empty
 *
 *      Output: 2, 1, 6, 3, 11, 7, 8, 4, 9, 5, 10
 *
 *    Dry Run, Example 3 (edge):
 *      Single [7]    : (7,0)->1, (7,1) VISIT 7, (7,2) POP          -> [7]
 *      Chain 1->2->3 : push (1,0),(2,0),(3,0) one by one.
 *                      VISIT 3, POP. VISIT 2, POP. VISIT 1, POP.   -> [3,2,1]
 *                      Stack grew to size 3 = N (worst case).
 *      Wide tree     : (1,0) push 2. VISIT 2. VISIT 1. Then push 3,
 *                      4, 5 one at a time (never together).      -> [2,1,3,4,5]
 *                      Stack never holds more than 2 pairs.
 *
 * ----------------------------------------------------------------------------
 *  Compare the 2 approaches:
 *
 *      Approach     | Time | Space | Modifies tree? | Difficulty
 *      -------------+------+-------+----------------+-----------
 *      Recursive    | O(N) | O(H)  | No             | Easy
 *      Iterative    | O(N) | O(H)  | No             | Medium
 *
 *    Morris does NOT exist for N-ary trees (needs exactly left and right).
 *
 * ----------------------------------------------------------------------------
 *  Compare with other N-ary traversals (Example 1 tree):
 *
 *      Preorder   (Root, children L to R)         : 1 3 5 6 2 4
 *      Inorder    (child0, Root, other children)  : 5 3 6 1 2 4   <== this one
 *      Postorder  (children L to R, Root)         : 5 6 3 2 4 1
 *      Level Order (BFS)                          : 1 3 2 4 5 6
 *
 *    Only the position of "visit" changes in DFS:
 *      before all children = preorder
 *      after the FIRST child = inorder (this convention)
 *      after all children = postorder
 *
 * ----------------------------------------------------------------------------
 *  When to use N-ary Inorder?
 *    - Mostly for learning. It connects binary inorder to N-ary trees.
 *    - Real problems use Preorder, Postorder, or Level Order.
 *    - Good practice for the "state counter on the stack" trick. The same
 *      trick gives iterative postorder for N-ary trees.
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
 *    1. Recursive: calling children[0] without "n > 0" -> crash on a leaf.
 *    2. Recursive: step 3 loop starting at i = 0 -> child 0 visited twice.
 *    3. Iterative: forgetting childIdx++ before the push -> infinite loop.
 *    4. Iterative: using children[childIdx] instead of
 *       children[childIdx - 1] in state 2..n -> skips a child or reads out
 *       of range.
 *    5. Iterative: using a vector as the container under the reference
 *       binding -> reference breaks after a push. Keep default deque.
 *    6. Using node->left / node->right. N-ary has only node->children.
 *    7. Mixing the 3 states: 0 = first child, 1 = visit, 2..n = rest.
 *    8. Copy paste comment: your code comments say "Preorder Traversal".
 *       Change them to "Inorder Traversal".
 *
 * ----------------------------------------------------------------------------
 *  Practice Problems (N-ary tree only):
 *    589. N-ary Tree Preorder Traversal           (Easy)
 *    590. N-ary Tree Postorder Traversal          (Easy)
 *    429. N-ary Tree Level Order Traversal        (Medium)
 *    559. Maximum Depth of N-ary Tree             (Easy)
 *    690. Employee Importance                     (Medium, N-ary style)
 *   1376. Time Needed to Inform All Employees     (Medium, N-ary style)
 *   1490. Clone N-ary Tree                        (Medium, Premium)
 *   1506. Find Root of N-Ary Tree                 (Medium, Premium)
 *    431. Encode N-ary Tree to Binary Tree        (Hard, Premium)
 *    428. Serialize and Deserialize N-ary Tree    (Hard, Premium)
 *   1522. Diameter of N-Ary Tree                  (Medium, Premium)
 *
 *    No LeetCode problem asks for N-ary inorder. This one is for concept.
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
static vector<int> Inorder(Node* root){
	vector<int> ans;

	if (root == nullptr)
		return ans;

	auto dfs = [&](auto&& self, Node* node) -> void{
		// Base Case
		if (node == nullptr)
			return;

		// get current node's number of children
		int n = node->children.size();

		// Step 1: Traverse the first child (if it exists)
		if (n > 0)
			self(self, node->children[0]);

		// Step 2: Visit the current node
		ans.push_back(node->val);

		// Step 3: Traverse the remaining children (if they exist)
        for (int i = 1; i < n; ++i){
            self(self, node->children[i]);
        }
	};

	dfs(dfs, root);
	return ans;
}

// Approach 2: Use Iteration to perform Preorder Traversal of an N-ary tree
static vector<int> InorderIterative(Node* root){
	vector<int> ans;

	if (root == nullptr)
		return ans;

	// Use stack of pairs to store nodes and their child indices
	stack<pair<Node*, int>> st;
	st.emplace(root, 0);

	while (!st.empty()){
		// Get the current node and its child index from the top of the stack
		auto& [node, childIdx] = st.top();

		// get current node's number of children
		int n = node->children.size();

		// If the child index is 0, visit the current node
		if (childIdx == 0){
			childIdx++; // Increment child index for the next iteration
			if (n > 0)
				st.emplace(node->children[0], 0); // Push the first child onto the stack
		}
		// Visit current node
		else if (childIdx == 1) {
			ans.push_back(node->val); // store the value of the node in the answer vector
			childIdx++;
		}

		// Remaining children
		else if (childIdx <= n) {
			Node* child = node->children[childIdx - 1];
			childIdx++;

			st.push({child, 0});
		}

		// All children processed
		else {
			st.pop();
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
	vector<int> recursiveResult = Inorder(root);
	cout << "Preorder Traversal (Recursive): ";
	printTraversal(recursiveResult);

	// Approach 2: Preorder Traversal using Iteration
	vector<int> iterativeResult = InorderIterative(root);
	cout << "Preorder Traversal (Iterative): ";
	printTraversal(iterativeResult);

}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}