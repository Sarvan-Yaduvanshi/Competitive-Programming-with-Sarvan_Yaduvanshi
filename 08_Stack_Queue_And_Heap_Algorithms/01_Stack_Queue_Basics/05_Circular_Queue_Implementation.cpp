/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           05 — CIRCULAR QUEUE: IMPLEMENTATION & MODULO ARITHMETIC            ║
║           From Zero to Grandmaster — Complete Foundation                     ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Why Circular Queue?
 2. Circular Indexing with Modulo
 3. Full vs Empty Detection
 4. Implementation
 5. Detailed Dry Run
 6. Double-Ended Circular Queue (Deque concept)

WHY CIRCULAR QUEUE?
──────────────────
  Problem with Linear Queue:
  ┌────┬────┬────┬────┬────┐
  │    │    │ 30 │ 40 │ 50 │   front=2, rear=4
  └────┴────┴────┴────┴────┘
    ↑    ↑
    WASTED! These positions can never be reused.

  Circular Queue wraps around:
  ┌────┬────┬────┬────┬────┐
  │ 60 │ 70 │ 30 │ 40 │ 50 │   front=2, rear=1
  └────┴────┴────┴────┴────┘
    ↑                        ← rear wrapped around using modulo!

CIRCULAR INDEXING:
─────────────────
  The key formula: nextIndex = (currentIndex + 1) % capacity

  For capacity = 5:
    (0+1) % 5 = 1
    (1+1) % 5 = 2
    (2+1) % 5 = 3
    (3+1) % 5 = 4
    (4+1) % 5 = 0  ← WRAPS AROUND to beginning!

  Visual (circular):
         ┌───┐
     ┌───┤ 0 ├───┐
     │   └───┘   │
   ┌─┴─┐       ┌─┴─┐
   │ 4 │       │ 1 │
   └─┬─┘       └─┬─┘
     │   ┌───┐   │
     └───┤ 3 ├───┘
         └─┬─┘
         ┌─┴─┐
         │ 2 │
         └───┘

FULL vs EMPTY DETECTION:
───────────────────────
  Problem: If front == rear, is it full or empty?

  Solution 1: Waste one slot
    Empty: front == rear (no elements)
    Full:  (rear + 1) % cap == front (one slot wasted)
    Usable capacity = cap - 1

  Solution 2: Use a count variable ✅ (our approach)
    Empty: count == 0
    Full:  count == capacity
    Usable capacity = cap (no waste!)

  Solution 3: Use a flag (wasLastOperationEnqueue?)
*/

#include <iostream>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: CIRCULAR QUEUE IMPLEMENTATION
// ═══════════════════════════════════════════════════════════════
/*
  DRY RUN — Capacity=5: enqueue(10,20,30,40,50), dequeue(), dequeue(), enqueue(60,70)

  State format: [front..rear] with circular positions

  Operation    │ front │ rear │ count │ Array State              │ Returns
  ─────────────┼───────┼──────┼───────┼──────────────────────────┼────────
  Initial      │   0   │  -1  │   0   │ [_, _, _, _, _]          │ —
  enqueue(10)  │   0   │   0  │   1   │ [10, _, _, _, _]         │ —
  enqueue(20)  │   0   │   1  │   2   │ [10, 20, _, _, _]        │ —
  enqueue(30)  │   0   │   2  │   3   │ [10, 20, 30, _, _]       │ —
  enqueue(40)  │   0   │   3  │   4   │ [10, 20, 30, 40, _]      │ —
  enqueue(50)  │   0   │   4  │   5   │ [10, 20, 30, 40, 50]     │ — (FULL)
  dequeue()    │   1   │   4  │   4   │ [_, 20, 30, 40, 50]      │ 10
  dequeue()    │   2   │   4  │   3   │ [_, _, 30, 40, 50]       │ 20
  enqueue(60)  │   2   │   0  │   4   │ [60, _, 30, 40, 50]      │ — ← WRAPPED!
  enqueue(70)  │   2   │   1  │   5   │ [60, 70, 30, 40, 50]     │ — (FULL again)

  Visual after wrapping:
  ┌────────────────────────────────────────────┐
  │  Index:   0    1    2    3    4             │
  │         [60] [70] [30] [40] [50]           │
  │               ↑    ↑                       │
  │             rear  front                    │
  │                                            │
  │  Logical order (front→rear):               │
  │  30 → 40 → 50 → 60 → 70                  │
  │                                            │
  │  Circular view:                            │
  │        ┌────┐                              │
  │    ┌───┤ 60 ├───┐                          │
  │    │   └────┘   │                          │
  │  ┌─┴──┐       ┌─┴──┐                      │
  │  │ 50 │       │ 70 │                       │
  │  └─┬──┘       └─┬──┘                      │
  │    │   ┌────┐   │                          │
  │    └───┤ 40 ├───┘                          │
  │        └─┬──┘                              │
  │        ┌─┴──┐                              │
  │        │ 30 │ ← FRONT                     │
  │        └────┘                              │
  └────────────────────────────────────────────┘
*/

