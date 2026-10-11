/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — MERGE TWO SORTED LISTS (LeetCode 21)                        ║
║           From Zero to Grandmaster — Core Pattern                          ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Iterative Merge (Using Dummy Node)
 2. Recursive Merge
 3. In-Place Merge

DRY RUN — Merge [1→3→5] and [2→4→6]:
─────────────────────────────────────
  dummy → ?

  Step 1: Compare 1 vs 2 → pick 1 → dummy → 1
          A: 3→5, B: 2→4→6

  Step 2: Compare 3 vs 2 → pick 2 → dummy → 1 → 2
          A: 3→5, B: 4→6

  Step 3: Compare 3 vs 4 → pick 3 → dummy → 1 → 2 → 3
          A: 5, B: 4→6

  Step 4: Compare 5 vs 4 → pick 4 → dummy → 1 → 2 → 3 → 4
          A: 5, B: 6

  Step 5: Compare 5 vs 6 → pick 5 → dummy → 1 → 2 → 3 → 4 → 5
          A: NULL, B: 6

  Step 6: A is NULL → attach remaining B
          dummy → 1 → 2 → 3 → 4 → 5 → 6 → NULL ✅

  Time: O(n + m)  Space: O(1) iterative / O(n+m) recursive
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
// 1. ITERATIVE MERGE — O(n+m) time, O(1) space
// ═══════════════════════════════════════════════════════════════

Node* mergeTwoSorted(Node* l1, Node* l2) {
    Node dummy(0);
    Node* tail = &dummy;

    while (l1 && l2) {
        if (l1->data <= l2->data) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    tail->next = (l1 != nullptr) ? l1 : l2;
    return dummy.next;
}

// ═══════════════════════════════════════════════════════════════
// 2. RECURSIVE MERGE — O(n+m) time, O(n+m) space
// ═══════════════════════════════════════════════════════════════

Node* mergeTwoSortedRecursive(Node* l1, Node* l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    if (l1->data <= l2->data) {
        l1->next = mergeTwoSortedRecursive(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeTwoSortedRecursive(l1, l2->next);
        return l2;
    }
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  MERGE TWO SORTED LINKED LISTS                        ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Iterative
    cout << "═══ ITERATIVE MERGE ═══\n";
    int a1[] = {1, 3, 5, 7};
    int b1[] = {2, 4, 6, 8};
    Node* l1 = buildList(a1, 4);
    Node* l2 = buildList(b1, 4);
    cout << "List A: "; printList(l1);
    cout << "List B: "; printList(l2);
    Node* merged = mergeTwoSorted(l1, l2);
    cout << "Merged: "; printList(merged);
    freeList(merged);

    // Recursive
    cout << "\n═══ RECURSIVE MERGE ═══\n";
    int a2[] = {1, 4, 7};
    int b2[] = {2, 3, 5, 6, 8};
    l1 = buildList(a2, 3);
    l2 = buildList(b2, 5);
    cout << "List A: "; printList(l1);
    cout << "List B: "; printList(l2);
    merged = mergeTwoSortedRecursive(l1, l2);
    cout << "Merged: "; printList(merged);
    freeList(merged);

    // Edge: one empty
    cout << "\n═══ EDGE: ONE EMPTY ═══\n";
    int a3[] = {1, 2, 3};
    l1 = buildList(a3, 3);
    l2 = nullptr;
    cout << "List A: "; printList(l1);
    cout << "List B: "; printList(l2);
    merged = mergeTwoSorted(l1, l2);
    cout << "Merged: "; printList(merged);
    freeList(merged);

    return 0;
}

