/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           09 — LAMBDA BASICS                                               ║
║           From Zero to Grandmaster — Anonymous Functions                   ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. What Are Lambdas?
 2. Lambda Syntax
 3. Capture List Basics
 4. Lambda as Custom Comparator (The CP Killer Feature)
 5. Lambda with STL Algorithms

CORE IDEA:
──────────
  Lambdas are INLINE anonymous functions.
  Instead of defining a separate function, write it right where you need it.

  They're THE most important modern C++ feature for competitive programming.
  Custom sorting, filtering, transforming — all done with lambdas.
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: BASIC LAMBDA SYNTAX
// ═══════════════════════════════════════════════════════════════
/*
 SYNTAX:
 ───────
 [capture](parameters) -> return_type { body }

 Parts:
   [capture]    — What variables from outside to access
   (parameters) — Function parameters (like normal functions)
   -> return    — Return type (usually auto-deduced, optional)
   { body }     — The function body

 EXAMPLES:
   []()         { cout << "Hello"; }     // No capture, no params
   [](int x)    { return x * 2; }        // Takes param, returns value
   [&](int x)   { sum += x; }            // Captures by reference
   [=](int x)   { return x + base; }     // Captures by copy

 DRY RUN:
   auto double_it = [](int x) { return x * 2; };
   double_it(5) → evaluates body with x=5 → returns 5*2 = 10
*/

