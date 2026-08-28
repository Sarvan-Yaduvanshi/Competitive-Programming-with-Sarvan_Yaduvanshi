/*
                          ╔══════════════════════════════════════════════════════════════╗
                          ║  04. THE "TAKE / NOT-TAKE" PATTERN — Most Important Pattern! ║
                          ║  Level 2 — Recursion Patterns (The Core Engine of CP)        ║
                          ╚══════════════════════════════════════════════════════════════╝

🧠 THE TAKE / NOT-TAKE PATTERN (a.k.a. Include/Exclude)

This is THE most important recursion pattern in competitive programming.
Almost everything builds on this.

📖 THE IDEA:-

At each index i, you have exactly 2 CHOICES:
    ✅ TAKE arr[i]   — include it in current selection
    ❌ NOT TAKE arr[i] — skip it

This creates a BINARY TREE of decisions:

                      i=0
                    /      \
              TAKE a[0]   SKIP a[0]
               /    \       /    \
          TAKE a[1] SKIP  TAKE  SKIP    ... for each index

Total leaves = 2^n (every possible subset!)

🎯 Example of Problems that use this pattern:
   1. Print ALL subsequences
   2. Print subsequences with sum = K
   3. Count subsequences with sum = K
   4. Check if ANY subsequence has sum = K
   5. Generate all subsets (Power Set) — LC 78

1️⃣ THE "PAUSE BUTTON" (How the Call Stack actually works)
---------------------------------------------------------------------------
The biggest mistake beginners make is thinking recursion reads top-to-bottom
and finishes immediately. It does not!

Recursion is a PAUSE BUTTON.
When you write: `self(idx + 1)`
-> The computer literally FREEZES the current function on that exact line.
-> It puts the frozen function into a box (The Call Stack).
-> It spawns a brand new, fresh function for `idx + 1`.
-> The frozen function WILL NOT UNPAUSE until the child function hits
   a base case and dies.

2️⃣ TREE ARCHITECTURE (Level by Level)
---------------------------------------------------------------------------
Every recursive tree has two directions:
↓ VERTICAL (The Levels)   : Controlled by `idx`. Going deeper means moving
                            forward in the array.
→ HORIZONTAL (The Branches): Controlled by CHOICES. At every `idx`, you
                             split into branches (Take vs. Not Take).

3️⃣ THE ART OF BACKTRACKING (Why do we pop?)
---------------------------------------------------------------------------
Since we use ONE global array to store our subset (e.g., `current`),
we must clean up after ourselves.
1. We push `arr[idx]` (Take).
2. We pause and let the child explore everything.
3. The child finishes. We unpause.
4. We MUST pop `arr[idx]` off! Why? So that when we move to the next line
   (Choice 2: Not Take), the array is exactly how it was before we started!


===========================================================================
  🗺️ FAMOUS EXAMPLE 1: Standard Subsets (No Duplicates)
  Array: {1, 2, 3}
===========================================================================
Let's watch the stack simulate step-by-step.
State tracked: [Current Subset] idx
/*       Dry Run: arr = {1, 2, 3}
 *       Build Recursive Tree (Pick / Don't Pick):
 *
 Level 0 (idx=0)                                   [ ] start (empty subset)
										       /         \
									      Take 1          Skip 1
									     /                      \
Level 1 (idx=1)                    [ 1 ]                           [ ]
							    /       \                        /     \
						 Take 2       Skip 2                Take 2      Skip 2
						/               \                  /               \
Level 2 (idx=2)    [ 1, 2 ]             [ 1 ]          [ 2 ]               [ ]
				   /      \            /     \         /     \            /     \
				 T(3)    S(3)        T(3)   S(3)     T(3)   S(3)        T(3)   S(3)
				/          \         /        \      /        \         /        \
Level 3     [1,2,3]       [1,2]    [1,3]      [1]  [2,3]      [2]     [3]        [ ]
(idx=3)        |            |        |         |     |         |       |          |
			 ✅ ANS       ✅ ANS    ✅ ANS    ✅ ANS ✅ ANS    ✅ ANS  ✅ ANS      ✅ ANS
		  (Base Case:   (Base)    (Base)    (Base)(Base)    (Base)  (Base)     (Base)
		   idx == 3)

STACK SIMULATION (Chronological Order - Depth First):
1. Start idx 0. Take '1' -> [1]
2. idx 1. Take '2' -> [1,2]
3. idx 2. Take '3' -> [1,2,3], idx 3 BASE (save)
4. Backtrack pop 3 -> [1,2], Not Take '3' -> idx 3 BASE (save [1,2])
5. Backtrack pop 2 -> [1], Take '3' -> [1,3], idx 3 BASE
6. Backtrack pop 3 -> [1], Not Take '3' -> idx 3 BASE (save [1])
7. Backtrack pop 1 -> [ ], Take '2' -> [2], then explore '3' take/not-take
8. Finally Not Take '2' path gives [3] and [ ] at base.


===========================================================================
  🗺️ FAMOUS EXAMPLE 2: Subsets II (With Duplicates)
  Array: {1, 2, 2} (Must sort first!)
===========================================================================
Rule: If you say "Not Take" to a number, you must skip ALL identical
numbers in that specific branch, otherwise you build twins!
 *      Dry Run: nums = [1, 2, 2] (Indices: 0, 1, 2)
 *      Build Recursive Tree (For-Loop Approach):
 *      Pruning Rule: if (i > idx && nums[i] == nums[i-1]) continue;
 *
 Level 0 (idx=0)                          [ ]  start(empty subset)
								  (Adds [ ] to ans)
						  /                |                 \
					   i = 0             i = 1              i = 2
					  Take 1            Take 2             Take 2
					  /                    |                  \
Level 1          [ 1 ] (idx=1)        [ 2 ] (idx=2)           |
			   (Adds [1] to ans)    (Adds [2] to ans)      ❌ PRUNED!
				  /       \                |             (i > idx (2 > 0)
			   i = 1      i = 2          i = 2          and nums[2]==nums[1])
			  Take 2     Take 2         Take 2                |
			  /             \              |             (Skips duplicate
Level 2   [ 1, 2 ] (idx=2)  |          [ 2, 2 ] (idx=3)   branch entirely!)
	   (Adds [1,2] to ans)  ❌ PRUNED! (Adds [2,2] to ans)
			  |           (i > idx (2 > 1)
			i = 2         and nums[2]==nums[1])
		   Take 2
			  |
Level 3  [ 1, 2, 2 ] (idx=3)
	  (Adds [1,2,2] to ans)

FINAL ANS ARRAY: [[], [1], [1,2], [1,2,2], [2], [2,2]]

-> Notice the MAGIC JUMP (The Pruning Rule):
      When we are at subset [1] (where idx = 1), our for loop looks at the remaining numbers to pick next.
            1. First, the loop tries i = 1 (the first 2). It takes it, goes down the tree, and builds [1, 2].
            2. After backtracking, the loop increments to i = 2 (the second 2).
            3. Now our logic triggers: if (i > idx && nums[i] == nums[i-1]) (Because 2 > 1, and nums[2] == nums[1])
			4. The code hits continue;. We skip calling the recursive function for this duplicate 2 completely! This kills the duplicate [1, 2] branch from ever forming.
   Why this is important: The rule i > idx means "Are we trying to pick a number that is exactly the same as the one we just skipped horizontally?" If yes, continue (jump over it).

===========================================================================
  📐 THE TEMPLATES (Conceptual Blueprints)
===========================================================================

// --- TEMPLATE A: Pure Subsets (No Duplicates) ---
// Use this for Knapsack, Subsets I, and simple combinations.
Function DFS(idx, arr):
    // 1. Base Case
    If idx == arr.size:
        Save current subset
        Return

    // 2. Choice 1: TAKE
    Add arr[idx] to current
    DFS(idx + 1, arr)       // Pause!
    Remove last element     // Backtrack!

    // 3. Choice 2: NOT TAKE
    DFS(idx + 1, arr)       // Pause!


// --- TEMPLATE B: Take / Not-Take (WITH Duplicates) ---
// Sort the array first!
Function DFS(idx, arr):
    // 1. Base Case
    If idx == arr.size:
        Save current subset
        Return

    // 2. Choice 1: TAKE
    Add arr[idx] to current
    DFS(idx + 1, arr)
    Remove last element     // Backtrack!

    // 3. Choice 2: NOT TAKE (The Skip Logic)
    next_idx = idx + 1
    While next_idx < arr.size AND arr[next_idx] == arr[idx]:
        next_idx = next_idx + 1

    DFS(next_idx, arr)      // Jump over all duplicates!


// --- TEMPLATE C: The For-Loop (WITH Duplicates) ---
// The GM favorite for Combinations/Permutations. Creates an N-ary tree.
// Sort the array first!
Function DFS(start_idx, arr):
    // 1. Save every state instantly (Every node is a valid subset!)
    Save current subset

    // 2. Loop through choices horizontally
    For i from start_idx to arr.size - 1:

        // Skip duplicate sibling branches
        If i > start_idx AND arr[i] == arr[i - 1]:
            Continue to next i

        // Take
        Add arr[i] to current
        // Go deeper (Vertical)
        DFS(i + 1, arr)
        // Backtrack
        Remove last element

===========================================================================
  🧠 PART 2: GRANDMASTER COMPLEXITY & COLLECTION RULES
===========================================================================

4️⃣ THE "LEAF NODE" RULE (When do we actually save the answer?)
---------------------------------------------------------------------------
Beginners blindly push to their answer array at the base case. A GM knows
exactly what they are collecting based on the problem type:

Target: ALL SUBSETS (e.g., Power Set)
-> Rule: Every single node in the tree is a valid answer!
-> Action (For-Loop Template): Save the subset immediately at the top of
   the function BEFORE the loop.
-> Action (Take/Not Take): Save only at the final base case (idx == n),
   because that represents a completed path.

Target: EXACT LENGTH / COMBINATIONS (e.g., Target Sum, K-length subsets)
-> Rule: The intermediate nodes are garbage. We ONLY care about the leaves!
-> Action: You MUST use a strict condition at the base case.
   Example:
   if (idx == arr.size()) {
       if (current.size() == k) res.push_back(current);
       return;
   }


5️⃣ COMPLEXITY CHEAT SHEET (The Math)
---------------------------------------------------------------------------
Never guess the complexity. Memorize these bounds:

▶ PURE SUBSETS (Take / Not Take)
- Time Complexity: O(2^n)
  Why? At every index, you branch 2 ways. A tree of depth n has 2^n leaves.
  (If copying arrays to a result list, it becomes O(n * 2^n)).
- Space Complexity: O(n)
  Why? The recursion stack only pauses n times. It never goes deeper
  than the length of the array.

▶ SUBSETS II (Sort and Skip Duplicates)
- Time Complexity: O(2^n) in the worst case (if all elements are unique).
  In reality, it is much faster because duplicate branches are killed O(1).
- Space Complexity: O(n) for the recursion stack + O(log n) for sorting.

▶ COMBINATIONS (Choose k from n)
- Time Complexity: O(nCr) or O(C(n, k))
  Why? You aggressively prune dead ends, so the tree only explores paths
  that actually lead to a valid k-length combination.
- Space Complexity: O(k)
  Because you stop diving once your subset reaches size k.

===========================================================================
*/
