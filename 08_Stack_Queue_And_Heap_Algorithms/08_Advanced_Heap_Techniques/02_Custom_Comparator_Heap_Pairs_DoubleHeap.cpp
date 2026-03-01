/*
╔══════════════════════════════════════════════════════════════════════════════╗
║       02 — CUSTOM COMPARATOR STRUCTS + HEAP WITH PAIRS + DOUBLE HEAP         ║
║           From Zero to Grandmaster — Advanced Heap Techniques               ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Custom Comparator Struct — Deep Dive
 2. Heap with pair / tuple
 3. Double Heap (Two-Heap Technique) — Extended
 4. Decrease Key Simulation

CUSTOM COMPARATOR — HOW IT REALLY WORKS:
────────────────────────────────────────
  priority_queue uses comp(a, b) to determine ordering.

  RULE: comp(a, b) = true means "a has LOWER priority than b"
                     → b goes closer to top

  ┌──────────────────────────────────────────────────────────────┐
  │  For MAX HEAP: comp(a,b) = (a < b)    → larger values on top│
  │  For MIN HEAP: comp(a,b) = (a > b)    → smaller values on top│
  │                                                               │
  │  Think: comp returns true when a should be BELOW b in heap   │
  └──────────────────────────────────────────────────────────────┘

  Why is this confusing?
    sort(v.begin(), v.end(), comp) → comp(a,b)=true means "a before b"
    priority_queue<T, vector<T>, comp> → comp(a,b)=true means "a AFTER b" (lower priority)

  They're OPPOSITE because:
    sort → ascending by default (smallest first)
    PQ   → max-heap by default (largest first = highest priority)

EXAMPLES:
────────
  1. Sort students by grade (highest first), then by name (alphabetical)

  struct Student { string name; int grade; };

  struct Compare {
      bool operator()(const Student& a, const Student& b) {
          if (a.grade != b.grade) return a.grade < b.grade;  // Higher grade = higher priority
          return a.name > b.name;  // Alphabetically first = higher priority
      }
  };

  priority_queue<Student, vector<Student>, Compare> pq;
  → Top of PQ: highest grade, alphabetically first name among ties

  2. Dijkstra: min-heap by distance

  priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
  → pair sorts by first element, then second
  → (dist, node) → smallest distance on top ✅
*/

#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <functional>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// 1. CUSTOM COMPARATOR WITH STRUCT
// ═══════════════════════════════════════════════════════════════

struct Task {
    string name;
    int priority;
    int deadline;
};

// Tasks ordered by: highest priority first, then earliest deadline
struct TaskCompare {
    bool operator()(const Task& a, const Task& b) {
        if (a.priority != b.priority)
            return a.priority < b.priority;  // Higher priority on top
        return a.deadline > b.deadline;       // Earlier deadline on top
    }
};

// ═══════════════════════════════════════════════════════════════
// 2. HEAP WITH PAIR AND TUPLE
// ═══════════════════════════════════════════════════════════════

