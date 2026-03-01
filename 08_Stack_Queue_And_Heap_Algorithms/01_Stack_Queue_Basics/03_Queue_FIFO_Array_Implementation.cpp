/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           03 — QUEUE: FIFO CONCEPT & ARRAY IMPLEMENTATION                    ║
║           From Zero to Grandmaster — Complete Foundation                     ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. What is a Queue?
 2. FIFO (First In, First Out) Concept
 3. Queue Operations
 4. Array-Based Implementation (Linear)
 5. Front / Rear Pointer Logic
 6. Queue Overflow & Underflow
 7. Applications Overview
 8. Dry Run with Visualization

WHAT IS A QUEUE?
────────────────
A Queue is a linear data structure that follows the FIFO (First In, First Out)
principle. Think of it like a line at a ticket counter:
  • People JOIN at the REAR (enqueue)
  • People LEAVE from the FRONT (dequeue)
  • The person who came FIRST leaves FIRST

Real-World Analogies:
  🎫 Ticket counter line  — First person in line gets served first
  🖨️  Print queue          — First document sent prints first
  📱 Message queue         — Messages processed in order received
  🚗 Traffic signal        — Cars cross in arrival order
  💻 CPU task scheduling   — Processes run in FIFO order
  📞 Call center           — Calls answered in received order

FIFO VISUALIZATION:
──────────────────
  Enqueue 10, 20, 30:

  FRONT                         REAR
    ↓                             ↓
  ┌────┬────┬────┐
  │ 10 │ 20 │ 30 │
  └────┴────┴────┘
  First in          Last in

  Dequeue() → returns 10 (the FIRST element enqueued)

  FRONT              REAR
    ↓                  ↓
  ┌────┬────┐
  │ 20 │ 30 │
  └────┴────┘

QUEUE OPERATIONS & COMPLEXITY:
─────────────────────────────
  ┌────────────────────┬──────────┬──────────────────────────┐
  │ Operation          │  Time    │ Description              │
  ├────────────────────┼──────────┼──────────────────────────┤
  │ enqueue(x)         │  O(1)    │ Add x at rear            │
  │ dequeue()          │  O(1)*   │ Remove from front        │
  │ front() / peek()   │  O(1)    │ View front element       │
  │ rear()             │  O(1)    │ View rear element        │
  │ isEmpty()          │  O(1)    │ Check if empty           │
  │ isFull()           │  O(1)    │ Check if full            │
  │ size()             │  O(1)    │ Number of elements       │
  └────────────────────┴──────────┴──────────────────────────┘
  * O(1) with circular indexing, O(n) with shifting in linear array

