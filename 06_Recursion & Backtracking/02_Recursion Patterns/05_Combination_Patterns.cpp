/*
               ╔══════════════════════════════════════════════════════════════════════╗
               ║  05. COMBINATION — Theory + Approach (Recursion & Backtracking)      ║
               ║  Level: Zero → Grandmaster | Topic: Combination                      ║
               ╚══════════════════════════════════════════════════════════════════════╝

════════════════════════════════════════════════════════════════════════
SECTION 1 — WHAT IS COMBINATION?
════════════════════════════════════════════════════════════════════════

Combination = selection of items from a set where ORDER DOES NOT MATTER.

    {1,2,3} -> [1,2] and [2,1] are SAME combination.
    (This is what separates it from Permutation, where order matters.)

FORMULA — choosing k items from n items:

    nCk = n! / (k! * (n-k)!)

EXAMPLE: n = 3 {1,2,3}, k = 2

    3C2 = 3! / (2! * 1!) = 6/2 = 3

    Valid combinations: [1,2], [1,3], [2,3]
    NOT counted again : [2,1], [3,1], [3,2]  (same as above, order ignored)

WHY RECURSION FITS HERE:
    Combination = repeatedly deciding, for each element,
    "do I PICK it or SKIP it?" -> this decision tree IS recursion.
    Backtracking = after exploring a PICK, UNDO it (pop) and try SKIP,
    so we can reuse the same path/array for every branch.


════════════════════════════════════════════════════════════════════════
SECTION 2 — CORE APPROACH: "TAKE / NOT-TAKE" (Pick / Not-Pick)
════════════════════════════════════════════════════════════════════════

Every combination problem reduces to this skeleton DECISION at each index:

    function(index, current_path, remaining_target):
        base case -> if index reaches end (or target satisfied/violated):
                         store/reject current_path, return

        BRANCH 1 (TAKE)   : add arr[index] to path -> recurse (index+1 or same index)
        BRANCH 2 (NOT-TAKE): recurse without adding -> index+1
        BACKTRACK          : remove arr[index] from path before returning
                              (undo the choice so next branch starts clean)

Two flavors of "index movement" after TAKE:
    - index+1  -> element can be used ONLY ONCE   (Combination Sum II, III, Subsets)
    - index    -> element can be REUSED            (Combination Sum I - unlimited supply)

This single fact (does index move or stay after taking) is what
separates "with repetition" vs "without repetition" problems.


════════════════════════════════════════════════════════════════════════
SECTION 3 — PROBLEM FAMILY OVERVIEW
════════════════════════════════════════════════════════════════════════

🎯 Problems covered:
   1. Subsets            — LC 78  (all subsets, distinct elements)
   2. Subsets II          — LC 90  (subsets, input has duplicates)
   3. Combinations         — LC 77  (choose k from 1..n)
   4. Combination Sum I    — LC 39  (unlimited reuse, distinct elements)
   5. Combination Sum II   — LC 40  (each used once, may have duplicates)
   6. Combination Sum III  — LC 216 (exactly k numbers, digits 1-9, sum = n)

┌────────────────┬────────────────┬──────────────────┬──────────────────────┐
│ Problem        │ Reuse element? │ Input has dups?  │ Avoid dup results?   │
├────────────────┼────────────────┼──────────────────┼──────────────────────┤
│ Subsets        │ NO             │ NO               │ NO                   │
│ Subsets II     │ NO             │ YES              │ YES (sort + skip)    │
│ Combinations   │ NO             │ NO               │ NO                   │
│ Comb Sum I     │ YES            │ NO               │ NO                   │
│ Comb Sum II    │ NO             │ YES              │ YES (sort + skip)    │
│ Comb Sum III   │ NO             │ NO (1-9 fixed)   │ NO                   │
└────────────────┴────────────────┴──────────────────┴──────────────────────┘


════════════════════════════════════════════════════════════════════════
SECTION 4 — HANDLING DUPLICATES (universal trick)
════════════════════════════════════════════════════════════════════════

1. SORT the array first.
2. In the "NOT-TAKE" / loop branch, SKIP all consecutive duplicates:

       while (index+1 < n && arr[index] == arr[index+1]) index++;

   Why this works: sorting groups equal values together. When we
   decide to SKIP a value at some position, we must skip ALL its
   duplicates too — otherwise skipping value=5 at index 2 and then
   "trying again" at index 3 (also 5) produces the exact same branch
   twice -> duplicate result sets.

   Rule of thumb: duplicates only cause repeated OUTPUT when the SAME
   value is skipped more than once at the SAME recursion depth.
   Taking duplicates is fine (that's a different depth/path).


════════════════════════════════════════════════════════════════════════
SECTION 5 — PROBLEM 1: SUBSETS (LC 78)
════════════════════════════════════════════════════════════════════════

Statement: array of DISTINCT integers -> return ALL possible subsets
(the power set). Order doesn't matter, no duplicates in input.

APPROACH (Take/Not-Take, index+1 either way since no reuse):
    solve(index, path):
        if index == n:
            store path (every path is a valid subset, no target to check)
            return
        // NOT-TAKE
        solve(index+1, path)
        // TAKE
        path.push(arr[index])
        solve(index+1, path)
        path.pop()               <-- backtrack

    Key insight: EVERY node in the recursion tree (not just leaves)
    is a valid subset. That's why subset count = 2^n (each element:
    in or out, independently).

DRY RUN TREE for arr = [1,2,3]:

                                   solve(0, [])
                        NOT-TAKE 1 /            \ TAKE 1
                     solve(1,[])                solve(1,[1])
                  NT2/      \T2                NT2/      \T2
            solve(2,[])   solve(2,[2])   solve(2,[1])   solve(2,[1,2])
             NT3/\T3        NT3/\T3        NT3/\T3         NT3/\T3
             []  [3]       [2] [2,3]      [1] [1,3]      [1,2] [1,2,3]

    Leaves (8 = 2^3) = all subsets:
    [], [3], [2], [2,3], [1], [1,3], [1,2], [1,2,3]

    Complexity: Time O(2^n * n) [2^n nodes, O(n) to copy each path]
                Space O(n) recursion depth + O(2^n * n) output storage


════════════════════════════════════════════════════════════════════════
SECTION 6 — PROBLEM 2: SUBSETS II (LC 90)
════════════════════════════════════════════════════════════════════════

Statement: array MAY contain duplicates -> return all UNIQUE subsets.

APPROACH (loop-based take, cleaner for duplicate-skipping):
    1. SORT array.
    2. solve(index, path):
           store path (every node is valid, like Subsets)
           for i = index to n-1:
               if i > index AND arr[i] == arr[i-1]: continue   <-- skip dup
               path.push(arr[i])
               solve(i+1, path)
               path.pop()                                      <-- backtrack

    Why "i > index" guard: the FIRST occurrence of a value at this
    depth is always allowed (that's a genuine new branch); only
    the REPEATS right after it (at the same loop level) get skipped.

DRY RUN for arr = [1,2,2] (sorted already):

    solve(0, [])  -> store []
      i=0 take 1 -> path=[1] -> store [1]
          i=1 take 2 -> path=[1,2] -> store [1,2]
              i=2 take 2 -> path=[1,2,2] -> store [1,2,2]
          i=2 (arr[2]==arr[1], i>index) -> SKIP
      i=1 take 2 -> path=[2] -> store [2]
          i=2 take 2 -> path=[2,2] -> store [2,2]
      i=2 (arr[2]==arr[1], i>index) -> SKIP   <-- prevents duplicate [2] again

    Unique subsets: [], [1], [1,2], [1,2,2], [2], [2,2]   (6 total, not 8)


════════════════════════════════════════════════════════════════════════
SECTION 7 — PROBLEM 3: COMBINATIONS (LC 77)
════════════════════════════════════════════════════════════════════════

Statement: given n, k -> return all combinations of k numbers chosen
from range [1, n]. Pure application of nCk formula's combinations.

APPROACH:
    solve(start, path):
        if path.size() == k:
            store path
            return
        for i = start to n:
            // PRUNING: if remaining numbers (n - i + 1) < numbers
            // still needed (k - path.size()), no point continuing
            if (n - i + 1) < (k - path.size()): break
            path.push(i)
            solve(i+1, path)
            path.pop()               <-- backtrack

    Key insight: "start" parameter (not 0) enforces order i < j < k...
    inside path, automatically avoiding [1,2] AND [2,1] both appearing.
    That's literally what makes it a COMBINATION and not a PERMUTATION.

DRY RUN for n=4, k=2:

    solve(1, [])
      take 1 -> [1]
        take 2 -> [1,2] STORE
        take 3 -> [1,3] STORE
        take 4 -> [1,4] STORE
      take 2 -> [2]
        take 3 -> [2,3] STORE
        take 4 -> [2,4] STORE
      take 3 -> [3]
        take 4 -> [3,4] STORE
      take 4 -> [4]  (no numbers left, k not reached, pruned by loop bound)

    Result: [1,2] [1,3] [1,4] [2,3] [2,4] [3,4]  -> matches 4C2 = 6 ✓

FULL RECURSION TREE (branch-style) for n=4, k=2:
(each node label = path so far; loop "for i=start..n" fans OUT
 multiple children per node, NOT just binary take/not-take)

                              solve(1, [])
                 ┌────────────────┼────────────────┬───────────────┐
              i=1│              i=2│             i=3│            i=4│
             [1]              [2]              [3]             [4]
          ┌───┼───┐         ┌───┴───┐            │            (empty
       i=2│ i=3│ i=4│    i=3│    i=4│         i=4│             range,
       [1,2] [1,3] [1,4]  [2,3]  [2,4]        [3,4]            size<k,
        STORE STORE STORE  STORE  STORE       STORE            no child)

    Leaves = 6 nodes, each a stored answer -> matches 4C2 = 6 ✓
    Branch count shrinks each level because loop starts at i+1
    (never revisits earlier numbers) -> this fan-out shrink is the
    "start" parameter doing its job (order i<j enforced automatically).

TIME COMPLEXITY:
    Total valid leaves = nCk (by definition of combinations).
    Each leaf/path takes O(k) to copy into the answer list.
    Internal (non-leaf) nodes are bounded by a similar combinatorial
    count, so overall:
        Time = O(k * nCk)
    (nCk = n!/(k!(n-k)!) ; the k factor = cost of copying each path)

SPACE COMPLEXITY:
    Recursion depth = at most k (path fills up to size k, then returns).
        Auxiliary/recursion stack space = O(k)
    Output storage (all combinations) = O(k * nCk)   [not counted as
    "extra" space in most conventions since it's the required output]


════════════════════════════════════════════════════════════════════════
SECTION 8 — PROBLEM 4: COMBINATION SUM I (LC 39)
════════════════════════════════════════════════════════════════════════

Statement: distinct integers, target sum. Each number may be used
UNLIMITED times. Return all unique combinations summing to target.

APPROACH (index does NOT advance on TAKE -> allows reuse):
    solve(index, path, remaining):
        if remaining == 0: store path; return
        if remaining < 0 OR index == n: return     <-- base/prune

        // TAKE (stay at same index -> reuse allowed)
        path.push(arr[index])
        solve(index, path, remaining - arr[index])
        path.pop()                                  <-- backtrack

        // NOT-TAKE (move to next index -> never use arr[index] again)
        solve(index+1, path, remaining)

    Key insight: this is the ONLY problem in the family where the
    TAKE branch does not increment index — that single line is what
    grants "unlimited reuse".

DRY RUN for arr=[2,3], target=5:

    solve(0, [], 5)
      TAKE 2 -> path=[2], remaining=3
        TAKE 2 -> path=[2,2], remaining=1
          TAKE 2 -> remaining=-1 -> PRUNE, backtrack
          NOT-TAKE(idx1) -> path=[2,2], remaining=1, arr[1]=3>1 eventually prune
        NOT-TAKE(idx1) -> path=[2], remaining=3
          TAKE 3 -> path=[2,3], remaining=0 -> STORE [2,3]
          NOT-TAKE(idx2) -> index==n -> return
      NOT-TAKE(idx1) -> path=[], remaining=5
        TAKE 3 -> path=[3], remaining=2
          TAKE 3 -> remaining=-1 -> PRUNE
          NOT-TAKE -> index==n -> return
        NOT-TAKE -> index==n -> return

    Result: [[2,3]]

FULL RECURSION TREE (binary take/not-take style) for arr=[2,3], target=5:
(T = TAKE current index [stays same idx], N = NOT-TAKE [moves idx+1])
(node label = (index, path, remaining))

                                  (0, [], 5)
                        T2 /                    \ N
                (0,[2],3)                      (1, [], 5)
              T2/      \N                    T3/         \N
        (0,[2,2],1)  (1,[2],3)          (1,[3],2)      (2,[],5)
          T2/  \N      T3/  \N            T3/ \N        idx==n
    (0,..,-1) (1,[2],3) (1,[2,3],0) (2,[2],3)  (2,[3],2) (2,[3],2) return
     PRUNE     idx==n    ★STORE      idx==n     idx==n     idx==n
    (remaining  return   [2,3]        return     return     return
     <0)                (target=0)

    ★ Only [2,3] survives all prune/base checks -> Result = [[2,3]]
    Notice: PRUNE happens the instant remaining<0 (no need to reach
    a "full" leaf) -> this early cutoff is what keeps runtime sane.

TIME COMPLEXITY:
    Branching factor = 2 (TAKE / NOT-TAKE) at every node.
    Max recursion depth on the "keep taking smallest element" path
    ≈ target / min(arr)   (worst case: smallest element repeatedly).
    Worst-case tree size (before pruning) ~ O(2^(target/min(arr))).
    Standard accepted bound (CLRS-style, ignoring tight pruning):
        Time = O(2^target)            [loose upper bound]
        Tighter practical bound = O(2^(target/min_element) * k)
        (k = avg length of a valid combination, for the copy cost)

SPACE COMPLEXITY:
    Recursion stack depth = O(target / min(arr))
        (deepest path = repeatedly picking the smallest element
         until remaining hits 0 or goes negative)
    Output storage = O(k * count_of_valid_combinations)


════════════════════════════════════════════════════════════════════════
SECTION 9 — PROBLEM 5: COMBINATION SUM II (LC 40)
════════════════════════════════════════════════════════════════════════

Statement: array MAY have duplicates, each element used AT MOST ONCE,
find all unique combinations summing to target.

APPROACH (sort + loop + skip-duplicate + index+1 = no reuse):
    1. SORT array.
    2. solve(index, path, remaining):
           if remaining == 0: store path; return
           for i = index to n-1:
               if arr[i] > remaining: break            <-- prune (sorted!)
               if i > index AND arr[i] == arr[i-1]: continue  <-- skip dup
               path.push(arr[i])
               solve(i+1, path, remaining - arr[i])     <-- i+1 = no reuse
               path.pop()                                <-- backtrack

    Combines BOTH tricks: duplicate-skip (Section 4) + no-reuse (i+1).

DRY RUN for arr=[1,1,2] (sorted), target=3:

    solve(0, [], 3)
      i=0 take 1 -> path=[1], remaining=2
          i=1 take 1 -> path=[1,1], remaining=1
              i=2 take 2 -> path=[1,1,2]... wait remaining=1, arr[2]=2>1 -> break
              (no store here, remaining never hits exactly 0 this branch... )
          i=2 take 2 -> path=[1,2], remaining=0 -> STORE [1,2]
      i=1 (arr[1]==arr[0], i>index) -> SKIP  <-- prevents duplicate [1,2] again
      i=2 take 2 -> path=[2], remaining=1 -> no i left -> nothing stored

    Result: [[1,2]]   (only ONE [1,2], duplicate branch correctly skipped)


════════════════════════════════════════════════════════════════════════
SECTION 10 — PROBLEM 6: COMBINATION SUM III (LC 216)
════════════════════════════════════════════════════════════════════════

Statement: find all combinations of EXACTLY k numbers, using digits
1-9 ONLY ONCE each, that sum to n.

APPROACH (fixed universe 1-9, need BOTH count==k AND sum==n):
    solve(start, path, remaining):
        if path.size() == k:
            if remaining == 0: store path
            return                                      <-- either way, stop
        for i = start to 9:
            if i > remaining: break            <-- prune (digits ascending)
            path.push(i)
            solve(i+1, path, remaining - i)     <-- i+1 = each digit once
            path.pop()                          <-- backtrack

    Key insight: TWO simultaneous stopping conditions (size==k AND
    sum==0) — this is "Combinations" (Section 7) + "Combination Sum I"
    (Section 8) merged into one, but digits fixed 1-9 and no reuse.

DRY RUN for k=3, n=7:

    solve(1, [], 7)
      take 1 -> [1], remaining=6
        take 2 -> [1,2], remaining=4
          take 3 -> [1,2,3]... size=3 but remaining=1 != 0 -> NOT stored
          take 4 -> [1,2,4], size=3, remaining=0 -> STORE [1,2,4]
        take 3 -> [1,3], remaining=3
          take 4 -> [1,3,4], size=3, remaining=-1... wait remaining=3-4<0
             actually check: i>remaining prune -> 4>3 -> break before this
        take 4 -> [1,4], remaining=2 -> next i must be <=2, i=... limited
      take 2 -> [2], remaining=5
        take 3 -> [2,3], remaining=2 -> next digit must be <=2 but >3, none
        take 4 -> [2,4], remaining=1 -> STORE? size=2 continue... no digit=1 left(<5) skip since <start
      ... (tree continues similarly)

    Result includes: [1,2,4]  (verify: 1+2+4=7, size=3 ✓)
    Full answer set for k=3,n=7: [[1,2,4]]


════════════════════════════════════════════════════════════════════════
SECTION 11 — GRANDMASTER SUMMARY (mental checklist before coding)
════════════════════════════════════════════════════════════════════════

Ask these 4 questions for ANY combination problem:

    1. Can I REUSE an element?
           YES -> TAKE branch keeps same index      (Comb Sum I)
           NO  -> TAKE branch moves to index+1       (all others)

    2. Does input have DUPLICATES that could cause duplicate OUTPUT?
           YES -> SORT + skip consecutive dup at SAME depth (Section 4)
           NO  -> no special handling needed

    3. Is there a TARGET/SUM constraint?
           YES -> track "remaining", prune when remaining<0 or
                  arr[i] > remaining (if sorted, break early)
           NO  -> every node (or every leaf) is a valid answer

    4. Is there a FIXED SIZE constraint (exactly k elements)?
           YES -> stop/check only when path.size()==k
           NO  -> check condition at every step (subsets) or at
                  target==0 (unbounded sum problems)

    Always BACKTRACK (pop) after every recursive TAKE call — this is
    non-negotiable; it's what makes the same array/path reusable
    across all sibling branches instead of allocating new memory.

*/


