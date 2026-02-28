/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           06 — NAMESPACES IN C++                                           ║
║           From Zero to Grandmaster — Scope Management                      ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. What Are Namespaces?
 2. using namespace std — Pros and Cons
 3. Selective Using Declarations
 4. Custom Namespaces
 5. Namespace Best Practices for CP

CORE IDEA:
──────────
  Namespaces prevent name collisions. Without them, if two libraries
  both define a function called "sort", the compiler wouldn't know
  which one you mean.

  std:: is the namespace for ALL standard library components.
  Without "using namespace std", you'd write std::vector, std::sort, etc.
*/

#include <bits/stdc++.h>
using namespace std;  // THE CP WAY — explained below

// ═══════════════════════════════════════════════════════════════
// SECTION 1: WHAT ARE NAMESPACES?
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 A namespace is a declarative region that provides scope.

 Without namespaces:
   std::cout << "Hello";
   std::vector<int> v;
   std::sort(v.begin(), v.end());

 With "using namespace std":
   cout << "Hello";
   vector<int> v;
   sort(v.begin(), v.end());

 In CP, we ALWAYS use "using namespace std" because:
   • Less typing = faster coding
   • Every line saved matters in contests
   • Name collisions are rare in contest code

 In PRODUCTION code, DON'T use it because:
   • Can cause subtle name collisions
   • Makes code less readable (unclear which namespace)
   • Bad practice in header files
*/

// ═══════════════════════════════════════════════════════════════
// SECTION 2: CUSTOM NAMESPACES
// ═══════════════════════════════════════════════════════════════
/*
 You can define your own namespaces to organize code.
 Useful in team contests (each member's code in separate namespace).
*/

namespace geometry {
    struct Point {
        double x, y;
    };

    double distance(Point a, Point b) {
        return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }
}

namespace graph {
    vector<vector<int>> adj;

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: NAME COLLISION PITFALLS
// ═══════════════════════════════════════════════════════════════
/*
 COMMON PITFALLS with "using namespace std":

 1. Variable named "count":
    int count = 5;  // CONFLICT with std::count!

 2. Variable named "distance":
    int distance = 10;  // CONFLICT with std::distance!

 3. Variable named "next":
    int next = 3;  // CONFLICT with std::next!

 4. Variable named "prev":
    int prev = 2;  // CONFLICT with std::prev!

 GM TIP: If you get weird compilation errors with common variable names,
         it might be a namespace collision! Rename your variable.

 SAFE ALTERNATIVES:
   int cnt = 5;    // instead of count
   int dist = 10;  // instead of distance
   int nxt = 3;    // instead of next
   int prv = 2;    // instead of prev
*/

// ═══════════════════════════════════════════════════════════════
// SECTION 4: SELECTIVE USING DECLARATIONS
// ═══════════════════════════════════════════════════════════════
/*
 ALTERNATIVE to "using namespace std":
 Import only what you need:

 using std::cout;
 using std::cin;
 using std::vector;
 using std::sort;

 This avoids most collisions while reducing typing.
 Some competitive programmers prefer this approach.
*/

void demonstrateNamespaces() {
    cout << "═══ NAMESPACE DEMOS ═══\n\n";

    // Using custom namespace
    geometry::Point a = {0, 0};
    geometry::Point b = {3, 4};
    cout << "Distance between (0,0) and (3,4): "
         << geometry::distance(a, b) << "\n\n";

    // Name collision demo
    // int count = 5;  // This would shadow std::count!
    int cnt = 5;       // Safe alternative
    vector<int> v = {1, 2, 2, 3, 2, 4};
    cout << "Using std::count safely:\n";
    cout << "  Count of 2 in {1,2,2,3,2,4}: " << count(v.begin(), v.end(), 2) << "\n";
    cout << "  Our variable cnt: " << cnt << "\n\n";

    // Demonstrating :: scope resolution
    cout << "std::string works: " << string("Hello, STL!") << "\n";
    cout << "std::max works: max(3,7) = " << max(3, 7) << "\n";
    cout << "std::min works: min(3,7) = " << min(3, 7) << "\n\n";
}

void demonstrateCommonMistakes() {
    cout << "═══ COMMON NAMESPACE MISTAKES ═══\n\n";

    // MISTAKE 1: Shadowing std functions
    // int distance = 5;  // DON'T! Shadows std::distance
    int dist = 5;  // DO! Safe naming
    cout << "Tip: Use 'dist' instead of 'distance'\n";
    cout << "Tip: Use 'cnt' instead of 'count'\n";
    cout << "Tip: Use 'nxt' instead of 'next'\n";
    cout << "Tip: Use 'prv' instead of 'prev'\n";
    cout << "Tip: Use 'res' instead of 'result'\n\n";

    // MISTAKE 2: Forgetting that max/min are in std
    // #define max(a,b) ((a)>(b)?(a):(b))  // DON'T! Breaks std::max
    cout << "Tip: Don't #define max/min — use std::max/std::min\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demonstrateNamespaces();
    demonstrateCommonMistakes();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. 'using namespace std;' is FINE for CP — saves time\n";
    cout << "2. Avoid variable names that collide with std functions\n";
    cout << "3. Use cnt/dist/nxt/prv instead of count/distance/next/prev\n";
    cout << "4. Custom namespaces useful for organizing team code\n";
    cout << "5. Never #define max/min — it breaks STL!\n";

    return 0;
}

