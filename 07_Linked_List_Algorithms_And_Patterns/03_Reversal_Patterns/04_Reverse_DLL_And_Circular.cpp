/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           04 — REVERSE DOUBLY & CIRCULAR LINKED LIST                       ║
║           From Zero to Grandmaster — Core Pattern                          ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Reverse Doubly Linked List
 2. Reverse Circular Singly Linked List
 3. Reverse Even Length Groups

DRY RUN — Reverse Doubly Linked List [1 ⟷ 2 ⟷ 3]:
───────────────────────────────────────────────────
  Step 1: curr = 1, swap prev & next pointers
          1->prev = 2 (was NULL), 1->next = NULL (was 2)
          Move: curr = 1->prev = 2

  Step 2: curr = 2, swap prev & next
          2->prev = 3 (was 1), 2->next = 1 (was 3)
          Move: curr = 2->prev = 3

  Step 3: curr = 3, swap prev & next
          3->prev = NULL (was 2), 3->next = 2 (was NULL)
          Move: curr = 3->prev = NULL → STOP

  New head = 3 (last node processed before NULL)
  Result: NULL ⟵ 3 ⟷ 2 ⟷ 1 ⟶ NULL ✅

  Time: O(n)  Space: O(1)
*/

#include <iostream>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// DOUBLY LINKED LIST REVERSAL
// ═══════════════════════════════════════════════════════════════

struct DNode {
    int data;
    DNode* prev;
    DNode* next;
    DNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};

DNode* buildDLL(int arr[], int n) {
    if (n == 0) return nullptr;
    DNode* head = new DNode(arr[0]);
    DNode* tail = head;
    for (int i = 1; i < n; i++) {
        DNode* node = new DNode(arr[i]);
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    return head;
}

void printDLL(DNode* head) {
    cout << "NULL <-> ";
    while (head) {
        cout << head->data;
        if (head->next) cout << " <-> ";
        head = head->next;
    }
    cout << " <-> NULL\n";
}

void freeDLL(DNode* head) {
    while (head) { DNode* t = head; head = head->next; delete t; }
}

DNode* reverseDLL(DNode* head) {
    if (!head) return nullptr;

    DNode* curr = head;
    DNode* temp = nullptr;

    while (curr) {
        // Swap prev and next
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;

        // Move to next node (which is now prev due to swap)
        curr = curr->prev;
    }

    // temp->prev is the last node we processed (new head)
    if (temp) head = temp->prev;
    return head;
}

// ═══════════════════════════════════════════════════════════════
// CIRCULAR SINGLY LINKED LIST REVERSAL
// ═══════════════════════════════════════════════════════════════

struct CNode {
    int data;
    CNode* next;
    CNode(int val) : data(val), next(nullptr) {}
};

CNode* buildCircularSLL(int arr[], int n) {
    if (n == 0) return nullptr;
    CNode* head = new CNode(arr[0]);
    head->next = head;
    CNode* tail = head;
    for (int i = 1; i < n; i++) {
        CNode* node = new CNode(arr[i]);
        node->next = head;
        tail->next = node;
        tail = node;
    }
    return head;
}

void printCircular(CNode* head) {
    if (!head) { cout << "(empty)\n"; return; }
    CNode* curr = head;
    do {
        cout << curr->data;
        curr = curr->next;
        if (curr != head) cout << " -> ";
    } while (curr != head);
    cout << " -> (back to " << head->data << ")\n";
}

CNode* reverseCircularSLL(CNode* head) {
    if (!head || head->next == head) return head;

    CNode* prev = nullptr;
    CNode* curr = head;
    CNode* next = nullptr;

    do {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    } while (curr != head);

    // Connect: old head points to new head (prev), complete the circle
    head->next = prev;
    return prev;
}

void freeCircular(CNode* head) {
    if (!head) return;
    CNode* curr = head->next;
    while (curr != head) {
        CNode* t = curr;
        curr = curr->next;
        delete t;
    }
    delete head;
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  REVERSE DOUBLY & CIRCULAR LINKED LIST                 ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Reverse DLL
    cout << "═══ REVERSE DOUBLY LINKED LIST ═══\n";
    int arr1[] = {1, 2, 3, 4, 5};
    DNode* dll = buildDLL(arr1, 5);
    cout << "Before: "; printDLL(dll);
    dll = reverseDLL(dll);
    cout << "After:  "; printDLL(dll);
    freeDLL(dll);

    // Reverse Circular SLL
    cout << "\n═══ REVERSE CIRCULAR SINGLY LINKED LIST ═══\n";
    int arr2[] = {10, 20, 30, 40};
    CNode* csll = buildCircularSLL(arr2, 4);
    cout << "Before: "; printCircular(csll);
    csll = reverseCircularSLL(csll);
    cout << "After:  "; printCircular(csll);
    freeCircular(csll);

    return 0;
}

