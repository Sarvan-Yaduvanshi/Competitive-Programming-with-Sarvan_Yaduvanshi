/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — DOUBLY LINKED LIST: COMPLETE OPERATIONS                     ║
║           From Zero to Grandmaster — Complete DLL Guide                    ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. DLL Node Structure
 2. Insert: Head, Tail, Position, Before/After Node
 3. Delete: Head, Tail, By Value, Given Node Pointer
 4. Reverse DLL
 5. Flatten Multilevel DLL (LeetCode 430)

DLL KEY ADVANTAGE:
─────────────────
  Given a pointer to ANY node, you can delete it in O(1)!
  (In SLL, you need to find the previous node first → O(n))

  ┌──────────┬───────┬──────────┐
  │  prev ◀──┼ data  │  next ───┼──▶
  └──────────┴───────┴──────────┘

  DELETE NODE (given pointer):
    node->prev->next = node->next
    node->next->prev = node->prev
    delete node   →   O(1)! ✅

DRY RUN — Insert at Position 2 in DLL [10 ⟷ 20 ⟷ 40]:
──────────────────────────────────────────────────────
  Insert 30 at position 2 (0-indexed):

  Step 1: Navigate to position 1 (node 20)
  Step 2: newNode->next = curr->next (40)
          newNode->prev = curr (20)
  Step 3: curr->next->prev = newNode (40's prev = 30)
          curr->next = newNode (20's next = 30)

  Result: 10 ⟷ 20 ⟷ 30 ⟷ 40 ✅
*/

#include <iostream>
using namespace std;

struct DNode {
    int data;
    DNode* prev;
    DNode* next;
    DNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};

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

// ═══════════════════════════════════════════════════════════════
// INSERT OPERATIONS
// ═══════════════════════════════════════════════════════════════

DNode* insertAtHead(DNode* head, int val) {
    DNode* newNode = new DNode(val);
    newNode->next = head;
    if (head) head->prev = newNode;
    return newNode;
}

DNode* insertAtTail(DNode* head, int val) {
    DNode* newNode = new DNode(val);
    if (!head) return newNode;

    DNode* tail = head;
    while (tail->next) tail = tail->next;
    tail->next = newNode;
    newNode->prev = tail;
    return head;
}

DNode* insertAtPosition(DNode* head, int val, int pos) {
    if (pos == 0) return insertAtHead(head, val);

    DNode* curr = head;
    for (int i = 0; i < pos - 1 && curr; i++) curr = curr->next;

    if (!curr) return head;

    DNode* newNode = new DNode(val);
    newNode->next = curr->next;
    newNode->prev = curr;
    if (curr->next) curr->next->prev = newNode;
    curr->next = newNode;
    return head;
}

// ═══════════════════════════════════════════════════════════════
// DELETE OPERATIONS
// ═══════════════════════════════════════════════════════════════

DNode* deleteHead(DNode* head) {
    if (!head) return nullptr;
    DNode* newHead = head->next;
    if (newHead) newHead->prev = nullptr;
    delete head;
    return newHead;
}

DNode* deleteTail(DNode* head) {
    if (!head) return nullptr;
    if (!head->next) { delete head; return nullptr; }

    DNode* tail = head;
    while (tail->next) tail = tail->next;
    tail->prev->next = nullptr;
    delete tail;
    return head;
}

// O(1) delete when you have the node pointer!
DNode* deleteNode(DNode* head, DNode* node) {
    if (!node) return head;

    if (node->prev) node->prev->next = node->next;
    else head = node->next;  // Deleting head

    if (node->next) node->next->prev = node->prev;

    delete node;
    return head;
}

DNode* deleteByValue(DNode* head, int val) {
    DNode* curr = head;
    while (curr) {
        if (curr->data == val) return deleteNode(head, curr);
        curr = curr->next;
    }
    return head;
}

// ═══════════════════════════════════════════════════════════════
// REVERSE DLL — O(n) time, O(1) space
// ═══════════════════════════════════════════════════════════════

DNode* reverseDLL(DNode* head) {
    DNode* curr = head;
    DNode* temp = nullptr;

    while (curr) {
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev;  // Move forward (prev is now next)
    }

    return temp ? temp->prev : head;
}

// ═══════════════════════════════════════════════════════════════
// FLATTEN MULTILEVEL DLL (LeetCode 430)
// ═══════════════════════════════════════════════════════════════
/*
  Multilevel DLL has child pointers creating sub-lists:

  1 ⟷ 2 ⟷ 3 ⟷ 4 ⟷ 5 ⟷ 6
          |
          7 ⟷ 8 ⟷ 9 ⟷ 10
              |
              11 ⟷ 12

  Flattened: 1⟷2⟷3⟷7⟷8⟷11⟷12⟷9⟷10⟷4⟷5⟷6
*/

struct MLNode {
    int data;
    MLNode* prev;
    MLNode* next;
    MLNode* child;
    MLNode(int val) : data(val), prev(nullptr), next(nullptr), child(nullptr) {}
};

MLNode* flattenMultilevel(MLNode* head) {
    MLNode* curr = head;

    while (curr) {
        if (curr->child) {
            // Find tail of child list
            MLNode* childTail = curr->child;
            while (childTail->next) childTail = childTail->next;

            // Connect child tail to curr->next
            childTail->next = curr->next;
            if (curr->next) curr->next->prev = childTail;

            // Connect curr to child
            curr->next = curr->child;
            curr->child->prev = curr;
            curr->child = nullptr;
        }
        curr = curr->next;
    }

    return head;
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  DOUBLY LINKED LIST: COMPLETE OPERATIONS               ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Build and test
    cout << "═══ INSERT OPERATIONS ═══\n";
    DNode* head = nullptr;
    head = insertAtTail(head, 10);
    head = insertAtTail(head, 20);
    head = insertAtTail(head, 40);
    cout << "Initial: "; printDLL(head);
    head = insertAtHead(head, 5);
    cout << "Insert 5 at head: "; printDLL(head);
    head = insertAtPosition(head, 30, 3);
    cout << "Insert 30 at pos 3: "; printDLL(head);

    // Delete operations
    cout << "\n═══ DELETE OPERATIONS ═══\n";
    head = deleteHead(head);
    cout << "Delete head: "; printDLL(head);
    head = deleteTail(head);
    cout << "Delete tail: "; printDLL(head);
    head = deleteByValue(head, 20);
    cout << "Delete value 20: "; printDLL(head);

    freeDLL(head);

    // Reverse DLL
    cout << "\n═══ REVERSE DLL ═══\n";
    head = nullptr;
    for (int i = 5; i >= 1; i--) head = insertAtHead(head, i);
    cout << "Before: "; printDLL(head);
    head = reverseDLL(head);
    cout << "After:  "; printDLL(head);
    freeDLL(head);

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "KEY INSIGHT: DLL delete given node = O(1)!\n";
    cout << "This is why LRU Cache uses DLL + HashMap.\n";
    cout << "PRACTICE: LeetCode 430, 146, 460\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

