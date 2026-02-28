/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — ITERATOR INVALIDATION RULES                                 ║
║           From Zero to Grandmaster — Avoiding Undefined Behavior           ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

 ITERATOR INVALIDATION = when an iterator becomes "dangling" (unsafe to use)
 after modifying the container.

 THIS CAUSES THE MOST SUBTLE BUGS IN CP!

 ┌──────────────────┬────────────────────────────────────────────────────┐
 │ Container        │ When Iterators Are Invalidated                    │
 ├──────────────────┼────────────────────────────────────────────────────┤
 │ vector           │ insert/erase at or before → ALL after invalidated │
 │                  │ push_back if capacity exceeded → ALL invalidated  │
 │ deque            │ insert/erase → ALL invalidated (except front/back)│
 │ list             │ NEVER (only erased element's iterator)            │
 │ set/map          │ NEVER (only erased element's iterator)            │
 │ unordered_set/map│ rehash → ALL invalidated                         │
 └──────────────────┴────────────────────────────────────────────────────┘
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ── SAFE ERASE WHILE ITERATING — VECTOR ──
    cout << "═══ SAFE ERASE — VECTOR ═══\n\n";
    {
        vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        // Remove even numbers SAFELY
        // WRONG: for (auto it = v.begin(); it != v.end(); ++it) if (*it%2==0) v.erase(it);
        // The ++ would use an invalidated iterator!

        // CORRECT Method 1: erase-remove idiom
        v.erase(remove_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; }), v.end());
        cout << "erase-remove (even): ";
        for (int x : v) cout << x << " ";
        cout << "\n";
    }
    {
        vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        // CORRECT Method 2: erase returns next valid iterator
        for (auto it = v.begin(); it != v.end(); ) {
            if (*it % 2 == 0)
                it = v.erase(it);  // erase returns next valid iterator!
            else
                ++it;
        }
        cout << "erase+return (even): ";
        for (int x : v) cout << x << " ";
        cout << "\n\n";
    }

    // ── SAFE ERASE WHILE ITERATING — SET ──
    cout << "═══ SAFE ERASE — SET ═══\n\n";
    {
        set<int> s = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        // Set iterators are stable! Only erased element invalidated.
        for (auto it = s.begin(); it != s.end(); ) {
            if (*it % 3 == 0)
                it = s.erase(it);  // C++11: erase returns next iterator
            else
                ++it;
        }
        cout << "set erase multiples of 3: ";
        for (int x : s) cout << x << " ";
        cout << "\n\n";
    }

    // ── SAFE ERASE WHILE ITERATING — MAP ──
    cout << "═══ SAFE ERASE — MAP ═══\n\n";
    {
        map<string, int> m = {{"a",1}, {"b",2}, {"c",3}, {"d",4}, {"e",5}};
        for (auto it = m.begin(); it != m.end(); ) {
            if (it->second % 2 == 0)
                it = m.erase(it);
            else
                ++it;
        }
        cout << "map erase even values: ";
        for (auto& [k, v] : m) cout << k << ":" << v << " ";
        cout << "\n\n";
    }

    // ── VECTOR PUSH_BACK INVALIDATION ──
    cout << "═══ VECTOR PUSH_BACK DANGER ═══\n\n";
    {
        vector<int> v = {1, 2, 3};
        auto it = v.begin();
        cout << "Before push_back: *it = " << *it << ", cap = " << v.capacity() << "\n";
        // v.push_back(4); ← If this causes reallocation, 'it' is INVALID!
        // SAFE: use reserve() first, or don't hold iterators across push_back
        v.reserve(100);  // Now push_back won't invalidate
        it = v.begin();  // Refresh iterator after reserve (reserve can invalidate!)
        v.push_back(4);
        cout << "After push_back(with reserve): *it = " << *it << "\n\n";
    }

    // ── COMMON BUG PATTERNS ──
    cout << "═══ COMMON BUG PATTERNS ═══\n\n";
    cout << "BUG 1: Erasing in for loop without updating iterator\n";
    cout << "  FIX: it = container.erase(it)\n\n";
    cout << "BUG 2: push_back while holding iterator to vector\n";
    cout << "  FIX: use index instead, or reserve() first\n\n";
    cout << "BUG 3: Using iterator after container is destroyed\n";
    cout << "  FIX: don't return/store iterators from local containers\n\n";

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. vector: ANY insert/erase can invalidate iterators\n";
    cout << "2. set/map: only erased element's iterator is invalidated\n";
    cout << "3. Safe erase pattern: it = container.erase(it)\n";
    cout << "4. For vector: prefer erase-remove idiom\n";
    cout << "5. When in doubt, use indices instead of iterators\n";

    return 0;
}

