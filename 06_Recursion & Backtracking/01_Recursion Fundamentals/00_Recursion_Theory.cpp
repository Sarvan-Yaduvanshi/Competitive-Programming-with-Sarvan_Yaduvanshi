/*
╔══════════════════════════════════════════════════════════════════════════════╗
║          LEVEL 1: RECURSION FUNDAMENTALS — ZERO TO GRANDMASTER               ║
║          Complete Theory + Deep Insight Edition                              ║
║          By Sarvan Yaduvanshi                                                ║
╚══════════════════════════════════════════════════════════════════════════════╝

    INDEX:
    ──────
    §1  WHAT IS RECURSION?
    §2  THE 3 PILLARS OF RECURSION
    §3  HOW RECURSION WORKS — THE CALL STACK
    §4  THE TWO PHASES — CORE INSIGHT (★ Most Important)
    §5  PRE-ORDER vs POST-ORDER WORK
    §6  EXAMPLES WITH FULL DRY RUN TREES
    §7  RECURSION vs ITERATION
    §8  COMMON MISTAKES
    §9  TIME & SPACE COMPLEXITY
    §10 RECURRENCE RELATIONS
    §11 RECURSION TEMPLATE (Generic)

══════════════════════════════════════════════════════════════════════════════
§1  📖 WHAT IS RECURSION?
══════════════════════════════════════════════════════════════════════════════

    Recursion = A function that calls ITSELF to solve a smaller version
                of the same problem.

    One final powerful line:
    --->  Recursion = Stack simulation + smaller subproblem

    Think of it like Russian dolls 🪆:
        - Open a doll → there's a smaller doll inside
        - Keep opening → eventually you reach the smallest doll (BASE CASE)
        - Then you close them back up (RETURNING from recursive calls)

══════════════════════════════════════════════════════════════════════════════
§2  🧠 THE 3 PILLARS OF RECURSION
══════════════════════════════════════════════════════════════════════════════

    1. BASE CASE (When to stop)
       - Without this → infinite recursion → stack overflow → crash
       - The simplest case you can answer directly

    2. RECURSIVE CASE (How to break down)
       - Call the SAME function with a SMALLER input
       - Must make PROGRESS toward the base case

    3. TRUST / FAITH (The Leap of Faith)
       - ASSUME the recursive call gives the correct answer
       - Just handle: what does THIS level do?

══════════════════════════════════════════════════════════════════════════════
§3  📊 HOW RECURSION WORKS — THE CALL STACK
══════════════════════════════════════════════════════════════════════════════

    When you call factorial(4):

        Call Stack (LIFO — Last In First Out):

        ┌──────────────────────┐
        │  factorial(1) = 1    │  ← BASE CASE (returns 1)
        ├──────────────────────┤
        │  factorial(2) = 2×1  │  ← returns 2
        ├──────────────────────┤
        │  factorial(3) = 3×2  │  ← returns 6
        ├──────────────────────┤
        │  factorial(4) = 4×6  │  ← returns 24   (FIRST CALLED, LAST RESOLVED)
        └──────────────────────┘

        Answer: 24

    Key insight about the stack:
        ↓  Each recursive call PUSHES a new frame onto the stack
        ↑  Each return POPS a frame off the stack
        ↩  The base case is the TURNING POINT — first to return

══════════════════════════════════════════════════════════════════════════════
§4  ★ THE TWO PHASES — MOST IMPORTANT CONCEPT ★
══════════════════════════════════════════════════════════════════════════════

    Recursion is NOT just "calling itself."
    Recursion is a ROUND TRIP with two distinct phases:

        Phase 1 ↓  GOING DOWN   → call stack BUILDS   (forward journey)
        Phase 2 ↑  COMING BACK  → call stack UNWINDS  (return journey)

    The MENTAL MODEL:

              [Call 1: i=1]           ← journey starts HERE
                   ↓  ↑
              [Call 2: i=2]
                   ↓  ↑
              [Call 3: i=3]
                   ↓  ↑
              [Call 4: i=4]
                   ↓  ↑
              [Call 5: i=5]
                   ↓  ↑
              [Base case: i=6]        ← TURN AROUND ↩ (first to RETURN)
                  returns

    The SECRET weapon hidden inside this:

    ┌────────────────────────────────────────────────────────────────────┐
    │  Code BEFORE the recursive call  →  runs on the way DOWN  ↓        │
    │  Code AFTER  the recursive call  →  runs on the way UP    ↑        │
    └────────────────────────────────────────────────────────────────────┘

    🔑 ONE-LINE MEMORY TRICK:
        👉  "Before call  =  FORWARD  output  (pre-order)"
        👉  "After  call  =  REVERSE  output  (post-order)"

══════════════════════════════════════════════════════════════════════════════
§5  📐 PRE-ORDER vs POST-ORDER WORK
══════════════════════════════════════════════════════════════════════════════

    ────────────────────────────────────────────────────────────────────
    PRE-ORDER WORK
    ────────────────────────────────────────────────────────────────────
    ➤ Any code written BEFORE the recursive call
    ➤ Executes on the WAY DOWN ↓ (call stack building phase)
    ➤ Processes parent BEFORE children
    ➤ Produces FORWARD / INCREASING / NATURAL ORDER output

        void func(int i, int n) {
            if (i > n) return;           // base case

            doWork(i);                   // ★ PRE-ORDER WORK ★
                                         //   (runs going DOWN ↓)
            func(i + 1, n);              // recursive call
        }

    ────────────────────────────────────────────────────────────────────
    POST-ORDER WORK
    ────────────────────────────────────────────────────────────────────
    ➤ Any code written AFTER the recursive call
    ➤ Executes on the WAY BACK UP ↑ (call stack unwinding phase)
    ➤ Processes parent AFTER children
    ➤ Produces REVERSE / DECREASING output
    ➤ FREE REVERSAL — no extra array, no extra loop needed! 🆓

        void func(int i, int n) {
            if (i > n) return;           // base case

            func(i + 1, n);              // recursive call

            doWork(i);                   // ★ POST-ORDER WORK ★
                                         //   (runs coming BACK UP ↑)
        }

    ────────────────────────────────────────────────────────────────────
    BOTH PRE + POST IN THE SAME FUNCTION (Powerful!)
    ────────────────────────────────────────────────────────────────────

        void func(int i, int n) {
            if (i > n) return;

            printf("↓ Going down:  %d\n", i);   // PRE-ORDER
            func(i + 1, n);
            printf("↑ Coming back: %d\n", i);   // POST-ORDER
        }

        Output for func(1, 3):
            ↓ Going down:  1
            ↓ Going down:  2
            ↓ Going down:  3
            ↑ Coming back: 3
            ↑ Coming back: 2
            ↑ Coming back: 1

    ╔══════════════════════════════╦══════════════════════════════╗
    ║      PRE-ORDER WORK          ║      POST-ORDER WORK         ║
    ╠══════════════════════════════╬══════════════════════════════╣
    ║ Code BEFORE recursive call   ║ Code AFTER recursive call    ║
    ║ Runs on the way DOWN ↓       ║ Runs on the way UP ↑         ║
    ║ Stack BUILDING phase         ║ Stack UNWINDING phase        ║
    ║ First call executes FIRST    ║ First call executes LAST     ║
    ║ Last call executes LAST      ║ Last call executes FIRST     ║
    ║ Output: FORWARD order        ║ Output: REVERSE order        ║
    ║ Example: print 1 → N         ║ Example: print N → 1         ║
    ╚══════════════════════════════╩══════════════════════════════╝

══════════════════════════════════════════════════════════════════════════════
§6  🔥 EXAMPLES WITH FULL DRY RUN TREES
══════════════════════════════════════════════════════════════════════════════

    ══════════════════════════════════════════════════════════════════════
    EXAMPLE 1 — INCREASING ORDER  (Pre-Order Work)
    Print 1 to N,  N = 5
    ══════════════════════════════════════════════════════════════════════

    CODE:
        void printIncreasing(int i, int n) {
            if (i > n) return;            // BASE CASE

            printf("%d ", i);             // ★ PRE-ORDER WORK ★
                                          //   (BEFORE the recursive call)
            printIncreasing(i + 1, n);    // recursive call
        }
        // Invoke: printIncreasing(1, 5)

    ──────────────────────────────────────────────────────────────────────
    🌲 CALL TREE DRY RUN
    ──────────────────────────────────────────────────────────────────────

        printIncreasing(1, 5)
        │
        ├─ prints 1        ← ★ PRE-ORDER (runs NOW, before going deeper)
        │
        └──→ printIncreasing(2, 5)
             │
             ├─ prints 2   ← ★ PRE-ORDER
             │
             └──→ printIncreasing(3, 5)
                  │
                  ├─ prints 3  ← ★ PRE-ORDER
                  │
                  └──→ printIncreasing(4, 5)
                       │
                       ├─ prints 4  ← ★ PRE-ORDER
                       │
                       └──→ printIncreasing(5, 5)
                            │
                            ├─ prints 5  ← ★ PRE-ORDER
                            │
                            └──→ printIncreasing(6, 5)
                                 │
                                 └─ 6 > 5 → BASE CASE → return ✋
                                 ↑ returns
                            ↑ returns
                       ↑ returns
                  ↑ returns
             ↑ returns
        ↑ returns

    ──────────────────────────────────────────────────────────────────────
    📊 STACK TRACE
    ──────────────────────────────────────────────────────────────────────

        ┌────────────────────────────┐
        │  printIncreasing(6, 5)     │ → 6 > 5, BASE CASE, immediate return
        ├────────────────────────────┤
        │  printIncreasing(5, 5)     │ → prints 5, then calls (6,5)
        ├────────────────────────────┤
        │  printIncreasing(4, 5)     │ → prints 4, then calls (5,5)
        ├────────────────────────────┤
        │  printIncreasing(3, 5)     │ → prints 3, then calls (4,5)
        ├────────────────────────────┤
        │  printIncreasing(2, 5)     │ → prints 2, then calls (3,5)
        ├────────────────────────────┤
        │  printIncreasing(1, 5)     │ → prints 1, then calls (2,5)  ← FIRST CALLED
        └────────────────────────────┘

    ✅  OUTPUT:  1  2  3  4  5

    WHY?
        → We print BEFORE going deeper.
        → Each level prints ITS value on the WAY DOWN.
        → First call (i=1) prints first → forward order naturally.

    ══════════════════════════════════════════════════════════════════════
    EXAMPLE 2 — DECREASING ORDER  (Post-Order Work)
    Print N to 1,  N = 5
    ══════════════════════════════════════════════════════════════════════

    CODE:
        void printDecreasing(int i, int n) {
            if (i > n) return;            // BASE CASE

            printDecreasing(i + 1, n);    // recursive call

            printf("%d ", i);             // ★ POST-ORDER WORK ★
                                          //   (AFTER the recursive call)
        }
        // Invoke: printDecreasing(1, 5)

    ──────────────────────────────────────────────────────────────────────
    🌲 CALL TREE DRY RUN
    ──────────────────────────────────────────────────────────────────────

        printDecreasing(1, 5)
        │
        └──→ printDecreasing(2, 5)
             │
             └──→ printDecreasing(3, 5)
                  │
                  └──→ printDecreasing(4, 5)
                       │
                       └──→ printDecreasing(5, 5)
                            │
                            └──→ printDecreasing(6, 5)
                                 │
                                 └─ 6 > 5 → BASE CASE → return ✋
                                 ↑ returns
                            ↑ prints 5   ← ★ POST-ORDER (first to print)
                       ↑ prints 4        ← ★ POST-ORDER
                  ↑ prints 3             ← ★ POST-ORDER
             ↑ prints 2                  ← ★ POST-ORDER
        ↑ prints 1                       ← ★ POST-ORDER (last to print)

    ──────────────────────────────────────────────────────────────────────
    📊 STACK TRACE
    ──────────────────────────────────────────────────────────────────────

        BUILDING ↓ (NO printing during descent — just going deeper):
        ┌────────────────────────────┐
        │  printDecreasing(6, 5)     │ → BASE CASE, immediate return
        ├────────────────────────────┤
        │  printDecreasing(5, 5)     │ → calls (6,5), then prints 5  ← prints 1st
        ├────────────────────────────┤
        │  printDecreasing(4, 5)     │ → calls (5,5), then prints 4  ← prints 2nd
        ├────────────────────────────┤
        │  printDecreasing(3, 5)     │ → calls (4,5), then prints 3  ← prints 3rd
        ├────────────────────────────┤
        │  printDecreasing(2, 5)     │ → calls (3,5), then prints 2  ← prints 4th
        ├────────────────────────────┤
        │  printDecreasing(1, 5)     │ → calls (2,5), then prints 1  ← prints 5th
        └────────────────────────────┘ ← FIRST CALLED, prints LAST

        UNWINDING ↑ (printing fires in reverse order):
            (6,5) returns →
            (5,5) resumes → prints 5
            (4,5) resumes → prints 4
            (3,5) resumes → prints 3
            (2,5) resumes → prints 2
            (1,5) resumes → prints 1

    ✅  OUTPUT:  5  4  3  2  1

    WHY?
        → We print AFTER returning from deeper calls.
        → The deepest call (i=5) is the FIRST to resume after base case.
        → First call (i=1) is the LAST to resume → last to print.
        → This gives FREE REVERSAL — the call stack reverses for us! 🆓

══════════════════════════════════════════════════════════════════════════════
§7  🔥 RECURSION vs ITERATION
══════════════════════════════════════════════════════════════════════════════

    Every recursion CAN be converted to iteration (using an explicit stack).
    But recursion is more NATURAL for:
        - Tree / Graph traversal
        - Divide and Conquer
        - Backtracking (try all possibilities)
        - Dynamic Programming (top-down / memoization)

    ╔═══════════════════════╦═══════════════════════════╗
    ║   RECURSION           ║   ITERATION               ║
    ╠═══════════════════════╬═══════════════════════════╣
    ║ Uses call stack       ║ Uses loop variable        ║
    ║ Can stack overflow    ║ No stack overflow         ║
    ║ More elegant code     ║ Sometimes verbose         ║
    ║ O(n) stack space      ║ O(1) space possible       ║
    ║ FREE reversal (post)  ║ Need extra array/stack    ║
    ╚═══════════════════════╩═══════════════════════════╝

══════════════════════════════════════════════════════════════════════════════
§8  ⚠️ COMMON MISTAKES IN RECURSION
══════════════════════════════════════════════════════════════════════════════

    1. MISSING BASE CASE        → infinite recursion → stack overflow
    2. WRONG BASE CASE          → wrong answer or infinite loop
    3. NOT MAKING PROGRESS      → f(n) calls f(n) instead of f(n-1)
    4. WRONG RETURN VALUE       → forgetting to return the result
    5. CONFUSING PRE vs POST    → printing before/after call gives opposite outputs
    6. GLOBAL STATE NOT UNDONE  → must undo changes in backtracking problems

══════════════════════════════════════════════════════════════════════════════
§9  🎯 TIME & SPACE COMPLEXITY OF RECURSION
══════════════════════════════════════════════════════════════════════════════

    TIME:  Count total number of recursive calls made
           - Linear recursion (1 call/level): O(n)
           - Binary recursion (Fibonacci naive): O(2^n)
           - Branching factor b, depth d: O(b^d)

    SPACE: Depth of recursion tree = max call stack depth
           - Linear recursion: O(n)
           - Divide & Conquer (balanced): O(log n)
           - Plus any auxiliary space per call

══════════════════════════════════════════════════════════════════════════════
§10 📐 RECURRENCE RELATIONS
══════════════════════════════════════════════════════════════════════════════

    Every recursive function defines a recurrence:

        factorial(n) = n * factorial(n-1)       → T(n) = T(n-1) + O(1)   → O(n)
        fib(n) = fib(n-1) + fib(n-2)           → T(n) = T(n-1) + T(n-2) → O(2^n)
        mergeSort(n) = 2*mergeSort(n/2) + O(n)  → T(n) = 2T(n/2) + O(n)  → O(n log n)

    Master Theorem for T(n) = aT(n/b) + O(n^d):
        - If d < log_b(a)  →  O(n^(log_b(a)))
        - If d = log_b(a)  →  O(n^d × log n)
        - If d > log_b(a)  →  O(n^d)

══════════════════════════════════════════════════════════════════════════════
§11 🏗️ RECURSION TEMPLATE (Generic)
══════════════════════════════════════════════════════════════════════════════

    ReturnType solve(parameters) {

        // ── 1. BASE CASE ──────────────────────────────────────────────
        if (base_condition) return base_value;

        // ── 2. PRE-ORDER WORK (optional) ──────────────────────────────
        // Do work that must happen BEFORE going deeper (forward phase)

        // ── 3. RECURSIVE CALL ─────────────────────────────────────────
        ReturnType subResult = solve(smaller_parameters);

        // ── 4. POST-ORDER WORK (optional) ─────────────────────────────
        // Do work that must happen AFTER coming back (reverse phase)

        // ── 5. COMBINE & RETURN ───────────────────────────────────────
        return combine(current_work, subResult);
    }

══════════════════════════════════════════════════════════════════════════════
💎 MASTER REVISION CHECKLIST
══════════════════════════════════════════════════════════════════════════════

    FUNDAMENTALS:
    [ ] Recursion = function calls itself with smaller input
    [ ] 3 Pillars: Base case, Recursive case, Trust/Faith
    [ ] Call stack is LIFO — last called, first resolved

    TWO PHASES:
    [ ] Phase 1 ↓ = going down = stack building   = forward journey
    [ ] Phase 2 ↑ = coming up  = stack unwinding  = return journey
    [ ] Base case = the TURNING POINT of the journey

    PRE / POST ORDER:
    [ ] Pre-order  = code BEFORE call = runs going DOWN  ↓ = forward output
    [ ] Post-order = code AFTER  call = runs coming UP   ↑ = reverse output
    [ ] Both can exist in the SAME function simultaneously
    [ ] Post-order gives FREE REVERSAL without any extra array

    COMPLEXITY:
    [ ] Time  = count total recursive calls
    [ ] Space = depth of recursion tree (call stack depth)
    [ ] Know how to write and solve recurrence relations

══════════════════════════════════════════════════════════════════════════════
*/

// Theory complete. See numbered implementation files for code problems!