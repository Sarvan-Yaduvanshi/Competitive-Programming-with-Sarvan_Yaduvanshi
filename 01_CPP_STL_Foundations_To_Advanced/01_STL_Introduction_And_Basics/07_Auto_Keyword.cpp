/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           07 — AUTO KEYWORD IN C++                                         ║
║           From Zero to Grandmaster — Type Deduction Magic                  ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. What is auto?
 2. auto with STL Containers
 3. auto& vs const auto& vs auto
 4. auto with Structured Bindings (C++17)
 5. auto in Lambda Parameters (C++14/20)
 6. When NOT to Use auto

CORE IDEA:
──────────
  'auto' lets the compiler DEDUCE the type automatically.
  Instead of writing: map<string, vector<int>>::iterator it = m.begin();
  Just write:         auto it = m.begin();

  Same result, 50 less characters. In contests, this is GOLD.
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: BASIC AUTO USAGE
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 auto deduces the type from the initializer expression.

 auto x = 5;        → int
 auto y = 3.14;     → double
 auto s = "hello"s; → string (with s suffix)
 auto v = vector<int>{1,2,3}; → vector<int>

 DRY RUN:
   auto a = 42;          // compiler sees 42 → int
   auto b = 42LL;        // compiler sees 42LL → long long
   auto c = 42.0;        // compiler sees 42.0 → double
   auto d = 42.0f;       // compiler sees 42.0f → float
   auto e = true;        // compiler sees true → bool
   auto f = 'A';         // compiler sees 'A' → char
*/