class CircularQueue {
private:
    int* arr;
    int frontIdx, rearIdx;
    int capacity;
    int count;

public:
    CircularQueue(int cap) : capacity(cap), frontIdx(0), rearIdx(-1), count(0) {
        arr = new int[capacity];
    }

    ~CircularQueue() {
        delete[] arr;
    }

    // Enqueue: Add at rear (wraps around) — O(1)
    void enqueue(int val) {
        if (isFull()) {
            cout << "  ❌ OVERFLOW! Queue is full (count=" << count << ")\n";
            return;
        }
        rearIdx = (rearIdx + 1) % capacity;  // Circular increment
        arr[rearIdx] = val;
        count++;
    }

    // Dequeue: Remove from front (wraps around) — O(1)
    int dequeue() {
        if (isEmpty()) {
            cout << "  ❌ UNDERFLOW! Queue is empty.\n";
            return -1;
        }
        int val = arr[frontIdx];
        frontIdx = (frontIdx + 1) % capacity;  // Circular increment
        count--;
        return val;
    }

    int front() {
        if (isEmpty()) return -1;
        return arr[frontIdx];
    }

    int rear() {
        if (isEmpty()) return -1;
        return arr[rearIdx];
    }

    bool isEmpty() { return count == 0; }
    bool isFull() { return count == capacity; }
    int size() { return count; }

    void display() {
        if (isEmpty()) {
            cout << "  Queue: (empty)\n";
            return;
        }
        cout << "  FRONT→ ";
        int idx = frontIdx;
        for (int i = 0; i < count; i++) {
            cout << arr[idx];
            if (i < count - 1) cout << " → ";
            idx = (idx + 1) % capacity;
        }
        cout << " ←REAR";
        cout << "  [f=" << frontIdx << " r=" << rearIdx << " cnt=" << count << "]\n";
    }

    // Show raw array for debugging
    void displayRaw() {
        cout << "  Raw: [";
        for (int i = 0; i < capacity; i++) {
            bool inUse = false;
            int idx = frontIdx;
            for (int j = 0; j < count; j++) {
                if (idx == i) { inUse = true; break; }
                idx = (idx + 1) % capacity;
            }
            if (inUse) cout << arr[i];
            else cout << "_";
            if (i < capacity - 1) cout << ", ";
        }
        cout << "]\n";
    }
};

// ═══════════════════════════════════════════════════════════════
// SECTION 2: DEMONSTRATION
// ═══════════════════════════════════════════════════════════════

