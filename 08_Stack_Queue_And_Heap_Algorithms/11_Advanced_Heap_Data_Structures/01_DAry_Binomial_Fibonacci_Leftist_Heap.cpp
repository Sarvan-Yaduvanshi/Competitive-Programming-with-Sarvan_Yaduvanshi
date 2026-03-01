/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — D-ARY HEAP, BINOMIAL HEAP, FIBONACCI HEAP CONCEPTS            ║
║           From Zero to Grandmaster — Advanced Heap Data Structures          ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. D-ary Heap
 2. Binomial Heap (Concept + Implementation)
 3. Fibonacci Heap (Concept)
 4. Pairing Heap (Concept)
 5. Leftist & Skew Heap (Concept)

D-ARY HEAP:
──────────
  Generalization of binary heap: each node has D children.

  Binary heap: D=2    →  height = log₂(n)
  D-ary heap:  D=d    →  height = log_d(n)

  ┌────────────────────────────────────────────────────┐
  │ D=2 (binary):     D=3 (ternary):    D=4:          │
  │      10                 10              10          │
  │     / \              /  |  \         / | | \        │
  │    8   7            8   7   6      8  7  6  5      │
  │   / \              /|\ /|\                          │
  │  5   3            5 3 2 1 4                        │
  │                                                     │
  │ Height comparison for n=1000000:                   │
  │   D=2: ≈20,  D=4: ≈10,  D=8: ≈7                  │
  └────────────────────────────────────────────────────┘

  Parent of i:      (i - 1) / D
  j-th child of i:  D * i + j + 1   (j = 0,1,...,D-1)

  Trade-off:
    Higher D → shorter tree → fewer swaps in heapifyDown
    Higher D → more comparisons per level (find min among D children)

  Optimal for Dijkstra: D = E/V (edge-to-vertex ratio)

  Insert:       O(log_d(n))    — faster with higher D
  ExtractMin:   O(d × log_d(n)) — more comparisons per level
  DecreaseKey:  O(log_d(n))

BINOMIAL HEAP:
─────────────
  A collection of binomial trees satisfying min-heap property.

  Binomial tree B_k:
    B_0: single node
    B_k: B_{k-1} attached as leftmost child of another B_{k-1}

  Properties:
    B_k has 2^k nodes
    B_k has height k
    B_k has C(k,i) nodes at depth i

  B_0   B_1    B_2        B_3
   o     o      o           o
         |     /|          /|\
         o    o  o        o  o  o
              |          /|  |
              o         o  o o
                        |
                        o

  Key operations:
    merge:       O(log n)  ← THE key advantage!
    insert:      O(log n) amortized O(1)
    extractMin:  O(log n)
    decreaseKey: O(log n)

FIBONACCI HEAP:
──────────────
  The theoretically optimal heap for graph algorithms.

  ┌────────────────┬──────────┬───────────────────┐
  │ Operation      │ Binary   │ Fibonacci         │
  ├────────────────┼──────────┼───────────────────┤
  │ Insert         │ O(log n) │ O(1) amortized    │
  │ Find Min       │ O(1)     │ O(1)              │
  │ Extract Min    │ O(log n) │ O(log n) amortized│
  │ Decrease Key   │ O(log n) │ O(1) amortized    │
  │ Merge          │ O(n)     │ O(1)              │
  │ Delete         │ O(log n) │ O(log n) amortized│
  └────────────────┴──────────┴───────────────────┘

  Why it matters:
    Dijkstra with Fibonacci heap: O(V log V + E)
    Dijkstra with binary heap:    O((V+E) log V)

  In practice, Fibonacci heap has high constant factors.
  For competitive programming, binary heap (priority_queue) is usually enough.

LEFTIST HEAP:
────────────
  Mergeable heap where the left subtree is always at least as "heavy"
  as the right subtree. Merge is O(log n).

  s-value (shortest path to null descendant):
    s(null) = 0
    s(node) = 1 + min(s(left), s(right))

  Rule: s(left) >= s(right) for every node
  If violated, swap children.

SKEW HEAP:
─────────
  Self-adjusting version of leftist heap.
  On every merge, ALWAYS swap children (no s-value tracking).
  Amortized O(log n) merge.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// D-ARY HEAP IMPLEMENTATION
// ═══════════════════════════════════════════════════════════════

class DAryMinHeap {
    int D;
    vector<int> heap;

    int parent(int i) { return (i - 1) / D; }
    int child(int i, int j) { return D * i + j + 1; }  // j-th child (0-indexed)