void demonstrateBasicAuto() {
    cout << "═══ BASIC AUTO USAGE ═══\n\n";

    auto a = 42;          // int
    auto b = 42LL;        // long long
    auto c = 3.14;        // double
    auto d = true;        // bool
    auto e = 'X';         // char
    auto f = string("CP");// string

    cout << "auto a = 42        → type: int,       value: " << a << "\n";
    cout << "auto b = 42LL      → type: long long, value: " << b << "\n";
    cout << "auto c = 3.14      → type: double,    value: " << c << "\n";
    cout << "auto d = true      → type: bool,      value: " << d << "\n";
    cout << "auto e = 'X'       → type: char,      value: " << e << "\n";
    cout << "auto f = string()  → type: string,    value: " << f << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: AUTO WITH STL CONTAINERS
// ═══════════════════════════════════════════════════════════════
/*
 THIS IS WHERE AUTO SHINES IN CP:
 ─────────────────────────────────
 Without auto:
   vector<int>::iterator it = v.begin();
   map<string, vector<int>>::iterator it2 = m.begin();
   pair<int, string> p = *m.begin();

 With auto:
   auto it = v.begin();
   auto it2 = m.begin();
   auto p = *m.begin();

 So much cleaner! And no chance of getting the type wrong.
*/

void demonstrateAutoWithSTL() {
    cout << "═══ AUTO WITH STL CONTAINERS ═══\n\n";

    // Vector iterator
    vector<int> v = {10, 20, 30, 40, 50};
    auto it = v.begin();  // vector<int>::iterator
    cout << "vector begin: " << *it << "\n";

    // Set iterator
    set<int> s = {50, 10, 30};
    auto sit = s.begin();  // set<int>::iterator
    cout << "set begin (smallest): " << *sit << "\n";

    // Map iterator
    map<string, int> m = {{"alice", 95}, {"bob", 87}};
    auto mit = m.begin();  // map<string,int>::iterator
    cout << "map begin: " << mit->first << " → " << mit->second << "\n";

    // Complex type without auto:
    // map<string, vector<pair<int,int>>>::iterator → PAINFUL
    map<string, vector<pair<int, int>>> complex_map;
    complex_map["data"] = {{1, 2}, {3, 4}};
    auto cit = complex_map.begin();  // auto saves the day!
    cout << "complex map: " << cit->first << " has "
         << cit->second.size() << " pairs\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: auto vs auto& vs const auto&
// ═══════════════════════════════════════════════════════════════
/*
 CRITICAL DISTINCTION:
 ─────────────────────
 auto x = expr;        → COPIES the value (new variable)
 auto& x = expr;       → REFERENCE to original (modify original)
 const auto& x = expr; → READ-ONLY reference (efficient, no copy)

 DRY RUN:
   vector<int> v = {1, 2, 3};

   for (auto x : v)        → x is a COPY, modifying x doesn't change v
   for (auto& x : v)       → x IS v[i], modifying x CHANGES v
   for (const auto& x : v) → x IS v[i], but can't modify (read-only)

 GM TIP: Use const auto& for reading, auto& for modifying.
         NEVER use plain auto in range loops for large objects (copies!).
*/

void demonstrateAutoReferences() {
    cout << "═══ auto vs auto& vs const auto& ═══\n\n";

    vector<int> v = {1, 2, 3, 4, 5};

    // auto (copy) — does NOT modify original
    cout << "Before (auto copy): ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    for (auto x : v) {
        x *= 10;  // Modifies the COPY only
    }
    cout << "After auto x*=10:   ";
    for (int x : v) cout << x << " ";
    cout << " (unchanged!)\n\n";

    // auto& (reference) — MODIFIES original
    for (auto& x : v) {
        x *= 10;  // Modifies the ORIGINAL
    }
    cout << "After auto& x*=10:  ";
    for (int x : v) cout << x << " ";
    cout << " (changed!)\n\n";

    // const auto& (read-only reference) — EFFICIENT reading
    cout << "const auto& (read-only, no copy): ";
    for (const auto& x : v) {
        cout << x << " ";
        // x *= 2;  // COMPILE ERROR: x is const!
    }
    cout << "\n\n";

    // Performance difference with large objects
    vector<string> names = {"Alice", "Bob", "Charlie", "David"};
    cout << "For strings, const auto& avoids expensive copies:\n";
    for (const auto& name : names) {
        cout << "  " << name << " (no copy made)\n";
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: STRUCTURED BINDINGS (C++17) with auto
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Structured bindings let you decompose pairs, tuples, and structs
 into named variables.

 Old way:
   pair<int,int> p = {3, 7};
   int a = p.first;
   int b = p.second;

 C++17 way:
   auto [a, b] = pair{3, 7};

 SUPER useful with map iteration:
   for (auto& [key, value] : my_map) { ... }
*/

void demonstrateStructuredBindings() {
    cout << "═══ STRUCTURED BINDINGS (C++17) ═══\n\n";

    // With pair
    auto [x, y] = make_pair(3, 7);
    cout << "pair: x=" << x << ", y=" << y << "\n";

    // With tuple
    auto [a, b, c] = make_tuple(1, "hello", 3.14);
    cout << "tuple: a=" << a << ", b=" << b << ", c=" << c << "\n\n";

    // With map iteration — THE KILLER FEATURE
    map<string, int> scores = {{"Alice", 95}, {"Bob", 87}, {"Charlie", 92}};
    cout << "Map with structured bindings:\n";
    for (auto& [name, score] : scores) {
        cout << "  " << name << " scored " << score << "\n";
    }
    cout << "\n";

    // With array
    int arr[] = {10, 20, 30};
    auto [p, q, r] = arr;
    cout << "array: p=" << p << ", q=" << q << ", r=" << r << "\n\n";

    // Modifying through structured bindings
    map<string, int> freq;
    freq["a"] = 1;
    freq["b"] = 2;
    for (auto& [key, val] : freq) {
        val *= 100;  // Modifies the map!
    }
    cout << "After modification: ";
    for (auto& [key, val] : freq) {
        cout << key << "=" << val << " ";
    }
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: AUTO IN LAMBDA AND FUNCTION RETURNS
// ═══════════════════════════════════════════════════════════════

void demonstrateAdvancedAuto() {
    cout << "═══ ADVANCED AUTO USAGE ═══\n\n";

    // auto in lambda parameters (C++14 generic lambda)
    auto add = [](auto a, auto b) { return a + b; };
    cout << "Generic lambda: add(3, 4) = " << add(3, 4) << "\n";
    cout << "Generic lambda: add(3.5, 4.2) = " << add(3.5, 4.2) << "\n";
    cout << "Generic lambda: add(string, string) = " << add(string("Hello"), string(" World")) << "\n\n";

    // auto return type deduction (C++14)
    auto multiply = [](int a, int b) -> auto { return a * b; };
    cout << "Auto return: 6 * 7 = " << multiply(6, 7) << "\n\n";

    // auto with algorithms
    vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};
    auto maxIt = max_element(v.begin(), v.end());
    auto minIt = min_element(v.begin(), v.end());
    cout << "max_element: " << *maxIt << " at index " << (maxIt - v.begin()) << "\n";
    cout << "min_element: " << *minIt << " at index " << (minIt - v.begin()) << "\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demonstrateBasicAuto();
    demonstrateAutoWithSTL();
    demonstrateAutoReferences();
    demonstrateStructuredBindings();
    demonstrateAdvancedAuto();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. auto deduces types — saves typing, prevents errors\n";
    cout << "2. Use auto& to modify, const auto& to read efficiently\n";
    cout << "3. NEVER use plain auto in loops for large objects (copies!)\n";
    cout << "4. Structured bindings (auto [a,b]) = C++17 magic for pairs/maps\n";
    cout << "5. Generic lambdas with auto = write once, works for all types\n";

    return 0;
}

