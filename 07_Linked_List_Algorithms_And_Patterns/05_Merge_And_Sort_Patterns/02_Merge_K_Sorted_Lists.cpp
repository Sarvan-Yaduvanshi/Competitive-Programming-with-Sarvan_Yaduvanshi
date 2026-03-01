/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — MERGE K SORTED LISTS (LeetCode 23 — Hard)                   ║
║           From Zero to Grandmaster — Core Pattern                          ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Brute Force: Merge one by one — O(kN)
 2. Min-Heap (Priority Queue) — O(N log k)
 3. Divide and Conquer — O(N log k)

APPROACH COMPARISON:
┌─────────────────────┬───────────┬───────────┐
│ Method              │   Time    │   Space   │
├─────────────────────┼───────────┼───────────┤
│ Merge one by one    │  O(k*N)   │   O(1)    │
│ Min-Heap            │ O(N*logk) │   O(k)    │
│ Divide & Conquer    │ O(N*logk) │  O(logk)  │
└─────────────────────┴───────────┴───────────┘
  N = total number of nodes, k = number of lists

DRY RUN — Min Heap on 3 lists:
  L1: 1 → 4 → 5
  L2: 1 → 3 → 4
  L3: 2 → 6

  Heap (min): push heads → [1(L1), 1(L2), 2(L3)]
  Pop 1(L1) → push 4(L1) → Heap: [1(L2), 2(L3), 4(L1)]
  Pop 1(L2) → push 3(L2) → Heap: [2(L3), 3(L2), 4(L1)]
  Pop 2(L3) → push 6(L3) → Heap: [3(L2), 4(L1), 6(L3)]
  Pop 3(L2) → push 4(L2) → Heap: [4(L1), 4(L2), 6(L3)]
  Pop 4(L1) → push 5(L1) → Heap: [4(L2), 5(L1), 6(L3)]
  Pop 4(L2) → no more   → Heap: [5(L1), 6(L3)]
  Pop 5(L1) → no more   → Heap: [6(L3)]
  Pop 6(L3) → no more   → Heap: []

  Result: 1 → 1 → 2 → 3 → 4 → 4 → 5 → 6 → NULL ✅
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

void printList(Node* head) {
    while (head) { cout << head->data; if (head->next) cout << " -> "; head = head->next; }
    cout << " -> NULL\n";
}

void freeList(Node* head) { while (head) { Node* t = head; head = head->next; delete t; } }

Node* buildList(int arr[], int n) {
    if (n == 0) return nullptr;
    Node* head = new Node(arr[0]);
    Node* tail = head;
    for (int i = 1; i < n; i++) { tail->next = new Node(arr[i]); tail = tail->next; }
    return head;
}

// ═══════════════════════════════════════════════════════════════
// HELPER: Merge two sorted lists
// ═══════════════════════════════════════════════════════════════

Node* mergeTwoLists(Node* l1, Node* l2) {
    Node dummy(0);
    Node* tail = &dummy;
    while (l1 && l2) {
        if (l1->data <= l2->data) { tail->next = l1; l1 = l1->next; }
        else { tail->next = l2; l2 = l2->next; }
        tail = tail->next;
    }
    tail->next = l1 ? l1 : l2;
    return dummy.next;
}

// ═══════════════════════════════════════════════════════════════
// 1. MIN-HEAP APPROACH — O(N log k) time, O(k) space
// ═══════════════════════════════════════════════════════════════

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->data > b->data;  // Min-heap
    }
};

Node* mergeKListsHeap(vector<Node*>& lists) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    // Push all heads
    for (auto head : lists) {
        if (head) minHeap.push(head);
    }

    Node dummy(0);
    Node* tail = &dummy;

    while (!minHeap.empty()) {
        Node* smallest = minHeap.top();
        minHeap.pop();

        tail->next = smallest;
        tail = tail->next;

        if (smallest->next) {
            minHeap.push(smallest->next);
        }
    }

    return dummy.next;
}

// ═══════════════════════════════════════════════════════════════
// 2. DIVIDE AND CONQUER — O(N log k) time, O(log k) space
// ═══════════════════════════════════════════════════════════════

Node* mergeKListsDC(vector<Node*>& lists, int left, int right) {
    if (left == right) return lists[left];
    if (left > right) return nullptr;

    int mid = left + (right - left) / 2;
    Node* l1 = mergeKListsDC(lists, left, mid);
    Node* l2 = mergeKListsDC(lists, mid + 1, right);
    return mergeTwoLists(l1, l2);
}

Node* mergeKListsDivideConquer(vector<Node*>& lists) {
    if (lists.empty()) return nullptr;
    return mergeKListsDC(lists, 0, lists.size() - 1);
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  MERGE K SORTED LINKED LISTS                           ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Min-Heap approach
    cout << "═══ MIN-HEAP APPROACH ═══\n";
    int a1[] = {1, 4, 5};
    int a2[] = {1, 3, 4};
    int a3[] = {2, 6};
    vector<Node*> lists1 = {buildList(a1, 3), buildList(a2, 3), buildList(a3, 2)};
    for (int i = 0; i < 3; i++) { cout << "List " << i+1 << ": "; printList(lists1[i]); }
    Node* merged = mergeKListsHeap(lists1);
    cout << "Merged: "; printList(merged);
    freeList(merged);

    // Divide and Conquer
    cout << "\n═══ DIVIDE AND CONQUER APPROACH ═══\n";
    vector<Node*> lists2 = {buildList(a1, 3), buildList(a2, 3), buildList(a3, 2)};
    for (int i = 0; i < 3; i++) { cout << "List " << i+1 << ": "; printList(lists2[i]); }
    merged = mergeKListsDivideConquer(lists2);
    cout << "Merged: "; printList(merged);
    freeList(merged);

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE: LeetCode 23\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