void demonstrateBasicLambda() {
    cout << "═══ BASIC LAMBDA SYNTAX ═══\n\n";

    // Simplest lambda
    auto hello = []() { cout << "Hello, Lambda!\n"; };
    hello();

    // Lambda with parameter
    auto double_it = [](int x) { return x * 2; };
    cout << "double_it(5) = " << double_it(5) << "\n";
    cout << "double_it(21) = " << double_it(21) << "\n";

    // Lambda with multiple parameters
    auto add = [](int a, int b) { return a + b; };
    cout << "add(3, 7) = " << add(3, 7) << "\n";

    // Lambda with explicit return type
    auto divide = [](int a, int b) -> double { return (double)a / b; };
    cout << "divide(7, 2) = " << divide(7, 2) << "\n";

    // Immediately invoked lambda (rarely used but cool)
    int result = [](int x) { return x * x; }(6);
    cout << "Immediate lambda(6²) = " << result << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: CAPTURE LIST
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 The capture list defines what variables the lambda can access
 from the enclosing scope.

 [=]    — Capture ALL by value (copy)
 [&]    — Capture ALL by reference
 [x]    — Capture x by value
 [&x]   — Capture x by reference
 [=, &x] — All by value, but x by reference
 [&, x]  — All by reference, but x by value

 DRY RUN:
   int base = 10;
   auto addBase = [base](int x) { return x + base; };
   addBase(5) → 5 + 10 = 15
   base = 20;
   addBase(5) → 5 + 10 = 15 (captured value of base at creation time!)

   auto addBaseRef = [&base](int x) { return x + base; };
   base = 20;
   addBaseRef(5) → 5 + 20 = 25 (uses current value via reference!)
*/

void demonstrateCaptureList() {
    cout << "═══ CAPTURE LIST ═══\n\n";

    int offset = 100;

    // Capture by value — uses value at CREATION time
    auto byValue = [offset](int x) { return x + offset; };
    cout << "By value: offset=100, add(5) = " << byValue(5) << "\n";
    offset = 200;
    cout << "By value: offset=200, add(5) = " << byValue(5) << " (still 105!)\n\n";

    // Capture by reference — uses CURRENT value
    auto byRef = [&offset](int x) { return x + offset; };
    cout << "By ref: offset=200, add(5) = " << byRef(5) << "\n";
    offset = 300;
    cout << "By ref: offset=300, add(5) = " << byRef(5) << " (updates!)\n\n";

    // Capture all by reference — common in CP
    int sum = 0;
    int cnt = 0;
    vector<int> v = {3, 1, 4, 1, 5, 9};
    for_each(v.begin(), v.end(), [&](int x) {
        sum += x;
        cnt++;
    });
    cout << "Capture all by ref: sum=" << sum << ", cnt=" << cnt << "\n\n";

    // Mixed capture
    int a = 10, b = 20;
    auto mixed = [a, &b]() {
        // a is read-only copy, b is modifiable reference
        b = a + b;  // b becomes 30
        // a = 5;    // ERROR: a is const (captured by value)
    };
    mixed();
    cout << "Mixed: a=" << a << ", b=" << b << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: LAMBDA AS CUSTOM COMPARATOR (THE CP KILLER FEATURE)
// ═══════════════════════════════════════════════════════════════
/*
 THIS IS WHERE LAMBDAS SHINE IN CP:
 ──────────────────────────────────

 sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
 → Sorts in DESCENDING order!

 sort(v.begin(), v.end(), [](pair<int,int>& a, pair<int,int>& b) {
     return a.second < b.second;  // Sort by second element
 });

 DRY RUN:
   v = {(1,5), (3,2), (2,8)}
   Sort by second element:
     Compare (1,5) vs (3,2): 5 < 2? NO → (3,2) first
     Compare (1,5) vs (2,8): 5 < 8? YES → (1,5) before (2,8)
     Result: {(3,2), (1,5), (2,8)}
*/

void demonstrateLambdaComparator() {
    cout << "═══ LAMBDA AS COMPARATOR ═══\n\n";

    // Sort descending
    vector<int> v = {5, 2, 8, 1, 9, 3};
    sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
    cout << "Descending: ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    // Sort by absolute value
    vector<int> v2 = {-5, 2, -8, 1, -9, 3};
    sort(v2.begin(), v2.end(), [](int a, int b) {
        return abs(a) < abs(b);
    });
    cout << "By |value|: ";
    for (int x : v2) cout << x << " ";
    cout << "\n";

    // Sort pairs by second element
    vector<pair<string, int>> students = {
        {"Alice", 85}, {"Bob", 95}, {"Charlie", 75}, {"David", 95}
    };
    sort(students.begin(), students.end(),
         [](const pair<string, int>& a, const pair<string, int>& b) {
             if (a.second != b.second) return a.second > b.second; // Higher score first
             return a.first < b.first;  // Same score → alphabetical
         });
    cout << "Students (by score desc, name asc):\n";
    for (auto& [name, score] : students) {
        cout << "  " << name << ": " << score << "\n";
    }
    cout << "\n";

    // Sort with external data (capture!)
    vector<int> indices = {0, 1, 2, 3, 4};
    vector<int> values = {30, 10, 50, 20, 40};
    sort(indices.begin(), indices.end(), [&values](int a, int b) {
        return values[a] < values[b];  // Sort indices by corresponding values
    });
    cout << "Indices sorted by values: ";
    for (int i : indices) cout << i << "(val=" << values[i] << ") ";
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: LAMBDA WITH STL ALGORITHMS
// ═══════════════════════════════════════════════════════════════

void demonstrateLambdaWithAlgorithms() {
    cout << "═══ LAMBDA WITH STL ALGORITHMS ═══\n\n";

    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // count_if — count elements matching a condition
    int even_count = count_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
    cout << "Even count: " << even_count << "\n";

    // find_if — find first element matching condition
    auto it = find_if(v.begin(), v.end(), [](int x) { return x > 5; });
    cout << "First > 5: " << *it << "\n";

    // all_of, any_of, none_of
    bool all_positive = all_of(v.begin(), v.end(), [](int x) { return x > 0; });
    bool any_even = any_of(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
    bool none_negative = none_of(v.begin(), v.end(), [](int x) { return x < 0; });
    cout << "all positive: " << all_positive << "\n";
    cout << "any even: " << any_even << "\n";
    cout << "none negative: " << none_negative << "\n";

    // transform — apply function to each element
    vector<int> squared(v.size());
    transform(v.begin(), v.end(), squared.begin(), [](int x) { return x * x; });
    cout << "Squared: ";
    for (int x : squared) cout << x << " ";
    cout << "\n";

    // accumulate with lambda (custom fold)
    int product = accumulate(v.begin(), v.end(), 1,
                             [](int acc, int x) { return acc * x; });
    cout << "Product: " << product << "\n";

    // partition — separate elements by condition
    vector<int> nums = {1, 8, 3, 6, 5, 4, 7, 2, 9, 10};
    partition(nums.begin(), nums.end(), [](int x) { return x % 2 == 0; });
    cout << "After partition (even first): ";
    for (int x : nums) cout << x << " ";
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: CP PROBLEM — USING LAMBDA EFFECTIVELY
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM: Given N events with start and end times,
          find maximum events that don't overlap.
          (Classic Greedy — Activity Selection)

 APPROACH: Sort by end time using lambda, greedily pick earliest ending.

 DRY RUN:
   Events: {(1,3), (2,5), (3,4), (6,8), (5,7)}
   Sort by end: {(1,3), (3,4), (2,5), (5,7), (6,8)}
   Pick (1,3) → last_end=3
   Pick (3,4) → 3 >= 3, skip? No, 3 >= 3... actually start >= last_end → pick
   Wait: (3,4) start=3, last_end=3 → 3 >= 3 → pick → last_end=4
   (2,5) start=2, 2 < 4 → skip
   (5,7) start=5, 5 >= 4 → pick → last_end=7
   (6,8) start=6, 6 < 7 → skip
   Answer: 3 events
*/

void solveProblem() {
    cout << "═══ CP PROBLEM: ACTIVITY SELECTION ═══\n\n";

    vector<pair<int, int>> events = {{1, 3}, {2, 5}, {3, 4}, {6, 8}, {5, 7}};

    // Sort by end time using lambda
    sort(events.begin(), events.end(),
         [](const pair<int, int>& a, const pair<int, int>& b) {
             return a.second < b.second;
         });

    cout << "Sorted by end time: ";
    for (auto& [s, e] : events) cout << "(" << s << "," << e << ") ";
    cout << "\n";

    int count = 0, last_end = -1;
    vector<pair<int, int>> selected;
    for (auto& [start, end] : events) {
        if (start >= last_end) {
            selected.push_back({start, end});
            last_end = end;
            count++;
        }
    }

    cout << "Selected events: ";
    for (auto& [s, e] : selected) cout << "(" << s << "," << e << ") ";
    cout << "\nMax non-overlapping events: " << count << "\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demonstrateBasicLambda();
    demonstrateCaptureList();
    demonstrateLambdaComparator();
    demonstrateLambdaWithAlgorithms();
    solveProblem();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. Lambda = [capture](params) { body }\n";
    cout << "2. [&] captures all by reference (most common in CP)\n";
    cout << "3. Lambda comparators are THE way to do custom sorting\n";
    cout << "4. count_if, find_if, all_of — use lambdas as predicates\n";
    cout << "5. Capture external data for index-sorting patterns\n";

    return 0;
}

/*
 PRACTICE PROBLEMS:
 ──────────────────
 1. [CF Sort by Frequency]  Custom sort with lambda
 2. [LC Meeting Rooms II]   https://leetcode.com/problems/meeting-rooms-ii/
 3. [CSES Movie Festival]   https://cses.fi/problemset/task/1629 (Activity Selection)
*/