    void heapifyUp(int idx) {
        while (idx > 0 && heap[parent(idx)] > heap[idx]) {
            swap(heap[parent(idx)], heap[idx]);
            idx = parent(idx);
        }
    }

    void heapifyDown(int idx) {
        while (true) {
            int smallest = idx;
            for (int j = 0; j < D; j++) {
                int c = child(idx, j);
                if (c < (int)heap.size() && heap[c] < heap[smallest]) {
                    smallest = c;
                }
            }
            if (smallest == idx) break;
            swap(heap[idx], heap[smallest]);
            idx = smallest;
        }
    }

public:
    DAryMinHeap(int d) : D(d) {}

    void insert(int val) {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }

    int extractMin() {
        int minVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) heapifyDown(0);
        return minVal;
    }

    int getMin() { return heap[0]; }
    bool empty() { return heap.empty(); }
    int size() { return heap.size(); }
};

// ═══════════════════════════════════════════════════════════════
// LEFTIST HEAP (MERGEABLE MIN HEAP)
// ═══════════════════════════════════════════════════════════════

struct LeftistNode {
    int val, rank;
    LeftistNode *left, *right;
    LeftistNode(int v) : val(v), rank(1), left(nullptr), right(nullptr) {}
};

LeftistNode* mergeLeftist(LeftistNode* a, LeftistNode* b) {
    if (!a) return b;
    if (!b) return a;

    // Ensure a has smaller root
    if (a->val > b->val) swap(a, b);

    // Merge b with right subtree of a
    a->right = mergeLeftist(a->right, b);

    // Maintain leftist property: rank(left) >= rank(right)
    if (!a->left || (a->right && a->left->rank < a->right->rank)) {
        swap(a->left, a->right);
    }

    // Update rank
    a->rank = a->right ? a->right->rank + 1 : 1;
    return a;
}

class LeftistHeap {
    LeftistNode* root;

    void freeAll(LeftistNode* node) {
        if (!node) return;
        freeAll(node->left);
        freeAll(node->right);
        delete node;
    }

public:
    LeftistHeap() : root(nullptr) {}
    ~LeftistHeap() { freeAll(root); }

    void insert(int val) { root = mergeLeftist(root, new LeftistNode(val)); }

    int extractMin() {
        int minVal = root->val;
        LeftistNode* oldRoot = root;
        root = mergeLeftist(root->left, root->right);
        delete oldRoot;
        return minVal;
    }

    void merge(LeftistHeap& other) {
        root = mergeLeftist(root, other.root);
        other.root = nullptr;
    }

    int getMin() { return root->val; }
    bool empty() { return root == nullptr; }
};

// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  ADVANCED HEAP DATA STRUCTURES                           ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // D-ary Heap
    cout << "═══ 3-ARY (TERNARY) MIN HEAP ═══\n";
    DAryMinHeap dHeap(3);
    for (int v : {10, 30, 5, 20, 15, 1, 8}) {
        dHeap.insert(v);
    }
    cout << "  Extract min order: ";
    while (!dHeap.empty()) {
        cout << dHeap.extractMin() << " ";
    }
    cout << "\n\n";

    // Leftist Heap
    cout << "═══ LEFTIST HEAP (MERGEABLE) ═══\n";
    LeftistHeap lh1, lh2;
    for (int v : {10, 30, 5}) lh1.insert(v);
    for (int v : {20, 2, 15}) lh2.insert(v);

    cout << "  Heap1 min: " << lh1.getMin() << "\n";
    cout << "  Heap2 min: " << lh2.getMin() << "\n";

    lh1.merge(lh2);
    cout << "  After merge, min: " << lh1.getMin() << "\n";
    cout << "  Extract all: ";
    while (!lh1.empty()) {
        cout << lh1.extractMin() << " ";
    }
    cout << "\n";

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "HEAP COMPARISON:\n";
    cout << "┌──────────────┬────────┬────────┬────────┬────────┐\n";
    cout << "│ Operation    │ Binary │ D-ary  │ Binomi │ Fib    │\n";
    cout << "├──────────────┼────────┼────────┼────────┼────────┤\n";
    cout << "│ Insert       │O(logn) │O(log_d)│O(logn) │ O(1)*  │\n";
    cout << "│ ExtractMin   │O(logn) │O(dlogd)│O(logn) │O(logn)*│\n";
    cout << "│ DecreaseKey  │O(logn) │O(log_d)│O(logn) │ O(1)*  │\n";
    cout << "│ Merge        │ O(n)   │ O(n)   │O(logn) │ O(1)   │\n";
    cout << "└──────────────┴────────┴────────┴────────┴────────┘\n";
    cout << "  * amortized\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