void heapWithPairs() {
    cout << "═══ HEAP WITH PAIRS ═══\n";

    // Min heap by first element, then second
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> minH;
    minH.push({5, 100});
    minH.push({3, 200});
    minH.push({3, 100});
    minH.push({7, 50});

    cout << "  Min heap (pair<int,int>):\n";
    while (!minH.empty()) {
        auto [a, b] = minH.top(); minH.pop();
        cout << "    (" << a << ", " << b << ")\n";
    }

    // Max heap with tuple
    cout << "\n  Max heap (tuple<int,string,int>):\n";
    priority_queue<tuple<int,string,int>> maxH;
    maxH.push({10, "Task_A", 1});
    maxH.push({20, "Task_B", 2});
    maxH.push({10, "Task_C", 3});

    while (!maxH.empty()) {
        auto [pri, name, id] = maxH.top(); maxH.pop();
        cout << "    (" << pri << ", " << name << ", " << id << ")\n";
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// 3. LAMBDA AS COMPARATOR
// ═══════════════════════════════════════════════════════════════

void heapWithLambda() {
    cout << "═══ HEAP WITH LAMBDA COMPARATOR ═══\n";

    auto cmp = [](const pair<int,string>& a, const pair<int,string>& b) {
        // Sort by value ascending, then name alphabetically
        if (a.first != b.first) return a.first > b.first;  // Smaller value = higher priority
        return a.second > b.second;  // Alphabetically smaller = higher priority
    };

    priority_queue<pair<int,string>, vector<pair<int,string>>, decltype(cmp)> pq(cmp);
    pq.push({5, "Eve"});
    pq.push({3, "Bob"});
    pq.push({3, "Alice"});
    pq.push({7, "Dave"});

    while (!pq.empty()) {
        auto [val, name] = pq.top(); pq.pop();
        cout << "    (" << val << ", " << name << ")\n";
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// 4. DOUBLE HEAP TECHNIQUE — SLIDING WINDOW COST (CSES 1077)
// ═══════════════════════════════════════════════════════════════
/*
  Sliding window of size k. For each window, find the cost of making
  all elements equal to the median. Cost = sum of |elem - median|.

  Approach: Maintain two halves using two heaps + lazy deletion.
    Left half: max heap (contains smaller elements, top = median if k is odd)
    Right half: min heap (contains larger elements)

  Track sum of each half to compute cost in O(1).

  Cost = (median × leftSize - leftSum) + (rightSum - median × rightSize)

  This is the full "two-heap with balance and lazy deletion" pattern.
*/

// Simplified demo of double heap for running median + cost
class DoubleHeap {
    priority_queue<int> maxH;           // Left half
    priority_queue<int, vector<int>, greater<int>> minH;  // Right half
    long long leftSum = 0, rightSum = 0;

    void balance() {
        while ((int)maxH.size() > (int)minH.size() + 1) {
            int val = maxH.top(); maxH.pop();
            minH.push(val);
            leftSum -= val;
            rightSum += val;
        }
        while ((int)minH.size() > (int)maxH.size()) {
            int val = minH.top(); minH.pop();
            maxH.push(val);
            rightSum -= val;
            leftSum += val;
        }
    }

public:
    void add(int val) {
        if (maxH.empty() || val <= maxH.top()) {
            maxH.push(val);
            leftSum += val;
        } else {
            minH.push(val);
            rightSum += val;
        }
        balance();
    }

    int getMedian() {
        return maxH.top();
    }

    // Cost to make all elements equal to median
    long long getCost() {
        int med = maxH.top();
        long long cost = (long long)med * maxH.size() - leftSum;
        cost += rightSum - (long long)med * minH.size();
        return cost;
    }

    int leftSize() { return maxH.size(); }
    int rightSize() { return minH.size(); }
};

// ═══════════════════════════════════════════════════════════════
// 5. DECREASE KEY SIMULATION
// ═══════════════════════════════════════════════════════════════
/*
  STL priority_queue does NOT support decrease_key.

  Workaround 1: Lazy deletion (push new, mark old as invalid)
    Used in Dijkstra: push (newDist, node), skip if dist[node] < popped dist

  Workaround 2: Use std::set as priority queue
    set supports insert O(log n) and erase O(log n)
    Decrease key = erase old + insert new

  Comparison:
  ┌────────────────────────┬──────────────┬──────────────────────┐
  │ Method                 │ Time         │ Complexity           │
  ├────────────────────────┼──────────────┼──────────────────────┤
  │ PQ + lazy delete       │ O(E log V)   │ Simple, slight waste │
  │ set as PQ              │ O(E log V)   │ Clean decrease-key   │
  │ Indexed PQ (custom)    │ O(E log V)   │ Optimal but complex  │
  │ Fibonacci heap         │ O(V log V+E) │ Theoretical best     │
  └────────────────────────┴──────────────┴──────────────────────┘
*/

void dijkstraWithSet() {
    cout << "═══ DIJKSTRA WITH SET (DECREASE KEY) ═══\n";

    int n = 4;
    vector<vector<pair<int,int>>> adj(n);
    adj[0] = {{1,1},{2,4}};
    adj[1] = {{2,2},{3,6}};
    adj[2] = {{3,3}};

    vector<int> dist(n, INT_MAX);
    set<pair<int,int>> pq;  // (distance, node)

    dist[0] = 0;
    pq.insert({0, 0});

    while (!pq.empty()) {
        auto [d, u] = *pq.begin();
        pq.erase(pq.begin());

        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                // Decrease key: erase old, insert new
                pq.erase({dist[v], v});
                dist[v] = dist[u] + w;
                pq.insert({dist[v], v});
            }
        }
    }

    cout << "  Distances from 0: ";
    for (int i = 0; i < n; i++) cout << "d[" << i << "]=" << dist[i] << " ";
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  CUSTOM COMPARATOR + HEAP PAIRS + DOUBLE HEAP            ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Custom comparator
    cout << "═══ CUSTOM COMPARATOR STRUCT ═══\n";
    priority_queue<Task, vector<Task>, TaskCompare> taskPQ;
    taskPQ.push({"Debug", 3, 5});
    taskPQ.push({"Feature", 5, 10});
    taskPQ.push({"Hotfix", 5, 2});
    taskPQ.push({"Test", 1, 3});

    cout << "  Tasks (highest priority, earliest deadline):\n";
    while (!taskPQ.empty()) {
        auto& t = taskPQ.top();
        cout << "    " << t.name << " (pri=" << t.priority << ", dl=" << t.deadline << ")\n";
        taskPQ.pop();
    }
    cout << "\n";

    heapWithPairs();
    heapWithLambda();

    // Double Heap
    cout << "═══ DOUBLE HEAP (RUNNING MEDIAN + COST) ═══\n";
    DoubleHeap dh;
    vector<int> nums = {1, 3, 6, 2, 8};
    for (int i = 0; i < (int)nums.size(); i++) {
        dh.add(nums[i]);
        cout << "  After adding " << nums[i]
             << ": median=" << dh.getMedian()
             << ", cost=" << dh.getCost() << "\n";
    }
    cout << "\n";

    dijkstraWithSet();

    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "KEY COMPARATOR RULES:\n";
    cout << "  sort:  comp(a,b)=true → a comes BEFORE b\n";
    cout << "  PQ:    comp(a,b)=true → a has LOWER priority (b on top)\n";
    cout << "  They are OPPOSITE!\n\n";
    cout << "PRACTICE:\n";
    cout << "  CSES 1077 — Sliding Window Cost\n";
    cout << "  LC 295  — Find Median from Data Stream\n";
    cout << "  LC 480  — Sliding Window Median\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

