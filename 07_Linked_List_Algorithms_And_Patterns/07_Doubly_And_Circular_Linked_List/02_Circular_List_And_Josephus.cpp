/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — CIRCULAR LINKED LIST & JOSEPHUS PROBLEM                     ║
║           From Zero to Grandmaster — Circular List Patterns                ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Circular Singly Linked List — All Operations
 2. Circular Doubly Linked List — All Operations
 3. Josephus Problem (Classic Circular Elimination)
 4. Detect if List is Circular

JOSEPHUS PROBLEM:
────────────────
  N people stand in a circle. Starting from person 1, every Kth person
  is eliminated. Find the last person standing.

  DRY RUN — N=7, K=3:
  ┌─────────────────────────────────────┐
  │  Circle: 1 2 3 4 5 6 7             │
  │                                     │
  │  Round 1: Count 3 from 1 → kill 3  │
  │  Circle: 1 2 _ 4 5 6 7             │
  │                                     │
  │  Round 2: Count 3 from 4 → kill 6  │
  │  Circle: 1 2 _ 4 5 _ 7             │
  │                                     │
  │  Round 3: Count 3 from 7 → kill 2  │
  │  Circle: 1 _ _ 4 5 _ 7             │
  │                                     │
  │  Round 4: Count 3 from 4 → kill 7  │
  │  Circle: 1 _ _ 4 5 _ _             │
  │                                     │
  │  Round 5: Count 3 from 1 → kill 5  │
  │  Circle: 1 _ _ 4 _ _ _             │
  │                                     │
  │  Round 6: Count 3 from 1 → kill 1  │
  │  Circle: _ _ _ 4 _ _ _             │
  │                                     │
  │  Last person standing: 4  ✅        │
  └─────────────────────────────────────┘

  Mathematical Formula: J(n, k) = (J(n-1, k) + k) % n
  Base case: J(1, k) = 0

  Time: O(n) with formula, O(n*k) with simulation
*/

#include <iostream>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// CIRCULAR SINGLY LINKED LIST
// ═══════════════════════════════════════════════════════════════

struct CNode {
    int data;
    CNode* next;
    CNode(int val) : data(val), next(nullptr) {}
};

CNode* insertAtHead(CNode* last, int val) {
    CNode* newNode = new CNode(val);
    if (!last) {
        newNode->next = newNode;  // Self-loop
        return newNode;
    }
    newNode->next = last->next;  // New node points to head
    last->next = newNode;        // Last points to new node (new head)
    return last;
}

CNode* insertAtTail(CNode* last, int val) {
    CNode* newNode = new CNode(val);
    if (!last) {
        newNode->next = newNode;
        return newNode;
    }
    newNode->next = last->next;  // New node points to head
    last->next = newNode;        // Old last points to new node
    return newNode;              // New node is the new last
}

CNode* deleteNode(CNode* last, int val) {
    if (!last) return nullptr;

    // Single node
    if (last->next == last && last->data == val) {
        delete last;
        return nullptr;
    }

    CNode* curr = last->next;  // Start from head
    CNode* prev = last;

    do {
        if (curr->data == val) {
            prev->next = curr->next;
            if (curr == last) last = prev;
            delete curr;
            return last;
        }
        prev = curr;
        curr = curr->next;
    } while (curr != last->next);

    return last;
}

void printCircular(CNode* last) {
    if (!last) { cout << "(empty)\n"; return; }
    CNode* head = last->next;
    CNode* curr = head;
    do {
        cout << curr->data;
        curr = curr->next;
        if (curr != head) cout << " -> ";
    } while (curr != head);
    cout << " -> (back to " << head->data << ")\n";
}

void freeCircular(CNode* last) {
    if (!last) return;
    CNode* curr = last->next;
    while (curr != last) {
        CNode* t = curr;
        curr = curr->next;
        delete t;
    }
    delete last;
}

// ═══════════════════════════════════════════════════════════════
// JOSEPHUS PROBLEM — Simulation with Circular LL
// ═══════════════════════════════════════════════════════════════

int josephusLinkedList(int n, int k) {
    // Build circular list: 1, 2, ..., n
    CNode* head = new CNode(1);
    CNode* prev = head;
    for (int i = 2; i <= n; i++) {
        CNode* node = new CNode(i);
        prev->next = node;
        prev = node;
    }
    prev->next = head;  // Make circular

    CNode* curr = prev;  // Start from the node before head

    while (curr->next != curr) {  // More than one node left
        // Count k-1 steps
        for (int i = 1; i < k; i++) {
            curr = curr->next;
        }

        // Remove curr->next
        CNode* toRemove = curr->next;
        cout << "  Eliminated: " << toRemove->data << "\n";
        curr->next = toRemove->next;
        delete toRemove;
    }

    int survivor = curr->data;
    delete curr;
    return survivor;
}

// Mathematical O(n) solution
int josephusMath(int n, int k) {
    int result = 0;  // Base case: J(1, k) = 0
    for (int i = 2; i <= n; i++) {
        result = (result + k) % i;
    }
    return result + 1;  // 1-indexed
}

// Recursive solution
int josephusRecursive(int n, int k) {
    if (n == 1) return 0;
    return (josephusRecursive(n - 1, k) + k) % n;
}

// ═══════════════════════════════════════════════════════════════
// DETECT CIRCULAR LIST
// ═══════════════════════════════════════════════════════════════

bool isCircular(CNode* head) {
    if (!head) return true;
    CNode* curr = head->next;
    while (curr && curr != head) {
        curr = curr->next;
    }
    return curr == head;
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  CIRCULAR LINKED LIST & JOSEPHUS PROBLEM               ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Circular SLL operations
    cout << "═══ CIRCULAR SINGLY LINKED LIST ═══\n";
    CNode* last = nullptr;
    last = insertAtTail(last, 1);
    last = insertAtTail(last, 2);
    last = insertAtTail(last, 3);
    last = insertAtTail(last, 4);
    last = insertAtTail(last, 5);
    cout << "List: "; printCircular(last);

    last = deleteNode(last, 3);
    cout << "Delete 3: "; printCircular(last);

    last = insertAtHead(last, 0);
    cout << "Insert 0 at head: "; printCircular(last);

    cout << "Is Circular: " << (isCircular(last->next) ? "YES" : "NO") << "\n";
    freeCircular(last);

    // Josephus Problem
    cout << "\n═══ JOSEPHUS PROBLEM (N=7, K=3) ═══\n";
    cout << "Simulation:\n";
    int survivor = josephusLinkedList(7, 3);
    cout << "Last person standing: " << survivor << "\n";

    cout << "\nMathematical solution: " << josephusMath(7, 3) << "\n";
    cout << "Recursive solution: " << josephusRecursive(7, 3) + 1 << "\n";

    // More examples
    cout << "\n═══ MORE JOSEPHUS EXAMPLES ═══\n";
    for (int n : {5, 10, 41}) {
        for (int k : {2, 3}) {
            cout << "N=" << n << ", K=" << k << " → Survivor: " << josephusMath(n, k) << "\n";
        }
    }

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE: CSES Josephus I & II, GFG Josephus Problem\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

