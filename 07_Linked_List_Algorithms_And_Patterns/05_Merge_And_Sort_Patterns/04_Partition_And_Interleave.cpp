/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           04 — PARTITION LIST (LeetCode 86)                                ║
║           From Zero to Grandmaster — Merge & Sort Patterns                 ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Partition List (LeetCode 86) — Nodes < x before nodes >= x
 2. Sort List 0-1-2 (3-way partition)
 3. Interleave Two Lists (Weave Pattern)

DRY RUN — Partition with x=3 on [1→4→3→2→5→2]:
───────────────────────────────────────────────
  Less list:    1 → 2 → 2 → NULL    (nodes < 3)
  Greater list: 4 → 3 → 5 → NULL    (nodes >= 3)

  Connect: less tail → greater head
  Result: 1 → 2 → 2 → 4 → 3 → 5 → NULL ✅

  KEY: Maintain relative order within each partition!

  Two Dummy List Pattern:
  ┌────────────────────────────────────────────┐
  │ lessHead → [1] → [2] → [2]               │
  │ greaterHead → [4] → [3] → [5]            │
  │                                            │
  │ Connect: [2].next = [4]                   │
  │ Result: 1 → 2 → 2 → 4 → 3 → 5 → NULL    │
  └────────────────────────────────────────────┘
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
// 1. PARTITION LIST — O(n) time, O(1) space
// ═══════════════════════════════════════════════════════════════

Node* partition(Node* head, int x) {
    Node lessHead(0), greaterHead(0);
    Node* less = &lessHead;
    Node* greater = &greaterHead;

    while (head) {
        if (head->data < x) {
            less->next = head;
            less = less->next;
        } else {
            greater->next = head;
            greater = greater->next;
        }
        head = head->next;
    }

    greater->next = nullptr;          // IMPORTANT: terminate greater list
    less->next = greaterHead.next;    // Connect less tail → greater head

    return lessHead.next;
}

// ═══════════════════════════════════════════════════════════════
// 2. THREE-WAY PARTITION (Sort 0-1-2) — O(n) time, O(1) space
// ═══════════════════════════════════════════════════════════════

Node* sortList012(Node* head) {
    Node zeroH(0), oneH(0), twoH(0);
    Node* z = &zeroH, *o = &oneH, *t = &twoH;

    while (head) {
        if (head->data == 0) { z->next = head; z = z->next; }
        else if (head->data == 1) { o->next = head; o = o->next; }
        else { t->next = head; t = t->next; }
        head = head->next;
    }

    z->next = oneH.next ? oneH.next : twoH.next;
    o->next = twoH.next;
    t->next = nullptr;

    return zeroH.next;
}

// ═══════════════════════════════════════════════════════════════
// 3. INTERLEAVE / WEAVE TWO LISTS — O(n+m) time, O(1) space
// ═══════════════════════════════════════════════════════════════
/*
  DRY RUN — Interleave [1→3→5] and [2→4→6]:
  Pick 1, pick 2: 1 → 2
  Pick 3, pick 4: 1 → 2 → 3 → 4
  Pick 5, pick 6: 1 → 2 → 3 → 4 → 5 → 6
  Result: 1 → 2 → 3 → 4 → 5 → 6 → NULL ✅
*/

Node* interleave(Node* l1, Node* l2) {
    Node dummy(0);
    Node* tail = &dummy;

    while (l1 && l2) {
        tail->next = l1;
        l1 = l1->next;
        tail = tail->next;

        tail->next = l2;
        l2 = l2->next;
        tail = tail->next;
    }

    tail->next = l1 ? l1 : l2;
    return dummy.next;
}

// ═══════════════════════════════════════════════════════════════
// 4. SPLIT LL INTO TWO HALVES — Used in merge sort
// ═══════════════════════════════════════════════════════════════

pair<Node*, Node*> splitList(Node* head) {
    if (!head || !head->next) return {head, nullptr};

    Node* slow = head;
    Node* fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* second = slow->next;
    slow->next = nullptr;
    return {head, second};
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  PARTITION LIST, 3-WAY PARTITION, INTERLEAVE, SPLIT    ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Partition
    cout << "═══ PARTITION LIST (x=3) ═══\n";
    int a1[] = {1, 4, 3, 2, 5, 2};
    Node* head = buildList(a1, 6);
    cout << "Before: "; printList(head);
    head = partition(head, 3);
    cout << "After:  "; printList(head);
    freeList(head);

    // Sort 0-1-2
    cout << "\n═══ SORT 0-1-2 ═══\n";
    int a2[] = {2, 1, 0, 2, 1, 0, 1};
    head = buildList(a2, 7);
    cout << "Before: "; printList(head);
    head = sortList012(head);
    cout << "After:  "; printList(head);
    freeList(head);

    // Interleave
    cout << "\n═══ INTERLEAVE TWO LISTS ═══\n";
    int a3[] = {1, 3, 5, 7};
    int a4[] = {2, 4, 6};
    Node* l1 = buildList(a3, 4);
    Node* l2 = buildList(a4, 3);
    cout << "L1: "; printList(l1);
    cout << "L2: "; printList(l2);
    head = interleave(l1, l2);
    cout << "Interleaved: "; printList(head);
    freeList(head);

    // Split
    cout << "\n═══ SPLIT INTO TWO HALVES ═══\n";
    int a5[] = {1, 2, 3, 4, 5};
    head = buildList(a5, 5);
    cout << "Original: "; printList(head);
    auto [first, second] = splitList(head);
    cout << "First half:  "; printList(first);
    cout << "Second half: "; printList(second);
    freeList(first);
    freeList(second);

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE: LeetCode 86, 328 (Odd-Even), 725 (Split in K)\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

