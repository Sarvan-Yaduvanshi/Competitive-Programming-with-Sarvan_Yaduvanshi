/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — FLATTEN LINKED LIST & MULTI-LEVEL LISTS                     ║
║           From Zero to Grandmaster — Advanced Pointer Manipulation         ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Flatten Sorted Sub-Lists (GFG Classic)
 2. Multi-Level Linked List with Child Pointers
 3. Flattening Nested List
 4. Memory Optimization Tricks

FLATTEN SORTED SUB-LISTS:
────────────────────────
  Each node has next (right) and down pointers.
  Each down-list is sorted. Merge all into one sorted list.

  Input:
   5 → 10 → 19 → 28
   |    |    |    |
   7   20   22   35
   |         |    |
   8        50   40
   |              |
   30            45

  Output: 5→7→8→10→19→20→22→28→30→35→40→45→50

DRY RUN — Flatten (merge from right to left):
─────────────────────────────────────────────
  Step 1: Merge [28, 35, 40, 45] with [19, 22, 50]
          → [19, 22, 28, 35, 40, 45, 50]

  Step 2: Merge result with [10, 20]
          → [10, 19, 20, 22, 28, 35, 40, 45, 50]

  Step 3: Merge result with [5, 7, 8, 30]
          → [5, 7, 8, 10, 19, 20, 22, 28, 30, 35, 40, 45, 50] ✅

  Time: O(N * M) where N = total nodes, M = max down-list length
  Space: O(1)
*/

#include <iostream>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// 1. FLATTEN SORTED SUB-LISTS (GFG Classic)
// ═══════════════════════════════════════════════════════════════

struct FNode {
    int data;
    FNode* next;   // Right pointer (main horizontal list)
    FNode* down;   // Down pointer (sub-list)
    FNode(int val) : data(val), next(nullptr), down(nullptr) {}
};

// Merge two sorted down-lists
FNode* mergeTwoDown(FNode* a, FNode* b) {
    if (!a) return b;
    if (!b) return a;

    FNode* result;
    if (a->data <= b->data) {
        result = a;
        result->down = mergeTwoDown(a->down, b);
    } else {
        result = b;
        result->down = mergeTwoDown(a, b->down);
    }
    result->next = nullptr;
    return result;
}

FNode* flatten(FNode* root) {
    if (!root || !root->next) return root;

    // Recursively flatten from the right
    root->next = flatten(root->next);

    // Merge current list with flattened right
    root = mergeTwoDown(root, root->next);

    return root;
}

void printDown(FNode* head) {
    while (head) {
        cout << head->data;
        if (head->down) cout << " -> ";
        head = head->down;
    }
    cout << " -> NULL\n";
}

void freeFList(FNode* head) {
    while (head) { FNode* t = head; head = head->down; delete t; }
}

// ═══════════════════════════════════════════════════════════════
// 2. MULTI-LEVEL LINKED LIST WITH CHILD POINTERS
// ═══════════════════════════════════════════════════════════════
/*
  Each node can have a child list (like a tree turned on its side):

  1 → 2 → 3 → 4
      |       |
      5 → 6   7
          |
          8

  Flatten DFS order: 1 → 2 → 5 → 6 → 8 → 3 → 4 → 7
*/

struct MLNode {
    int data;
    MLNode* next;
    MLNode* child;
    MLNode(int val) : data(val), next(nullptr), child(nullptr) {}
};

MLNode* flattenMultiLevel(MLNode* head) {
    if (!head) return nullptr;

    MLNode* curr = head;
    while (curr) {
        if (curr->child) {
            // Find tail of child list
            MLNode* childTail = curr->child;
            while (childTail->next) childTail = childTail->next;

            // Splice child list into main list
            childTail->next = curr->next;
            curr->next = curr->child;
            curr->child = nullptr;
        }
        curr = curr->next;
    }
    return head;
}

void printMLList(MLNode* head) {
    while (head) {
        cout << head->data;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << " -> NULL\n";
}

void freeMLList(MLNode* head) {
    while (head) { MLNode* t = head; head = head->next; delete t; }
}

// ═══════════════════════════════════════════════════════════════
// 3. MEMORY OPTIMIZATION TRICKS
// ═══════════════════════════════════════════════════════════════
/*
  TRICK 1: Node Pooling (Arena Allocation)
  ─────────────────────────────────────────
  Pre-allocate a large array of nodes. Use index instead of pointer.
  Avoids malloc/free overhead in CP.

  const int MAXN = 1e6;
  struct Node {
      int data, next;  // next is INDEX, not pointer
  } pool[MAXN];
  int poolIdx = 0;

  int newNode(int val) {
      pool[poolIdx].data = val;
      pool[poolIdx].next = -1;
      return poolIdx++;
  }

  TRICK 2: Store Data in Existing Pointers
  ──────────────────────────────────────────
  For small values, encode data in the lower bits of the pointer.
  (Advanced — only for specific scenarios)

  TRICK 3: Use vector<int> as Linked List
  ─────────────────────────────────────────
  next[i] = index of next element
  val[i] = value at index i
  Much faster than pointer-based LL in CP.
*/

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  FLATTEN LINKED LIST & MULTI-LEVEL LISTS               ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Flatten sorted sub-lists
    cout << "═══ FLATTEN SORTED SUB-LISTS ═══\n";
    FNode* f5 = new FNode(5);
    FNode* f7 = new FNode(7);
    FNode* f8 = new FNode(8);
    FNode* f30 = new FNode(30);
    FNode* f10 = new FNode(10);
    FNode* f20 = new FNode(20);
    FNode* f19 = new FNode(19);
    FNode* f22 = new FNode(22);
    FNode* f50 = new FNode(50);
    FNode* f28 = new FNode(28);
    FNode* f35 = new FNode(35);
    FNode* f40 = new FNode(40);
    FNode* f45 = new FNode(45);

    f5->down = f7; f7->down = f8; f8->down = f30;
    f10->down = f20;
    f19->down = f22; f22->down = f50;
    f28->down = f35; f35->down = f40; f40->down = f45;

    f5->next = f10; f10->next = f19; f19->next = f28;

    cout << "Flattened: ";
    FNode* flat = flatten(f5);
    printDown(flat);
    freeFList(flat);

    // Multi-level list
    cout << "\n═══ MULTI-LEVEL LINKED LIST ═══\n";
    MLNode* m1 = new MLNode(1);
    MLNode* m2 = new MLNode(2);
    MLNode* m3 = new MLNode(3);
    MLNode* m4 = new MLNode(4);
    MLNode* m5 = new MLNode(5);
    MLNode* m6 = new MLNode(6);
    MLNode* m7 = new MLNode(7);
    MLNode* m8 = new MLNode(8);

    m1->next = m2; m2->next = m3; m3->next = m4;
    m2->child = m5; m5->next = m6;
    m6->child = m8;
    m4->child = m7;

    cout << "Before flatten: 1->2->3->4 with children\n";
    MLNode* flattened = flattenMultiLevel(m1);
    cout << "After flatten:  "; printMLList(flattened);
    freeMLList(flattened);

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE: GFG Flatten a Linked List, LeetCode 430\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

