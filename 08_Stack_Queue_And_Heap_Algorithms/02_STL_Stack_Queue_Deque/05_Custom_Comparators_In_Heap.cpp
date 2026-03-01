/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           05 — CUSTOM COMPARATORS IN HEAP / PRIORITY QUEUE                   ║
║           From Zero to Grandmaster — STL Mastery                            ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Why Custom Comparators?
 2. Functor (Struct with operator())
 3. Lambda Comparator
 4. Function Pointer
 5. Custom Class in Heap
 6. Multi-Criteria Sorting
 7. Competitive Programming Patterns

WHY CUSTOM COMPARATORS?
──────────────────────
  Default priority_queue only gives you max/min by natural ordering.
  What if you need:
    • Sort by frequency, then by value?
    • Sort tasks by deadline, then by priority?
    • Min heap on one field, max on another?
    • Sort strings by length?

  You need a CUSTOM COMPARATOR!

HOW COMPARATORS WORK:
────────────────────
  A comparator comp(a, b) returns true if 'a' should come AFTER 'b' in the PQ.

  ┌────────────────────────────────────────────────────┐
  │ For priority_queue:                                │
  │   comp(a, b) = true  → 'b' has HIGHER priority    │
  │   comp(a, b) = false → 'a' has HIGHER priority    │
  │                                                    │
  │ Think of it as: "should a go below b?"             │
  │                                                    │
  │ MAX HEAP: less<int>     → a < b → a below b       │
  │   (bigger elements stay on top)                    │
  │ MIN HEAP: greater<int>  → a > b → a below b       │
  │   (smaller elements stay on top)                   │
  └────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <functional>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: FUNCTOR COMPARATOR (STRUCT)
// ═══════════════════════════════════════════════════════════════
/*
  A functor is a struct/class with operator() overloaded.
  This is the most common way to define custom comparators for PQ.

  struct Compare {
      bool operator()(const T& a, const T& b) {
          return ...;  // true if 'a' has LOWER priority than 'b'
      }
  };
*/

// Example: Min heap using functor
struct MinCompare {
    bool operator()(int a, int b) {
        return a > b;  // a has lower priority if a > b → smaller on top
    }
};

// Example: Sort by absolute value (smaller |x| on top)
struct AbsCompare {
    bool operator()(int a, int b) {
        return abs(a) > abs(b);  // Larger |x| has lower priority
    }
};

