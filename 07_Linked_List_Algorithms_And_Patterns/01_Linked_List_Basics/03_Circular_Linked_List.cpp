/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           03 — CIRCULAR LINKED LIST: STRUCTURE & TRAVERSAL                 ║
║           From Zero to Grandmaster — Complete Foundation                    ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Circular Singly Linked List
 2. Circular Doubly Linked List
 3. Traversal Patterns
 4. Detecting Circular List
 5. Use Cases

CIRCULAR SINGLY LINKED LIST:
────────────────────────────
  Last node's next points BACK to the first node (no NULL!)

        ┌───────────────────────────────┐
        │                               │
        ▼                               │
   ┌───┬───┐   ┌───┬───┐   ┌───┬───┐  │
   │ 1 │ ──┼──▶│ 2 │ ──┼──▶│ 3 │ ──┼──┘
   └───┴───┘   └───┴───┘   └───┴───┘
    ↑ head

  head->next != NULL  (NEVER null in circular list!)
  Traversal: start at head, stop when we come back to head

CIRCULAR DOUBLY LINKED LIST:
────────────────────────────
        ┌──────────────────────────────────────────┐
        │                                          │
        ▼                                          │
   ┌──┬───┬──┐   ┌──┬───┬──┐   ┌──┬───┬──┐       │
   │◀─│ 1 │──┼──▶│◀─│ 2 │──┼──▶│◀─│ 3 │──┼───────┘
   └──┴───┴──┘   └──┴───┴──┘   └──┴───┴──┘
    ↑           ↑                        │
    └────────────────────────────────────┘
     head->prev = last, last->next = head
*/

#include <iostream>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: CIRCULAR SINGLY LINKED LIST
// ═══════════════════════════════════════════════════════════════

struct CNode {
    int data;
    CNode* next;
    CNode(int val) : data(val), next(nullptr) {}
};

/*
  DRY RUN — Building Circular SLL from [1, 2, 3, 4]:

  Step 1: head = new CNode(1), head->next = head  (self-loop)
          ┌────┐
          │    ▼
          [1]──┘

  Step 2: Insert 2 after head
          head ──▶ [1] ──▶ [2] ──┐
                    ↑             │
                    └─────────────┘

  Step 3: Insert 3 after 2
          head ──▶ [1] ──▶ [2] ──▶ [3] ──┐
                    ↑                      │
                    └──────────────────────┘

  Step 4: Insert 4 after 3
          head ──▶ [1] ──▶ [2] ──▶ [3] ──▶ [4] ──┐
                    ↑                               │
                    └───────────────────────────────┘
*/

CNode* buildCircularSLL(int arr[], int n) {
    if (n == 0) return nullptr;

    CNode* head = new CNode(arr[0]);
    head->next = head;  // Self-loop for single node

    CNode* tail = head;
    for (int i = 1; i < n; i++) {
        CNode* newNode = new CNode(arr[i]);
        newNode->next = head;    // New node points to head
        tail->next = newNode;    // Old tail points to new node
        tail = newNode;          // Update tail
    }
    return head;
}

void printCircularSLL(CNode* head) {
    if (head == nullptr) { cout << "(empty)\n"; return; }

    cout << "Circular SLL: ";
    CNode* curr = head;
    do {
        cout << curr->data;
        curr = curr->next;
        if (curr != head) cout << " -> ";
    } while (curr != head);
    cout << " -> (back to " << head->data << ")\n";
}

bool isCircular(CNode* head) {
    if (head == nullptr) return true;  // Empty is trivially circular

    CNode* curr = head->next;
    while (curr != nullptr && curr != head) {
        curr = curr->next;
    }
    return curr == head;
}

int lengthCircular(CNode* head) {
    if (head == nullptr) return 0;

    int count = 1;
    CNode* curr = head->next;
    while (curr != head) {
        count++;
        curr = curr->next;
    }
    return count;
}

void deleteCircularSLL(CNode* head) {
    if (head == nullptr) return;
    CNode* curr = head->next;
    while (curr != head) {
        CNode* temp = curr;
        curr = curr->next;
        delete temp;
    }
    delete head;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: CIRCULAR DOUBLY LINKED LIST
// ═══════════════════════════════════════════════════════════════

struct CDNode {
    int data;
    CDNode* prev;
    CDNode* next;
    CDNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};

CDNode* buildCircularDLL(int arr[], int n) {
    if (n == 0) return nullptr;

    CDNode* head = new CDNode(arr[0]);
    head->prev = head;
    head->next = head;

    CDNode* tail = head;
    for (int i = 1; i < n; i++) {
        CDNode* newNode = new CDNode(arr[i]);
        newNode->next = head;
        newNode->prev = tail;
        tail->next = newNode;
        head->prev = newNode;
        tail = newNode;
    }
    return head;
}

void printCircularDLL(CDNode* head) {
    if (head == nullptr) { cout << "(empty)\n"; return; }

    cout << "Circular DLL: ";
    CDNode* curr = head;
    do {
        cout << curr->data;
        curr = curr->next;
        if (curr != head) cout << " <-> ";
    } while (curr != head);
    cout << " <-> (back to " << head->data << ")\n";
}

void deleteCircularDLL(CDNode* head) {
    if (head == nullptr) return;
    CDNode* curr = head->next;
    while (curr != head) {
        CDNode* temp = curr;
        curr = curr->next;
        delete temp;
    }
    delete head;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: USE CASES
// ═══════════════════════════════════════════════════════════════
/*
  USE CASES FOR CIRCULAR LINKED LIST:
  ───────────────────────────────────
  1. Round-Robin Scheduling (OS process scheduling)
  2. Josephus Problem (elimination game)
  3. Circular Buffer (streaming data)
  4. Music Playlist (repeat mode)
  5. Board Games (players taking turns)
  6. Token Ring Network

  KEY DIFFERENCE FROM LINEAR LL:
  • No NULL termination → No "end" of list
  • Must use head comparison to detect full traversal
  • Infinite loop risk if traversal condition is wrong!
*/

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  CIRCULAR LINKED LIST: STRUCTURE & TRAVERSAL           ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Circular Singly Linked List
    cout << "═══ CIRCULAR SINGLY LINKED LIST ═══\n\n";
    int arr1[] = {1, 2, 3, 4, 5};
    CNode* csll = buildCircularSLL(arr1, 5);
    printCircularSLL(csll);
    cout << "Is Circular: " << (isCircular(csll) ? "YES" : "NO") << "\n";
    cout << "Length: " << lengthCircular(csll) << "\n";
    deleteCircularSLL(csll);

    // Circular Doubly Linked List
    cout << "\n═══ CIRCULAR DOUBLY LINKED LIST ═══\n\n";
    int arr2[] = {10, 20, 30, 40};
    CDNode* cdll = buildCircularDLL(arr2, 4);
    printCircularDLL(cdll);

    // Show connections
    cout << "\nNode connections:\n";
    CDNode* curr = cdll;
    do {
        cout << "  Node(" << curr->data << "): prev=" << curr->prev->data
             << ", next=" << curr->next->data << "\n";
        curr = curr->next;
    } while (curr != cdll);

    deleteCircularDLL(cdll);

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE PROBLEMS:\n";
    cout << "───────────────────\n";
    cout << "1. Insert at any position in circular SLL\n";
    cout << "2. Delete a node from circular SLL\n";
    cout << "3. Split circular list into two halves\n";
    cout << "4. Check if a given SLL is circular or linear\n";
    cout << "5. Convert linear SLL to circular and vice versa\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

