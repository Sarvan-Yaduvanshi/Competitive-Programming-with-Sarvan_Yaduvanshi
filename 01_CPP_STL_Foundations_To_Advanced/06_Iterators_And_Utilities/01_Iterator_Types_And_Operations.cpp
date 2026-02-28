/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — ITERATOR TYPES AND OPERATIONS                               ║
║           From Zero to Grandmaster                                         ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

 ITERATOR HIERARCHY:
 ───────────────────
   Input Iterator      → read-only, forward (istream_iterator)
   Output Iterator     → write-only, forward (ostream_iterator)
   Forward Iterator    → read/write, forward (forward_list, unordered_*)
   Bidirectional       → +backward (list, set, map)
   Random Access       → +arithmetic (vector, deque, array)

 ┌────────────────┬────┬────┬────┬────┬────┬─────┬──────────────────────┐
 │ Operation      │ In │ Out│ Fwd│ Bid│ RA │ Note│ Example              │
 ├────────────────┼────┼────┼────┼────┼────┼─────┼──────────────────────┤
 │ *it (read)     │ ✓  │    │ ✓  │ ✓  │ ✓  │     │ int x = *it;         │
 │ *it = val      │    │ ✓  │ ✓  │ ✓  │ ✓  │     │ *it = 42;            │
 │ ++it           │ ✓  │ ✓  │ ✓  │ ✓  │ ✓  │     │ advance forward      │
 │ --it           │    │    │    │ ✓  │ ✓  │     │ go backward           │
 │ it + n         │    │    │    │    │ ✓  │     │ jump n positions      │
 │ it - it        │    │    │    │    │ ✓  │     │ distance              │
 │ it[n]          │    │    │    │    │ ✓  │     │ random access         │
 │ it == it       │ ✓  │    │ ✓  │ ✓  │ ✓  │     │ equality check        │
 │ it < it        │    │    │    │    │ ✓  │     │ comparison            │
 └────────────────┴────┴────┴────┴────┴────┴─────┴──────────────────────┘
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ── begin, end, rbegin, rend ──
    cout << "═══ begin/end/rbegin/rend ═══\n\n";
    vector<int> v = {10, 20, 30, 40, 50};

    cout << "Forward:  ";
    for (auto it = v.begin(); it != v.end(); ++it) cout << *it << " ";
    cout << "\n";

    cout << "Reverse:  ";
    for (auto it = v.rbegin(); it != v.rend(); ++it) cout << *it << " ";
    cout << "\n";

    cout << "cbegin:   " << *v.cbegin() << " (const, can't modify)\n\n";

    // ── advance, distance, next, prev ──
    cout << "═══ advance / distance / next / prev ═══\n\n";

    // advance — move iterator by n positions
    auto it = v.begin();
    advance(it, 3);
    cout << "advance(begin, 3) = " << *it << "\n";

    // distance — count elements between iterators
    cout << "distance(begin, end) = " << distance(v.begin(), v.end()) << "\n";

    // next — return new iterator n positions ahead
    auto it2 = next(v.begin(), 2);
    cout << "next(begin, 2) = " << *it2 << "\n";

    // prev — return new iterator n positions back
    auto it3 = prev(v.end(), 1);
    cout << "prev(end, 1) = " << *it3 << "\n\n";

    // ── With set (bidirectional — NO arithmetic!) ──
    cout << "═══ ITERATORS WITH SET ═══\n\n";
    set<int> s = {50, 10, 30, 20, 40};

    auto sit = s.begin();
    advance(sit, 2);  // Can't do sit + 2!
    cout << "set: advance(begin, 2) = " << *sit << "\n";
    cout << "set: next(begin) = " << *next(s.begin()) << "\n";
    cout << "set: prev(end) = " << *prev(s.end()) << " (max element)\n";
    cout << "set: distance = " << distance(s.begin(), s.end()) << "\n\n";

    // ── Output iterators (writing to stream) ──
    cout << "═══ OUTPUT ITERATORS ═══\n\n";
    cout << "ostream_iterator: ";
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
    cout << "\n";

    // Copy from one container to another
    vector<int> dest;
    copy(v.begin(), v.end(), back_inserter(dest));
    cout << "back_inserter copy: ";
    for (int x : dest) cout << x << " ";
    cout << "\n\n";

    // ── Useful iterator patterns ──
    cout << "═══ USEFUL PATTERNS ═══\n\n";

    // Get last element safely
    if (!v.empty()) cout << "Last element: " << *prev(v.end()) << "\n";

    // K-th element
    int k = 3;
    cout << k << "-th element (0-indexed): " << *next(v.begin(), k) << "\n";

    // Iterate every other element
    cout << "Every other: ";
    for (auto it = v.begin(); it != v.end(); advance(it, min(2, (int)distance(it, v.end()))))
        cout << *it << " ";
    cout << "\n\n";

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. 5 iterator types: Input, Output, Forward, Bidirectional, Random Access\n";
    cout << "2. advance() for non-random-access, +n for random access\n";
    cout << "3. next()/prev() return NEW iterator (don't modify original)\n";
    cout << "4. distance() works for all, O(1) for RA, O(n) for others\n";
    cout << "5. *prev(s.end()) = max element of set\n";

    return 0;
}

