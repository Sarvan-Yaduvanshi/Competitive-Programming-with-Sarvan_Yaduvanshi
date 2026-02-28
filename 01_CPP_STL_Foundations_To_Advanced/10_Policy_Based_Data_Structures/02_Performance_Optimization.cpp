/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — PERFORMANCE OPTIMIZATION FOR CP                             ║
║           From Zero to Grandmaster — The AC vs TLE Difference              ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Fast I/O (ios::sync, cin.tie, printf/scanf)
 2. Reserve Optimization
 3. Emplace vs Push
 4. Avoid Unnecessary Copies
 5. Move Semantics
 6. Memory Layout & Cache Optimization
 7. Pragma Directives
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    // ═══ SECTION 1: FAST I/O ═══
    /*
     THE #1 OPTIMIZATION IN CP:

     ALWAYS add these two lines:
       ios::sync_with_stdio(false);  — Unsync C++ streams from C streams
       cin.tie(nullptr);             — Untie cin from cout

     This makes cin/cout as fast as scanf/printf!

     WITHOUT these: cin/cout flush on each operation → VERY SLOW
     WITH these: buffered I/O → 5-10x faster

     ALTERNATIVE: Use scanf/printf directly (C-style)
       scanf("%d", &n);
       printf("%d\n", n);

     FASTER ALTERNATIVE: Custom fast reader
       (Only needed for EXTREME cases, >10^7 input values)
    */
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "═══ FAST I/O ═══\n\n";
    cout << "ios::sync_with_stdio(false) + cin.tie(nullptr)\n";
    cout << "This is the SINGLE most important optimization!\n";
    cout << "NEVER use endl → use '\\n' instead (endl flushes buffer!)\n\n";

    // Benchmark: endl vs '\n'
    {
        stringstream ss;
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < 100000; i++) ss << i << '\n';
        auto t1 = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();

        stringstream ss2;
        start = chrono::steady_clock::now();
        for (int i = 0; i < 100000; i++) ss2 << i << endl;
        auto t2 = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();

        cout << "'\\n' (10^5): " << t1 << " ms\n";
        cout << "endl (10^5): " << t2 << " ms\n";
        cout << "(endl is SLOWER because it flushes after each line!)\n\n";
    }

    // ═══ SECTION 2: RESERVE OPTIMIZATION ═══
    cout << "═══ RESERVE OPTIMIZATION ═══\n\n";
    {
        const int N = 5000000;
        auto start = chrono::steady_clock::now();
        vector<int> v1;
        for (int i = 0; i < N; i++) v1.push_back(i);
        auto t1 = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();

        start = chrono::steady_clock::now();
        vector<int> v2;
        v2.reserve(N);
        for (int i = 0; i < N; i++) v2.push_back(i);
        auto t2 = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();

        cout << "Without reserve (5×10^6): " << t1 << " ms\n";
        cout << "With reserve (5×10^6):    " << t2 << " ms\n\n";
    }

    // ═══ SECTION 3: EMPLACE vs PUSH ═══
    cout << "═══ EMPLACE vs PUSH ═══\n\n";
    cout << "push_back(val)    → creates val, then copies/moves into container\n";
    cout << "emplace_back(args) → constructs directly in container memory\n\n";
    cout << "For int/double: negligible difference\n";
    cout << "For pair/struct: emplace avoids temporary + copy\n\n";

    // Example
    vector<pair<int, string>> vp;
    vp.push_back(make_pair(1, "hello"));  // Create temp pair, then move
    vp.push_back({2, "world"});           // C++11 braces
    vp.emplace_back(3, "best");           // Construct directly! No temp!
    cout << "All three work, emplace is fastest for complex types\n\n";

    // ═══ SECTION 4: AVOID COPIES ═══
    cout << "═══ AVOID UNNECESSARY COPIES ═══\n\n";
    cout << "BAD:  for (string s : vec) ...         (copies each string!)\n";
    cout << "GOOD: for (const string& s : vec) ...  (no copy!)\n";
    cout << "GOOD: for (const auto& s : vec) ...    (no copy!)\n\n";
    cout << "BAD:  void f(vector<int> v) ...        (copies entire vector!)\n";
    cout << "GOOD: void f(const vector<int>& v) ... (no copy!)\n\n";

    // Benchmark
    {
        vector<string> big(100000, "hello world this is a test string");

        auto start = chrono::steady_clock::now();
        long long len = 0;
        for (auto s : big) len += s.size();  // COPIES each string!
        auto t1 = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();

        start = chrono::steady_clock::now();
        len = 0;
        for (const auto& s : big) len += s.size();  // No copy!
        auto t2 = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();

        cout << "Copy loop (10^5 strings):       " << t1 << " ms\n";
        cout << "Const ref loop (10^5 strings):  " << t2 << " ms\n\n";
    }

    // ═══ SECTION 5: MOVE SEMANTICS ═══
    cout << "═══ MOVE SEMANTICS ═══\n\n";
    cout << "move() transfers ownership of resources instead of copying.\n";
    cout << "After move, the source object is in a valid but unspecified state.\n\n";

    string s1 = "Hello, World!";
    cout << "Before move: s1 = \"" << s1 << "\"\n";
    string s2 = move(s1);
    cout << "After move:  s2 = \"" << s2 << "\", s1 = \"" << s1 << "\" (moved-from)\n\n";

    // Practical: return large vector from function (automatic move)
    auto buildLargeVector = []() -> vector<int> {
        vector<int> v(1000000);
        iota(v.begin(), v.end(), 0);
        return v;  // Compiler applies move (or NRVO) — no copy!
    };
    auto result = buildLargeVector();
    cout << "Returned vector size: " << result.size() << " (no copy via NRVO/move)\n\n";

    // ═══ SECTION 6: COMPLETE OPTIMIZATION CHECKLIST ═══
    cout << "═══ OPTIMIZATION CHECKLIST ═══\n\n";
    cout << "☐ ios::sync_with_stdio(false); cin.tie(nullptr);\n";
    cout << "☐ Use '\\n' instead of endl\n";
    cout << "☐ reserve() vectors when size is known\n";
    cout << "☐ Use const auto& in range-for loops\n";
    cout << "☐ Pass large objects by const reference\n";
    cout << "☐ emplace_back over push_back for pairs/structs\n";
    cout << "☐ Use unordered_map + custom hash + reserve\n";
    cout << "☐ #pragma GCC optimize(\"O2,unroll-loops\")\n";
    cout << "☐ Avoid frequent allocations inside loops\n";
    cout << "☐ Use bitwise operations where possible\n";
    cout << "☐ nth_element O(N) instead of sort O(NlogN) for median\n\n";

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. Fast IO = #1 optimization (5-10x speedup)\n";
    cout << "2. '\\n' not endl, const auto& not auto\n";
    cout << "3. reserve() prevents reallocation TLE\n";
    cout << "4. Move semantics: compiler often does this for you\n";
    cout << "5. Profile before optimizing — find the actual bottleneck\n";

    return 0;
}

