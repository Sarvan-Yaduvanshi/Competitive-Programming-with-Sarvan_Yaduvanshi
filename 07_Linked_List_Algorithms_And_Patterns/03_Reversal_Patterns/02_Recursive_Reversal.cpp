/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — RECURSIVE REVERSAL OF LINKED LIST                           ║
║           From Zero to Grandmaster — Core Pattern                          ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Head Recursion (Standard)
 2. Tail Recursion (Optimized)

DRY RUN — Head Recursive Reversal on [1 → 2 → 3 → NULL]:
──────────────────────────────────────────────────────────
  reverse(1):
    → reverse(2):
      → reverse(3):
        → BASE CASE: 3->next is NULL, return 3 (new head)
        ← newHead = 3

      After return: head=2
        2->next->next = 2   →  3->next = 2  (3 now points to 2)
        2->next = NULL
        State: 3 → 2 → NULL, and 1 still → 2
        Return newHead (3)

    After return: head=1
      1->next->next = 1   →  2->next = 1  (2 now points to 1)
      1->next = NULL
      State: 3 → 2 → 1 → NULL
      Return newHead (3)

  Result: 3 → 2 → 1 → NULL ✅

  KEY INSIGHT:
    head->next->next = head  ← Makes next node point BACK to current
    head->next = NULL        ← Breaks the forward link

  Time: O(n)   Space: O(n) — recursive call stack
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
// 1. HEAD RECURSIVE REVERSAL — O(n) time, O(n) space
// ═══════════════════════════════════════════════════════════════

Node* reverseRecursive(Node* head) {
    // Base case: empty list or single node
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    // Recursively reverse the rest
    Node* newHead = reverseRecursive(head->next);

    // Make the next node point back to current
    head->next->next = head;
    head->next = nullptr;

    return newHead;
}

// ═══════════════════════════════════════════════════════════════
// 2. TAIL RECURSIVE REVERSAL — O(n) time, O(n) space
// ═══════════════════════════════════════════════════════════════
/*
  Tail recursion: the recursive call is the LAST operation
  (Can be optimized by compiler to iterative — O(1) space)

  DRY RUN on [1 → 2 → 3 → NULL]:

  reverseTail(1, NULL):
    next = 2, 1->next = NULL
    → reverseTail(2, 1):
      next = 3, 2->next = 1
      → reverseTail(3, 2):
        next = NULL, 3->next = 2
        → reverseTail(NULL, 3):
          BASE CASE: return 3

  Result: 3 → 2 → 1 → NULL ✅
*/

Node* reverseTailRecursive(Node* curr, Node* prev) {
    if (curr == nullptr) return prev;

    Node* next = curr->next;
    curr->next = prev;
    return reverseTailRecursive(next, curr);
}

Node* reverseTail(Node* head) {
    return reverseTailRecursive(head, nullptr);
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  RECURSIVE REVERSAL OF LINKED LIST                     ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Head Recursive
    cout << "═══ HEAD RECURSIVE REVERSAL ═══\n";
    int arr[] = {1, 2, 3, 4, 5};
    Node* head = buildList(arr, 5);
    cout << "Before: "; printList(head);
    head = reverseRecursive(head);
    cout << "After:  "; printList(head);
    freeList(head);

    // Tail Recursive
    cout << "\n═══ TAIL RECURSIVE REVERSAL ═══\n";
    head = buildList(arr, 5);
    cout << "Before: "; printList(head);
    head = reverseTail(head);
    cout << "After:  "; printList(head);
    freeList(head);

    // Edge cases
    cout << "\n═══ EDGE CASES ═══\n";
    head = nullptr;
    head = reverseRecursive(head);
    cout << "Empty: "; printList(head);

    head = new Node(42);
    head = reverseRecursive(head);
    cout << "Single: "; printList(head);
    freeList(head);

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "HEAD vs TAIL RECURSION:\n";
    cout << "─────────────────────────\n";
    cout << "Head: Process AFTER recursive call (backtracking)\n";
    cout << "Tail: Process BEFORE recursive call (no backtracking)\n";
    cout << "Head: Harder to understand, but elegant\n";
    cout << "Tail: Easier to convert to iterative\n";
    cout << "Both: O(n) time, O(n) space (call stack)\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

