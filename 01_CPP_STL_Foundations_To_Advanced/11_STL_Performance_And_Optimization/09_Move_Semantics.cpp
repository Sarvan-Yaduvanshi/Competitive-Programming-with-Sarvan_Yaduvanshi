/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           09 — MOVE SEMANTICS — THE COMPLETE GUIDE                         ║
║           From Zero to Grandmaster — Transfer, Don't Copy                  ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. What is Move Semantics? (Lvalue vs Rvalue)
 2. std::move — What It Actually Does (Hint: Nothing!)
 3. Move Constructor and Move Assignment
 4. When the Compiler Moves for You (Automatic!)
 5. When to Use std::move Explicitly
 6. std::swap — Move Under the Hood
 7. Perfect Forwarding (brief)
 8. CP-Relevant Move Patterns

═══════════════════════════════════════════════════════════════════════════════
 LVALUE vs RVALUE
═══════════════════════════════════════════════════════════════════════════════

 LVALUE (Left value):
   Has a NAME and ADDRESS. Lives beyond the expression.
   int x = 5;        // x is an lvalue
   string s = "hi";  // s is an lvalue

 RVALUE (Right value):
   TEMPORARY. No name. Dies at the end of the expression.
   5                  // rvalue (literal)
   x + y              // rvalue (temporary result)
   string("hello")    // rvalue (temporary object)
   move(s)            // converts lvalue to rvalue reference!

 WHY IT MATTERS:
   Copying an lvalue: we MUST copy (the original is still needed)
   "Copying" an rvalue: we can STEAL its guts (it's dying anyway!)

   This "stealing" is MOVE SEMANTICS.

 DRY RUN:
   string s1 = "Hello World";
   // s1 owns: pointer → "Hello World" (heap), size=11, cap=11

   string s2 = s1;  // COPY: allocate new memory, copy 11 chars
   // s1 owns: pointer → "Hello World"
   // s2 owns: pointer → "Hello World" (DIFFERENT memory!)

   string s3 = move(s1);  // MOVE: steal s1's pointer!
   // s3 owns: pointer → "Hello World" (SAME memory as old s1!)
   // s1 owns: pointer → nullptr, size=0 (gutted!)

   Move cost: ~3 pointer copies (pointer, size, capacity)
   Copy cost: allocate memory + copy 11 bytes
   For a 1MB string: move = 24 bytes, copy = 1,000,024 bytes!
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: BASIC MOVE DEMONSTRATION
// ═══════════════════════════════════════════════════════════════

void basicMoveDemo() {
    cout << "═══ BASIC MOVE DEMONSTRATION ═══\n\n";

    // String move
    string s1 = "Hello, Competitive Programming World!";
    cout << "Before move:\n";
    cout << "  s1 = \"" << s1 << "\" (size=" << s1.size() << ")\n";

    string s2 = move(s1);  // MOVE: steal s1's internal buffer
    cout << "\nAfter move:\n";
    cout << "  s2 = \"" << s2 << "\" (size=" << s2.size() << ")\n";
    cout << "  s1 = \"" << s1 << "\" (size=" << s1.size() << ") ← emptied!\n\n";

    // Vector move
    vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << "Before: v1.size()=" << v1.size() << "\n";
    vector<int> v2 = move(v1);
    cout << "After:  v2.size()=" << v2.size() << ", v1.size()=" << v1.size() << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: WHAT std::move ACTUALLY DOES
// ═══════════════════════════════════════════════════════════════
/*
 CRITICAL UNDERSTANDING:
 ───────────────────────
 std::move() does NOT move anything!
 It's just a CAST from lvalue reference to rvalue reference.

 Equivalent to: static_cast<T&&>(x)

 It's the MOVE CONSTRUCTOR that does the actual work:
   string(string&& other) {
       data_ptr = other.data_ptr;   // Steal pointer
       size_ = other.size_;         // Steal size
       other.data_ptr = nullptr;     // Leave source empty
       other.size_ = 0;
   }

 std::move just says: "I don't need this anymore, feel free to steal."
*/

void whatMoveDoes() {
    cout << "═══ WHAT std::move ACTUALLY DOES ═══\n\n";

    cout << "std::move(x) = static_cast<T&&>(x)\n";
    cout << "It's just a CAST — marks x as 'safe to steal from'\n\n";

    cout << "The MOVE CONSTRUCTOR/ASSIGNMENT does the real work:\n";
    cout << "  1. Copy the pointer/handle from source\n";
    cout << "  2. Set source's pointer to nullptr\n";
    cout << "  3. Now destination owns the memory\n\n";

    cout << "Cost comparison:\n";
    cout << "  Copy string (1MB): allocate 1MB + memcpy 1MB   → ~1ms\n";
    cout << "  Move string (1MB): copy 3 pointers (24 bytes)  → ~1ns\n";
    cout << "  Speedup: ~1,000,000x for large strings!\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: BENCHMARK — COPY vs MOVE
// ═══════════════════════════════════════════════════════════════

void benchmarkCopyVsMove() {
    cout << "═══ COPY vs MOVE BENCHMARK ═══\n\n";

    // Large string
    string bigStr(10000000, 'x');  // 10MB string

    // Copy
    {
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < 100; i++) {
            string copy = bigStr;  // COPY 10MB
        }
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "Copy 10MB string × 100: " << ms << " ms\n";
    }

    // Move (need to re-create source each time since move empties it)
    {
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < 100; i++) {
            string src(10000000, 'x');
            string moved = move(src);  // MOVE
        }
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "Create+Move 10MB × 100: " << ms << " ms\n";
        // Note: this also includes creation, so let's test pure move
    }

    // Pure move benchmark
    {
        vector<string> sources(100, string(1000000, 'x'));  // 1MB each
        auto start = chrono::steady_clock::now();
        vector<string> destinations;
        destinations.reserve(100);
        for (auto& s : sources) destinations.push_back(move(s));
        auto us = chrono::duration_cast<chrono::microseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "Pure move 1MB × 100:    " << us << " μs (microseconds!)\n\n";
    }
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: WHEN COMPILER MOVES AUTOMATICALLY
// ═══════════════════════════════════════════════════════════════

void autoMoves() {
    cout << "═══ AUTOMATIC MOVES (Compiler Does It For You) ═══\n\n";

    // Case 1: Returning local variable (NRVO/Move)
    cout << "CASE 1: Return local variable\n";
    cout << "  vector<int> build() { vector<int> v; ...; return v; }\n";
    cout << "  → Compiler applies NRVO or implicit move ✓\n";
    cout << "  → DON'T write: return move(v); (can PREVENT NRVO!)\n\n";

    // Case 2: Temporary passed to function
    cout << "CASE 2: Passing temporary to function\n";
    cout << "  void f(vector<int> v);\n";
    cout << "  f(vector<int>{1,2,3});  → Temporary, auto-moved ✓\n\n";

    // Case 3: Container reallocation
    cout << "CASE 3: vector reallocation\n";
    cout << "  When vector doubles capacity, elements are MOVED not copied\n";
    cout << "  (if move constructor is noexcept)\n\n";

    // Case 4: STL algorithms
    cout << "CASE 4: STL algorithms (sort, remove, etc.)\n";
    cout << "  sort uses move assignments internally ✓\n\n";

    // RULES
    cout << "RULES — When to write std::move explicitly:\n";
    cout << "  ✓ Transfer ownership: container.push_back(move(local_var))\n";
    cout << "  ✓ Swap-like patterns: a = move(b); b = move(c);\n";
    cout << "  ✓ Moving into containers: vec.push_back(move(str));\n";
    cout << "  ✗ DON'T move return values (return v; is already optimal)\n";
    cout << "  ✗ DON'T move const objects (const can't be stolen from)\n";
    cout << "  ✗ DON'T use after move (object is in valid but unspecified state)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: std::swap — MOVE UNDER THE HOOD
// ═══════════════════════════════════════════════════════════════

void swapUnderHood() {
    cout << "═══ std::swap — MOVE UNDER THE HOOD ═══\n\n";

    /*
     Old swap (pre-C++11, COPY-based):
       template<class T>
       void swap(T& a, T& b) {
           T temp = a;   // COPY
           a = b;        // COPY
           b = temp;     // COPY
       }
       → 3 copies of potentially large object!

     Modern swap (MOVE-based):
       template<class T>
       void swap(T& a, T& b) {
           T temp = move(a);   // MOVE (steal a's guts)
           a = move(b);        // MOVE (steal b's guts)
           b = move(temp);     // MOVE (steal temp's guts)
       }
       → 3 moves ≈ 3 pointer swaps ≈ ~24 bytes total!
    */

    vector<int> a(1000000, 1);
    vector<int> b(1000000, 2);

    auto start = chrono::steady_clock::now();
    for (int i = 0; i < 10000; i++) swap(a, b);
    auto us = chrono::duration_cast<chrono::microseconds>(
        chrono::steady_clock::now() - start).count();
    cout << "swap(vector<10^6>) × 10^4: " << us << " μs\n";
    cout << "Each swap moves 3 pointers ≈ 24 bytes regardless of size!\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 6: CP-RELEVANT MOVE PATTERNS
// ═══════════════════════════════════════════════════════════════

void cpMovePatterns() {
    cout << "═══ CP-RELEVANT MOVE PATTERNS ═══\n\n";

    // Pattern 1: Build adjacency list with move
    cout << "Pattern 1: Adjacency list construction\n";
    int n = 5;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        adj[i].push_back(i + 1);
        adj[i + 1].push_back(i);
    }
    // Transfer adjacency list to another structure
    vector<vector<int>> adj2 = move(adj);  // O(1) move of entire 2D vector!
    cout << "  move(adj) → adj2: O(1) regardless of graph size\n";
    cout << "  adj is now empty: size=" << adj.size() << "\n\n";

    // Pattern 2: Moving strings into containers
    cout << "Pattern 2: Move strings into vector\n";
    vector<string> words;
    words.reserve(3);
    string word1 = "competitive";
    string word2 = "programming";
    words.push_back(move(word1));  // Move instead of copy
    words.push_back(move(word2));
    words.emplace_back("mastery");  // Even better: emplace
    cout << "  After move: word1=\"" << word1 << "\", word2=\"" << word2 << "\"\n";
    cout << "  words: "; for (auto& w : words) cout << w << " "; cout << "\n\n";

    // Pattern 3: swap instead of 3-variable rotation
    cout << "Pattern 3: swap for rotation\n";
    int x = 1, y = 2, z = 3;
    cout << "  Before: x=" << x << " y=" << y << " z=" << z << "\n";
    // Rotate x←y←z←x
    int temp = move(x);
    x = move(y);
    y = move(z);
    z = move(temp);
    cout << "  After:  x=" << x << " y=" << y << " z=" << z << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 7: MOVED-FROM STATE
// ═══════════════════════════════════════════════════════════════

void movedFromState() {
    cout << "═══ MOVED-FROM STATE ═══\n\n";

    cout << "After move(x), x is in a 'valid but unspecified' state.\n\n";

    cout << "SAFE operations on moved-from object:\n";
    cout << "  ✓ Destructor (always safe)\n";
    cout << "  ✓ Assignment (x = new_value)\n";
    cout << "  ✓ .clear() then reuse\n";
    cout << "  ✓ .size() (returns some valid value, usually 0)\n\n";

    cout << "UNSAFE (undefined behavior):\n";
    cout << "  ✗ Access elements (v[0] after move)\n";
    cout << "  ✗ Rely on specific state (empty, zero, etc.)\n\n";

    // Demonstrate
    vector<int> v = {1, 2, 3};
    vector<int> v2 = move(v);
    cout << "After move: v.size()=" << v.size() << " (valid but unspecified)\n";
    v = {10, 20, 30};  // Safe to reassign!
    cout << "After reassign: v.size()=" << v.size() << " ✓\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    basicMoveDemo();
    whatMoveDoes();
    benchmarkCopyVsMove();
    autoMoves();
    swapUnderHood();
    cpMovePatterns();
    movedFromState();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. Move = steal internal resources (pointers), not copy data\n";
    cout << "2. std::move is just a cast, move constructor does the work\n";
    cout << "3. Move cost ≈ 24 bytes regardless of container size\n";
    cout << "4. Compiler auto-moves: returns, temporaries, reallocations\n";
    cout << "5. DON'T move return values — compiler does it better\n";
    cout << "6. After move: object is valid but unspecified — reassign or destroy\n";
    cout << "7. swap() uses 3 moves internally — always O(1) for containers\n";

    return 0;
}

