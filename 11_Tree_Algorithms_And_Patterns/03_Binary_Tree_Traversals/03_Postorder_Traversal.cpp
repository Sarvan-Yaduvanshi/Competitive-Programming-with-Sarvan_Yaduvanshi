/*
Author: Sarvan Yaduvanshi
Created : 2026-11-03 13:47:52
*/

/*
 * ============================================================================
 *  TREE TRAVERSAL PATTERN 3: POSTORDER TRAVERSAL (Left -> Right -> Root)
 *  Time: O(N)  |  Space: O(H) recursive/two stacks, O(1) Morris  (H = height)
 * ============================================================================
 *
 *  What is Postorder?
 *
 *    Rule (LRN):   1. Traverse LEFT subtree
 *                  2. Traverse RIGHT subtree
 *                  3. Visit ROOT (Node)
 *
 *    Name trick : POST = root comes AFTER its children.
 *    Easy line  : "Print the node when BOTH children are completely done."
 *
 *    Same rule is applied to EVERY subtree, not only the main root.
 *
 *  Golden Facts (VERY IMPORTANT):
 *    1. In postorder, the LAST value is always the ROOT of the tree.
 *    2. Children are always processed BEFORE their parent.
 *       So when you reach a node, you already know the answer of its
 *       left and right subtree. This is the base of Tree DP.
 *    3. Postorder = REVERSE of (Root -> Right -> Left).
 *       Your Approach 2 uses this trick.
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
 *    Postorder Output : [4, 5, 2, 6, 3, 1]
 *
 * ----------------------------------------------------------------------------
 *  EXAMPLE 2: Uneven Tree (same BST as before)
 *
 *                 10
 *                /  \
 *               5    15
 *              /    /  \
 *             3    12   20
 *              \
 *               4
 *
 *    Postorder Output : [4, 3, 5, 12, 20, 15, 10]
 *    (Not sorted. Only INORDER of a BST is sorted.)
 *
 * ----------------------------------------------------------------------------
 *  EXAMPLE 3: Edge Cases
 *
 *      Empty tree  (root = null)   ->  []       (early return in all 3)
 *      Single node [7]             ->  [7]
 *
 *      Left skewed  :      3                   Postorder : [1, 2, 3]
 *                         /
 *                        2
 *                       /
 *                      1
 *
 *      Right skewed :  1 -> 2 -> 3             Postorder : [3, 2, 1]
 *      (height H = N, worst case)
 *
 * ============================================================================
 *  APPROACH 1: RECURSIVE (lambda with self, your Approach 1)
 * ============================================================================
 *
 *    - Edge case : root == nullptr -> return empty vector.
 *    - Lambda takes (self, node). "self" lets a lambda call itself.
 *    - Base case : node == nullptr -> return.
 *    - Order of the 3 lines is the whole traversal:
 *          self(node->left)         <- go left FIRST
 *          self(node->right)        <- go right SECOND
 *          ans.push_back(node->val) <- VISIT LAST
 *    - "ans" is captured by reference [&], so one shared vector is used.
 *    - Time O(N), Space O(H) call stack.
 *
 *    Dry Run, Example 1 (VISIT happens AFTER both children return):
 *
 *      postorder(1)
 *        postorder(2)
 *          postorder(4)
 *            postorder(null) -> return
 *            postorder(null) -> return
 *            VISIT 4
 *          postorder(5)
 *            postorder(null) -> return
 *            postorder(null) -> return
 *            VISIT 5
 *          VISIT 2
 *        postorder(3)
 *          postorder(null) -> return        (3 has no left child)
 *          postorder(6)
 *            postorder(null) -> return
 *            postorder(null) -> return
 *            VISIT 6
 *          VISIT 3
 *        VISIT 1
 *
 *      Result: 4, 5, 2, 6, 3, 1
 *
 *    Dry Run, Example 2:
 *
 *      postorder(10)
 *        postorder(5)
 *          postorder(3)
 *            postorder(null) -> return
 *            postorder(4)
 *              postorder(null) -> return
 *              postorder(null) -> return
 *              VISIT 4
 *            VISIT 3
 *          postorder(null) -> return        (5 has no right child)
 *          VISIT 5
 *        postorder(15)
 *          postorder(12)
 *            postorder(null) -> return
 *            postorder(null) -> return
 *            VISIT 12
 *          postorder(20)
 *            postorder(null) -> return
 *            postorder(null) -> return
 *            VISIT 20
 *          VISIT 15
 *        VISIT 10
 *
 *      Result: 4, 3, 5, 12, 20, 15, 10
 *
 *    Dry Run, Example 3 (left skewed 3 -> 2 -> 1):
 *
 *      postorder(3)
 *        postorder(2)
 *          postorder(1)
 *            postorder(null) -> return
 *            postorder(null) -> return
 *            VISIT 1
 *          postorder(null) -> return
 *          VISIT 2
 *        postorder(null) -> return
 *        VISIT 3
 *
 *      Result: 1, 2, 3
 *      Single [7] : null, null, VISIT 7      -> [7]
 *      Empty      : early return             -> []
 *
 * ============================================================================
 *  APPROACH 2: ITERATIVE WITH TWO STACKS (your Approach 2)
 * ============================================================================
 *
 *    Idea (2 steps):
 *      Step 1: Do a modified preorder: Root -> Right -> Left.
 *              Every popped node from st1 is pushed on st2.
 *      Step 2: st2 now holds Root, Right, Left order (bottom -> top).
 *              Popping st2 reverses it: Left, Right, Root = POSTORDER.
 *
 *    Loop while st1 not empty:
 *      - curr = st1.top(); st1.pop();
 *      - st2.push(curr);
 *      - push LEFT child on st1 first (if exists).
 *      - push RIGHT child on st1 second (if exists).
 *        Stack is LIFO, so RIGHT is popped first. That gives Root, Right,
 *        Left on st2.
 *    Then: while st2 not empty -> ans.push_back(st2.top()->val); st2.pop();
 *
 *    - Time O(N), Space O(N) (st2 holds ALL nodes, st1 holds up to O(H)).
 *    - Compare with preorder iterative: there we push RIGHT first. Here we
 *      push LEFT first, because the order is reversed at the end.
 *
 *    Dry Run, Example 1 (stack: bottom -> top, top at the right):
 *
 *      Start          : st1 = [1]                    st2 = []
 *      pop 1 -> st2   : push 2, push 3               st1 = [2, 3]
 *                                                    st2 = [1]
 *      pop 3 -> st2   : no left, push 6              st1 = [2, 6]
 *                                                    st2 = [1, 3]
 *      pop 6 -> st2   : no children                  st1 = [2]
 *                                                    st2 = [1, 3, 6]
 *      pop 2 -> st2   : push 4, push 5               st1 = [4, 5]
 *                                                    st2 = [1, 3, 6, 2]
 *      pop 5 -> st2   : no children                  st1 = [4]
 *                                                    st2 = [1, 3, 6, 2, 5]
 *      pop 4 -> st2   : no children                  st1 = []
 *                                                    st2 = [1, 3, 6, 2, 5, 4]
 *
 *      st2 order (bottom -> top) = Root, Right, Left = 1 3 6 2 5 4
 *      Pop st2 from the top:  4, 5, 2, 6, 3, 1
 *
 *      Output: 4, 5, 2, 6, 3, 1
 *
 *    Dry Run, Example 2:
 *
 *      Start          : st1 = [10]                   st2 = []
 *      pop 10 -> st2  : push 5, push 15              st1 = [5, 15]
 *                                                    st2 = [10]
 *      pop 15 -> st2  : push 12, push 20             st1 = [5, 12, 20]
 *                                                    st2 = [10, 15]
 *      pop 20 -> st2  : no children                  st1 = [5, 12]
 *                                                    st2 = [10, 15, 20]
 *      pop 12 -> st2  : no children                  st1 = [5]
 *                                                    st2 = [10, 15, 20, 12]
 *      pop 5  -> st2  : push 3 (right null)          st1 = [3]
 *                                                    st2 = [10, 15, 20, 12, 5]
 *      pop 3  -> st2  : push 4 (left null)           st1 = [4]
 *                                                    st2 = [10,15,20,12,5,3]
 *      pop 4  -> st2  : no children                  st1 = []
 *                                                    st2 = [10,15,20,12,5,3,4]
 *
 *      Pop st2 from the top:  4, 3, 5, 12, 20, 15, 10
 *
 *      Output: 4, 3, 5, 12, 20, 15, 10
 *
 *    Dry Run, Example 3 (left skewed 3 -> 2 -> 1):
 *
 *      st1 = [3]        pop 3 -> st2 = [3],       push 2   st1 = [2]
 *      pop 2 -> st2 = [3, 2],                     push 1   st1 = [1]
 *      pop 1 -> st2 = [3, 2, 1],                           st1 = []
 *      Pop st2 from the top:  1, 2, 3
 *
 *      Output: 1, 2, 3
 *      Single [7] : st1=[7], pop -> st2=[7], pop st2 -> [7]
 *
 * ============================================================================
 *  APPROACH 3: MORRIS POSTORDER (your Approach 3, O(1) space)
 * ============================================================================
 *
 *    - No recursion, no stack. Uses TEMPORARY thread links like Morris
 *      inorder, plus ONE extra trick: reverse a right boundary.
 *
 *    Setup: dummy node (value 0), dummy.left = root, curr = &dummy.
 *      Why dummy? The LAST right spine of the whole tree (root -> right ->
 *      right ...) never gets a second visit without it. With dummy, the
 *      whole tree becomes the LEFT subtree of dummy, so that spine is
 *      collected at the very end. (Dummy lives on the stack, no delete.)
 *
 *    Loop while curr != nullptr:
 *
 *      Case 1: curr->left == nullptr
 *          Nothing to visit. Just curr = curr->right.
 *          (right may be a real child OR a thread going back up)
 *
 *      Case 2: curr->left exists
 *          Find predecessor: start at curr->left, keep going right while
 *          (pred->right != null AND pred->right != curr).
 *
 *          Case 2a: pred->right == nullptr   (FIRST time here)
 *              Make thread: pred->right = curr.
 *              Go left: curr = curr->left.      (NO visit)
 *
 *          Case 2b: pred->right == curr      (SECOND time, came back)
 *              Left subtree is DONE. Collect its RIGHT BOUNDARY from
 *              curr->left down to pred, in REVERSE order (bottom -> top).
 *              Remove thread: pred->right = nullptr.
 *              Go right: curr = curr->right.
 *
 *    Why the right boundary, in reverse?
 *      After the left subtree of curr is fully done, the only nodes still
 *      waiting are the nodes on the path  curr->left -> right -> right ->
 *      ... -> pred.  Each of them has finished its left side and its right
 *      side (the right ones were already printed). So they print bottom up:
 *      pred first, curr->left last. That is postorder.
 *
 *    How reverse works (no extra memory):
 *      reverseRightBoundary(from, to) flips the right pointers on the path
 *      so that walking from "to" going right reaches "from".
 *      collect...() = reverse, walk from "to" to "from" collecting values,
 *      then reverse back so the tree is restored.
 *
 *      Mini example, path 1 -> 3 -> 6, 6.right = thread to dummy D:
 *
 *        Before   : 1 -> 3 -> 6
 *        reverse  : prev=1, curr=3.
 *                   next=6;  3.right=1; prev=3; curr=6.
 *                   next=D;  6.right=3; prev=6; curr=D. prev==to, STOP.
 *        Now      : 6 -> 3 -> 1
 *        Walk     : collect 6, 3, 1
 *        reverse back : 1 -> 3 -> 6, then pred->right = nullptr.
 *
 *    - Time O(N): each edge is walked and reversed a constant number of
 *      times. Space O(1).
 *
 *    Dry Run, Example 1:  (D = dummy, D.left = 1)
 *
 *      curr=D : left=1. pred: 1 -> 3 -> 6 (6.right null).
 *               2a: thread 6->D. curr = 1
 *      curr=1 : left=2. pred: 2 -> 5 (5.right null).
 *               2a: thread 5->1. curr = 2
 *      curr=2 : left=4. pred=4 (4.right null).
 *               2a: thread 4->2. curr = 4
 *      curr=4 : left null. Case 1: curr = 4.right = 2 (thread)
 *      curr=2 : left=4. pred=4, 4.right == 2 == curr.
 *               2b: collect path 4..4 -> COLLECT 4.
 *               4.right = null. curr = 2.right = 5
 *      curr=5 : left null. Case 1: curr = 5.right = 1 (thread)
 *      curr=1 : left=2. pred: 2 -> 5, 5.right == 1 == curr.
 *               2b: collect path 2 -> 5, reversed -> COLLECT 5, 2.
 *               5.right = null. curr = 1.right = 3
 *      curr=3 : left null. Case 1: curr = 3.right = 6
 *      curr=6 : left null. Case 1: curr = 6.right = D (thread)
 *      curr=D : left=1. pred: 1 -> 3 -> 6, 6.right == D == curr.
 *               2b: collect path 1 -> 3 -> 6, reversed -> COLLECT 6, 3, 1.
 *               6.right = null. curr = D.right = null
 *      End    : STOP, all threads removed, tree is same as before.
 *
 *      Output: 4, 5, 2, 6, 3, 1
 *
 *    Dry Run, Example 2:  (D.left = 10)
 *
 *      curr=D  : pred: 10 -> 15 -> 20. 2a: thread 20->D. curr = 10
 *      curr=10 : left=5. pred=5 (5.right null). 2a: thread 5->10. curr = 5
 *      curr=5  : left=3. pred: 3 -> 4 (4.right null).
 *                2a: thread 4->5. curr = 3
 *      curr=3  : left null. Case 1: curr = 3.right = 4
 *      curr=4  : left null. Case 1: curr = 4.right = 5 (thread)
 *      curr=5  : left=3. pred: 3 -> 4, 4.right == 5 == curr.
 *                2b: collect path 3 -> 4, reversed -> COLLECT 4, 3.
 *                4.right = null. curr = 5.right = 10 (thread)
 *      curr=10 : left=5. pred=5, 5.right == 10 == curr.
 *                2b: collect path 5..5 -> COLLECT 5.
 *                5.right = null. curr = 10.right = 15
 *      curr=15 : left=12. pred=12 (12.right null).
 *                2a: thread 12->15. curr = 12
 *      curr=12 : left null. Case 1: curr = 12.right = 15 (thread)
 *      curr=15 : left=12. pred=12, 12.right == 15 == curr.
 *                2b: collect path 12..12 -> COLLECT 12.
 *                12.right = null. curr = 15.right = 20
 *      curr=20 : left null. Case 1: curr = 20.right = D (thread)
 *      curr=D  : left=10. pred: 10 -> 15 -> 20, 20.right == D == curr.
 *                2b: collect path 10 -> 15 -> 20, reversed
 *                -> COLLECT 20, 15, 10.
 *                20.right = null. curr = D.right = null
 *      End     : STOP
 *
 *      Output: 4, 3, 5, 12, 20, 15, 10
 *
 *    Dry Run, Example 3 (left skewed 3 -> 2 -> 1):  (D.left = 3)
 *
 *      curr=D : pred=3 (3.right null). 2a: thread 3->D. curr = 3
 *      curr=3 : left=2. pred=2. 2a: thread 2->3. curr = 2
 *      curr=2 : left=1. pred=1. 2a: thread 1->2. curr = 1
 *      curr=1 : left null. Case 1: curr = 1.right = 2 (thread)
 *      curr=2 : pred=1, 1.right == 2. 2b: COLLECT 1.
 *               1.right = null. curr = 2.right = 3 (thread)
 *      curr=3 : pred=2, 2.right == 3. 2b: COLLECT 2.
 *               2.right = null. curr = 3.right = D (thread)
 *      curr=D : pred=3, 3.right == D. 2b: COLLECT 3.
 *               3.right = null. curr = null
 *      Output: 1, 2, 3     (no stack used)
 *
 *      Single [7] : D: pred=7, thread 7->D, curr=7.
 *                   curr=7: left null, curr = 7.right = D.
 *                   curr=D: pred=7, 7.right == D, COLLECT 7, curr = null.
 *                   -> [7]
 *
 * ----------------------------------------------------------------------------
 *  Compare all 3 approaches:
 *
 *      Approach     | Time | Space      | Modifies tree? | Difficulty
 *      -------------+------+------------+----------------+-----------
 *      Recursive    | O(N) | O(H)       | No             | Easy
 *      Two Stacks   | O(N) | O(N)       | No             | Medium
 *      Morris       | O(N) | O(1)       | Temporarily    | Very Hard
 *
 * ----------------------------------------------------------------------------
 *  Compare with other traversals (Example 1 tree):
 *
 *      Preorder   (N L R) : 1 2 4 5 3 6
 *      Inorder    (L N R) : 4 2 5 1 3 6
 *      Postorder  (L R N) : 4 5 2 6 3 1      <== this one
 *      Level Order (BFS)  : 1 2 3 4 5 6
 *
 *    Only the position of "visit" changes in DFS:
 *      before children = preorder
 *      between children = inorder
 *      after children = postorder
 *
 * ----------------------------------------------------------------------------
 *  When to use Postorder?
 *    - Delete / free a whole tree (children first, then parent).
 *    - Height, depth, size of a tree (need children's answer first).
 *    - Diameter, balanced check, max path sum (Tree DP).
 *    - Lowest Common Ancestor.
 *    - Postfix expression from an expression tree.
 *    - Folder size (size of folder = sum of children sizes + itself).
 *    - Any task where children must be done BEFORE the parent.
 *
 * ----------------------------------------------------------------------------
 *  Complexity:
 *    Time  : O(N) - every node visited exactly once.
 *    Space : Recursive O(H). Two Stacks O(N). Morris O(1).
 *            Balanced tree : H = log N
 *            Skewed tree   : H = N  (worst case)
 *
 * ----------------------------------------------------------------------------
 *  Common Mistakes:
 *    1. Two stacks: pushing RIGHT before LEFT on st1 -> output becomes
 *       Root, Left, Right reversed wrongly (gives Root-first mix, not
 *       postorder). Push LEFT first, RIGHT second.
 *    2. Two stacks: reading st2 from the bottom. Must pop from the top.
 *    3. Recursive: putting VISIT before the recursive calls (that is
 *       preorder) or between them (that is inorder).
 *    4. Morris: forgetting the dummy node -> last right spine is missed.
 *    5. Morris: forgetting to reverse the boundary BACK -> tree is broken.
 *    6. Morris: collecting in Case 2a (first visit). Must collect in 2b.
 *    7. Morris: forgetting "pred->right != curr" in the while loop ->
 *       infinite loop on the thread.
 *    8. Recursive: forgetting the base case (node == nullptr) -> crash.
 *
 * ----------------------------------------------------------------------------
 *  Practice Problems (in order):
 *    145. Binary Tree Postorder Traversal         (Easy)   <- start here
 *    590. N-ary Tree Postorder Traversal          (Easy)
 *    104. Maximum Depth of Binary Tree            (Easy)
 *    226. Invert Binary Tree                      (Easy)
 *    110. Balanced Binary Tree                    (Easy)
 *    543. Diameter of Binary Tree                 (Easy)
 *    236. Lowest Common Ancestor of a Binary Tree (Medium)
 *    106. Construct Binary Tree from Inorder
 *         and Postorder Traversal                 (Medium)
 *    124. Binary Tree Maximum Path Sum            (Hard)
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

// Approach 1: Recursive Postorder Traversal
static vector<int> postorderTraversalRecursive(TreeNode* root){
	vector<int> ans;

	// Edge case: if the root is null, return an empty vector
	if (root == nullptr)
		return ans;

	// Recursive lambda function for postorder traversal
	auto postorder = [&](auto&& self, const TreeNode* node) -> void{
		// Base case: if the current node is null, return
		if (node == nullptr)
			return;

		// Postorder traversal: visit left subtree, right subtree, then current node
		// Recursive call to the left child
		self(self, node->left);

		// Recursive call to the right child
		self(self, node->right);

		// Visit the current node and add its value to the answer vector
		ans.push_back(node->val);
	};

	postorder(postorder, root);
	return ans;
}

// Approach 2: Iterative Postorder Traversal using two stacks
static vector<int> postorderTraversalIterative(TreeNode* root){
	vector<int> ans;

	// Edge case: if the root is null, return an empty vector
	if (root == nullptr)
		return ans;

	// Use two stacks to perform postorder traversal iteratively
	stack<TreeNode*> st1; // Stack to hold nodes for processing
	stack<TreeNode*> st2; // Stack to hold nodes in postorder sequence

	st1.push(root); // Start with the root node in the first stack

	// Process nodes until the first stack is empty
	while (!st1.empty()){
		// save the top node from the first stack and pop it
		TreeNode* curr = st1.top();
		st1.pop();

		// Push the current node onto the second stack to maintain postorder sequence
		st2.push(curr);

		// left child is pushed first so that right child is processed first (LIFO order)
		if (curr->left != nullptr)
			st1.push(curr->left);

		// right child is pushed after left child so that it is processed first (LIFO order)
		if (curr->right != nullptr)
			st1.push(curr->right);
	}

	// Build the final postorder traversal result from the second stack
	while (!st2.empty()){
		ans.push_back(st2.top()->val); // store the value of the node in the answer vector
		st2.pop(); // remove the node from the second stack after visiting
	}

	return ans;
}

// Approach 3: Morris Postorder Traversal (Threaded Binary Tree)
static vector<int> postorderTraversalMorrisAlgo(TreeNode* root){
	vector<int> ans;

	// Edge case: if the root is null, return an empty vector
	if (root == nullptr)
		return ans;

	// Lambda function to reverse the right boundary of a subtree
	auto reverseRightBoundary = [](TreeNode* from, TreeNode* to) -> void{
		// Base case: if the from and to nodes are the same, no reversal is needed
		if (from == to)
			return;

		// Use two pointers to reverse the right boundary of the subtree
		TreeNode* prev = from; // initialize prev to the starting node of the boundary
		TreeNode* curr = from->right; // initialize curr to the right child of the starting node

		// Continue reversing the right boundary until we reach the 'to' node
		while (true){
			// Step 1: Save the next node to process (the right child of the current node)
			TreeNode* next = curr->right;

			// Step 2: Reverse the right pointer of the current node to point to the previous node
			curr->right = prev;

			// Step 3: Move the prev and curr pointers forward to continue the reversal
			prev = curr;
			curr = next;

			// Step 4: If we have reached the 'to' node, break the loop as the reversal is complete
			if (prev == to)
				break;
		}
	};

	// Lambda function to collect the values of the nodes in the reversed right boundary
	auto collectReverseRightBoundary = [&](TreeNode* from, TreeNode* to) -> void{
		// Step 1: Reverse the right boundary of the subtree from 'from' to 'to'
		reverseRightBoundary(from, to);

		// Step 2: Traverse the reversed right boundary and collect the values of the nodes
		TreeNode* curr = to;
		while (true){
			// Step 3: Add the value of the current node to the answer vector
			ans.push_back(curr->val);

			// Step 4: If we have reached the 'from' node, break the loop as we have collected all values
			if (curr == from)
				break;

			// Step 5: Move to the right child of the current node to continue collecting values
			curr = curr->right;
		}

		// Step 6: Reverse the right boundary back to its original order to restore the tree structure
		reverseRightBoundary(to, from);
	};

	TreeNode dummy(0);
	dummy.left = root;

	TreeNode* curr = &dummy;

	while (curr != nullptr){
		if (curr->left == nullptr){
			curr = curr->right;

		} else{
			TreeNode* predecessor = curr->left;
			while (predecessor->right != nullptr && predecessor->right != curr)
				predecessor = predecessor->right;

			if (predecessor->right == nullptr){
				predecessor->right = curr;
				curr = curr->left;

			} else{
				collectReverseRightBoundary(curr->left, predecessor);

				predecessor->right = nullptr;
				curr = curr->right;
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

	// Approach 1: Recursive Postorder Traversal
	vector<int> postorderRecursive = postorderTraversalRecursive(root);
	cout << "Postorder Traversal (Recursive) ";
	printTraversal(postorderRecursive);

	// Approach 2: Iterative Postorder Traversal
	vector<int> postorderIterative = postorderTraversalIterative(root);
	cout << "Postorder Traversal (Iterative) ";
	printTraversal(postorderIterative);

	// Approach 3: Morris Postorder Traversal
	vector<int> postorderMorris = postorderTraversalMorrisAlgo(root);
	cout << "Postorder Traversal (Morris) ";
	printTraversal(postorderMorris);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}