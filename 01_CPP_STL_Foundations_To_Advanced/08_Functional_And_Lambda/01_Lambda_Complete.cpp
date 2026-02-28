/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — LAMBDA COMPLETE GUIDE                                       ║
║           From Zero to Grandmaster                                         ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

 Lambda syntax: [capture](params) mutable -> return_type { body }

 Capture modes:
   []      — nothing
   [=]     — all by value
   [&]     — all by reference
   [x]     — x by value
   [&x]    — x by reference
   [=, &x] — all by value, x by reference
   [this]  — capture this pointer (in class methods)
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ── Basic Lambda ──
    cout << "═══ LAMBDA BASICS ═══\n\n";
    auto greet = []() { cout << "Hello Lambda!\n"; };
    greet();

    auto square = [](int x) { return x * x; };
    cout << "square(7) = " << square(7) << "\n";

    auto divide = [](int a, int b) -> double { return (double)a / b; };
    cout << "divide(7,2) = " << divide(7, 2) << "\n\n";

    // ── Capture by Value vs Reference ──
    cout << "═══ CAPTURE ═══\n\n";
    int base = 10;
    auto byVal = [base](int x) { return x + base; };
    auto byRef = [&base](int x) { return x + base; };

    cout << "base=10, byVal(5)=" << byVal(5) << "\n";
    base = 100;
    cout << "base=100, byVal(5)=" << byVal(5) << " (still 15!)\n";
    cout << "base=100, byRef(5)=" << byRef(5) << " (105!)\n\n";

    // ── Mutable Lambda ──
    cout << "═══ MUTABLE LAMBDA ═══\n\n";
    /*
     By-value captures are const by default.
     'mutable' allows modifying the copy.
    */
    int counter = 0;
    auto increment = [counter]() mutable -> int {
        return ++counter;  // Modifies the COPY
    };
    cout << "Call 1: " << increment() << "\n";
    cout << "Call 2: " << increment() << "\n";
    cout << "Call 3: " << increment() << "\n";
    cout << "Original counter: " << counter << " (unchanged!)\n\n";

    // ── Generic Lambda (C++14) ──
    cout << "═══ GENERIC LAMBDA ═══\n\n";
    auto add = [](auto a, auto b) { return a + b; };
    cout << "add(3, 4) = " << add(3, 4) << "\n";
    cout << "add(3.5, 4.2) = " << add(3.5, 4.2) << "\n";
    cout << "add(str, str) = " << add(string("Hello"), string(" World")) << "\n\n";

    // ── Init Capture (C++14) ──
    cout << "═══ INIT CAPTURE ═══\n\n";
    auto ptr = make_unique<int>(42);
    // Move unique_ptr into lambda
    auto lambda = [p = move(ptr)]() { cout << "Moved value: " << *p << "\n"; };
    lambda();
    cout << "ptr is now: " << (ptr ? "valid" : "null") << "\n\n";

    // ── Lambda as Comparator ──
    cout << "═══ LAMBDA AS COMPARATOR ═══\n\n";
    vector<int> v = {-3, 1, -4, 1, 5, -9, 2};
    sort(v.begin(), v.end(), [](int a, int b) { return abs(a) < abs(b); });
    cout << "Sort by abs: "; for (int x : v) cout << x << " "; cout << "\n";

    // Sort indices by value
    vector<int> vals = {30, 10, 50, 20, 40};
    vector<int> idx(5);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&vals](int a, int b) { return vals[a] < vals[b]; });
    cout << "Indices sorted by value: ";
    for (int i : idx) cout << i << "(=" << vals[i] << ") ";
    cout << "\n\n";

    // ── Lambda with STL Algorithms ──
    cout << "═══ LAMBDA WITH ALGORITHMS ═══\n\n";
    v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    cout << "Even count: " << count_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; }) << "\n";
    cout << "All positive: " << all_of(v.begin(), v.end(), [](int x) { return x > 0; }) << "\n";
    cout << "Any > 8: " << any_of(v.begin(), v.end(), [](int x) { return x > 8; }) << "\n";

    auto it = find_if(v.begin(), v.end(), [](int x) { return x > 5; });
    cout << "First > 5: " << *it << "\n";

    // Partition: evens first
    partition(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
    cout << "Partitioned (even first): "; for (int x : v) cout << x << " "; cout << "\n\n";

    // ── Recursive Lambda (GM-Level DFS) ──
    cout << "═══ RECURSIVE LAMBDA (DFS) ═══\n\n";
    /*
     The C++14 way for recursive lambdas:
     auto dfs = [&](auto self, int node) -> void { ... self(self, next); };
     Call as: dfs(dfs, start);
    */
    int n = 5;
    vector<vector<int>> adj(n);
    adj[0] = {1, 2}; adj[1] = {3}; adj[2] = {4};

    vector<bool> visited(n, false);
    auto dfs = [&](auto self, int u) -> void {
        visited[u] = true;
        cout << "  Visit " << u << "\n";
        for (int v : adj[u]) {
            if (!visited[v]) self(self, v);
        }
    };
    cout << "DFS from 0:\n";
    dfs(dfs, 0);
    cout << "\n";

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. [&] captures all by ref (most common in CP)\n";
    cout << "2. mutable for modifying by-value captures\n";
    cout << "3. Generic lambda (auto params) works for any type\n";
    cout << "4. Recursive: auto f = [&](auto self, ...) { self(self, ...); }\n";
    cout << "5. Lambda comparators are THE way to do custom sorting\n";

    return 0;
}

