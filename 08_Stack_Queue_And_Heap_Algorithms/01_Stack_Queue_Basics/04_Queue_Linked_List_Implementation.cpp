/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           04 — QUEUE: LINKED LIST IMPLEMENTATION                             ║
║           From Zero to Grandmaster — Complete Foundation                     ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Queue Using Linked List — Concept
 2. Node Structure
 3. Enqueue (Insert at Tail)
 4. Dequeue (Delete from Head)
 5. Complete Implementation
 6. Dry Run with Memory Visualization

WHY LINKED LIST FOR QUEUE?
──────────────────────────
  Array Queue Problems:
    ❌ Fixed size (overflow possible)
    ❌ Wasted space in linear queue
    ❌ Need circular indexing for efficient dequeue

  Linked List Queue:
    ✅ Dynamic size — grows/shrinks on demand
    ✅ O(1) enqueue AND dequeue (with front + rear pointers)
    ✅ No wasted space
    ❌ Extra memory for pointers
    ❌ Not cache-friendly

LINKED LIST QUEUE VISUALIZATION:
───────────────────────────────
  Enqueue = Insert at tail (rear)
  Dequeue = Delete from head (front)

  Enqueue 10, 20, 30:
  front                              rear
    ↓                                  ↓
  [10 | ──]──▶ [20 | ──]──▶ [30 | NULL]

  Dequeue() → returns 10:
  front              rear
    ↓                  ↓
  [20 | ──]──▶ [30 | NULL]

  Key: front = head, rear = tail
  Enqueue at tail: O(1) since we maintain rear pointer
  Dequeue from head: O(1) since front pointer always at head
*/

#include <iostream>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: NODE STRUCTURE
// ═══════════════════════════════════════════════════════════════

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// ═══════════════════════════════════════════════════════════════
// SECTION 2: QUEUE USING LINKED LIST
// ═══════════════════════════════════════════════════════════════
/*
  DRY RUN — enqueue(10), enqueue(20), enqueue(30), dequeue(), front():

  enqueue(10):
    Create [10|NULL]
    front = rear = [10|NULL]
    size = 1

    front,rear
       ↓
    [10|NULL]

  enqueue(20):
    Create [20|NULL]
    rear->next = [20|NULL]
    rear = [20|NULL]
    size = 2

    front         rear
      ↓             ↓
    [10|──]──▶[20|NULL]

  enqueue(30):
    Create [30|NULL]
    rear->next = [30|NULL]
    rear = [30|NULL]
    size = 3

    front                   rear
      ↓                       ↓
    [10|──]──▶[20|──]──▶[30|NULL]

  dequeue() → 10:
    val = front->data = 10
    temp = front = [10|...]
    front = front->next = [20|...]
    delete temp
    size = 2

    front         rear
      ↓             ↓
    [20|──]──▶[30|NULL]

  front() → 20:
    return front->data = 20
*/

class QueueLL {
private:
    Node* frontNode;
    Node* rearNode;
    int count;

public:
    QueueLL() : frontNode(nullptr), rearNode(nullptr), count(0) {}

    ~QueueLL() {
        while (frontNode) {
            Node* temp = frontNode;
            frontNode = frontNode->next;
            delete temp;
        }
    }

    // Enqueue: Insert at rear — O(1)
    void enqueue(int val) {
        Node* newNode = new Node(val);
        if (isEmpty()) {
            frontNode = rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
        count++;
    }

    // Dequeue: Delete from front — O(1)
    int dequeue() {
        if (isEmpty()) {
            cout << "  ❌ UNDERFLOW! Queue is empty.\n";
            return -1;
        }
        int val = frontNode->data;
        Node* temp = frontNode;
        frontNode = frontNode->next;
        if (frontNode == nullptr) {
            rearNode = nullptr;  // Queue became empty
        }
        delete temp;
        count--;
        return val;
    }

    int front() {
        if (isEmpty()) return -1;
        return frontNode->data;
    }

    int rear() {
        if (isEmpty()) return -1;
        return rearNode->data;
    }

    bool isEmpty() { return frontNode == nullptr; }
    int size() { return count; }

    void display() {
        if (isEmpty()) {
            cout << "  Queue: (empty)\n";
            return;
        }
        cout << "  FRONT→ ";
        Node* curr = frontNode;
        while (curr) {
            cout << "[" << curr->data << "]";
            if (curr->next) cout << " → ";
            curr = curr->next;
        }
        cout << " ←REAR\n";
    }

    void displayDetailed() {
        if (isEmpty()) {
            cout << "  Queue: (empty)\n";
            return;
        }
        cout << "  Queue (front to rear):\n";
        Node* curr = frontNode;
        while (curr) {
            cout << "    data=" << curr->data << " @" << curr
                 << " next→" << curr->next;
            if (curr == frontNode) cout << " [FRONT]";
            if (curr == rearNode) cout << " [REAR]";
            cout << "\n";
            curr = curr->next;
        }
    }
};

// ═══════════════════════════════════════════════════════════════
// SECTION 3: DEMONSTRATION
// ═══════════════════════════════════════════════════════════════

void demonstrateQueueLL() {
    cout << "═══ LINKED LIST QUEUE DEMONSTRATION ═══\n\n";

    QueueLL q;

    cout << "Enqueue 10, 20, 30, 40:\n";
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.display();
    cout << "Size: " << q.size() << "\n";
    cout << "Front: " << q.front() << ", Rear: " << q.rear() << "\n\n";

    cout << "Detailed view:\n";
    q.displayDetailed();

    cout << "\nDequeue: " << q.dequeue() << "\n";
    q.display();

    cout << "Dequeue: " << q.dequeue() << "\n";
    q.display();

    q.enqueue(50);
    q.enqueue(60);
    cout << "After enqueue 50, 60:\n";
    q.display();

    cout << "\nDrain queue:\n";
    while (!q.isEmpty()) {
        cout << "  " << q.dequeue();
        if (!q.isEmpty()) cout << " → ";
    }
    cout << "\n\nQueue empty: " << (q.isEmpty() ? "true" : "false") << "\n";

    cout << "\nTest underflow:\n";
    q.dequeue();

    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  QUEUE: LINKED LIST IMPLEMENTATION                       ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    demonstrateQueueLL();

    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE PROBLEMS:\n";
    cout << "───────────────────\n";
    cout << "1. Implement a deque (double-ended queue) using linked list\n";
    cout << "2. Reverse a linked-list-based queue without extra space\n";
    cout << "3. Implement a priority queue using linked list\n";
    cout << "4. Sort a queue using only enqueue and dequeue\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

