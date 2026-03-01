/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — ITERATIVE REVERSAL OF LINKED LIST                           ║
║           From Zero to Grandmaster — Core Pattern                          ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Three-Pointer Iterative Reversal
 2. Dry Run Step by Step
 3. Edge Cases

THE THREE-POINTER TECHNIQUE:
───────────────────────────
  Use three pointers: prev, curr, next

  Algorithm:
  ──────────
  prev = NULL
  curr = head
  while (curr != NULL):
      next = curr->next     // Save next
      curr->next = prev     // Reverse the link
      prev = curr           // Move prev forward
      curr = next           // Move curr forward
  return prev               // New head

DRY RUN on [1 → 2 → 3 → 4 → NULL]:
────────────────────────────────────
  Initial:
    prev=NULL  curr=1  →  2 → 3 → 4 → NULL

  Iteration 1:
    next = 2
    1->next = NULL (was 2)
    prev = 1, curr = 2
    NULL ← 1    2 → 3 → 4 → NULL
           ↑    ↑
          prev  curr

  Iteration 2:
    next = 3
    2->next = 1 (was 3)
    prev = 2, curr = 3
    NULL ← 1 ← 2    3 → 4 → NULL
                ↑    ↑
               prev  curr

  Iteration 3:
    next = 4
    3->next = 2 (was 4)
    prev = 3, curr = 4
    NULL ← 1 ← 2 ← 3    4 → NULL
                     ↑    ↑
                    prev  curr

  Iteration 4:
    next = NULL
    4->next = 3 (was NULL)
    prev = 4, curr = NULL
    NULL ← 1 ← 2 ← 3 ← 4
                          ↑
                         prev (new head!)

  Result: 4 → 3 → 2 → 1 → NULL  ✅

  Time: O(n)   Space: O(1)
*/

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

Node* buildList(int arr[], int n) {
    if (n == 0) return nullptr;
    Node* head = new Node(arr[0]);
    Node* tail = head;
    for (int i = 1; i < n; i++) { tail->next = new Node(arr[i]); tail = tail->next; }
    return head;
}

void printList(Node* head) {
    while (head) { cout << head->data; if (head->next) cout << " -> "; head = head->next; }
    cout << " -> NULL\n";
}

void freeList(Node* head) { while (head) { Node* t = head; head = head->next; delete t; } }

// ═══════════════════════════════════════════════════════════════
// ITERATIVE REVERSAL — O(n) time, O(1) space
// ═══════════════════════════════════════════════════════════════

Node* reverseIterative(Node* head) {
    Node* prev = nullptr;
    Node* curr = head;
    Node* next = nullptr;

    while (curr != nullptr) {
        next = curr->next;     // Save next node
        curr->next = prev;     // Reverse the link
        prev = curr;           // Move prev forward
        curr = next;           // Move curr forward
    }

    return prev;  // prev is now the new head
}

// Verbose version with step-by-step output
Node* reverseIterativeVerbose(Node* head) {
    Node* prev = nullptr;
    Node* curr = head;
    Node* next = nullptr;
    int step = 0;

    cout << "  Step " << step << ": prev=NULL, curr=" << (curr ? to_string(curr->data) : "NULL") << "\n";

    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        step++;

        cout << "  Step " << step << ": prev=" << (prev ? to_string(prev->data) : "NULL")
             << ", curr=" << (curr ? to_string(curr->data) : "NULL") << "\n";
    }

    return prev;
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  ITERATIVE REVERSAL OF LINKED LIST                     ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Normal case
    cout << "═══ NORMAL CASE ═══\n";
    int arr[] = {1, 2, 3, 4, 5};
    Node* head = buildList(arr, 5);
    cout << "Before: "; printList(head);
    head = reverseIterative(head);
    cout << "After:  "; printList(head);
    freeList(head);

    // Verbose dry run
    cout << "\n═══ STEP-BY-STEP DRY RUN ═══\n";
    int arr2[] = {10, 20, 30, 40};
    head = buildList(arr2, 4);
    cout << "Input: "; printList(head);
    head = reverseIterativeVerbose(head);
    cout << "Output: "; printList(head);
    freeList(head);

    // Edge cases
    cout << "\n═══ EDGE CASES ═══\n";

    // Empty list
    head = nullptr;
    head = reverseIterative(head);
    cout << "Empty list reversed: "; printList(head);

    // Single node
    head = new Node(42);
    head = reverseIterative(head);
    cout << "Single node reversed: "; printList(head);
    freeList(head);

    // Two nodes
    int arr3[] = {1, 2};
    head = buildList(arr3, 2);
    cout << "Two nodes before: "; printList(head);
    head = reverseIterative(head);
    cout << "Two nodes after:  "; printList(head);
    freeList(head);

    return 0;
}

