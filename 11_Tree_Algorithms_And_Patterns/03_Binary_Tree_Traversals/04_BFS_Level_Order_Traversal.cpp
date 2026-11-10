/*
Author: Sarvan Yaduvanshi
Created : 2026-11-03 13:47:52
*/

/*
 * ============================================================================
 *  TREE TRAVERSAL PATTERN 4: LEVEL ORDER TRAVERSAL (BFS)
 *  Time: O(N)  |  Space: O(W)   (W = maximum width of the tree)
 * ============================================================================
 *
 *  What is BFS (Breadth First Search)?
 *
 *    BFS is a traversal that visits nodes LEVEL BY LEVEL, from top to bottom
 *    and from left to right. It finishes ALL nodes at distance 1 from the
 *    start before it touches any node at distance 2, and so on.
 *
 *    Easy line  : "Visit everything NEAR first, then go farther."
 *    Picture    : a stone dropped in water. Ripples spread ring by ring.
 *    Other name : Level Order Traversal (when used on a tree).
 *
 *    Rule for a tree:
 *      1. Visit the root                (level 0)
 *      2. Visit all nodes of level 1    (left to right)
 *      3. Visit all nodes of level 2    (left to right)
 *      4. ... until no level is left.
 *
 *  DFS vs BFS (the big picture):
 *
 *      DFS (Pre/In/Post) : go DEEP first, use STACK or recursion.
 *      BFS (Level Order) : go WIDE first, use QUEUE.
 *
 * ----------------------------------------------------------------------------
 *  WHY QUEUE? (and not stack, array, or other DSA)
 *
 *    BFS needs one rule: "the node discovered FIRST must be processed
 *    FIRST". That rule is exactly FIFO (First In, First Out) = QUEUE.
 *
 *    Why it works on a tree:
 *      - Nodes of level L are already inside the queue.
 *      - When we pop one, its children (level L+1) go to the BACK.
 *      - All level L nodes are ahead of them, so they are popped first.
 *      - So level L+1 can never be processed before level L ends.
 *
 *    Why NOT other structures:
 *
 *      Stack (LIFO)    : last child pushed is popped first, so we dive deep.
 *                        That is DFS (preorder), not BFS.
 *      Recursion       : uses the call stack (a stack). Same problem, goes
 *                        deep first. (Can be forced with a depth parameter,
 *                        see "Related Concepts".)
 *      Priority Queue  : pops by smallest value or cost, not by arrival.
 *                        Used in Dijkstra, not in plain BFS.
 *      Plain Array     : can work if you keep a head index, but it is a
 *                        queue in disguise. queue<T> is cleaner.
 *      Deque           : works too (it is a queue with 2 ends). Needed for
 *                        zigzag and 0-1 BFS.
 *      Set / Map       : no order of arrival. Useless for BFS order.
 *
 *    queue<T> in C++: push() adds at BACK, front() reads FRONT, pop()
 *    removes FRONT. All O(1).
 *
 * ----------------------------------------------------------------------------
 *  THE LEVEL SIZE TRICK (most important line in your code)
 *
 *      size_t level_size = q.size();
 *
 *    Problem : q.size() CHANGES while we pop parents and push children.
 *              If we looped "while q.size()", levels would mix together.
 *    Fix     : take a SNAPSHOT of the size at the start of each level.
 *              Pop exactly that many nodes. Those are the current level.
 *              Everything pushed during the loop belongs to the NEXT level.
 *
 *    Without snapshot -> you get a flat list [1,2,3,4,5,6,7].
 *    With snapshot    -> you get grouped levels [[1],[2,3],[4,5,6],[7]].
 *
 * ----------------------------------------------------------------------------
 *  YOUR CODE: Step by Step
 *
 *    Edge case  : root == nullptr -> return empty vector.
 *    Setup      : queue<TreeNode*> q, push root (level 0).
 *    Outer loop : while (!q.empty())      one iteration = ONE LEVEL.
 *    Step 2     : level_size = q.size()   snapshot of this level.
 *                 current_level.reserve(level_size) allocates memory once.
 *    Inner loop : for i in [0, level_size)   pop exactly this level.
 *      Step 3   : current_node = q.front(); q.pop();
 *      Step 4   : current_level.emplace_back(current_node->val);   VISIT
 *      Step 5   : if left  exists -> q.push(left)    (next level, back)
 *      Step 6   : if right exists -> q.push(right)   (next level, back)
 *    Step 7     : ans.emplace_back(current_level);   level finished, store.
 *
 *    Left is pushed BEFORE right, so each level comes out left to right.
 *    Time  O(N): every node is pushed once and popped once.
 *    Space O(W): queue holds at most one full level at a time.
 *
 * ----------------------------------------------------------------------------
 *  EXAMPLE (best example, 4 levels, uneven shape)
 *
 *                  1                  Level 0
 *                 / \
 *                2   3                Level 1
 *               / \   \
 *              4   5   6              Level 2
 *                 /
 *                7                    Level 3
 *
 *    Level Order Output : [[1], [2, 3], [4, 5, 6], [7]]
 *
 * ----------------------------------------------------------------------------
 *  FULL DRY RUN  (queue: FRONT at the left, BACK at the right)
 *
 *    Start : q = [1]          ans = []
 *
 *    ---- OUTER LOOP 1  (Level 0) ----
 *      level_size = 1, current_level = []
 *        i=0 : pop 1.   current_level = [1]
 *                       push left 2, push right 3
 *                       q = [2, 3]
 *      store level -> ans = [[1]]
 *
 *    ---- OUTER LOOP 2  (Level 1) ----
 *      level_size = 2, current_level = []
 *        i=0 : pop 2.   current_level = [2]
 *                       push left 4, push right 5
 *                       q = [3, 4, 5]
 *        i=1 : pop 3.   current_level = [2, 3]
 *                       left is null (skip), push right 6
 *                       q = [4, 5, 6]
 *      store level -> ans = [[1], [2, 3]]
 *
 *    ---- OUTER LOOP 3  (Level 2) ----
 *      level_size = 3, current_level = []
 *        i=0 : pop 4.   current_level = [4]
 *                       no children
 *                       q = [5, 6]
 *        i=1 : pop 5.   current_level = [4, 5]
 *                       push left 7, right is null (skip)
 *                       q = [6, 7]
 *        i=2 : pop 6.   current_level = [4, 5, 6]
 *                       no children
 *                       q = [7]
 *      store level -> ans = [[1], [2, 3], [4, 5, 6]]
 *
 *    ---- OUTER LOOP 4  (Level 3) ----
 *      level_size = 1, current_level = []
 *        i=0 : pop 7.   current_level = [7]
 *                       no children
 *                       q = []
 *      store level -> ans = [[1], [2, 3], [4, 5, 6], [7]]
 *
 *    ---- END ----
 *      q is empty -> while loop stops.
 *
 *    Output : [[1], [2, 3], [4, 5, 6], [7]]
 *
 *    Notice: when level 2 started, the queue was [4, 5, 6] and 7 was NOT in
 *    it yet. The snapshot (3) stopped us from popping 7 in the same level.
 *
 * ----------------------------------------------------------------------------
 *  Edge Cases:
 *
 *      Empty tree  (root = null)  ->  []
 *      Single node [7]            ->  [[7]]
 *      Left skewed 3 -> 2 -> 1    ->  [[3], [2], [1]]   (queue size is 1)
 *      Perfect tree, last level   ->  holds about N/2 nodes in the queue
 *                                     (worst case space O(N))
 *
 * ----------------------------------------------------------------------------
 *  Compare with all traversals (same tree as above):
 *
 *      Preorder    (N L R) : 1 2 4 5 7 3 6
 *      Inorder     (L N R) : 4 2 7 5 1 3 6
 *      Postorder   (L R N) : 4 7 5 2 6 3 1
 *      Level Order (BFS)   : 1 2 3 4 5 6 7     (grouped: [[1],[2,3],[4,5,6],[7]])
 *
 *      Approach     | DS used   | Goes      | Space
 *      -------------+-----------+-----------+------------------------------
 *      Pre/In/Post  | stack/rec | deep      | O(H) height
 *      Level Order  | queue     | wide      | O(W) width
 *
 *      Skewed tree : DFS space O(N), BFS space O(1).
 *      Perfect tree: DFS space O(log N), BFS space O(N / 2).
 *      So neither is always better. It depends on the tree shape.
 *
 * ----------------------------------------------------------------------------
 *  RELATED CONCEPTS (learn these next)
 *
 *    1. BFS on a GRAPH
 *         A graph can have cycles, so add a visited set/array. Mark a node
 *         visited when you PUSH it (not when you pop it), else the same
 *         node enters the queue many times. A tree needs no visited,
 *         because it has no cycles and each node has one parent.
 *
 *    2. SHORTEST PATH in an UNWEIGHTED graph or grid
 *         BFS reaches every node by the fewest edges, because it goes ring
 *         by ring. Level number = distance from start.
 *         Examples: shortest path in a maze, word ladder.
 *
 *    3. MULTI-SOURCE BFS
 *         Push ALL starting nodes into the queue at the beginning. All
 *         rings expand at the same time. Example: rotting oranges.
 *
 *    4. BFS on a GRID (matrix)
 *         Node = cell, neighbors = 4 (or 8) directions. Same queue idea.
 *         Examples: number of islands, flood fill.
 *
 *    5. 0-1 BFS
 *         Edge weights are only 0 or 1. Use a DEQUE. Push 0-weight
 *         neighbors at the FRONT, 1-weight at the BACK.
 *
 *    6. DIJKSTRA = BFS with a PRIORITY QUEUE
 *         Same idea, but pop the smallest distance first. Needed when
 *         edges have different weights.
 *
 *    7. TOPOLOGICAL SORT (Kahn's Algorithm)
 *         BFS on a DAG using indegree. Push nodes with indegree 0, pop,
 *         reduce neighbors' indegree.
 *
 *    8. BIDIRECTIONAL BFS
 *         Search from start and target at the same time, stop when the two
 *         searches meet. Much faster on big graphs.
 *
 *    9. LEVEL ORDER by DFS (recursion trick)
 *         Do preorder and pass "depth". If ans.size() == depth, add a new
 *         vector. Then ans[depth].push_back(val). Gives the same output as
 *         BFS, using the call stack. Space O(H).
 *
 *   10. FLAT BFS (no levels)
 *         Remove the level_size snapshot and the inner for loop. You get a
 *         plain list [1,2,3,4,5,6,7]. Use it when you do not care about
 *         level grouping.
 *
 * ----------------------------------------------------------------------------
 *  Small changes to the same template (level order variations):
 *
 *      Reverse level order  : reverse(ans) at the end.
 *      Zigzag               : flip direction on every odd level.
 *      Right side view      : keep only the LAST node of each level.
 *      Left side view       : keep only the FIRST node of each level.
 *      Average of levels    : sum the level, divide by level_size.
 *      Minimum depth        : stop at the FIRST node with no children.
 *      Maximum depth        : count how many levels (ans.size()).
 *      Maximum width        : track index of leftmost and rightmost node.
 *      N-ary tree           : push all children in a loop, not only 2.
 *
 * ----------------------------------------------------------------------------
 *  When to use BFS?
 *    - Need nodes grouped by LEVEL.
 *    - Need the SHORTEST path (fewest edges) in an unweighted graph.
 *    - Need the NEAREST something (nearest exit, closest 0).
 *    - Answer depends on distance from the start.
 *    - Need minimum depth, since it can stop early at the first leaf.
 *    - Spreading problems (fire, rotting, infection, flood).
 *
 *  When to use DFS instead?
 *    - Need to explore ALL paths (backtracking).
 *    - Need children's answers first (Tree DP, postorder).
 *    - Tree is very wide, so a queue would use a lot of memory.
 *
 * ----------------------------------------------------------------------------
 *  Complexity:
 *    Time  : O(N) - each node is pushed once and popped once.
 *    Space : O(W) - the queue holds at most one level of nodes.
 *            Skewed tree  : W = 1
 *            Perfect tree : W is about N / 2 (worst case)
 *    Output vector is not counted in auxiliary space.
 *
 * ----------------------------------------------------------------------------
 *  Common Mistakes:
 *    1. Not taking the level_size snapshot -> levels mix together.
 *    2. Using q.size() directly as the loop limit -> it grows inside the
 *       loop, so the loop reads into the next level.
 *    3. Forgetting the null check before q.push(left / right) -> crash when
 *       reading ->val of a null node.
 *    4. Pushing the root when it is null -> crash on the first pop.
 *    5. Using a stack instead of a queue -> you get DFS, not BFS.
 *    6. Graph BFS: marking visited on POP instead of PUSH -> duplicates in
 *       the queue, slow or wrong answers.
 *    7. Pushing right before left -> each level comes out right to left.
 *    8. Reading q.front() after q.pop() -> undefined behavior. Read first,
 *       then pop.
 *
 * ----------------------------------------------------------------------------
 *  Practice Problems (in order):
 *    102. Binary Tree Level Order Traversal       (Medium) <- start here
 *    107. Binary Tree Level Order Traversal II    (Medium)
 *    199. Binary Tree Right Side View             (Medium)
 *    637. Average of Levels in Binary Tree        (Easy)
 *    111. Minimum Depth of Binary Tree            (Easy)
 *    104. Maximum Depth of Binary Tree            (Easy)
 *    103. Binary Tree Zigzag Level Order          (Medium)
 *    429. N-ary Tree Level Order Traversal        (Medium)
 *    116. Populating Next Right Pointers in Each Node  (Medium)
 *    993. Cousins in Binary Tree                  (Easy)
 *    662. Maximum Width of Binary Tree            (Medium)
 *    994. Rotting Oranges                         (Medium, grid BFS)
 *    127. Word Ladder                             (Hard, graph BFS)
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

struct TreeNode{
	int val;
	TreeNode* left;
	TreeNode* right;

	explicit TreeNode(const int v) : val(v), left(nullptr), right(nullptr) {}
};

// 1. Standard Level-by-Level BFS (Returns 2D vector grouped by levels)
static vector<vector<int>> levelOrderOrBFS(TreeNode* root) {
	vector<vector<int>> ans;

	// Edge case: empty tree
	if (root == nullptr)
		return ans;

	// Use queue for BFS traversal(queue properties: FIFO, first in first out)
	queue<TreeNode*> q;
	q.push(root); // Step 1: Push Level 0 (Root) into the FIFO queue

	// Step 2: Process each level until the queue is empty
	while (!q.empty()){
		// Step 2: Take a snapshot of how many nodes are in the current level
		size_t level_size = q.size();
		vector<int> current_level;
		current_level.reserve(level_size);

		// Step 3: Process ONLY the nodes belonging to the current level
		for (int i = 0; i < level_size; i++){
			TreeNode* current_node = q.front(); // Get the front node in the queue (FIFO)
			q.pop(); // Remove the front node from the queue after processing

			// Step 4: Add the current node's value to the current level's result
			current_level.emplace_back(current_node->val);

			// Step 5: Push left children to the BACK of the queue for the next level
			if (current_node->left != nullptr)
				q.push(current_node->left);

			// Step 6: Push right children to the BACK of the queue for the next level
			if (current_node->right != nullptr)
				q.push(current_node->right);
		}

		// Step 7: Current level is completely finished; store it!
		ans.emplace_back(current_level);
	}

	return ans;
}

// Function to build a binary tree from a vector of values (for testing purposes)
static TreeNode* buildTree(const vector<int>& values){
	size_t n = values.size();

	// Edge case: empty tree or root is null
	if (n == 0 || values[0] == -1)
		return nullptr;

	auto* root = new TreeNode(values[0]);

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

	// Perform BFS Level Order Traversal
	vector<vector<int>> bfs_result = levelOrderOrBFS(root);
	cout << "BFS Level Order Traversal (grouped by levels):\n[";
	for (size_t i = 0; i < bfs_result.size(); ++i){
		cout << "[";
		for (size_t j = 0; j < bfs_result[i].size(); ++j){
			cout << bfs_result[i][j];
			if (j < bfs_result[i].size() - 1)
				cout << " ";
		}
		cout << "]";
		if (i < bfs_result.size() - 1)
			cout << ", ";
	}
	cout << "]\n";

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

	solve();

    return 0;
}
