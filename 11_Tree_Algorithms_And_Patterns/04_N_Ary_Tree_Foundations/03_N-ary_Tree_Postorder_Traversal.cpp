/*
Author: Sarvan Yaduvanshi
Created : 2026-11-11 02:32:21
*/

/*
 * ============================================================================
 *  TREE TRAVERSAL PATTERN 6: N-ARY TREE POSTORDER TRAVERSAL (Children -> Root)
 *  Time: O(N)  |  Space: O(H)   (H = height of tree)
 * ============================================================================
 *
 *  What is Postorder (N-ary)?
 *
 *    Rule:   1. Traverse each CHILD subtree, from LEFT to RIGHT
 *               (child[0] first, then child[1], then child[2] ...)
 *            2. Visit ROOT (Node) LAST
 *
 *    Name trick : POST = parent comes AFTER all its children.
 *    Easy line  : "Print the node when ALL its children are completely done."
 *
 *    Same rule is applied to EVERY subtree, not only the main root.
 *
 *    Binary vs N-ary:
 *      Binary postorder : Left -> Right -> Root       (2 fixed children)
 *      N-ary postorder  : child0 -> child1 -> ... -> childK -> Root
 *                         (a LOOP over children replaces left/right)
 *
 *  Golden Facts (VERY IMPORTANT):
 *    1. The LAST value is always the ROOT.
 *    2. Children are done BEFORE the parent. When you reach a node, you
 *       already know the answer of every child subtree. This is the base of
 *       Tree DP (height, size, sum, diameter).
 *    3. Postorder = REVERSE of (Root -> children from RIGHT to LEFT).
 *       Your Approach 2 uses this trick.
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
 *    Postorder Output : [5, 6, 3, 2, 4, 1]
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
 *    Postorder Output : [2, 6, 11, 7, 3, 8, 4, 9, 10, 5, 1]
 *
 * ----------------------------------------------------------------------------
 *  EXAMPLE 3: Edge Cases
 *
 *      Empty tree  (root = null)   ->  []
 *      Single node [7]             ->  [7]      (children list is empty)
 *
 *      Skewed chain  1 -> 2 -> 3   ->  [3, 2, 1]
 *      (height H = N, worst case stack)
 *
 *      Wide tree (root 1 with leaf children 2,3,4,5):
 *                    1
 *                 / | | \
 *                2  3 4  5          ->  [2, 3, 4, 5, 1]
 *
 * ============================================================================
 *  APPROACH 1: RECURSIVE
 * ============================================================================
 *
 *    - Edge case : root == nullptr -> return empty vector.
 *    - Lambda (self, node), base case node == nullptr -> return.
 *    - Order of the lines is the whole traversal:
 *          for (child : node->children)     <- every child FIRST,
 *              self(self, child)               left to right
 *          ans.emplace_back(node->val)      <- VISIT LAST
 *    - Compare with preorder: only the VISIT line moves below the loop.
 *    - Time O(N), Space O(H) call stack.
 *
 *    Dry Run, Example 1 (VISIT happens AFTER the children loop ends):
 *
 *      dfs(1)
 *        dfs(3)
 *          dfs(5) -> VISIT 5        (no children)
 *          dfs(6) -> VISIT 6        (no children)
 *          VISIT 3
 *        dfs(2) -> VISIT 2          (no children)
 *        dfs(4) -> VISIT 4          (no children)
 *        VISIT 1
 *
 *      Result: 5, 6, 3, 2, 4, 1
 *
 *    Dry Run, Example 2:
 *
 *      dfs(1)
 *        dfs(2) -> VISIT 2          (leaf)
 *        dfs(3)
 *          dfs(6) -> VISIT 6        (leaf)
 *          dfs(7)
 *            dfs(11) -> VISIT 11    (leaf)
 *            VISIT 7
 *          VISIT 3
 *        dfs(4)
 *          dfs(8) -> VISIT 8        (leaf)
 *          VISIT 4
 *        dfs(5)
 *          dfs(9)  -> VISIT 9       (leaf)
 *          dfs(10) -> VISIT 10      (leaf)
 *          VISIT 5
 *        VISIT 1
 *
 *      Result: 2, 6, 11, 7, 3, 8, 4, 9, 10, 5, 1
 *
 *    Dry Run, Example 3 (edge):
 *      Single [7] : dfs(7), loop empty, VISIT 7        -> [7]
 *      Chain 1->2->3 : dfs(1) -> dfs(2) -> dfs(3)
 *                      VISIT 3, VISIT 2, VISIT 1       -> [3, 2, 1]
 *      Empty      : early return                       -> []
 *
 * ============================================================================
 *  APPROACH 2: ITERATIVE WITH ONE STACK + REVERSE
 * ============================================================================
 *
 *    Idea (2 steps):
 *      Step 1: Do a modified preorder: Root -> children from RIGHT to LEFT.
 *              Store the order in ans.
 *      Step 2: reverse(ans). Reverse of (Root, right..left)
 *              = (left..right, Root) = POSTORDER.
 *
 *    Loop while stack not empty:
 *      - node = st.top(); st.pop();
 *      - ans.emplace_back(node->val);
 *      - push children in NORMAL order (child[0] first, last child last),
 *        skip null children.
 *        Stack is LIFO, so the LAST child is popped first. That gives
 *        Root, right ... left.
 *    After the loop: reverse(ans.begin(), ans.end()).
 *
 *    - Compare with preorder iterative: there children are pushed in
 *      REVERSE. Here they are pushed in NORMAL order, because the order is
 *      flipped at the end.
 *    - Time O(N), Space O(N) (ans holds all, stack up to O(N) for wide).
 *
 *    Dry Run, Example 1 (stack: bottom -> top, top at the right):
 *
 *      Start         : stack = [1]            ans = []
 *      pop 1         : push 3, 2, 4           stack = [3, 2, 4]
 *                                             ans = [1]
 *      pop 4         : no children            stack = [3, 2]
 *                                             ans = [1, 4]
 *      pop 2         : no children            stack = [3]
 *                                             ans = [1, 4, 2]
 *      pop 3         : push 5, 6              stack = [5, 6]
 *                                             ans = [1, 4, 2, 3]
 *      pop 6         : no children            stack = [5]
 *                                             ans = [1, 4, 2, 3, 6]
 *      pop 5         : no children            stack = []
 *                                             ans = [1, 4, 2, 3, 6, 5]
 *
 *      ans = Root, right..left = 1 4 2 3 6 5
 *      reverse(ans) -> 5, 6, 3, 2, 4, 1
 *
 *      Output: 5, 6, 3, 2, 4, 1   (same as recursion)
 *
 *    Dry Run, Example 2:
 *
 *      Start    : stack = [1]
 *      pop 1    : push 2, 3, 4, 5             stack = [2, 3, 4, 5]
 *                 ans = [1]
 *      pop 5    : push 9, 10                  stack = [2, 3, 4, 9, 10]
 *                 ans = [1, 5]
 *      pop 10   : no children                 stack = [2, 3, 4, 9]
 *                 ans = [1, 5, 10]
 *      pop 9    : no children                 stack = [2, 3, 4]
 *                 ans = [1, 5, 10, 9]
 *      pop 4    : push 8                      stack = [2, 3, 8]
 *                 ans = [1, 5, 10, 9, 4]
 *      pop 8    : no children                 stack = [2, 3]
 *                 ans = [1, 5, 10, 9, 4, 8]
 *      pop 3    : push 6, 7                   stack = [2, 6, 7]
 *                 ans = [1, 5, 10, 9, 4, 8, 3]
 *      pop 7    : push 11                     stack = [2, 6, 11]
 *                 ans = [1, 5, 10, 9, 4, 8, 3, 7]
 *      pop 11   : no children                 stack = [2, 6]
 *                 ans = [1, 5, 10, 9, 4, 8, 3, 7, 11]
 *      pop 6    : no children                 stack = [2]
 *                 ans = [1, 5, 10, 9, 4, 8, 3, 7, 11, 6]
 *      pop 2    : no children                 stack = []
 *                 ans = [1, 5, 10, 9, 4, 8, 3, 7, 11, 6, 2]
 *
 *      reverse(ans) -> 2, 6, 11, 7, 3, 8, 4, 9, 10, 5, 1
 *
 *      Output: 2, 6, 11, 7, 3, 8, 4, 9, 10, 5, 1
 *
 *    Dry Run, Example 3 (wide tree, root 1 with children 2,3,4,5):
 *
 *      pop 1 : push 2,3,4,5      ans = [1]
 *      pop 5, pop 4, pop 3, pop 2   ans = [1, 5, 4, 3, 2]
 *      reverse(ans) -> 2, 3, 4, 5, 1
 *
 *      Single [7] : pop 7, ans = [7], reverse -> [7]
 *
 * ============================================================================
 *  APPROACH 3: ITERATIVE WITH ONE STACK + CHILD INDEX (true postorder, O(H))
 * ============================================================================
 *
 *    Idea: the stack holds pairs (node, idx). idx = index of the NEXT child
 *    of that node that is still not visited. No reverse, no extra vector
 *    beyond ans. This copies what recursion does by hand.
 *
 *    Loop while stack not empty:
 *      - (node, idx) = top of stack.
 *      - If idx < node->children.size():
 *            child = node->children[idx];
 *            top.idx++                 (remember the next child to do)
 *            push (child, 0)           (go DOWN into this child)
 *      - Else (all children done):
 *            VISIT node (ans.emplace_back(node->val));
 *            pop.
 *
 *    - Visit happens only when idx reaches the end = all children done.
 *      That is the POSTORDER rule.
 *    - Time O(N), Space O(H) (stack holds one path, not all children).
 *
 *    Dry Run, Example 1 (stack pairs: bottom -> top):
 *
 *      stack = [(1,0)]
 *      top (1,0): child 3          -> stack = [(1,1), (3,0)]
 *      top (3,0): child 5          -> stack = [(1,1), (3,1), (5,0)]
 *      top (5,0): no children      -> VISIT 5, pop
 *      top (3,1): child 6          -> stack = [(1,1), (3,2), (6,0)]
 *      top (6,0): no children      -> VISIT 6, pop
 *      top (3,2): all done         -> VISIT 3, pop
 *      top (1,1): child 2          -> stack = [(1,2), (2,0)]
 *      top (2,0): no children      -> VISIT 2, pop
 *      top (1,2): child 4          -> stack = [(1,3), (4,0)]
 *      top (4,0): no children      -> VISIT 4, pop
 *      top (1,3): all done         -> VISIT 1, pop
 *      End: stack empty
 *
 *      Output: 5, 6, 3, 2, 4, 1
 *
 *    Dry Run, Example 2:
 *
 *      (1,0) -> child 2:   (1,1),(2,0)        VISIT 2
 *      (1,1) -> child 3:   (1,2),(3,0)
 *      (3,0) -> child 6:   (3,1),(6,0)        VISIT 6
 *      (3,1) -> child 7:   (3,2),(7,0)
 *      (7,0) -> child 11:  (7,1),(11,0)       VISIT 11
 *      (7,1) all done                         VISIT 7
 *      (3,2) all done                         VISIT 3
 *      (1,2) -> child 4:   (1,3),(4,0)
 *      (4,0) -> child 8:   (4,1),(8,0)        VISIT 8
 *      (4,1) all done                         VISIT 4
 *      (1,3) -> child 5:   (1,4),(5,0)
 *      (5,0) -> child 9:   (5,1),(9,0)        VISIT 9
 *      (5,1) -> child 10:  (5,2),(10,0)       VISIT 10
 *      (5,2) all done                         VISIT 5
 *      (1,4) all done                         VISIT 1
 *
 *      Output: 2, 6, 11, 7, 3, 8, 4, 9, 10, 5, 1
 *
 *    Dry Run, Example 3:
 *      Chain 1->2->3 : push (1,0),(2,0),(3,0). VISIT 3, VISIT 2, VISIT 1.
 *                      Stack never holds more than 3 pairs.
 *      Wide tree     : stack holds at most 2 pairs (root + current child).
 *                      Output 2, 3, 4, 5, 1.
 *
 * ----------------------------------------------------------------------------
 *  Compare the 3 approaches:
 *
 *      Approach          | Time | Space  | Difficulty
 *      ------------------+------+--------+-----------
 *      Recursive         | O(N) | O(H)   | Easy
 *      Stack + Reverse   | O(N) | O(N)   | Easy-Medium
 *      Stack + Index     | O(N) | O(H)   | Medium
 *
 *    Morris does NOT exist for N-ary trees (needs exactly left and right).
 *
 * ----------------------------------------------------------------------------
 *  Compare with other traversals (Example 1 tree):
 *
 *      Preorder   (Root, children L to R)  : 1 3 5 6 2 4
 *      Postorder  (children L to R, Root)  : 5 6 3 2 4 1     <== this one
 *      Level Order (BFS)                   : 1 3 2 4 5 6
 *                                            (grouped: [[1],[3,2,4],[5,6]])
 *
 * ----------------------------------------------------------------------------
 *  When to use N-ary Postorder?
 *    - Delete / free a whole tree (children first, then parent).
 *    - Height, size, sum of a subtree (need children's answer first).
 *    - Folder size (folder = sum of children + itself).
 *    - Org chart: time or cost to reach the whole team under a manager.
 *    - Evaluate an expression tree, build step by step upwards.
 *    - Tree DP: diameter, max path, count of something per subtree.
 *
 * ----------------------------------------------------------------------------
 *  Complexity:
 *    Time  : O(N) - every node visited exactly once.
 *    Space : Recursive O(H). Stack + Reverse O(N). Stack + Index O(H).
 *
 * ----------------------------------------------------------------------------
 *  Common Mistakes:
 *    1. Stack + Reverse: pushing children in REVERSE (that is the preorder
 *       habit). Push in NORMAL order here.
 *    2. Stack + Reverse: forgetting reverse() at the end -> you print
 *       Root, right..left (wrong).
 *    3. Stack + Index: forgetting idx++ before pushing the child -> same
 *       child pushed forever, infinite loop.
 *    4. Recursive: putting VISIT before the loop (that is preorder).
 *    5. Using node->left / node->right. N-ary has only node->children.
 *    6. Forgetting the base case (node == nullptr) -> crash.
 *    7. Mixing postorder with level order. Postorder goes DEEP first.
 *
 * ============================================================================
 *  IMPORTANT INTERVIEW PROBLEMS (Postorder / "children first" pattern)
 * ============================================================================
 *
 *  LeetCode (start here, in order):
 *    590. N-ary Tree Postorder Traversal             (Easy)   <- start here
 *    690. Employee Importance                        (Medium, N-ary style)
 *   1376. Time Needed to Inform All Employees        (Medium, N-ary style)
 *    337. House Robber III                           (Medium, Tree DP)
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
static vector<int> postorder(const Node* root){
	vector<int> ans;

	if (root == nullptr)
		return ans;

	auto dfs = [&](auto&& self, const Node* node) -> void{
		// Base Case
		if (node == nullptr)
			return;

		// Recursively visit all children of the current node
		for (const Node* child : node->children)
			self(self, child);

		// Add current value to answer
		ans.emplace_back(node->val);
	};

	dfs(dfs, root);
	return ans;
}

// Approach 2: Use Iteration to perform Preorder Traversal of an N-ary tree
static vector<int> postorderIterative(Node* root){
	vector<int> ans;

	// empty tree check
	if (root == nullptr)
		return ans;

	// Use two stacks to simulate the recursive call stack and reverse the order
	stack<Node*> st1; // Stack to hold nodes for processing
	stack<Node*> st2; // Stack to hold nodes in postorder sequence
	st1.push(root);

	while (!st1.empty()){
		Node* node = st1.top();
		st1.pop();

		// Push the current node onto the second stack to maintain postorder sequence
		st2.push(node);

		// Push children onto the first stack in NORMAL order (left to right)
		// so that they are processed in reverse order (right to left) when popped
		for (Node* child : node->children)
			st1.push(child);
	}

	// Build the final postorder traversal result from the second stack
	while (!st2.empty()){
		ans.push_back(st2.top()->val); // store the value of the node in the answer vector
        st2.pop(); // remove the node from the second stack after visiting
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
	vector<int> recursiveResult = postorder(root);
	cout << "Preorder Traversal (Recursive): ";
	printTraversal(recursiveResult);

	// Approach 2: Preorder Traversal using Iteration
	vector<int> iterativeResult = postorderIterative(root);
	cout << "Preorder Traversal (Iterative): ";
	printTraversal(iterativeResult);

}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}