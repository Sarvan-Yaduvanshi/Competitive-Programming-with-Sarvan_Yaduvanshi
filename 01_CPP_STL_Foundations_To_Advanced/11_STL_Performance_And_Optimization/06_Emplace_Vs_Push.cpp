/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           06 — EMPLACE vs PUSH — THE COMPLETE TRUTH                        ║
║           From Zero to Grandmaster — In-Place Construction                 ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. push_back vs emplace_back — What Actually Happens
 2. insert vs emplace — For Associative Containers
 3. When emplace ACTUALLY Helps (and when it doesn't)
 4. Benchmarks with Complex Types
 5. Pitfalls of emplace

═══════════════════════════════════════════════════════════════════════════════
 WHAT'S THE DIFFERENCE?
═══════════════════════════════════════════════════════════════════════════════

 push_back(value):
   1. Construct the object (possibly as temporary)
   2. COPY or MOVE it into the container's memory

 emplace_back(constructor_args...):
   1. Construct the object DIRECTLY in the container's memory
   2. No temporary, no copy, no move!

 DRY RUN with pair<string, vector<int>>:

   push_back({name, vec}):
     Step 1: Create temporary pair → allocates string + vector (COPY!)
     Step 2: Move temp into vector's slot
     Step 3: Destroy temporary

   emplace_back(name, vec):
     Step 1: Construct pair directly in vector's slot → allocates once
     Step 2: Done!

   Savings: 1 temporary construction + 1 move + 1 destruction
*/

#include <bits/stdc++.h>
using namespace std;

// A "heavy" object to demonstrate the difference
struct HeavyObject {
    string name;
    vector<int> data;
    static int constructCount;
    static int copyCount;
    static int moveCount;

    HeavyObject(const string& n, int size) : name(n), data(size, 42) {
        constructCount++;
    }
    HeavyObject(const HeavyObject& o) : name(o.name), data(o.data) {
        copyCount++;
    }
    HeavyObject(HeavyObject&& o) noexcept : name(move(o.name)), data(move(o.data)) {
        moveCount++;
    }

    static void resetCounters() { constructCount = copyCount = moveCount = 0; }
    static void printCounters(const string& label) {
        cout << "  " << label << ": construct=" << constructCount
             << ", copy=" << copyCount << ", move=" << moveCount << "\n";
    }
};
int HeavyObject::constructCount = 0;
int HeavyObject::copyCount = 0;
int HeavyObject::moveCount = 0;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: push_back vs emplace_back — COUNTED
// ═══════════════════════════════════════════════════════════════

void countedComparison() {
    cout << "═══ push_back vs emplace_back — OPERATION COUNTS ═══\n\n";

    // push_back with temporary
    {
        vector<HeavyObject> v;
        v.reserve(3);
        HeavyObject::resetCounters();
        v.push_back(HeavyObject("test", 100));  // Construct temp + move
        HeavyObject::printCounters("push_back(temp)");
    }

    // push_back with existing object
    {
        vector<HeavyObject> v;
        v.reserve(3);
        HeavyObject obj("test", 100);
        HeavyObject::resetCounters();
        v.push_back(obj);  // COPY (obj still needed)
        HeavyObject::printCounters("push_back(obj) ");
    }

    // push_back with move
    {
        vector<HeavyObject> v;
        v.reserve(3);
        HeavyObject obj("test", 100);
        HeavyObject::resetCounters();
        v.push_back(move(obj));  // MOVE
        HeavyObject::printCounters("push_back(move)");
    }

    // emplace_back — constructs in-place!
    {
        vector<HeavyObject> v;
        v.reserve(3);
        HeavyObject::resetCounters();
        v.emplace_back("test", 100);  // Construct directly! No temp!
        HeavyObject::printCounters("emplace_back()  ");
    }
    cout << "\n";
    cout << "emplace_back: 1 construct, 0 copies, 0 moves ← BEST!\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: WHEN emplace MATTERS AND WHEN IT DOESN'T
// ═══════════════════════════════════════════════════════════════

void whenItMatters() {
    cout << "═══ WHEN emplace MATTERS ═══\n\n";

    // For primitives (int, double) — NO difference
    cout << "--- Primitives: NO difference ---\n";
    {
        vector<int> v;
        v.reserve(100);

        auto start = chrono::steady_clock::now();
        for (int i = 0; i < 10000000; i++) v.push_back(i);
        auto t1 = chrono::duration_cast<chrono::microseconds>(
            chrono::steady_clock::now() - start).count();
        v.clear();

        start = chrono::steady_clock::now();
        for (int i = 0; i < 10000000; i++) v.emplace_back(i);
        auto t2 = chrono::duration_cast<chrono::microseconds>(
            chrono::steady_clock::now() - start).count();

        cout << "  int push_back (10^7):    " << t1 << " μs\n";
        cout << "  int emplace_back (10^7): " << t2 << " μs\n";
        cout << "  (Nearly identical — int is trivially copyable)\n\n";
    }

    // For pairs — emplace avoids make_pair
    cout << "--- Pairs: emplace is cleaner and slightly faster ---\n";
    {
        vector<pair<int, string>> v;
        v.reserve(1000000);

        auto start = chrono::steady_clock::now();
        for (int i = 0; i < 1000000; i++)
            v.push_back(make_pair(i, "hello"));
        auto t1 = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        v.clear();

        start = chrono::steady_clock::now();
        for (int i = 0; i < 1000000; i++)
            v.emplace_back(i, "hello");
        auto t2 = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();

        cout << "  pair push_back (10^6):    " << t1 << " ms\n";
        cout << "  pair emplace_back (10^6): " << t2 << " ms\n\n";
    }

    // For maps — emplace vs insert
    cout << "--- Maps: emplace vs insert ---\n";
    {
        map<int, string> m;
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < 500000; i++)
            m.insert({i, "value"});
        auto t1 = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        m.clear();

        start = chrono::steady_clock::now();
        for (int i = 0; i < 500000; i++)
            m.emplace(i, "value");
        auto t2 = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();

        cout << "  map insert (5×10^5):  " << t1 << " ms\n";
        cout << "  map emplace (5×10^5): " << t2 << " ms\n\n";
    }
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: EMPLACE PATTERNS FOR CP
// ═══════════════════════════════════════════════════════════════

void emplacePatterns() {
    cout << "═══ EMPLACE PATTERNS FOR CP ═══\n\n";

    // vector of pairs
    vector<pair<int, int>> edges;
    edges.emplace_back(1, 2);      // Instead of push_back({1, 2})
    edges.emplace_back(3, 4);
    cout << "Edge list: ";
    for (auto& [u, v] : edges) cout << "(" << u << "," << v << ") ";
    cout << "\n";

    // vector of tuples
    vector<tuple<int, int, int>> wedges;
    wedges.emplace_back(1, 2, 5);  // (u, v, weight)
    wedges.emplace_back(3, 4, 3);
    cout << "Weighted edges: ";
    for (auto& [u, v, w] : wedges)
        cout << "(" << u << "→" << v << ",w=" << w << ") ";
    cout << "\n";

    // set emplace
    set<pair<int, int>> pq;
    pq.emplace(5, 1);   // Instead of insert({5, 1})
    pq.emplace(3, 2);
    pq.emplace(7, 3);
    cout << "Set: ";
    for (auto& [d, n] : pq) cout << "(" << d << "," << n << ") ";
    cout << "\n";

    // map emplace with try_emplace (C++17 — doesn't construct value if key exists)
    map<string, vector<int>> groups;
    groups.try_emplace("A", vector<int>{1, 2, 3});  // Only constructs if "A" missing
    groups.try_emplace("A", vector<int>{4, 5, 6});  // "A" exists → does NOTHING
    cout << "groups[\"A\"]: ";
    for (int x : groups["A"]) cout << x << " ";
    cout << "(second try_emplace was no-op)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: PITFALLS OF EMPLACE
// ═══════════════════════════════════════════════════════════════

void emplacePitfalls() {
    cout << "═══ EMPLACE PITFALLS ═══\n\n";

    // Pitfall 1: emplace can call explicit constructors!
    cout << "PITFALL 1: emplace bypasses explicit constructors\n";
    cout << "  vector<unique_ptr<int>> v;\n";
    cout << "  v.emplace_back(new int(42));  // Works but dangerous!\n";
    cout << "  v.push_back(make_unique<int>(42));  // SAFER\n\n";

    // Pitfall 2: emplace may still copy if you pass an existing object
    cout << "PITFALL 2: Passing existing object to emplace still copies!\n";
    cout << "  string s = \"hello\";\n";
    cout << "  v.emplace_back(s);  // COPIES s (s is lvalue)\n";
    cout << "  v.emplace_back(move(s));  // MOVES s\n";
    cout << "  v.emplace_back(\"hello\");  // Constructs in-place ← BEST\n\n";

    // Pitfall 3: For simple types, emplace = push_back
    cout << "PITFALL 3: For int/double, emplace_back = push_back\n";
    cout << "  Don't obsess over emplace for primitives.\n";
    cout << "  Use emplace for pairs, tuples, structs, strings.\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: SUMMARY TABLE
// ═══════════════════════════════════════════════════════════════

void summaryTable() {
    cout << "═══ EMPLACE vs PUSH SUMMARY ═══\n\n";
    cout << "┌─────────────────────────────┬──────────────────┬──────────────────┐\n";
    cout << "│ Scenario                    │ push_back        │ emplace_back     │\n";
    cout << "├─────────────────────────────┼──────────────────┼──────────────────┤\n";
    cout << "│ int / double                │ Same             │ Same             │\n";
    cout << "│ pair<int,int>               │ {1,2} or make_pr │ 1, 2 ✓ (cleaner)│\n";
    cout << "│ pair<string,vector>         │ Copy temp then mv│ In-place ✓ FAST  │\n";
    cout << "│ struct with constructor     │ Create + move    │ In-place ✓ FAST  │\n";
    cout << "│ From existing variable      │ Copy or move     │ Copy or move     │\n";
    cout << "│ From string literal         │ Create + move    │ In-place ✓       │\n";
    cout << "└─────────────────────────────┴──────────────────┴──────────────────┘\n\n";

    cout << "GM RULE: Always use emplace_back for pairs, tuples, and structs.\n";
    cout << "         For primitives, either works — don't overthink it.\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    countedComparison();
    whenItMatters();
    emplacePatterns();
    emplacePitfalls();
    summaryTable();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. emplace_back constructs in-place → no temporary, no move\n";
    cout << "2. For int/double: identical performance to push_back\n";
    cout << "3. For pair/struct/string: emplace avoids unnecessary copies\n";
    cout << "4. map.emplace(k,v) > map.insert({k,v}) for complex values\n";
    cout << "5. try_emplace (C++17): doesn't construct value if key exists\n";
    cout << "6. HABIT: Always write emplace_back(args) in CP code\n";

    return 0;
}