void demonstrateFunctor() {
    cout << "═══ SECTION 1: FUNCTOR COMPARATOR ═══\n\n";

    // Min heap using custom functor
    priority_queue<int, vector<int>, MinCompare> minPQ;
    for (int v : {30, 10, 50, 20, 40}) {
        minPQ.push(v);
    }
    cout << "Min heap (functor): ";
    while (!minPQ.empty()) {
        cout << minPQ.top() << " ";
        minPQ.pop();
    }
    cout << "\n";

    // Absolute value heap
    priority_queue<int, vector<int>, AbsCompare> absPQ;
    for (int v : {-5, 3, -1, 4, -2}) {
        absPQ.push(v);
    }
    cout << "Abs min heap: ";
    while (!absPQ.empty()) {
        cout << absPQ.top() << " ";
        absPQ.pop();
    }
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: LAMBDA COMPARATOR (C++11+)
// ═══════════════════════════════════════════════════════════════
/*
  Using lambda requires passing type AND instance to constructor:

  auto cmp = [](int a, int b) { return a > b; };
  priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
*/

void demonstrateLambda() {
    cout << "═══ SECTION 2: LAMBDA COMPARATOR ═══\n\n";

    // Min heap using lambda
    auto cmp = [](int a, int b) { return a > b; };
    priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);

    for (int v : {30, 10, 50, 20, 40}) pq.push(v);

    cout << "Min heap (lambda): ";
    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << "\n";

    // Sort strings by length (shorter on top)
    auto lenCmp = [](const string& a, const string& b) {
        return a.length() > b.length();  // Longer string has lower priority
    };
    priority_queue<string, vector<string>, decltype(lenCmp)> strPQ(lenCmp);

    for (string s : {"banana", "fig", "apple", "kiwi", "elderberry"}) {
        strPQ.push(s);
    }

    cout << "Shortest string first: ";
    while (!strPQ.empty()) {
        cout << strPQ.top() << "(" << strPQ.top().length() << ") ";
        strPQ.pop();
    }
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: CUSTOM CLASS IN HEAP
// ═══════════════════════════════════════════════════════════════
/*
  For custom classes, you can either:
    1. Overload operator< in the class (for max heap)
    2. Provide a comparator struct (more flexible)

  Method 1: operator< overload
  ────────────────────────────
  struct Task {
      int priority;
      string name;
      bool operator<(const Task& other) const {
          return priority < other.priority;  // Higher priority on top
      }
  };
  priority_queue<Task> pq;  // Uses operator<

  Method 2: External comparator
  ─────────────────────────────
  struct TaskCompare {
      bool operator()(const Task& a, const Task& b) {
          return a.deadline > b.deadline;  // Earlier deadline on top
      }
  };
  priority_queue<Task, vector<Task>, TaskCompare> pq;
*/

struct Task {
    int priority;
    int deadline;
    string name;

    // For max heap by priority (higher priority on top)
    bool operator<(const Task& other) const {
        return priority < other.priority;
    }
};

// Comparator: earlier deadline on top
struct DeadlineCompare {
    bool operator()(const Task& a, const Task& b) {
        if (a.deadline != b.deadline)
            return a.deadline > b.deadline;  // Earlier deadline = higher priority
        return a.priority < b.priority;      // Tie-break: higher priority first
    }
};

void demonstrateCustomClass() {
    cout << "═══ SECTION 3: CUSTOM CLASS IN HEAP ═══\n\n";

    // Max heap by priority (uses operator<)
    priority_queue<Task> byPriority;
    byPriority.push({3, 10, "Bug Fix"});
    byPriority.push({5, 5, "Deploy"});
    byPriority.push({1, 15, "Meeting"});
    byPriority.push({4, 3, "Code Review"});

    cout << "By priority (highest first):\n";
    while (!byPriority.empty()) {
        auto t = byPriority.top();
        byPriority.pop();
        cout << "  [pri=" << t.priority << " dl=" << t.deadline
             << "] " << t.name << "\n";
    }

    // Min heap by deadline (uses DeadlineCompare)
    priority_queue<Task, vector<Task>, DeadlineCompare> byDeadline;
    byDeadline.push({3, 10, "Bug Fix"});
    byDeadline.push({5, 5, "Deploy"});
    byDeadline.push({1, 15, "Meeting"});
    byDeadline.push({4, 3, "Code Review"});

    cout << "\nBy deadline (earliest first):\n";
    while (!byDeadline.empty()) {
        auto t = byDeadline.top();
        byDeadline.pop();
        cout << "  [dl=" << t.deadline << " pri=" << t.priority
             << "] " << t.name << "\n";
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: MULTI-CRITERIA SORTING
// ═══════════════════════════════════════════════════════════════
/*
  Common CP pattern: Sort by multiple criteria.

  Example: Sort students by score (desc), then by name (asc).

  Comparator logic:
    If scores differ: higher score = higher priority → a.score < b.score
    If scores same: alphabetically earlier name = higher priority → a.name > b.name
*/

struct Student {
    string name;
    int score;
};

struct StudentCompare {
    bool operator()(const Student& a, const Student& b) {
        if (a.score != b.score)
            return a.score < b.score;  // Higher score on top
        return a.name > b.name;        // Alphabetically earlier on top
    }
};

void demonstrateMultiCriteria() {
    cout << "═══ SECTION 4: MULTI-CRITERIA SORTING ═══\n\n";

    priority_queue<Student, vector<Student>, StudentCompare> pq;
    pq.push({"Alice", 90});
    pq.push({"Bob", 85});
    pq.push({"Charlie", 90});
    pq.push({"Diana", 95});
    pq.push({"Eve", 85});

    cout << "Rank (by score desc, name asc):\n";
    int rank = 1;
    while (!pq.empty()) {
        auto s = pq.top();
        pq.pop();
        cout << "  " << rank++ << ". " << s.name
             << " (score=" << s.score << ")\n";
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: CP PATTERNS WITH CUSTOM COMPARATORS
// ═══════════════════════════════════════════════════════════════

// Pattern: K closest points to origin
void kClosestPoints() {
    cout << "═══ SECTION 5: K CLOSEST POINTS PATTERN ═══\n\n";

    vector<pair<int, int>> points = {{3, 3}, {5, -1}, {-2, 4}, {1, 1}, {-3, -2}};
    int k = 3;

    // Max heap of size K — largest distance on top
    // When heap exceeds K, pop the farthest point
    auto distCmp = [](const pair<int,int>& a, const pair<int,int>& b) {
        int da = a.first * a.first + a.second * a.second;
        int db = b.first * b.first + b.second * b.second;
        return da < db;  // Larger distance on top (max heap)
    };

    priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(distCmp)> pq(distCmp);

    for (auto& p : points) {
        pq.push(p);
        if ((int)pq.size() > k) pq.pop();  // Remove farthest
    }

    cout << "K=" << k << " closest points to origin:\n";
    while (!pq.empty()) {
        auto [x, y] = pq.top();
        pq.pop();
        cout << "  (" << x << ", " << y << ") dist²=" << x*x + y*y << "\n";
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  CUSTOM COMPARATORS IN HEAP / PRIORITY QUEUE             ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    demonstrateFunctor();
    demonstrateLambda();
    demonstrateCustomClass();
    demonstrateMultiCriteria();
    kClosestPoints();

    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "COMPARATOR CHEAT SHEET:\n";
    cout << "───────────────────────\n";
    cout << "  MAX HEAP (default):   less<T>      → a < b → bigger on top\n";
    cout << "  MIN HEAP:             greater<T>    → a > b → smaller on top\n";
    cout << "  Custom:               comp(a,b)=true → b above a\n\n";
    cout << "  Functor:  struct Cmp { bool operator()(T a, T b) {...} };\n";
    cout << "  Lambda:   auto cmp = [](T a, T b) {...};\n";
    cout << "            PQ<T, vec<T>, decltype(cmp)> pq(cmp);\n";
    cout << "  Class:    bool operator<(const T& o) const {...}\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

