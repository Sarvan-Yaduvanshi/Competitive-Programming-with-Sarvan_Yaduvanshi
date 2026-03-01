/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — ADVANCED HEAP: LAZY DELETION, INDEXED PQ, TWO-HEAP            ║
║           From Zero to Grandmaster — Advanced Heap Techniques               ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Custom Comparator Struct (Advanced)
 2. Lazy Deletion in Heap
 3. Indexed Priority Queue
 4. Two-Heap (Double Heap) Technique
 5. Sliding Window Median

LAZY DELETION:
─────────────
  Problem: STL priority_queue doesn't support delete(key) or decrease-key.
  Solution: Mark elements as "deleted" and skip them when popping.

  ┌──────────────────────────────────────────────────────┐
  │  Instead of actually removing from heap:              │
  │    1. Keep a "to_delete" set/map                     │
  │    2. When popping, check if top is marked           │
  │    3. If marked, pop and continue (lazy cleanup)     │
  │                                                       │
  │  Use case: Sliding window problems, event simulation  │
  └──────────────────────────────────────────────────────┘

INDEXED PRIORITY QUEUE:
──────────────────────
  A priority queue that supports:
    - insert(key, priority)
    - extractMin/Max()
    - decreaseKey(key, newPriority)
    - increaseKey(key, newPriority)
    - delete(key)
    - contains(key)

  Used in: Dijkstra (efficient), Prim's MST

  Implementation: Heap array + position map + reverse position map

TWO-HEAP TECHNIQUE:
──────────────────
  Split data into two halves using two heaps:
    Left half  → Max Heap (get largest of small half)
    Right half → Min Heap (get smallest of large part)

  Applications:
    - Find Median (LC 295)
    - Sliding Window Median (LC 480)
    - Balance partitioning
*/

#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <set>
#include <functional>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: LAZY DELETION PATTERN
// ═══════════════════════════════════════════════════════════════
/*
  Example: Maintain dynamic max where elements can be added and removed.

  DRY RUN:
    add(5), add(3), add(8), getMax()→8
    remove(8), getMax()→5
    add(10), remove(3), getMax()→10

  With lazy deletion:
    heap = [8,5,3], deleted = {}
    remove(8): deleted = {8:1}
    getMax(): pop 8 (deleted), pop 5 → return 5
    heap = [5,3], deleted = {}
*/

class LazyMaxHeap {
    priority_queue<int> heap;
    unordered_map<int, int> toDelete;  // value → count to delete

    void cleanTop() {
        while (!heap.empty() && toDelete.count(heap.top()) && toDelete[heap.top()] > 0) {
            toDelete[heap.top()]--;
            if (toDelete[heap.top()] == 0) toDelete.erase(heap.top());
            heap.pop();
        }
    }

public:
    void add(int val) { heap.push(val); }

    void remove(int val) { toDelete[val]++; }

    int getMax() {
        cleanTop();
        return heap.empty() ? -1 : heap.top();
    }

    int extractMax() {
        cleanTop();
        if (heap.empty()) return -1;
        int val = heap.top();
        heap.pop();
        return val;
    }

    int size() {
        // Note: this is approximate without full cleanup
        int deletedCount = 0;
        for (auto& [k, v] : toDelete) deletedCount += v;
        return (int)heap.size() - deletedCount;
    }
};

// ═══════════════════════════════════════════════════════════════
// SECTION 2: INDEXED PRIORITY QUEUE (MIN)
// ═══════════════════════════════════════════════════════════════
/*
  Supports decrease-key in O(log n) — essential for Dijkstra.

  Three arrays:
    heap[]:    the actual heap (stores keys)
    pos[key]:  position of key in heap array
    val[key]:  priority/value of key

  Operations:
    insert(key, priority): Add key with given priority
    decreaseKey(key, newPri): Decrease priority, bubble up
    extractMin(): Remove and return key with smallest priority
*/

class IndexedMinPQ {
    int maxN;
    int sz;
    vector<int> heap;     // heap[i] = key at position i
    vector<int> pos;      // pos[key] = position in heap (-1 if not present)
    vector<int> vals;     // vals[key] = priority value

    void swim(int i) {
        while (i > 0 && vals[heap[(i-1)/2]] > vals[heap[i]]) {
            swap(heap[(i-1)/2], heap[i]);
            pos[heap[(i-1)/2]] = (i-1)/2;
            pos[heap[i]] = i;
            i = (i-1)/2;
        }
    }

