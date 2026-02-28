/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           04 — CUSTOM COMPARATORS (All Methods)                            ║
║           05 — ADAPTOR PATTERNS FOR CP                                     ║
║           From Zero to Grandmaster                                         ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

  This file covers all comparator methods + advanced CP patterns:
  monotonic stack/queue, lazy deletion PQ, median stream.
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: ALL COMPARATOR METHODS
// ═══════════════════════════════════════════════════════════════

// Method 1: Functor (struct with operator())
struct CompareByAbs {
    bool operator()(int a, int b) const {
        return abs(a) > abs(b);  // Min heap by absolute value
    }
};

// Method 2: For custom structs with operator<
struct Task {
    int priority, id;
    string name;
    // Default: max heap uses operator<
    bool operator<(const Task& o) const {
        if (priority != o.priority) return priority < o.priority;
        return id > o.id;  // Lower id = higher priority on tie
    }
};

void allComparatorMethods() {
    cout << "═══ ALL COMPARATOR METHODS ═══\n\n";

    // Method 1: Functor
    priority_queue<int, vector<int>, CompareByAbs> pq1;
    for (int x : {-5, 2, -8, 1, -9, 3}) pq1.push(x);
    cout << "Functor (min by |x|): ";
    while (!pq1.empty()) { cout << pq1.top() << " "; pq1.pop(); }
    cout << "\n";

    // Method 2: Built-in greater/less
    priority_queue<int, vector<int>, greater<int>> minPQ;
    for (int x : {5, 2, 8, 1, 9}) minPQ.push(x);
    cout << "greater<int> (min heap): ";
    while (!minPQ.empty()) { cout << minPQ.top() << " "; minPQ.pop(); }
    cout << "\n";

    // Method 3: Lambda
    auto cmp = [](const pair<int,int>& a, const pair<int,int>& b) {
        return a.first + a.second > b.first + b.second;
    };
    priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> pq3(cmp);
    pq3.push({1, 5});
    pq3.push({3, 2});
    pq3.push({2, 1});
    cout << "Lambda (min sum): ";
    while (!pq3.empty()) {
        auto [a, b] = pq3.top(); pq3.pop();
        cout << "(" << a << "+" << b << "=" << a+b << ") ";
    }
    cout << "\n";

    // Method 4: Struct with operator<
    priority_queue<Task> taskPQ;
    taskPQ.push({3, 1, "Low"});
    taskPQ.push({5, 2, "High"});
    taskPQ.push({5, 3, "High2"});
    taskPQ.push({1, 4, "Critical"});
    cout << "Struct operator<: ";
    while (!taskPQ.empty()) {
        auto t = taskPQ.top(); taskPQ.pop();
        cout << t.name << "(p=" << t.priority << ") ";
    }
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: LAZY DELETION PRIORITY QUEUE
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM: PQ doesn't support delete(x). How to handle?

 APPROACH: "Lazy deletion"
   1. Mark elements as deleted (using a set or counter)
   2. When popping, skip deleted elements
   3. Effective deletion without modifying the heap!
*/

void lazyDeletionPQ() {
    cout << "═══ LAZY DELETION PQ ═══\n\n";

    priority_queue<int> pq;  // Max heap
    unordered_map<int, int> deleted;  // deleted[x] = count of pending deletions

    // Add elements
    for (int x : {5, 3, 8, 1, 9, 2, 7}) pq.push(x);

    // "Delete" 8 and 5 lazily
    deleted[8]++;
    deleted[5]++;

    cout << "Elements in PQ with 8,5 lazily deleted:\n";
    cout << "Pop order: ";

    while (!pq.empty()) {
        int top = pq.top();
        pq.pop();
        if (deleted[top] > 0) {
            deleted[top]--;
            continue;  // Skip deleted
        }
        cout << top << " ";
    }
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: MEDIAN STREAM (TWO HEAPS)
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM: Maintain median of a stream of numbers.

 APPROACH: Two heaps
   maxHeap (lower half) — contains smaller half, max on top
   minHeap (upper half) — contains larger half, min on top

   Balance: |maxHeap.size() - minHeap.size()| ≤ 1
   Median: top of maxHeap (if odd count)
           avg of both tops (if even count)
*/

void medianStream() {
    cout << "═══ MEDIAN STREAM (TWO HEAPS) ═══\n\n";

    priority_queue<int> maxHeap;                              // Lower half
    priority_queue<int, vector<int>, greater<int>> minHeap;   // Upper half

    auto addNum = [&](int x) {
        if (maxHeap.empty() || x <= maxHeap.top())
            maxHeap.push(x);
        else
            minHeap.push(x);

        // Balance
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    };

    auto getMedian = [&]() -> double {
        if (maxHeap.size() > minHeap.size()) return maxHeap.top();
        return (maxHeap.top() + minHeap.top()) / 2.0;
    };

    vector<int> stream = {5, 15, 1, 3, 8, 7, 9, 10, 6, 2};
    cout << "Stream:  ";
    for (int x : stream) cout << x << " ";
    cout << "\nMedians: ";
    for (int x : stream) {
        addNum(x);
        cout << fixed << setprecision(1) << getMedian() << " ";
    }
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: MONOTONIC STACK — NEXT SMALLER ELEMENT
// ═══════════════════════════════════════════════════════════════

void nextSmaller() {
    cout << "═══ NEXT SMALLER ELEMENT ═══\n\n";

    vector<int> arr = {4, 8, 5, 2, 25};
    int n = arr.size();
    vector<int> nse(n, -1);

    stack<int> st;  // Increasing stack
    for (int i = 0; i < n; i++) {
        while (!st.empty() && arr[st.top()] > arr[i]) {
            nse[st.top()] = arr[i];
            st.pop();
        }
        st.push(i);
    }

    cout << "Array: ";
    for (int x : arr) cout << x << "\t";
    cout << "\nNSE:   ";
    for (int x : nse) cout << x << "\t";
    cout << "\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    allComparatorMethods();
    lazyDeletionPQ();
    medianStream();
    nextSmaller();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. Four comparator methods: functor, greater<>, lambda, operator<\n";
    cout << "2. Lazy deletion: mark deleted, skip on pop\n";
    cout << "3. Median stream: maxHeap (lower) + minHeap (upper)\n";
    cout << "4. Monotonic stack: O(n) for next greater/smaller\n";
    cout << "5. These patterns appear in 30%+ of medium-hard CP problems\n";

    return 0;
}