FRONT / REAR POINTER LOGIC:
───────────────────────────
  Linear Array Queue:
  ┌────┬────┬────┬────┬────┐
  │ 10 │ 20 │ 30 │    │    │
  └────┴────┴────┴────┴────┘
    ↑              ↑
  front=0       rear=2

  Enqueue(40):
  ┌────┬────┬────┬────┬────┐
  │ 10 │ 20 │ 30 │ 40 │    │
  └────┴────┴────┴────┴────┘
    ↑                   ↑
  front=0            rear=3

  Dequeue() → 10:
  ┌────┬────┬────┬────┬────┐
  │    │ 20 │ 30 │ 40 │    │
  └────┴────┴────┴────┴────┘
         ↑              ↑
       front=1       rear=3

  PROBLEM: After many dequeue operations, front moves right.
  Space at beginning is WASTED! (We can't reuse it)
  SOLUTION: Use CIRCULAR QUEUE (next file)

OVERFLOW & UNDERFLOW:
────────────────────
  OVERFLOW:  rear == capacity - 1 → Queue is full
  UNDERFLOW: front > rear (or front == -1) → Queue is empty

APPLICATIONS OF QUEUE:
─────────────────────
  1. BFS (Breadth-First Search)
  2. Level-order tree traversal
  3. CPU Scheduling (FCFS)
  4. Printer queue
  5. Message/Event queue
  6. Sliding window problems
  7. Cache implementation
  8. Network packet handling
  9. Order processing systems
*/

#include <iostream>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: LINEAR QUEUE USING ARRAY
// ═══════════════════════════════════════════════════════════════
/*
  Memory Layout:
  ┌──────────────────────────────────────┐
  │  Queue Object                        │
  │  arr[0] arr[1] arr[2] ... arr[N-1]  │
  │  front = -1 (empty)                  │
  │  rear  = -1 (empty)                  │
  │  capacity = MAX_SIZE                 │
  └──────────────────────────────────────┘

  Empty state:  front = rear = -1
  After first enqueue: front = rear = 0
  After dequeue: front++ (shift front forward)

  Drawback: Space before front is permanently wasted.
*/

class LinearQueue {
private:
    static const int MAX_SIZE = 1000;
    int arr[MAX_SIZE];
    int frontIdx, rearIdx;

public:
    LinearQueue() : frontIdx(-1), rearIdx(-1) {}

    // Enqueue: Add element at rear — O(1)
    /*
      Case 1: Queue empty → set front = rear = 0, store value
      Case 2: Queue not full → rear++, store value
      Case 3: Queue full → OVERFLOW
    */
    void enqueue(int val) {
        if (isFull()) {
            cout << "  ❌ OVERFLOW! Queue is full.\n";
            return;
        }
        if (isEmpty()) {
            frontIdx = 0;
        }
        arr[++rearIdx] = val;
    }

    // Dequeue: Remove element from front — O(1)
    /*
      Case 1: Queue empty → UNDERFLOW
      Case 2: Only one element → reset front = rear = -1
      Case 3: Multiple elements → front++
    */
    int dequeue() {
        if (isEmpty()) {
            cout << "  ❌ UNDERFLOW! Queue is empty.\n";
            return -1;
        }
        int val = arr[frontIdx];
        if (frontIdx == rearIdx) {
            // Last element — reset queue
            frontIdx = rearIdx = -1;
        } else {
            frontIdx++;
        }
        return val;
    }

    int front() {
        if (isEmpty()) {
            cout << "  ❌ Queue is empty.\n";
            return -1;
        }
        return arr[frontIdx];
    }

    int rear() {
        if (isEmpty()) {
            cout << "  ❌ Queue is empty.\n";
            return -1;
        }
        return arr[rearIdx];
    }

    bool isEmpty() { return frontIdx == -1; }
    bool isFull() { return rearIdx == MAX_SIZE - 1; }

    int size() {
        if (isEmpty()) return 0;
        return rearIdx - frontIdx + 1;
    }

    void display() {
        if (isEmpty()) {
            cout << "  Queue: (empty)\n";
            return;
        }
        cout << "  FRONT→ ";
        for (int i = frontIdx; i <= rearIdx; i++) {
            cout << arr[i];
            if (i < rearIdx) cout << " → ";
        }
        cout << " ←REAR\n";
    }
};

// ═══════════════════════════════════════════════════════════════
// SECTION 2: COMPLETE DRY RUN
// ═══════════════════════════════════════════════════════════════
/*
  DRY RUN — enqueue(10), enqueue(20), enqueue(30), dequeue(), enqueue(40), front()

  Operation    │ frontIdx │ rearIdx │ Array State          │ Returns
  ─────────────┼──────────┼─────────┼──────────────────────┼─────────
  Initial      │    -1    │   -1    │ [_, _, _, _, _]       │ —
  enqueue(10)  │     0    │    0    │ [10, _, _, _, _]      │ —
  enqueue(20)  │     0    │    1    │ [10, 20, _, _, _]     │ —
  enqueue(30)  │     0    │    2    │ [10, 20, 30, _, _]    │ —
  dequeue()    │     1    │    2    │ [_, 20, 30, _, _]     │ 10
  enqueue(40)  │     1    │    3    │ [_, 20, 30, 40, _]    │ —
  front()      │     1    │    3    │ [_, 20, 30, 40, _]    │ 20
  dequeue()    │     2    │    3    │ [_, _, 30, 40, _]     │ 20
  dequeue()    │     3    │    3    │ [_, _, _, 40, _]      │ 30
  dequeue()    │    -1    │   -1    │ [_, _, _, _, _]       │ 40
  dequeue()    │   ERR    │  ERR    │ UNDERFLOW!            │ —

  Visual at each stage:
  ┌──────────────────────────────────────────────────┐
  │ After enqueue(10,20,30):                          │
  │   FRONT→ [10] [20] [30] [ ] [ ] ←REAR            │
  │           f=0            r=2                      │
  │                                                    │
  │ After dequeue() → returns 10:                     │
  │          [ ] [20] [30] [ ] [ ]                    │
  │               f=1       r=2                       │
  │   ⚠️ Index 0 is wasted! Can't use it again!       │
  │                                                    │
  │ After enqueue(40):                                │
  │          [ ] [20] [30] [40] [ ]                   │
  │               f=1            r=3                  │
  └──────────────────────────────────────────────────┘
*/

void demonstrateLinearQueue() {
    cout << "═══ SECTION 1: LINEAR QUEUE DEMONSTRATION ═══\n\n";

    LinearQueue q;

    cout << "isEmpty: " << (q.isEmpty() ? "true" : "false") << "\n\n";

    cout << "Enqueue 10, 20, 30:\n";
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.display();
    cout << "Size: " << q.size() << "\n";
    cout << "Front: " << q.front() << "\n";
    cout << "Rear: " << q.rear() << "\n\n";

    cout << "Dequeue: " << q.dequeue() << "\n";
    q.display();

    cout << "Enqueue 40, 50:\n";
    q.enqueue(40);
    q.enqueue(50);
    q.display();
    cout << "Size: " << q.size() << "\n\n";

    cout << "Dequeue all elements:\n";
    while (!q.isEmpty()) {
        cout << "  Dequeued: " << q.dequeue() << "  ";
        q.display();
    }

    cout << "\nTest underflow:\n";
    q.dequeue();

    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: QUEUE WITH SHIFTING (O(n) dequeue)
// ═══════════════════════════════════════════════════════════════
/*
  Alternative approach: After dequeue, shift all elements left.
  This wastes no space but dequeue is O(n).

  Before dequeue:  [10, 20, 30, 40, _]  rear=3
  After dequeue:   [20, 30, 40, _, _]   rear=2
  (All elements shifted left by 1)

  This is generally WORSE than the linear queue.
  But it shows why circular queue is the real solution.
*/

class ShiftingQueue {
private:
    static const int MAX_SIZE = 100;
    int arr[MAX_SIZE];
    int rearIdx;

public:
    ShiftingQueue() : rearIdx(-1) {}

    void enqueue(int val) {
        if (rearIdx == MAX_SIZE - 1) {
            cout << "  ❌ OVERFLOW!\n";
            return;
        }
        arr[++rearIdx] = val;
    }

    // O(n) dequeue — shifts all elements
    int dequeue() {
        if (rearIdx == -1) {
            cout << "  ❌ UNDERFLOW!\n";
            return -1;
        }
        int val = arr[0];
        // Shift all elements left
        for (int i = 0; i < rearIdx; i++) {
            arr[i] = arr[i + 1];
        }
        rearIdx--;
        return val;
    }

    int front() { return (rearIdx == -1) ? -1 : arr[0]; }
    int rear() { return (rearIdx == -1) ? -1 : arr[rearIdx]; }
    bool isEmpty() { return rearIdx == -1; }
    int size() { return rearIdx + 1; }

    void display() {
        if (isEmpty()) {
            cout << "  Queue: (empty)\n";
            return;
        }
        cout << "  FRONT→ ";
        for (int i = 0; i <= rearIdx; i++) {
            cout << arr[i];
            if (i < rearIdx) cout << " → ";
        }
        cout << " ←REAR\n";
    }
};

void demonstrateShiftingQueue() {
    cout << "═══ SECTION 3: SHIFTING QUEUE (O(n) dequeue) ═══\n\n";

    ShiftingQueue q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.display();

    cout << "Dequeue (shifts all elements): " << q.dequeue() << "\n";
    q.display();

    cout << "Dequeue: " << q.dequeue() << "\n";
    q.display();

    q.enqueue(50);
    q.display();

    cout << "\n⚠️  Shifting queue wastes time O(n) per dequeue.\n";
    cout << "✅ Solution: Use CIRCULAR QUEUE (next file)!\n\n";
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  QUEUE: FIFO CONCEPT & ARRAY IMPLEMENTATION              ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    demonstrateLinearQueue();
    demonstrateShiftingQueue();

    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "KEY TAKEAWAYS:\n";
    cout << "───────────────\n";
    cout << "1. Queue = FIFO (First In, First Out)\n";
    cout << "2. Linear array queue wastes space after dequeue\n";
    cout << "3. Shifting queue fixes space but O(n) dequeue\n";
    cout << "4. SOLUTION: Circular Queue (next file!)\n";
    cout << "\n";
    cout << "PRACTICE PROBLEMS:\n";
    cout << "───────────────────\n";
    cout << "1. Implement a queue that supports getMax() in O(1)\n";
    cout << "2. Reverse a queue using only queue operations\n";
    cout << "3. Reverse first K elements of a queue\n";
    cout << "4. Interleave first and second half of queue\n";
    cout << "5. Generate binary numbers 1 to N using queue\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

