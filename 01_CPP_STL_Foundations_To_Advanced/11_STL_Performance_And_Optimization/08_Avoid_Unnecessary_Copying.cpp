/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           08 — AVOID UNNECESSARY COPYING                                   ║
║           From Zero to Grandmaster — Every Copy is a Crime                 ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. The Cost of Copying — Why It Matters
 2. Range-for Loop: auto vs auto& vs const auto&
 3. Function Parameters: By Value vs By Reference
 4. Return Value Optimization (RVO/NRVO)
 5. String Copy Traps
 6. Container Copy Traps
 7. The Complete Anti-Copy Checklist

═══════════════════════════════════════════════════════════════════════════════
 THE COST OF COPYING
═══════════════════════════════════════════════════════════════════════════════

 Copying an int: ~1 nanosecond (trivial)
 Copying a string of length L: ~L nanoseconds (allocate + memcpy)
 Copying a vector of size N: ~N × sizeof(T) nanoseconds
 Copying a map of size N: ~N × O(log N) (reconstruct BST!)

 DRY RUN — Accidental Copy in Loop:
   vector<string> words = {"hello", "world", ...};  // 10^5 strings, avg len 100

   BAD: for (auto w : words) { ... }
     → Each iteration: allocate 100 bytes, copy 100 chars, deallocate
     → Total: 10^5 × 100 bytes = 10^7 bytes copied!

   GOOD: for (const auto& w : words) { ... }
     → Each iteration: bind reference (just a pointer) → 0 copies!
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: RANGE-FOR LOOP COPIES
// ═══════════════════════════════════════════════════════════════

void rangeForCopies() {
    cout << "═══ RANGE-FOR LOOP: auto vs auto& vs const auto& ═══\n\n";

    vector<string> words(100000, "competitive_programming_is_awesome");

    // BAD: auto (copies each string!)
    {
        auto start = chrono::steady_clock::now();
        int total = 0;
        for (auto w : words) total += w.size();  // COPIES!
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "for (auto w : words):       " << ms << " ms (COPIES every string!)\n";
    }

    // GOOD: const auto& (no copy, read-only)
    {
        auto start = chrono::steady_clock::now();
        int total = 0;
        for (const auto& w : words) total += w.size();  // No copy!
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "for (const auto& w : words):" << ms << " ms (zero copies!)\n";
    }

    // MODIFY: auto& (no copy, allows modification)
    {
        auto start = chrono::steady_clock::now();
        for (auto& w : words) w[0] = 'C';  // Modify in-place
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "for (auto& w : words):      " << ms << " ms (modify, no copy)\n\n";
    }

    /*
     RULE:
       Read-only:  for (const auto& x : container)
       Modify:     for (auto& x : container)
       NEVER:      for (auto x : container)  ← unless T is trivial (int, char)

       Exception: for (int x : vec) is fine — copying an int is free.
    */

    cout << "┌───────────────────┬────────┬────────┬───────────────────────┐\n";
    cout << "│ Syntax            │ Copies │ Modify │ Use When              │\n";
    cout << "├───────────────────┼────────┼────────┼───────────────────────┤\n";
    cout << "│ auto x            │ YES    │ copy   │ ONLY for int/char/ptr │\n";
    cout << "│ auto& x           │ NO     │ YES    │ Need to modify element│\n";
    cout << "│ const auto& x     │ NO     │ NO     │ Read-only (DEFAULT)   │\n";
    cout << "│ auto&& x          │ NO     │ YES    │ Forwarding reference  │\n";
    cout << "└───────────────────┴────────┴────────┴───────────────────────┘\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: FUNCTION PARAMETER COPIES
// ═══════════════════════════════════════════════════════════════

// BAD: copies entire vector on every call!
int sumBad(vector<int> v) {
    int s = 0;
    for (int x : v) s += x;
    return s;
}

// GOOD: no copy, read-only access
int sumGood(const vector<int>& v) {
    int s = 0;
    for (int x : v) s += x;
    return s;
}

// MODIFY: pass by reference, modify in place
void sortInPlace(vector<int>& v) {
    sort(v.begin(), v.end());
}

void functionParamCopies() {
    cout << "═══ FUNCTION PARAMETER COPIES ═══\n\n";

    vector<int> big(1000000);
    iota(big.begin(), big.end(), 0);

    // BAD: by value
    {
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < 10; i++) sumBad(big);
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "sumBad(vector<int> v) × 10:       " << ms << " ms (copies 10^6 ints each!)\n";
    }

    // GOOD: by const reference
    {
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < 10; i++) sumGood(big);
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "sumGood(const vector<int>& v) × 10:" << ms << " ms (zero copies!)\n\n";
    }

    cout << "RULES:\n";
    cout << "  Read-only:  void f(const vector<int>& v)\n";
    cout << "  Modify:     void f(vector<int>& v)\n";
    cout << "  Small (≤16B): void f(int x)  → by value is fine\n";
    cout << "  NEVER:      void f(vector<int> v)  → copies entire vector!\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: RETURN VALUE OPTIMIZATION (RVO / NRVO)
// ═══════════════════════════════════════════════════════════════
/*
 GOOD NEWS: Modern compilers are SMART about returns!

 RVO (Return Value Optimization):
   The compiler constructs the return value DIRECTLY in the caller's memory.
   No copy, no move — as if the function builds the object where it's needed.

 NRVO (Named Return Value Optimization):
   Same but for named local variables.

 DRY RUN:
   vector<int> build() {
       vector<int> v = {1, 2, 3, 4, 5};
       return v;  // Compiler builds v directly in caller's space
   }
   auto result = build();  // NO copy! result IS v.
*/

