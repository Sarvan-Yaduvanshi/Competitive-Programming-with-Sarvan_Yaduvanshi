/*
╔══════════════════════════════════════════════════════════════╗
║        LEVEL 1: RECURSION FUNDAMENTALS — THEORY              ║
║        Zero to Grandmaster Recursion Series                  ║
║        By Sarvan Yaduvanshi                                  ║
╚══════════════════════════════════════════════════════════════╝

════════════════════════════════════════════════════════════════
📖 WHAT IS RECURSION?
════════════════════════════════════════════════════════════════

Recursion = A function that calls ITSELF to solve a smaller version
            of the same problem.

Think of it like Russian dolls 🪆:
    - Open a doll → there's a smaller doll inside
    - Keep opening → eventually you reach the smallest doll (BASE CASE)
    - Then you close them back (RETURNING from recursive calls)

════════════════════════════════════════════════════════════════
🧠 THE 3 PILLARS OF RECURSION
════════════════════════════════════════════════════════════════

1. BASE CASE (When to stop)
   - Without this → infinite recursion → stack overflow → crash
   - The simplest case you can answer directly

2. RECURSIVE CASE (How to break down)
   - Call the SAME function with a SMALLER input
   - Must make progress toward the base case

3. TRUST / FAITH (The Leap of Faith)
   - ASSUME the recursive call gives the correct answer
   - Just handle: what does THIS level do?

════════════════════════════════════════════════════════════════
📊 HOW RECURSION WORKS — THE CALL STACK
════════════════════════════════════════════════════════════════

When you call factorial(4):

    Call Stack (LIFO — Last In First Out):

    ┌──────────────────┐
    │ factorial(1) = 1  │  ← BASE CASE (returns 1)
    ├──────────────────┤
    │ factorial(2) = 2*1│  ← returns 2
    ├──────────────────┤
    │ factorial(3) = 3*2│  ← returns 6
    ├──────────────────┤
    │ factorial(4) = 4*6│  ← returns 24
    └──────────────────┘

    Answer: 24

════════════════════════════════════════════════════════════════
🔥 RECURSION vs ITERATION
════════════════════════════════════════════════════════════════

Every recursion CAN be converted to iteration (using explicit stack).
But recursion is more NATURAL for:
    - Tree/Graph traversal
    - Divide and Conquer
    - Backtracking (try all possibilities)
    - Dynamic Programming (top-down)

╔═══════════════════╦═══════════════════════╗
║   RECURSION       ║    ITERATION          ║
╠═══════════════════╬═══════════════════════╣
║ Uses call stack   ║ Uses loop variable    ║
║ Can stackoverflow ║ No stack overflow     ║
║ More elegant code ║ Sometimes verbose     ║
║ O(n) stack space  ║ O(1) space possible   ║
╚═══════════════════╩═══════════════════════╝

════════════════════════════════════════════════════════════════
⚠️ COMMON MISTAKES IN RECURSION
════════════════════════════════════════════════════════════════

1. MISSING BASE CASE → infinite recursion
2. BASE CASE WRONG → wrong answer or infinite loop
3. NOT MAKING PROGRESS → f(n) calls f(n) instead of f(n-1)
4. WRONG RETURN VALUE → forgetting to return
5. MODIFYING GLOBAL STATE without undoing (backtracking)

════════════════════════════════════════════════════════════════
🎯 TIME & SPACE COMPLEXITY OF RECURSION
════════════════════════════════════════════════════════════════

TIME:  Count how many recursive calls are made total
       - Linear recursion: O(n)
       - Binary recursion (fibonacci naive): O(2^n)
       - Branching factor b, depth d: O(b^d)

SPACE: Depth of recursion tree = max call stack depth
       - Linear recursion: O(n)
       - Divide & conquer (balanced): O(log n)
       - Plus any auxiliary space per call

════════════════════════════════════════════════════════════════
📐 RECURRENCE RELATIONS
════════════════════════════════════════════════════════════════

Every recursive function defines a recurrence:

    factorial(n) = n * factorial(n-1)     → T(n) = T(n-1) + O(1) → O(n)
    fib(n) = fib(n-1) + fib(n-2)         → T(n) = T(n-1) + T(n-2) → O(2^n)
    mergeSort(n) = 2*mergeSort(n/2) + O(n) → T(n) = 2T(n/2) + O(n) → O(n log n)

Master Theorem for T(n) = aT(n/b) + O(n^d):
    - If d < log_b(a): O(n^(log_b(a)))
    - If d = log_b(a): O(n^d * log n)
    - If d > log_b(a): O(n^d)

════════════════════════════════════════════════════════════════
🏗️ RECURSION TEMPLATE (Generic)
════════════════════════════════════════════════════════════════

    ReturnType solve(parameters) {
        // 1. BASE CASE
        if (base_condition) return base_value;

        // 2. RECURSIVE CASE
        // - Do some work at current level
        // - Make recursive call(s) with smaller input
        // - Combine results

        ReturnType subResult = solve(smaller_parameters);
        return combine(current_work, subResult);
    }

════════════════════════════════════════════════════════════════
*/

// This file is theory-only. See the numbered files for implementations!

