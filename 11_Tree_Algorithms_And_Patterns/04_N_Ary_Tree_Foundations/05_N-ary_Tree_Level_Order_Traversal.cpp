/*
Author: Sarvan Yaduvanshi
Created : 2026-11-11 03:32:36
*/

/*
 * ============================================================================
 *  TREE TRAVERSAL PATTERN 8: N-ARY TREE LEVEL ORDER TRAVERSAL (BFS)
 *  Time: O(N)  |  Space: O(W) BFS, O(H) DFS   (W = max width, H = height)
 * ============================================================================
 *
 *  What is Level Order (N-ary)?
 *
 *    Visit nodes LEVEL BY LEVEL, top to bottom, and inside one level from
 *    LEFT to RIGHT (child[0] first, then child[1], ...). Output is grouped:
 *    one inner vector per level.
 *
 *    Easy line  : "Visit everything NEAR the root first, then go farther."
 *    Other name : BFS (Breadth First Search) on a tree.
 *
 *    Binary vs N-ary:
 *      Binary BFS : push left, push right        (2 fixed children)
 *      N-ary BFS  : LOOP over node->children     (any number of children)
 *      Everything else (queue, level_size snapshot) is the SAME.
 *
 *    Why queue? FIFO: the node found FIRST is processed FIRST, so level L
 *    is always finished before level L+1 starts. (Full explanation is in
 *    your Binary Level Order concept file.)
 *
 * ----------------------------------------------------------------------------
 *  EXAMPLE 1: Small N-ary Tree
 *
 *                  1                  Level 0
 *                / | \
 *               3  2  4               Level 1
 *              / \
 *             5   6                   Level 2
 *
 *    Level Order Output : [[1], [3, 2, 4], [5, 6]]
 *
 * ----------------------------------------------------------------------------
 *  EXAMPLE 2: Bigger N-ary Tree (uneven, 4 levels)
 *
 *                       1                    Level 0
 *                 /   /   \   \
 *                2   3     4   5             Level 1
 *                   / \    |   / \
 *                  6   7   8   9  10         Level 2
 *                      |
 *                      11                    Level 3
 *
 *    Level Order Output : [[1], [2, 3, 4, 5], [6, 7, 8, 9, 10], [11]]
 *
 * ----------------------------------------------------------------------------
 *  EXAMPLE 3: Edge Cases
 *
 *      Empty tree  (root = null)   ->  []
 *      Single node [7]             ->  [[7]]
 *
 *      Skewed chain  1 -> 2 -> 3   ->  [[1], [2], [3]]
 *      (BFS queue size is always 1, DFS stack depth is N)
 *
 *      Wide tree (root 1 with leaf children 2,3,4,5):
 *                    1
 *                 / | | \
 *                2  3 4  5          ->  [[1], [2, 3, 4, 5]]
 *      (BFS queue holds N - 1 nodes at once, worst case space)
 *
 * ============================================================================
 *  APPROACH 1: BFS WITH QUEUE (your Approach 1)
 * ============================================================================
 *
 *    - Edge case : root == nullptr -> return empty vector.
 *    - queue<Node*> q, push root.
 *    - Outer loop : while (!q.empty())     one iteration = ONE LEVEL.
 *    - levelSize = q.size()                SNAPSHOT of this level.
 *      (q.size() changes inside the loop, so take it BEFORE popping.)
 *    - Inner loop : for i in [0, levelSize)
 *        Step A : currentNode = q.front(); q.pop();
 *        Step B : currentLevel.push_back(currentNode->val);   VISIT
 *        Step C : for (child : currentNode->children)
 *                     if child != nullptr -> q.push(child);   next level
 *    - After inner loop: ans.push_back(currentLevel).
 *    - Children are pushed in order, so each level comes out left to right.
 *    - Time O(N): each node pushed once, popped once.
 *      Space O(W): queue holds at most one level (plus part of the next).
 *
 *    Dry Run, Example 1 (queue: FRONT at the left, BACK at the right):
 *
 *      Start : q = [1]            ans = []
 *
 *      ---- LEVEL 0 ----
 *      levelSize = 1
 *        pop 1 -> currentLevel = [1]; push 3, 2, 4     q = [3, 2, 4]
 *      ans = [[1]]
 *
 *      ---- LEVEL 1 ----
 *      levelSize = 3
 *        pop 3 -> currentLevel = [3];       push 5, 6  q = [2, 4, 5, 6]
 *        pop 2 -> currentLevel = [3, 2];    no children q = [4, 5, 6]
 *        pop 4 -> currentLevel = [3, 2, 4]; no children q = [5, 6]
 *      ans = [[1], [3, 2, 4]]
 *
 *      ---- LEVEL 2 ----
 *      levelSize = 2
 *        pop 5 -> currentLevel = [5];       no children q = [6]
 *        pop 6 -> currentLevel = [5, 6];    no children q = []
 *      ans = [[1], [3, 2, 4], [5, 6]]
 *
 *      End : q empty -> STOP
 *
 *      Output: [[1], [3, 2, 4], [5, 6]]
 *
 *    Dry Run, Example 2:
 *
 *      Start : q = [1]
 *
 *      ---- LEVEL 0 ----  levelSize = 1
 *        pop 1 -> [1]; push 2, 3, 4, 5          q = [2, 3, 4, 5]
 *
 *      ---- LEVEL 1 ----  levelSize = 4
 *        pop 2 -> [2];          no children      q = [3, 4, 5]
 *        pop 3 -> [2, 3];       push 6, 7        q = [4, 5, 6, 7]
 *        pop 4 -> [2, 3, 4];    push 8           q = [5, 6, 7, 8]
 *        pop 5 -> [2, 3, 4, 5]; push 9, 10       q = [6, 7, 8, 9, 10]
 *
 *      ---- LEVEL 2 ----  levelSize = 5
 *        pop 6  -> [6];                  no children  q = [7, 8, 9, 10]
 *        pop 7  -> [6, 7];               push 11      q = [8, 9, 10, 11]
 *        pop 8  -> [6, 7, 8];            no children  q = [9, 10, 11]
 *        pop 9  -> [6, 7, 8, 9];         no children  q = [10, 11]
 *        pop 10 -> [6, 7, 8, 9, 10];     no children  q = [11]
 *
 *      ---- LEVEL 3 ----  levelSize = 1
 *        pop 11 -> [11];                 no children  q = []
 *
 *      End : q empty -> STOP
 *
 *      Output: [[1], [2, 3, 4, 5], [6, 7, 8, 9, 10], [11]]
 *
 *      Notice: when level 2 started, q = [6, 7, 8, 9, 10] and 11 was NOT in
 *      it yet. The snapshot (5) stopped us from popping 11 in the same level.
 *
 *    Dry Run, Example 3 (edge):
 *      Single [7]    : q=[7], levelSize=1, pop 7, level [7]      -> [[7]]
 *      Chain 1->2->3 : 3 outer loops, each levelSize = 1         -> [[1],[2],[3]]
 *      Wide tree     : level 0 pushes 2,3,4,5 (q size 4),
 *                      level 1 pops all 4                      -> [[1],[2,3,4,5]]
 *      Empty         : early return                              -> []
 *
 * ============================================================================
 *  APPROACH 2: DFS WITH DEPTH (your Approach 2)
 * ============================================================================
 *
 *    Idea: do a normal PREORDER DFS, but carry a "depth" number. The answer
 *    vector is indexed by depth: ans[depth] holds that level.
 *
 *    - Lambda takes (self, node, depth). Start with dfs(root, 0).
 *    - Base case : node == nullptr -> return.
 *    - NEW LEVEL TRICK:
 *          if (depth == ans.size()) ans.emplace_back();
 *      First time DFS reaches a depth, ans has exactly "depth" vectors,
 *      so size == depth. Add one empty vector for the new level.
 *    - VISIT : ans[depth].push_back(node->val);
 *    - Recurse every child with depth + 1.
 *    - Why order inside a level is still left to right: DFS visits child[0]
 *      subtree fully before child[1]. So at any depth, nodes arrive from the
 *      left side of the tree first.
 *    - Time O(N), Space O(H) call stack (output not counted).
 *    - Use when: you want recursion, or the tree is very wide (BFS queue
 *      would be big) and shallow.
 *
 *    Dry Run, Example 1  (ans shown after each VISIT):
 *
 *      dfs(1, 0) : size 0 == 0 -> new level.  VISIT 1   ans = [[1]]
 *        dfs(3, 1) : size 1 == 1 -> new level. VISIT 3  ans = [[1],[3]]
 *          dfs(5, 2) : size 2 == 2 -> new.     VISIT 5  ans = [[1],[3],[5]]
 *          dfs(6, 2) : size 3 != 2.            VISIT 6  ans = [[1],[3],[5,6]]
 *        dfs(2, 1) : size 3 != 1.              VISIT 2  ans = [[1],[3,2],[5,6]]
 *        dfs(4, 1) : size 3 != 1.              VISIT 4  ans = [[1],[3,2,4],[5,6]]
 *
 *      Output: [[1], [3, 2, 4], [5, 6]]   (same as BFS)
 *
 *    Dry Run, Example 2:
 *
 *      dfs(1, 0)  : new level 0.        ans[0] = [1]
 *        dfs(2, 1)  : new level 1.      ans[1] = [2]
 *        dfs(3, 1)  :                   ans[1] = [2, 3]
 *          dfs(6, 2)  : new level 2.    ans[2] = [6]
 *          dfs(7, 2)  :                 ans[2] = [6, 7]
 *            dfs(11, 3) : new level 3.  ans[3] = [11]
 *        dfs(4, 1)  :                   ans[1] = [2, 3, 4]
 *          dfs(8, 2)  :                 ans[2] = [6, 7, 8]
 *        dfs(5, 1)  :                   ans[1] = [2, 3, 4, 5]
 *          dfs(9, 2)  :                 ans[2] = [6, 7, 8, 9]
 *          dfs(10, 2) :                 ans[2] = [6, 7, 8, 9, 10]
 *
 *      Output: [[1], [2, 3, 4, 5], [6, 7, 8, 9, 10], [11]]   (same as BFS)
 *
 *    Dry Run, Example 3 (edge):
 *      Single [7]    : dfs(7,0) new level, VISIT 7                -> [[7]]
 *      Chain 1->2->3 : dfs(1,0), dfs(2,1), dfs(3,2), each makes a
 *                      new level                                  -> [[1],[2],[3]]
 *      Wide tree     : dfs(1,0) new level, then 2,3,4,5 at depth 1
 *                      (first one makes the level)              -> [[1],[2,3,4,5]]
 *      Empty         : early return                               -> []
 *
 * ----------------------------------------------------------------------------
 *  Compare the 2 approaches:
 *
 *      Approach     | DS used    | Time | Space      | Difficulty
 *      -------------+------------+------+------------+-----------
 *      BFS (queue)  | queue      | O(N) | O(W)       | Easy
 *      DFS + depth  | call stack | O(N) | O(H)       | Easy-Medium
 *
 *      Skewed chain : BFS space O(1),  DFS space O(N).
 *      Very wide    : BFS space O(N),  DFS space O(1) (H = 2).
 *      So neither is always better. It depends on the tree shape.
 *
 * ----------------------------------------------------------------------------
 *  Compare with other N-ary traversals (Example 1 tree):
 *
 *      Preorder    (Root, children L to R)         : 1 3 5 6 2 4
 *      Inorder     (child0, Root, other children)  : 5 3 6 1 2 4
 *      Postorder   (children L to R, Root)         : 5 6 3 2 4 1
 *      Level Order (BFS)                           : 1 3 2 4 5 6
 *                                         grouped  : [[1],[3,2,4],[5,6]]
 *
 *    Flat BFS = remove the levelSize snapshot and the inner for loop.
 *    You get a plain list [1, 3, 2, 4, 5, 6].
 *
 * ----------------------------------------------------------------------------
 *  Small changes to the same template (N-ary variations):
 *
 *      Reverse level order  : reverse(ans) at the end.
 *      Zigzag               : reverse every odd level.
 *      Right side view      : keep only the LAST node of each level.
 *      Max depth            : ans.size() (levels count, nodes counted).
 *      Level sum / average  : sum currentLevel, divide by levelSize.
 *      Minimum depth        : stop at the FIRST node with no children.
 *
 * ----------------------------------------------------------------------------
 *  When to use N-ary Level Order?
 *    - Need nodes grouped by LEVEL.
 *    - Need the depth or distance from the root.
 *    - Org chart: people grouped by management level.
 *    - File system: folders grouped by depth.
 *    - Time to inform / spread problems (each level = 1 time step).
 *
 * ----------------------------------------------------------------------------
 *  Complexity:
 *    Time  : O(N) - each node visited exactly once.
 *    Space : BFS O(W), DFS O(H). Output vector is not counted.
 *
 * ----------------------------------------------------------------------------
 *  Common Mistakes:
 *    1. BFS: no levelSize snapshot -> levels mix together.
 *    2. BFS: using q.size() directly as loop limit -> it grows inside the
 *       loop and reads into the next level.
 *    3. Using node->left / node->right. N-ary has only node->children.
 *    4. DFS: using "depth > ans.size()" or forgetting the new-level check
 *       -> ans[depth] out of range -> crash.
 *    5. DFS: passing depth instead of depth + 1 to children -> all nodes
 *       land in the wrong level.
 *    6. BFS: forgetting the root null check -> crash on the first pop.
 *    7. BFS: reading q.front() after q.pop() -> undefined behavior.
 *    8. Copy paste comments: both approach comments in your code say
 *       "Preorder Traversal". Change them to "Level Order Traversal".
 *
 * ----------------------------------------------------------------------------
 *  Practice Problems (N-ary tree only):
 *    429. N-ary Tree Level Order Traversal        (Medium) <- start here
 *    589. N-ary Tree Preorder Traversal           (Easy)
 *    590. N-ary Tree Postorder Traversal          (Easy)
 *    559. Maximum Depth of N-ary Tree             (Easy)
 *    690. Employee Importance                     (Medium, BFS or DFS)
 *   1376. Time Needed to Inform All Employees     (Medium, BFS or DFS)
 *   1490. Clone N-ary Tree                        (Medium, Premium)
 *   1506. Find Root of N-Ary Tree                 (Medium, Premium)
 *    428. Serialize and Deserialize N-ary Tree    (Hard, Premium)
 *    431. Encode N-ary Tree to Binary Tree        (Hard, Premium)
 *   1522. Diameter of N-Ary Tree                  (Medium, Premium)
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

// Approach 1: Use BFS (Level Order Traversal) to perform Preorder Traversal of an N-ary tree
static vector<vector<int>> LevelOrder(Node* root){
	vector<vector<int>> ans;

	// empty tree check
    if (root == nullptr)
        return ans;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()){
    	// Get the number of nodes at the current level
        const size_t levelSize = q.size();
    	vector<int> currentLevel;
    	currentLevel.reserve(levelSize);

    	// Process all nodes at the current level
        for (size_t i = 0; i < levelSize; ++i){
            Node* currentNode = q.front();
            q.pop();

            currentLevel.push_back(currentNode->val);

            // Enqueue all children of the current node
            for (Node* child : currentNode->children){
                if (child != nullptr)
                    q.push(child);
            }
        }

        ans.push_back(currentLevel);
    }

    return ans;
}

// Approach 2: Use DFFS (Depth First Search) to perform Preorder Traversal of an N-ary tree
static vector<vector<int>> LevelOrderDFS(Node* root){
    vector<vector<int>> ans;

    // empty tree check
    if (root == nullptr)
        return ans;

    // Lambda function for DFS traversal
    auto dfs = [&](auto&& self, Node* node, int depth) -> void{
        // Base case: if the current node is null, return
        if (node == nullptr)
            return;

        // If we reach a new depth level, add a new vector for that level
        if (depth == ans.size())
            ans.emplace_back();

        // Add the current node's value to the corresponding depth level
        ans[depth].push_back(node->val);

        // Recursively call DFS for each child of the current node
        for (Node* child : node->children)
            self(self, child, depth + 1);

    };

    dfs(dfs, root, 0);
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
	auto bfs_result = LevelOrder(root);
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

	// Approach 2: Preorder Traversal using DFS
	auto dfs_result = LevelOrderDFS(root);
	cout << "DFS Level Order Traversal (grouped by levels):\n[";
    for (size_t i = 0; i < dfs_result.size(); ++i){
        cout << "[";
        for (size_t j = 0; j < dfs_result[i].size(); ++j){
            cout << dfs_result[i][j];
            if (j < dfs_result[i].size() - 1)
                cout << " ";
        }
        cout << "]";
        if (i < dfs_result.size() - 1)
            cout << ", ";
    }
	cout << "]\n";
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}