vector<int> buildVector(int n) {
    vector<int> v(n);
    iota(v.begin(), v.end(), 0);
    return v;  // RVO/NRVO: no copy!
}

void demonstrateRVO() {
    cout << "═══ RETURN VALUE OPTIMIZATION (RVO) ═══\n\n";

    auto start = chrono::steady_clock::now();
    for (int i = 0; i < 100; i++) {
        auto v = buildVector(100000);  // No copy thanks to RVO!
    }
    auto ms = chrono::duration_cast<chrono::milliseconds>(
        chrono::steady_clock::now() - start).count();
    cout << "buildVector(10^5) × 100: " << ms << " ms\n";
    cout << "Compiler applies NRVO → no copies on return! ✓\n\n";

    cout << "RULES FOR SAFE RETURN:\n";
    cout << "  ✓ return local_variable;   → NRVO applies\n";
    cout << "  ✓ return {1, 2, 3};        → RVO applies\n";
    cout << "  ✓ return move(local_var);   → Explicit move (redundant, compiler does it)\n";
    cout << "  ✗ return condition ? a : b; → May prevent NRVO (two candidates)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: STRING COPY TRAPS
// ═══════════════════════════════════════════════════════════════

void stringCopyTraps() {
    cout << "═══ STRING COPY TRAPS ═══\n\n";

    // Trap 1: substr always copies
    cout << "TRAP 1: substr() ALWAYS creates a new string\n";
    string s = "Hello, World of Competitive Programming!";
    {
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < 1000000; i++) {
            string sub = s.substr(0, 10);  // Allocates + copies 10 chars!
        }
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "  substr() × 10^6: " << ms << " ms\n";
    }
    cout << "  FIX: Use string_view for non-owning substrings (C++17)\n\n";

    // Trap 2: String concatenation in loop
    cout << "TRAP 2: String concatenation in loop = O(n²)\n";
    {
        auto start = chrono::steady_clock::now();
        string result;
        for (int i = 0; i < 100000; i++) result += "abc";
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "  s += \"abc\" × 10^5: " << ms << " ms\n";
    }
    {
        auto start = chrono::steady_clock::now();
        string result;
        result.reserve(300000);
        for (int i = 0; i < 100000; i++) result += "abc";
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "  With reserve:     " << ms << " ms\n\n";
    }

    // Trap 3: Passing string by value
    cout << "TRAP 3: void f(string s) copies the string!\n";
    cout << "  FIX: void f(const string& s) or void f(string_view s)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: CONTAINER COPY TRAPS
// ═══════════════════════════════════════════════════════════════

void containerCopyTraps() {
    cout << "═══ CONTAINER COPY TRAPS ═══\n\n";

    // Trap 1: Structured binding copies
    cout << "TRAP 1: Structured binding without & copies!\n";
    map<string, vector<int>> data;
    data["key"] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    cout << "  auto [k, v] = *data.begin();    → COPIES key and value!\n";
    cout << "  auto& [k, v] = *data.begin();   → REFERENCES, no copy ✓\n";
    cout << "  const auto& [k, v] = ...        → Read-only ref, no copy ✓\n\n";

    // Trap 2: map[] operator with value type
    cout << "TRAP 2: Accessing map with [] can default-construct!\n";
    map<int, vector<int>> m;
    // m[5] creates an empty vector<int> if key 5 doesn't exist!
    cout << "  m[5].size() when key absent = " << m[5].size() << " (created empty!)\n";
    cout << "  Now m.size() = " << m.size() << " (entry was silently created!)\n";
    cout << "  FIX: Use m.count(k) or m.find(k) to check existence\n\n";

    // Trap 3: Unnecessary copy in algorithm
    cout << "TRAP 3: sort with copy comparator\n";
    cout << "  sort(v.begin(), v.end(), [](string a, string b) { ... });\n";
    cout << "  → COPIES a and b for EVERY comparison! O(n log n) copies!\n";
    cout << "  FIX: [](const string& a, const string& b) { ... }\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 6: THE COMPLETE ANTI-COPY CHECKLIST
// ═══════════════════════════════════════════════════════════════

void antiCopyChecklist() {
    cout << "═══ ANTI-COPY CHECKLIST ═══\n\n";

    cout << "☑ Range-for: const auto& (not auto)\n";
    cout << "☑ Function params: const T& (not T)\n";
    cout << "☑ Lambda captures: [&] or [&var] (not [=] for large objects)\n";
    cout << "☑ Lambda comparator: const T& params (not T)\n";
    cout << "☑ Structured bindings: auto& [k,v] (not auto [k,v])\n";
    cout << "☑ String operations: string_view or const string&\n";
    cout << "☑ Return: rely on RVO/NRVO (don't return const& to local!)\n";
    cout << "☑ Map access: .find()/.count() to check, not []\n";
    cout << "☑ vector of strings: reserve + emplace_back\n";
    cout << "☑ swap() instead of temp copy for large objects\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    rangeForCopies();
    functionParamCopies();
    demonstrateRVO();
    stringCopyTraps();
    containerCopyTraps();
    antiCopyChecklist();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. const auto& in range-for → zero copies\n";
    cout << "2. const T& for function params → zero copies\n";
    cout << "3. RVO/NRVO: compiler avoids copies on return automatically\n";
    cout << "4. substr() ALWAYS copies → use string_view instead\n";
    cout << "5. Lambda comparator: ALWAYS use const T& params\n";
    cout << "6. Every unnecessary copy = wasted time → potential TLE\n";

    return 0;
}