void demonstrateCircularQueue() {
    cout << "═══ CIRCULAR QUEUE DEMONSTRATION (capacity=5) ═══\n\n";

    CircularQueue cq(5);

    // Fill the queue
    cout << "Enqueue 10, 20, 30, 40, 50:\n";
    for (int v : {10, 20, 30, 40, 50}) {
        cq.enqueue(v);
    }
    cq.display();
    cq.displayRaw();
    cout << "Full: " << (cq.isFull() ? "YES" : "NO") << "\n\n";

    // Test overflow
    cout << "Try enqueue(60) on full queue:\n";
    cq.enqueue(60);

    // Dequeue some
    cout << "\nDequeue twice:\n";
    cout << "  Dequeued: " << cq.dequeue() << "\n";
    cout << "  Dequeued: " << cq.dequeue() << "\n";
    cq.display();
    cq.displayRaw();

    // Enqueue with wrap-around
    cout << "\nEnqueue 60, 70 (wraps around!):\n";
    cq.enqueue(60);
    cq.enqueue(70);
    cq.display();
    cq.displayRaw();
    cout << "Full: " << (cq.isFull() ? "YES" : "NO") << "\n";

    cout << "\nFront: " << cq.front() << ", Rear: " << cq.rear() << "\n";

    // Drain
    cout << "\nDrain all:\n";
    while (!cq.isEmpty()) {
        cout << "  " << cq.dequeue();
        if (!cq.isEmpty()) cout << " → ";
    }
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: MODULO ARITHMETIC EXPLANATION
// ═══════════════════════════════════════════════════════════════

void demonstrateModuloArithmetic() {
    cout << "═══ MODULO ARITHMETIC FOR CIRCULAR INDEXING ═══\n\n";

    int cap = 5;
    cout << "Capacity = " << cap << "\n";
    cout << "Formula: next = (current + 1) % capacity\n\n";

    cout << "  Current → Next\n";
    cout << "  ───────────────\n";
    for (int i = 0; i < 2 * cap; i++) {
        int next = (i + 1) % cap;
        cout << "  " << i << " → " << next;
        if (i == cap - 1) cout << "  ← WRAPS AROUND!";
        cout << "\n";
    }

    cout << "\n  This is how we achieve circular behavior\n";
    cout << "  without any conditional checks!\n\n";

    cout << "  Mathematical proof of wrap-around:\n";
    cout << "  ─────────────────────────────────\n";
    cout << "  For cap = 5:\n";
    cout << "    index:    0  1  2  3  4  5  6  7  8  9\n";
    cout << "    % 5:      0  1  2  3  4  0  1  2  3  4\n";
    cout << "    Pattern repeats every 'cap' steps!\n\n";
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  CIRCULAR QUEUE IMPLEMENTATION & MODULO ARITHMETIC       ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    demonstrateModuloArithmetic();
    demonstrateCircularQueue();

    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "COMPARISON TABLE:\n";
    cout << "───────────────────────────────────────────────────────────\n";
    cout << "┌────────────────┬───────────┬───────────┬──────────────┐\n";
    cout << "│ Feature        │ Linear Q  │ Shifting  │ Circular Q   │\n";
    cout << "├────────────────┼───────────┼───────────┼──────────────┤\n";
    cout << "│ Enqueue        │ O(1)      │ O(1)      │ O(1)         │\n";
    cout << "│ Dequeue        │ O(1)*     │ O(n)      │ O(1)         │\n";
    cout << "│ Space waste    │ HIGH      │ NONE      │ NONE         │\n";
    cout << "│ Reuse slots    │ NO        │ YES       │ YES          │\n";
    cout << "│ Wrap around    │ NO        │ NO        │ YES          │\n";
    cout << "└────────────────┴───────────┴───────────┴──────────────┘\n";
    cout << "  * O(1) but wastes space\n\n";
    cout << "PRACTICE PROBLEMS:\n";
    cout << "───────────────────\n";
    cout << "1. LC 622  — Design Circular Queue\n";
    cout << "2. LC 641  — Design Circular Deque\n";
    cout << "3. LC 346  — Moving Average from Data Stream\n";
    cout << "4. Implement circular buffer for producer-consumer pattern\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