    void sink(int i) {
        while (2*i+1 < sz) {
            int j = 2*i+1;
            if (j+1 < sz && vals[heap[j+1]] < vals[heap[j]]) j++;
            if (vals[heap[i]] <= vals[heap[j]]) break;
            swap(heap[i], heap[j]);
            pos[heap[i]] = i;
            pos[heap[j]] = j;
            i = j;
        }
    }

public:
    IndexedMinPQ(int maxN) : maxN(maxN), sz(0), heap(maxN), pos(maxN, -1), vals(maxN, INT_MAX) {}

    bool contains(int key) { return pos[key] != -1; }
    bool empty() { return sz == 0; }

    void insert(int key, int val) {
        vals[key] = val;
        heap[sz] = key;
        pos[key] = sz;
        swim(sz);
        sz++;
    }

    void decreaseKey(int key, int newVal) {
        vals[key] = newVal;
        swim(pos[key]);
    }

    pair<int,int> extractMin() {
        int key = heap[0];
        int val = vals[key];
        sz--;
        swap(heap[0], heap[sz]);
        pos[heap[0]] = 0;
        pos[key] = -1;
        sink(0);
        return {key, val};
    }

    int minVal() { return vals[heap[0]]; }
    int minKey() { return heap[0]; }
};

// ═══════════════════════════════════════════════════════════════
// SECTION 3: TWO-HEAP — SLIDING WINDOW MEDIAN (LC 480)
// ═══════════════════════════════════════════════════════════════
/*
  Sliding window of size k, find median of each window.
  Use two heaps + lazy deletion.

  DRY RUN: [1,3,-1,-3,5,3,6,7], k=3
  Window [1,3,-1]:  sorted [-1,1,3] → median=1
  Window [3,-1,-3]: sorted [-3,-1,3] → median=-1
  Window [-1,-3,5]: sorted [-3,-1,5] → median=-1
  ...
*/

vector<double> medianSlidingWindow(vector<int>& nums, int k) {
    // Use multiset for O(log n) insert/delete/find
    multiset<int> left, right;  // left = smaller half, right = larger half
    vector<double> result;

    auto balance = [&]() {
        while (left.size() > right.size() + 1) {
            right.insert(*left.rbegin());
            left.erase(prev(left.end()));
        }
        while (right.size() > left.size()) {
            left.insert(*right.begin());
            right.erase(right.begin());
        }
    };

    auto getMedian = [&]() -> double {
        if (k % 2 == 1) return *left.rbegin();
        return ((double)*left.rbegin() + *right.begin()) / 2.0;
    };

    for (int i = 0; i < (int)nums.size(); i++) {
        // Add nums[i]
        if (left.empty() || nums[i] <= *left.rbegin())
            left.insert(nums[i]);
        else
            right.insert(nums[i]);

        // Remove nums[i-k] (sliding window)
        if (i >= k) {
            int toRemove = nums[i - k];
            if (left.count(toRemove))
                left.erase(left.find(toRemove));
            else
                right.erase(right.find(toRemove));
        }

        balance();

        if (i >= k - 1) result.push_back(getMedian());
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  ADVANCED HEAP: LAZY DELETE, INDEXED PQ, TWO-HEAP        ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Lazy Deletion
    cout << "═══ LAZY DELETION ═══\n";
    LazyMaxHeap lh;
    lh.add(5); lh.add(3); lh.add(8);
    cout << "  Max after add(5,3,8): " << lh.getMax() << "\n";
    lh.remove(8);
    cout << "  Max after remove(8): " << lh.getMax() << "\n";
    lh.add(10);
    cout << "  Max after add(10): " << lh.getMax() << "\n\n";

    // Indexed PQ
    cout << "═══ INDEXED PRIORITY QUEUE ═══\n";
    IndexedMinPQ ipq(10);
    ipq.insert(0, 10);
    ipq.insert(1, 5);
    ipq.insert(2, 15);
    ipq.insert(3, 3);
    cout << "  Min key: " << ipq.minKey() << " (val=" << ipq.minVal() << ")\n";
    ipq.decreaseKey(2, 1);
    cout << "  After decreaseKey(2, 1): min key=" << ipq.minKey() << "\n";
    auto [k, v] = ipq.extractMin();
    cout << "  ExtractMin: key=" << k << " val=" << v << "\n\n";

    // Sliding Window Median
    cout << "═══ SLIDING WINDOW MEDIAN (LC 480) ═══\n";
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    auto medians = medianSlidingWindow(nums, 3);
    cout << "  Array: [1,3,-1,-3,5,3,6,7], k=3\n  Medians: ";
    for (double m : medians) cout << m << " ";
    cout << "\n";

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE:\n";
    cout << "  LC 480  — Sliding Window Median\n";
    cout << "  LC 295  — Find Median from Data Stream\n";
    cout << "  LC 1792 — Maximum Average Pass Ratio\n";
    cout << "  Dijkstra with Indexed PQ for optimal performance\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

