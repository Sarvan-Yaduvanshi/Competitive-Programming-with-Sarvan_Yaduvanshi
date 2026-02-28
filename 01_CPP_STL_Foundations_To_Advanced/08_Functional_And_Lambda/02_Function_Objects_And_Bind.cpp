/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — FUNCTION OBJECTS, std::function, AND std::bind              ║
║           From Zero to Grandmaster                                         ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Functors (Function Objects)
 2. std::function — The Universal Function Wrapper
 3. std::bind — Partial Application
 4. Predefined Functors (less, greater, plus, etc.)
 5. CP Patterns with Function Objects

WHAT ARE FUNCTORS?
──────────────────
  A functor is a CLASS with operator() overloaded.
  It acts like a function but can hold STATE.
  Lambdas are actually syntactic sugar for functors!
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: FUNCTORS (Function Objects)
// ═══════════════════════════════════════════════════════════════

struct Multiplier {
    int factor;
    Multiplier(int f) : factor(f) {}
    int operator()(int x) const { return x * factor; }
};

struct DescendingCompare {
    bool operator()(int a, int b) const { return a > b; }
};

void demonstrateFunctors() {
    cout << "═══ FUNCTORS ═══\n\n";

    // Stateful functor
    Multiplier triple(3);
    Multiplier double_it(2);
    cout << "triple(5) = " << triple(5) << "\n";
    cout << "double_it(5) = " << double_it(5) << "\n";

    // Functor as comparator
    vector<int> v = {3, 1, 4, 1, 5, 9};
    sort(v.begin(), v.end(), DescendingCompare());
    cout << "Sorted desc (functor): ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    // Functor with transform
    v = {1, 2, 3, 4, 5};
    vector<int> result(v.size());
    transform(v.begin(), v.end(), result.begin(), Multiplier(10));
    cout << "×10: ";
    for (int x : result) cout << x << " ";
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: std::function — Universal Function Wrapper
// ═══════════════════════════════════════════════════════════════
/*
 std::function<ReturnType(ParamTypes...)> can hold:
   • Regular functions
   • Lambdas
   • Functors
   • Member function pointers (with bind)

 USEFUL IN CP FOR:
   • Recursive lambdas (alternative to auto self pattern)
   • Storing callbacks
   • DP memoization with function pointers

 WARNING: std::function has overhead (type erasure).
          For performance-critical code, prefer auto + templates.
*/

int regularFunction(int x) { return x * x; }

void demonstrateStdFunction() {
    cout << "═══ std::function ═══\n\n";

    // Hold regular function
    function<int(int)> f1 = regularFunction;
    cout << "Regular: f1(5) = " << f1(5) << "\n";

    // Hold lambda
    function<int(int)> f2 = [](int x) { return x + 100; };
    cout << "Lambda: f2(5) = " << f2(5) << "\n";

    // Hold functor
    function<int(int)> f3 = Multiplier(7);
    cout << "Functor: f3(5) = " << f3(5) << "\n\n";

    // Recursive lambda WITH std::function (alternative to auto self)
    function<int(int)> factorial = [&](int n) -> int {
        if (n <= 1) return 1;
        return n * factorial(n - 1);
    };
    cout << "factorial(5) = " << factorial(5) << "\n";

    // Recursive DFS with std::function
    int n = 5;
    vector<vector<int>> adj(n);
    adj[0] = {1, 2}; adj[1] = {3}; adj[2] = {4};
    vector<bool> vis(n, false);

    function<void(int)> dfs = [&](int u) {
        vis[u] = true;
        cout << "  Visit " << u << "\n";
        for (int v : adj[u])
            if (!vis[v]) dfs(v);
    };
    cout << "\nDFS with std::function:\n";
    dfs(0);

    // Compare: auto self vs std::function for recursion
    cout << "\n";
    cout << "auto self pattern:    FASTER (no type erasure overhead)\n";
    cout << "std::function pattern: CLEANER syntax but ~2x slower\n";
    cout << "GM TIP: Use auto self for competitive, std::function for clarity\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: std::bind — Partial Application
// ═══════════════════════════════════════════════════════════════

int add3(int a, int b, int c) { return a + b + c; }

void demonstrateBind() {
    cout << "═══ std::bind ═══\n\n";

    using namespace std::placeholders;

    // Fix first argument
    auto add_10 = bind(add3, 10, _1, _2);
    cout << "add3(10, 20, 30) via bind: " << add_10(20, 30) << "\n";

    // Reorder arguments
    auto swapped = bind(add3, _3, _2, _1);
    cout << "swapped(1,2,3) = add3(3,2,1) = " << swapped(1, 2, 3) << "\n";

    // Bind with STL algorithms
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto count_gt5 = count_if(v.begin(), v.end(), bind(greater<int>(), _1, 5));
    cout << "Count > 5: " << count_gt5 << "\n\n";

    cout << "GM TIP: Lambdas have mostly replaced bind in modern C++.\n";
    cout << "Equivalent lambda: [](int x) { return x > 5; }\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: PREDEFINED FUNCTORS
// ═══════════════════════════════════════════════════════════════

void demonstratePredefinedFunctors() {
    cout << "═══ PREDEFINED FUNCTORS ═══\n\n";

    /*
     Arithmetic:  plus<>, minus<>, multiplies<>, divides<>, modulus<>, negate<>
     Comparison:  equal_to<>, not_equal_to<>, greater<>, less<>,
                  greater_equal<>, less_equal<>
     Logical:     logical_and<>, logical_or<>, logical_not<>
     Bitwise:     bit_and<>, bit_or<>, bit_xor<>
    */

    vector<int> v = {5, 2, 8, 1, 9, 3};

    // Sorting with predefined functors
    sort(v.begin(), v.end(), greater<int>());
    cout << "sort(greater): "; for (int x : v) cout << x << " "; cout << "\n";

    sort(v.begin(), v.end(), less<int>());
    cout << "sort(less):    "; for (int x : v) cout << x << " "; cout << "\n";

    // Priority queue with greater (min heap)
    priority_queue<int, vector<int>, greater<int>> minPQ;
    for (int x : v) minPQ.push(x);
    cout << "PQ(greater) = min heap, top: " << minPQ.top() << "\n";

    // Accumulate with multiplies (product)
    int product = accumulate(v.begin(), v.end(), 1, multiplies<int>());
    cout << "Product: " << product << "\n";

    // Transform with negate
    vector<int> neg(v.size());
    transform(v.begin(), v.end(), neg.begin(), negate<int>());
    cout << "Negated: "; for (int x : neg) cout << x << " "; cout << "\n\n";

    // Set operations with custom comparators
    set<int, greater<int>> descSet = {3, 1, 4, 1, 5, 9};
    cout << "Descending set: ";
    for (int x : descSet) cout << x << " ";
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: CP PATTERN — MEMOIZED RECURSIVE LAMBDA
// ═══════════════════════════════════════════════════════════════

void memoizedDP() {
    cout << "═══ MEMOIZED DP WITH LAMBDA ═══\n\n";

    // Fibonacci with memoization using recursive lambda
    map<int, long long> memo;
    function<long long(int)> fib = [&](int n) -> long long {
        if (n <= 1) return n;
        if (memo.count(n)) return memo[n];
        return memo[n] = fib(n - 1) + fib(n - 2);
    };

    cout << "Fibonacci sequence:\n";
    for (int i = 0; i <= 15; i++) {
        cout << "  fib(" << i << ") = " << fib(i) << "\n";
    }

    cout << "\nGM TIP: For DP, prefer array-based memoization over map.\n";
    cout << "Map adds O(log n) overhead per lookup.\n\n";

    // Better approach for known range:
    const int MAXN = 50;
    vector<long long> dp(MAXN + 1, -1);
    function<long long(int)> fib2 = [&](int n) -> long long {
        if (n <= 1) return n;
        if (dp[n] != -1) return dp[n];
        return dp[n] = fib2(n - 1) + fib2(n - 2);
    };
    cout << "fib(45) = " << fib2(45) << "\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demonstrateFunctors();
    demonstrateStdFunction();
    demonstrateBind();
    demonstratePredefinedFunctors();
    memoizedDP();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. Functors = structs with operator() (lambdas are syntactic sugar)\n";
    cout << "2. std::function: universal wrapper, useful for recursive lambdas\n";
    cout << "3. std::bind: mostly replaced by lambdas in modern C++\n";
    cout << "4. Predefined: greater<>, less<>, multiplies<>, negate<>\n";
    cout << "5. For recursion: auto self is faster, std::function is cleaner\n";
    cout << "6. Memoized DP: function<> + map or vector cache\n";

    return 0;
}

