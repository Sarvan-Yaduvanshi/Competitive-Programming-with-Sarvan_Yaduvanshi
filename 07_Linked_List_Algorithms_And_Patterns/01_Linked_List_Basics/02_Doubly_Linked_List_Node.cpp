/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — DOUBLY LINKED LIST: NODE STRUCTURE & OPERATIONS               ║
║           From Zero to Grandmaster — Complete Foundation                     ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Doubly Linked List Node Structure
 2. Building a DLL
 3. Forward & Backward Traversal
 4. Advantages & Disadvantages vs SLL

DOUBLY LINKED LIST NODE:
───────────────────────
  ┌──────────┬───────┬──────────┐
  │  prev ◀──┼ data  │  next ───┼──▶
  └──────────┴───────┴──────────┘

  struct DNode {
      int data;
      DNode* prev;   // Points to previous node
      DNode* next;   // Points to next node
  };

VISUALIZATION:
─────────────
  NULL ◀── [10] ⟷ [20] ⟷ [30] ⟷ [40] ──▶ NULL
            ↑                        ↑
           head                     tail

  Each node has TWO pointers:
  • prev: points to the previous node (NULL for head)
  • next: points to the next node (NULL for tail)

ADVANTAGES OVER SLL:
  ✅ O(1) delete if node pointer is given (no need to find prev)
  ✅ Bidirectional traversal
  ✅ Used in LRU Cache, Browser History, Text Editors
  ❌ Extra memory per node (one more pointer)
  ❌ More complex insert/delete logic
*/

#include <iostream>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: DOUBLY LINKED LIST NODE
// ═══════════════════════════════════════════════════════════════

struct DNode {
    int data;
    DNode* prev;
    DNode* next;

    DNode(int val) : data(val), prev(nullptr), next(nullptr) {}
    DNode(int val, DNode* p, DNode* n) : data(val), prev(p), next(n) {}
};

// ═══════════════════════════════════════════════════════════════
// SECTION 2: BUILD DLL
// ═══════════════════════════════════════════════════════════════
/*
  DRY RUN — Building DLL from array [10, 20, 30]:

  Step 1: head = new DNode(10)
          NULL ◀── [10] ──▶ NULL
                    ↑
                  head, tail

  Step 2: newNode = new DNode(20), tail->next = newNode, newNode->prev = tail
          NULL ◀── [10] ⟷ [20] ──▶ NULL
                    ↑       ↑
                  head     tail

  Step 3: newNode = new DNode(30), tail->next = newNode, newNode->prev = tail
          NULL ◀── [10] ⟷ [20] ⟷ [30] ──▶ NULL
                    ↑               ↑
                  head             tail
*/

DNode* buildDLL(int arr[], int n) {
    if (n == 0) return nullptr;

    DNode* head = new DNode(arr[0]);
    DNode* tail = head;

    for (int i = 1; i < n; i++) {
        DNode* newNode = new DNode(arr[i]);
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    return head;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: TRAVERSAL (FORWARD & BACKWARD)
// ═══════════════════════════════════════════════════════════════

void printForward(DNode* head) {
    cout << "Forward:  NULL <-> ";
    DNode* curr = head;
    while (curr != nullptr) {
        cout << curr->data;
        if (curr->next != nullptr) cout << " <-> ";
        curr = curr->next;
    }
    cout << " <-> NULL\n";
}

void printBackward(DNode* head) {
    if (head == nullptr) { cout << "Backward: (empty)\n"; return; }

    // Find tail
    DNode* tail = head;
    while (tail->next != nullptr) tail = tail->next;

    cout << "Backward: NULL <-> ";
    DNode* curr = tail;
    while (curr != nullptr) {
        cout << curr->data;
        if (curr->prev != nullptr) cout << " <-> ";
        curr = curr->prev;
    }
    cout << " <-> NULL\n";
}

void deleteDLL(DNode* head) {
    while (head) {
        DNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: COMPARISON — SLL vs DLL
// ═══════════════════════════════════════════════════════════════
/*
  ┌─────────────────────┬────────────┬────────────┐
  │ Feature             │    SLL     │    DLL     │
  ├─────────────────────┼────────────┼────────────┤
  │ Node pointers       │    1       │    2       │
  │ Memory per node     │  data+8B   │ data+16B  │
  │ Forward traversal   │    ✅      │    ✅     │
  │ Backward traversal  │    ❌      │    ✅     │
  │ Delete given node   │   O(n)*    │   O(1)    │
  │ Insert before node  │   O(n)*    │   O(1)    │
  │ Complexity          │  Simple    │  Complex  │
  │ Used in LRU Cache   │    ❌      │    ✅     │
  └─────────────────────┴────────────┴────────────┘
  * Need to find previous node first
*/

void demonstrateDLL() {
    cout << "═══ DOUBLY LINKED LIST DEMO ═══\n\n";

    int arr[] = {10, 20, 30, 40, 50};
    DNode* head = buildDLL(arr, 5);

    printForward(head);
    printBackward(head);

    // Show node connections
    cout << "\nNode Details:\n";
    DNode* curr = head;
    while (curr != nullptr) {
        cout << "  Node(" << curr->data << "): "
             << "prev=" << (curr->prev ? to_string(curr->prev->data) : "NULL")
             << ", next=" << (curr->next ? to_string(curr->next->data) : "NULL")
             << "\n";
        curr = curr->next;
    }

    deleteDLL(head);
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  DOUBLY LINKED LIST: NODE STRUCTURE & OPERATIONS         ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    demonstrateDLL();

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE PROBLEMS:\n";
    cout << "───────────────────\n";
    cout << "1. Build DLL from user input\n";
    cout << "2. Find the middle node of a DLL\n";
    cout << "3. Count nodes traversing both directions\n";
    cout << "4. Check if DLL is a palindrome\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

